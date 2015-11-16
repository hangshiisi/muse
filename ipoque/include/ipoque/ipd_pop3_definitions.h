/********************************************************************************/
/**
 ** \file       ipd_pop3_definitions.h
 ** \brief      Structures and enumerations for all events of the mail Protocol Pop3.
 **/
/********************************************************************************/

#ifndef __IPOQUE_DECODER_POP3_INCLUDE_FILE__
#define __IPOQUE_DECODER_POP3_INCLUDE_FILE__

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif

/** a POP3 response line */
struct ipd_pop3_response {
    struct ipd_charset_string response_line; /**< complete text of the line sent by the server */
    u8 success;                         /**< set to 1 if the status indicator is +OK, 0 otherwise */
};

/**
 * Structure for POP3 command, which was received
 */
struct ipd_pop3_command {
    /** complete command */
    struct ipd_charset_string command_line;
    /** command code like AUTH or RETR */
    struct ipd_charset_string command_code;
    /** command arguments like 5 by RETR */
    struct ipd_charset_string command_arguments;
    /** contained message number or "0" if no message number is contained */
    u32 message_number;
};

/**
 * Structure for a POP3 LIST or POP3 UIDL answer from the server
 */
struct ipd_pop3_list_entry {
    /** the additional property from list (size in bytes) or uidl (unique ID of the message) for this entry */
    struct ipd_charset_string property;
    /** the message number of the entry */
    u32 message_number;
};

/** Enumeration for simple pop3 events. This is given by the \c type at \ref ipd_decoder_event_callback
 */
enum ipd_simple_event_pop3_enumeration
{
    /** This event is sent when the first payload data has been processed and the client and server roles have been
     * determined. The provided data is a pointer to an int that contains the client direction (0 or 1). */
    IPD_EVENT_POP3_CLIENT_DIRECTION,     /* returns int * */
    /** This event provides the text of the initial server greeting as a */
    IPD_EVENT_POP3_SERVER_GREETING,     /**< struct ipd_charset_string. */
	/** Provides a struct ipd_charset_string * with the login name of the user. */
    IPD_EVENT_POP3_USER,
    /** Provides a struct ipd_charset_string * with the password of the user, if available. */
    IPD_EVENT_POP3_PASS,
    /** MD5 digest sent by the user during APOP authentication; \c data points to a */
    IPD_EVENT_POP3_APOP_DIGEST,         /**< struct ipd_charset_string. */
    /** Indicates that the client issued a RETR command; \c data is a */
    IPD_EVENT_POP3_RETR,                /**< NULL pointer. */
    /** Indicates that the client issued a TOP command; \c data is a */
    IPD_EVENT_POP3_TOP,                 /**< NULL pointer.  */
    /** Indicates that the client issued a QUIT command; \c data is a */
    IPD_EVENT_POP3_QUIT,                /**< NULL pointer.  */

    /** Indicates that the server answers to a LIST command; \c data is a */
    IPD_EVENT_POP3_LIST_ENTRY,                /**< ipd_pop3_list_entry.  */
    /** Indicates that the server answers to a UIDL command; \c data is a */
    IPD_EVENT_POP3_UIDL_ENTRY,                /**< ipd_pop3_list_entry.  */
    /** Indicates that the server answers to a LIST command and the end was reached; \c data is a */
    IPD_EVENT_POP3_LIST_END,                  /**< NULL pointer.  */
    /** Indicates that the server answers to a UIDL command and the end was reached; \c data is a */
    IPD_EVENT_POP3_UIDL_END,                  /**< NULL pointer.  */

    /** Value of the From: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_POP3_IMF_FROM,            /**< struct ipd_imf_address. */
    /** Value of the To: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_POP3_IMF_TO,              /**< struct ipd_imf_address. */
    /** Value of the Cc: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_POP3_IMF_CC,              /**< struct ipd_imf_address. */
    /** Value of the Bcc: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_POP3_IMF_BCC,             /**< struct ipd_imf_address. */
    /** Value of the Subject: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_POP3_IMF_SUBJECT,         /**< struct ipd_charset_string. */
    /** Value of the Date: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_POP3_IMF_DATE,            /**< struct ipd_charset_string. */

    /** Value of the Sender: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_POP3_IMF_SENDER,          /**< struct ipd_imf_address. */
    /** Value of the Reply-To: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_POP3_IMF_REPLY_TO,        /**< struct ipd_imf_address. */
    /** Value of the Message-Id: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_POP3_IMF_MESSAGE_ID,      /**< struct ipd_charset_string. */
    /** Value of the In-Reply-To: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_POP3_IMF_IN_REPLY_TO,     /**< struct ipd_charset_string. */
    /** Value of the References: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_POP3_IMF_REFERENCES,      /**< struct ipd_charset_string. */
    /** Value of the Comments: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_POP3_IMF_COMMENTS,        /**< struct ipd_charset_string. */
    /** Value of the Keywords: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_POP3_IMF_KEYWORDS,        /**< struct ipd_charset_string. */
    /** Value of the Trace: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_POP3_IMF_TRACE,           /**< struct ipd_charset_string. */

    /** Value of the Resent-Date: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_POP3_IMF_RESENT_DATE,     /**< struct ipd_charset_string. */
    /** Value of the Resent-From: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_POP3_IMF_RESENT_FROM,     /**< struct ipd_imf_address. */
    /** Value of the Resent-Sender: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_POP3_IMF_RESENT_SENDER,   /**< struct ipd_imf_address. */
    /** Value of the Resent-To: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_POP3_IMF_RESENT_TO,       /**< struct ipd_imf_address. */
    /** Value of the Resent-Cc: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_POP3_IMF_RESENT_CC,       /**< struct ipd_imf_address. */
    /** Value of the Resent-Bcc: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_POP3_IMF_RESENT_BCC,      /**< struct ipd_imf_address. */
    /** Value of the Resent-Msg-Id: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_POP3_IMF_RESENT_MSG_ID,   /**< struct ipd_charset_string. */
    /** Value of the MIME-Version: header field of a transmitted mail message; \c data points to a */
    IPD_EVENT_POP3_IMF_MIME_VERSION,    /**< struct ipd_charset_string. */
    /** Complete header field (including field name). Sent for all message or part header fields of a transmitted message not
     * covered by more specific events; \c data points to a */
    IPD_EVENT_POP3_IMF_OTHER,           /**< struct ipd_imf_part_data. */
    /** The entire header of a mail message; \c data points to a */
    IPD_EVENT_POP3_IMF_HEADER,          /**< struct ipd_charset_string. */

    /** Value of the Content-Type: header field of a message or MIME part; \c data points to a */
    IPD_EVENT_POP3_IMF_CONTENT_TYPE,    /**< struct ipd_imf_content_type. */
    
    /** Value of the Content-Transfer-Encoding: header field of a message or MIME part; \c data points to a */
    IPD_EVENT_POP3_IMF_CONTENT_TRANSFER_ENCODING, /**< struct ipd_imf_part_data. */
    /** Value of the Content-Disposition: header field of a MIME part; \c data points to a */
    IPD_EVENT_POP3_IMF_CONTENT_DISPOSITION, /**< struct ipd_imf_part_data. */
    /** The entire header of a MIME part; \c data points to a */
    IPD_EVENT_POP3_IMF_PART_HEADER,     /**< struct ipd_imf_part_data. */

    /** This event indicates the begin of a byte stream (MIME part body, multipart preamble or epilogue); \c data points to a */
    IPD_EVENT_POP3_IMF_DATA_BEGIN,		/**< struct ipd_charset_string containing the section number of the part. */
    /** A block of data in a byte stream; \c data points to a */
    IPD_EVENT_POP3_IMF_DATA,            /**< struct ipd_imf_part_data. */
    /** This event indicates the end of a byte stream; \c data points to a */
    IPD_EVENT_POP3_IMF_DATA_END,		/**< struct ipd_charset_string containing the section number of the part. */

    /** This event indicates the end of a mail message; \c data is a */
    IPD_EVENT_POP3_IMF_DONE,    		/**< NULL pointer */
    
	/** This event indicates the start of a TLS connection. */
    IPD_EVENT_POP3_STARTTLS,
    /** This event is issued when decoding of an POP3 connection fails. It provides a const char * to a message describing the failure reason. */
    IPD_EVENT_POP3_INVALID,				/* returns char*   */
    /** This event indicates the end of a connection. It does not provide any data. */
    IPD_EVENT_POP3_CONNECTION_END,		/* returns NOTHING */

    /** The server's response to the most recent command. This event is only emitted if the most recent POP3
     * command was reported in a (non-IMF) PADE event. \c data points to a */
    IPD_EVENT_POP3_RESPONSE,            /**< struct ipd_pop3_response. */
    /** This event indicates the receive of the given POP3 command and provides with the struct ipd_pop3_command * structure all details about the command. */
    IPD_EVENT_POP3_COMMAND,             /**< struct ipd_pop3_command. */

    /** Value of Return-Path: header field of a transmitted mail message; denotes the address where
     * to send error messages; \c data points to a */
    IPD_EVENT_POP3_IMF_RETURN_PATH,     /**< struct ipd_charset_string. */
    /** Value of Received: header field of a transmitted mail message; an array of strings: each hop
     * across the path from sender to receiver adds information about the respective sender. \c data points to a */
    IPD_EVENT_POP3_IMF_RECEIVED,        /**< struct ipd_charset_string. */

    IPD_NUMBER_OF_POP3_EVENTS,
};

#endif                          /* __IPOQUE_DECODER_POP3_INCLUDE_FILE__ */
