/********************************************************************************/
/**
 ** \file       pace2_s5_timeout.h
 ** \brief      PACE 2 timeout handling definitions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef PACE2_S5_TIMEOUT_H
#define PACE2_S5_TIMEOUT_H

/* Public Prototypes ************************************************************/

/**
 * \brief Check for timeouts and handle them.
 *
 * This function should be called for every packet when the actual processing
 * is finished. If internal flow and subscriber tracking is used the timeout events
 * can be retrieved after this function call as well.
 *
 * @param[in]   pace2_module        Pointer to the PACE 2 module.
 * @param[in]   thread_ID           Identifier of a thread.
 * @param[out]  return_event_mask   The mask to be filled with event types created during the current call.
 * \returns     0, if processing was successful.
 */
int pace2_s5_handle_timeout(PACE2_module * const pace2_module, int thread_ID, PACE2_bitmask *return_event_mask);

#endif /* PACE2_S5_TIMEOUT_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
