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

#ifdef WIN32
#include <WinSock2.h>
#include <inttypes.h>
#endif

#include <pace2.h>
#include "event_handler.h"
#include "pace2_netfilter.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <getopt.h>

static u8 running = 1;
static int full_features = 0;

/* content struct */
typedef struct {
	
	struct pace2_netfilter netfilter;
	/* PACE 2 module pointer */
	 PACE2_module *pace2;

	/* PACE 2 configuration structure */
	 struct PACE2_global_config config;
	 

	/* Result counters */
	u64 packet_counter ;
	u64 byte_counter;
	u64 protocol_counter[PACE2_PROTOCOL_COUNT];
	u64 protocol_counter_bytes[PACE2_PROTOCOL_COUNT];
	u64 protocol_stack_length_counter[PACE2_PROTOCOL_STACK_MAX_DEPTH];
	u64 protocol_stack_length_counter_bytes[PACE2_PROTOCOL_STACK_MAX_DEPTH];
	u64 application_counter[PACE2_APPLICATIONS_COUNT];
	u64 application_counter_bytes[PACE2_APPLICATIONS_COUNT];
	u64 attribute_counter[PACE2_APPLICATION_ATTRIBUTES_COUNT];
	u64 attribute_counter_bytes[PACE2_APPLICATION_ATTRIBUTES_COUNT];
	u64 http_response_payload_bytes;

	u64 next_packet_id;

	u64 license_exceeded_packets;

	PACE2_timestamp last_output_ts;
} content_t;

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
static void pace_print_results( content_t * const content )
{
    u32 c;
    fprintf( stderr, "  %-20s %-15s %s\n\n", "Protocol", "Packets", "Bytes" );
    for ( c = 0; c < PACE2_PROTOCOL_COUNT; c++ ) {
        if ( content->protocol_counter_bytes[c] != 0 ) {
            fprintf( stderr, "  %-20s %-15llu %llu\n",
                     prot_long_str[c], content->protocol_counter[c], content->protocol_counter_bytes[c] );
        }
    }
    fprintf( stderr, "\n\n" );
    fprintf( stderr, "  %-20s %-15s %s\n\n", "Stack length", "Packets", "Bytes" );
    for ( c = 0; c < PACE2_PROTOCOL_STACK_MAX_DEPTH; c++ ) {
        fprintf( stderr, "  %-20u %-15llu %llu\n",
                 c, content->protocol_stack_length_counter[c], content->protocol_stack_length_counter_bytes[c] );
    }
    fprintf( stderr, "\n\n" );
    fprintf( stderr, "  %-20s %-15s %s\n\n", "Application", "Packets", "Bytes" );
    for ( c = 0; c < PACE2_APPLICATIONS_COUNT; c++ ) {
        if ( content->application_counter_bytes[c] != 0 ) {
            fprintf( stderr, "  %-20s %-15llu %llu\n",
                     app_str[c],content->application_counter[c], content->application_counter_bytes[c] );
        }
    }
    fprintf( stderr, "\n\n" );
    fprintf( stderr, "  %-20s %-15s %s\n\n", "Attribute", "Packets", "Bytes" );
    for ( c = 0; c < PACE2_APPLICATION_ATTRIBUTES_COUNT; c++ ) {
        if ( content->attribute_counter[c] != 0 ) {
            fprintf( stderr, "  %-20s %-15llu %llu\n",
                     pace2_get_application_attribute_str(c), content->attribute_counter[c], content->attribute_counter_bytes[c] );
        }
    }

    fprintf( stderr, "\n" );
    fprintf( stderr, "HTTP response payload bytes: %llu\n", content->http_response_payload_bytes );
    fprintf( stderr, "\n" );

    fprintf( stderr, "\n" );
    fprintf( stderr, "Packet counter: %llu\n", content->packet_counter );
    fprintf( stderr, "\n" );

    if ( content->license_exceeded_packets > 0 ) {
        fprintf( stderr, "License exceeded packets: %llu.\n\n", content->license_exceeded_packets );
    }
} /* pace_print_results */

/* Configure and initialize PACE 2 module */
static void pace_configure_and_initialize( content_t * const content, const char * const license_file )
{
    /* Initialize configuration with default values */
    pace2_init_default_config( &content->config );
    pace2_set_license_config( &content->config, license_file );

    /* Set necessary memory wrapper functions */
    content->config.general.pace2_alloc = malloc_wrapper;
    content->config.general.pace2_free = free_wrapper;
    content->config.general.pace2_realloc = realloc_wrapper;

    /* set size of hash table for flow and subscriber tracking */
    // content->config.tracking.flow.generic.max_size.memory_size = 400 * 1024 * 1024;
    // content->config.tracking.subscriber.generic.max_size.memory_size = 400 * 1024 * 1024;

    if (full_features) {
        printf("Enabling full classification and decoding feature set.\n\n");

        /* Stage 1: enable IP defragmentation */
        content->config.s1_preparing.defrag.enabled = 1;
        content->config.s1_preparing.max_framing_depth = 10;
        content->config.s1_preparing.max_decaps_level = 10;

        /* Stage 2: enable PARO and set necessary values */
        content->config.s2_reordering.enabled = 1;
        content->config.s2_reordering.packet_buffer_size = 16 * 1024 * 1024;
        content->config.s2_reordering.packet_timeout = 5 * content->config.general.clock_ticks_per_second;

        /* Stage 3: enable specific classification components */
        content->config.s3_classification.asym_detection_enabled = 1;
        content->config.s3_classification.sit.enabled = 1;
        content->config.s3_classification.sit.key_reduce_factor = 1;
        content->config.s3_classification.sit.memory = 1 * 1024 * 1024;
        content->config.s3_classification.cdn_caching_enabled = 1;
        content->config.s3_classification.os_enabled = 1;
        content->config.s3_classification.nat_enabled = 1;
        content->config.s3_classification.rtp_performance_enabled = 1;
        content->config.s3_classification.csi_enabled = 1;

        /* Uncomment the specific dissector to generate meta data events */
//        config.s3_classification.dissector_metadata_config.tcp.enabled = IPQ_TRUE;
//        config.s3_classification.dissector_metadata_config.ip.enabled = IPQ_TRUE;
//        config.s3_classification.dissector_metadata_config.h264.enabled = IPQ_TRUE;
//        config.s3_classification.dissector_metadata_config.amr.enabled = IPQ_TRUE;
//        config.s3_classification.dissector_metadata_config.rtp.enabled = IPQ_TRUE;
//        config.s3_classification.dissector_metadata_config.id3.enabled = IPQ_TRUE;
//        config.s3_classification.dissector_metadata_config.mp3.enabled = IPQ_TRUE;
//        config.s3_classification.dissector_metadata_config.http.enabled = IPQ_TRUE;
//        config.s3_classification.dissector_metadata_config.mp4.enabled = IPQ_TRUE;

        /* Stage 4: enable decoding */
        content->config.s4_decoding.enabled = 1;
    } else {
        printf("Using minimal feature set.\n\n");
    }

    /* uncomment the following line to only activate classification of protocol HTTP */
    // PACE2_PROTOCOLS_BITMASK_RESET(config.s3_classification.active_classifications.bitmask);
    // content->config.s3_classification.active_classifications.protocols.http = IPQ_TRUE;

    /* uncomment the following line to only activate decoding of protocol HTTP */
    // PACE2_PROTOCOLS_BITMASK_RESET(config.s4_decoding.active_advanced_decoders.bitmask);
    // content->config.s4_decoding.active_advanced_decoders.protocols.http = IPQ_TRUE;

    /* Initialize PACE 2 detection module */
    content->pace2 = pace2_init_module( &content->config );

    if ( content->pace2 == NULL ) {
        panic( "Initialization of PACE module failed\n" );
    }

    /* Licensing */
    if ( license_file != NULL ) {

        PACE2_class_return_state retval;
        PACE2_classification_status_event lic_event;

        memset(&lic_event, 0, sizeof(PACE2_classification_status_event));
        retval = pace2_class_get_license(content->pace2, 0, &lic_event);
        if (retval == PACE2_CLASS_SUCCESS) {
            pace2_debug_event(stdout, (PACE2_event const * const) &lic_event);
        }
    }
} /* pace_configure_and_initialize */

/* Print out all PACE 2 events currently in the event queue */
static void process_events( content_t * const content )
{
    PACE2_event *event;

    while ( ( event = pace2_get_next_event( content->pace2, 0 ) ) ) {
        /* some additional processing is necessary */
        if ( event->header.type == PACE2_CLASS_HTTP_EVENT ) {
            const PACE2_class_HTTP_event * const http_event = &event->http_class_meta_data;
            if (http_event->meta_data_type == PACE2_CLASS_HTTP_RESPONSE_DATA_TRANSFER) {
                const struct ipd_class_http_transfer_payload_struct * const http_payload = &http_event->event_data.response_data_transfer;
                content->http_response_payload_bytes += http_payload->data.content.length;
            }
        }
        pace2_debug_advanced_event(stdout, event);
    }
} /* process_events */

static void stage3_to_5( content_t * const content )
{
    const PACE2_event *event;
    PACE2_bitmask pace2_event_mask;
    PACE2_packet_descriptor *out_pd;

    /* Process stage 3 and 4 as long as packets are available from stage 2 */
    while ( (out_pd = pace2_s2_get_next_packet(content->pace2, 0)) ) {

        /* Account every processed packet */
        content->packet_counter++;
        content->byte_counter += out_pd->framing->stack[0].frame_length;

        /* Process stage 3: packet classification */
        if ( pace2_s3_process_packet( content->pace2, 0, out_pd, &pace2_event_mask ) != PACE2_S3_SUCCESS ) {
            continue;
        } /* Stage 3 processing */

        /* Get all thrown events of stage 3 */
        while ( ( event = pace2_get_next_event(content->pace2, 0) ) ) {
            /* some additional processing is necessary */
            if ( event->header.type == PACE2_CLASSIFICATION_RESULT ) {
                PACE2_classification_result_event const * const classification = &event->classification_result_data;
                u8 attribute_iterator;

                content->protocol_counter[classification->protocol.stack.entry[classification->protocol.stack.length-1]]++;
                content->protocol_counter_bytes[classification->protocol.stack.entry[classification->protocol.stack.length-1]] += out_pd->framing->stack[0].frame_length;
                content->protocol_stack_length_counter[classification->protocol.stack.length - 1]++;
                content->protocol_stack_length_counter_bytes[classification->protocol.stack.length - 1] += out_pd->framing->stack[0].frame_length;

                content->application_counter[classification->application.type]++;
                content->application_counter_bytes[classification->application.type] += out_pd->framing->stack[0].frame_length;

                for ( attribute_iterator = 0; attribute_iterator < classification->application.attributes.length; attribute_iterator++) {
                    content->attribute_counter[classification->application.attributes.list[attribute_iterator]]++;
                    content->attribute_counter_bytes[classification->application.attributes.list[attribute_iterator]] += out_pd->framing->stack[0].frame_length;
                }
            } else if ( event->header.type == PACE2_LICENSE_EXCEEDED_EVENT ) {
                content->license_exceeded_packets++;
            }
        } /* Stage 3 event processing */

        /* Process stage 4: protocol decoding */
        if ( pace2_s4_process_packet( content->pace2, 0, out_pd, NULL, &pace2_event_mask ) != PACE2_S4_SUCCESS ) {
            continue;
        }

        /* Print out decoder events */
        process_events(content);

    } /* Stage 2 packets */

    /* Process stage 5: timeout handling */
    if ( pace2_s5_handle_timeout( content->pace2, 0, &pace2_event_mask ) != 0 ) {
        return;
    }

    /* Print out decoder events generated while cleaning up flows that timed out */
    process_events( content );

} /* stage3_to_5 */

static void stage1_and_2( const struct timeval * const time,
                               const void * const payload,
                               uint16_t payload_len,
                               const uint64_t * const packet_id,
                               const uint8_t layer,
                               void * const user_data )
{
    PACE2_packet_descriptor pd;
    content_t * const content = user_data;
    PACE2_s1_input_frame_type stage1_layer_type;
    
        /* calculate timestamp in given resolution */
    u64 timestamp = ( ( u64 ) time->tv_sec ) * content->config.general.clock_ticks_per_second + time->tv_usec / ( 1000000 / content->config.general.clock_ticks_per_second );
    
    if ( layer == 2 ) {
        stage1_layer_type = PACE2_S1_L2;
    } else if ( layer == 3 ) {
        stage1_layer_type = PACE2_S1_L3;
    } else {
        return;
    }
    /* Stage 1: Prepare packet descriptor and run ip defragmentation */
    if ( pace2_s1_process_packet( content->pace2, 0, timestamp, (struct iphdr *)payload, payload_len, stage1_layer_type, &pd, NULL, 0 ) != PACE2_S1_SUCCESS ) {
        // pace2_netfilter_set_verdict( &content->netfilter, *packet_id, PACE2_NF_ACCEPT );
        nfq_set_verdict( content->netfilter.nfq_q_h, *packet_id, PACE2_NF_ACCEPT, 
                
                           payload_len, 
                           payload);
        return;
    }
    
        /* Set unique packet id. The flow_id is set by the internal flow tracking */
    pd.packet_id = *packet_id;

    pd.packet_user_data = ( void * ) packet_id;
    pd.packet_user_data_len = sizeof(*packet_id);

    /* Stage 2: Packet reordering */
    if ( pace2_s2_process_packet( content->pace2, 0, &pd ) != PACE2_S2_SUCCESS ) {
        return;
    }

    stage3_to_5(content);
        nfq_set_verdict( content->netfilter.nfq_q_h, *packet_id, PACE2_NF_ACCEPT, 
                
                           payload_len, 
                           payload);
} /* stage1_and_2 */

static void pace_cleanup_and_exit( content_t * const content )
{
    if ( content == NULL ) return;
    pace2_netfilter_exit( &content->netfilter );
    /* Flush any remaining packets from the buffers */
    pace2_flush_engine( content->pace2, 0 );

    /* Process packets which are ejected after flushing */
    stage3_to_5( content );

    /* Output detection results */
    pace_print_results( content );

    /* Destroy PACE 2 module and free memory */
    pace2_exit_module( content->pace2 );
} /* pace_cleanup_and_exit */

void print_help_and_exit(void) {
    printf("Usage: pace2_integration_example [options]\n\n");
    printf("  -a\tEnable full PACE feature set.\n");
    printf("  -l\tUse a specific license file.\n");
    printf("  -h\tPrint this help message\n\n");
    printf("  -n\tNetfilter\n\n");
    exit(0);
}

int main( int argc, char **argv )
{
	content_t content = {};

    const char * license_file = NULL;
    int c = 0;

    while ((c = getopt(argc, argv, "ahn:l:")) != -1) {
        switch (c) {
            case 'a':
                full_features = 1;
                break;
            case 'l':
                license_file = optarg;
                break;
            case 'h':
                print_help_and_exit();
                break;
            case 'n':
                break;
        }
    }

    if (argc == 1) {
        print_help_and_exit();
    }

    /* Initialize PACE 2 */
    pace2_netfilter_initialize( &content.netfilter, stage1_and_2, &content );
    pace_configure_and_initialize( &content, license_file );
    
    pace2_netfilter_packet_loop( &content.netfilter, &running );

    pace_cleanup_and_exit( &content );

    return 0;
} /* main */
