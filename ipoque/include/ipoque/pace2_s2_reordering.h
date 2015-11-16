/********************************************************************************/
/**
 ** \file       pace2_s2_reordering.h
 ** \brief      PACE 2 reordering definitions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef PACE2_S2_REORDERING_H
#define PACE2_S2_REORDERING_H

/* Public Types *****************************************************************/

/**
 * @brief Return state of stage 2 processing functions.
 */
typedef enum {
    PACE2_S2_SUCCESS = 0,           /*!< Processing was successful. */
    PACE2_S2_FAILURE                /*!< Processing failed.
    An error occurred during packet reordering. No further processing should be done for this packet. */
} PACE2_s2_return_state;

/* Public Prototypes ************************************************************/

/**
 * @brief Performs stage 2 processing of a single packet.
 *
 * TCP Packets might optionally be reordered by the packet reordering engine.
 * The engine will buffer out-of-order packets until the missing packets arrive or a
 * specific timeout occurs.
 *
 * @param[in]   pace2_module        Pointer to the PACE 2 module.
 * @param[in]   thread_ID           The ID of the thread currently processing.
 * @param[in]   packet_descriptor   The packet descriptor given by pace2_stage2_get_next_packet.
 * @retval PACE2_S2_SUCCESS         @copydoc PACE2_s2_return_state::PACE2_S2_SUCCESS
 * @retval PACE2_S2_FAILURE         @copydoc PACE2_s2_return_state::PACE2_S2_FAILURE
 */
PACE2_s2_return_state pace2_s2_process_packet(PACE2_module * const pace2_module,
                                              int thread_ID,
                                              PACE2_packet_descriptor *packet_descriptor );

/**
 * @brief Update timestamp of the packet reordering engine.
 *
 * The function updates the timestamp of the packet reordering engine.
 * If @ref INTERNAL flow tracking is used, the timestamp of the polling hash table
 * will be updated too.
 *
 * @param[in]   pace2_module        Pointer to the PACE 2 module.
 * @param[in]   thread_ID           The ID of the thread currently processing.
 * @param[in]   timestamp           Timestamp value.
 * @returns     0, if processing was successful.
 */
int pace2_s2_update_timestamp(PACE2_module * const pace2_module, int thread_ID, PACE2_timestamp timestamp);

/**
 * @brief Get next packet for processing from the reordering engine.
 *
 * The function returns the next reordered packet for further processing.
 *
 * @param[in]   pace2_module        Pointer to the PACE 2 module.
 * @param[in]   thread_ID           The ID of the thread currently processing.
 * @returns     Packet descriptor pointer to next packet for further processing.
 */
PACE2_packet_descriptor * pace2_s2_get_next_packet(PACE2_module * const pace2_module, int thread_ID);

#endif /* PACE2_S2_REORDERING_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
