/********************************************************************************/
/**
 ** \file       ipd_pptp_definitions.h
 ** \brief      Structures and enumerations for all events of the PPTP Protocol.
 **/
/********************************************************************************/

#ifndef __IPOQUE_DECODER_PPTP_INCLUDE_FILE__
#define __IPOQUE_DECODER_PPTP_INCLUDE_FILE__

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif

/** PPTP decoder event types (used as values of the \c type argument of a \ref ipd_decoder_event_callback function)
 */
enum ipd_simple_event_pptp_enumeration
{
	/** sent for each PPTP tunnel that is set up; \c data points to a */
    IPD_EVENT_PPTP_TUNNEL_SETUP,	/**< u64 *. */
	/** sent for each PPTP tunnel that is shut down; \c data points to a */
    IPD_EVENT_PPTP_TUNNEL_SHUTDOWN,	/**< u64 *. */

	/** sent for each IP packet that is decoded from a PPTP tunnel; \c data points to a */
    IPD_EVENT_PPTP_IP_PACKET,		/**< struct ipd_tunnelled_ip_packet *. */

    IPD_NUMBER_OF_PPTP_EVENTS,
};

#endif /* __IPOQUE_DECODER_PPTP_INCLUDE_FILE__ */
