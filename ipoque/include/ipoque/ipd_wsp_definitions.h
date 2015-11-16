/********************************************************************************/
/**
 ** \file       ipd_wsp_definitions.h
 ** \brief      Event definitions for the Wireless Session Protocol.
 **/
/********************************************************************************/

#ifndef __IPOQUE_DECODER_WSP_INCLUDE_FILE__
#define __IPOQUE_DECODER_WSP_INCLUDE_FILE__

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif

#include <time.h>

/** \brief Enumeration of the WSP decoder event types
    \details These are the possible values of the `type` argument of an \ref ipd_decoder_event_callback
    function when the `protocol` is `IPOQUE_PROTOCOL_WAP_WSP` (WSP over UDP) or `IPOQUE_PROTOCOL_WAP_WTP_WSP` (WSP over WTP).
*/
enum ipd_wsp_event_type
{
    IPD_WSP_NEW_CONNECTION,     /* start of a new flow with WSP traffic; payload: struct ipd_5tuple */
    IPD_WSP_PDU_HEADER,         /* header of a PDU (all fields up to Data); payload: struct ipd_wsp_pdu_header */
    IPD_WSP_PDU_DATA,           /* Data field of a PDU; payload: struct ipd_wsp_pdu_data */

    IPD_NUMBER_OF_WSP_EVENTS
};

/** \anchor pdu_types
    \name PDU type values
    As defined in WSPSPEC, table 34 (other values in the range 0x01..0x7f are valid).
    \see ipd_wsp_pdu_header::pdu_type
    @{
*/
#define IPD_WSP_PDU_TYPE_CONNECT 0x01
#define IPD_WSP_PDU_TYPE_CONNECT_REPLY  0x02
#define IPD_WSP_PDU_TYPE_REDIRECT 0x03
#define IPD_WSP_PDU_TYPE_REPLY 0x04
#define IPD_WSP_PDU_TYPE_DISCONNECT 0x05
#define IPD_WSP_PDU_TYPE_PUSH 0x06
#define IPD_WSP_PDU_TYPE_CONFIRMED_PUSH 0x07
#define IPD_WSP_PDU_TYPE_SUSPEND 0x08
#define IPD_WSP_PDU_TYPE_RESUME 0x09

// Get PDUs
#define IPD_WSP_PDU_TYPE_GET 0x40
#define IPD_WSP_PDU_TYPE_OPTIONS 0x41
#define IPD_WSP_PDU_TYPE_HEAD 0x42
#define IPD_WSP_PDU_TYPE_DELETE 0x43
#define IPD_WSP_PDU_TYPE_TRACE 0x44

// Post PDUs
#define IPD_WSP_PDU_TYPE_POST 0x60
#define IPD_WSP_PDU_TYPE_PUT 0x61

/** @} */

/** \brief representation of the non-Data fields of a WSP protocol data unit
    \details Covers only those PDU fields that are used by the Method Invocation facility (WSPSPEC,
    section 8.2.3), except for acknowledgment headers.
*/
struct ipd_wsp_pdu_header {
    /** \brief transaction ID
        \details TID field of the PDU (in connectionless WSP) or WTP TID (in connection-mode WSP)
    */
    u16 tid;

    /** \brief PDU type
        \details Type field of the PDU (the assigned values from the WSP spec are available as a \ref pdu_types "set of defines")
    */
    u8 pdu_type;

    /** \brief Status code
        \details Status field of the PDU (only present in Reply PDUs, set to 0 if not present). Values
        correspond to HTTP status codes; the exact mapping is defined in WSPSPEC, table 36. */
    u8 reply_status;

    /** \brief request URI
        \details Uri field of the PDU (only present in Get and Post PDUs, set to a zero-length string if not present)
    */
    struct ipd_string uri;

    /** \brief type/subtype from the ContentType field of the PDU */
    struct ipd_string content_type;

    /** \brief value of the charset parameter (if present) from the ContentType field of the PDU */
    struct ipd_string content_type_charset;

    /** \brief pointer to an array of header field descriptions */
    const struct ipd_wsp_header_field *headers;
    /** \brief number of elements in #headers */
    u64 number_of_headers;

    /** \brief pointer to an array containing the values of the Content-Encoding header fields, in order of appearance */
    const struct ipd_string *content_encodings;
    /** \brief number of elements in #content_encodings */
    u64 number_of_content_encodings;

    /** \brief value of the Content-Length header field
       \details If this header field is not present, the value ULONG_MAX is used.
    */
    u64 content_length;

    /** \brief First-byte-pos value from the Content-Range header field
       \details If this header field is not present, the value 0 is used.
    */
    u64 first_byte_pos;

    /** \brief Entity-length value from the Content-Range header field
        \details If this header field is not present, or does not specify the entity length, the value ULONG_MAX is used
    */
    u64 entity_length;

    struct ipd_string host;     /**< \brief value of the Host header field */
    struct ipd_string location; /**< \brief value of the Location header field */
    struct ipd_string referer;  /**< \brief value of the Referer header field */
    struct ipd_string transfer_encoding; /**< \brief value of the Transfer-Encoding header field */
    struct ipd_string user_agent;        /**< \brief value of the User-Agent header field */

    /** \brief pointer to an array of cookies
        \details In server-originated messages, this array represents the Set-Cookie headers; in
        client-originated messages, it represents the Cookie headers
    */
    const struct ipd_wsp_cookie *cookies;
    /** \brief number of elements in #cookies */
    u64 number_of_cookies;

    /** \brief flag that is set if the PDU contains a Data field
        \details The Data PDU field will be reported in the IPD_WSP_PDU_DATA events
        that follow.
    */
    u8 has_data;

    /** \brief flag that is set if this PDU is being transmitted from the server to the client */
    u8 from_server;
};

/** \brief Representation of one segment of the Data field of a WSP protocol data unit */
struct ipd_wsp_pdu_data {
    /** \copydoc ipd_wsp_pdu_header::tid */
    u16 tid;

    /** \copydoc ipd_wsp_pdu_header::pdu_type */
    u8 pdu_type;

    /** \brief a segment of the Data field of the PDU
        \details The segments are reported in-order, ie. the Data field of the WSP message with a given
        transaction ID is the concatenation of the #content fields of all IPD_WSP_PDU_DATA events with that
        #tid.
    */
    struct ipd_string content;

    /** \brief flag that is set if more IPD_WSP_PDU_DATA events for this PDU will follow */
    u8 more_data;
};

/** \brief representation of a Cookie or Set-Cookie header field */
struct ipd_wsp_cookie {
    struct ipd_string name;     /**< \brief cookie name */
    struct ipd_string value;    /**< \brief cookie value */

    struct ipd_string domain;   /**< \brief Domain attribute */
    struct ipd_string path;     /**< \brief Path attribute */

    /** \brief cookie lifetime in seconds (Max-Age attribute, Set-Cookie only)
        \details If the Max-Age attribute is not present, the value ULONG_MAX is used
    */
    u64 max_age;

    u8 secure;                  /**< \brief flag that is set when the Secure attribute is present in a Set-Cookie header */
};

/** \brief list of possible representations of a header field value (selects a branch of the ipd_wsp_header_value union) */
enum ipd_wsp_header_value_type {
    IPD_WSP_STRING_VALUE,       /**< \brief string in ipd_wsp_header_value::string */
    /** \brief string that may contain escaped characters in ipd_wsp_header_value::quoted_string
        \details refer to the quoted-string production in RFC 2616 for details
    */
    IPD_WSP_QUOTED_STRING_VALUE,
    IPD_WSP_TIME_VALUE,         /**< \brief Unix timestamp in ipd_wsp_header_value::time */
    IPD_WSP_UINT_VALUE,         /**< \brief unsigned integer in ipd_wsp_header_value::uint */

    /** \brief no "cooked" representation of the field value is available; the raw bytes can be found in
        ipd_wsp_header_field::raw_value
    */
    IPD_WSP_UNTYPED_VALUE
};

/** \brief union of all supported representations of a header field value (an accompanying \ref
    ipd_wsp_header_value_type tag tells which branch is used)
*/
union ipd_wsp_header_value {
    struct ipd_string string;   /**< \brief a string */

    /** \brief a string that may contain escaped characters
     * \details refer to the quoted-string production in RFC 2616 for details */
    struct ipd_string quoted_string;

    time_t time;                /**< \brief a Unix timestamp */
    u64 uint;                   /**< \brief an unsigned integer */
};

/** \brief representation of one header field from a WSP Message */
struct ipd_wsp_header_field {
    /** \brief numeric code for the header field name
        \details Refer to WSPSPEC, table 39 for a list of code assignments for "well-known field names".
        The special value 0xFF is used by PADE to indicate that the field name was not numerically coded, but
        sent as a string (which can be found in #name_as_string)
    */
    u8 name_as_code;

    /** \brief header field name
        \details This string will always be defined. For well-known headers (where the field name is not
        transmitted as a string over the network), PADE provides a value by looking up #name_as_code in an
        internal table.
    */
    struct ipd_string name_as_string;

    struct ipd_string raw_value; /**< \brief header field value as an uninterpreted byte string */

    enum ipd_wsp_header_value_type value_type; /**< \brief type tag that indicates which branch of the #value field is used */
    union ipd_wsp_header_value value;          /**< \brief "cooked" (i.e. typed) representation of the header field value */
};

#endif /* __IPOQUE_DECODER_WSP_INCLUDE_FILE__ */
