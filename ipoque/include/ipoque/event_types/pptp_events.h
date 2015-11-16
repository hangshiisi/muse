/********************************************************************************/
/**
 ** \file       pptp_events.h
 ** \brief      PPTP event definitions
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef PPTP_EVENTS_H
#define PPTP_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the advanced PPTP event.
 */
#define PACE2_ADVANCED_PPTP_EVENT_GROUP PACE2_ADVANCED_PROTOCOL_META_DATA_GROUP

/* Event Types ******************************************************************/

/**
 * @brief Types for advanced PPTP events.
 */
typedef enum {
    PACE2_ADVANCED_PPTP_TUNNEL_SETUP,                 /**< @ref IPD_EVENT_PPTP_TUNNEL_SETUP */
    PACE2_ADVANCED_PPTP_TUNNEL_SHUTDOWN,              /**< @ref IPD_EVENT_PPTP_TUNNEL_SHUTDOWN */
    PACE2_ADVANCED_PPTP_IP_PACKET,                    /**< @ref IPD_EVENT_PPTP_IP_PACKET */

    PACE2_NUMBER_OF_ADVANCED_PPTP_EVENT_TYPES         /**< Number of implemented event types. */
} PACE2_advanced_PPTP_event_type;

/* Event Structures *************************************************************/

#ifndef PACE2_DISABLE_DECODER

/**
 * @brief Data structure for advanced PPTP events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_ADVANCED_HTTP_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_advanced_PPTP_event_type meta_data_type;                  /**< PPTP event subtype. */
    PACE2_ADVANCED_META_DATA_EVENT_EXTRA_FIELDS;
    union {
        struct ipd_tunnelled_ip_packet ip_packet;                   /**< Contains data for a @ref PACE2_ADVANCED_PPTP_TUNNEL_SETUP event. */
        u64 setup;                                                  /**< Contains data for a @ref PACE2_ADVANCED_PPTP_TUNNEL_SHUTDOWN event. */
        u64 shutdown;                                               /**< Contains data for a @ref PACE2_ADVANCED_PPTP_IP_PACKET event. */
    } event_data;                                                   /**< Named union which contains the data of the sub-event types. */
} PACE2_advanced_PPTP_event;

#endif

#endif /* PPTP_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
