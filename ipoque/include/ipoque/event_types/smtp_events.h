/********************************************************************************/
/**
 ** \file       smtp_events.h
 ** \brief      SMTP stage4 event definitions
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef SMTP_EVENTS_H
#define SMTP_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the advanced SMTP event.
 */
#define PACE2_ADVANCED_SMTP_EVENT_GROUP PACE2_ADVANCED_PROTOCOL_META_DATA_GROUP

/* Event Types ******************************************************************/

/**
 * @brief Types for advanced smtp events.
 */
typedef enum {
    PACE2_ADVANCED_SMTP_CLIENT_DIRECTION,                 /**< @ref IPD_EVENT_SMTP_CLIENT_DIRECTION. */
    PACE2_ADVANCED_SMTP_SERVER_GREETING,                  /**< @ref IPD_EVENT_SMTP_SERVER_GREETING. */
    PACE2_ADVANCED_SMTP_CONNECTION_END,                   /**< @ref IPD_EVENT_SMTP_CONNECTION_END. */
    PACE2_ADVANCED_SMTP_INVALID,                          /**< @ref IPD_EVENT_SMTP_INVALID. */
    PACE2_ADVANCED_SMTP_EHLO,                             /**< @ref IPD_EVENT_SMTP_EHLO. */
    PACE2_ADVANCED_SMTP_STARTTLS,                         /**< @ref IPD_EVENT_SMTP_STARTTLS. */
    PACE2_ADVANCED_SMTP_USER,                             /**< @ref IPD_EVENT_SMTP_USER. */
    PACE2_ADVANCED_SMTP_PASS,                             /**< @ref IPD_EVENT_SMTP_PASS. */
    PACE2_ADVANCED_SMTP_MAIL_FROM,                        /**< @ref IPD_EVENT_SMTP_MAIL_FROM. */
    PACE2_ADVANCED_SMTP_MAIL_FROM_SIZE,                   /**< @ref IPD_EVENT_SMTP_MAIL_FROM_SIZE. */
    PACE2_ADVANCED_SMTP_RCPT_TO,                          /**< @ref IPD_EVENT_SMTP_RCPT_TO. */
    PACE2_ADVANCED_SMTP_RESET,                            /**< @ref IPD_EVENT_SMTP_RESET. */
    PACE2_ADVANCED_SMTP_QUIT,                             /**< @ref IPD_EVENT_SMTP_QUIT. */
    PACE2_ADVANCED_SMTP_SERVER_REPLY,                     /**< @ref IPD_EVENT_SMTP_SERVER_REPLY. */
    PACE2_ADVANCED_SMTP_DATA,                             /**< @ref IPD_EVENT_SMTP_DATA. */
    PACE2_ADVANCED_SMTP_IMF_FROM,                         /**< @ref IPD_EVENT_SMTP_IMF_FROM. */
    PACE2_ADVANCED_SMTP_IMF_TO,                           /**< @ref IPD_EVENT_SMTP_IMF_TO. */
    PACE2_ADVANCED_SMTP_IMF_CC,                           /**< @ref IPD_EVENT_SMTP_IMF_CC. */
    PACE2_ADVANCED_SMTP_IMF_BCC,                          /**< @ref IPD_EVENT_SMTP_IMF_BCC. */
    PACE2_ADVANCED_SMTP_IMF_SUBJECT,                      /**< @ref IPD_EVENT_SMTP_IMF_SUBJECT. */
    PACE2_ADVANCED_SMTP_IMF_DATE,                         /**< @ref IPD_EVENT_SMTP_IMF_DATE. */
    PACE2_ADVANCED_SMTP_IMF_SENDER,                       /**< @ref IPD_EVENT_SMTP_IMF_SENDER. */
    PACE2_ADVANCED_SMTP_IMF_REPLY_TO,                     /**< @ref IPD_EVENT_SMTP_IMF_REPLY_TO. */
    PACE2_ADVANCED_SMTP_IMF_MESSAGE_ID,                   /**< @ref IPD_EVENT_SMTP_IMF_MESSAGE_ID. */
    PACE2_ADVANCED_SMTP_IMF_IN_REPLY_TO,                  /**< @ref IPD_EVENT_SMTP_IMF_IN_REPLY_TO. */
    PACE2_ADVANCED_SMTP_IMF_REFERENCES,                   /**< @ref IPD_EVENT_SMTP_IMF_REFERENCES. */
    PACE2_ADVANCED_SMTP_IMF_COMMENTS,                     /**< @ref IPD_EVENT_SMTP_IMF_COMMENTS. */
    PACE2_ADVANCED_SMTP_IMF_KEYWORDS,                     /**< @ref IPD_EVENT_SMTP_IMF_KEYWORDS. */
    PACE2_ADVANCED_SMTP_IMF_TRACE,                        /**< @ref IPD_EVENT_SMTP_IMF_TRACE. */
    PACE2_ADVANCED_SMTP_IMF_RESENT_DATE,                  /**< @ref IPD_EVENT_SMTP_IMF_RESENT_DATE. */
    PACE2_ADVANCED_SMTP_IMF_RESENT_FROM,                  /**< @ref IPD_EVENT_SMTP_IMF_RESENT_FROM. */
    PACE2_ADVANCED_SMTP_IMF_RESENT_SENDER,                /**< @ref IPD_EVENT_SMTP_IMF_RESENT_SENDER. */
    PACE2_ADVANCED_SMTP_IMF_RESENT_TO,                    /**< @ref IPD_EVENT_SMTP_IMF_RESENT_TO. */
    PACE2_ADVANCED_SMTP_IMF_RESENT_CC,                    /**< @ref IPD_EVENT_SMTP_IMF_RESENT_CC. */
    PACE2_ADVANCED_SMTP_IMF_RESENT_BCC,                   /**< @ref IPD_EVENT_SMTP_IMF_RESENT_BCC. */
    PACE2_ADVANCED_SMTP_IMF_RESENT_MSG_ID,                /**< @ref IPD_EVENT_SMTP_IMF_RESENT_MSG_ID. */
    PACE2_ADVANCED_SMTP_IMF_MIME_VERSION,                 /**< @ref IPD_EVENT_SMTP_IMF_MIME_VERSION. */
    PACE2_ADVANCED_SMTP_IMF_OTHER,                        /**< @ref IPD_EVENT_SMTP_IMF_OTHER. */
    PACE2_ADVANCED_SMTP_IMF_HEADER,                       /**< @ref IPD_EVENT_SMTP_IMF_HEADER. */
    PACE2_ADVANCED_SMTP_IMF_CONTENT_TYPE,                 /**< @ref IPD_EVENT_SMTP_IMF_CONTENT_TYPE. */
    PACE2_ADVANCED_SMTP_IMF_CONTENT_TRANSFER_ENCODING,    /**< @ref IPD_EVENT_SMTP_IMF_CONTENT_TRANSFER_ENCODING. */
    PACE2_ADVANCED_SMTP_IMF_CONTENT_DISPOSITION,          /**< @ref IPD_EVENT_SMTP_IMF_CONTENT_DISPOSITION. */
    PACE2_ADVANCED_SMTP_IMF_PART_HEADER,                  /**< @ref IPD_EVENT_SMTP_IMF_PART_HEADER. */
    PACE2_ADVANCED_SMTP_IMF_DATA_BEGIN,                   /**< @ref IPD_EVENT_SMTP_IMF_DATA_BEGIN. */
    PACE2_ADVANCED_SMTP_IMF_DATA,                         /**< @ref IPD_EVENT_SMTP_IMF_DATA. */
    PACE2_ADVANCED_SMTP_IMF_DATA_END,                     /**< @ref IPD_EVENT_SMTP_IMF_DATA_END. */
    PACE2_ADVANCED_SMTP_IMF_DONE,                         /**< @ref IPD_EVENT_SMTP_IMF_DONE. */
    PACE2_ADVANCED_SMTP_IMF_RETURN_PATH,                  /**< @ref IPD_EVENT_SMTP_IMF_RETURN_PATH. */
    PACE2_ADVANCED_SMTP_IMF_RECEIVED,                     /**< @ref IPD_EVENT_SMTP_IMF_RECEIVED. */

    PACE2_NUMBER_OF_ADVANCED_SMTP_EVENT_TYPES             /**< Number of implemented event types. */
} PACE2_advanced_smtp_event_type;

/* Event Structures *************************************************************/

#ifndef PACE2_DISABLE_DECODER

/**
 * @brief Data structure for advanced SMTP events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_ADVANCED_SMTP_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_advanced_smtp_event_type meta_data_type;      /**< SMTP event subtype. */
    PACE2_ADVANCED_META_DATA_EVENT_EXTRA_FIELDS;
    union {
        int client_direction;                                      /**< Contains data for a @ref PACE2_ADVANCED_SMTP_CLIENT_DIRECTION event. */
        struct ipd_charset_string server_greeting;                 /**< Contains data for a @ref PACE2_ADVANCED_SMTP_SERVER_GREETING event. */
        const char * invalid;                                      /**< Contains data for a @ref PACE2_ADVANCED_SMTP_INVALID event. */
        struct ipd_charset_string ehlo;                            /**< Contains data for a @ref PACE2_ADVANCED_SMTP_EHLO event. */
        struct ipd_charset_string user;                            /**< Contains data for a @ref PACE2_ADVANCED_SMTP_USER event. */
        struct ipd_charset_string pass;                            /**< Contains data for a @ref PACE2_ADVANCED_SMTP_PASS event. */
        struct ipd_charset_string mail_from;                       /**< Contains data for a @ref PACE2_ADVANCED_SMTP_MAIL_FROM event. */
        u64 mail_from_size;                                        /**< Contains data for a @ref PACE2_ADVANCED_SMTP_MAIL_FROM_SIZE event. */
        struct ipd_charset_string rcpt_to;                         /**< Contains data for a @ref PACE2_ADVANCED_SMTP_RCPT_TO event. */
        struct ipd_smtp_reply server_reply;                        /**< Contains data for a @ref PACE2_ADVANCED_SMTP_SERVER_REPLY event. */
        struct ipd_imf_address imf_from;                           /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_FROM event. */
        struct ipd_imf_address imf_to;                             /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_TO event. */
        struct ipd_imf_address imf_cc;                             /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_CC event. */
        struct ipd_imf_address imf_bcc;                            /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_BCC event. */
        struct ipd_charset_string imf_subject;                     /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_SUBJECT event. */
        struct ipd_charset_string imf_date;                        /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_DATE event. */
        struct ipd_imf_address imf_sender;                         /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_SENDER event. */
        struct ipd_imf_address imf_reply_to;                       /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_REPLY_TO event. */
        struct ipd_charset_string imf_message_id;                  /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_MESSAGE_ID event. */
        struct ipd_charset_string imf_in_reply_to;                 /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_IN_REPLY_TO event. */
        struct ipd_charset_string imf_references;                  /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_REFERENCES event. */
        struct ipd_charset_string imf_comments;                    /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_COMMENTS event. */
        struct ipd_charset_string imf_keywords;                    /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_KEYWORDS event. */
        struct ipd_charset_string imf_trace;                       /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_TRACE event. */
        struct ipd_charset_string imf_resent_date;                 /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_RESENT_DATE event. */
        struct ipd_imf_address imf_resent_from;                    /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_RESENT_FROM event. */
        struct ipd_imf_address imf_resent_sender;                  /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_RESENT_SENDER event. */
        struct ipd_imf_address imf_resent_to;                      /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_RESENT_TO event. */
        struct ipd_imf_address imf_resent_cc;                      /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_RESENT_CC event. */
        struct ipd_imf_address imf_resent_bcc;                     /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_RESENT_BCC event. */
        struct ipd_charset_string imf_resent_msg_id;               /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_RESENT_MSG_ID event. */
        struct ipd_charset_string imf_mime_version;                /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_MIME_VERSION event. */
        struct ipd_imf_part_data imf_other;                        /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_OTHER event. */
        struct ipd_charset_string imf_header;                      /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_HEADER event. */
        struct ipd_imf_content_type imf_content_type;              /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_CONTENT_TYPE event. */
        struct ipd_imf_part_data imf_content_transfer_encoding;    /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_CONTENT_TRANSFER_ENCODING event. */
        struct ipd_imf_part_data imf_content_disposition;          /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_CONTENT_DISPOSITION event. */
        struct ipd_imf_part_data imf_part_header;                  /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_PART_HEADER event. */
        struct ipd_charset_string imf_data_begin;                  /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_DATA_BEGIN event. */
        struct ipd_imf_part_data  imf_data;                        /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_DATA event. */
        struct ipd_charset_string imf_data_end;                    /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_DATA_END event. */
        struct ipd_charset_string imf_return_path;                 /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_RETURN_PATH event. */
        struct ipd_charset_string imf_received;                    /**< Contains data for a @ref PACE2_ADVANCED_SMTP_IMF_RECEIVED event. */

    } event_data;                                                  /**< Named union which contains the data of the sub-event types. */
} PACE2_advanced_smtp_event;

#endif

#endif /* SMTP_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
