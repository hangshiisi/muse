/********************************************************************************/
/**
 ** \file       ipd_ftp_definitions.h
 ** \brief      Structures and enumerations for all events of the FTP Protocol.
 **/
/********************************************************************************/

#ifndef __IPOQUE_DECODER_FTP_INCLUDE_FILE__
#define __IPOQUE_DECODER_FTP_INCLUDE_FILE__

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif

/**
 * Enumeration for the type of a transfer in FTP
 */
enum ipd_ftp_transfer_enumeration
{
    /** transfer is an upload (STOR, STOU, APPE commands) */
    IPD_TRANSFER_FTP_UPLOAD,
    /** transfer is a download (RETR command) */
    IPD_TRANSFER_FTP_DOWNLOAD,
    /** transfer contains a directory listing (LIST, NLST, MLSD commands) */
    IPD_TRANSFER_FTP_LIST,
};

/**
 * Structure for start of down- and uploads in a ftp session or for the result of a list command
 */
struct ipd_ftp_transfer_info
{
    u64 transfer_id;
    /** The type of a transfer. @see ipd_ftp_transfer_enumeration */
    enum ipd_ftp_transfer_enumeration transfer_type;
	/** name of the transferred file (only set for types #IPD_TRANSFER_FTP_UPLOAD and #IPD_TRANSFER_FTP_DOWNLOAD) */
	struct ipd_charset_string server_file_name;
};

/**
 * Structure that associates an FTP data connection with the control flow transfer that caused it to be opened.
 */
struct ipd_ftp_data_flow_info
{
    /** Flow ID of the control flow */
    u64 session_flow_id;
    /** The transfer ID from the corresponding FTP_TRANSFER_INIT event on the control connection */
    u64 transfer_id;
};

/**
 * Structure for data which are send in a transfer
 * @see ipd_ftp_transfer_info
 */
struct ipd_ftp_data
{
	/** The connection id of the correlating session*/
	u64 session_flow_id;
    /** The transfer ID from the corresponding FTP_TRANSFER_INIT event on the control connection */
    u64 transfer_id;
	/** The offset of this data block in the transmitted file (does not start at 0 if the REST command was used) */
	u64 offset;
	/** The data's of this data block*/
	struct ipd_charset_string data;
};

/**
 * Enumeration for the type of a command
 */
enum ipd_ftp_command_enum
{
    /** unknown command */
    IPD_FTP_COMMAND_UNKNOWN,
    /** CDUP command */
    IPD_FTP_COMMAND_CDUP,
    /** RNFR command */
    IPD_FTP_COMMAND_RNFR,
    /** RNTO command */
    IPD_FTP_COMMAND_RNTO,
    /** USER command */
    IPD_FTP_COMMAND_USER,
    /** PASS command */
    IPD_FTP_COMMAND_PASS,
    /** ACCT command */
    IPD_FTP_COMMAND_ACCT,
    /** CWD command */
    IPD_FTP_COMMAND_CWD,
    /** QUIT command */
    IPD_FTP_COMMAND_QUIT,
    /** PORT command */
    IPD_FTP_COMMAND_PORT,
    /** PASV command */
    IPD_FTP_COMMAND_PASV,
    /** RETR command */
    IPD_FTP_COMMAND_RETR,
    /** STOR command */
    IPD_FTP_COMMAND_STOR,
    /** STOU command */
    IPD_FTP_COMMAND_STOU,
    /** APPE command */
    IPD_FTP_COMMAND_APPE,
    /** REST command */
    IPD_FTP_COMMAND_REST,
    /** ABOR command */
    IPD_FTP_COMMAND_ABOR,
    /** DELE command */
    IPD_FTP_COMMAND_DELE,
    /** RMD command */
    IPD_FTP_COMMAND_RMD,
    /** MKD command */
    IPD_FTP_COMMAND_MKD,
    /** PWD command */
    IPD_FTP_COMMAND_PWD,
    /** LIST command */
    IPD_FTP_COMMAND_LIST,
    /** NLST command */
    IPD_FTP_COMMAND_NLST,
    /** MLSD command */
    IPD_FTP_COMMAND_MLSD,
    /** MODE command */
    IPD_FTP_COMMAND_MODE,
    /** NOOP command */
    IPD_FTP_COMMAND_NOOP,
    /** EPRT command */
    IPD_FTP_COMMAND_EPRT,
    /** EPSV command */
    IPD_FTP_COMMAND_EPSV,
};

/**
 * Structure for a command in FTP.
 */

/**
 * Structure for a reply in FTP.
 */
struct ipd_ftp_reply
{
    /**
     * The code of the reply. \ref code/100 signals the \link ipd_ftp_reply::code category\endlink of a reply.
     *  - category 1: command successfully done, but one more reply will come later.
     *  - category 2: command successfully done.
     *  - category 3: command successfully done, but one more command is needed.
     *  - category 4: command failed (temporary), maybe a second call will be successfully.
     *  - category 5: command failed (error).
     */
    u16 code;
    /** The message which is send with the reply. */
    struct ipd_charset_string message;
    /** Is true (1) if the reply is a multiline reply and signals, that one more line will follow. The last line is set to false (0)*/
    u8 continued:1;
};



/**
 * Enumeration for simple FTP events. This is passed as \c type to the \ref ipd_decoder_event_callback.
 */
enum ipd_simple_event_ftp_enumeration
{
	/** Signals the start of a new FTP control connection; \c data is a */
    IPD_EVENT_FTP_NEW_CONTROL_CONNECTION,   /**< NULL pointer */
    /** Signals the start of a new FTP data connection; \c data points to a */
    IPD_EVENT_FTP_NEW_DATA_CONNECTION, /**< struct ipd_ftp_data_flow_info */
    /** This event indicates that the server has signalled successful completion of the transfer (226 reply); \c data points to the */
    IPD_EVENT_FTP_TRANSFER_END,         /**< u64 transfer id from the #IPD_EVENT_FTP_TRANSFER_INIT event */
    /** This event indicates that the server has signalled that the transfer was aborted (4xx or 5xx reply); * \c data points to the */
    IPD_EVENT_FTP_TRANSFER_CANCELED,	/**< u64 transfer id from the #IPD_EVENT_FTP_TRANSFER_INIT event. */
    /** Provides a struct ipd_ftp_data * with the session flow id, offset and data for a transfer. Can be the result of list command or a file transfer. */
    IPD_EVENT_FTP_DATA,				// returns struct ipd_ftp_data
    /** Indicates the end of an FTP control flow; \c data is a */
    IPD_EVENT_FTP_END_OF_CONTROL_FLOW,		/**< NULL pointer */
    /** Indicates the end of an FTP data flow; \c data points to a */
    IPD_EVENT_FTP_END_OF_DATA_FLOW,		/**< struct ipd_ftp_data_flow_info */
    /** This event is issued when decoding of an FTP connection fails. It provides a const char * to a message describing the failure reason. */
    IPD_EVENT_FTP_INVALID,      	// returns u8 * (invalid txt msg)
    /** Provides a struct ipd_ftp_command * with the information about a send command in FTP. */
    IPD_EVENT_FTP_COMMAND,          // returns struct ipd_ftp_command
    /** Provides a struct ipd_ftp_reply * with the information about a send reply in FTP. */
    IPD_EVENT_FTP_REPLY,            //returns struct ipd_ftp_reply
    /** Provides a struct ipd_ftp_transfer_info * with the information about a transfer what is initialized. Will be send after a transfer command like STOR, RETR or LIST.*/
    IPD_EVENT_FTP_TRANSFER_INIT,    // returns struct ipd_ftp_transfer_info

    IPD_NUMBER_OF_FTP_EVENTS,
};

#endif /* __IPOQUE_DECODER_FTP_INCLUDE_FILE__ */
