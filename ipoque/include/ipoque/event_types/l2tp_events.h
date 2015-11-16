/********************************************************************************/
/**
 ** \file       l2tp_events.h
 ** \brief      L2TP stage4 event definitions
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef L2TP_EVENTS_H
#define L2TP_EVENTS_H

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the advanced L2TP event.
 */
#define PACE2_ADVANCED_L2TP_EVENT_GROUP PACE2_ADVANCED_PROTOCOL_META_DATA_GROUP

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Types ******************************************************************/

/**
 * @brief Types for advanced L2TP events.
 */
typedef enum {
    PACE2_ADVANCED_L2TP_TUNNEL_SETUP,           /**< @ref IPD_EVENT_L2TP_TUNNEL_SETUP */
    PACE2_ADVANCED_L2TP_TUNNEL_SHUTDOWN,        /**< @ref IPD_EVENT_L2TP_TUNNEL_SHUTDOWN */
    PACE2_ADVANCED_L2TP_IP_PACKET,              /**< @ref IPD_EVENT_L2TP_IP_PACKET */

    PACE2_NUMBER_OF_ADVANCED_L2TP_EVENT_TYPES   /**< Number of implemented event types. */
} PACE2_advanced_l2tp_event_type;

/* Event Structures *************************************************************/

#ifndef PACE2_DISABLE_DECODER

/**
 * @brief Data structure for advanced L2TP events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_ADVANCED_L2TP_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_advanced_l2tp_event_type meta_data_type;      /**< L2TP event subtype. */
    PACE2_ADVANCED_META_DATA_EVENT_EXTRA_FIELDS;
    union {
        u64 setup;                                      /**< Contains data for a @ref PACE2_ADVANCED_L2TP_TUNNEL_SETUP event. */
        u64 shutdown;                                   /**< Contains data for a @ref PACE2_ADVANCED_L2TP_TUNNEL_SHUTDOW event. */
        struct ipd_tunnelled_ip_packet ip_packet;       /**< Contains data for a @ref PACE2_ADVANCED_L2TP_IP_PACKET event. */
    } event_data;                                       /**< Named union which contains the data of the sub-event types. */
} PACE2_advanced_l2tp_event;

#endif

#endif /* L2TP_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
