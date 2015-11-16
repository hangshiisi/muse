/********************************************************************************/
/**
 ** \file       pace2_status_fastpath.h
 ** \brief      PACE 2 module wrapper for the classification fastpath status functions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef PACE2_STATUS_FASTPATH_H
#define PACE2_STATUS_FASTPATH_H

/* Includes *********************************************************************/
#include "pace2_basic_def.h"
#include "event_types/fastpath_events.h"

/* Public Types *****************************************************************/

/**
 * @brief Return state of classification fastpath status functions.
 */
typedef enum {
    PACE2_FP_SUCCESS = 0,               /**< Function returned successfully, returned data is valid. */
    PACE2_FP_PARAM_MISSING,             /**< Function parameter is missing. */
    PACE2_FP_STAT_UNAVAILABLE,          /**< Status isn't available. */
    PACE2_FP_UNKNOWN_ERROR              /**< An unknown error occurred */
} PACE2_fastpath_return_state;

/* Public Prototypes ************************************************************/

/**
 * @brief Get the fastpath information of the last packet.
 *
 * This function returns the fastpath information of the last packet processed by the classification stage.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       Identifier of a thread.
 * @param[out]  fp_event        Pointer to a variable, which is used to store the received data.
 *                              This variable is a event structure of type @ref PACE2_fastpath_event .
 * @retval PACE2_FP_SUCCESS            @copydoc PACE2_fastpath_return_state::PACE2_FP_SUCCESS
 * @retval PACE2_FP_PARAM_MISSING      @copydoc PACE2_fastpath_return_state::PACE2_FP_PARAM_MISSING
 * @retval PACE2_FP_STAT_UNAVAILABLE   @copydoc PACE2_fastpath_return_state::PACE2_FP_STAT_UNAVAILABLE
 *                                     \arg The fastpath is disabled.
 * @retval PACE2_FP_UNKNOWN_ERROR      @copydoc PACE2_fastpath_return_state::PACE2_FP_UNKNOWN_ERROR
 */
PACE2_fastpath_return_state pace2_fastpath_get_status(PACE2_module * const pace2_module,
                                                      int const thread_ID,
                                                      PACE2_fastpath_event * const fp_event);

#endif /* PACE2_STATUS_FASTPATH_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
