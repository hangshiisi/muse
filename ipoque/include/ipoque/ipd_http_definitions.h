/********************************************************************************/
/**
 ** \file       ipd_http_definitions.h
 ** \brief      Structures and enumerations for all events of the HTTP Protocol.
 **/
/********************************************************************************/



/* decoder output for http */

#ifndef __IPOQUE_DECODER_HTTP_INCLUDE_FILE__
#define __IPOQUE_DECODER_HTTP_INCLUDE_FILE__

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif

/**
 * Enumeration for simple http events. This is passed as \c type to the \ref ipd_decoder_event_callback.
 */

enum ipd_simple_event_http_enumeration
{
    /* all values (except marked ones) return struct ipd_charset_string */

	/** Provides a struct ipd_5tuple with information of the 5-tuple describing the transport-layer connection */
    IPD_EVENT_HTTP_5TUPLE,		      /* struct ipd_5tuple */

    /* request data */
    /** The entire request header, including the request-line. */
    IPD_EVENT_HTTP_REQUEST_HEADER,
    /** The method string of the HTTP request like "GET" or "POST". */
    IPD_EVENT_HTTP_REQUEST_METHOD,
    /** The path of the requested file on the server like "/stuff/index.html". */
    IPD_EVENT_HTTP_REQUEST_PATH,
    /** The version string of the HTTP request like "HTTP/1.1". */
    IPD_EVENT_HTTP_REQUEST_VERSION,
    /** The host-name of the HTTP server that the request is sent to like "www.notreallythere.net"; \c data points to a */
    IPD_EVENT_HTTP_REQUEST_HOST, /**< struct ipd_http_header_field. */
    /** The useragent string of the program sending the HTTP request like "Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9.2.2pre) Gecko/20100130 Ubuntu/9.10 (karmic) Namoroka/3.6.2pre"; \c data points to a */
    IPD_EVENT_HTTP_REQUEST_USERAGENT, /**< struct ipd_http_header_field. */
    /** The referrer string that i.e. is set by web browsers to the http page that the request originated from like "http://www.notreallythere.net/"; \c data points to a */
    IPD_EVENT_HTTP_REQUEST_REFERER, /**< struct ipd_http_header_field. */
    /** The string describing the requested content type like "text/html"; \c data points to a */
    IPD_EVENT_HTTP_REQUEST_CONTENTTYPE, /**< struct ipd_http_header_field. */
    /** The cookie(s) sent with the request; \c data points to a */
    IPD_EVENT_HTTP_REQUEST_COOKIE, /**< struct ipd_http_header_field. */
    /** A string describing the requested range if only a part of the requested file should be transfered; \c data points to a */
    IPD_EVENT_HTTP_REQUEST_RANGE, /**< struct ipd_http_header_field. */
    /** The length of the request data as a string; \c data points to a */
    IPD_EVENT_HTTP_REQUEST_CONTENT_LENGTH, /**< struct ipd_http_header_field. */
    /** This event is issued for all HTTP request header lines that no special events exist for. The string contains the complete header line like "Connection: keep-alive". */
    IPD_EVENT_HTTP_REQUEST_UNKNOWN,
    /** This event is issued for each decoded piece of HTTP request payload data. */
    IPD_EVENT_HTTP_REQUEST_PAYLOAD,
    /** This event indicates that the decoding of the HTTP request completed. It does not provide any data. */
    IPD_EVENT_HTTP_REQUEST_DONE,        /* no data */

    /* response data */
    /** The entire response header, including the status-line. */
    IPD_EVENT_HTTP_RESPONSE_HEADER,
    /** The version string of the HTTP response like "HTTP/1.1". */
    IPD_EVENT_HTTP_RESPONSE_VERSION,
    /** The HTTP response code as a string like "200". */
    IPD_EVENT_HTTP_RESPONSE_CODE,
    /** The HTTP response reason phrase string like "OK". */
    IPD_EVENT_HTTP_RESPONSE_REASON_PHRASE,
    /** The length of the response data as a string; \c data points to a */
    IPD_EVENT_HTTP_RESPONSE_CONTENT_LENGTH, /**< struct ipd_http_header_field. */
    /** A string describing the range inside the requested document that is actually delivered with the HTTP response; \c data points to a */
    IPD_EVENT_HTTP_RESPONSE_CONTENT_RANGE, /**< struct ipd_http_header_field. */
    /** The content type of the response data like "image/gif"; \c data points to a */
    IPD_EVENT_HTTP_RESPONSE_CONTENTTYPE, /**< struct ipd_http_header_field. */
    /** The encoding of the actually transmitted response data like "gzip"; \c data points to a */
    IPD_EVENT_HTTP_RESPONSE_CONTENT_ENCODING, /**< struct ipd_http_header_field. */
    /** The transfer encoding of the actually transmitted response data like "chunked"; \c data points to a */
    IPD_EVENT_HTTP_RESPONSE_TRANSFER_ENCODING, /**< struct ipd_http_header_field. */
    /** The connection type sent with the HTTP response like "keep-alive"; \c data points to a */
    IPD_EVENT_HTTP_RESPONSE_CONNECTION, /**< struct ipd_http_header_field. */
    /** A string with cookie(s) to be set with the HTTP response; \c data points to a */
    IPD_EVENT_HTTP_RESPONSE_SET_COOKIE, /**< struct ipd_http_header_field. */
    /** The new location of the requested document if it was moved permanently or temporarily (response codes 3xx) like "http://www.notreallythere.net/new/index.html"; \c data points to a */
    IPD_EVENT_HTTP_RESPONSE_LOCATION, /**< struct ipd_http_header_field. */
    /** This event is issued for all HTTP response header lines that no special events exist for. The string contains the complete header line like "Server: Apache-Coyote/1.1". */
    IPD_EVENT_HTTP_RESPONSE_UNKNOWN,
    /** This event is issued for each decoded piece of HTTP response payload data. */
    IPD_EVENT_HTTP_RESPONSE_PAYLOAD,
    /** This event indicates that the decoding of the HTTP response completed.  It does not provide any data.*/
    IPD_EVENT_HTTP_RESPONSE_DONE,       /* no data */

    /* end of the flow */
    /** This event indicates that the decoding of the HTTP connection cannot be continued. It provides a const char * to a message describing the failure reason. */
    IPD_EVENT_HTTP_INVALID,     /* const char * */
    /** This event indicates that the HTTP connection ended. It does not provide any data. */
    IPD_EVENT_HTTP_END_OF_FLOW, /* no data */

    /* interaction with website decoders */
    /** This event is sent to indicate that none of the currently configured HTTP-postprocessing decoders needs this flow. */
    IPD_EVENT_HTTP_NO_POSTPROC,

    IPD_NUMBER_OF_HTTP_EVENTS,
};

/** structure describing an HTTP header field */
struct ipd_http_header_field {
    struct ipd_charset_string value;        /**< the field-value (everything after the first ':', with leading whitespace removed) */
    struct ipd_charset_string entire_field; /**< complete header line */
};

#endif                          /* __IPOQUE_DECODER_HTTP_INCLUDE_FILE__ */
