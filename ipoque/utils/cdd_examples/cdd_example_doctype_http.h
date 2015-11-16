/********************************************************************************/
/**
 ** \file       cdd_example_doctype_http.h
 ** \brief      PACE 2 Custom Defined Decoder DOCTYPE example.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/
#ifndef CDD_EXAMPLE_DOCTYPE_HTTP_H
#define CDD_EXAMPLE_DOCTYPE_HTTP_H

/* Includes *********************************************************************/
#include "cdd_example_generic.h"

/* Public Macros ****************************************************************/

#define CDD_DOCTYPE_VALUES(D) \
    D(CDD_HTML_5,                   HTML 5) \
    D(CDD_HTML_4_01_STRICT,         HTML 4.01 Strict) \
    D(CDD_HTML_4_01_TRANSITIONAL,   HTML 4.01 Transitional) \
    D(CDD_HTML_4_01_FRAMESET,       HTML 4.01 Frameset) \
    D(CDD_XHTML_1_0_STRICT,         XHTML 1.0 Strict) \
    D(CDD_XHTML_1_0_TRANSITIONAL,   XHTML 1.0 Transitional) \
    D(CDD_XHTML_1_0_FRAMESET,       XHTML 1.0 Frameset) \
    D(CDD_XHTML_1_1,                XHTML 1.1) \
    D(CDD_HTML_INVALID,             HTML is invalid) \
    D(CDD_DOCTYPE_UNKOWN,           Doctype is unkown) \

/* Public Types *****************************************************************/
enum cdd_html_doctype {
    CDD_DOCTYPE_VALUES(GENERATE_ENUM)
};

struct cdd_doctype_event_data {
    enum cdd_html_doctype doctype;
};

struct cdd_http_event_data {
    uint32_t number_http_payload_events;
};

struct cdd_http_user_data {
    uint32_t event_counter;
};

/* Public Variables *************************************************************/
static struct cdd_http_user_data global_http_payload_event_counter;
static char const * const cdd_doctype_str[] = {CDD_DOCTYPE_VALUES(GENERATE_STRING)};

/* Public Prototypes ************************************************************/
static inline PACE2_return_state cdd_decode_doctype(PACE2_module * const pace2_module,
                                                    int const thread_ID,
                                                    PACE2_event const * event,
                                                    struct PACE2_cdd_callback_data * const callback_data)
{
    if (event->header.type == PACE2_ADVANCED_HTTP_EVENT &&
        event->http_advanced_meta_data.meta_data_type == PACE2_ADVANCED_HTTP_RESPONSE_PAYLOAD) {
        struct ipd_charset_string const * response_payload = NULL;
        struct cdd_doctype_event_data * cdd_doctype_data = NULL;
        PACE2_event * cdd_event = NULL;
        struct ipd_string html_doctype = {NULL, 0};
        char * line_end = NULL;
        char * tag_end = NULL;
        PACE2_return_state retval;

        /* use local variable to shorten usage of event data */
        response_payload = &event->http_advanced_meta_data.event_data.response_payload;
        html_doctype.buffer = memmem(response_payload->content.buffer,
                                     response_payload->content.length,
                                     "<!DOCTYPE ",
                                     strlen("<!DOCTYPE "));
        if (html_doctype.buffer == NULL) {
            return PACE2_SUCCESS;
        }

        html_doctype.length = response_payload->content.length - (html_doctype.buffer - response_payload->content.buffer);

        /* allocate event slot for the CDD */
        retval = pace2_cdd_allocate_event(pace2_module, thread_ID, CDD_DOCTYPE_EVENT_ID, &cdd_event);
        if (retval != PACE2_SUCCESS) {
            return retval;
        }

        cdd_doctype_data = (struct cdd_doctype_event_data *) cdd_event->cdd_meta_data.cdd_data;

        line_end = memchr(html_doctype.buffer, '\n', html_doctype.length);
        tag_end = memchr(html_doctype.buffer, '>', html_doctype.length);

        if (NULL == tag_end) {
            // end of DOCTYPE tag is not in this packet. Nothing to be done here.
            return PACE2_SUCCESS;
        }

        if (NULL == line_end) {
            line_end = html_doctype.buffer + html_doctype.length - 1;
        }

        /* Check if HTML is valid */
        if (tag_end > line_end) {
            cdd_doctype_data->doctype = CDD_HTML_INVALID;

            /* throw CDD event */
            pace2_cdd_throw_event(pace2_module, thread_ID, cdd_event);
            return PACE2_SUCCESS;
        }

        if (memmem(html_doctype.buffer, html_doctype.length, "DTD/xhtml11.dtd", strlen("DTD/xhtml11.dtd"))) {
            cdd_doctype_data->doctype = CDD_XHTML_1_1;
        } else if (memmem(html_doctype.buffer, html_doctype.length, "DTD/xhtml1-frameset.dtd", strlen("DTD/xhtml1-frameset.dtd"))) {
            cdd_doctype_data->doctype = CDD_XHTML_1_0_FRAMESET;
        } else if (memmem(html_doctype.buffer, html_doctype.length, "DTD/xhtml1-transitional.dtd", strlen("DTD/xhtml1-transitional.dtd"))) {
            cdd_doctype_data->doctype = CDD_XHTML_1_0_TRANSITIONAL;
        } else if (memmem(html_doctype.buffer, html_doctype.length, "DTD/xhtml1-strict.dtd", strlen("DTD/xhtml1-strict.dtd"))) {
            cdd_doctype_data->doctype = CDD_XHTML_1_0_STRICT;
        } else if (memmem(html_doctype.buffer, html_doctype.length, "html4/frameset.dtd", strlen("html4/frameset.dtd"))) {
            cdd_doctype_data->doctype = CDD_HTML_4_01_FRAMESET;
        } else if (memmem(html_doctype.buffer, html_doctype.length, "html4/loose.dtd", strlen("html4/loose.dtd"))) {
            cdd_doctype_data->doctype = CDD_HTML_4_01_TRANSITIONAL;
        } else if (memmem(html_doctype.buffer, html_doctype.length, "html4/strict.dtd", strlen("html4/strict.dtd"))) {
            cdd_doctype_data->doctype = CDD_HTML_4_01_STRICT;
        } else if (memmem(html_doctype.buffer, html_doctype.length, "html", strlen("html"))) {
            cdd_doctype_data->doctype = CDD_HTML_5;
        } else {
            cdd_doctype_data->doctype = CDD_HTML_INVALID;
        }

        /* throw CDD event */
        pace2_cdd_throw_event(pace2_module, thread_ID, cdd_event);
    }
    return PACE2_SUCCESS;
}

void cdd_print_doctype_event (PACE2_cdd_event const * const cdd_event)
{
    struct cdd_doctype_event_data * cdd_doctype_data = NULL;

    if (cdd_event == NULL) {
        return;
    }
    cdd_doctype_data = (struct cdd_doctype_event_data *) cdd_event->cdd_data;
    printf("CDD Event: ID = %5u; Event ID = %5u; Doctype: %s\n",
           cdd_event->cdd_id, cdd_event->cdd_event_id, cdd_doctype_str[cdd_doctype_data->doctype]);
}

PACE2_return_state cdd_count_http_payload(PACE2_module * const pace2_module,
                                          int const thread_ID,
                                          PACE2_event const * const event,
                                          struct PACE2_cdd_callback_data * const callback_data)
{
    struct cdd_http_user_data *data = (struct cdd_http_user_data *)callback_data->cdd_userptr;

    /* simple sanity check */
    if (data == NULL) {
        return PACE2_FAILURE;
    }

    /* count HTTP payload events */
    if (event->header.type == PACE2_ADVANCED_HTTP_EVENT &&
        (event->http_advanced_meta_data.meta_data_type == PACE2_ADVANCED_HTTP_RESPONSE_PAYLOAD ||
         event->http_advanced_meta_data.meta_data_type == PACE2_ADVANCED_HTTP_REQUEST_PAYLOAD))
    {
        data->event_counter++;
    }

    /* throw an event with the actual number for each flow dropped event */
    if (event->header.type == PACE2_FLOW_DROPPED_EVENT) {
        struct cdd_http_event_data * cdd_http_data = NULL;
        PACE2_event * cdd_event = NULL;

        /* allocate event slot for the CDD */
        PACE2_return_state retval = pace2_cdd_allocate_event(pace2_module, thread_ID, CDD_HTTP_EVENT_ID, &cdd_event);
        if (retval != PACE2_SUCCESS) {
            return retval;
        }

        cdd_http_data = (struct cdd_http_event_data *) cdd_event->cdd_meta_data.cdd_data;
        cdd_http_data->number_http_payload_events = data->event_counter;

        /* throw CDD event */
        pace2_cdd_throw_event(pace2_module, thread_ID, cdd_event);
    }

    return PACE2_SUCCESS;
}

void cdd_print_http_event (PACE2_cdd_event const * const cdd_event)
{
    struct cdd_http_event_data * cdd_http_data = NULL;

    if (cdd_event == NULL) {
        return;
    }
    cdd_http_data = (struct cdd_http_event_data *) cdd_event->cdd_data;
    printf("CDD Event: ID = %5u; Event ID = %5u; HTTP Payload Events: %10u\n",
           cdd_event->cdd_id, cdd_event->cdd_event_id, cdd_http_data->number_http_payload_events);
}

#endif                  /* CDD_EXAMPLE_DOCTYPE_HTTP_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
