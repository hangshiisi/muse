/********************************************************************************/
/**
 ** \file       ipd_class_voip_definitions.h
 ** \brief      Structures and enumerations for all events of class VoIP.
 **/
/********************************************************************************/

#ifndef IPD_CLASS_VOIP_DEFINITIONS_H_
#define IPD_CLASS_VOIP_DEFINITIONS_H_

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif

/**
 * Enumeration for the VoIP type
 */
enum ipd_voip_class_struct_enum {
    /** VoIP session starts */
    IPD_CLASS_EVENT_VOIP_SESSION,     /* struct ipd_class_voip_session_struct */
    /** VoIP call is in buildup or clearing */
    IPD_CLASS_EVENT_VOIP_CALL,        /* struct ipd_class_voip_call_struct */
    /** VoIP call contains RTP Data */
    IPD_CLASS_EVENT_VOIP_RTP_DATA,    /* struct ipd_voip_class_rtp_data */
    /** VoIP session ends */
    IPD_CLASS_EVENT_VOIP_SESSION_END, /* struct ipd_class_voip_session_end_struct */
    /** VoIP RTP session starts */
    IPD_CLASS_EVENT_VOIP_RTP_SESSION, /* struct ipd_voip_class_rtp_session_struct */
    /** VoIP RTP session ends */
    IPD_CLASS_EVENT_VOIP_RTP_SESSION_END, /* struct ipd_voip_class_rtp_session_end_struct */
    /** RTP flow of VoIP got an invalid packet */
    IPD_CLASS_EVENT_VOIP_RTP_INVALID, /* struct ipd_voip_class_rtp_invalid_struct */
    /** VoIP flow got an invalid packet */
    IPD_CLASS_EVENT_VOIP_INVALID, /* struct ipd_class_voip_invalid_struct */

    IPD_NUMBER_OF_CLASS_VOIP_EVENTS,
};

/* when changing this enum, don't forget to update the conversion table to chat AV states above
 * chat_sip_state_cb() */
/**
 * Enumeration for the states of a VoIP call (Dialog)
 */
enum ipd_voip_class_call_status {
    /** will be used after a SIP-(Call-)Request is sent (INVITE)*/
    IPD_VOIP_CLASS_CALL_ANNOUNCED,

    /** will be used after the INVITE is rejected either by the user or a busy signal (INVITE FAIL) */
    IPD_VOIP_CLASS_CALL_REJECTED,
    /** will be used when TRYING is send (RINGING) */
    IPD_VOIP_CLASS_CALL_ACKNOWLEDGED,
    
    /** will be used when the caller cancels the call */
    IPD_VOIP_CLASS_CALL_CANCELLED,
    
    /** will be used when the buildup of the call is complete */
    IPD_VOIP_CLASS_CALL_ESTABLISHED,
    /** will be used when the clearing of the call is complete */
    IPD_VOIP_CLASS_CALL_ENDED,
};

#define VOIP_CALL_STATUS_NAMES \
    "announced",               \
    "rejected",                \
    "acknowledged",            \
    "cancelled",               \
    "established",             \
    "ended"

/**
 * Structure for the VoIP session
 */
struct ipd_class_voip_session_struct {
    /** The generic. Contains the id of this event. @see ipd_class_generic_header*/
    struct ipd_class_generic_header generic;

    /** The connection id of the SIP flow */
    u64 connection_id;
};

/**
 * Structure for the end of a VoIP session
 */
struct ipd_class_voip_session_end_struct {
    /** The generic. Contains the id of this event. @see ipd_class_generic_header*/
    struct ipd_class_generic_header generic;

    /** The connection id of the SIP flow */
    u64 connection_id;
    /** The id of the VoIP session of this flow */
    u64 voip_session_id;
};

/**
 * Structure for an invalid packet in the VoIP session
 */
struct ipd_class_voip_invalid_struct {
    /** The generic. Contains the id of this event. @see ipd_class_generic_header*/
    struct ipd_class_generic_header generic;

    /** The connection id of the SIP flow */
    u64 connection_id;
    /** The id of the VoIP session of this flow */
    u64 voip_session_id;
};

/**
 * Structure for a VoIP call event
 */
struct ipd_class_voip_call_struct {
    /** The generic. Contains the id of this event. @see ipd_class_generic_header*/
    struct ipd_class_generic_header generic;
    /** The id of the VoIP session*/
    u64 voip_session_id;

    /** The current state of the call @see ipd_voip_class_call_status*/
    enum ipd_voip_class_call_status status;
    /** The display name of the caller */
    charset_string from_name;
    /** The URI of the caller */
    charset_string from_uri;
    /** The display name of the receiver */
    charset_string to_name;
    /** The URI of the receiver */
    charset_string to_uri;
    /** The call id (Call-ID: header field) */
    charset_string call_id;
    /** The User-Agent: header field of the SIP message triggering the call state
     * change; it is never set in messages from the server, and is optional in
     * client messages; the call update to status==IPD_VOIP_CLASS_CALL_ANNOUNCED
     * is guaranteed to be triggered by a client request (an INVITE) */
    charset_string user_agent;

    /** The time between ESTABLISHED and END */
    u64 duration;

    /** A flag, which indicates a caller behind a proxy. (set if INVITE request had more than one Via: header) */
    u8 caller_is_behind_proxy;
};

/**
 * Structure for the RTP session in VoIP
 */
struct ipd_voip_class_rtp_session_struct {
    /** The generic. Contains the id of this event. @see ipd_class_generic_header*/
    struct ipd_class_generic_header generic;

    /** The connection id of the RTP flow */
    u64 rtp_connection_id;
    /** The id of the VoIP session*/
    u64 voip_session_id;
    /** The VoIP call id */
    u64 voip_call_id;
};

/**
 * Structure for the end of a RTP session in VoIP
 */
struct ipd_voip_class_rtp_session_end_struct {
    /** The generic. Contains the id of this event. @see ipd_class_generic_header*/
    struct ipd_class_generic_header generic;

    /** The connection id of the RTP flow */
    u64 rtp_connection_id;
    /** The id of the RTP session*/
    u64 rtp_session_id;
};

/**
 * Structure for an invalid packet in the RTP session in VoIP
 */
struct ipd_voip_class_rtp_invalid_struct {
    /** The generic. Contains the id of this event. @see ipd_class_generic_header*/
    struct ipd_class_generic_header generic;

    /** The connection id of the RTP flow */
    u64 rtp_connection_id;
    /** The id of the RTP session*/
    u64 rtp_session_id;
};

/**
 * Structure for all Information of one RTP Packet
 */
struct ipd_voip_class_rtp_data {
    /** The generic. Contains the id of this event. @see ipd_class_generic_header*/
    struct ipd_class_generic_header generic;
    /** The id of the VoIP session*/
    u64 voip_session_id;
    /** The VoIP call id */
    u64 voip_call_id;
    /** The RTP connection ID (flow ID) */
    u64 rtp_connection_id;
    /** The id of the RTP session*/
    u64 rtp_session_id;

    /** The payload type of the RTP packet */
    charset_string encoding_name;
    /** The clock rate of the RTP packet*/
    u32 clock_rate;
    /** The used channels of the RTP packet*/
    u16 channels;

    /** The direction of the packet; 0: from caller, 1: to caller */
    int direction;
    /** The data payload of the RTP packet */
	charset_string data;
    /** The SSRC of the RTP-packet */
    u32 ssrc;
};

#endif                          /* IPD_CLASS_VOIP_DEFINITIONS_H_ */
