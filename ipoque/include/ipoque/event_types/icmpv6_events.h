/********************************************************************************/
/**
 ** \file       icmpv6_events.h
 ** \brief      ICMPv6 stage4 event definitions
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef ICMPV6_EVENTS_H
#define ICMPV6_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the advanced ICMPv6 event.
 */
#define PACE2_ADVANCED_ICMPV6_EVENT_GROUP PACE2_ADVANCED_PROTOCOL_META_DATA_GROUP

/* Event Types ******************************************************************/

/**
 * @brief Types for advanced icmpv6 events.
 */
typedef enum {
    PACE2_ADVANCED_ICMPV6_ROUTER_SOLICIT,               /**< @ref IPD_EVENT_ICMPV6_ROUTER_SOLICIT */
    PACE2_ADVANCED_ICMPV6_ROUTER_ADVERT,                /**< @ref IPD_EVENT_ICMPV6_ROUTER_ADVERT */
    PACE2_ADVANCED_ICMPV6_NEIGHBOR_SOLICIT,             /**< @ref IPD_EVENT_ICMPV6_NEIGHBOR_SOLICIT */
    PACE2_ADVANCED_ICMPV6_NEIGHBOR_ADVERT,              /**< @ref IPD_EVENT_ICMPV6_NEIGHBOR_ADVERT */
    PACE2_ADVANCED_ICMPV6_REDIRECT,                     /**< @ref IPD_EVENT_ICMPV6_REDIRECT */

    PACE2_NUMBER_OF_ADVANCED_ICMPV6_EVENT_TYPES         /**< Number of implemented event types. */
} PACE2_advanced_icmpv6_event_type;

/* Event Structures *************************************************************/

#ifndef PACE2_DISABLE_DECODER

/**
 * @brief Data structure for advanced icmpv6 events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_ADVANCED_ICMPV6_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_advanced_icmpv6_event_type meta_data_type;    /**< ICMPv6 event subtype. */
    PACE2_ADVANCED_META_DATA_EVENT_EXTRA_FIELDS;
    union {
        struct ipd_icmpv6_router_solicit router_sol;    /**< Contains data for a @ref PACE2_ADVANCED_ICMPV6_ROUTER_SOLICIT event. */
        struct ipd_icmpv6_router_advert router_adv;     /**< Contains data for a @ref PACE2_ADVANCED_ICMPV6_ROUTER_ADVERT event. */
        struct ipd_icmpv6_neighbor_solicit neig_sol;    /**< Contains data for a @ref PACE2_ADVANCED_ICMPV6_NEIGHBOR_SOLICIT event. */
        struct ipd_icmpv6_neighbor_advert neig_adv;     /**< Contains data for a @ref PACE2_ADVANCED_ICMPV6_NEIGHBOR_ADVERT event. */
        struct ipd_icmpv6_redirect redirect;            /**< Contains data for a @ref PACE2_ADVANCED_ICMPV6_REDIRECT event. */
    } event_data;                                       /**< Named union which contains the data of the sub-event types. */
} PACE2_advanced_icmpv6_event;

#endif

#endif /* ICMPV6_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
