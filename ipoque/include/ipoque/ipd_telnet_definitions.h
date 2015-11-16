/********************************************************************************/
/**
 ** \file       ipd_telnet_definitions.h
 ** \brief      Structures and enumerations for all events of the Telnet Protocol.
 **/
/********************************************************************************/

#ifndef __IPOQUE_DECODER_TELNET_INCLUDE_FILE__
#define __IPOQUE_DECODER_TELNET_INCLUDE_FILE__

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif

/** Enumeration for the type of marked commands */
enum ipd_telnet_marked_command_type_enum
{
	/** Signals, thats the set term ansi was send. */
    IPD_TELNET_MARKED_COMMAND_SET_TERM_ANSI,
    /** Signals, thats the set term vt52 was send. */
    IPD_TELNET_MARKED_COMMAND_SET_TERM_VT52,
    /** Signals, thats the set term vtnt was send. */
    IPD_TELNET_MARKED_COMMAND_SET_TERM_VTNT,
    /** Signals, thats the set term vt100 was send. */
    IPD_TELNET_MARKED_COMMAND_SET_TERM_VT100,
    /** Signals, thats the set term vt220 was send. */
    IPD_TELNET_MARKED_COMMAND_SET_TERM_VT220,
    /** Signals, thats the set term vt320 was send. */
    IPD_TELNET_MARKED_COMMAND_SET_TERM_VT320,
    /** Signals, thats the set term vt420 was send. */
    IPD_TELNET_MARKED_COMMAND_SET_TERM_VT420,
    /** Signals, thats the set term xterm was send. */
    IPD_TELNET_MARKED_COMMAND_SET_TERM_XTERM,
    /** Define the max of marked commands */
    IPD_TELNET_MARKED_COMMAND_COUNT,
};

/** Structure for a telnet command. */
struct ipd_telnet_command
{
	/** The data which are part of the command */
	struct ipd_charset_string command;
	/** The direction of the command */
	u8 direction;
};

/** Structure of a marked telnet command.*/
struct ipd_telnet_marked_command
{
	/** The telnet command as struct ipd_telnet_command * @see ipd_telnet_command*/
	struct ipd_telnet_command *command;
	/** The type of the marked command. @see ipd_telnet_marked_command_type_enum*/
	enum ipd_telnet_marked_command_type_enum type;
};

/** Structure for telnet data. */
struct ipd_telnet_data
{
	/** The direction of the command */
	u8 direction;
	/** The data which are send */
	struct ipd_charset_string data;
};

/**
 * Enumeration for simple Telnet events. This is passed as \c type to the \ref ipd_decoder_event_callback.
 */
enum ipd_simple_event_telnet_enumeration
{
	/** This event indicates a new Telnet connection. It is just a marker, data is a NULL pointer. */
    IPD_EVENT_TELNET_NEW_CONNECTION,		/* NULL */
    /** This event indicates the end of the Telnet connection and flow. It is just a marker, data is a NULL pointer. */
    IPD_EVENT_TELNET_END_OF_FLOW,			/* NULL */
    /** This event is issued when decoding of an Telnet connection fails. It provides a const char * to a message describing the failure reason. */
    IPD_EVENT_TELNET_INVALID,				/* char* */
    /** Provides a struct ipd_telnet_command * with the connection id, direction and the data for the command.*/
    IPD_EVENT_TELNET_COMMAND,				/* struct ipd_telnet_command */
    /** Provides a struct ipd_telnet_marked_command * with the command and the type.*/
    IPD_EVENT_TELNET_MARKED_COMMAND,		/* struct ipd_telnet_marked_command */
    /** Provides a struct ipd_telnet_data * with the cconnection id, direction and the data.*/
    IPD_EVENT_TELNET_DATA,					/* struct ipd_telnet_data */

    IPD_NUMBER_OF_TELNET_EVENTS,
};

#endif /* __IPOQUE_DECODER_TELNET_INCLUDE_FILE__ */
