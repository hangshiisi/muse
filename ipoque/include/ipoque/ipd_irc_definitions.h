/********************************************************************************/
/**
 ** \file       ipd_irc_definitions.h
 ** \brief      Structures and enumerations for all events of the IRC Protocol.
 **/
/********************************************************************************/

#ifndef __IPOQUE_DECODER_IRC_INCLUDE_FILE__
#define __IPOQUE_DECODER_IRC_INCLUDE_FILE__

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif


/** Structure for events that provide information about IRC chatrooms or actual messages */
struct ipd_irc_chat_data
{
	/** The chatroom the event relates to. This can be a the username of the user receiving a message in case of
		a private message or a chatroom name that starts with a # character. */
	struct ipd_charset_string chatroom;
	/** The nickname of the user sending a message. */
	struct ipd_charset_string nick;
	/** The username of the user sending a message. This information is not always available */
	struct ipd_charset_string user;
	/** A message string the event relates to. Can be empty depending on the actual event. */
	struct ipd_charset_string message;
};

/** Structure for events that provide IRC nickname information */
struct ipd_irc_nick_data
{
	/** The username of the user the event relates to. */
	struct ipd_charset_string user;
	/** The old nickname of the user.*/
	struct ipd_charset_string old_nick;
	/** The current nickname of the user. */
	struct ipd_charset_string nick;
};

/** Structure for events that provide IRC file transfer information and data */
struct ipd_irc_ft_data
{
	/** The username of the user that is connected to the IRC server. */
	struct ipd_charset_string user;
	/** The name of the IRC server the user is connected to. */
	struct ipd_charset_string server;
	/** A transfer id that is unique for the IRC connection. */
	struct ipd_charset_string transfer_id;
	/** The user who is the sender of the file. */
	struct ipd_charset_string sender;
	/** The user who is the receiver of the file. */
	struct ipd_charset_string receiver;
	/** The filename of the file being transmitted. */
	struct ipd_charset_string filename;
	/** The file size in bytes of the file being transmitted. */
	u32 file_size;
	/** A segment of actual file transfer data. */
	struct ipd_charset_string data;
	/** Number of bytes of the particular file already transmitted. */
	u64 already_transferred_size;
	u8 last_file_segment;
};

/**
 * Structure for IRC command, which was received
 */
struct ipd_irc_command
{
    /** complete command */
    struct ipd_charset_string command_line;
    /** command code like NICK or JOIN */
    struct ipd_charset_string command_code;
    /** command arguments */
    struct ipd_charset_string command_arguments;
};


/** Enumeration for simple irc events. This is passed as \c type to the \ref ipd_decoder_event_callback.
 */

enum ipd_simple_event_irc_enumeration
{
	/* all values (except marked ones) returns ipd_charset_string* */
	/** Provides a struct ipd_irc_nick_data * with nickname information for the currently connected user. */
	IPD_EVENT_IRC_NICK_USER,	// returns struct ipd_irc_nick_data*
	/** Provides a struct ipd_irc_nick_data * with nickname information for another user on the connected IRC server. */
	IPD_EVENT_IRC_NICK_OTHER,	// returns struct ipd_irc_nick_data*
	/** Provides a struct ipd_irc_chat_data * with information about a private message that is transmitted. */
	IPD_EVENT_IRC_PRIMSG,		// returns struct ipd_irc_chat_data*
	/** Provides a struct ipd_charset_string * with the username of the user that is currently connecting to a ICR server. */
	IPD_EVENT_IRC_LOGIN_USER,
	/** Provides a struct ipd_charset_string * with the password of the user that is currently connecting to a ICR server. */
	IPD_EVENT_IRC_PASS,
	/** Provides a struct ipd_charset_string * with the hostname of the client machine from which the user is connecting. */
	IPD_EVENT_IRC_LOGIN_HOST,
	/** Provides a struct ipd_charset_string * with the name of the IRC server which the user is connecting to. */
	IPD_EVENT_IRC_LOGIN_SERVERNAME,
	/** Provides a struct ipd_charset_string * with the real name of the user that is currently connecting to a ICR server. */
	IPD_EVENT_IRC_LOGIN_REALNAME,
	/** This event is issued when the currently connected user quits from the IRC server. It does not provide any data. */
	IPD_EVENT_IRC_QUIT_USER,	// returns NULL
	/** Provides a struct ipd_irc_chat_data * with information about another user who is quitting from the ICR server. */
	IPD_EVENT_IRC_QUIT_OTHER,	// returns struct ipd_irc_chat_data*
	/** Provides a struct ipd_irc_chat_data * with information about a user joining a chatroom. */
	IPD_EVENT_IRC_JOIN,			// returns struct ipd_irc_chat_data*
	/** Provides a struct ipd_irc_chat_data * with information about a user leaving a chatroom. */
	IPD_EVENT_IRC_PART,			// returns struct ipd_irc_chat_data*
	/** Provides a struct ipd_irc_chat_data * with information about the topic of a chatroom. */
	IPD_EVENT_IRC_TOPIC,		// returns struct ipd_irc_chat_data*
	/** Provides a struct ipd_irc_ft_data * with information about a new file transfer that is announced. */
	IPD_EVENT_IRC_FT_ANNOUNCE,	// returns struct ipd_irc_ft_data*
	/** Provides a struct ipd_irc_ft_data * with a segment of file transfer data. */
	IPD_EVENT_IRC_FT_DATA,		// returns struct ipd_irc_ft_data*
	/** Provides a struct ipd_irc_command * with the details of the command. */
	IPD_EVENT_IRC_COMMAND,      // returns struct ipd_irc_command*
	/** This event is issued when decoding of a IRC connection fails. It provides a const char * to a message describing the failure reason. */
	IPD_EVENT_IRC_INVALID,		// returns const char *
	/** This event is issued when a IRC connection ends. It does not provide any data. */
	IPD_EVENT_IRC_END_OF_FLOW,	// returns NULL

	IPD_NUMBER_OF_IRC_EVENTS,
};


#endif /* __IPOQUE_DECODER_IRC_INCLUDE_FILE__ */
