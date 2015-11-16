/********************************************************************************/
/**
 ** \file       pace2_status_rtcp.h
 ** \brief      PACE 2 module wrapper for RTCP report functions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef PACE2_STATUS_RTCP_H
#define PACE2_STATUS_RTCP_H

/* Includes *********************************************************************/
#include "pace2_basic_def.h"
#include "event_types/rtcp_events.h"

/* Public Types *****************************************************************/

/**
 * @brief Return state of RTP performance report functions.
 */
typedef enum {
    PACE2_RTCP_SUCCESS,                 /**< Function returned successfully, returned data is valid. */
    PACE2_RTCP_PARAM_MISSING,           /**< Function parameter is missing. */
    PACE2_RTCP_STATS_UNAVAILABLE,       /**< RTCP reports are disabled. */
} PACE2_RTCP_return_state;

/* Public Prototypes ************************************************************/

/**
 * @brief Get the RTCP sender report or receiver report of a RTCP packet process by the classification stage.
 *
 * If the current packet is an RTCP sender report or receiver report packet, save the packet's direction
 * and the LSR and DLSR fields from the first reception report block to output data structure.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       Identifier of a thread.
 * @param[out]  rtcp_event      Pointer to a variable, which is used to store the received data.
 *                              This variable is a event structure of type @ref PACE2_RTP_event .
 * @retval PACE2_RTCP_SUCCESS           @copydoc PACE2_RTCP_return_state::PACE2_RTCP_SUCCESS
 * @retval PACE2_RTCP_PARAM_MISSING     @copydoc PACE2_RTCP_return_state::PACE2_RTCP_PARAM_MISSING
 * @retval PACE2_RTCP_STATS_UNAVAILABLE @copydoc PACE2_RTCP_return_state::PACE2_RTCP_STATS_UNAVAILABLE
 */
PACE2_RTCP_return_state pace2_rtcp_get_report(PACE2_module * const pace2_module,
                                              int const thread_ID,
                                              PACE2_RTCP_event * const rtcp_event);

#endif /* PACE2_STATUS_RTCP_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
