/********************************************************************************/
/**
 ** \file       pace2_s4_decoding.h
 ** \brief      PACE 2 decoding definitions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef PACE2_S4_DECODING_H
#define PACE2_S4_DECODING_H

/* Public Types *****************************************************************/

/**
 * @brief Return state of stage 4 processing functions.
 */
typedef enum {
    PACE2_S4_SUCCESS = 0,           /*!< Processing was successful. */
    PACE2_S4_PARAM_MISSING,         /*!< Function parameter is missing. */
    PACE2_S4_INPUT_MISSING,         /*!< Input data is missing. */
    PACE2_S4_OUT_OF_MEMORY,         /*!< Memory allocation failed. */
    PACE2_S4_NOT_INITIALIZED,       /*!< Stage 4 is not initialized. */
    PACE2_S4_FAILURE                /*!< Processing failed. */
} PACE2_s4_return_state;

/* Public Prototypes ************************************************************/

/**
 * @brief Performs stage 4 processing of a single packet.
 *
 * The function performs packet based protocol decoding. It provides advanced and class meta data.
 * The stage 4 part of @ref PACE2_global_config has to be configured for packet based decoding.
 *
 * @param[in]   pace2_module        Pointer to the PACE 2 module.
 * @param[in]   thread_ID           The ID of the thread currently processing.
 * @param[in]   packet_descriptor   The packet descriptor given by @ref pace2_s2_get_next_packet.
 * @param[in]   classifier_token    Contains required data for stage4 processing.
 *                                  Can be left out (set to NULL) if stage4 processing is done by the PACE2_module as lower stages
 *                                  and no other flow has been processed in between.
 * @param[out]  return_event_mask   The mask to be filled with event types created during the current call.
 * @retval PACE2_S4_SUCCESS         @copydoc PACE2_s4_return_state::PACE2_S4_SUCCESS
 * @retval PACE2_S4_PARAM_MISSING   @copydoc PACE2_s4_return_state::PACE2_S4_PARAM_MISSING
 * @retval PACE2_S4_OUT_OF_MEMORY   @copydoc PACE2_s4_return_state::PACE2_S4_OUT_OF_MEMORY
 *                                  \arg Memory allocation for stage 4 flow data failed. This value will be returned
 *                                  only in cases the @ref EXTERNAL flow tracking is used.
 * @retval PACE2_S4_NOT_INITIALIZED @copydoc PACE2_s4_return_state::PACE2_S4_NOT_INITIALIZED
 *                                  \arg Stage 4 is not configured for packet based decoding.
 * @retval PACE2_S4_FAILURE         @copydoc PACE2_s4_return_state::PACE2_S4_FAILURE
 */
PACE2_s4_return_state pace2_s4_process_packet(PACE2_module * const pace2_module,
                                              int thread_ID,
                                              PACE2_packet_descriptor *packet_descriptor,
                                              const PACE2_classifier_token *classifier_token,
                                              PACE2_bitmask *return_event_mask);

/**
 * @brief Performs stage 4 processing on a data stream.
 *
 * The function performs stream based protocol decoding. It provides advanced and class meta data.
 * The stage 4 part of @ref PACE2_global_config has to be configured for stream based decoding.
 *
 * @param[in]   pace2_module        Pointer to the PACE 2 module.
 * @param[in]   thread_ID           The ID of the thread currently processing.
 * @param[in]   stream_descriptor   The stream descriptor prefilled by @ref pace2_s4_prepare_stream and later amended by the user with stream data.
 * @param[in]   classifier_token    Contains required data for stage4 processing.
 *                                  Can be left out (set to NULL) if stage4 processing is done by the PACE2_module as lower stages
 *                                  and no other flow has been processed in between.
 * @param[out]  return_event_mask   The mask to be filled with event types created during the current call.
 * @retval PACE2_S4_SUCCESS         @copydoc PACE2_s4_return_state::PACE2_S4_SUCCESS
 * @retval PACE2_S4_PARAM_MISSING   @copydoc PACE2_s4_return_state::PACE2_S4_PARAM_MISSING
 * @retval PACE2_S4_INPUT_MISSING   @copydoc PACE2_s4_return_state::PACE2_S4_INPUT_MISSING
 *                                  \arg No flow data for stage 4 available.
 *                                  \arg Stream data is not available.
 * @retval PACE2_S4_NOT_INITIALIZED @copydoc PACE2_s4_return_state::PACE2_S4_NOT_INITIALIZED
 *                                  \arg Stage 4 is not configured for stream based decoding.
 * @retval PACE2_S4_FAILURE         @copydoc PACE2_s4_return_state::PACE2_S4_FAILURE
 * @note currently works only using external tracking
 */
PACE2_s4_return_state pace2_s4_process_stream(PACE2_module * const pace2_module,
                                              int thread_ID,
                                              PACE2_stream_descriptor *stream_descriptor,
                                              const PACE2_classifier_token *classifier_token,
                                              PACE2_bitmask *return_event_mask);

/**
 * @brief Prepares a stream descriptor for use in stage 4 from an already existing packet descriptor.
 *
 * @param[in]   pace2_module        Pointer to the PACE 2 module.
 * @param[in]   thread_ID           The ID of the thread currently processing.
 * @param[in]   packet_descriptor   Pointer to an already existing packet descriptor.
 * @param[out]  stream_descriptor   Pointer to the stream descriptor to prepare.
 * @retval PACE2_S4_SUCCESS         @copydoc PACE2_s4_return_state::PACE2_S4_SUCCESS
 * @retval PACE2_S4_PARAM_MISSING   @copydoc PACE2_s4_return_state::PACE2_S4_PARAM_MISSING
 */
PACE2_s4_return_state pace2_s4_prepare_stream(PACE2_module * const pace2_module,
                                              int const thread_ID,
                                              PACE2_packet_descriptor const * const packet_descriptor,
                                              PACE2_stream_descriptor * const stream_descriptor);

#endif /* PACE2_S4_DECODING_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
