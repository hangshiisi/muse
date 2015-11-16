/********************************************************************************/
/**
 ** \file       ipd_l2tp_definitions.h
 ** \brief      Enumeration for the L2TP Protocol Events.
 **/
/********************************************************************************/

#ifndef __IPOQUE_DECODER_L2TP_INCLUDE_FILE__
#define __IPOQUE_DECODER_L2TP_INCLUDE_FILE__

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif

/** L2TP decoder event types (used as values of the \c type argument of a \ref ipd_decoder_event_callback function)
 */
enum ipd_simple_event_l2tp_enumeration
{
	/** sent for each L2TP tunnel that is set up ; \c data points to a */
    IPD_EVENT_L2TP_TUNNEL_SETUP,	/**< u64 *. */
	/** sent for each L2TP tunnel that is shut down ; \c data points to a */
    IPD_EVENT_L2TP_TUNNEL_SHUTDOWN,	/**< u64 *. */

	/** sent for each IP packet that is decoded from a L2TP tunnel ; \c data points to a */
    IPD_EVENT_L2TP_IP_PACKET,		/**< struct struct ipd_tunnelled_ip_packet *. */

    IPD_NUMBER_OF_L2TP_EVENTS,
};

#endif                          /* __IPOQUE_DECODER_L2TP_INCLUDE_FILE__ */
