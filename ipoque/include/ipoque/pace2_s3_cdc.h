/********************************************************************************/
/**
 ** \file         pace2_s3_cdc.h
 ** \brief        Custom Defined Classification related API
 ** \copyright    ipoque GmbH
 **/
/********************************************************************************/

#ifndef PACE2_S3_CDC_H
#define PACE2_S3_CDC_H

/* Includes *********************************************************************/
#include "pace2_basic_def.h"

/* Public Types *****************************************************************/

typedef enum {
    PACE2_CDC_EXCLUDE = 0,                  /*!< classification did not match */
    PACE2_CDC_MATCH,                        /*!< classification accepted */
    PACE2_CDC_MATCH_BUT_NEED_NEXT_PACKET,   /*!< classification accepted and requests further packets */
    PACE2_CDC_NEED_NEXT_PACKET              /*!< classification requests further packets */
} PACE2_cdc_return_state;

struct PACE2_cdc_generic_info {
    u16 flow_packet_counter[2];	/* the packet counters for both directions */
    u8 packet_direction;	/* the packet direction (0 or 1) */
    u8 initial_packet_direction;	/* the direction of the first packet of the flow (0 or 1) */

    /* this struct may grow in later versions but the previous fields will not change */
};

/**
 * This is the prototype for custom defined classificiation callbacks
 *
 * @param[in]   pace2_module        Pointer to the PACE 2 module.
 * @param[in]   thread_ID           The ID of the thread currently processing.
 * @param[in]   packet_descriptor   The packet descriptor given by @ref pace2_s2_get_next_packet.
 * @param[in]   userptr             the user pointer set when the corresponding classification gets registered from the configuration.
 *                                  See @ref PACE2_config_s3_cdc::callback_userptr for details.
 * @param[in]   flow_area           the pointer to the dedicated flow area (the size is as requested in the configuration), might be NULL.
 *                                  See @ref PACE2_config_s3_cdc::flow_area_size for details.
 * @param[in]   src_area            the pointer to the dedicated subscriber area of the source of the packet (the size is as requested in the configuration), can be NULL.
 *                                  See @ref PACE2_config_s3_cdc::subscriber_area_size for details.
 * @param[in]   dst_area            the pointer to the dedicated subscriber area of the destination of the packet (the size is as requested in the configuration), can be NULL.
 *                                  See @ref PACE2_config_s3_cdc::subscriber_area_size for details.
 *
 * @retval PACE2_CDC_EXCLUDE                    @copydoc PACE2_cdc_return_state::PACE2_CDC_EXCLUDE
 * @retval PACE2_CDC_MATCH                      @copydoc PACE2_cdc_return_state::PACE2_CDC_MATCH
 * @retval PACE2_CDC_MATCH_BUT_NEED_NEXT_PACKET @copydoc PACE2_cdc_return_state::PACE2_CDC_MATCH_BUT_NEED_NEXT_PACKET
 * @retval PACE2_CDC_NEED_NEXT_PACKET           @copydoc PACE2_cdc_return_state::PACE2_CDC_NEED_NEXT_PACKET
 */
typedef PACE2_cdc_return_state (*pace2_cdc_callback_t)
                                            (PACE2_module * const pace2_module,
                                             PACE2_packet_descriptor *packet_descriptor,
                                             int thread_ID,
                                             void *userptr, void *flow_area,
                                             void *src_area, void *dst_area);

/**
 * This function returns the pointer to the current classification result
 * Note: it is only intended to get used with custom defined classification callbacks and
 * can also be invalid
 *
 * @param[in]   pace2_module        Pointer to the PACE 2 module.
 * @param[in]   thread_ID           The ID of the thread currently processing.
 *
 * @retval pointer to the current classification result, can be NULL
 */
const PACE2_classification_result_event *pace2_cdc_get_classification(PACE2_module * const pace2_module, int thread_ID);

/**
 * This function returns the pointer to the current custom defined classification exclude bitmask
 *
 * @param[in]   pace2_module        Pointer to the PACE 2 module.
 * @param[in]   thread_ID           The ID of the thread currently processing.
 *
 * @retval pointer to the custom defined classification exclude bitmask, can be NULL
 */
const u32 *pace2_cdc_get_excluded_bm(PACE2_module * const pace2_module, int thread_ID);


/**
 * @brief This function can be used in CDC to query some generic flow information.
 *
 * @param[in]   pace2_module        Pointer to the PACE 2 module.
 * @param[in]   thread_ID           The ID of the thread currently processing.
 * @returns     Pointer to a static area containing the generic information.
 */
const struct PACE2_cdc_generic_info *pace2_cdc_get_generic_info(PACE2_module * const pace2_module, int thread_ID);


#endif // PACE2_S3_CDC_H
