/********************************************************************************/
/**
 ** \file       http_events.h
 ** \brief      HTTP event definitions
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef HTTP_EVENTS_H
#define HTTP_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the basic HTTP request event.
 */
#define PACE2_BASIC_HTTP_REQUEST_EVENT_GROUP PACE2_BASIC_PROTOCOL_META_DATA_GROUP

/**
 * @brief Public define for the assigned meta data group of the basic HTTP response event.
 */
#define PACE2_BASIC_HTTP_RESPONSE_EVENT_GROUP PACE2_BASIC_PROTOCOL_META_DATA_GROUP

/**
 * @brief Public define for the assigned meta data group of the advanced HTTP event.
 */
#define PACE2_ADVANCED_HTTP_EVENT_GROUP PACE2_ADVANCED_PROTOCOL_META_DATA_GROUP

/**
 * @brief Public define for the assigned meta data group of the class HTTP event.
 */
#define PACE2_CLASS_HTTP_EVENT_GROUP PACE2_CLASS_PROTOCOL_META_DATA_GROUP

/* Event Types ******************************************************************/

/**
 * @brief Types for advanced HTTP events.
 */
typedef enum {
    PACE2_ADVANCED_HTTP_5TUPLE,                       /**< @ref IPD_EVENT_HTTP_REQUEST_HEADER */

    /// request data
    PACE2_ADVANCED_HTTP_REQUEST_HEADER,               /**< @ref IPD_EVENT_HTTP_REQUEST_HEADER */
    PACE2_ADVANCED_HTTP_REQUEST_METHOD,               /**< @ref IPD_EVENT_HTTP_REQUEST_METHOD */
    PACE2_ADVANCED_HTTP_REQUEST_PATH,                 /**< @ref IPD_EVENT_HTTP_REQUEST_PATH */
    PACE2_ADVANCED_HTTP_REQUEST_VERSION,              /**< @ref IPD_EVENT_HTTP_REQUEST_VERSION */
    PACE2_ADVANCED_HTTP_REQUEST_HOST,                 /**< @ref IPD_EVENT_HTTP_REQUEST_HOST */
    PACE2_ADVANCED_HTTP_REQUEST_USERAGENT,            /**< @ref IPD_EVENT_HTTP_REQUEST_USERAGENT */
    PACE2_ADVANCED_HTTP_REQUEST_REFERER,              /**< @ref IPD_EVENT_HTTP_REQUEST_REFERER */
    PACE2_ADVANCED_HTTP_REQUEST_CONTENTTYPE,          /**< @ref IPD_EVENT_HTTP_REQUEST_CONTENTTYPE */
    PACE2_ADVANCED_HTTP_REQUEST_COOKIE,               /**< @ref IPD_EVENT_HTTP_REQUEST_COOKIE */
    PACE2_ADVANCED_HTTP_REQUEST_RANGE,                /**< @ref IPD_EVENT_HTTP_REQUEST_RANGE */
    PACE2_ADVANCED_HTTP_REQUEST_CONTENT_LENGTH,       /**< @ref IPD_EVENT_HTTP_REQUEST_CONTENT_LENGTH */
    PACE2_ADVANCED_HTTP_REQUEST_UNKNOWN,              /**< @ref IPD_EVENT_HTTP_REQUEST_UNKNOWN */
    PACE2_ADVANCED_HTTP_REQUEST_PAYLOAD,              /**< @ref IPD_EVENT_HTTP_REQUEST_PAYLOAD */
    PACE2_ADVANCED_HTTP_REQUEST_DONE,                 /**< @ref IPD_EVENT_HTTP_REQUEST_DONE */

    /// response data
    PACE2_ADVANCED_HTTP_RESPONSE_HEADER,              /**< @ref IPD_EVENT_HTTP_RESPONSE_HEADER */
    PACE2_ADVANCED_HTTP_RESPONSE_VERSION,             /**< @ref IPD_EVENT_HTTP_RESPONSE_VERSION */
    PACE2_ADVANCED_HTTP_RESPONSE_CODE,                /**< @ref IPD_EVENT_HTTP_RESPONSE_CODE */
    PACE2_ADVANCED_HTTP_RESPONSE_REASON_PHRASE,       /**< @ref IPD_EVENT_HTTP_RESPONSE_REASON_PHRASE */
    PACE2_ADVANCED_HTTP_RESPONSE_CONTENT_LENGTH,      /**< @ref IPD_EVENT_HTTP_RESPONSE_CONTENT_LENGTH */
    PACE2_ADVANCED_HTTP_RESPONSE_CONTENT_RANGE,       /**< @ref IPD_EVENT_HTTP_RESPONSE_CONTENT_RANGE */
    PACE2_ADVANCED_HTTP_RESPONSE_CONTENTTYPE,         /**< @ref IPD_EVENT_HTTP_RESPONSE_CONTENTTYPE */
    PACE2_ADVANCED_HTTP_RESPONSE_CONTENT_ENCODING,    /**< @ref IPD_EVENT_HTTP_RESPONSE_CONTENT_ENCODING */
    PACE2_ADVANCED_HTTP_RESPONSE_TRANSFER_ENCODING,   /**< @ref IPD_EVENT_HTTP_RESPONSE_TRANSFER_ENCODING */
    PACE2_ADVANCED_HTTP_RESPONSE_CONNECTION,          /**< @ref IPD_EVENT_HTTP_RESPONSE_CONNECTION */
    PACE2_ADVANCED_HTTP_RESPONSE_SET_COOKIE,          /**< @ref IPD_EVENT_HTTP_RESPONSE_SET_COOKIE */
    PACE2_ADVANCED_HTTP_RESPONSE_LOCATION,            /**< @ref IPD_EVENT_HTTP_RESPONSE_LOCATION */
    PACE2_ADVANCED_HTTP_RESPONSE_UNKNOWN,             /**< @ref IPD_EVENT_HTTP_RESPONSE_UNKNOWN */
    PACE2_ADVANCED_HTTP_RESPONSE_PAYLOAD,             /**< @ref IPD_EVENT_HTTP_RESPONSE_PAYLOAD */
    PACE2_ADVANCED_HTTP_RESPONSE_DONE,                /**< @ref IPD_EVENT_HTTP_RESPONSE_DONE */

    /// end of the flow
    PACE2_ADVANCED_HTTP_INVALID,                      /**< @ref IPD_EVENT_HTTP_INVALID */
    PACE2_ADVANCED_HTTP_END_OF_FLOW,                  /**< @ref IPD_EVENT_HTTP_END_OF_FLOW */

    PACE2_ADVANCED_HTTP_NO_POSTPROC,                  /**< @ref IPD_EVENT_HTTP_NO_POSTPROC */

    PACE2_NUMBER_OF_ADVANCED_HTTP_EVENT_TYPES         /**< Number of implemented event types. */
} PACE2_advanced_HTTP_event_type;

/**
 * @brief Types for HTTP class events.
 */
typedef enum {
    PACE2_CLASS_HTTP_SESSION,                      /**< @ref IPD_HTTP_CLASS_SESSION */
    PACE2_CLASS_HTTP_TRANSACTION,                  /**< @ref IPD_HTTP_CLASS_TRANSACTION */
    PACE2_CLASS_HTTP_REQUEST_DATA_TRANSFER,        /**< @ref IPD_HTTP_CLASS_REQUEST_DATA_TRANSFER */
    PACE2_CLASS_HTTP_RESPONSE_DATA_TRANSFER,       /**< @ref IPD_HTTP_CLASS_RESPONSE_DATA_TRANSFER */
    PACE2_CLASS_HTTP_TRANSACTION_DONE,             /**< @ref IPD_HTTP_CLASS_TRANSACTION_DONE */
    PACE2_CLASS_HTTP_SESSION_DONE,                 /**< @ref IPD_HTTP_CLASS_SESSION_DONE */

    PACE2_NUMBER_OF_CLASS_HTTP_EVENT_TYPES         /**< Number of implemented event types. */
} PACE2_class_HTTP_event_type;

/**
 * @brief Meta data flags of basic HTTP request events.
 */
typedef enum {
    PACE2_HTTP_REQUEST_METHOD = 0,      /**< Request method part. */
    PACE2_HTTP_REQUEST_URI,             /**< Request URI part. */
    PACE2_HTTP_HOST,                    /**< Request host line. */
    PACE2_HTTP_USER_AGENT,              /**< Request user-agent line. */
    PACE2_HTTP_REFERER,                 /**< Request referer line. */
    PACE2_HTTP_CONTENT_TYPE,            /**< Request content type line. */
    PACE2_HTTP_CONTENT_LENGTH,          /**< Request content length line. */
    PACE2_HTTP_ACCEPT,                  /**< Request accept line. */
    PACE2_HTTP_ORIGIN,                  /**< Request origin line. */
    PACE2_HTTP_COOKIE,                  /**< Request cookie line. */
    PACE2_HTTP_SOAP_ACTION,             /**< Request soap action line. */
    PACE2_HTTP_X_FORWARDED_FOR,         /**< Request x-forwarded-for line. */
    PACE2_HTTP_X_SESSION_TYPE,          /**< Request x-session-type line. */
    PACE2_HTTP_X_STREAM_TYPE,           /**< Request x-stream-type line. */
    PACE2_HTTP_X_ONLINE_HOST,           /**< Request x-online-host line. */

    PACE2_NUMBER_OF_HTTP_REQUEST_FLAGS  /**< Number of implemented HTTP request line flags. */
} PACE2_basic_HTTP_request_line;

/**
 * @brief Meta data flags of basic HTTP response events.
 */
typedef enum {
    PACE2_HTTP_SERVER_RESPONSE = 0,     /**< Server response line. */
    PACE2_HTTP_SERVER_CONTENT_TYPE,     /**< Server response content type line. */
    PACE2_HTTP_SERVER_CONTENT_ENCODING, /**< Server response content encoding line. */
    PACE2_HTTP_SERVER_CONTENT_LENGTH,   /**< Server response content length line. */
    PACE2_HTTP_TRANSFER_ENCODING,       /**< Server response transfer encoding line. */
    PACE2_HTTP_SERVER,                  /**< Server response server line. */
    PACE2_HTTP_SET_COOKIE_LINE,         /**< Server response set-cookie line. */

    PACE2_NUMBER_OF_HTTP_RESPONSE_FLAGS /**< Number of implemented HTTP response line flags. */
} PACE2_basic_HTTP_response_line;

/* Event Structures *************************************************************/

/**
 * @brief Data structure of a basic HTTP request meta data event.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_BASIC_HTTP_REQUEST_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_bitmask meta_data_mask;               /**< Bitmask, which states the available HTTP request meta data. */
    struct {
        PACE2_basic_HTTP_request_line type;     /**< Request line of type @ref PACE2_basic_HTTP_request_line.*/
        PACE2_byte_buffer content;              /**< Request line content. */
    } line[PACE2_NUMBER_OF_HTTP_REQUEST_FLAGS]; /**< Data structure for a single HTTP request header line.
                                                     Contains content for each available header line of type @ref PACE2_basic_HTTP_request_line */
} PACE2_basic_HTTP_request_event;

/**
 * @brief Data structure of a basic HTTP response meta data event.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_BASIC_HTTP_RESPONSE_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_bitmask meta_data_mask;               /**< Bitmask, which states the available HTTP response meta data. */
    struct {
        PACE2_basic_HTTP_response_line type;    /**< Response line of type @ref PACE2_basic_HTTP_response_line.*/
        PACE2_byte_buffer content;              /**< Response line content. */
    } line[PACE2_NUMBER_OF_HTTP_RESPONSE_FLAGS];/**< Data structure for a single HTTP response header.
                                                     Contains content for each available header line of type @ref PACE2_basic_HTTP_response_line */
} PACE2_basic_HTTP_response_event;

#ifndef PACE2_DISABLE_DECODER
/**
 * @brief Data structure for advanced HTTP events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_ADVANCED_HTTP_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_advanced_HTTP_event_type meta_data_type;  /**< HTTP event subtype. */
    PACE2_ADVANCED_META_DATA_EVENT_EXTRA_FIELDS;
    union {
        struct ipd_5tuple tuple;                                    /**< Contains data for a @ref PACE2_ADVANCED_HTTP_5TUPLE event. */
        struct ipd_charset_string request_header;                   /**< Contains data for a @ref PACE2_ADVANCED_HTTP_REQUEST_HEADER event. */
        struct ipd_charset_string request_method;                   /**< Contains data for a @ref PACE2_ADVANCED_HTTP_REQUEST_METHOD event. */
        struct ipd_charset_string request_path;                     /**< Contains data for a @ref PACE2_ADVANCED_HTTP_REQUEST_PATH event. */
        struct ipd_charset_string request_version;                  /**< Contains data for a @ref PACE2_ADVANCED_HTTP_REQUEST_VERSION event. */
        struct ipd_http_header_field request_host;                  /**< Contains data for a @ref PACE2_ADVANCED_HTTP_REQUEST_HOST event. */
        struct ipd_http_header_field request_useragent;             /**< Contains data for a @ref PACE2_ADVANCED_HTTP_REQUEST_USERAGENT event. */
        struct ipd_http_header_field request_referer;               /**< Contains data for a @ref PACE2_ADVANCED_HTTP_REQUEST_REFERER event. */
        struct ipd_http_header_field request_contenttype;           /**< Contains data for a @ref PACE2_ADVANCED_HTTP_REQUEST_CONTENTTYPE event. */
        struct ipd_http_header_field request_cookie;                /**< Contains data for a @ref PACE2_ADVANCED_HTTP_REQUEST_COOKIE event. */
        struct ipd_http_header_field request_range;                 /**< Contains data for a @ref PACE2_ADVANCED_HTTP_REQUEST_RANGE event. */
        struct ipd_http_header_field request_content_length;        /**< Contains data for a @ref PACE2_ADVANCED_HTTP_REQUEST_CONTENT_LENGTH event. */
        struct ipd_charset_string request_unknown;                  /**< Contains data for a @ref PACE2_ADVANCED_HTTP_REQUEST_UNKNOWN event. */
        struct ipd_charset_string request_payload;                  /**< Contains data for a @ref PACE2_ADVANCED_HTTP_REQUEST_PAYLOAD event. */
        struct ipd_charset_string response_header;                  /**< Contains data for a @ref PACE2_ADVANCED_HTTP_RESPONSE_HEADER event. */
        struct ipd_charset_string response_version;                 /**< Contains data for a @ref PACE2_ADVANCED_HTTP_RESPONSE_VERSION event. */
        struct ipd_charset_string response_code;                    /**< Contains data for a @ref PACE2_ADVANCED_HTTP_RESPONSE_CODE event. */
        struct ipd_charset_string response_reason_phrase;           /**< Contains data for a @ref PACE2_ADVANCED_HTTP_RESPONSE_REASON_PHRASE event. */
        struct ipd_http_header_field response_content_length;       /**< Contains data for a @ref PACE2_ADVANCED_HTTP_RESPONSE_CONTENT_LENGTH event. */
        struct ipd_http_header_field response_content_range;        /**< Contains data for a @ref PACE2_ADVANCED_HTTP_RESPONSE_CONTENT_RANGE event. */
        struct ipd_http_header_field response_contenttype;          /**< Contains data for a @ref PACE2_ADVANCED_HTTP_RESPONSE_CONTENTTYPE event. */
        struct ipd_http_header_field response_content_encoding;     /**< Contains data for a @ref PACE2_ADVANCED_HTTP_RESPONSE_CONTENT_ENCODING event. */
        struct ipd_http_header_field response_transfer_encoding;    /**< Contains data for a @ref PACE2_ADVANCED_HTTP_RESPONSE_TRANSFER_ENCODING event. */
        struct ipd_http_header_field response_connection;           /**< Contains data for a @ref PACE2_ADVANCED_HTTP_RESPONSE_CONNECTION event. */
        struct ipd_http_header_field response_set_cookie;           /**< Contains data for a @ref PACE2_ADVANCED_HTTP_RESPONSE_SET_COOKIE event. */
        struct ipd_http_header_field response_location;             /**< Contains data for a @ref PACE2_ADVANCED_HTTP_RESPONSE_LOCATION event. */
        struct ipd_charset_string response_unknown;                 /**< Contains data for a @ref PACE2_ADVANCED_HTTP_RESPONSE_UNKNOWN event. */
        struct ipd_charset_string response_payload;                 /**< Contains data for a @ref PACE2_ADVANCED_HTTP_RESPONSE_PAYLOAD event. */
        const char *invalid;                                        /**< Contains data for a @ref PACE2_ADVANCED_HTTP_INVALID event. */
    } event_data;                                   /**< Named union which contains the data of the sub-event types. */
} PACE2_advanced_HTTP_event;

/**
 * @brief Data structure for HTTP class events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_CLASS_HTTP_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_class_HTTP_event_type meta_data_type;     /**< HTTP event subtype. */
    PACE2_CLASS_META_DATA_EVENT_EXTRA_FIELDS;
    union {
        struct ipd_class_http_session_struct session;                           /**< Contains data for a @ref PACE2_CLASS_HTTP_SESSION event. */
        struct ipd_class_http_transaction_struct transaction;                   /**< Contains data for a @ref PACE2_CLASS_HTTP_TRANSACTION event. */
        struct ipd_class_http_transfer_payload_struct request_data_transfer;    /**< Contains data for a @ref PACE2_CLASS_HTTP_REQUEST_DATA_TRANSFER event. */
        struct ipd_class_http_transfer_payload_struct response_data_transfer;   /**< Contains data for a @ref PACE2_CLASS_HTTP_RESPONSE_DATA_TRANSFER event. */
        struct ipd_class_http_transaction_struct transaction_done;              /**< Contains data for a @ref PACE2_CLASS_HTTP_TRANSACTION_DONE event. */
        struct ipd_class_http_session_struct session_done;                      /**< Contains data for a @ref PACE2_CLASS_HTTP_SESSION_DONE event. */
    } event_data;                                   /**< Named union which contains the data of the sub-event types. */
} PACE2_class_HTTP_event;
#endif

#endif /* HTTP_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
