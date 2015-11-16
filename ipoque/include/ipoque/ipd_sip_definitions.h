/********************************************************************************/
/**
 ** \file       ipd_sip_definitions.h
 ** \brief      Structures and enumerations for all events of the SIP Protocol.
 **/
/********************************************************************************/

#ifndef __IPOQUE_DECODER_SIP_INCLUDE_FILE__
#define __IPOQUE_DECODER_SIP_INCLUDE_FILE__

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif

/** fields of a SIP From: oder To: header */
struct ipd_sip_contact_param {
    struct ipd_charset_string header_value; /**< entire value of the header line, eg. "Bob <sip:bob@biloxi.com>;tag=a6c85cf"*/
    struct ipd_charset_string display_name; /**< display name, eg. "Bob" */
    struct ipd_charset_string uri;          /**< URI, eg. "sip:bob@biloxi.com" */
    struct ipd_charset_string tag;          /**< tag, eg. "a6c85cf" */
};

/** fields of a SIP request-line */
struct ipd_sip_request_line {
    struct ipd_charset_string method; /**< request method (eg, REGISTER, INVITE, BYE) */
    struct ipd_charset_string request_uri; /**< request-URI (eg, "sip:user@example.com") */
    struct ipd_charset_string sip_version; /**< SIP version ("SIP/2.0") */
};

/** fields of a SIP status-line */
struct ipd_sip_status_line {
    struct ipd_charset_string sip_version; /**< SIP version */
    struct ipd_charset_string status_code; /**< status code (eg, "200") */
    struct ipd_charset_string reason_phrase; /**< reason phrase (eg., "OK") */
};

/** fields of a SIP CSeq header field */
struct ipd_sip_cseq {
    u32 number;                 /**< sequence number */
    struct ipd_charset_string method; /** request method */
};

/** \brief elements of a Remote-Party-ID header field value

	\details Refer to 
    <a href="http://tools.ietf.org/html/draft-ietf-sip-privacy-04#section-6.1">Remote-Party-ID</a>
    for detailed information about this header field.
*/
struct ipd_sip_remote_party_id {
    /** \brief entire header field value, eg.
     * <tt>"Mary Doe" <sip:mdoe@foo.com>;party=called;id-type=subscriber;screen=yes</tt>
     */
    struct ipd_charset_string field_value;

    /** \brief display name, eg. "Mary Doe" */
    struct ipd_charset_string display_name; 

    /** \brief URI, eg. "sip:mdoe@foo.com" */
    struct ipd_charset_string uri;          

    /** \brief pointer to an array of parameters, eg. "party=called", "id-type=subscriber", "screen=yes" */
    const struct ipd_charset_string *parameters;

    /** \brief number of parameters in #parameters */
    u64 number_of_parameters;
};

/** \brief representation of a P-Asserted-Identity header field value

	\details Refer to
    <a href="http://tools.ietf.org/html/rfc3325#section-9.1">P-Asserted-Identity</a>
	for detailed information about this header field.
*/
struct ipd_sip_asserted_identity {
    /** \brief entire header field value, eg.
     * <tt>"Cullen Jennings" <sip:fluffy@cisco.com></tt>
     */
    struct ipd_charset_string field_value;

    /** \brief display name, eg. "Cullen Jennings" */
    struct ipd_charset_string display_name; 

    /** \brief URI, eg. "sip:fluffy@cisco.com" */
    struct ipd_charset_string uri;          
};

/** \brief representation of a SDP origin (o=) line */
struct ipd_sdp_origin {
    /** \brief the entire field value (everything after the 'o=') */
    struct ipd_charset_string field_value;

    /** \brief the user's login name on the originating host, or "-" */
    struct ipd_charset_string username;

    /** \brief sess-id field */
    struct ipd_charset_string sess_id;

    /** \brief sess-version field */
    struct ipd_charset_string sess_version;

    /** \brief address type of the origin address (0 for IP4, 1 for IP6) */
    u8 address_is_ipv6;

    /** \brief address of the machine from which this session was created
        \details If the origin address in the session description is not given as an IPv4 or IPv6 address
        literal, but as a FQDN, this structure field is left at all-zeros. */
    union ip_v4_v6_addr address;
};

/** \brief representation of a SDP media (m=) line */
struct ipd_sdp_media {
    /** \brief the entire field value (everything after the 'm=') */
    struct ipd_charset_string field_value;

    /** \brief media type - "audio", "video" etc. */
    struct ipd_charset_string media_type;
    /** \brief protocol - usually "RTP/AVP" */
    struct ipd_charset_string proto;

    u16 port_base;  /**< \brief first port (in host byte order) */
    u16 port_count; /**< \brief number of ports used for this media description */
    /** \brief increment between port numbers
        \details usually 2 for RTP/AVP - even ports for RTP, odd for RTCP */
    u16 port_step;
};

/** \brief representation of a SDP connection data (c=) line */
struct ipd_sdp_connection_data {
    /** \brief the entire field value (everything after the 'c=') */
    struct ipd_charset_string field_value;

    /** \brief address type of the connection address (0 for IP4, 1 for IP6) */
    u8 address_is_ipv6;

    /** \brief the connection address
        \details If the connection address in the session description is not given as an IPv4 or IPv6 address
        literal, but as a FQDN, this structure field is left at all-zeros. */
    union ip_v4_v6_addr address;

    /** \brief number of addresses (assigned contiguously, starting from #address) */
    int address_count;

    /** \brief index of the media description (in ipd_sip_message::sdp_media_lines) that this connection data
        line belongs to, or -1 for session-level connection data */
    int media_index;
};

/** \brief representation of a SDP attribute data (a=) line */
struct ipd_sdp_attribute_data {
    /** \brief the entire field value (everything after the 'a=') */
    struct ipd_charset_string field_value;

    /** \brief name of the attribute */
    struct ipd_charset_string attribute;
    /** \brief value of the attribute */
    struct ipd_charset_string value;

    /** \brief index of the media description (in ipd_sip_message::sdp_media_lines) that this attribute data
        line belongs to, or -1 for session-level attribute data */
    int media_index;
};

/** Enumeration whether a SIP message is a request or a response */
typedef enum {
    IPD_SIP_REQUEST, /** <Signals a SIP request*/
    IPD_SIP_RESPONSE, /** <Signals a SIP response*/
} ipd_sip_message_type;

/** parsed header fields from a SIP message and its payload */
struct ipd_sip_message {
    union ip_v4_v6_addr source_address; /**< sender IP address */
    u8 source_address_is_ipv6;         /**< flag that is set if #source_address contains an IPv6 address */

    ipd_sip_message_type type;  /**< message type (request or response) */
    union {
        struct ipd_sip_request_line request;
        struct ipd_sip_status_line response;
    };

    /* header fields */
    struct ipd_sip_contact_param to; /**< To: header field */
    struct ipd_sip_contact_param from; /**< From: header field */
    struct ipd_sip_cseq cseq;          /**< CSeq: header field */
    struct ipd_charset_string call_id; /**< Call-ID: header field */
    struct ipd_charset_string user_agent; /**< User-Agent: header field (if set) */
    struct ipd_charset_string content_type; /**< Content-Type: header field */

    /** \brief an array of Remote-Party-ID header fields, each represented by a struct ipd_sip_remote_party_id */
    const struct ipd_sip_remote_party_id *remote_party_ids;
    u64 number_of_remote_party_ids;                         /**< \brief number of elements in #remote_party_ids */

    /** \brief an array of P-Asserted-Identity header fields, each represented by a struct ipd_sip_asserted_identity */
    const struct ipd_sip_asserted_identity *asserted_identities;
    u64 number_of_asserted_identities; /**< \brief number of elements in #asserted_identities */

    /** the number of Via: header lines; in requests, a count larger than 1 indicates that the request passed
     * through a SIP proxy (cf. sections 8.1.1.7 and 16.6 of RFC 3261) */
    u64 via_count;

    struct ipd_charset_string header;       /**< header of the SIP message */
    struct ipd_charset_string body;         /**< body of the SIP message */

    /** @name SDP fields
     * fields that are only set when the content type is application/sdp */
    /**@{*/
    struct ipd_sdp_origin sdp_origin;       /**< \brief SDP origin ("o=") field, represented by a struct ipd_sdp_origin */

    /** \brief array of SDP media ("m=") fields, each represented by a struct ipd_sdp_media */
    const struct ipd_sdp_media *sdp_media_lines;
    u64 number_of_sdp_media_lines;          /**< \brief number of elements in #sdp_media_lines */

    /** \brief array of SDP connection data ("c=") lines, each represented by a struct ipd_sdp_connection_data */
    const struct ipd_sdp_connection_data *sdp_connection_data_lines;
    u64 number_of_sdp_connection_data_lines; /**< \brief number of elements in #sdp_connection_data_lines */

    /** \brief array of SDP attribute data ("a=") lines, each represented by a struct ipd_sdp_attribute_data */
    const struct ipd_sdp_attribute_data *sdp_attribute_data_lines;
    u64 number_of_sdp_attribute_data_lines; /**< \brief number of elements in #sdp_attribute_data_lines */

    struct ipd_address_port *candidates_array; /**< array of candidate addresses for RTP flows */
    u64 candidates_array_len;              /**< number of candidate addresses */
    /**@}*/
};

/** SIP decoder event types (used as values of the \c type argument of a \ref ipd_decoder_event_callback function)
 */
enum ipd_simple_event_sip_enumeration
{
    IPD_EVENT_SIP_MESSAGE,      /**< Issued for each decoded SIP message.  \c data points to a struct
                                 * ipd_sip_message. */
    IPD_EVENT_SIP_END_OF_FLOW,  /**< Signals connection termination (TCP transport) or flow timeout (UDP, TCP). */
    IPD_EVENT_SIP_INVALID,      /**< Issued when decoding a message fails.  An error message is passed as a
                                 * <tt>char *</tt> in the \c data argument. */

    IPD_EVENT_SIP_RTP_DATA,     /**< Issued for each RTP packet in flows correlated to this SIP flow.  \c data
                                 * points to a struct ipd_rtp_data. */
    IPD_EVENT_SIP_RTP_END_OF_FLOW,	/**< Signals flow timeout of a correlated RTP flow. */
    IPD_EVENT_SIP_RTP_INVALID,	/**< Issued when decoding a packet in a correlated RTP flow fails.  An error
                                 * message is passed as a <tt>char *</tt> in the \c data argument. */
    IPD_EVENT_SIP_RTP_SSRC,     /**< Issued for each SSRC in RTP packets in flows correlated to this SIP flow.  \c data
                                 * points to a struct ipd_rtp_ssrc. */
    IPD_NUMBER_OF_SIP_EVENTS,
};

#endif                          /* __IPOQUE_DECODER_SIP_INCLUDE_FILE__ */
