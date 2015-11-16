/********************************************************************************/
/**
 ** \file       fastpath_events.h
 ** \brief      Fastpath status event definitions
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef FASTPATH_EVENTS_H
#define FASTPATH_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the fastpath status event.
 */
#define PACE2_FASTPATH_EVENT_GROUP PACE2_NO_GROUP

/* Event Structures *************************************************************/

/**
 * @brief Data structure of a detections fastpath status event.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_FASTPATH_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    struct ipoque_fastpath_information fastpath;/**< Data structure of a @ref PACE2_FASTPATH_EVENT event. */
} PACE2_fastpath_event;

#endif /* FASTPATH_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
