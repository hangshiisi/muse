/********************************************************************************/
/**
 ** \file       pace2_integration_example_napatech.c
 ** \brief      PACE 2 integration example with napatech support.
 ** \date       Mar 17, 2015
 ** \version    1.0
 ** \copyright  ipoque GmbH
 **
 ** This is a simple program to show the integration of the PACE 2 library.
 ** with napatech NICs.
 **/
/********************************************************************************/

#include <nt.h>
#include <pace2.h>
#include "read_pcap.h"
#include "event_handler.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

struct global_options {
    uint64_t print_stats_after_x_packets;
    uint32_t port;
    bool full_features;
} options = { .print_stats_after_x_packets = 10, .port = 0xFFFFFFFF };

struct napatech_vars {
    NtNetStreamRx_t h_net_rx;           // Handle to the RX stream
    NtConfigStream_t h_cfg_stream;      // Handle to a config stream
    NtNtplInfo_t ntpl_info;             // Return data structure from the NT_NTPL() call.
    u64 timestamp_divisor;              /* Depending on the configured timestamp type of the adapter, a divisor is
                                           necessary to convert the read timestamp into the default timestamp in ms. */
} napa_vars;

struct napatech_statistics {
    uint64_t numPackets;              // The number of packets received
    int numBytes;                       // The number of bytes received
} napa_stats;

/* PACE 2 module pointer */
static PACE2_module *pace2;

/* PACE 2 configuration structure */
static struct PACE2_global_config pace2_config;

struct pace_statistics {
   uint64_t packet_counter;
   uint64_t byte_counter;
   uint64_t protocol_counter[PACE2_PROTOCOL_COUNT];
   uint64_t protocol_counter_bytes[PACE2_PROTOCOL_COUNT];
   uint64_t protocol_stack_length_counter[PACE2_PROTOCOL_STACK_MAX_DEPTH];
   uint64_t protocol_stack_length_counter_bytes[PACE2_PROTOCOL_STACK_MAX_DEPTH];
   uint64_t application_counter[PACE2_APPLICATIONS_COUNT];
   uint64_t application_counter_bytes[PACE2_APPLICATIONS_COUNT];
   uint64_t attribute_counter[PACE2_APPLICATION_ATTRIBUTES_COUNT];
   uint64_t attribute_counter_bytes[PACE2_APPLICATION_ATTRIBUTES_COUNT];
   uint64_t http_response_payload_bytes;

   uint64_t next_packet_id;

   uint64_t license_exceeded_packets;
} pace_stats;

/* Protocol, application and attribute name strings */
static const char *prot_long_str[] = { PACE2_PROTOCOLS_LONG_STRS };
static const char *app_str[] = { PACE2_APPLICATIONS_SHORT_STRS };

int napatech_setup(void)
{
    NtInfoStream_t info_stream_h;
    NtInfo_t info_stream;
    char tmp_buffer[50];
    char error_buffer[NT_ERRBUF_SIZE];
    int status;

    // Initialize the NTAPI library and thereby check if NTAPI_VERSION can be used together with this library
    if ((status = NT_Init(NTAPI_VERSION)) != NT_SUCCESS) {
        // Get the status code as text
        NT_ExplainError(status, error_buffer, sizeof(error_buffer));
        fprintf(stderr, "NT_Init() failed: %s\n", error_buffer);
        return -1;
    }

    /* Open a info stream. */
    if((status = NT_InfoOpen(&info_stream_h, "SystemInfo")) != NT_SUCCESS) {
        NT_ExplainError(status, error_buffer, sizeof(error_buffer));
        fprintf(stderr, "NT_InfoOpen() failed: %s\n", error_buffer);
        return -1;
    }

    /* An existing adapter with ID 0 is assumed. */
    info_stream.u.adapter.adapterNo = 0;
    info_stream.cmd = NT_INFO_CMD_READ_ADAPTER_V4;
    if((status = NT_InfoRead(info_stream_h, &info_stream)) != NT_SUCCESS) {
        NT_ExplainError(status, error_buffer, sizeof(error_buffer));
        fprintf(stderr, "NT_InfoRead() failed: %s\n", error_buffer);
        return -1;
    }

    /* Depending on the configured timestamp type, a timestamp divisor is necessary*/
    switch (info_stream.u.adapter_v4.data.timestampType) {
        case NT_TIMESTAMP_TYPE_NATIVE:
        case NT_TIMESTAMP_TYPE_NATIVE_NDIS:
        case NT_TIMESTAMP_TYPE_NATIVE_UNIX:
            napa_vars.timestamp_divisor = 1e5;
            break;
        case NT_TIMESTAMP_TYPE_PCAP:
            napa_vars.timestamp_divisor = 1e3;
            break;
        case NT_TIMESTAMP_TYPE_PCAP_NANOTIME:
            napa_vars.timestamp_divisor = 1e6;
            break;
        default:
            napa_vars.timestamp_divisor = 1;
            fprintf(stderr, "Adapter timestamp type not supported: %u\n", info_stream.u.adapter_v4.data.timestampType);
    }

    /* Close the info stream after usage. */
    if((status = NT_InfoClose(info_stream_h)) != NT_SUCCESS) {
        NT_ExplainError(status, error_buffer, sizeof(error_buffer));
        fprintf(stderr, "NT_InfoClose() failed: %s\n", error_buffer);
        return -1;
    }

    // Open a config stream to assign a filter to a stream ID.
    if ((status = NT_ConfigOpen(&napa_vars.h_cfg_stream, "TestStream")) != NT_SUCCESS) {
        // Get the status code as text
        NT_ExplainError(status, error_buffer, sizeof(error_buffer));
        fprintf(stderr, "NT_ConfigOpen() failed: %s\n", error_buffer);
        return -1;
    }

    // Assign traffic to stream ID 1
    if (options.port != 0xFFFFFFFF) {
        snprintf(tmp_buffer, 50, "Assign[streamid=1] = port == %u", options.port);
    } else {
        snprintf(tmp_buffer, 50, "Assign[streamid=1] All");
    }

    if ((status = NT_NTPL(napa_vars.h_cfg_stream, tmp_buffer, &napa_vars.ntpl_info, NT_NTPL_PARSER_VALIDATE_NORMAL)) != NT_SUCCESS) {
        // Get the status code as text
        NT_ExplainError(status, error_buffer, sizeof(error_buffer));
        fprintf(stderr, "NT_NTPL() failed: %s\n"
                ">>> NTPL errorcode: %X\n>>> %s\n>>> %s\n>>> %s\n",
                error_buffer, napa_vars.ntpl_info.u.errorData.errCode,
                napa_vars.ntpl_info.u.errorData.errBuffer[0], napa_vars.ntpl_info.u.errorData.errBuffer[1],
                napa_vars.ntpl_info.u.errorData.errBuffer[2]);
        return -1;
    }

    // Get a stream handle with stream ID 1.
    if ((status = NT_NetRxOpen(&napa_vars.h_net_rx, "TestStream", NT_NET_INTERFACE_PACKET, 1, -1)) != NT_SUCCESS) {
        // Get the status code as text
        NT_ExplainError(status, error_buffer, sizeof(error_buffer));
        fprintf(stderr, "NT_NetRxOpen() failed: %s\n", error_buffer);
        return -1;
    }

    return 0;
}

/* Memory allocation wrappers */
static void *malloc_wrapper( u64 size, int thread_ID, void *user_ptr, int scope ) {
    return malloc( size );
} /* malloc_wrapper */

static void free_wrapper( void *ptr, int thread_ID, void *user_ptr, int scope ) {
    free( ptr );
} /* free_wrapper */

static void *realloc_wrapper( void *ptr, u64 size, int thread_ID, void *user_ptr, int scope ) {
    return realloc( ptr, size );
}

/* Configure and initialize PACE 2 module */
static void pace_configure_and_initialize( const char * const license_file )
{
    /* Initialize configuration with default values */
    pace2_init_default_config(&pace2_config);
    pace2_set_license_config(&pace2_config, license_file);

    /* Set necessary memory wrapper functions */
    pace2_config.general.pace2_alloc = malloc_wrapper;
    pace2_config.general.pace2_free = free_wrapper;
    pace2_config.general.pace2_realloc = realloc_wrapper;

    /* set size of hash table for flow and subscriber tracking */
    // pace2_config.tracking.flow.generic.max_size.memory_size = 400 * 1024 * 1024;
    // pace2_config.tracking.subscriber.generic.max_size.memory_size = 400 * 1024 * 1024;

    if (options.full_features) {
        printf("Enabling full classification and decoding feature set.\n\n");

        /* Stage 1: enable IP defragmentation */
        pace2_config.s1_preparing.defrag.enabled = 1;
        pace2_config.s1_preparing.max_framing_depth = 10;
        pace2_config.s1_preparing.max_decaps_level = 10;

        /* Stage 2: enable PARO and set necessary values */
        pace2_config.s2_reordering.enabled = 1;
        pace2_config.s2_reordering.packet_buffer_size = 16 * 1024 * 1024;
        pace2_config.s2_reordering.packet_timeout = 5 * pace2_config.general.clock_ticks_per_second;

        /* Stage 3: enable specific classification components */
        pace2_config.s3_classification.asym_detection_enabled = 1;
        pace2_config.s3_classification.sit.enabled = 1;
        pace2_config.s3_classification.sit.key_reduce_factor = 1;
        pace2_config.s3_classification.sit.memory = 1 * 1024 * 1024;
        pace2_config.s3_classification.cdn_caching_enabled = 1;
        pace2_config.s3_classification.os_enabled = 1;
        pace2_config.s3_classification.nat_enabled = 1;
        pace2_config.s3_classification.rtp_performance_enabled = 1;
        pace2_config.s3_classification.csi_enabled = 1;

        /* Stage 4: enable decoding */
        pace2_config.s4_decoding.enabled = 1;
    } else {
        printf("Using minimal feature set.\n\n");
    }

    /* uncomment the following line to only activate classification of protocol HTTP */
    // PACE2_PROTOCOLS_BITMASK_RESET(pace2_config.s3_classification.active_classifications.bitmask);
    // pace2_config.s3_classification.active_classifications.protocols.http = IPQ_TRUE;

    /* uncomment the following line to only activate decoding of protocol HTTP */
    // PACE2_PROTOCOLS_BITMASK_RESET(pace2_config.s4_decoding.active_advanced_decoders.bitmask);
    // pace2_config.s4_decoding.active_advanced_decoders.protocols.http = IPQ_TRUE;

    /* Initialize PACE 2 detection module */
    pace2 = pace2_init_module( &pace2_config );

    if ( pace2 == NULL ) {
        fprintf(stderr, "Initialization of PACE module failed\n" );
        exit(1);
    }

    /* Licensing */
    if ( license_file != NULL ) {

        const ipoque_pace_license_information_t *lic_info = NULL;

        switch( pace2_get_license_information( pace2, &lic_info, 0 ) ) {
            case PACE2_SUCCESS:
                fprintf(stderr, "License init error code: %u\n"
                        "License init error reason: %s\nLicense load error code: %u\n"
                        "License load error reason: %s\nLicense validation error code: %u\n"
                        "License validation error reason: %s\nLicense limitation error code: %u\n"
                        "License limitation error reason: %s\nNumber of mac addresses found: %u\n",
                        lic_info->init_error_code, lic_info->init_error_reason,
                        lic_info->load_error_code, lic_info->load_error_reason,
                        lic_info->validation_error_code, lic_info->validation_error_reason,
                        lic_info->limitation_error_code, lic_info->limitation_error_reason,
                        lic_info->no_of_mac_addresses_found);
                break;

            case PACE2_PARAM_MISSING:
                fprintf( stderr, "Parameter missing\n" );
                break;

            case PACE2_FAILURE:
                fprintf( stderr, "Licensing feature is not available.\n\n" );
                break;
            default:
                break;
        }
    }
} /* pace_configure_and_initialize */

/* Print out all PACE 2 events currently in the event queue */
static void process_events(void)
{
    PACE2_event *event;

    while ( ( event = pace2_get_next_event( pace2, 0 ) ) ) {
        /* some additional processing is necessary */
        if ( event->header.type == PACE2_CLASS_HTTP_EVENT ) {
            const PACE2_class_HTTP_event * const http_event = &event->http_class_meta_data;
            if (http_event->meta_data_type == PACE2_CLASS_HTTP_RESPONSE_DATA_TRANSFER) {
                const struct ipd_class_http_transfer_payload_struct * const http_payload = &http_event->event_data.response_data_transfer;
                pace_stats.http_response_payload_bytes += http_payload->data.content.length;
            }
        }
        pace2_debug_advanced_event(stdout, event);
    }
} /* process_events */

static void stage3_to_5( void )
{
    const PACE2_event *event;
    PACE2_bitmask pace2_event_mask;
    PACE2_packet_descriptor *out_pd;

    /* Process stage 3 and 4 as long as packets are available from stage 2 */
    while ( (out_pd = pace2_s2_get_next_packet(pace2, 0)) ) {

        /* Account every processed packet */
        pace_stats.packet_counter++;
        pace_stats.byte_counter += out_pd->framing->stack[0].frame_length;

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

                pace_stats.protocol_counter[classification->protocol.stack.entry[classification->protocol.stack.length-1]]++;
                pace_stats.protocol_counter_bytes[classification->protocol.stack.entry[classification->protocol.stack.length-1]] += out_pd->framing->stack[0].frame_length;
                pace_stats.protocol_stack_length_counter[classification->protocol.stack.length - 1]++;
                pace_stats.protocol_stack_length_counter_bytes[classification->protocol.stack.length - 1] += out_pd->framing->stack[0].frame_length;

                pace_stats.application_counter[classification->application.type]++;
                pace_stats.application_counter_bytes[classification->application.type] += out_pd->framing->stack[0].frame_length;

                for ( attribute_iterator = 0; attribute_iterator < classification->application.attributes.length; attribute_iterator++) {
                    pace_stats.attribute_counter[classification->application.attributes.list[attribute_iterator]]++;
                    pace_stats.attribute_counter_bytes[classification->application.attributes.list[attribute_iterator]] += out_pd->framing->stack[0].frame_length;
                }
            } else if ( event->header.type == PACE2_LICENSE_EXCEEDED_EVENT ) {
                pace_stats.license_exceeded_packets++;
            }
        } /* Stage 3 event processing */

        /* Process stage 4: protocol decoding */
        if (pace2_config.s4_decoding.enabled) {
            if (pace2_s4_process_packet( pace2, 0, out_pd, NULL, &pace2_event_mask ) != PACE2_S4_SUCCESS) {
                continue;
            }

            /* Print out decoder events */
            process_events();
        }

    } /* Stage 2 packets */

    /* Process stage 5: timeout handling */
    if ( pace2_s5_handle_timeout( pace2, 0, &pace2_event_mask ) != 0 ) {
        return;
    }

    /* Print out decoder events generated while cleaning up flows that timed out */
    if (pace2_config.s4_decoding.enabled) {
        process_events();
    }

} /* stage3_to_5 */

static void stage1_and_2( const uint64_t timestamp, const struct iphdr *iph, uint16_t ipsize )
{
    PACE2_packet_descriptor pd;

    /* Stage 1: Prepare packet descriptor and run ip defragmentation */
    if (pace2_s1_process_packet( pace2, 0, timestamp, iph, ipsize, PACE2_S1_L3, &pd, NULL, 0 ) != PACE2_S1_SUCCESS) {
        return;
    }

    /* Set unique packet id. The flow_id is set by the internal flow tracking */
    pd.packet_id = ++pace_stats.next_packet_id;

    /* Stage 2: Packet reordering */
    if ( pace2_s2_process_packet( pace2, 0, &pd ) != PACE2_S2_SUCCESS ) {
        return;
    }

    stage3_to_5();
} /* stage1_and_2 */

/* Print classification results */
static void pace_print_results( void )
{
    u32 c;

    printf("\n\n  %-20s %-15s %s\n\n", "Protocol", "Packets", "Bytes" );
    for ( c = 0; c < PACE2_PROTOCOL_COUNT; c++ ) {
        if ( pace_stats.protocol_counter_bytes[c] != 0 ) {
            printf("  %-20s %-15lu %lu\n",
                     prot_long_str[c], pace_stats.protocol_counter[c], pace_stats.protocol_counter_bytes[c] );
        }
    }

    printf("\n\n  %-20s %-15s %s\n\n", "Stack length", "Packets", "Bytes" );
    for ( c = 0; c < PACE2_PROTOCOL_STACK_MAX_DEPTH; c++ ) {
        printf("  %-20u %-15lu %lu\n",
                 c, pace_stats.protocol_stack_length_counter[c], pace_stats.protocol_stack_length_counter_bytes[c] );
    }

    printf("\n\n  %-20s %-15s %s\n\n", "Application", "Packets", "Bytes" );
    for ( c = 0; c < PACE2_APPLICATIONS_COUNT; c++ ) {
        if ( pace_stats.application_counter_bytes[c] != 0 ) {
            printf("  %-20s %-15lu %lu\n",
                     app_str[c], pace_stats.application_counter[c], pace_stats.application_counter_bytes[c] );
        }
    }

    printf("\n\n  %-20s %-15s %s\n\n", "Attribute", "Packets", "Bytes" );
    for ( c = 0; c < PACE2_APPLICATION_ATTRIBUTES_COUNT; c++ ) {
        if ( pace_stats.attribute_counter[c] != 0 ) {
            printf("  %-20s %-15lu %lu\n",
                     pace2_get_application_attribute_str(c), pace_stats.attribute_counter[c], pace_stats.attribute_counter_bytes[c] );
        }
    }

    printf("\nHTTP response payload bytes: %lu\n\n", pace_stats.http_response_payload_bytes );
    printf("\nPacket counter: %lu\n\n", pace_stats.packet_counter );

    if ( pace_stats.license_exceeded_packets > 0 ) {
        printf("License exceeded packets: %lu.\n\n", pace_stats.license_exceeded_packets );
    }
} /* pace_print_results */

int packet_loop(void (*packet_processing)(const uint64_t timestamp, const struct iphdr *iph, uint16_t ipsize))
{
    char error_buffer[NT_ERRBUF_SIZE];
    NtNetBuf_t h_net_buf;       // Net buffer container.  Packet data is returned in this when calling NT_NetRxGet().

    // pass each packet to PACE
    while (1) {
        int ret = NT_NetRxGetNextPacket(napa_vars.h_net_rx, &h_net_buf, 0);

        if (ret != NT_SUCCESS) {
            if( (ret != NT_STATUS_TIMEOUT)  && (ret != NT_STATUS_TRYAGAIN) ) {
                NT_ExplainError(ret, error_buffer, sizeof(error_buffer)-1);
                fprintf(stderr, "NT_NetRxGetNextPacket() failed: %s\n", error_buffer);
                return -1;
            }
            continue;
        }

        struct _mac {
            uint8_t dst[6];
            uint8_t src[6];
            uint16_t typelen;
        } *mac = (struct _mac*) NT_NET_GET_PKT_L2_PTR(h_net_buf);

        printf("%6s %016llX - %04d - %02X:%02X:%02X:%02X:%02X:%02X  %02X:%02X:%02X:%02X:%02X:%02X  %04x\n",
                  (NT_NET_GET_PKT_DESCRIPTOR_TYPE(h_net_buf) == NT_PACKET_DESCRIPTOR_TYPE_PCAP ? "PCAP" :
                        NT_NET_GET_PKT_DESCRIPTOR_TYPE(h_net_buf) == NT_PACKET_DESCRIPTOR_TYPE_NT ? "NT" :
                                NT_NET_GET_PKT_DESCRIPTOR_TYPE(h_net_buf) == NT_PACKET_DESCRIPTOR_TYPE_NT_EXTENDED ? "NT_EXT" : "Unknown"),
                (unsigned long long)NT_NET_GET_PKT_TIMESTAMP(h_net_buf),
                NT_NET_GET_PKT_WIRE_LENGTH(h_net_buf),
                mac->dst[0], mac->dst[1], mac->dst[2], mac->dst[3], mac->dst[4], mac->dst[5],
                mac->src[0], mac->src[1], mac->src[2], mac->src[3], mac->src[4], mac->src[5],
                mac->typelen);

        napa_stats.numPackets++;
        uint32_t len = NT_NET_GET_PKT_WIRE_LENGTH(h_net_buf);
        napa_stats.numBytes += len;

        uint64_t timestamp = NT_NET_GET_PKT_TIMESTAMP(h_net_buf) ;
        timestamp /= napa_vars.timestamp_divisor;

        // hand-over packet to PACE:
        (*packet_processing)(timestamp, (struct iphdr *) &mac[1], len - 4 - sizeof(*mac)); // -4 = CRC length

        if (napa_stats.numPackets > 1 && (napa_stats.numPackets % options.print_stats_after_x_packets) == 0) {
            pace_print_results();
        }
    }

    return 0;
}

int napatech_finish(void)
{
    char tmpBuffer[20];             			// Buffer to build filter string
    char errorBuffer[NT_ERRBUF_SIZE];
    int status;

    // Delete the filter
    snprintf(tmpBuffer, 20, "delete=%d", napa_vars.ntpl_info.ntplId);
    if ((status = NT_NTPL(napa_vars.h_cfg_stream, tmpBuffer, &napa_vars.ntpl_info, NT_NTPL_PARSER_VALIDATE_NORMAL)) != NT_SUCCESS) {
        // Get the status code as text
        NT_ExplainError(status, errorBuffer, sizeof(errorBuffer));
        fprintf(stderr, "NT_NTPL() failed: %s\n"
                ">>> NTPL errorcode: %X\n>>> %s\n>>> %s\n>>> %s\n",
                errorBuffer, napa_vars.ntpl_info.u.errorData.errCode,
                napa_vars.ntpl_info.u.errorData.errBuffer[0], napa_vars.ntpl_info.u.errorData.errBuffer[1],
                napa_vars.ntpl_info.u.errorData.errBuffer[2]);
        return -1;
    }

    // Close the config stream
    if ((status = NT_ConfigClose(napa_vars.h_cfg_stream)) != NT_SUCCESS) {
        // Get the status code as text
        NT_ExplainError(status, errorBuffer, sizeof(errorBuffer));
        fprintf(stderr, "NT_ConfigClose() failed: %s\n", errorBuffer);
        return -1;
    }

    // Close the stream and release the hostbuffer. This will also remove the NTPL assignments performed.
    NT_NetRxClose(napa_vars.h_net_rx);
    printf("Done: %lu packets, %d bytes\n", napa_stats.numPackets, napa_stats.numBytes);

    // Close down the NTAPI library
    NT_Done();

    return 0;
}

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

    int c = 0;
    while ((c = getopt(argc, argv, "ahp:l:o:")) != -1) {
        switch (c) {
            case 'h':
                printf("Usage: pace2_integration_example_napatech [options]\n\n"
                        "  -a\tEnable full PACE feature set.\n"
                        "  -p\tWhat port should be captured on.\n"
                        "  -l\tUse a specific license file for PACE.\n"
                        "  -n\tNumber of packets, that should be captured before PACE statistic is printed.\n"
                        "  -h\tPrint this help message\n\n");
                return 0;
            case 'a':
                options.full_features = 1;
                break;
            case 'p':
                options.port = strtoul(optarg, NULL, 10);
                break;
            case 'n':
                options.print_stats_after_x_packets = strtoul(optarg, NULL, 10);
                break;
            case 'l':
                license_file = optarg;
                break;
        }
    }

    /* Initialize NTCAP suite */
    if (napatech_setup() != 0) {
        fprintf(stderr, "Initializing of NTAPI failed!\n" );
        return 1;
    }

    /* Initialize PACE 2 */
    pace_configure_and_initialize( license_file );

    /* Read from  file and pass packets to stage1_and_2 */
    if ( packet_loop( &stage1_and_2 ) != 0 ) {
        fprintf(stderr, "Error in packet loop!\n" );
        return 1;
    }

    pace_cleanup_and_exit();

    napatech_finish();

    return 0;
}
