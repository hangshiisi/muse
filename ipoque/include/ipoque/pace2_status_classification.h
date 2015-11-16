/********************************************************************************/
/**
 ** \file       pace2_status_classification.h
 ** \brief      PACE 2 module wrapper for classification status functions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef PACE2_STATUS_CLASSIFICATION_H
#define PACE2_STATUS_CLASSIFICATION_H

/* Includes *********************************************************************/
#include "pace2_basic_def.h"
#include "event_types/classification_events.h"

/* Public Types *****************************************************************/

/**
 * @brief Return state of classification status functions.
 */
typedef enum {
    PACE2_CLASS_SUCCESS = 0,            /**< Function returned successfully, returned data is valid. */
    PACE2_CLASS_PARAM_MISSING,          /**< Function parameter is missing. */
    PACE2_CLASS_STAT_UNAVAILABLE,       /**< Status is not available. */
    PACE2_CLASS_UNKNOWN_ERROR           /**< An unknown error occurred */
} PACE2_class_return_state;

/* Public Prototypes ************************************************************/

/**
 * @brief Get the detections API version number.
 *
 * This function returns the API version number of the main library.
 * The API version will be increased if the API has been changed.
 *
 * @param[out]  class_event     Pointer to a variable, which is used to store the received data.
 *                              This variable is a event structure of type @ref PACE2_classification_status_event.
 * @retval PACE2_CLASS_SUCCESS          @copydoc PACE2_class_return_state::PACE2_CLASS_SUCCESS
 * @retval PACE2_CLASS_PARAM_MISSING    @copydoc PACE2_class_return_state::PACE2_CLASS_PARAM_MISSING
 */
PACE2_class_return_state pace2_class_get_api_version(PACE2_classification_status_event * const class_event);

/**
 * @brief Get the detections release version number.
 *
 * This function returns the release version number of the library. If dynamic upgrade is enabled,
 * it's the version of the active library, otherwise it's the version of the main library.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       Identifier of a thread.
 * @param[out]  class_event     Pointer to a variable, which is used to store the received data.
 *                              This variable is a event structure of type @ref PACE2_classification_status_event.
 * @retval PACE2_CLASS_SUCCESS          @copydoc PACE2_class_return_state::PACE2_CLASS_SUCCESS
 * @retval PACE2_CLASS_PARAM_MISSING    @copydoc PACE2_class_return_state::PACE2_CLASS_PARAM_MISSING
 * @retval PACE2_CLASS_UNKNOWN_ERROR    @copydoc PACE2_class_return_state::PACE2_CLASS_UNKNOWN_ERROR
 */
PACE2_class_return_state pace2_class_get_version(PACE2_module * const pace2_module,
                                                 int const thread_ID,
                                                 PACE2_classification_status_event * const class_event);

/**
 * @brief Get the classifications license information.
 *
 * This function returns the license information of the classification.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       Identifier of a thread.
 * @param[out]  class_event     Pointer to a variable, which is used to store the received data.
 *                              This variable is a event structure of type @ref PACE2_classification_status_event.
 * @retval PACE2_CLASS_SUCCESS          @copydoc PACE2_class_return_state::PACE2_CLASS_SUCCESS
 * @retval PACE2_CLASS_PARAM_MISSING    @copydoc PACE2_class_return_state::PACE2_CLASS_PARAM_MISSING
 * @retval PACE2_CLASS_STAT_UNAVAILABLE @copydoc PACE2_class_return_state::PACE2_CLASS_STAT_UNAVAILABLE
 *                                      \arg Licensing is disabled.
 * @retval PACE2_CLASS_UNKNOWN_ERROR    @copydoc PACE2_class_return_state::PACE2_CLASS_UNKNOWN_ERROR
 */
PACE2_class_return_state pace2_class_get_license(PACE2_module * const pace2_module,
                                                 int const thread_ID,
                                                 PACE2_classification_status_event * const class_event);

#endif /* PACE2_STATUS_CLASSIFICATION_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
