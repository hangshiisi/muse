/********************************************************************************/
/**
 ** \file       pace2_status_tcp.h
 ** \brief      PACE 2 module wrapper for TCP statistic information functions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef PACE2_STATUS_TCP_H
#define PACE2_STATUS_TCP_H

/* Includes *********************************************************************/
#include "pace2_basic_def.h"
#include "event_types/tcp_events.h"

/* Public Types *****************************************************************/

/**
 * @brief Return state of TCP meta data functions.
 */
typedef enum {
    PACE2_TCP_SUCCESS = 0,              /**< Function returned successfully, returned data is valid. */
    PACE2_TCP_PARAM_MISSING,            /**< Function parameter is missing. */
    PACE2_TCP_STATS_UNAVAILABLE,        /**< TCP statistic information isn't available. */
    PACE2_TCP_STATS_DISABLED,           /**< TCP statistics are disabled. */
    PACE2_TCP_UNKNOWN_ERROR             /**< An unknown error occurred. */
} PACE2_TCP_return_state;

/* Public Prototypes ************************************************************/

/**
 * @brief Get the latency statistics of a TCP flow process by the classification stage.
 *
 * This function returns the latency statistics of the flow for a specified packet descriptor.
 *
 * @param[in]   pace2_module      Pointer to the PACE 2 module.
 * @param[in]   thread_ID         Identifier of a thread.
 * @param[in]   packet_descriptor Pointer to the pace2 packet descriptor.
 * @param[out]  tcp_event         Pointer to a variable, which is used to store the received data.
 *                                This variable is a event structure of type @ref PACE2_TCP_event .
 * @retval PACE2_TCP_SUCCESS            @copydoc PACE2_TCP_return_state::PACE2_TCP_SUCCESS
 * @retval PACE2_TCP_PARAM_MISSING      @copydoc PACE2_TCP_return_state::PACE2_TCP_PARAM_MISSING
 * @retval PACE2_TCP_STATS_UNAVAILABLE  @copydoc PACE2_TCP_return_state::PACE2_TCP_STATS_UNAVAILABLE
 *                                      \arg The flow isn't a TCP flow or the TCP handshake wasn't seen.
 * @retval PACE2_TCP_STATS_DISABLED     @copydoc PACE2_TCP_return_state::PACE2_TCP_STATS_DISABLED
 * @retval PACE2_TCP_UNKNOWN_ERROR      @copydoc PACE2_TCP_return_state::PACE2_TCP_UNKNOWN_ERROR
 *                                      \arg Flow data isn't available.
 */
PACE2_TCP_return_state pace2_tcp_get_latency_stats(PACE2_module * const pace2_module,
                                                   int const thread_ID,
                                                   PACE2_packet_descriptor * const packet_descriptor,
                                                   PACE2_TCP_event * const tcp_event);

/**
 * @brief Get the out-of-order statistics of the last TCP flow process by the classification stage.
 *
 * This function returns the out-of-order and retransmission counter values of the last TCP flow
 * processed by the detection.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       Identifier of a thread.
 * @param[out]  tcp_event       Pointer to a variable, which is used to store the received data.
 *                              This variable is a event structure of type @ref PACE2_TCP_event .
 * @retval PACE2_TCP_SUCCESS            @copydoc PACE2_TCP_return_state::PACE2_TCP_SUCCESS
 * @retval PACE2_TCP_PARAM_MISSING      @copydoc PACE2_TCP_return_state::PACE2_TCP_PARAM_MISSING
 * @retval PACE2_TCP_STATS_UNAVAILABLE  @copydoc PACE2_TCP_return_state::PACE2_TCP_STATS_UNAVAILABLE
 * @retval PACE2_TCP_STATS_DISABLED     @copydoc PACE2_TCP_return_state::PACE2_TCP_STATS_DISABLED
 */
PACE2_TCP_return_state pace2_tcp_get_out_of_order_stats(PACE2_module * const pace2_module,
                                                        int const thread_ID,
                                                        PACE2_TCP_event * const tcp_event);

/**
 * @brief Get the global TCP retransmission statistics of the classification stage.
 *
 * This function returns the number of all TCP packets, which are retransmitted.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       Identifier of a thread.
 * @param[out]  tcp_event       Pointer to a variable, which is used to store the received data.
 *                              This variable is a event structure of type @ref PACE2_TCP_event .
 * @retval PACE2_TCP_SUCCESS            @copydoc PACE2_TCP_return_state::PACE2_TCP_SUCCESS
 * @retval PACE2_TCP_PARAM_MISSING      @copydoc PACE2_TCP_return_state::PACE2_TCP_PARAM_MISSING
 * @retval PACE2_TCP_STATS_DISABLED     @copydoc PACE2_TCP_return_state::PACE2_TCP_STATS_DISABLED
 */
PACE2_TCP_return_state pace2_tcp_get_restransmission_stats(PACE2_module * const pace2_module,
                                                           int const thread_ID,
                                                           PACE2_TCP_event * const tcp_event);

#endif /* PACE2_STATUS_TCP_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
