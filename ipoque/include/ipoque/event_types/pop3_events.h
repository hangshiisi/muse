/********************************************************************************/
/**
 ** \file       pop3_events.h
 ** \brief      POP3 stage4 event definitions
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef POP3_EVENTS_H
#define POP3_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the advanced POP3 event.
 */
#define PACE2_ADVANCED_POP_EVENT_GROUP PACE2_ADVANCED_PROTOCOL_META_DATA_GROUP

/* Event Types ******************************************************************/

/**
 * @brief Types for advanced pop3 events.
 */
typedef enum {
    PACE2_ADVANCED_POP3_CLIENT_DIRECTION,                 /**< @ref IPD_EVENT_POP3_CLIENT_DIRECTION */
    PACE2_ADVANCED_POP3_SERVER_GREETING,                  /**< @ref IPD_EVENT_POP3_SERVER_GREETING */
    PACE2_ADVANCED_POP3_USER,                             /**< @ref IPD_EVENT_POP3_USER */
    PACE2_ADVANCED_POP3_PASS,                             /**< @ref IPD_EVENT_POP3_PASS */
    PACE2_ADVANCED_POP3_APOP_DIGEST,                      /**< @ref IPD_EVENT_POP3_APOP_DIGEST */
    PACE2_ADVANCED_POP3_RETR,                             /**< @ref IPD_EVENT_POP3_RETR */
    PACE2_ADVANCED_POP3_TOP,                              /**< @ref IPD_EVENT_POP3_TOP */
    PACE2_ADVANCED_POP3_QUIT,                             /**< @ref IPD_EVENT_POP3_QUIT */
    PACE2_ADVANCED_POP3_LIST_ENTRY,                       /**< @ref IPD_EVENT_POP3_LIST_ENTRY */
    PACE2_ADVANCED_POP3_UIDL_ENTRY,                       /**< @ref IPD_EVENT_POP3_UIDL_ENTRY */
    PACE2_ADVANCED_POP3_LIST_END,                         /**< @ref IPD_EVENT_POP3_LIST_END */
    PACE2_ADVANCED_POP3_UIDL_END,                         /**< @ref IPD_EVENT_POP3_UIDL_END */
    PACE2_ADVANCED_POP3_IMF_FROM,                         /**< @ref IPD_EVENT_POP3_IMF_FROM */
    PACE2_ADVANCED_POP3_IMF_TO,                           /**< @ref IPD_EVENT_POP3_IMF_TO */
    PACE2_ADVANCED_POP3_IMF_CC,                           /**< @ref IPD_EVENT_POP3_IMF_CC */
    PACE2_ADVANCED_POP3_IMF_BCC,                          /**< @ref IPD_EVENT_POP3_IMF_BCC */
    PACE2_ADVANCED_POP3_IMF_SUBJECT,                      /**< @ref IPD_EVENT_POP3_IMF_SUBJECT */
    PACE2_ADVANCED_POP3_IMF_DATE,                         /**< @ref IPD_EVENT_POP3_IMF_DATE */
    PACE2_ADVANCED_POP3_IMF_SENDER,                       /**< @ref IPD_EVENT_POP3_IMF_SENDER */
    PACE2_ADVANCED_POP3_IMF_REPLY_TO,                     /**< @ref IPD_EVENT_POP3_IMF_REPLY_TO */
    PACE2_ADVANCED_POP3_IMF_MESSAGE_ID,                   /**< @ref IPD_EVENT_POP3_IMF_MESSAGE_ID */
    PACE2_ADVANCED_POP3_IMF_IN_REPLY_TO,                  /**< @ref IPD_EVENT_POP3_IMF_IN_REPLY_TO */
    PACE2_ADVANCED_POP3_IMF_REFERENCES,                   /**< @ref IPD_EVENT_POP3_IMF_REFERENCES */
    PACE2_ADVANCED_POP3_IMF_COMMENTS,                     /**< @ref IPD_EVENT_POP3_IMF_COMMENTS */
    PACE2_ADVANCED_POP3_IMF_KEYWORDS,                     /**< @ref IPD_EVENT_POP3_IMF_KEYWORDS */
    PACE2_ADVANCED_POP3_IMF_TRACE,                        /**< @ref IPD_EVENT_POP3_IMF_TRACE */
    PACE2_ADVANCED_POP3_IMF_RESENT_DATE,                  /**< @ref IPD_EVENT_POP3_IMF_RESENT_DATE */
    PACE2_ADVANCED_POP3_IMF_RESENT_FROM,                  /**< @ref IPD_EVENT_POP3_IMF_RESENT_FROM */
    PACE2_ADVANCED_POP3_IMF_RESENT_SENDER,                /**< @ref IPD_EVENT_POP3_IMF_RESENT_SENDER */
    PACE2_ADVANCED_POP3_IMF_RESENT_TO,                    /**< @ref IPD_EVENT_POP3_IMF_RESENT_TO */
    PACE2_ADVANCED_POP3_IMF_RESENT_CC,                    /**< @ref IPD_EVENT_POP3_IMF_RESENT_CC */
    PACE2_ADVANCED_POP3_IMF_RESENT_BCC,                   /**< @ref IPD_EVENT_POP3_IMF_RESENT_BCC */
    PACE2_ADVANCED_POP3_IMF_RESENT_MSG_ID,                /**< @ref IPD_EVENT_POP3_IMF_RESENT_MSG_ID */
    PACE2_ADVANCED_POP3_IMF_MIME_VERSION,                 /**< @ref IPD_EVENT_POP3_IMF_MIME_VERSION */
    PACE2_ADVANCED_POP3_IMF_OTHER,                        /**< @ref IPD_EVENT_POP3_IMF_OTHER */
    PACE2_ADVANCED_POP3_IMF_HEADER,                       /**< @ref IPD_EVENT_POP3_IMF_HEADER */
    PACE2_ADVANCED_POP3_IMF_CONTENT_TYPE,                 /**< @ref IPD_EVENT_POP3_IMF_CONTENT_TYPE */
    PACE2_ADVANCED_POP3_IMF_CONTENT_TRANSFER_ENCODING,    /**< @ref IPD_EVENT_POP3_IMF_CONTENT_TRANSFER_ENCODING */
    PACE2_ADVANCED_POP3_IMF_CONTENT_DISPOSITION,          /**< @ref IPD_EVENT_POP3_IMF_CONTENT_DISPOSITION */
    PACE2_ADVANCED_POP3_IMF_PART_HEADER,                  /**< @ref IPD_EVENT_POP3_IMF_PART_HEADER */
    PACE2_ADVANCED_POP3_IMF_DATA_BEGIN,                   /**< @ref IPD_EVENT_POP3_IMF_DATA_BEGIN */
    PACE2_ADVANCED_POP3_IMF_DATA,                         /**< @ref IPD_EVENT_POP3_IMF_DATA */
    PACE2_ADVANCED_POP3_IMF_DATA_END,                     /**< @ref IPD_EVENT_POP3_IMF_DATA_END */
    PACE2_ADVANCED_POP3_IMF_DONE,                         /**< @ref IPD_EVENT_POP3_IMF_DONE */
    PACE2_ADVANCED_POP3_STARTTLS,                         /**< @ref IPD_EVENT_POP3_STARTTLS */
    PACE2_ADVANCED_POP3_INVALID,                          /**< @ref IPD_EVENT_POP3_INVALID */
    PACE2_ADVANCED_POP3_CONNECTION_END,                   /**< @ref IPD_EVENT_POP3_CONNECTION_END */
    PACE2_ADVANCED_POP3_RESPONSE,                         /**< @ref IPD_EVENT_POP3_RESPONSE */
    PACE2_ADVANCED_POP3_COMMAND,                          /**< @ref IPD_EVENT_POP3_COMMAND */
    PACE2_ADVANCED_POP3_IMF_RETURN_PATH,                  /**< @ref IPD_EVENT_POP3_IMF_RETURN_PATH */
    PACE2_ADVANCED_POP3_IMF_RECEIVED,                     /**< @ref IPD_EVENT_POP3_IMF_RECEIVED */

    PACE2_NUMBER_OF_ADVANCED_POP3_EVENT_TYPES             /**< Number of implemented event types. */
} PACE2_advanced_pop3_event_type;

/* Event Structures *************************************************************/

#ifndef PACE2_DISABLE_DECODER

/**
 * @brief Data structure for advanced pop3 events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_ADVANCED_POP3_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_advanced_pop3_event_type meta_data_type;      /**< POP3 event subtype. */
    PACE2_ADVANCED_META_DATA_EVENT_EXTRA_FIELDS;
    union {
        int  client_direction;                                     /**< Contains data for a @ref PACE2_ADVANCED_POP3_CLIENT_DIRECTION event. */
        struct ipd_charset_string server_greeting;                 /**< Contains data for a @ref PACE2_ADVANCED_POP3_SERVER_GREETING event. */
        struct ipd_charset_string user;                            /**< Contains data for a @ref PACE2_ADVANCED_POP3_USER event. */
        struct ipd_charset_string pass;                            /**< Contains data for a @ref PACE2_ADVANCED_POP3_PASS event. */
        struct ipd_charset_string apop_digest;                     /**< Contains data for a @ref PACE2_ADVANCED_POP3_APOP_DIGEST event. */
        struct ipd_pop3_list_entry list_entry;                     /**< Contains data for a @ref PACE2_ADVANCED_POP3_LIST_ENTRY event. */
        struct ipd_pop3_list_entry uidl_entry;                     /**< Contains data for a @ref PACE2_ADVANCED_POP3_UIDL_ENTRY event. */
        struct ipd_imf_address imf_from;                           /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_FROM event. */
        struct ipd_imf_address imf_to;                             /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_TO event. */
        struct ipd_imf_address imf_cc;                             /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_CC event. */
        struct ipd_imf_address imf_bcc;                            /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_BCC event. */
        struct ipd_charset_string imf_subject;                     /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_SUBJECT event. */
        struct ipd_charset_string imf_date;                        /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_DATE event. */
        struct ipd_imf_address imf_sender;                         /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_SENDER event. */
        struct ipd_imf_address imf_reply_to;                       /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_REPLY_TO event. */
        struct ipd_charset_string imf_message_id;                  /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_MESSAGE_ID event. */
        struct ipd_charset_string imf_in_reply_to;                 /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_IN_REPLY_TO event. */
        struct ipd_charset_string imf_references;                  /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_REFERENCES event. */
        struct ipd_charset_string imf_comments;                    /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_COMMENTS event. */
        struct ipd_charset_string imf_keywords;                    /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_KEYWORDS event. */
        struct ipd_charset_string imf_trace;                       /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_TRACE event. */
        struct ipd_charset_string imf_resent_date;                 /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_RESENT_DATE event. */
        struct ipd_imf_address imf_resent_from;                    /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_RESENT_FROM event. */
        struct ipd_imf_address imf_resent_sender;                  /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_RESENT_SENDER event. */
        struct ipd_imf_address imf_resent_to;                      /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_RESENT_TO event. */
        struct ipd_imf_address imf_resent_cc;                      /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_RESENT_CC event. */
        struct ipd_imf_address imf_resent_bcc;                     /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_RESENT_BCC event. */
        struct ipd_charset_string imf_resent_msg_id;               /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_RESENT_MSG_ID event. */
        struct ipd_charset_string imf_mime_version;                /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_MIME_VERSION event. */
        struct ipd_imf_part_data  imf_other;                       /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_OTHER event. */
        struct ipd_charset_string imf_header;                      /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_HEADER event. */
        struct ipd_imf_content_type imf_content_type;              /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_CONTENT_TYPE event. */
        struct ipd_imf_part_data imf_content_transfer_encoding;    /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_CONTENT_TRANSFER_ENCODING event. */
        struct ipd_imf_part_data imf_content_disposition;          /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_CONTENT_DISPOSITION event. */
        struct ipd_imf_part_data imf_part_header;                  /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_PART_HEADER event. */
        struct ipd_charset_string imf_data_begin;                  /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_DATA_BEGIN event. */
        struct ipd_imf_part_data imf_data;                         /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_DATA event. */
        struct ipd_charset_string imf_data_end;                    /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_DATA_END event. */
        const char * invalid;                                      /**< Contains data for a @ref PACE2_ADVANCED_POP3_INVALID event. */
        struct ipd_pop3_response response;                         /**< Contains data for a @ref PACE2_ADVANCED_POP3_RESPONSE event. */
        struct ipd_pop3_command command;                           /**< Contains data for a @ref PACE2_ADVANCED_POP3_COMMAND event. */
        struct ipd_charset_string imf_return_path;                 /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_RETURN_PATH event. */
        struct ipd_charset_string imf_received;                    /**< Contains data for a @ref PACE2_ADVANCED_POP3_IMF_RECEIVED event. */
    } event_data;                                                  /**< Named union which contains the data of the sub-event types. */
} PACE2_advanced_pop3_event;

#endif

#endif /* POP3_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
