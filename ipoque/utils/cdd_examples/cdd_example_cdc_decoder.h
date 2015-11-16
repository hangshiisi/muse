/********************************************************************************/
/**
 ** \file       cdd_example_cdc_decoder.h
 ** \brief      PACE 2 Custom Defined Decoder CDC example.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/
#ifndef CDD_EXAMPLE_CDC_DECODER_H
#define CDD_EXAMPLE_CDC_DECODER_H

/* Includes *********************************************************************/
#include "cdd_example_generic.h"

/* Public Types *****************************************************************/
struct cdd_amazon_event_data {
    struct ipd_charset_string request_path;
};

/* Public Prototypes ************************************************************/
PACE2_cdc_return_state cdc_classify_amazon(PACE2_module * const pace2_module,
                                           PACE2_packet_descriptor *packet_descriptor,
                                           int thread_ID,
                                           void *userptr, void *flow_area,
                                           void *src_area, void *dst_area)
{
    PACE2_classification_result_event const * const res = pace2_cdc_get_classification(pace2_module, thread_ID);

    if (res != NULL) {
        /* This CDC process HTTP traffic only */
        if (res->protocol.excluded_mask->protocols.http == 1) {
            return PACE2_CDC_EXCLUDE;
        }

        if (res->protocol.stack.length > PACE2_RESULT_PROTOCOL_LAYER_7 &&
            res->protocol.stack.entry[PACE2_RESULT_PROTOCOL_LAYER_7] == PACE2_PROTOCOL_HTTP) {
            PACE2_basic_HTTP_request_event * basic_http = NULL;

            if (pace2_cpi_get_http_request_data(pace2_module, thread_ID, &basic_http) == PACE2_CPI_SUCCESS &&
                basic_http != NULL &&
                PACE2_MASK_INCLUDES_FLAG(basic_http->meta_data_mask, PACE2_HTTP_HOST) &&
                memmem(basic_http->line[PACE2_HTTP_HOST].content.ptr,
                       basic_http->line[PACE2_HTTP_HOST].content.len,
                       "amazon.de",
                       strlen("amazon.de")) != NULL) {
                if (packet_descriptor->flow_user_data != NULL) {
                    ((union cdd_flow_user_data *)packet_descriptor->flow_user_data)->cdc_matched = 1;
                }
                return PACE2_CDC_MATCH;
            }
        }
    }
    return PACE2_CDC_EXCLUDE;
}

PACE2_return_state cdd_decode_amazon(PACE2_module * const pace2_module,
                                     int const thread_ID,
                                     PACE2_event const * event,
                                     struct PACE2_cdd_callback_data * const callback_data)
{
    if (pace2_module == NULL ||
        event == NULL ||
        callback_data == NULL) {
        return PACE2_FAILURE;
    }

    if (callback_data->descriptor.packet == NULL ||
        callback_data->descriptor.packet->flow_user_data == NULL ||
        callback_data->descriptor_set != PACE2_CDD_DESCRIPTOR_SET_PACKET) {
        return PACE2_SUCCESS;
    }

    if (((union cdd_flow_user_data *)callback_data->descriptor.packet->flow_user_data)->cdc_matched == 1 &&
        event->header.type == PACE2_ADVANCED_HTTP_EVENT &&
        event->http_advanced_meta_data.meta_data_type == PACE2_ADVANCED_HTTP_REQUEST_PATH) {
        struct cdd_amazon_event_data * cdd_amazon_data = NULL;
        PACE2_event * cdd_event = NULL;

        /* allocate event slot for the CDD */
        PACE2_return_state retval = pace2_cdd_allocate_event(pace2_module, thread_ID, CDD_AMAZON_EVENT_ID, &cdd_event);
        if (retval != PACE2_SUCCESS) {
            return retval;
        }

        cdd_amazon_data = (struct cdd_amazon_event_data *) cdd_event->cdd_meta_data.cdd_data;
        cdd_amazon_data->request_path = event->http_advanced_meta_data.event_data.request_path;

        /* throw CDD event */
        pace2_cdd_throw_event(pace2_module, thread_ID, cdd_event);
    }
    return PACE2_SUCCESS;
}

void cdd_print_amazon_event (PACE2_cdd_event const * const cdd_event)
{
    struct cdd_amazon_event_data * cdd_amazon_data = NULL;

    if (cdd_event == NULL) {
        return;
    }
    cdd_amazon_data = (struct cdd_amazon_event_data *) cdd_event->cdd_data;
    printf("CDD Event: ID = %5u; Event ID = %5u; Amazon Request Path: %.*s\n",
           cdd_event->cdd_id, cdd_event->cdd_event_id,
           (int) cdd_amazon_data->request_path.content.length,
           cdd_amazon_data->request_path.content.buffer);
}

#endif                  /* CDD_EXAMPLE_CDC_DECODER_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
