/********************************************************************************/
/**
 ** \file       tcp_events.h
 ** \brief      TCP meta data event definitions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef TCP_EVENTS_H
#define TCP_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the TCP event.
 */
#define PACE2_TCP_EVENT_GROUP PACE2_POLLING_PROTOCOL_META_DATA_GROUP

/**
 * @brief Public define for the assigned meta data group of the TCP started event.
 */
#define PACE2_TCP_STARTED_EVENT_GROUP PACE2_START_GROUP

/**
 * @brief Public define for the assigned meta data group of the TCP dropped event.
 */
#define PACE2_TCP_CLOSED_EVENT_GROUP PACE2_DROP_GROUP

/* Event Types ******************************************************************/

/**
 * @brief TCP statistic information flags.
 */
enum PACE2_TCP_data_flags {
    PACE2_TCP_LATENCY_STATS = 0,        /**< Latency statistics of a TCP flow. */
    PACE2_TCP_OUT_OF_ORDER_STATS,       /**< Out-of-order statistics of a TCP flow. */
    PACE2_TCP_RETRANSMISSION_STATS,     /**< Global TCP retransmission statistics. */

    PACE2_NUMBER_OF_TCP_DATA_FLAGS      /**< Number of implemented TCP data flags. */
};

/**
 * @brief The reason for a TCP close event
 */
typedef enum pace2_tcp_close_reason {
    TCP_FIN,     /*!< The TCP connection was finished. */
    TCP_RST      /*!< The TCP connection was aborted. */
} PACE2_tcp_close_reason;

/* Event Structures *************************************************************/

/**
 * @brief Event structure of a TCP statistics information event.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_TCP_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_bitmask meta_data_mask;       /**< Bitmask, which states the available TCP statistic information. */
    flow_latency_struct_t latency_stats;                /**< Data structure of the @ref PACE2_TCP_LATENCY_STATS flag. */
    ipoque_flow_ooo_count_struct_t out_of_order_stats;  /**< Data structure of the  @ref PACE2_TCP_OUT_OF_ORDER_STATS flag. */
    u64 retransmission_stats;                           /**< Variable of the @ref PACE2_TCP_RETRANSMISSION_STATS flag */
} PACE2_TCP_event;

/**
 * @brief Event structure of a TCP started event.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_TCP_STARTED_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    u64 flow_id;                /**< flow ID (assigned by PACE2) of this flow */
} PACE2_TCP_started_event;

/**
 * @brief Event structure of a TCP dropped event.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_TCP_CLOSED_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    u64 flow_id;                                  /**< flow ID (assigned by PACE2) of this flow */
    enum pace2_tcp_close_reason close_reason;     /**< Reason for the close of this TCP connection. Values can be @ref PACE2_tcp_close_reason  */
} PACE2_TCP_closed_event;

#endif /* TCP_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
