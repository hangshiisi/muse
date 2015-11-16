#ifndef __IPOQUE_DECODER_JABBER_INCLUDE_FILE__
#define __IPOQUE_DECODER_JABBER_INCLUDE_FILE__

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif

/**
 * Structure for a jabber chat message
 */
struct ipd_jabber_message_struct
{
	/** The jabber ID for the contact from which the message comes*/
    struct ipd_charset_string from_jid;
    /** The jabber ID for the contact to which the message goes*/
    struct ipd_charset_string to_jid;
    /** The send message*/
    struct ipd_charset_string message;
    /** The ID of the chat room*/
    struct ipd_charset_string room_id;
};

/**
 * Structure for VoIP
 */
struct ipd_jabber_voip_struct
{
	/** The jabber ID for the contact from which the voip part comes*/
    struct ipd_charset_string from_jid;
    /** The jabber ID for the contact to which the voip part goes*/
    struct ipd_charset_string to_jid;
    /** The ID of the correlating audio and video session*/
    struct ipd_charset_string av_session_id;
};

/**
 * Structure for IBB announcements, opening, closure, and error messages.
 */
struct ipd_jabber_ibb_announcement_struct
{
    /** The id of the side sending the message/file. */
    struct ipd_charset_string from;
    /** The id of the side receiving the message/file. */
    struct ipd_charset_string to;
    /** The identifier of the announced transfer. */
    struct ipd_charset_string ibb_sid;
    /** The name  of the transferred file. */
    struct ipd_charset_string file_name;
    /** The size of the transferred file. */
    u64 file_size;
};

/**
 * Structure for opening an IBB file transfer.
 */
struct ipd_jabber_ibb_open_filetransfer_struct
{
    /** The id of the side sending the message/file. */
    struct ipd_charset_string from;
    /** The id of the side receiving the message/file. */
    struct ipd_charset_string to;
    /** The identifier of the announced transfer. */
    struct ipd_charset_string ibb_sid;
    /** The maximum block size for the transferred file. */
    u32 maximum_block_size;
};

/**
 * Structure for IBB BASE-64 encoded data.
 */
struct ipd_jabber_ibb_data_struct
{
    /** The id of the side sending the message/file. */
    struct ipd_charset_string from;
    /** The id of the side receiving the message/file. */
    struct ipd_charset_string to;
    /** The identifier of the announced transfer. */
    struct ipd_charset_string ibb_sid;
    /** The sequence number of the part of the transferred file. */
    u32 sequence_number;
    /** The offset of the data from the beginning of the file. */
    u64 offset;
    /** The BASE-64 encoded data of the transferred file. */
    struct ipd_charset_string data;
    /** The decoded raw data of the transferred file. */
    struct ipd_charset_string data_raw;
};

/** Enumeration for simple JABBER events. This is passed as \c type to the \ref ipd_decoder_event_callback.
 */
enum ipd_event_jabber_enum
{
    /** This event indicates a new JABBER connection. It does not provide any data. */
    IPD_EVENT_JABBER_NEW_CONNECTION,    // returns NULL
    /** This event indicates the end of an Jabber connection. It does not provide any data. */
    IPD_EVENT_JABBER_CLOSE_CONNECTION,  // returns NULL
    /** Signals the start of a TLS connection. */
    IPD_EVENT_JABBER_STARTTLS,			// returns NULL
    /** Provides a struct ipd_charset_string * with the jabber id of the connecting user. */
    IPD_EVENT_JABBER_LOG_ON,
    /** Provides a struct ipd_charset_string * with the jabber id of the buddy. */
    IPD_EVENT_JABBER_BUDDY_ADD,
    /** Provides a struct ipd_charset_string * with the jabber id of the buddy which should be added. */
    IPD_EVENT_JABBER_ADD_NEW_BUDDY,
    /** Provides a struct ipd_charset_string * with the jabber id of the buddy which accept the buddy invite. */
    IPD_EVENT_JABBER_NEW_BUDDY_ACCEPT,
    /** Provides a struct ipd_charset_string * with the jabber id of the buddy which cancel the buddy invite. */
    IPD_EVENT_JABBER_NEW_BUDDY_CANCEL,
    /** Provides a struct ipd_charset_string * with the jabber id of the user who goes to online. */
    IPD_EVENT_JABBER_USER_ON,
    /** Provides a struct ipd_charset_string * with the jabber id of the user who goes to offline. */
    IPD_EVENT_JABBER_USER_OFF,
    /** Provides a struct ipd_charset_string * with the jabber id of the user who goes to do not disturb. */
    IPD_EVENT_JABBER_USER_DO_NOT_DISTURB,
    /** Signals that the user has send a message. Provides a struct ipd_jabber_message_struct * with the send message. */
    IPD_EVENT_JABBER_MESSAGE_OUT,       // returns struct ipd_jabber_message_struct
    /** Signals that the user has received a message. Provides a struct ipd_jabber_message_struct * with the received message. */
    IPD_EVENT_JABBER_MESSAGE_IN,        // returns struct ipd_jabber_message_struct
    /** Signals that a buddy has change his status. Provides a struct ipd_jabber_message_struct * with from for the buddy and message for the new status. */
    IPD_EVENT_JABBER_BUDDY_CHANGE_STATUS,       // returns struct ipd_jabber_message_struct
    /** Signals that the use has change his status. Provides a struct ipd_charset_string * with the new status. */
    IPD_EVENT_JABBER_CHANGE_STATUS,
    /** Signals the announce of a VOIP. Provides a struct ipd_jabber_voip_struct * with the information about the av_session. */
    IPD_EVENT_JABBER_VOIP_ANNOUNCE,     // returns struct ipd_jabber_voip_struct
    /** Signals the accept of a VOIP. Provides a struct ipd_jabber_voip_struct * with the information about the av_session. */
    IPD_EVENT_JABBER_VOIP_ACCEPT,       // returns struct ipd_jabber_voip_struct
    /** Signals the reject of a VOIP. Provides a struct ipd_jabber_voip_struct * with the information about the av_session. */
    IPD_EVENT_JABBER_VOIP_REJECT,       // returns struct ipd_jabber_voip_struct
    /** Signals the end of a VOIP. Provides a struct ipd_jabber_voip_struct * with the information about the av_session. */
    IPD_EVENT_JABBER_VOIP_END,  // returns struct ipd_jabber_voip_struct
    /** Provides a struct ipd_rtp_data * with a RTP packet which is related to an JABBER voice over IP session.
	 * This event is actually issued by the RTP decoder. */
    IPD_EVENT_JABBER_RTP_DATA,  // returns struct ipd_rtp_data defined in ipd_rtp_definitions.h
    /** This event is issued when decoding of an JABBER connection fails. It provides a const char * to a message describing the failure reason. */
    IPD_EVENT_JABBER_INVALID,   // returns char*
    /** This event is issued when an JABBER connection ends. It does not provide any data. */
    IPD_EVENT_JABBER_END_OF_FLOW,       // returns NULL
    /** This event is issued when an JABBER stream is compressed. It provides the information message containing compression type used. */
    IPD_EVENT_JABBER_STREAM_COMPRESSED,       // returns struct ipd_charset_string.
    /** This event is issued when an JABBER connection contains compressed data. It provides the compressed data. */
    IPD_EVENT_JABBER_COMPRESSED_DATA,       // returns struct ipd_charset_string.
    /** This event is issued when a SSRC value is occured. */
    IPD_EVENT_JABBER_RTP_SSRC,

    /** IBB file transfer announcement. Issued when found announcement of a new file to be transferred by IBB.
     * Provides the struct ipd_jabber_ibb_announcement_struct * (file name, size, SID, and the identifier of the involved parties if possible). */
    IPD_EVENT_JABBER_IBB_ANNOUNCEMENT,       // returns ipd_jabber_ibb_announcement_struct *
    /** IBB file transfer opening. Issued when the file transferred is opened. Provides the struct ipd_jabber_ibb_open_filetransfer_struct * (SID, maximum block size,
     * and the identifier of the involved parties if possible). */
    IPD_EVENT_JABBER_IBB_OPEN_FILETRANSFER,       // returns ipd_jabber_ibb_open_filetransfer_struct *
    /** IBB file transfer closure. Issued when the file transfer is completed. Provides the struct ipd_jabber_ibb_announcement_struct *
     * (SID and the identifier of the involved parties if possible). */
    IPD_EVENT_JABBER_IBB_CLOSE_FILETRANSFER,       // returns ipd_jabber_ibb_announcement_struct *
    /** IBB file transfer rejection. Issued when the announcement of the file transfer was rejected.
     * Provides the struct ipd_jabber_ibb_announcement_struct * (identifier of the involved parties if possible). */
    IPD_EVENT_JABBER_IBB_REJECT_FILETRANSFER,       // returns ipd_jabber_ibb_announcement_struct *
    /** IBB file transfer data. Issued when found BASE-64 encoded data sent by an IBB file transfer.
     * Provides the struct ipd_jabber_ibb_data_struct * (SID, chunk sequence number, pointer to the data, and the identifier of the involved parties if possible). */
    IPD_EVENT_JABBER_IBB_DATA,       // returns ipd_jabber_ibb_data_struct *

    IPD_NUMBER_OF_JABBER_EVENTS,
};

#endif                          /* __IPOQUE_DECODER_JABBER_INCLUDE_FILE__ */
