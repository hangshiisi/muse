/********************************************************************************/
/**
 ** \file       cdd_events.h
 ** \brief      Custom Defined Decoder event body definition
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef CDD_EVENTS_H
#define CDD_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Group ******************************************************************/
/**
 * @brief Public define for the assigned meta data group of custom defined decoder events.
 */
#define PACE2_CUSTOM_DEFINED_DECODER_EVENT_GROUP PACE2_CUSTOM_DEFINED_EVENT_GROUP

#ifndef PACE2_DISABLE_DECODER

/* Event Structures *************************************************************/

/**
 * @brief Data structure for advanced IRC events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_CDD_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;

    u32 cdd_id;                   /*!< ID of the CDD generating the event. */
    u32 cdd_event_id;             /*!< CDD-specific ID of the event. Each different event of a single CDD must have a different cdd_event_id. */
    u8 cdd_data[];                /*!< Data of the CDD event. */
} PACE2_cdd_event;

#endif /* PACE2_DISABLE_DECODER */

#endif /* CDD_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
