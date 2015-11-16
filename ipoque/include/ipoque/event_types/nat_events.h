/********************************************************************************/
/**
 ** \file       nat_events.h
 ** \brief      NAT detection event definitions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef NAT_EVENTS_H
#define NAT_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the NAT event.
 */
#define PACE2_NAT_EVENT_GROUP PACE2_ENGINE_META_DATA_GROUP

/* Event Types ******************************************************************/

/**
 * @brief Types for NAT detection events.
 */
typedef enum {
    PACE2_NAT_MAIN_OS = 0,              /**< NAT main operating system event. */
    PACE2_NAT_DECISION,                 /**< NAT decision event. */

    PACE2_NUMBER_OF_NAT_EVENT_SUBTYPES  /**< number of implemented NAT events. */
} PACE2_NAT_event_type;

/* Event Structures *************************************************************/

/**
 * @brief Data structure for NAT events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_NAT_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_bitmask meta_data_mask;       /**< Bitmask, which states the available NAT meta data. */
    PACE2_OS_type nat_main_os;          /**< Variable for a @ref PACE2_NAT_MAIN_OS event. */
    struct {
        PACE2_boolean detected_nat;     /**< Flag to state that a NAT decision has been made. */
        PACE2_boolean of_source;        /**< Flag to state that the changed NAT flag refers to the source or destination
                                             subscriber. Is @ref IPQ_TRUE for the source subscriber and @ref IPQ_FALSE
                                             for the destination subscriber of the processed packet. */
    } nat_decision;                     /**< Named structure for a @ref PACE2_NAT_DECISION event. */
} PACE2_NAT_event;

#endif /* NAT_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
