/********************************************************************************/
/**
 ** \file       license_events.h
 ** \brief      License event definitions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef LICENSE_EVENTS_H
#define LICENSE_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the license exceeded event.
 */
#define PACE2_LICENSE_EXCEEDED_EVENT_GROUP PACE2_ENGINE_META_DATA_GROUP

/* Event Structures *************************************************************/

/**
 * @brief Data structure of license exceeded events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_LICENSE_EXCEEDED_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    ipoque_pace_license_information_t license;  /**< Data structure which contains the license information. */
} PACE2_license_event;

#endif /* LICENSE_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
