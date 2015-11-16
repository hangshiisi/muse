/********************************************************************************/
/**
 ** \file       radius_events.h
 ** \brief      Radius stage4 event definitions
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef RADIUS_EVENTS_H
#define RADIUS_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the advanced radius event.
 */
#define PACE2_ADVANCED_RADIUS_EVENT_GROUP PACE2_ADVANCED_PROTOCOL_META_DATA_GROUP

/* Event Types ******************************************************************/

/**
 * @brief Types for advanced radius events.
 */
typedef enum {
    PACE2_ADVANCED_RADIUS_GENERAL_PACKET_INFORMATION ,   /**< @ref IPD_EVENT_RADIUS_GENERAL_PACKET_INFORMATION */
    PACE2_ADVANCED_RADIUS_ATTRIBUTE,                     /**< @ref IPD_EVENT_RADIUS_ATTRIBUTE */

    PACE2_NUMBER_OF_ADVANCED_RADIUS_EVENT_TYPES          /**< Number of implemented event types. */
} PACE2_advanced_Radius_event_type;

/* Event Structures *************************************************************/

#ifndef PACE2_DISABLE_DECODER
/**
 * @brief Data structure for advanced radius events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_ADVANCED_RADIUS_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_advanced_Radius_event_type meta_data_type;    /**< Radius event subtype. */
    PACE2_ADVANCED_META_DATA_EVENT_EXTRA_FIELDS;
    union {
        struct ipd_radius_general_packet_information gpi; /**< Contains data for a @ref PACE2_ADVANCED_RADIUS_GENERAL_PACKET_INFORMATION event. */
        struct ipd_radius_attribute attribute;          /**< Contains data for a @ref PACE2_ADVANCED_RADIUS_ATTRIBUTE event. */
    } event_data;                                       /**< Named union which contains the data of the sub-event types. */
} PACE2_advanced_radius_event;
#endif

#endif /* RADIUS_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
