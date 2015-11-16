/********************************************************************************/
/**
 ** \file       pace2_status_sit.h
 ** \brief      PACE 2 module wrapper for the SSL session id tracker (SIT) status functions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef PACE2_STATUS_SIT_H
#define PACE2_STATUS_SIT_H

/* Includes *********************************************************************/
#include "pace2_basic_def.h"
#include "event_types/sit_events.h"

/* Public Types *****************************************************************/

/**
 * @brief Return state of SIT statistics function.
 */
typedef enum {
    PACE2_SIT_SUCCESS = 0,              /**< Function returned successfully, returned data is valid. */
    PACE2_SIT_PARAM_MISSING,            /**< Function parameter is missing. */
    PACE2_SIT_STAT_UNAVAILABLE,         /**< Statistics are not available. */
} PACE2_SIT_return_state;

/* Public Prototypes ************************************************************/

/**
 * @brief Get the current statistics of the classification SSL session id tracker.
 *
 * This function returns the statistic information of the SSL session id tracker.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       Identifier of a thread.
 * @param[out]  sit_event       Pointer to a variable, which is used to store the received data.
 *                              This variable is a event structure of type @ref PACE2_SIT_event .
 * @retval PACE2_SIT_SUCCESS            @copydoc PACE2_SIT_return_state::PACE2_SIT_SUCCESS
 * @retval PACE2_SIT_PARAM_MISSING      @copydoc PACE2_SIT_return_state::PACE2_SIT_PARAM_MISSING
 * @retval PACE2_SIT_STAT_UNAVAILABLE   @copydoc PACE2_SIT_return_state::PACE2_SIT_STAT_UNAVAILABLE
 */
PACE2_SIT_return_state pace2_sit_get_statistics(PACE2_module * const pace2_module,
                                                int const thread_ID,
                                                PACE2_SIT_event * const sit_event);

#endif /* PACE2_STATUS_SIT_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
