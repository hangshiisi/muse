/********************************************************************************/
/**
 ** \file       telnet_events.h
 ** \brief      Telnet meta data event definitions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef TELNET_EVENTS_H
#define TELNET_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Group ******************************************************************/
/**
 * @brief Public define for the assigned meta data group of the advanced telnet events.
 */
#define PACE2_ADVANCED_TELNET_EVENT_GROUP PACE2_ADVANCED_PROTOCOL_META_DATA_GROUP

/* Event Flags ******************************************************************/

/**
 * @brief Telnet meta data flags.
 */
typedef enum {
    PACE2_ADVANCED_TELNET_NEW_CONNECTION = 0,   /**< @ref IPD_EVENT_TELNET_NEW_CONNECTION */
    PACE2_ADVANCED_TELNET_END_OF_FLOW,          /**< @ref IPD_EVENT_TELNET_END_OF_FLOW */
    PACE2_ADVANCED_TELNET_INVALID,              /**< @ref IPD_EVENT_TELNET_INVALID */
    PACE2_ADVANCED_TELNET_COMMAND,              /**< @ref IPD_EVENT_TELNET_COMMAND */
    PACE2_ADVANCED_TELNET_MARKED_COMMAND,       /**< @ref IPD_EVENT_TELNET_NEW_CONNECTION */
    PACE2_ADVANCED_TELNET_DATA,                 /**< @ref IPD_EVENT_TELNET_DATA */

    PACE2_NUMBER_OF_ADVANCED_TELNET_EVENTS      /**< Number of implemented event types. */
} PACE2_advanced_telnet_event_type;

/* Event Structures *************************************************************/

#ifndef PACE2_DISABLE_DECODER

/**
 * @brief Data structure for advanced telnet events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_ADVANCED_TELNET_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_advanced_telnet_event_type meta_data_type;           /**< Telnet event subtype. */
    PACE2_ADVANCED_META_DATA_EVENT_EXTRA_FIELDS;
    union {
        const char* invalid;                                 /**< Contains data for a @ref PACE2_ADVANCED_TELNET_INVALID event. */
        struct ipd_telnet_command command;                   /**< Contains data for a @ref PACE2_ADVANCED_TELNET_COMMAND event. */
        struct ipd_telnet_marked_command marked_command;     /**< Contains data for a @ref PACE2_ADVANCED_TELNET_MARKED_COMMAND event. */
        struct ipd_telnet_data data;                         /**< Contains data for a @ref PACE2_ADVANCED_TELNET_DATA event. */
    } event_data;
} PACE2_advanced_telnet_event;

#endif

#endif // TELNET_EVENTS_H

/*********************************************************************************
 ** EOF
 ********************************************************************************/
