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

#include "pthread.h"

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

static u64 license_exceeded_packets = 0;

/* Protocol, application and attribute name strings */
static const char *prot_long_str[] = { PACE2_PROTOCOLS_LONG_STRS };
static const char *app_str[] = { PACE2_APPLICATIONS_SHORT_STRS };

#define MAX_PACKET_SIZE 1600
#define RING_BUFFER_MAX_ELEMENTS 50

/* best performance is achieved, when the worker thread count is 1 less than
   the number of logical cores available, so one thread is free for reading
   and distributing the packets */
#define EXAMPLE_THREAD_COUNT 3

#define RINGBBUFFER_LAST_WRITTEN_EMPTY -1

struct packet_struct {
    uint64_t time;
    uint16_t ipsize;
    u8 packet_payload[MAX_PACKET_SIZE];
};

struct pace2_example_thread_struct {
    pthread_t thread;

    u64 packet_counter;
    u64 byte_counter;
    u64 protocol_counter[PACE2_PROTOCOL_COUNT];
    u64 protocol_counter_bytes[PACE2_PROTOCOL_COUNT];
    u64 protocol_stack_length_counter[PACE2_PROTOCOL_STACK_MAX_DEPTH];
    u64 protocol_stack_length_counter_bytes[PACE2_PROTOCOL_STACK_MAX_DEPTH];
    u64 application_counter[PACE2_APPLICATIONS_COUNT];
    u64 application_counter_bytes[PACE2_APPLICATIONS_COUNT];
    u64 attribute_counter[PACE2_APPLICATION_ATTRIBUTES_COUNT];
    u64 attribute_counter_bytes[PACE2_APPLICATION_ATTRIBUTES_COUNT];
    u64 license_exceeded_packets;
    u64 next_packet_id;

    struct packet_struct ring_packet_buffer[RING_BUFFER_MAX_ELEMENTS];
    volatile int ring_buffer_last_written_elem;
    volatile int ring_buffer_last_read_elem;

    u8 thread_id;
    u8 done;

} pace2_example_wt[EXAMPLE_THREAD_COUNT];

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

/* Print out all PACE 2 events currently in the event queue */
static void process_events( u8 t_id)
{
    PACE2_event *event;

    while ( ( event = pace2_get_next_event( pace2, t_id ) ) ) {
        /* some additional processing is necessary */
    }
} /* process_events */

static void stage3_to_5( u8 t_id )
{
    const PACE2_event *event;
    PACE2_bitmask pace2_event_mask;
    PACE2_packet_descriptor *out_pd;

    /* Process stage 3 and 4 as long as packets are available from stage 2 */
    while ( (out_pd = pace2_s2_get_next_packet(pace2, t_id)) ) {

        /* Account every processed packet */
        pace2_example_wt[t_id].packet_counter++;
        pace2_example_wt[t_id].byte_counter += out_pd->framing->stack[0].frame_length;

        /* Process stage 3: packet classification */
        if ( pace2_s3_process_packet( pace2, t_id, out_pd, &pace2_event_mask ) != PACE2_S3_SUCCESS ) {
            continue;
        } /* Stage 3 processing */

        /* Get all thrown events of stage 3 */
        while ( ( event = pace2_get_next_event(pace2, t_id) ) ) {
            /* some additional processing is necessary */
            if ( event->header.type == PACE2_CLASSIFICATION_RESULT ) {
                PACE2_classification_result_event const * const classification = &event->classification_result_data;
                u8 attribute_iterator;

                pace2_example_wt[t_id].protocol_counter[classification->protocol.stack.entry[classification->protocol.stack.length-1]]++;
                pace2_example_wt[t_id].protocol_counter_bytes[classification->protocol.stack.entry[classification->protocol.stack.length-1]] += out_pd->framing->stack[0].frame_length;
                pace2_example_wt[t_id].protocol_stack_length_counter[classification->protocol.stack.length - 1]++;
                pace2_example_wt[t_id].protocol_stack_length_counter_bytes[classification->protocol.stack.length - 1] += out_pd->framing->stack[0].frame_length;

                pace2_example_wt[t_id].application_counter[classification->application.type]++;
                pace2_example_wt[t_id].application_counter_bytes[classification->application.type] += out_pd->framing->stack[0].frame_length;

                for ( attribute_iterator = 0; attribute_iterator < classification->application.attributes.length; attribute_iterator++) {
                    pace2_example_wt[t_id].attribute_counter[classification->application.attributes.list[attribute_iterator]]++;
                    pace2_example_wt[t_id].attribute_counter_bytes[classification->application.attributes.list[attribute_iterator]] += out_pd->framing->stack[0].frame_length;
                }
            } else if ( event->header.type == PACE2_LICENSE_EXCEEDED_EVENT ) {
                pace2_example_wt[t_id].license_exceeded_packets++;
            }
        } /* Stage 3 event processing */

        /* Process stage 4: protocol decoding */
        if ( pace2_s4_process_packet( pace2, t_id, out_pd, NULL, &pace2_event_mask ) != PACE2_S4_SUCCESS ) {
            continue;
        }

        /* Print out decoder events */
        process_events( t_id );

    } /* Stage 2 packets */

    /* Process stage 5: timeout handling */
    if ( pace2_s5_handle_timeout( pace2, t_id, &pace2_event_mask ) != 0 ) {
        return;
    }

    /* Print out decoder events generated while cleaning up flows that timed out */
    process_events( t_id );

} /* stage3_to_5 */

void stage1_and_2( const uint64_t time, const struct iphdr *iph, uint16_t ipsize, u8 t_id )
{
    PACE2_packet_descriptor pd;

    /* Stage 1: Prepare packet descriptor and run ip defragmentation */
    if (pace2_s1_process_packet( pace2, t_id, time, iph, ipsize, PACE2_S1_L3, &pd, NULL, 0 ) != PACE2_S1_SUCCESS) {
        return;
    }

    /* Set unique packet id. The flow_id is set by the internal flow tracking */
    pd.packet_id = ++pace2_example_wt[t_id].next_packet_id;

    /* Stage 2: Packet reordering */
    if ( pace2_s2_process_packet( pace2, t_id, &pd ) != PACE2_S2_SUCCESS ) {
        return;
    }

    stage3_to_5( t_id );
} /* stage1_and_2 */

void *worker_thread_main(void *t)
{
    struct pace2_example_thread_struct *thread_struct = (struct pace2_example_thread_struct *)t;
    u16 next_buffer_id_to_process;

    // go to sleep if no data is available
    while (thread_struct->ring_buffer_last_written_elem == RINGBBUFFER_LAST_WRITTEN_EMPTY) {
        usleep( 0 );
        if (thread_struct->done == 1) {
            break;
        }
    }

    next_buffer_id_to_process = (thread_struct->ring_buffer_last_read_elem + 1) % RING_BUFFER_MAX_ELEMENTS;
    while (thread_struct->done == 0 ||
           (next_buffer_id_to_process != thread_struct->ring_buffer_last_written_elem &&
            thread_struct->ring_buffer_last_written_elem != RINGBBUFFER_LAST_WRITTEN_EMPTY)) {

        next_buffer_id_to_process = (thread_struct->ring_buffer_last_read_elem + 1) % RING_BUFFER_MAX_ELEMENTS;
        // process
        stage1_and_2( thread_struct->ring_packet_buffer[next_buffer_id_to_process].time,
                      (const struct iphdr *)&thread_struct->ring_packet_buffer[next_buffer_id_to_process].packet_payload[0],
                      thread_struct->ring_packet_buffer[next_buffer_id_to_process].ipsize,
                      thread_struct->thread_id );

        thread_struct->ring_buffer_last_read_elem = next_buffer_id_to_process;


        while (next_buffer_id_to_process == thread_struct->ring_buffer_last_written_elem && thread_struct->done == 0) {
        usleep( 0 );

            if (thread_struct->done == 1 && next_buffer_id_to_process == thread_struct->ring_buffer_last_written_elem) {
                break;
            }
        }
        if (thread_struct->done == 1 && next_buffer_id_to_process == thread_struct->ring_buffer_last_written_elem) {
            break;
        }
    }

    /* Flush any remaining packets from the buffers */
    pace2_flush_engine( pace2, thread_struct->thread_id );

    /* Process packets which are ejected after flushing */
    stage3_to_5( thread_struct->thread_id );

    return NULL;
}

void packet_distribution(const uint64_t time, const struct iphdr *iph, uint16_t ipsize)
{
    u8 t_id = 0;
    u16 next_buffer_id_to_write;

    if (iph->version == 4) {
        u_int32_t used_addr = ntohl(iph->saddr) > ntohl(iph->daddr) ? ntohl(iph->daddr) : ntohl(iph->saddr);
        t_id = used_addr % EXAMPLE_THREAD_COUNT;
    }

    // copy the packet to the corresponding q and wakeup the correspnding worker thread
    next_buffer_id_to_write = (pace2_example_wt[t_id].ring_buffer_last_written_elem + 1) % RING_BUFFER_MAX_ELEMENTS;

    // fall asleep if nothing was read so far or the buffer is full
    while ((next_buffer_id_to_write == 0 && pace2_example_wt[t_id].ring_buffer_last_written_elem == RING_BUFFER_MAX_ELEMENTS - 1 &&
            pace2_example_wt[t_id].ring_buffer_last_read_elem == RINGBBUFFER_LAST_WRITTEN_EMPTY) ||
           (next_buffer_id_to_write == pace2_example_wt[t_id].ring_buffer_last_read_elem)) {

        usleep( 0 );
    }

    pace2_example_wt[t_id].ring_packet_buffer[next_buffer_id_to_write].time = time;
    pace2_example_wt[t_id].ring_packet_buffer[next_buffer_id_to_write].ipsize = ipsize;
    memcpy( &pace2_example_wt[t_id].ring_packet_buffer[next_buffer_id_to_write].packet_payload[0],
            iph,
            ipsize );

    pace2_example_wt[t_id].ring_buffer_last_written_elem = next_buffer_id_to_write;
}

/* Configure and initialize PACE 2 module */
static void pace_configure_and_initialize( const char * const license_file )
{
    u8 i;

    /* Initialize configuration with default values */
    pace2_init_default_config( &config );
    pace2_set_license_config( &config, license_file );

    /* Set necessary memory wrapper functions */
    config.general.pace2_alloc = malloc_wrapper;
    config.general.pace2_free = free_wrapper;
    config.general.pace2_realloc = realloc_wrapper;

    /* Set number of threads*/
    config.general.number_of_threads = EXAMPLE_THREAD_COUNT;

    /* set size of hash table for flow and subscriber tracking */
    // config.tracking.flow.generic.max_size.memory_size = 400 * 1024 * 1024;
    // config.tracking.subscriber.generic.max_size.memory_size = 400 * 1024 * 1024;

    /* The following features improves detection rate */

    /* Stage 1: enable IP defragmentation */
    // config.s1_preparing.defrag.enabled = 1;
    // config.s1_preparing.max_framing_depth = 10;
    // config.s1_preparing.max_decaps_level = 10;

    /* Stage 2: enable PARO and set necessary values */
    // config.s2_reordering.enabled = 1;
    // config.s2_reordering.packet_buffer_size = 16 * 1024 * 1024;
    // config.s2_reordering.packet_timeout = 5 * config.general.clock_ticks_per_second;

    /* Stage 3: enable specific classification components */
    // config.s3_classification.asym_detection_enabled = 1
    // config.s3_classification.sit.enabled = 1;
    // config.s3_classification.sit.key_reduce_factor = 1;
    // config.s3_classification.sit.memory = 1 * 1024 * 1024;

    // uncomment the following line to only activate classification of protocol HTTP
    // PACE2_PROTOCOLS_BITMASK_RESET(config.s3_classification.active_classifications.bitmask);
    // config.s3_classification.active_classifications.protocols.http = IPQ_TRUE;

    /* Stage 4: enable decoding */
    //config.s4_decoding.enabled = 1;
    // uncomment the following line to only activate decoding of protocol HTTP
    // PACE2_PROTOCOLS_BITMASK_RESET(config.s4_decoding.active_advanced_decoders.bitmask);
    // config.s4_decoding.active_advanced_decoders.protocols.http = IPQ_TRUE;

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

    memset( &pace2_example_wt, 0, sizeof(struct pace2_example_thread_struct) * EXAMPLE_THREAD_COUNT );
    for ( i = 0; i < EXAMPLE_THREAD_COUNT; ++i ) {
        pace2_example_wt[i].thread_id = i;
        pace2_example_wt[i].ring_buffer_last_written_elem = RINGBBUFFER_LAST_WRITTEN_EMPTY;
        pace2_example_wt[i].ring_buffer_last_read_elem = RINGBBUFFER_LAST_WRITTEN_EMPTY;

        pthread_create(&pace2_example_wt[i].thread, NULL, worker_thread_main, (void *)&(pace2_example_wt[i]));
    }
} /* pace_configure_and_initialize */

static void pace_cleanup_and_exit( void )
{
    u8 i;

    /* join processing threads and sum up results */
    for ( i = 0; i < EXAMPLE_THREAD_COUNT; ++i ) {
        u16 j;
        pace2_example_wt[i].done = 1;
        pthread_join(pace2_example_wt[i].thread, NULL);

        packet_counter += pace2_example_wt[i].packet_counter;
        fprintf(stderr, "thread: %u, had packets: %llu\n",
                i,
                pace2_example_wt[i].packet_counter);
        byte_counter += pace2_example_wt[i].byte_counter;

        license_exceeded_packets += pace2_example_wt[i].license_exceeded_packets;

        for ( j = 0; j < PACE2_PROTOCOL_COUNT; ++j ) {
            protocol_counter[j] += pace2_example_wt[i].protocol_counter[j];
            protocol_counter_bytes[j] += pace2_example_wt[i].protocol_counter_bytes[j];
        }
        for ( j = 0; j < PACE2_PROTOCOL_STACK_MAX_DEPTH; ++j ) {
            protocol_stack_length_counter[j] += pace2_example_wt[i].protocol_stack_length_counter[j];
            protocol_stack_length_counter_bytes[j] += pace2_example_wt[i].protocol_stack_length_counter_bytes[j];
        }
        for ( j = 0; j < PACE2_APPLICATIONS_COUNT; ++j ) {
            application_counter[j] += pace2_example_wt[i].application_counter[j];
            application_counter_bytes[j] += pace2_example_wt[i].application_counter_bytes[j];
        }
        for ( j = 0; j < PACE2_APPLICATION_ATTRIBUTES_COUNT; ++j ) {
            attribute_counter[j] += pace2_example_wt[i].attribute_counter[j];
            attribute_counter_bytes[j] += pace2_example_wt[i].attribute_counter_bytes[j];
        }
    }

    /* Output detection results */
    pace_print_results();

    /* Destroy PACE 2 module and free memory */
    pace2_exit_module( pace2 );

    pthread_exit( 0 );
} /* pace_cleanup_and_exit */

int main( int argc, char **argv )
{
    const char * license_file = NULL;

    /* Arg check */
    if ( argc < 2 ) {
        panic( "PCAP file not given, please give the pcap file as parameter\n" );
    } else if ( argc > 2 ) {
        license_file = argv[2];
    }

    /* Initialize PACE 2 */
    pace_configure_and_initialize( license_file );

    /* Read the pcap file and pass packets to stage1_and_2 */
    if ( read_pcap_loop( argv[1], config.general.clock_ticks_per_second, &packet_distribution ) != 0 ) {
        panic( "could not open pcap interface / file\n" );
    }

    pace_cleanup_and_exit();

    return 0;
} /* main */
