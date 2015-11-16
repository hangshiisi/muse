/********************************************************************************/
/**
 ** \file       pace2_integration_example_cdD.c
 ** \brief      PACE 2 integration example with internal tracking to show CDD capabilities.
 ** \date       Jun 17, 2015
 ** \version    1.0
 ** \copyright  ipoque GmbH
 **
 ** This is a simple program to show the integration of the PACE 2 library.
 ** The program uses the internal tracking feature of the library.
 ** Additionally it shows how to integrate custom defined decoders.
 **/
/********************************************************************************/

/* Includes *********************************************************************/
#ifdef __linux__
#include <netinet/tcp.h>
#endif

#ifdef WIN32
#include <WinSock2.h>
#include <inttypes.h>
#endif

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <pace2.h>
#include "read_pcap.h"
#include "event_handler.h"
#include "cdd_examples/cdd_example_doctype_http.h"
#include "cdd_examples/cdd_example_cdc_decoder.h"
#include "cdd_examples/cdd_example_class.h"

/* Private Variables ************************************************************/

/* PACE 2 module pointer */
static PACE2_module *pace2 = NULL;

/* PACE 2 configuration structure */
static struct PACE2_global_config config;

/* CDD specific configuration structures */
static struct PACE2_config_s4_cdd cdd_config[NUMBER_OF_CDD];
static uint32_t cdd_event_sizes[NUMBER_OF_CDD][NUMBER_OF_CDD_EVENTS];

/* CDC specific configuration structures */
static struct PACE2_config_s3_cdc cdc_config[NUMBER_OF_CDC];

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
static u64 http_response_payload_bytes = 0;

static u64 next_packet_id = 0;

static u64 license_exceeded_packets = 0;

/* Protocol, application and attribute name strings */
static char const * prot_str[] = {PACE2_PROTOCOLS_LONG_STRS};
static char const * app_str[] = {PACE2_APPLICATIONS_LONG_STRS};

/* Private Definitions **********************************************************/

/* Memory allocation wrappers */
static void *malloc_wrapper(u64 size,
                             int thread_ID,
                             void *user_ptr,
                             int scope)
{
    return malloc(size);
} /* malloc_wrapper */

static void free_wrapper(void *ptr,
                          int thread_ID,
                          void *user_ptr,
                          int scope)
{
    free(ptr);
} /* free_wrapper */

static void *realloc_wrapper(void *ptr,
                              u64 size,
                              int thread_ID,
                              void *user_ptr,
                              int scope)
{
    return realloc(ptr, size);
}


/* panic is used for abnormal errors (allocation errors, file not found,...) */
static void panic(const char *msg)
{
    printf("%s", msg);
    exit(1);
} /* panic */

/* Print classification results to stderr */
static void pace_print_results(void)
{
    u32 c;
    fprintf(stderr, "  %-20s %-15s %s\n\n", "Protocol", "Packets", "Bytes");
    for (c = 0; c < PACE2_PROTOCOL_COUNT; c++) {
        if (protocol_counter_bytes[c] != 0) {
            fprintf(stderr, "  %-20s %-15llu %llu\n",
                     prot_str[c], protocol_counter[c], protocol_counter_bytes[c]);
        }
    }
    fprintf(stderr, "\n\n");
    fprintf(stderr, "  %-20s %-15s %s\n\n", "Stack length", "Packets", "Bytes");
    for (c = 0; c < PACE2_PROTOCOL_STACK_MAX_DEPTH; c++) {
        fprintf(stderr, "  %-20u %-15llu %llu\n",
                 c, protocol_stack_length_counter[c], protocol_stack_length_counter_bytes[c]);
    }
    fprintf(stderr, "\n\n");
    fprintf(stderr, "  %-20s %-15s %s\n\n", "Application", "Packets", "Bytes");
    for (c = 0; c < PACE2_APPLICATIONS_COUNT; c++) {
        if (application_counter_bytes[c] != 0) {
            fprintf(stderr, "  %-20s %-15llu %llu\n",
                     app_str[c], application_counter[c], application_counter_bytes[c]);
        }
    }
    fprintf(stderr, "\n\n");
    fprintf(stderr, "  %-20s %-15s %s\n\n", "Attribute", "Packets", "Bytes");
    for (c = 0; c < PACE2_APPLICATION_ATTRIBUTES_COUNT; c++) {
        if (attribute_counter[c] != 0) {
            fprintf(stderr, "  %-20s %-15llu %llu\n",
                     pace2_get_application_attribute_str(c), attribute_counter[c], attribute_counter_bytes[c]);
        }
    }
    fprintf(stderr, "\n\n");
    fprintf(stderr, "  %-20s %-15s %s\n\n", "Custom Class", "Packets", "Bytes");

    fprintf(stderr, "\n");
    fprintf(stderr, "HTTP response payload bytes: %llu\n", http_response_payload_bytes);
    fprintf(stderr, "\n");

    fprintf(stderr, "\n");
    fprintf(stderr, "Packet counter: %llu\n", packet_counter);
    fprintf(stderr, "\n");

    if (license_exceeded_packets > 0) {
        fprintf(stderr, "License exceeded packets: %llu.\n\n", license_exceeded_packets);
    }

} /* pace_print_results */

/* Configure and initialize PACE 2 module */
static void pace_configure_and_initialize(char const * const license_file)
{
    /* Initialize configuration with default values */
    pace2_init_default_config(&config);
    pace2_set_license_config(&config, license_file);

    /* Set necessary memory wrapper functions */
    config.general.pace2_alloc = malloc_wrapper;
    config.general.pace2_free = free_wrapper;
    config.general.pace2_realloc = realloc_wrapper;

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

    /* initialize custom defined classification */
    cdc_config[CDC_AMAZON_ID].callback = cdc_classify_amazon;
    cdc_config[CDC_AMAZON_ID].callback_userptr = NULL;
    cdc_config[CDC_AMAZON_ID].flow_area_size = 0;
    cdc_config[CDC_AMAZON_ID].subscriber_area_size = 0;

    config.s3_classification.cdc_number = 1;
    config.s3_classification.cdc_conf_array = cdc_config;
    config.tracking.flow.generic.user_data_size = sizeof(union cdd_flow_user_data);

    memset(cdd_config, 0, sizeof(struct PACE2_config_s4_cdd) * NUMBER_OF_CDD);
    memset(cdd_event_sizes, 0, sizeof(uint32_t) * NUMBER_OF_CDD * NUMBER_OF_CDD_EVENTS);

    /* initialize custom defined decoder of the doctype decoder */
    cdd_event_sizes[CDD_DOCTYPE_ID][0] = sizeof(struct cdd_doctype_event_data);
    cdd_config[CDD_DOCTYPE_ID].callback = cdd_decode_doctype;
    cdd_config[CDD_DOCTYPE_ID].callback_userptr = NULL;
    cdd_config[CDD_DOCTYPE_ID].number_of_events = NUMBER_OF_CDD_EVENTS;
    cdd_config[CDD_DOCTYPE_ID].event_size = cdd_event_sizes[CDD_DOCTYPE_ID];

    /* initialize custom defined decoder of the HTTP payload counter */
    cdd_event_sizes[CDD_HTTP_ID][0] = sizeof(struct cdd_http_event_data);
    cdd_config[CDD_HTTP_ID].callback = cdd_count_http_payload;
    cdd_config[CDD_HTTP_ID].callback_userptr = (void *) &global_http_payload_event_counter;
    cdd_config[CDD_HTTP_ID].number_of_events = NUMBER_OF_CDD_EVENTS;
    cdd_config[CDD_HTTP_ID].event_size = cdd_event_sizes[CDD_HTTP_ID];

    /* initialize custom defined decoder for amazon */
    cdd_event_sizes[CDD_AMAZON_ID][0] = sizeof(struct cdd_amazon_event_data);
    cdd_config[CDD_AMAZON_ID].callback = cdd_decode_amazon;
    cdd_config[CDD_AMAZON_ID].callback_userptr = NULL;
    cdd_config[CDD_AMAZON_ID].number_of_events = NUMBER_OF_CDD_EVENTS;
    cdd_config[CDD_AMAZON_ID].event_size = cdd_event_sizes[CDD_AMAZON_ID];

    /* initialize custom defined decoder for used password decoder */
    cdd_event_sizes[CDD_USERPASS_ID][0] = sizeof(struct cdd_userpass_event_data);
    cdd_config[CDD_USERPASS_ID].callback = cdd_decode_userpass;
    cdd_config[CDD_USERPASS_ID].callback_userptr = NULL;
    cdd_config[CDD_USERPASS_ID].number_of_events = NUMBER_OF_CDD_EVENTS;
    cdd_config[CDD_USERPASS_ID].event_size = cdd_event_sizes[CDD_USERPASS_ID];

    /* Stage 4: enable decoding */
    config.s4_decoding.enabled = 1;
    config.s4_decoding.cdd_number = NUMBER_OF_CDD;
    config.s4_decoding.cdd_conf_array = cdd_config;
    PACE2_PROTOCOLS_BITMASK_RESET(config.s4_decoding.active_advanced_decoders.bitmask);
    config.s4_decoding.active_advanced_decoders.protocols.http = IPQ_TRUE;
    config.s4_decoding.active_advanced_decoders.protocols.imap = IPQ_TRUE;
    config.s4_decoding.active_advanced_decoders.protocols.smtp = IPQ_TRUE;
    config.s4_decoding.active_advanced_decoders.protocols.pop = IPQ_TRUE;

    /* Initialize PACE 2 detection module */
    pace2 = pace2_init_module(&config);

    if (pace2 == NULL) {
        panic("Initialization of PACE module failed\n");
    }

    /* Licensing */
    if (license_file != NULL) {

        PACE2_class_return_state retval;
        PACE2_classification_status_event lic_event;

        memset(&lic_event, 0, sizeof(PACE2_classification_status_event));
        retval = pace2_class_get_license(pace2, 0, &lic_event);
        if (retval == PACE2_CLASS_SUCCESS) {
            pace2_debug_event(stdout, (PACE2_event const * const) &lic_event);
        }
    }
} /* pace_configure_and_initialize */

/* Print out all PACE 2 events currently in the event queue */
static void process_events(void)
{
    PACE2_event *event;

    while ((event = pace2_get_next_event(pace2, 0))) {
        /* some additional processing is necessary */
        if (event->header.type == PACE2_CLASS_HTTP_EVENT) {
            const PACE2_class_HTTP_event * const http_event = &event->http_class_meta_data;
            if (http_event->meta_data_type == PACE2_CLASS_HTTP_RESPONSE_DATA_TRANSFER) {
                const struct ipd_class_http_transfer_payload_struct * const http_payload = &http_event->event_data.response_data_transfer;
                http_response_payload_bytes += http_payload->data.content.length;
            }
        } else if (event->header.type == PACE2_CDD_EVENT) {
            /* It is recommend to use the cdd_event_id instead of cdd_id, because the cdd_id
             * value depends on the position of the CDD event inside the CDD configuration array.
             */
            if (event->cdd_meta_data.cdd_event_id == CDD_DOCTYPE_EVENT_ID) {
                cdd_print_doctype_event((PACE2_cdd_event const * const) event);
            } else if (event->cdd_meta_data.cdd_event_id == CDD_HTTP_EVENT_ID) {
                cdd_print_http_event((PACE2_cdd_event const * const) event);
            } else if (event->cdd_meta_data.cdd_event_id == CDD_AMAZON_EVENT_ID) {
                cdd_print_amazon_event((PACE2_cdd_event const * const) event);
            } else if (event->cdd_meta_data.cdd_event_id == CDD_USERPASS_EVENT_ID) {
                cdd_print_userpass_event((PACE2_cdd_event const * const) event);
            }
        } else if (event->header.type == PACE2_FLOW_DROPPED_EVENT) {
            cdd_cleanup_flow_user_data(&(event->flow_dropped));

        }
        pace2_debug_advanced_event(stdout, event);
    }
} /* process_events */

static void stage3_to_5(void)
{
    const PACE2_event *event;
    PACE2_bitmask pace2_event_mask;
    PACE2_packet_descriptor *out_pd;

    /* Process stage 3 and 4 as long as packets are available from stage 2 */
    while ((out_pd = pace2_s2_get_next_packet(pace2, 0))) {

        /* Account every processed packet */
        packet_counter++;
        byte_counter += out_pd->framing->stack[0].frame_length;

        /* Process stage 3: packet classification */
        if (pace2_s3_process_packet(pace2, 0, out_pd, &pace2_event_mask) != PACE2_S3_SUCCESS) {
            continue;
        } /* Stage 3 processing */

        /* Get all thrown events of stage 3 */
        while ((event = pace2_get_next_event(pace2, 0))) {

            /* some additional processing is necessary */
            if (event->header.type == PACE2_CLASSIFICATION_RESULT) {
                PACE2_classification_result_event const * const classification = &event->classification_result_data;
                u8 attribute_iterator;

                protocol_counter[classification->protocol.stack.entry[classification->protocol.stack.length-1]]++;
                protocol_counter_bytes[classification->protocol.stack.entry[classification->protocol.stack.length-1]] += out_pd->framing->stack[0].frame_length;
                protocol_stack_length_counter[classification->protocol.stack.length - 1]++;
                protocol_stack_length_counter_bytes[classification->protocol.stack.length - 1] += out_pd->framing->stack[0].frame_length;

                application_counter[classification->application.type]++;
                application_counter_bytes[classification->application.type] += out_pd->framing->stack[0].frame_length;

                for (attribute_iterator = 0; attribute_iterator < classification->application.attributes.length; attribute_iterator++) {
                    attribute_counter[classification->application.attributes.list[attribute_iterator]]++;
                    attribute_counter_bytes[classification->application.attributes.list[attribute_iterator]] += out_pd->framing->stack[0].frame_length;
                }
            } else if (event->header.type == PACE2_LICENSE_EXCEEDED_EVENT) {
                license_exceeded_packets++;
            }
        } /* Stage 3 event processing */

        /* Process stage 4: protocol decoding */
        if (pace2_s4_process_packet(pace2, 0, out_pd, NULL, &pace2_event_mask) != PACE2_S4_SUCCESS) {
            continue;
        }

        /* Print out decoder events */
        process_events();

    } /* Stage 2 packets */

    /* Process stage 5: timeout handling */
    if (pace2_s5_handle_timeout(pace2, 0, &pace2_event_mask) != 0) {
        return;
    }

    /* Print out decoder events generated while cleaning up flows that timed out */
    process_events();

} /* stage3_to_5 */

static void stage1_and_2(const uint64_t time, const struct iphdr *iph, uint16_t ipsize)
{
    PACE2_packet_descriptor pd;

    /* Stage 1: Prepare packet descriptor and run IP defragmentation */
    if (pace2_s1_process_packet(pace2, 0, time, iph, ipsize, PACE2_S1_L3, &pd, NULL, 0) != PACE2_S1_SUCCESS) {
        return;
    }

    /* Set unique packet id. The flow_id is set by the internal flow tracking */
    pd.packet_id = ++next_packet_id;

    /* Stage 2: Packet reordering */
    if (pace2_s2_process_packet(pace2, 0, &pd) != PACE2_S2_SUCCESS) {
        return;
    }

    stage3_to_5();
} /* stage1_and_2 */

static void pace2_cleanup_and_exit(void)
{
    /* Flush any remaining packets from the buffers */
    pace2_flush_engine(pace2, 0);

    /* Process packets which are ejected after flushing */
    stage3_to_5();

    /* Output detection results */
    pace_print_results();

    /* Destroy PACE 2 module and free memory */
    pace2_exit_module(pace2);
} /* pace_cleanup_and_exit */

int main(int argc, char **argv)
{
    char const * license_file = NULL;

    /* Arg check */
    if (argc < 2) {
        panic("PCAP file not given, please give the pcap file as parameter\n");
    } else if (argc > 2) {
        license_file = argv[2];
    }

    /* Initialize PACE 2 */
    pace_configure_and_initialize(license_file);

    /* Read the pcap file and pass packets to stage1_and_2 */
    if (read_pcap_loop(argv[1], config.general.clock_ticks_per_second, &stage1_and_2) != 0) {
        panic("could not open pcap interface / file\n");
    }

    pace2_cleanup_and_exit();

    return 0;
} /* main */
