/********************************************************************************/
/**
 ** \file       diameter_events.h
 ** \brief      Diameter stage4 event definitions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef DIAMETER_EVENTS_H
#define DIAMETER_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the advanced Diameter event.
 */
#define PACE2_ADVANCED_DIAMETER_EVENT_GROUP PACE2_ADVANCED_PROTOCOL_META_DATA_GROUP

/* Event Types ******************************************************************/

/**
 * @brief Types for advanced diameter events.
 */
typedef enum {
    PACE2_ADVANCED_DIAMETER_GENERAL_PACKET_INFORMATION,   /**< @ref IPD_EVENT_DIAMETER_GENERAL_PACKET_INFORMATION */
    PACE2_ADVANCED_DIAMETER_ATTRIBUTE,                    /**< @ref IPD_EVENT_DIAMETER_ATTRIBUTE */
    PACE2_ADVANCED_DIAMETER_INVALID,                      /**< @ref IPD_EVENT_DIAMETER_INVALID */
    PACE2_ADVANCED_DIAMETER_CONNECTION_TERMINATION,       /**< @ref IPD_EVENT_DIAMETER_CONNECTION_TERMINATION */
    PACE2_ADVANCED_DIAMETER_MESSAGE_TERMINATION,          /**< @ref IPD_EVENT_DIAMETER_MESSAGE_TERMINATION */

    PACE2_NUMBER_OF_ADVANCED_DIAMETER_EVENT_TYPES         /**< Number of implemented event types. */
} PACE2_advanced_Diameter_event_type;

/* Event Structures *************************************************************/

#ifndef PACE2_DISABLE_DECODER

/**
 * @brief Data structure for advanced diameter events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_ADVANCED_DIAMETER_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_advanced_Diameter_event_type meta_data_type;  /**< Diameter event subtype. */
    PACE2_ADVANCED_META_DATA_EVENT_EXTRA_FIELDS;
    union {
        struct ipd_diameter_general_packet_information gpi; /**< Contains data for a @ref PACE2_ADVANCED_DIAMETER_GENERAL_PACKET_INFORMATION event. */
        struct ipd_diameter_avp_information attribute;      /**< Contains data for a @ref PACE2_ADVANCED_DIAMETER_ATTRIBUTE event. */
        const char *invalid;                                /**< Contains data for a @ref PACE2_ADVANCED_DIAMETER_INVALID event. */
        struct ipd_diameter_connection_end conection_end;   /**< Contains data for a @ref PACE2_ADVANCED_DIAMETER_CONNECTION_TERMINATION event. */
        struct ipd_diameter_message_end message_end;        /**< Contains data for a @ref PACE2_ADVANCED_DIAMETER_MESSAGE_TERMINATION event. */
    } event_data;                                       /**< Named union which contains the data of the sub-event types. */
} PACE2_advanced_Diameter_event;

#endif

#endif /* DIAMETER_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
