/********************************************************************************/
/**
 ** \file       ipd_imap_definitions.h
 ** \brief      Structures and enumerations for all events of the IMAP Protocol.
 **/
/********************************************************************************/

#ifndef __IPOQUE_DECODER_IMAP_INCLUDE_FILE__
#define __IPOQUE_DECODER_IMAP_INCLUDE_FILE__

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif

/** IMAP decoder event types (used as values of the \c type argument of a \ref ipd_decoder_event_callback function)
 */
enum ipd_simple_event_imap_enumeration
{
    /** This event is sent when the first payload data has been processed and the client and server roles have been
     * determined. The provided data is a pointer to an int that contains the client direction (0 or 1). */
    IPD_EVENT_IMAP_CLIENT_DIRECTION,    /* returns int * */
    /** Provides a struct ipd_charset_string * with the login name of the user. */
    IPD_EVENT_IMAP_USER,
    /** Provides a struct ipd_charset_string * with the password of the user, if available. */
    IPD_EVENT_IMAP_PASS,
    /** This event indicates the start of a TLS connection. */
    IPD_EVENT_IMAP_STARTTLS,			/* returns NOTHING */

    /** The server greeting, \c data points to a */
    IPD_EVENT_IMAP_GREETING,            /**< struct ipd_imap_greeting. */

    /** This event is sent for each data item in a FETCH response that contains message text (BODY[], RFC822,
     * RFC822.HEADER, RFC822.TEXT). All IMF events in this flow up to the next IMF_DONE belong to this
     * (section of a) message. \c data points to a */
    IPD_EVENT_IMAP_FETCH_BODY_ITEM,  /**< struct ipd_imap_fetch_body_item. */

    /** Sent at the beginning of each APPEND command issued by the client, ie. before the IMF events of a mail that
     * the client uploads to the server. \c data points to a */
    IPD_EVENT_IMAP_APPEND,              /**< struct ipd_charset_string that contains the command tag. */

    /** Sent for each tagged server response, \c data points to a */
    IPD_EVENT_IMAP_RESPONSE,            /**< struct ipd_imap_response. */

    /** Sent when the client issues a LOGOUT command, \c data is */
    IPD_EVENT_IMAP_LOGOUT,              /**< a NULL pointer. */
    /** Indicates that the server has sent a BYE response, \c data is */
    IPD_EVENT_IMAP_BYE,                 /**< a NULL pointer. */

    /** Value of the From: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_IMAP_IMF_FROM,            /**< struct ipd_imf_address. */
    /** Value of the To: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_IMAP_IMF_TO,              /**< struct ipd_imf_address. */
    /** Value of the Cc: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_IMAP_IMF_CC,              /**< struct ipd_imf_address. */
    /** Value of the Bcc: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_IMAP_IMF_BCC,             /**< struct ipd_imf_address. */
    /** Value of the Subject: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_IMAP_IMF_SUBJECT,         /**< struct ipd_charset_string. */
    /** Value of the Date: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_IMAP_IMF_DATE,            /**< struct ipd_charset_string. */

    /** Value of the Sender: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_IMAP_IMF_SENDER,          /**< struct ipd_imf_address. */
    /** Value of the Reply-To: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_IMAP_IMF_REPLY_TO,        /**< struct ipd_imf_address. */
    /** Value of the Message-Id: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_IMAP_IMF_MESSAGE_ID,      /**< struct ipd_charset_string. */
    /** Value of the In-Reply-To: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_IMAP_IMF_IN_REPLY_TO,     /**< struct ipd_charset_string. */
    /** Value of the References: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_IMAP_IMF_REFERENCES,      /**< struct ipd_charset_string. */
    /** Value of the Comments: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_IMAP_IMF_COMMENTS,        /**< struct ipd_charset_string. */
    /** Value of the Keywords: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_IMAP_IMF_KEYWORDS,        /**< struct ipd_charset_string. */
    /** Value of the Trace: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_IMAP_IMF_TRACE,           /**< struct ipd_charset_string. */

    /** Value of the Resent-Date: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_IMAP_IMF_RESENT_DATE,     /**< struct ipd_charset_string. */
    /** Value of the Resent-From: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_IMAP_IMF_RESENT_FROM,     /**< struct ipd_imf_address. */
    /** Value of the Resent-Sender: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_IMAP_IMF_RESENT_SENDER,   /**< struct ipd_imf_address. */
    /** Value of the Resent-To: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_IMAP_IMF_RESENT_TO,       /**< struct ipd_imf_address. */
    /** Value of the Resent-Cc: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_IMAP_IMF_RESENT_CC,       /**< struct ipd_imf_address. */
    /** Value of the Resent-Bcc: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_IMAP_IMF_RESENT_BCC,      /**< struct ipd_imf_address. */
    /** Value of the Resent-Msg-Id: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_IMAP_IMF_RESENT_MSG_ID,   /**< struct ipd_charset_string. */
    /** Value of the MIME-Version: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_IMAP_IMF_MIME_VERSION,    /**< struct ipd_charset_string. */
    /** Complete header field (including field name). Sent for all message or part header fields of a transmitted message not
     * covered by more specific events; \c data points to a */
    IPD_EVENT_IMAP_IMF_OTHER,           /**< struct ipd_imf_part_data. */
    /** The entire header of a mail message; \c data points to a */
    IPD_EVENT_IMAP_IMF_HEADER,          /**< struct ipd_charset_string. */

    /** Value of the Content-Type: header field of a message or MIME part; \c data points to a */
    IPD_EVENT_IMAP_IMF_CONTENT_TYPE,    /**< struct ipd_imf_content_type. */
    /** Value of the Content-Transfer-Encoding: header field of a message or MIME part; \c data points to a */
    IPD_EVENT_IMAP_IMF_CONTENT_TRANSFER_ENCODING, /**< struct ipd_imf_part_data. */
    /** Value of the Content-Disposition: header field of a MIME part; \c data points to a */
    IPD_EVENT_IMAP_IMF_CONTENT_DISPOSITION, /**< struct ipd_imf_part_data. */
    /** The entire header of a MIME part; \c data points to a */
    IPD_EVENT_IMAP_IMF_PART_HEADER,     /**< struct ipd_imf_part_data. */

    /** This event indicates the begin of a byte stream (MIME part body, multipart preamble or epilogue); \c data points to a */
    IPD_EVENT_IMAP_IMF_DATA_BEGIN,		/**< struct ipd_charset_string containing the section number of the part. */
    /** A block of data in a byte stream; \c data points to a */
    IPD_EVENT_IMAP_IMF_DATA,            /**< struct ipd_imf_part_data. */
    /** This event indicates the end of a byte stream; \c data points to a */
    IPD_EVENT_IMAP_IMF_DATA_END,		/**< struct ipd_charset_string containing the section number of the part. */

    /** This event indicates the end of a continuous stream of IMF events belonging to one IMF message; \c data is a */
    IPD_EVENT_IMAP_IMF_DONE,    		/**< NULL pointer. */

    /** This event is issued when decoding of an IMAP connection fails. It provides a const char * to a message describing the failure reason. */
    IPD_EVENT_IMAP_INVALID,				/* returns char*   */
    /** This event indicates the end of a connection. It does not provide any data. */
    IPD_EVENT_IMAP_CONNECTION_END,		/* returns NOTHING */

    /** Value of Return-Path: header field of a transmitted mail message; denotes the address where
     * to send error messages; \c data points to a */
    IPD_EVENT_IMAP_IMF_RETURN_PATH,     /**< struct ipd_charset_string. */
    /** Value of Received: header field of a transmitted mail message; an array of strings: each hop
     * across the path from sender to receiver adds information about the respective sender. \c data points to a */
    IPD_EVENT_IMAP_IMF_RECEIVED,        /**< struct ipd_charset_string. */

    IPD_NUMBER_OF_IMAP_EVENTS,
};

/** IMAP response states for tagged responses */
enum ipd_imap_resp_state {
    IPD_IMAP_RESPONSE_OK,
    IPD_IMAP_RESPONSE_NO,
    IPD_IMAP_RESPONSE_BAD,
};

/** a tagged IMAP response */
struct ipd_imap_response {
    struct ipd_charset_string tag;
    enum ipd_imap_resp_state state;
    struct ipd_charset_string text;
};

/** condition codes for an IMAP greeting */
enum ipd_imap_greeting_state {
    IPD_IMAP_GREETING_OK,       /**< connection without pre-authentication */
    IPD_IMAP_GREETING_PREAUTH,  /**< pre-authenticated connection */
    IPD_IMAP_GREETING_BYE,      /**< rejected connection */
};

/** the IMAP server greeting */
struct ipd_imap_greeting {
    enum ipd_imap_greeting_state state;
    struct ipd_charset_string text;
};

/** describes which part of an IMF message are transmitted in a FETCH data item (in the following, "message"
 * refers either to a top-level message (when ipd_imap_fetch_body_item::number is empty), or to a MIME part
 * with content-type message/rfc822, ie. a forwarded message stored in an attachment) */
enum ipd_imap_part_spec {
	IMAP_SECTION_ALL,               /**< the entire message, or the body of a MIME part */
	IMAP_SECTION_HEADER,            /**< only the message header */
	IMAP_SECTION_HEADER_FIELDS,     /**< just selected message header fields */
	IMAP_SECTION_HEADER_FIELDS_NOT, /**< all not-selected message header fields */
	IMAP_SECTION_TEXT,              /**< the body of a message (omitting the header) */
	IMAP_SECTION_MIME,              /**< the header of a MIME part */
};

/** description of a FETCH data item that contains message text (parsed representation of BODY data items, cf. RFC 3501) */
struct ipd_imap_fetch_body_item {
    u64 sequence_number; /**< message sequence number (from the response head) */

    struct ipd_charset_string number; /**< MIME part number, eg. "1.2" (empty for "entire message")  */
    enum ipd_imap_part_spec section; /**< section of the message/MIME part that is fetched */

    /** space-separated list of header fields (only valid if section is IMAP_SECTION_HEADER_FIELDS or
     * IMAP_SECTION_HEADER_FIELDS_NOT */
    struct ipd_charset_string header_fields;

    u64 origin_octet;           /**< byte offset into the message part selected by the number and section fields */
    u8 origin_octet_set;        /**< flag; nonzero if the origin_octet field is set */
};

#endif                          /* __IPOQUE_DECODER_IMAP_INCLUDE_FILE__ */
