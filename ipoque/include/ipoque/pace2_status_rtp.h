/********************************************************************************/
/**
 ** \file       pace2_status_rtp.h
 ** \brief      PACE 2 module wrapper for RTP performance report functions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef PACE2_STATUS_RTP_H
#define PACE2_STATUS_RTP_H

/* Includes *********************************************************************/
#include "pace2_basic_def.h"
#include "event_types/rtp_events.h"

/* Public Types *****************************************************************/

/**
 * @brief Return state of RTP performance report functions.
 */
typedef enum {
    PACE2_RTP_SUCCESS,                  /**< Function returned successfully, returned data is valid. */
    PACE2_RTP_PARAM_MISSING,            /**< Function parameter is missing. */
    PACE2_RTP_STATS_UNAVAILABLE,        /**< RTP statistics are disabled. */
    PACE2_RTP_UNKNOWN_ERROR             /**< An unknown error occurred. */
} PACE2_RTP_return_state;

/* Public Prototypes ************************************************************/

/**
 * @brief Get the flow statistics for a RTP flow.
 *
 * Get all counter and statistic values of a RTP flow and for each direction.
 *
 * @param[in]   pace2_module      Pointer to the PACE 2 module.
 * @param[in]   thread_ID         Identifier of a thread.
 * @param[in]   packet_descriptor Pointer to the pace2 packet descriptor.
 * @param[out]  rtp_event         Pointer to a variable, which is used to store the received data.
 *                                This variable is a event structure of type @ref PACE2_RTP_event .
 * @retval PACE2_RTP_SUCCESS            @copydoc PACE2_RTP_return_state::PACE2_RTP_SUCCESS
 * @retval PACE2_RTP_PARAM_MISSING      @copydoc PACE2_RTP_return_state::PACE2_RTP_PARAM_MISSING
 * @retval PACE2_RTP_STATS_UNAVAILABLE  @copydoc PACE2_RTP_return_state::PACE2_RTP_STATS_UNAVAILABLE
 * @retval PACE2_RTP_UNKNOWN_ERROR      @copydoc PACE2_RTP_return_state::PACE2_RTP_UNKNOWN_ERROR
 */
PACE2_RTP_return_state pace2_rtp_get_flow_stats(PACE2_module * const pace2_module,
                                                int const thread_ID,
                                                PACE2_packet_descriptor * const packet_descriptor,
                                                PACE2_RTP_event * const rtp_event);

/**
 * @brief Reset packet counters for a RTP flow.
 *
 * @param[in]   pace2_module      Pointer to the PACE 2 module.
 * @param[in]   thread_ID         Identifier of a thread.
 * @param[in]   packet_descriptor Pointer to the pace2 packet descriptor of the flow.
 * @retval PACE2_RTP_SUCCESS            @copydoc PACE2_RTP_return_state::PACE2_RTP_SUCCESS
 * @retval PACE2_RTP_PARAM_MISSING      @copydoc PACE2_RTP_return_state::PACE2_RTP_PARAM_MISSING
 * @retval PACE2_RTP_STATS_UNAVAILABLE  @copydoc PACE2_RTP_return_state::PACE2_RTP_STATS_UNAVAILABLE
 * @retval PACE2_RTP_UNKNOWN_ERROR      @copydoc PACE2_RTP_return_state::PACE2_RTP_UNKNOWN_ERROR
 */
PACE2_RTP_return_state pace2_rtp_reset_flow_stats(PACE2_module * const pace2_module,
                                                  int const thread_ID,
                                                  PACE2_packet_descriptor * const packet_descriptor);

/**
 * @brief Reset internal sequence number state for a RTP flow.
 *
 * @param[in]   pace2_module      Pointer to the PACE 2 module.
 * @param[in]   thread_ID         Identifier of a thread.
 * @param[in]   packet_descriptor Pointer to the pace2 packet descriptor of the flow.
 * @retval PACE2_RTP_SUCCESS            @copydoc PACE2_RTP_return_state::PACE2_RTP_SUCCESS
 * @retval PACE2_RTP_PARAM_MISSING      @copydoc PACE2_RTP_return_state::PACE2_RTP_PARAM_MISSING
 * @retval PACE2_RTP_STATS_UNAVAILABLE  @copydoc PACE2_RTP_return_state::PACE2_RTP_STATS_UNAVAILABLE
 * @retval PACE2_RTP_UNKNOWN_ERROR      @copydoc PACE2_RTP_return_state::PACE2_RTP_UNKNOWN_ERROR
 */
PACE2_RTP_return_state pace2_rtp_reset_flow_sequence_num(PACE2_module * const pace2_module,
                                                         int const thread_ID,
                                                         PACE2_packet_descriptor * const packet_descriptor);

#endif /* PACE2_STATUS_RTP_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
