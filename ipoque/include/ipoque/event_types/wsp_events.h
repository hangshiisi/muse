/********************************************************************************/
/**
 ** \file       wsp_events.h
 ** \brief      WAP/WSP stage4 event definitions
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef WSP_EVENTS_H
#define WSP_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the advanced WSP event.
 */
#define PACE2_ADVANCED_WSP_EVENT_GROUP PACE2_ADVANCED_PROTOCOL_META_DATA_GROUP

/* Event Types ******************************************************************/

/**
 * @brief Types for advanced wsp events.
 */
typedef enum {
    PACE2_ADVANCED_WAP_WSP_NEW_CONNECTION ,         /**< @ref IPD_WSP_NEW_CONNECTION */
    PACE2_ADVANCED_WAP_WSP_PDU_HEADER,              /**< @ref IPD_WSP_PDU_HEADER */
    PACE2_ADVANCED_WAP_WSP_PDU_DATA,                /**< @ref IPD_WSP_PDU_DATA */

    PACE2_NUMBER_OF_ADVANCED_WSP_EVENT_TYPES        /**< Number of implemented event types. */
} PACE2_advanced_Wsp_event_type;

/* Event Structures *************************************************************/

#ifndef PACE2_DISABLE_DECODER

/**
 * @brief Data structure for advanced WSP events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_ADVANCED_WAP_WSP_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_advanced_Wsp_event_type meta_data_type;   /**< Wsp event subtype. */
    PACE2_ADVANCED_META_DATA_EVENT_EXTRA_FIELDS;
    union {
        struct ipd_5tuple  new_connection;       /**< Contains data for a @ref PACE2_ADVANCED_WAP_WSP_NEW_CONNECTION event. */
        struct ipd_wsp_pdu_header pdu_header;    /**< Contains data for a @ref PACE2_ADVANCED_WAP_WSP_PDU_HEADER event. */
        struct ipd_wsp_pdu_data pdu_data;        /**< Contains data for a @ref PACE2_ADVANCED_WAP_WSP_PDU_DATA event. */

    } event_data;                                   /**< Named union which contains the data of the sub-event types. */
} PACE2_advanced_wsp_event;

#endif

#endif /* WSP_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
