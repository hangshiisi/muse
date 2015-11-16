/********************************************************************************/
/**
 ** \file       pace2_integration_example.c
 ** \brief      PACE 2 integration example with internal tracking.
 ** \date       Dec 16, 2013
 ** \version    1.0
 ** \copyright  ipoque GmbH
 **
 ** This is a simple program to show the integration of the PACE 2 library.
 ** The program uses the internal tracking feature of the library.
 **/
/********************************************************************************/


#include <pace2.h>
#include "read_pcap.h"
#include "event_handler.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <getopt.h>

/* PACE 2 module pointer */
static PACE2_module *pace2 = NULL;

/* PACE 2 configuration structure */
static struct PACE2_global_config config;

/* Result counters */
static u64 packet_counter = 0;
static u64 byte_counter = 0;
static u64 protocol_counter[PACE2_PROTOCOL_COUNT];
static u64 protocol_counter_bytes[PACE2_PROTOCOL_COUNT];
static u64 protocol_stack_length_counter[PACE2_PROTOCOL_STACK_MAX_DEPTH];
static u64 protocol_stack_length_counter_bytes[PACE2_PROTOCOL_STACK_MAX_DEPTH];
static u64 application_counter[PACE2_APPLICATIONS_COUNT];
static u64 application_counter_bytes[PACE2_APPLICATIONS_COUNT];
static u64 attribute_counter[PACE2_APPLICATION_ATTRIBUTES_COUNT];
static u64 attribute_counter_bytes[PACE2_APPLICATION_ATTRIBUTES_COUNT];

static u64 next_packet_id = 0;

static u64 license_exceeded_packets = 0;

static const char * du_library_file = NULL;
static u64 du_load_at = 100;
static u64 du_activate_at = 100;
static u8 du_force_upgrade = 0;

/* Protocol, application and attribute name strings */
static const char *prot_long_str[] = { PACE2_PROTOCOLS_LONG_STRS };
static const char *app_str[] = { PACE2_APPLICATIONS_SHORT_STRS };

/* Memory allocation wrappers */
static void *malloc_wrapper( u64 size,
                             int thread_ID,
                             void *user_ptr,
                             int scope )
{
    return malloc( size );
} /* malloc_wrapper */

static void free_wrapper( void *ptr,
                          int thread_ID,
                          void *user_ptr,
                          int scope )
{
    free( ptr );
} /* free_wrapper */

static void *realloc_wrapper( void *ptr,
                              u64 size,
                              int thread_ID,
                              void *user_ptr,
                              int scope )
{
    return realloc( ptr, size );
}


/* panic is used for abnormal errors (allocation errors, file not found,...) */
static void panic( const char *msg )
{
    printf( "%s", msg );
    exit( 1 );
} /* panic */

/* Print classification results to stderr */
static void pace_print_results( void )
{
    u32 c;
    fprintf( stderr, "  %-20s %-15s %s\n\n", "Protocol", "Packets", "Bytes" );
    for ( c = 0; c < PACE2_PROTOCOL_COUNT; c++ ) {
        if ( protocol_counter_bytes[c] != 0 ) {
            fprintf( stderr, "  %-20s %-15llu %llu\n",
                     prot_long_str[c], protocol_counter[c], protocol_counter_bytes[c] );
        }
    }
    fprintf( stderr, "\n\n" );
    fprintf( stderr, "  %-20s %-15s %s\n\n", "Stack length", "Packets", "Bytes" );
    for ( c = 0; c < PACE2_PROTOCOL_STACK_MAX_DEPTH; c++ ) {
        fprintf( stderr, "  %-20u %-15llu %llu\n",
                 c, protocol_stack_length_counter[c], protocol_stack_length_counter_bytes[c] );
    }
    fprintf( stderr, "\n\n" );
    fprintf( stderr, "  %-20s %-15s %s\n\n", "Application", "Packets", "Bytes" );
    for ( c = 0; c < PACE2_APPLICATIONS_COUNT; c++ ) {
        if ( application_counter_bytes[c] != 0 ) {
            fprintf( stderr, "  %-20s %-15llu %llu\n",
                     app_str[c], application_counter[c], application_counter_bytes[c] );
        }
    }
    fprintf( stderr, "\n\n" );
    fprintf( stderr, "  %-20s %-15s %s\n\n", "Attribute", "Packets", "Bytes" );
    for ( c = 0; c < PACE2_APPLICATION_ATTRIBUTES_COUNT; c++ ) {
        if ( attribute_counter[c] != 0 ) {
            fprintf( stderr, "  %-20s %-15llu %llu\n",
                     pace2_get_application_attribute_str(c), attribute_counter[c], attribute_counter_bytes[c] );
        }
    }

    fprintf( stderr, "\n" );
    fprintf( stderr, "Packet counter: %llu\n", packet_counter );
    fprintf( stderr, "\n" );

    if ( license_exceeded_packets > 0 ) {
        fprintf( stderr, "License exceeded packets: %llu.\n\n", license_exceeded_packets );
    }
} /* pace_print_results */

#ifdef IPOQUE_PACE_DYNAMIC_UPGRADE
static void *ipoque_dlopen(const char *filename, int flag, void *userptr)
{
	return dlopen(filename, flag);
}

static void *ipoque_dlsym(void *handle, const char *symbol, void *userptr)
{
	return dlsym(handle, symbol);
}

static int ipoque_dlclose(void *handle, void *userptr)
{
	return dlclose(handle);
}

#endif

/* Configure and initialize PACE 2 module */
static void pace_configure_and_initialize( const char * const license_file )
{
    /* Initialize configuration with default values */
    pace2_init_default_config( &config );
    pace2_set_license_config( &config, license_file );

    /* Set necessary memory wrapper functions */
    config.general.pace2_alloc = malloc_wrapper;
    config.general.pace2_free = free_wrapper;
    config.general.pace2_realloc = realloc_wrapper;

#ifdef IPOQUE_PACE_DYNAMIC_UPGRADE
    config.dynamic_upgrade.enabled = IPQ_TRUE;
    config.dynamic_upgrade.pace2_dlopen = ipoque_dlopen;
    config.dynamic_upgrade.pace2_dlsym = ipoque_dlsym;
    config.dynamic_upgrade.pace2_dlclose = ipoque_dlclose;
#endif

    /* Stage 1: enable IP defragmentation */
    config.s1_preparing.defrag.enabled = 1;

    /* Stage 2: enable PARO and set necessary values */
    config.s2_reordering.enabled = 1;
    config.s2_reordering.packet_buffer_size = 16 * 1024 * 1024;
    config.s2_reordering.packet_timeout = 5 * config.general.clock_ticks_per_second;

    /* Stage 3: enable specific classification components */
    config.s3_classification.csi_enabled = 1;

    /* Initialize PACE 2 detection module */
    pace2 = pace2_init_module( &config );

    if ( pace2 == NULL ) {
        panic( "Initialization of PACE module failed\n" );
    }

    /* Licensing */
    if ( license_file != NULL ) {

        PACE2_class_return_state retval;
        PACE2_classification_status_event lic_event;

        memset(&lic_event, 0, sizeof(PACE2_classification_status_event));
        retval = pace2_class_get_license(pace2, 0, &lic_event);
        if (retval == PACE2_CLASS_SUCCESS) {
            pace2_debug_event(stdout, (PACE2_event const * const) &lic_event);
        }
    }

} /* pace_configure_and_initialize */

static void stage3_to_5( void )
{
    const PACE2_event *event;
    PACE2_bitmask pace2_event_mask;
    struct pace2_packet_descriptor *out_pd;

    /* Process stage 3 and 4 as long as packets are available from stage 2 */
    while ( (out_pd = pace2_s2_get_next_packet(pace2, 0)) ) {

        /* Account every processed packet */
        packet_counter++;
        byte_counter += out_pd->framing->stack[0].frame_length;

        /* Process stage 3: packet classification */
        if ( pace2_s3_process_packet( pace2, 0, out_pd, &pace2_event_mask ) != PACE2_S3_SUCCESS ) {
            continue;
        } /* Stage 3 processing */

        /* Get all thrown events of stage 3 */
        while ( ( event = pace2_get_next_event(pace2, 0) ) ) {
            /* some additional processing is necessary */
            if ( event->header.type == PACE2_CLASSIFICATION_RESULT ) {
                PACE2_classification_result_event const * const classification = &event->classification_result_data;
                u8 attribute_iterator;

                protocol_counter[classification->protocol.stack.entry[classification->protocol.stack.length-1]]++;
                protocol_counter_bytes[classification->protocol.stack.entry[classification->protocol.stack.length-1]] += out_pd->framing->stack[0].frame_length;
                protocol_stack_length_counter[classification->protocol.stack.length - 1]++;
                protocol_stack_length_counter_bytes[classification->protocol.stack.length - 1] += out_pd->framing->stack[0].frame_length;

                application_counter[classification->application.type]++;
                application_counter_bytes[classification->application.type] += out_pd->framing->stack[0].frame_length;

                for ( attribute_iterator = 0; attribute_iterator < classification->application.attributes.length; attribute_iterator++) {
                    attribute_counter[classification->application.attributes.list[attribute_iterator]]++;
                    attribute_counter_bytes[classification->application.attributes.list[attribute_iterator]] += out_pd->framing->stack[0].frame_length;
                }
            } else if ( event->header.type == PACE2_LICENSE_EXCEEDED_EVENT ) {
                license_exceeded_packets++;
            }
        }
    } /* Stage 2 packets */

    /* Process stage 5: timeout handling */
    if ( pace2_s5_handle_timeout( pace2, 0, &pace2_event_mask ) != 0 ) {
        return;
    }
} /* stage3_to_5 */

static void stage1_and_2( const uint64_t time, const struct iphdr *iph, uint16_t ipsize )
{
    struct pace2_packet_descriptor pd;

    if (du_library_file != NULL) {
        if (next_packet_id == du_load_at) {
            PACE2_dynamic_upgrade_load_state ret = pace2_dynamic_upgrade_load_library(pace2, du_library_file, du_force_upgrade);
            printf("Load library result: %u\n", ret);
            if (ret != PACE2_DYNAMIC_UPGRADE_LOAD_SUCCESSFUL) {
                panic("Could not load library.\n");
            }
        }

        if (next_packet_id == du_activate_at) {
            PACE2_dynamic_upgrade_activate_state ret = pace2_dynamic_upgrade_activate_loaded_library(pace2);
            printf("Activate library result: %u\n", ret);
            if (ret != PACE2_DYNAMIC_UPGRADE_ACTIVATE_SUCCESSFUL) {
                panic("Could not activate library.\n");
            }
        }
    }

    /* Stage 1: Prepare packet descriptor and run ip defragmentation */
    if (pace2_s1_process_packet( pace2, 0, time, iph, ipsize, PACE2_S1_L3, &pd, NULL, 0 ) != PACE2_S1_SUCCESS) {
        return;
    }

    /* Set unique packet id. The flow_id is set by the internal flow tracking */
    pd.packet_id = ++next_packet_id;

    /* Stage 2: Packet reordering */
    if ( pace2_s2_process_packet( pace2, 0, &pd ) != PACE2_S2_SUCCESS ) {
        return;
    }

    stage3_to_5();
} /* stage1_and_2 */

static void pace_cleanup_and_exit( void )
{
    /* Flush any remaining packets from the buffers */
    pace2_flush_engine( pace2, 0 );

    /* Process packets which are ejected after flushing */
    stage3_to_5();

    /* Output detection results */
    pace_print_results();

    /* Destroy PACE 2 module and free memory */
    pace2_exit_module( pace2 );
} /* pace_cleanup_and_exit */

int main( int argc, char **argv )
{
    const char * license_file = NULL;
    const char * trace_file = NULL;

    char option;

    const struct option option_list[] = {
        {"du_library", required_argument, 0, 'l'},
        {"du_load_at", required_argument, 0, 'L'},
        {"du_activate_at", required_argument, 0, 'A'},
        {"du_force", no_argument, 0, 'F'},
        {"license", required_argument, 0, 'i'},
        {"file", required_argument, 0, 'f'},
        {0, 0, 0, 0}
    };

    while ((option = getopt_long(argc, argv, "l:L:A:i:f:F", &option_list[0], NULL)) > 0) {
        switch (option) {
            case 'f':
                trace_file = optarg;
                break;

            case 'i':
                license_file = optarg;
                break;

            case 'l':
                du_library_file = optarg;
                break;

            case 'L':
                du_load_at = strtoull(optarg, NULL, 10);
                break;

            case 'A':
                du_activate_at = strtoull(optarg, NULL, 10);
                break;

            case 'F':
                du_force_upgrade = 1;
                break;
        }
    }

    if ( trace_file == NULL ) {
        panic( "PCAP file not given, please give the pcap file as parameter with -f\n" );
    }

    /* Initialize PACE 2 */
    pace_configure_and_initialize( license_file );

    /* Read the pcap file and pass packets to stage1_and_2 */
    if ( read_pcap_loop( trace_file, config.general.clock_ticks_per_second, &stage1_and_2 ) != 0 ) {
        panic( "could not open pcap interface / file\n" );
    }

    pace_cleanup_and_exit();

    return 0;
} /* main */
