#ifndef __IPOQUE_DECODER_H323_INCLUDE_FILE__
#define __IPOQUE_DECODER_H323_INCLUDE_FILE__

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif

/**
 * Enumeration for the h323 flow states
 */
enum h323_flow_state {
    IPD_H323_FLOW_START,            /**< Signals the idle state of a call (before start). */
    IPD_H323_FLOW_SETUP,            /**< The setup phase of the call (start). */
    IPD_H323_FLOW_CALL_PROCEEDING,  /**< The setup command will be transmitted to the called terminal. */
    IPD_H323_FLOW_ALERTING,         /**< The called terminal is ringing. */
    IPD_H323_FLOW_CONNECT,          /**< The call is established. */
    IPD_H323_FLOW_RELEASE_COMPLETE, /**< The call is shut down (busy, cancel, rejected, finished). */
    IPD_H323_FLOW_EMPTY             /**< Signals a H.245 tunneling in H.225 without a H.225 message. */
};

/**
 * struct for the participants
 */
struct h323_participant_struct {
    struct ipd_charset_string dialed_digits;    /**< dialed digits (e.g. 0123456789) */
    struct ipd_charset_string h323_id;          /**< H.323 id (e.g. nickname) */
    struct ipd_charset_string url_id;           /**< the H.323 url (e.g. name@h323.net) */
    struct ipd_charset_string email_id;         /**< the H.323 email */
};

/**
 * parsed fields from a H323 message and its payload
 * equals the cb data and the dialog-state data
 */
struct h323_state_struct {
    enum h323_flow_state flow_state;            /**< The current state of the H.323 call. */
    struct ipd_charset_string callIdentifier;   /**< The call identfier of the H.323 call. This value is guaranteed in all messages except "Empty" messages. */
    struct h323_participant_struct source;      /**< The source information of the H.323 call. Only the component H.323-Id of this value is guaranteed in all messages. */
    struct h323_participant_struct destination; /**< The destination information of the H.323 call. Only the component H.323-Id of this value is guaranteed in all messages. */
    u8 direction;                               /**< The direction of the current packet respectively the direction of the call (caller -> sender).
                                                  *  The point of usage and a leading 1 will show the difference. */
    u8 h245_tunneling;                          /**< Signals whether the H.245 parts are tunneled in the H.225 packets or not. */
    struct ipd_charset_string h245_address;     /**< The ip address of the H.245 flow. Should be occured only once per side in a  H.323 call. */
    u16 h245_port;                              /**< The port of the H.245 flow. Should be occured only once per side in a  H.323 call. */
    u8 h245_is_ipv6;                            /**< The H.245 is IPv6 or not. */
};

/**
 * H323 decoder event types (used as values of the \c type argument of a \ref ipd_decoder_event_callback function)
 */
enum ipd_simple_event_h323_enumeration
{
    IPD_EVENT_H323_MESSAGE,                 /**< Issued for each decoded H.323 message.  \c data points to a struct
                                             * h323_state_struct. */
    IPD_EVENT_H323_END_OF_FLOW,             /**< Signals connection termination (TCP transport) or flow timeout (UDP, TCP). No data will be passed. */
    IPD_EVENT_H323_INVALID,                 /**< Issued when decoding a message fails.  An error message is passed as a
                                             * <tt>char *</tt> in the \c data argument. */

    IPD_EVENT_H323_RTP_DATA,                /**< Issued for each RTP packet in flows correlated to this H.323 flow.  \c data
                                             * points to a struct ipd_rtp_data. */
    IPD_EVENT_H323_RTP_END_OF_FLOW,         /**< Signals flow timeout of a correlated RTP flow. No data will be passed. */
    IPD_EVENT_H323_RTP_INVALID,             /**< Issued when decoding a packet in a correlated RTP flow fails.  An error
                                             * message is passed as a <tt>char *</tt> in the \c data argument. */
    IPD_EVENT_H323_RTP_SSRC,                /**< Issued when a SSRC value is found. \c data points to a struct ipd_rtp_ssrc. */

    IPD_NUMBER_OF_H323_EVENTS,
};

#endif                          /* __IPOQUE_DECODER_H323_INCLUDE_FILE__ */
