/********************************************************************************/
/**
 ** \file       rtp_events.h
 ** \brief      RTP performance report event definitions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef RTP_EVENTS_H
#define RTP_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the basic RTP event.
 */
#define PACE2_BASIC_RTP_EVENT_GROUP PACE2_POLLING_PROTOCOL_META_DATA_GROUP

/* Event Types ******************************************************************/

/**
 * @brief PACE 2 type definition for a RTP flow statistic data structure.
 */
typedef struct ipoque_rtp_flow_stats_struct PACE2_RTP_flow_stats;

/**
 * @brief RTP performance report data flags.
 */
enum PACE2_RTP_data_flags {
    PACE2_RTP_FLOW_STATS = 0,    /**< Flow statistics for a RTP flow. */

    PACE2_NUMBER_OF_RTP_DATA_FLAGS      /**< Number of implemented RTP data flags. */
};

/* Event Structures *************************************************************/

/**
 * @brief Event structure of a RTP performance report.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_BASIC_RTP_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_bitmask meta_data_mask;       /**< Bitmask, which states the available RTP performance reports. */
    PACE2_RTP_flow_stats flow_stats;               /**< Data structure of the @ref PACE2_RTP_FLOW_STATS flag.*/
} PACE2_RTP_event;


#endif /* RTP_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
