/********************************************************************************/
/**
 ** \file       mail_events.h
 ** \brief      Mail event definitions
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef MAIL_EVENTS_H
#define MAIL_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the mail class event.
 */
#define PACE2_CLASS_MAIL_EVENT_GROUP PACE2_CLASS_PROTOCOL_META_DATA_GROUP

/* Event Types ******************************************************************/

/**
 * @brief Types for MAIL class events.
 */
typedef enum {
    PACE2_CLASS_MAIL_SESSION,                   /**< @ref IPD_MAIL_CLASS_SESSION */
    PACE2_CLASS_MAIL_LOGIN,                     /**< @ref IPD_MAIL_CLASS_LOGIN */
    PACE2_CLASS_MAIL_PASS,                      /**< @ref IPD_MAIL_CLASS_PASS */
    PACE2_CLASS_MAIL_SESSION_TRANSFER,          /**< @ref IPD_MAIL_CLASS_SESSION_TRANSFER */
    PACE2_CLASS_MAIL_SESSION_BODY_TRANSFER,     /**< @ref IPD_MAIL_CLASS_SESSION_BODY_TRANSFER */
    PACE2_CLASS_MAIL_SESSION_TRANSFER_END,      /**< @ref IPD_MAIL_CLASS_SESSION_TRANSFER_END */
    PACE2_CLASS_MAIL_ATTACHMENT_INFO,           /**< @ref IPD_MAIL_CLASS_ATTACHMENT_INFO */
    PACE2_CLASS_MAIL_ATTACHMENT_CONTENT,        /**< @ref IPD_MAIL_CLASS_ATTACHMENT_CONTENT */

    /** Provides data if one segment of a mail attachment including metadata about the attachment. */
    PACE2_CLASS_MAIL_ATTACHMENT_CONTENT_EXT,

    PACE2_NUMBER_OF_CLASS_MAIL_EVENT_TYPES      /**< Number of implemented event types. */
} PACE2_class_MAIL_event_type;

/* Event Structures *************************************************************/

#ifndef PACE2_DISABLE_DECODER

/**
 * @brief Data structure for @ref PACE2_CLASS_MAIL_ATTACHMENT_CONTENT_EXT events.
 *
 * This event is created at the same time @ref PACE2_CLASS_MAIL_ATTACHMENT_CONTENT. It contains the same data
 * as the according @ref PACE2_CLASS_MAIL_ATTACHMENT_CONTENT but additionally contains the data already submitted
 * via the @ref PACE2_CLASS_MAIL_ATTACHMENT_INFO event related to the same attachment.
 *
 * This event will not be created if @ref PACE2_config_s4_decoding.mail_class_enable_extended_attachment_content_events is disabled (default).
 */
typedef struct {
    struct ipd_class_mail_attachment_info_struct attachment_info;           /**< Contains data for the related @ref PACE2_CLASS_MAIL_ATTACHMENT_INFO event. */
    struct ipd_class_mail_attachment_content_struct attachment_content;     /**< Contains the actual attachment content data. */
} PACE2_class_MAIL_attachment_content_ext;

/**
 * @brief Data structure for MAIL class events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_CLASS_MAIL_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_class_MAIL_event_type meta_data_type;     /**< MAIL event subtype. */
    PACE2_CLASS_META_DATA_EVENT_EXTRA_FIELDS;
    union {
        struct ipd_class_mail_session_struct session;                           /**< Contains data for a @ref PACE2_CLASS_MAIL_SESSION event. */
        struct ipd_class_mail_session_string_struct login;                      /**< Contains data for a @ref PACE2_CLASS_MAIL_LOGIN event. */
        struct ipd_class_mail_session_string_struct password;                   /**< Contains data for a @ref PACE2_CLASS_MAIL_PASS event. */
        struct ipd_class_mail_transfer_struct transfer;                         /**< Contains data for a @ref PACE2_CLASS_MAIL_SESSION_TRANSFER event. */
        struct ipd_class_mail_transfer_body_struct body;                        /**< Contains data for a @ref PACE2_CLASS_MAIL_SESSION_BODY_TRANSFER event. */
        u64 transfer_end;                                                       /**< Contains data for a @ref PACE2_CLASS_MAIL_SESSION_TRANSFER_END event. */
        struct ipd_class_mail_attachment_info_struct attachment_info;           /**< Contains data for a @ref PACE2_CLASS_MAIL_ATTACHMENT_INFO event. */
        struct ipd_class_mail_attachment_content_struct attachment_content;     /**< Contains data for a @ref PACE2_CLASS_MAIL_ATTACHMENT_CONTENT event. */
        PACE2_class_MAIL_attachment_content_ext attachment_content_ext;         /**< Contains data for a @ref PACE2_CLASS_MAIL_ATTACHMENT_CONTENT_EXT event. */
    } event_data;                                   /**< Named union which contains the data of the sub-event types. */
} PACE2_class_MAIL_event;

#endif

#endif /* MAIL_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
