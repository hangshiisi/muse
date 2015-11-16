/********************************************************************************/
/**
 ** \file       dissector_metadata_events.h
 ** \brief      Dissector metadata event definitions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef DISSECTOR_METADATA_EVENTS_H
#define DISSECTOR_METADATA_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the dissector metadata event.
 */
#define PACE2_DISSECTOR_METADATA_EVENT_GROUP PACE2_BASIC_PROTOCOL_META_DATA_GROUP

/* Event Structure **************************************************************/

/**
 * @brief Data structure of KPI metadata events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_BASIC_DISSECTOR_METADATA_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    enum dissector_metadata_type metadata_type;       /**< Event data of the @ref PACE2_BASIC_DISSECTOR_METADATA_EVENT event. */
    union dissector_result metadata;                  /**< Event meta data */
} PACE2_dissector_metadata_event;

#endif /* DISSECTOR_METADATA_EVENTS_H */
/*********************************************************************************
 ** EOF
 ********************************************************************************/
