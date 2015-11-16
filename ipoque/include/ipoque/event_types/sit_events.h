/********************************************************************************/
/**
 ** \file       sit_events.h
 ** \brief      SSL session ID tracker (SIT) event definitions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef SIT_EVENTS_H
#define SIT_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the SIT event.
 */
#define PACE2_BASIC_SIT_EVENT_GROUP PACE2_NO_GROUP

/* Event Types ******************************************************************/

/**
 * @brief PACE 2 type definition for a SIT statistic data structure.
 */
typedef struct ipoque_pace_sit_stats PACE2_SIT_stats;

/* Event Structures *************************************************************/

/**
 * @brief Data structure for SIT events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_BASIC_SIT_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_SIT_stats sit_stats;      /**< Event data of the @ref PACE2_BASIC_SIT_EVENT event.*/
} PACE2_SIT_event;

#endif /* SIT_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
