/********************************************************************************/
/**
 ** \file       cdd_example_class.h
 ** \brief      PACE 2 Custom Defined Decoder example for an aggregating decoder.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef CDD_EXAMPLE_CLASS_H
#define CDD_EXAMPLE_CLASS_H

/* Includes *********************************************************************/
#include "cdd_example_generic.h"

/* Public Types *****************************************************************/
struct cdd_userpass_event_data {
    struct ipd_charset_string username;
    struct ipd_charset_string password;
};

/* Public Prototypes ************************************************************/
PACE2_return_state cdd_decode_userpass(PACE2_module * const pace2_module,
                                       int const thread_ID,
                                       PACE2_event const * const event,
                                       struct PACE2_cdd_callback_data * const callback_data)
{
    struct ipd_charset_string const * user = NULL;
    struct ipd_charset_string const * pass = NULL;
    struct cdd_class_flow_user_data * flow_user_data = NULL;
    struct cdd_userpass_event_data * cdd_userpass_data = NULL;
    PACE2_event * cdd_event = NULL;

    if (event->header.type == PACE2_ADVANCED_IMAP_EVENT) {
        if (event->imap_advanced_meta_data.meta_data_type == PACE2_ADVANCED_IMAP_USER) {
            user = &(event->imap_advanced_meta_data.event_data.user);
        } else if (event->imap_advanced_meta_data.meta_data_type == PACE2_ADVANCED_IMAP_PASS) {
            pass = &event->imap_advanced_meta_data.event_data.pass;
        }
    }

    if (event->header.type == PACE2_ADVANCED_POP3_EVENT) {
        if (event->pop3_advanced_meta_data.meta_data_type == PACE2_ADVANCED_POP3_USER) {
            user = &event->pop3_advanced_meta_data.event_data.user;
        } else if (event->pop3_advanced_meta_data.meta_data_type == PACE2_ADVANCED_POP3_PASS) {
            pass = &event->pop3_advanced_meta_data.event_data.pass;
        }
    }

    if (event->header.type == PACE2_ADVANCED_SMTP_EVENT) {
        if (event->smtp_advanced_meta_data.meta_data_type == PACE2_ADVANCED_SMTP_USER) {
            user = &event->smtp_advanced_meta_data.event_data.user;
        } else if (event->smtp_advanced_meta_data.meta_data_type == PACE2_ADVANCED_SMTP_PASS) {
            pass = &event->smtp_advanced_meta_data.event_data.pass;
        }
    }

    switch (callback_data->descriptor_set) {
        case PACE2_CDD_DESCRIPTOR_SET_PACKET:
            flow_user_data = &((union cdd_flow_user_data *)callback_data->descriptor.packet->flow_user_data)->class_data;
            break;
        case PACE2_CDD_DESCRIPTOR_SET_STREAM:
            flow_user_data = &((union cdd_flow_user_data *)callback_data->descriptor.stream->flow_user_data)->class_data;
            break;
        case PACE2_CDD_DESCRIPTOR_NOT_SET:
        default:
            /* accessing the flow user data is required for this CDD to work */
            return PACE2_FAILURE;
    }

    if (user) {
        if (NULL != flow_user_data->username.content.buffer) {
            free(flow_user_data->username.content.buffer);
        }

        flow_user_data->username.content.buffer = malloc(user->content.length);
        if (NULL == flow_user_data->username.content.buffer) {
            return PACE2_OUT_OF_MEMORY;
        }

        memcpy(flow_user_data->username.content.buffer, user->content.buffer, user->content.length);
        flow_user_data->username.content.length = user->content.length;
        flow_user_data->username.charset = user->charset;

        return PACE2_SUCCESS;
    }

    if (pass) {
        /* allocate event slot for the CDD */
        PACE2_return_state retval = pace2_cdd_allocate_event(pace2_module, thread_ID, CDD_USERPASS_EVENT_ID, &cdd_event);
        if (retval != PACE2_SUCCESS) {
            return retval;
        }

        /* access the event's data */
        cdd_userpass_data = (struct cdd_userpass_event_data *) cdd_event->cdd_meta_data.cdd_data;

        if (NULL != flow_user_data->username.content.buffer) {
            cdd_userpass_data->username = flow_user_data->username;
        }

        cdd_userpass_data->password = *pass;

        /* throw CDD event */
        return pace2_cdd_throw_event(pace2_module, thread_ID, cdd_event);
    }

    return PACE2_SUCCESS;
}

void cdd_print_userpass_event(PACE2_cdd_event const * const cdd_event)
{
    struct cdd_userpass_event_data * cdd_userpass_data = NULL;

    if (NULL == cdd_event) {
        return;
    }
    cdd_userpass_data = (struct cdd_userpass_event_data *) cdd_event->cdd_data;
    printf("CDD Event: ID = %5u; Event ID = %5u; Username: '%.*s', Password: '%.*s'\n",
           cdd_event->cdd_id, cdd_event->cdd_event_id,
           (int)cdd_userpass_data->username.content.length, cdd_userpass_data->username.content.buffer,
           (int)cdd_userpass_data->password.content.length, cdd_userpass_data->password.content.buffer);
}

void cdd_cleanup_flow_user_data(PACE2_flow_dropped const * const flow_dropped_event)
{
    struct cdd_class_flow_user_data * flow_user_data = NULL;

    if (NULL == flow_dropped_event) {
        return;
    }

    flow_user_data = (struct cdd_class_flow_user_data *)flow_dropped_event->flow_user_data;

    if (NULL != flow_user_data || NULL != flow_user_data->username.content.buffer) {
        free(flow_user_data->username.content.buffer);
        memset(flow_user_data, 0, sizeof(struct cdd_class_flow_user_data));
    }
}

#endif /* CDD_EXAMPLE_CLASS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
