/********************************************************************************/
/**
 ** \file       generic_events.h
 ** \brief      Generic PACE 2 event definitions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef GENERIC_EVENTS_H
#define GENERIC_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the flow started event.
 */
#define PACE2_FLOW_STARTED_EVENT_GROUP PACE2_START_GROUP

/**
 * @brief Public define for the assigned meta data group of the flow dropped event.
 */
#define PACE2_FLOW_DROPPED_EVENT_GROUP PACE2_DROP_GROUP

/**
 * @brief Public define for the assigned meta data group of the subscriber started event.
 */
#define PACE2_SUBSCRIBER_STARTED_EVENT_GROUP PACE2_START_GROUP

/**
 * @brief Public define for the assigned meta data group of the subscriber dropped event.
 */
#define PACE2_SUBSCRIBER_DROPPED_EVENT_GROUP PACE2_DROP_GROUP

/**
 * @brief Public define for the assigned meta data group of the flow info event.
 */
#define PACE2_FLOW_INFO_EVENT_GROUP PACE2_START_GROUP

/**
 * @brief Public define for the assigned meta data group of the flow process event.
 */
#define PACE2_FLOW_PROCESS_EVENT_GROUP PACE2_NO_GROUP

/**
 * @brief Public define for the assigned meta data group of the subscriber process event.
 */
#define PACE2_SUBSCRIBER_PROCESS_EVENT_GROUP PACE2_NO_GROUP

/* Event Structures *************************************************************/

/**
 * @brief Placeholder event structure.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_NO_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
} PACE2_no_event;

/**
 * @brief Data structure of flow start events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_FLOW_STARTED_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    u64 flow_id;                /**< flow ID (assigned by PACE2) of this flow */
} PACE2_flow_started;

/**
 * @brief Data structure of flow drop events. One reason for the drop can be a timeout.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_FLOW_DROPPED_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    u64 flow_id;                                        /**< flow ID (assigned by PACE2) of this flow */
    enum pace2_pht_removal_reason removal_reason;       /**< Reason for the drop of this flow. Values can be @ref PACE2_pht_removal_reason  */
} PACE2_flow_dropped;

/**
 * @brief Data structure of flow info events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_FLOW_INFO_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    u64 flow_id;                /**< flow ID (assigned by PACE2) of this flow */
    u64 src_id;                 /**< subscriber id of the source of the first packet in this flow */
    u64 dst_id;                 /**< subscriber id of the destination of the first packet in this flow */
    u16 src_port;               /**< source port of the source of the first packet in this flow, in network byte order.*/
    u16 dst_port;               /**< destination port of the destination of the first packet in this flow, in network byte order. */
} PACE2_flow_info;

/**
 * @brief Data structure of flow process events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_FLOW_PROCESS_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    u64 flow_id;                    /**< flow ID (assigned by PACE2) of this flow */
    u64 bytes;                      /**< accumulated number of transferred payload data (Layer 7) in bytes */
    u64 total_bytes;                /**< accumulated number of overall transferred data in bytes */
    u64 missing_bytes;              /**< accumulated number of missing bytes in TCP flows */
    PACE2_timestamp start_ts;       /**< timestamp of the first packet in this flow */
    PACE2_timestamp last_packet_ts; /**< timestamp of the last seen packet before flow drop */
} PACE2_flow_process;

/**
 * @brief Data structure of subscriber start events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_SUBSCRIBER_STARTED_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    u8 track_dst;                   /**< Tracking direction 0 or 1. */
    void *subscriber_user_data;     /**< Event data of the @ref PACE2_SUBSCRIBER_STARTED_EVENT event. */
    u64 subscriber_id;              /**< ID of the subscriber */
    PACE2_ip_address ip;            /**< The IP address of the subscriber. */
} PACE2_subscriber_started;

/**
 * @brief Data structure of subscriber drop events. One reason for the drop can be a timeout.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_SUBSCRIBER_DROPPED_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    void *subscriber_user_data;                         /**< Event data of the @ref PACE2_SUBSCRIBER_DROPPED_EVENT event. */
    enum pace2_pht_removal_reason removal_reason;       /**< Reason for the drop of this Subscriber entry. Values can be @ref PACE2_pht_removal_reason  */
    u64 subscriber_id;                                  /**< ID of the subscriber */
} PACE2_subscriber_dropped;

/**
 * @brief Data structure of subscriber process events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_FLOW_DROPPED_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    u64 subscriber_id;          /**< subscriber ID (assigned by PACE2) of this subscriber */
    u64 bytes_up;               /**< accumulated number of uploaded data's in bytes */
    u64 bytes_down;             /**< accumulated number of downloaded data's in bytes */
    u64 total_bytes;            /**< accumulated number of transfered data's in bytes */
} PACE2_subscriber_process;

#endif /* GENERIC_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
