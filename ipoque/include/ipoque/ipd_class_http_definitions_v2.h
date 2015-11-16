/********************************************************************************/
/**
 ** \file       ipd_class_http_definitions_v2.h
 ** \brief      Structures and enumerations for all events of class http in PACE2.
 **/
/********************************************************************************/

#ifndef IPD_CLASS_HTTP_DEFINITIONS_V2_H_
#define IPD_CLASS_HTTP_DEFINITIONS_V2_H_

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif

enum ipd_http_class_struct_enum
{

    IPD_HTTP_CLASS_SESSION,                             /**< struct ipd_class_http_session_struct * */

    IPD_HTTP_CLASS_TRANSACTION,                         /**< struct ipd_class_http_transaction_struct * */

    IPD_HTTP_CLASS_REQUEST_DATA_TRANSFER,               /**< struct ipd_class_http_transfer_payload_struct * */

    IPD_HTTP_CLASS_RESPONSE_DATA_TRANSFER,              /**< struct ipd_class_http_transfer_payload_struct * */

    IPD_HTTP_CLASS_TRANSACTION_DONE,                    /**< struct ipd_class_http_transaction_struct * */

    IPD_HTTP_CLASS_SESSION_DONE,                        /**< struct ipd_class_http_session_struct * */


    IPD_NUMBER_OF_HTTP_CLASS_EVENTS,
};
/** Main HTTP session structure, each HTTP connection session has this event as initial event.
 */
struct ipd_class_http_session_struct
{
    u64 http_session_id;                                     /**< id of the session */
    struct ipd_5tuple flow_tuple;                       /**< ip address and port for client and server */

    u64 connection_id;                                  /**< connection id of the used connection */
};


/**
 * Event for each HTTP request-response pair.
 * This event might be flushed multiple times in the future when HUGE POSTs happens.
 */
struct ipd_class_http_transaction_struct
{

    u64 http_transaction_id;                                         /**< id of the transaction */
    u64 http_session_id;                                        /**< id of the ipd_class_http_session the transaction belongs to */

    enum ipd_http_class_transaction_state_enum state;           /**< the current state of the transaction */

    struct ipd_5tuple flow_tuple;                               /**< ip address and port for client and server */

    struct ipd_charset_string request_method;                   /**< string of used method like "GET, POST,..." */

    struct ipd_charset_string request_path;                     /**< string of used url like "/index.html" */

    struct ipd_charset_string request_version;                  /**< string of request HTTP version like "HTTP/1.0" */

    struct ipd_charset_string request_host;                     /**< string of used host like "www.twitter.com" */

    struct ipd_charset_string request_useragent;                /**< string of used user agent like "Mozilla/5.0 (X11; U; Linux i686; de; rv:1.8.1.14)" */

    struct ipd_charset_string request_referrer;                 /**< string of used referrer like "www.facebook.com/dummy.html" */

    struct ipd_charset_string request_contenttype;              /**< string of used content type like "application/xml" */

    struct ipd_charset_string request_cookie;                   /**< string of cookie */

    struct ipd_charset_string request_range;                    /**< string of the requested range */

    struct ipd_charset_string request_content_length;           /**< string of request content length sent to the HTTP server */

    u64 request_other_lines;                                    /**< number of other lines in the request_other array */
    struct ipd_charset_string *request_other;                   /**< array of "other" lines like "Accept-Encoding: gzip,deflate" */

    struct ipd_charset_string response_version;                 /**< string of response HTTP version like "HTTP/1.0" */

    struct ipd_charset_string response_code;                    /**< string of response code number returned from the HTTP server like "200" */

    struct ipd_charset_string response_reason_phrase;           /**< response reason phrase returned from the HTTP server like "OK" */

    struct ipd_charset_string response_content_length;          /**< string of response content length returned from the HTTP server */

    struct ipd_charset_string response_content_range;           /**< string of the content range returned from the HTTP server */

    struct ipd_charset_string response_contenttype;             /**< response content type like "application/xml" */

    u64 response_content_encoding_array_len;
    struct ipd_charset_string *response_content_encoding;       /**< response content encoding like "gzip" */

    struct ipd_charset_string response_transfer_encoding;       /**< response transfer encoding like "chunked" */

    struct ipd_charset_string response_connection;              /**< response connection like "close" */

    u64 response_set_cookie_array_len;
    struct ipd_charset_string *response_set_cookie;             /**< response Set-Cookie header */

    struct ipd_charset_string response_location;                /**< response location for a http redirect */

    u64 response_other_lines;                                   /**< number of other lines in the response_other array */
    struct ipd_charset_string *response_other;                  /**< array of "other" lines like "Date: Wed, 07 May 2008 13:21:41 GMT" */
};

/** events for each http request - response pair
 */
struct ipd_class_http_transfer_payload_struct
{

    u64 http_transaction_id;                                    /**< id of the ipd_class_http_transaction it belongs to */

    u64 http_session_id;                                        /**< id of the ipd_class_http_session it belongs to */

    u64 data_offset;                                            /**< offset of the data in the downloaded data.*/

    struct ipd_charset_string data;                             /**< data with encoding */

    u8 payload_done;                                            /**< is !=0 in the final segment of a request or response payload */
};

typedef struct ipd_class_http_transfer_payload_struct ipd_class_http_transfer_payload_int_t;
typedef struct ipd_class_http_transaction_struct ipd_class_http_transaction_int_t;
typedef struct ipd_class_http_session_struct ipd_class_http_session_int_t;

#endif /* IPD_CLASS_HTTP_DEFINITIONS_V2_H_ */

