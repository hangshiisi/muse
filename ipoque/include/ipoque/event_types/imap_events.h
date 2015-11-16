/********************************************************************************/
/**
 ** \file       imap_events.h
 ** \brief      IMAP stage4 event definitions
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef IMAP_EVENTS_H
#define IMAP_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the advanced IMAP event.
 */
#define PACE2_ADVANCED_IMAP_EVENT_GROUP PACE2_ADVANCED_PROTOCOL_META_DATA_GROUP

/* Event Types ******************************************************************/

/**
 * @brief Types for advanced imap events.
 */
typedef enum {
    PACE2_ADVANCED_IMAP_CLIENT_DIRECTION,                 /**< @ref IPD_EVENT_IMAP_CLIENT_DIRECTION. */
    PACE2_ADVANCED_IMAP_USER,                             /**< @ref IPD_EVENT_IMAP_USER. */
    PACE2_ADVANCED_IMAP_PASS,                             /**< @ref IPD_EVENT_IMAP_PASS. */
    PACE2_ADVANCED_IMAP_STARTTLS,                         /**< @ref IPD_EVENT_IMAP_STARTTLS. */
    PACE2_ADVANCED_IMAP_GREETING,                         /**< @ref IPD_EVENT_IMAP_GREETING. */
    PACE2_ADVANCED_IMAP_FETCH_BODY_ITEM,                  /**< @ref IPD_EVENT_IMAP_FETCH_BODY_ITEM. */
    PACE2_ADVANCED_IMAP_APPEND,                           /**< @ref IPD_EVENT_IMAP_APPEND. */
    PACE2_ADVANCED_IMAP_RESPONSE,                         /**< @ref IPD_EVENT_IMAP_RESPONSE. */
    PACE2_ADVANCED_IMAP_LOGOUT,                           /**< @ref IPD_EVENT_IMAP_LOGOUT. */
    PACE2_ADVANCED_IMAP_BYE,                              /**< @ref IPD_EVENT_IMAP_BYE. */
    PACE2_ADVANCED_IMAP_IMF_FROM,                         /**< @ref IPD_EVENT_IMAP_IMF_FROM. */
    PACE2_ADVANCED_IMAP_IMF_TO,                           /**< @ref IPD_EVENT_IMAP_IMF_TO. */
    PACE2_ADVANCED_IMAP_IMF_CC,                           /**< @ref IPD_EVENT_IMAP_IMF_CC. */
    PACE2_ADVANCED_IMAP_IMF_BCC,                          /**< @ref IPD_EVENT_IMAP_IMF_BCC. */
    PACE2_ADVANCED_IMAP_IMF_SUBJECT,                      /**< @ref IPD_EVENT_IMAP_IMF_SUBJECT. */
    PACE2_ADVANCED_IMAP_IMF_DATE,                         /**< @ref IPD_EVENT_IMAP_IMF_DATE. */
    PACE2_ADVANCED_IMAP_IMF_SENDER,                       /**< @ref IPD_EVENT_IMAP_IMF_SENDER. */
    PACE2_ADVANCED_IMAP_IMF_REPLY_TO,                     /**< @ref IPD_EVENT_IMAP_IMF_REPLY_TO. */
    PACE2_ADVANCED_IMAP_IMF_MESSAGE_ID,                   /**< @ref IPD_EVENT_IMAP_IMF_MESSAGE_ID. */
    PACE2_ADVANCED_IMAP_IMF_IN_REPLY_TO,                  /**< @ref IPD_EVENT_IMAP_IMF_IN_REPLY_TO. */
    PACE2_ADVANCED_IMAP_IMF_REFERENCES,                   /**< @ref IPD_EVENT_IMAP_IMF_REFERENCES. */
    PACE2_ADVANCED_IMAP_IMF_COMMENTS,                     /**< @ref IPD_EVENT_IMAP_IMF_COMMENTS. */
    PACE2_ADVANCED_IMAP_IMF_KEYWORDS,                     /**< @ref IPD_EVENT_IMAP_IMF_KEYWORDS. */
    PACE2_ADVANCED_IMAP_IMF_TRACE,                        /**< @ref IPD_EVENT_IMAP_IMF_TRACE. */
    PACE2_ADVANCED_IMAP_IMF_RESENT_DATE,                  /**< @ref IPD_EVENT_IMAP_IMF_RESENT_DATE. */
    PACE2_ADVANCED_IMAP_IMF_RESENT_FROM,                  /**< @ref IPD_EVENT_IMAP_IMF_RESENT_FROM. */
    PACE2_ADVANCED_IMAP_IMF_RESENT_SENDER,                /**< @ref IPD_EVENT_IMAP_IMF_RESENT_SENDER. */
    PACE2_ADVANCED_IMAP_IMF_RESENT_TO,                    /**< @ref IPD_EVENT_IMAP_IMF_RESENT_TO. */
    PACE2_ADVANCED_IMAP_IMF_RESENT_CC,                    /**< @ref IPD_EVENT_IMAP_IMF_RESENT_CC. */
    PACE2_ADVANCED_IMAP_IMF_RESENT_BCC,                   /**< @ref IPD_EVENT_IMAP_IMF_RESENT_BCC. */
    PACE2_ADVANCED_IMAP_IMF_RESENT_MSG_ID,                /**< @ref IPD_EVENT_IMAP_IMF_RESENT_MSG_ID. */
    PACE2_ADVANCED_IMAP_IMF_MIME_VERSION,                 /**< @ref IPD_EVENT_IMAP_IMF_MIME_VERSION. */
    PACE2_ADVANCED_IMAP_IMF_OTHER,                        /**< @ref IPD_EVENT_IMAP_IMF_OTHER. */
    PACE2_ADVANCED_IMAP_IMF_HEADER,                       /**< @ref IPD_EVENT_IMAP_IMF_HEADER. */
    PACE2_ADVANCED_IMAP_IMF_CONTENT_TYPE,                 /**< @ref IPD_EVENT_IMAP_IMF_CONTENT_TYPE. */
    PACE2_ADVANCED_IMAP_IMF_CONTENT_TRANSFER_ENCODING,    /**< @ref IPD_EVENT_IMAP_IMF_CONTENT_TRANSFER_ENCODING. */
    PACE2_ADVANCED_IMAP_IMF_CONTENT_DISPOSITION,          /**< @ref IPD_EVENT_IMAP_IMF_CONTENT_DISPOSITION. */
    PACE2_ADVANCED_IMAP_IMF_PART_HEADER,                  /**< @ref IPD_EVENT_IMAP_IMF_PART_HEADER. */
    PACE2_ADVANCED_IMAP_IMF_DATA_BEGIN,                   /**< @ref IPD_EVENT_IMAP_IMF_DATA_BEGIN. */
    PACE2_ADVANCED_IMAP_IMF_DATA,                         /**< @ref IPD_EVENT_IMAP_IMF_DATA. */
    PACE2_ADVANCED_IMAP_IMF_DATA_END,                     /**< @ref IPD_EVENT_IMAP_IMF_DATA_END. */
    PACE2_ADVANCED_IMAP_IMF_DONE,                         /**< @ref IPD_EVENT_IMAP_IMF_DONE. */
    PACE2_ADVANCED_IMAP_INVALID,                          /**< @ref IPD_EVENT_IMAP_INVALID. */
    PACE2_ADVANCED_IMAP_CONNECTION_END,                   /**< @ref IPD_EVENT_IMAP_CONNECTION_END. */
    PACE2_ADVANCED_IMAP_IMF_RETURN_PATH,                  /**< @ref IPD_EVENT_IMAP_IMF_RETURN_PATH. */
    PACE2_ADVANCED_IMAP_IMF_RECEIVED,                     /**< @ref IPD_EVENT_IMAP_IMF_RECEIVED. */

    PACE2_NUMBER_OF_ADVANCED_IMAP_EVENT_TYPES             /**< Number of implemented event types. */
} PACE2_advanced_imap_event_type;

/* Event Structures *************************************************************/


#ifndef PACE2_DISABLE_DECODER
/**
 * @brief Data structure for advanced imap events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_ADVANCED_IMAP_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_advanced_imap_event_type meta_data_type;      /**< IMAP event subtype. */
    PACE2_ADVANCED_META_DATA_EVENT_EXTRA_FIELDS;
    union {
        int client_direction;                                      /**< Contains data for a @ref PACE2_ADVANCED_IMAP_CLIENT_DIRECTION event. */
        struct ipd_charset_string user;                            /**< Contains data for a @ref PACE2_ADVANCED_IMAP_USER event. */
        struct ipd_charset_string pass;                            /**< Contains data for a @ref PACE2_ADVANCED_IMAP_PASS event. */
        struct ipd_imap_greeting greeting;                         /**< Contains data for a @ref PACE2_ADVANCED_IMAP_GREETING event. */
        struct ipd_imap_fetch_body_item fetch_body_item;           /**< Contains data for a @ref PACE2_ADVANCED_IMAP_FETCH_BODY_ITEM event. */
        struct ipd_charset_string append;                          /**< Contains data for a @ref PACE2_ADVANCED_IMAP_APPEND event. */
        struct ipd_imap_response response;                         /**< Contains data for a @ref PACE2_ADVANCED_IMAP_RESPONSE event. */
        struct ipd_imf_address imf_from;                           /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_FROM event. */
        struct ipd_imf_address imf_to;                             /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_TO event. */
        struct ipd_imf_address imf_cc;                             /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_CC event. */
        struct ipd_imf_address imf_bcc;                            /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_BCC event. */
        struct ipd_charset_string imf_subject;                     /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_SUBJECT event. */
        struct ipd_charset_string imf_date;                        /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_DATE event. */
        struct ipd_imf_address imf_sender;                         /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_SENDER event. */
        struct ipd_imf_address imf_reply_to;                       /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_REPLY_TO event. */
        struct ipd_charset_string imf_message_id;                  /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_MESSAGE_ID event. */
        struct ipd_charset_string imf_in_reply_to;                 /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_IN_REPLY_TO event. */
        struct ipd_charset_string imf_references;                  /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_REFERENCES event. */
        struct ipd_charset_string imf_comments;                    /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_COMMENTS event. */
        struct ipd_charset_string imf_keywords;                    /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_KEYWORDS event. */
        struct ipd_charset_string imf_trace;                       /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_TRACE event. */
        struct ipd_charset_string imf_resent_date;                 /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_RESENT_DATE event. */
        struct ipd_imf_address imf_resent_from;                    /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_RESENT_FROM event. */
        struct ipd_imf_address imf_resent_sender;                  /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_RESENT_SENDER event. */
        struct ipd_imf_address imf_resent_to;                      /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_RESENT_TO event. */
        struct ipd_imf_address imf_resent_cc;                      /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_RESENT_CC event. */
        struct ipd_imf_address imf_resent_bcc;                     /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_RESENT_BCC event. */
        struct ipd_charset_string imf_resent_msg_id;               /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_RESENT_MSG_ID event. */
        struct ipd_charset_string imf_mime_version;                /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_MIME_VERSION event. */
        struct ipd_imf_part_data imf_other;                        /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_OTHER event. */
        struct ipd_charset_string imf_header;                      /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_HEADER event. */
        struct ipd_imf_content_type imf_content_type;              /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_CONTENT_TYPE event. */
        struct ipd_imf_part_data imf_content_transfer_encoding;    /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_CONTENT_TRANSFER_ENCODING event. */
        struct ipd_imf_part_data imf_content_disposition;          /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_CONTENT_DISPOSITION event. */
        struct ipd_imf_part_data imf_part_header;                  /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_PART_HEADER event. */
        struct ipd_charset_string imf_data_begin;                  /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_DATA_BEGIN event. */
        struct ipd_imf_part_data imf_data;                         /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_DATA event. */
        struct ipd_charset_string imf_data_end;                    /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_DATA_END event. */
        const char * invalid;                                      /**< Contains data for a @ref PACE2_ADVANCED_IMAP_INVALID event. */
        struct ipd_charset_string imf_return_path;                 /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_RETURN_PATH event. */
        struct ipd_charset_string imf_received;                    /**< Contains data for a @ref PACE2_ADVANCED_IMAP_IMF_RECEIVED event. */
    } event_data;                                                  /**< Named union which contains the data of the sub-event types. */
} PACE2_advanced_imap_event;

#endif

#endif /* IMAP_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
