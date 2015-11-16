/********************************************************************************/
/**
 ** \file       pace2_status_dhcp.h
 ** \brief      PACE 2 module wrapper for DHCP accounting information functions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef PACE2_STATUS_DHCP_H
#define PACE2_STATUS_DHCP_H

/* Includes *********************************************************************/
#include "pace2_basic_def.h"
#include "event_types/dhcp_events.h"

/* Public Types *****************************************************************/

/**
 * @brief Return state of the DHCP get information function.
 */
typedef enum {
    PACE2_DHCP_SUCCESS = 0,             /**< Function returned successfully, returned data is valid. */
    PACE2_DHCP_PARAM_MISSING,           /**< Function parameter is missing. */
    PACE2_DHCP_INFO_UNAVAILABLE,        /**< Information are not available. */
} PACE2_DHCP_return_state;

/* Public Prototypes ************************************************************/

/**
 * @brief Get the DHCPv4 accounting information.
 *
 * This function returns the DHCPv4 accounting information of the classification stage.
 * The buffer is available until the next packet processing is done.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       Identifier of a thread.
 * @param[out]  dhcp_event      Pointer to a variable, which is used to store the received data.
 *                              This variable is a event structure of type @ref PACE2_basic_DHCP_event .
 * @retval PACE2_DHCP_SUCCESS           @copydoc PACE2_DHCP_return_state::PACE2_DHCP_SUCCESS
 * @retval PACE2_DHCP_PARAM_MISSING     @copydoc PACE2_DHCP_return_state::PACE2_DHCP_PARAM_MISSING
 * @retval PACE2_DHCP_INFO_UNAVAILABLE  @copydoc PACE2_DHCP_return_state::PACE2_DHCP_INFO_UNAVAILABLE
 */
PACE2_DHCP_return_state pace2_dhcp_get_information(PACE2_module * const pace2_module,
                                                   int const thread_ID,
                                                   PACE2_basic_DHCP_event * const dhcp_event);

#endif /* PACE2_STATUS_DHCP_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
