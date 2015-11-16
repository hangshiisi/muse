/********************************************************************************/
/**
 ** \file       rtcp_events.h
 ** \brief      RTCP report event definitions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef RTCP_EVENTS_H
#define RTCP_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the basic RTCP event.
 */
#define PACE2_BASIC_RTCP_EVENT_GROUP PACE2_POLLING_PROTOCOL_META_DATA_GROUP

/* Event Types ******************************************************************/

/**
 * @brief PACE 2 type definition for a RTPC report data structure.
 */
typedef struct ipoque_rtcp_reception_report_struct PACE2_RTPC_report;

/* Event Structures *************************************************************/

/**
 * @brief Structure of a RTCP report event.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_BASIC_RTCP_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_RTPC_report rtcp_report;      /**< Event data of the @ref PACE2_BASIC_RTCP_EVENT event. */
} PACE2_RTCP_event;


#endif /* RTCP_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
