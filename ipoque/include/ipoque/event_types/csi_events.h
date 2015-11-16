/********************************************************************************/
/**
 ** \file       csi_events.h
 ** \brief      Client server indication event definitions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef CSI_EVENTS_H
#define CSI_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the CSI packet direction event.
 */
#define PACE2_CSI_PACKET_DIR_EVENT_GROUP PACE2_ENGINE_META_DATA_GROUP

/**
 * @brief Public define for the assigned meta data group of the CSI host type event.
 */
#define PACE2_CSI_HOST_TYPE_EVENT_GROUP PACE2_NO_GROUP

/* Event Structures *************************************************************/

/**
 * @brief Data structure for a event of type @ref PACE2_CSI_PACKET_DIR_EVENT.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_CSI_PACKET_DIR_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    enum ipoque_client_server_indication_packet_type packet_dir;    /**< Event data for a @ref PACE2_CSI_PACKET_DIR_EVENT event. */
} PACE2_csi_packet_dir_event;

/**
 * @brief Data structure for a event of type @ref PACE2_CSI_HOST_TYPE_EVENT.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_CSI_HOST_TYPE_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    struct ipoque_pace_client_server_indication_host_status src;    /**< Host status of the source subscriber */
    struct ipoque_pace_client_server_indication_host_status dst;    /**< Host status of the destination subscriber */
} PACE2_csi_host_type_event;

#endif /* CSI_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
