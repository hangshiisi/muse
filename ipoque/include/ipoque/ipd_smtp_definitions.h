/********************************************************************************/
/**
 ** \file       ipd_smtp_definitions.h
 ** \brief      Structures and enumerations for all events of the SMTP Protocol.
 **/
/********************************************************************************/

#ifndef __IPOQUE_DECODER_SMTP_INCLUDE_FILE__
#define __IPOQUE_DECODER_SMTP_INCLUDE_FILE__

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif

/** a SMTP reply line */
struct ipd_smtp_reply {
    struct ipd_charset_string reply_line; /**< complete text of the line sent by the server */
    u8 success;                 /**< set to 1 if the reply code is 2xx, 0 otherwise */
    u8 last_line;               /**< set to 1 if this is a single-line reply or the last line of a multi-line
                                 * response, 0 otherwise */
};

/** SMTP decoder event types (used as values of the \c type argument of a \ref ipd_decoder_event_callback function)
 */
enum ipd_simple_event_smtp_enumeration
{
    /** This event is sent when the first payload data has been processed and the client and server roles have been
     * determined. The provided data is a pointer to an int that contains the client direction (0 or 1). */
    IPD_EVENT_SMTP_CLIENT_DIRECTION,    /* returns int * */

    /** This event provides the text of the initial server greeting as a struct ipd_charset_string. It may be
     * generated more than once if the server greeting is a multiline reply. */
    IPD_EVENT_SMTP_SERVER_GREETING,
    /** This event indicates the end of a connection. It does not provide any data. */
    IPD_EVENT_SMTP_CONNECTION_END,		/* returns NOTHING */
    /** This event is issued when decoding of an SMTP connection fails. It provides a const char * to a message describing the failure reason. */
    IPD_EVENT_SMTP_INVALID,				/* returns char* */
    /** This event is sent when the client issues an EHLO or HELO command. The argument of the command is provided as a */
    IPD_EVENT_SMTP_EHLO,                /**< struct ipd_charset_string. */
    /** This event indicates the start of a TLS connection. */
    IPD_EVENT_SMTP_STARTTLS,			/* returns NOTHING */

    /** User name (extracted from an AUTH PLAIN or AUTH LOGIN command), given as a */
    IPD_EVENT_SMTP_USER,                /**< struct ipd_charset_string. */
    /** Password (extracted from an AUTH PLAIN or AUTH LOGIN command), given as a */
    IPD_EVENT_SMTP_PASS,                /**< struct ipd_charset_string. */

    /** Provides a struct ipd_charset_string * with the FROM tag provided by the smtp protocol. */
    IPD_EVENT_SMTP_MAIL_FROM,
    /** Provides a u64 * with the SIZE argument provided by the FROM tag by smtp protocol. */
    IPD_EVENT_SMTP_MAIL_FROM_SIZE,
    /** Provides a struct ipd_charset_string * with the TO tag provided by the smtp protocol. */
    IPD_EVENT_SMTP_RCPT_TO,
    /** This event indicates a SMTP RSET command. */
    IPD_EVENT_SMTP_RESET,				/* returns NOTHING */
    /** This event is sent when the client issues a QUIT command. */
    IPD_EVENT_SMTP_QUIT,                /* returns NOTHING */
    /** The server's reply to the most recent command. This event is only emitted if the most recent SMTP
     * command was reported in a (non-IMF) PADE event, and the reply is a completion (ie, 2xx, 4xx, or 5xx)
     * reply. Only the last line of a multiline reply is reported. \c data points to a */
    IPD_EVENT_SMTP_SERVER_REPLY,        /**< struct ipd_smtp_reply */
    /** This event indicates that a stream of IMF events for one mail message will follow. */
    IPD_EVENT_SMTP_DATA,				/* returns NOTHING */

    /** Value of the From: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_SMTP_IMF_FROM,            /**< struct ipd_imf_address. */
    /** Value of the To: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_SMTP_IMF_TO,              /**< struct ipd_imf_address. */
    /** Value of the Cc: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_SMTP_IMF_CC,              /**< struct ipd_imf_address. */
    /** Value of the Bcc: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_SMTP_IMF_BCC,             /**< struct ipd_imf_address. */
    /** Value of the Subject: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_SMTP_IMF_SUBJECT,         /**< struct ipd_charset_string. */
    /** Value of the Date: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_SMTP_IMF_DATE,            /**< struct ipd_charset_string. */

    /** Value of the Sender: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_SMTP_IMF_SENDER,          /**< struct ipd_imf_address. */
    /** Value of the Reply-To: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_SMTP_IMF_REPLY_TO,        /**< struct ipd_imf_address. */
    /** Value of the Message-Id: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_SMTP_IMF_MESSAGE_ID,      /**< struct ipd_charset_string. */
    /** Value of the In-Reply-To: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_SMTP_IMF_IN_REPLY_TO,     /**< struct ipd_charset_string. */
    /** Value of the References: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_SMTP_IMF_REFERENCES,      /**< struct ipd_charset_string. */
    /** Value of the Comments: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_SMTP_IMF_COMMENTS,        /**< struct ipd_charset_string. */
    /** Value of the Keywords: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_SMTP_IMF_KEYWORDS,        /**< struct ipd_charset_string. */
    /** Value of the Trace: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_SMTP_IMF_TRACE,           /**< struct ipd_charset_string. */

    /** Value of the Resent-Date: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_SMTP_IMF_RESENT_DATE,     /**< struct ipd_charset_string. */
    /** Value of the Resent-From: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_SMTP_IMF_RESENT_FROM,     /**< struct ipd_imf_address. */
    /** Value of the Resent-Sender: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_SMTP_IMF_RESENT_SENDER,   /**< struct ipd_imf_address. */
    /** Value of the Resent-To: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_SMTP_IMF_RESENT_TO,       /**< struct ipd_imf_address. */
    /** Value of the Resent-Cc: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_SMTP_IMF_RESENT_CC,       /**< struct ipd_imf_address. */
    /** Value of the Resent-Bcc: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_SMTP_IMF_RESENT_BCC,      /**< struct ipd_imf_address. */
    /** Value of the Resent-Msg-Id: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_SMTP_IMF_RESENT_MSG_ID,   /**< struct ipd_charset_string. */
    /** Value of the MIME-Version: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_SMTP_IMF_MIME_VERSION,    /**< struct ipd_charset_string. */
    /** Complete header field (including field name). Sent for all message or part header fields of a transmitted message not
     * covered by more specific events; \c data points to a */
    IPD_EVENT_SMTP_IMF_OTHER,           /**< struct ipd_imf_part_data. */
    /** The entire header of a mail message; \c data points to a */
    IPD_EVENT_SMTP_IMF_HEADER,          /**< struct ipd_charset_string. */

    /** Value of the Content-Type: header field of a message or MIME part; \c data points to a */
    IPD_EVENT_SMTP_IMF_CONTENT_TYPE,    /**< struct ipd_imf_content_type. */
    /** Value of the Content-Transfer-Encoding: header field of a message or MIME part; \c data points to a */
    IPD_EVENT_SMTP_IMF_CONTENT_TRANSFER_ENCODING, /**< struct ipd_imf_part_data. */
    /** Value of the Content-Disposition: header field of a MIME part; \c data points to a */
    IPD_EVENT_SMTP_IMF_CONTENT_DISPOSITION, /**< struct ipd_imf_part_data. */
    /** The entire header of a MIME part; \c data points to a */
    IPD_EVENT_SMTP_IMF_PART_HEADER,     /**< struct ipd_imf_part_data. */

    /** This event indicates the begin of a byte stream (MIME part body, multipart preamble or epilogue); \c data points to a */
    IPD_EVENT_SMTP_IMF_DATA_BEGIN,		/**< struct ipd_charset_string containing the section number of the part. */
    /** A block of data in a byte stream; \c data points to a */
    IPD_EVENT_SMTP_IMF_DATA,            /**< struct ipd_imf_part_data. */
    /** This event indicates the end of a byte stream; \c data points to a */
    IPD_EVENT_SMTP_IMF_DATA_END,		/**< struct ipd_charset_string containing the section number of the part. */

    /** This event indicates the end of a mail message; \c data is a */
    IPD_EVENT_SMTP_IMF_DONE,    		/**< NULL pointer */

    /** Value of Return-Path: header field of a transmitted mail message; denotes the address where
     * to send error messages; \c data points to a */
    IPD_EVENT_SMTP_IMF_RETURN_PATH,     /**< struct ipd_charset_string. */
    /** Value of Received: header field of a transmitted mail message; an array of strings: each hop
     * across the path from sender to receiver adds information about the respective sender. \c data points to a */
    IPD_EVENT_SMTP_IMF_RECEIVED,        /**< struct ipd_charset_string. */

    IPD_NUMBER_OF_SMTP_EVENTS,
};

#endif                          /* __IPOQUE_DECODER_SMTP_INCLUDE_FILE__ */
