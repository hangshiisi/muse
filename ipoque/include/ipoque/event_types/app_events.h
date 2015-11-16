/********************************************************************************/
/**
 ** \file       app_events.h
 ** \brief      Application event definitions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef APP_EVENTS_H
#define APP_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the application event.
 */
#define PACE2_APPLICATION_EVENT_GROUP PACE2_ENGINE_META_DATA_GROUP

/* Event Structure **************************************************************/

/**
 * @brief Data structure of application events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_APP_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_byte_buffer app_version;      /**< Event data of the @ref PACE2_APP_EVENT event. */
} PACE2_app_event;

#endif /* APP_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
