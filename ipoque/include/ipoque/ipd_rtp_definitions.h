/********************************************************************************/
/**
 ** \file       ipd_rtp_definitions.h
 ** \brief      Structures and enumerations for all events of the RTP Protocol.
 **/
/********************************************************************************/

#ifndef __IPOQUE_DECODER_RTP_INCLUDE_FILE__
#define __IPOQUE_DECODER_RTP_INCLUDE_FILE__

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif

/**
 * Enumeration for simple RTP events.
 */
enum ipd_simple_event_rtp_enumeration
{
    /** Provides a struct ipd_dtmf_tone * with the digit, duration and volume of a event.  */
    IPD_EVENT_RTP_DTMF_SYMBOL,

    IPD_NUMBER_OF_RTP_EVENTS
};

/** Structure wrapping one RTP packet.
 *
 * The meaning of all ID fields depends on the protocol/application that negotiated the addresses and
 * parameters of the RTP flow.
 *
 * See 
 * - \ref dec_doc_sip (for VoIP calls)
 * - \ref dec_doc_yahoo
 * - \ref dec_doc_oscar
 *
 * The #encoding_name, #clock_rate and #channels fields are derived from the payload type of in the packet,
 * using \c rtpmap: lines in the SDP session description used to negotiate this RTP flow. If the packet's
 * payload type was not defined in a session description, these fields are empty or zero.
 */
struct ipd_rtp_data {
    struct ipd_charset_string session_id;    /**< session ID */
	struct ipd_charset_string av_session_id; /**< A/V session ID */
    struct ipd_charset_string sender_id;     /**< ID of the sender of the packet */
    struct ipd_charset_string receiver_id;   /**< ID of the receiver of the packet */
    struct ipd_charset_string data;          /**< UDP payload of the packet */

    struct ipd_charset_string encoding_name; /**< name of encoding */
    u32 clock_rate;                          /**< clock rate  */
    u16 channels;                            /**< number of channels */
};

/**
 * Structure for the SSRC Event that provides the current SSRC and the current direction.
 */
struct ipd_rtp_ssrc {
    struct ipd_charset_string session_id;       /**< session ID */
    struct ipd_charset_string av_session_id;    /**< A/V session ID */
    struct ipd_charset_string sender_id;        /**< ID of the sender of the packet */
    struct ipd_charset_string receiver_id;      /**< ID of the receiver of the packet */
    u32 ssrc;                                   /**< the SSRC which is sent */
    u8 direction;                               /**< the direction of the packet with the SSRC in it */
};

/**
 * Structure for the DTMF event that provides information about the pushed digit.
 */
struct ipd_dtmf_tone
{
    u8  digit;                             /**< pushed digit as ascii character, see ETSI ES 201 235-1 */
    u16 duration;                          /**< event duration of pushing the digit */
    u16 volume;                            /**< if not null, volume of the pushed digit */
};


#endif                          /* __IPOQUE_DECODER_RTP_INCLUDE_FILE__ */
