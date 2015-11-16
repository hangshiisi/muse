/********************************************************************************/
/**
 ** \file       pace2_status_csi.h
 ** \brief      PACE 2 module wrapper for client-server indication status functions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef PACE2_STATUS_CSI_H
#define PACE2_STATUS_CSI_H

/* Includes *********************************************************************/
#include "pace2_basic_def.h"
#include "event_types/csi_events.h"

/* Public Types *****************************************************************/

/**
 * @brief Return state of client-server indication functions.
 */
typedef enum {
    PACE2_CSI_SUCCESS = 0,              /**< Function returned successfully, returned data is valid. */
    PACE2_CSI_MODULE_DISABLED,          /**< CSI module is disabled. */
    PACE2_CSI_PARAM_MISSING,            /**< Function parameter is missing. */
    PACE2_CSI_FASTPATH_USED,            /**< The fastpath of the detection  was used, requested data is not available. */
    PACE2_CSI_NOT_AVAILABLE             /**< The client-server indication is not available. */
} PACE2_CSI_return_state;

/* Public Prototypes ************************************************************/

/**
 * @brief Get direction of the last processed packet.
 *
 * This function returns the direction information for the last packet given to the classification stage.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       Identifier of a thread.
 * @param[out]  csi_event       Pointer to a variable, which is used to store the received data.
 *                              This variable is a event structure of type @ref PACE2_csi_packet_dir_event .
 * @retval PACE2_CSI_SUCCESS            @copydoc PACE2_CSI_return_state::PACE2_CSI_SUCCESS
 * @retval PACE2_CSI_MODULE_DISABLED    @copydoc PACE2_CSI_return_state::PACE2_CSI_MODULE_DISABLED
 * @retval PACE2_CSI_PARAM_MISSING      @copydoc PACE2_CSI_return_state::PACE2_CSI_PARAM_MISSING
 * @retval PACE2_CSI_FASTPATH_USED      @copydoc PACE2_CSI_return_state::PACE2_CSI_FASTPATH_USED
 * @retval PACE2_CSI_NOT_AVAILABLE      @copydoc PACE2_CSI_return_state::PACE2_CSI_NOT_AVAILABLE
 */
PACE2_CSI_return_state pace2_csi_get_packet_direction(PACE2_module * const pace2_module,
                                                      int const thread_ID,
                                                      PACE2_csi_packet_dir_event * const csi_event);

/**
 * @brief Get information about subscribers of the last processed packet.
 *
 * This function returns information about both subscribers of the last packet given to the classification stage.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       Identifier of a thread
 * @param[out]  csi_event       Pointer to a variable, which is used to store the received data.
 *                              This variable contains a event structure of type @ref PACE2_csi_host_type_event .
 * @retval PACE2_CSI_SUCCESS            @copydoc PACE2_CSI_return_state::PACE2_CSI_SUCCESS
 * @retval PACE2_CSI_MODULE_DISABLED    @copydoc PACE2_CSI_return_state::PACE2_CSI_MODULE_DISABLED
 * @retval PACE2_CSI_PARAM_MISSING      @copydoc PACE2_CSI_return_state::PACE2_CSI_PARAM_MISSING
 * @retval PACE2_CSI_FASTPATH_USED      @copydoc PACE2_CSI_return_state::PACE2_CSI_FASTPATH_USED
 * @retval PACE2_CSI_NOT_AVAILABLE      @copydoc PACE2_CSI_return_state::PACE2_CSI_NOT_AVAILABLE
 */
PACE2_CSI_return_state pace2_csi_get_host_type(PACE2_module * const pace2_module,
                                               int const thread_ID,
                                               PACE2_csi_host_type_event * const csi_event);

#endif /* PACE2_STATUS_CSI_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
