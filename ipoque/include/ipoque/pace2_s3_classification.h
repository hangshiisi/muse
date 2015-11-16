/********************************************************************************/
/**
 ** \file       pace2_s3_classification.h
 ** \brief      PACE 2 classification definitions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef PACE2_S3_CLASSIFICATION_H
#define PACE2_S3_CLASSIFICATION_H

/* Public Types *****************************************************************/

/**
 * @brief Return state of stage 3 processing functions.
 */
typedef enum {
    PACE2_S3_SUCCESS = 0,           /*!< Processing was successful. */
    PACE2_S3_PARAM_MISSING,         /*!< Function parameter is missing. */
    PACE2_S3_INPUT_MISSING,         /*!< Input data is missing. */
    PACE2_S3_REQUIRE_SUBSCRIBER,    /*!< Subscriber data is required for further processing. */
    PACE2_S3_INVALID_PACKET,        /*!< Given packet is invalid. */
    PACE2_S3_OUT_OF_MEMORY,         /*!< Memory allocation failed. */
    PACE2_S3_FAILURE,               /*!< Processing failed. */
    PACE2_S3_NOT_AVAILABLE          /*!< A required feature is not available. */
} PACE2_s3_return_state;

/* Public Prototypes ************************************************************/

/**
 * @brief Performs stage 3 processing of a single packet.
 *
 * The function performs the protocol and application classification.
 * It provides the detection results as well as basic meta data.
 *
 * @param[in]   pace2_module        Pointer to the PACE 2 module.
 * @param[in]   thread_ID           The ID of the thread currently processing.
 * @param[in]   packet_descriptor   The packet descriptor given by @ref pace2_s2_get_next_packet.
 * @param[out]  return_event_mask   The mask to be filled with event types created during the current call.
 * @retval PACE2_S3_SUCCESS         @copydoc PACE2_s3_return_state::PACE2_S3_SUCCESS
 * @retval PACE2_S3_PARAM_MISSING   @copydoc PACE2_s3_return_state::PACE2_S3_PARAM_MISSING
 * @retval PACE2_S3_INPUT_MISSING   @copydoc PACE2_s3_return_state::PACE2_S3_INPUT_MISSING
 *                                  This value will be returned only in cases the @ref EXTERNAL flow tracking
 *                                  is used. No flow data for the stage 3 processing available.
 * @retval PACE2_S3_REQUIRE_SUBSCRIBER  This value will be returned only in cases the @ref EXTERNAL subscriber tracking
 *                                  is used. The processing stopped, because subscriber data is
 *                                  not available for further classification steps. The function has to be called
 *                                  again with the given subscriber data.
 * @retval PACE2_S3_INVALID_PACKET  @copydoc PACE2_s3_return_state::PACE2_S3_INVALID_PACKET
 * @retval PACE2_S3_FAILURE         @copydoc PACE2_s3_return_state::PACE2_S3_FAILURE
 */
PACE2_s3_return_state pace2_s3_process_packet(PACE2_module * const pace2_module,
                                              int thread_ID,
                                              PACE2_packet_descriptor *packet_descriptor,
                                              PACE2_bitmask *return_event_mask);

/**
 * @brief Set the OpenVPN detection mode for stage 3 processing.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       @arg >= 0: The ID of the thread for which the OpenVPN detection mode should be changed.
 *                              @arg == @ref PACE2_ALL_THREADS "PACE2_ALL_THREADS": The OpenVPN detection mode will be
 *                              changed for all threads.
 * @param[in]   mode            Either @ref SAFE_CLASSIFICATION or @ref AGGRESSIVE_CLASSIFICATION. See the stage 3 configuration
 *                              option @ref PACE2_config_s3_classification::openvpn_mode "openvpn_mode" for details.
 * @retval PACE2_S3_SUCCESS         @copydoc PACE2_s3_return_state::PACE2_S3_SUCCESS
 * @retval PACE2_S3_PARAM_MISSING   @copydoc PACE2_s3_return_state::PACE2_S3_PARAM_MISSING
 * @retval PACE2_S3_NOT_AVAILABLE   The OpenVPN detection is not available.
 * @retval PACE2_S3_FAILURE         @copydoc PACE2_s3_return_state::PACE2_S3_FAILURE
 *                                  See the note.
 *
 * @note The value @ref PACE2_ALL_THREADS for thread_ID is supported only at the moment.
 */
PACE2_s3_return_state pace2_s3_set_openvpn_mode(PACE2_module * const pace2_module,
                                                int const thread_ID,
                                                PACE2_classification_mode const mode);

/**
 * @brief Set the Skype detection mode for stage 3 processing.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       @arg >= 0: The ID of the thread for which the Skype detection mode should be changed.
 *                              @arg == @ref PACE2_ALL_THREADS "PACE2_ALL_THREADS": The Skype detection mode will be
 *                              changed for all threads.
 * @param[in]   mode            Either @ref SAFE_CLASSIFICATION or @ref AGGRESSIVE_CLASSIFICATION. See the stage 3 configuration
 *                              option @ref PACE2_config_s3_classification::skype_mode "skype_mode" for details.
 * @retval PACE2_S3_SUCCESS         @copydoc PACE2_s3_return_state::PACE2_S3_SUCCESS
 * @retval PACE2_S3_PARAM_MISSING   @copydoc PACE2_s3_return_state::PACE2_S3_PARAM_MISSING
 * @retval PACE2_S3_NOT_AVAILABLE   The Skype detection is not available.
 * @retval PACE2_S3_FAILURE         @copydoc PACE2_s3_return_state::PACE2_S3_FAILURE
 *                                  See the note.
 *
 * @note The value @ref PACE2_ALL_THREADS for thread_ID is supported only at the moment.
 */
PACE2_s3_return_state pace2_s3_set_skype_mode(PACE2_module * const pace2_module,
                                              int const thread_ID,
                                              PACE2_classification_mode const mode);

/**
 * @brief Set the Radius detection mode for stage 3 processing.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       @arg >= 0: The ID of the thread for which the Radius detection mode should be changed.
 *                              @arg == @ref PACE2_ALL_THREADS "PACE2_ALL_THREADS": The Radius detection mode will be
 *                              changed for all threads.
 * @param[in]   mode            Either @ref SAFE_CLASSIFICATION or @ref AGGRESSIVE_CLASSIFICATION See the stage 3 configuration
 *                              option @ref PACE2_config_s3_classification::radius_mode "radius_mode" for details.
 * @retval PACE2_S3_SUCCESS         @copydoc PACE2_s3_return_state::PACE2_S3_SUCCESS
 * @retval PACE2_S3_PARAM_MISSING   @copydoc PACE2_s3_return_state::PACE2_S3_PARAM_MISSING
 * @retval PACE2_S3_FAILURE         @copydoc PACE2_s3_return_state::PACE2_S3_FAILURE
 *                                  See the note.
 *
 * @note The value @ref PACE2_ALL_THREADS for thread_ID is supported only at the moment.
 */
PACE2_s3_return_state pace2_s3_set_radius_mode(PACE2_module * const pace2_module,
                                               int const thread_ID,
                                               PACE2_classification_mode const mode);

/**
 * @brief Set the operation mode of the operating system detection during runtime.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       @arg >= 0: The ID of the thread for which the mode should be changed.
 *                              @arg == @ref PACE2_ALL_THREADS "PACE2_ALL_THREADS": The mode will be changed for all threads.
 * @param[in]   enable_os       @arg == @ref IPQ_TRUE "IPQ_TRUE": OS detection will be enabled.
 *                              @arg == @ref IPQ_FALSE "IPQ_FALSE": OS detection will be disabled.
 * @retval PACE2_S3_SUCCESS         @copydoc PACE2_s3_return_state::PACE2_S3_SUCCESS
 * @retval PACE2_S3_PARAM_MISSING   @copydoc PACE2_s3_return_state::PACE2_S3_PARAM_MISSING
 * @retval PACE2_S3_NOT_AVAILABLE   The OS detection is not available.
 * @retval PACE2_S3_FAILURE         @copydoc PACE2_s3_return_state::PACE2_S3_FAILURE
 *                                  See the note.
 *
 * @note The value @ref PACE2_ALL_THREADS for thread_ID is supported only at the moment.
 */
PACE2_s3_return_state pace2_s3_set_os_detection(PACE2_module * const pace2_module,
                                                int const thread_ID,
                                                PACE2_boolean const enable_os);

/**
 * @brief Set the operation mode of the NAT detection during runtime.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       @arg >= 0: The ID of the thread for which the mode should be changed.
 *                              @arg == @ref PACE2_ALL_THREADS "PACE2_ALL_THREADS": The mode will be changed for all threads.
 * @param[in]   enable_nat      @arg == @ref IPQ_TRUE "IPQ_TRUE": NAT detection will be enabled.
 *                              @arg == @ref IPQ_FALSE "IPQ_FALSE": NAT detection will be disabled.
 * @retval PACE2_S3_SUCCESS         @copydoc PACE2_s3_return_state::PACE2_S3_SUCCESS
 * @retval PACE2_S3_PARAM_MISSING   @copydoc PACE2_s3_return_state::PACE2_S3_PARAM_MISSING
 * @retval PACE2_S3_NOT_AVAILABLE   The NAT detection is not available.
 *                                  @arg The NAT detection requires an enabled OS detection.
 *                                  @arg The NAT detection requires an enabled client server indication.
 * @retval PACE2_S3_FAILURE         @copydoc PACE2_s3_return_state::PACE2_S3_FAILURE
 *                                  Reset of NAT state failed.
 *
 * @note The value @ref PACE2_ALL_THREADS for thread_ID is supported only at the moment.
 */
PACE2_s3_return_state pace2_s3_set_nat_detection(PACE2_module * const pace2_module,
                                                 int const thread_ID,
                                                 PACE2_boolean const enable_nat);

/**
 * @brief Reset the NAT detection state for the given subscriber.
 *
 * The function flushes the state of the NAT detection for the given subscriber and stores the last state of the
 * detected main OS and the NAT flag into an event structure of type @ref PACE2_NAT_EVENT. Please note that the
 * flag @ref PACE2_NAT_event::of_source "of_source" is unused in the context of this function, because no decision
 * can be made, whether the given subscriber is the source direction or destination direction of a packet.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       The ID of the processing thread.
 * @param[in]   subscriber_data Pointer to the subscriber data for which the state has to be flushed.
 * @param[out]  nat_event       Pointer to a NAT event structure to store the last state of the NAT detection.
 * @retval PACE2_S3_SUCCESS         @copydoc PACE2_s3_return_state::PACE2_S3_SUCCESS
 * @retval PACE2_S3_PARAM_MISSING   @copydoc PACE2_s3_return_state::PACE2_S3_PARAM_MISSING
 * @retval PACE2_S3_NOT_AVAILABLE   The NAT detection is not available.
 *                                  @arg The NAT detection requires an enabled OS detection.
 *                                  @arg The NAT detection requires an enabled client server indication.
 */
PACE2_s3_return_state pace2_s3_flush_nat_state(PACE2_module * const pace2_module,
                                               int const thread_ID,
                                               PACE2_subscriber_data * const subscriber_data,
                                               PACE2_NAT_event * const nat_event);

/**
 * @brief Set the operation mode of the asymmetric detection during runtime.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       @arg >= 0: The ID of the thread for which the mode should be changed.
 *                              @arg == @ref PACE2_ALL_THREADS "PACE2_ALL_THREADS": The mode will be changed for all threads.
 * @param[in]   enable_asym_detection   @arg == @ref IPQ_TRUE "IPQ_TRUE": asymmetric detection will be enabled.
 *                                      @arg == @ref IPQ_FALSE "IPQ_FALSE": asymmetric detection will be disabled.
 * @retval PACE2_S3_SUCCESS         @copydoc PACE2_s3_return_state::PACE2_S3_SUCCESS
 * @retval PACE2_S3_PARAM_MISSING   @copydoc PACE2_s3_return_state::PACE2_S3_PARAM_MISSING
 * @retval PACE2_S3_NOT_AVAILABLE   The asymmetric detection is not available.
 * @retval PACE2_S3_FAILURE         @copydoc PACE2_s3_return_state::PACE2_S3_FAILURE
 *                                  See the note.
 *
 * @note The value @ref PACE2_ALL_THREADS for thread_ID is supported only at the moment.
 */
PACE2_s3_return_state pace2_s3_set_asymmetric_detection(PACE2_module * const pace2_module,
                                                        int const thread_ID,
                                                        PACE2_boolean const enable_asym_detection);

/**
 * @brief Set the operation mode of the client server indication (CSI) during runtime.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       @arg >= 0: The ID of the thread for which the mode should be changed.
 *                              @arg == @ref PACE2_ALL_THREADS "PACE2_ALL_THREADS": The mode will be changed for all threads.
 * @param[in]   enable_csi      @arg == @ref IPQ_TRUE "IPQ_TRUE": CSI will be enabled.
 *                              @arg == @ref IPQ_FALSE "IPQ_FALSE": CSI will be disabled.
 * @retval PACE2_S3_SUCCESS         @copydoc PACE2_s3_return_state::PACE2_S3_SUCCESS
 * @retval PACE2_S3_PARAM_MISSING   @copydoc PACE2_s3_return_state::PACE2_S3_PARAM_MISSING
 * @retval PACE2_S3_NOT_AVAILABLE   The CSI is not available.
 * @retval PACE2_S3_FAILURE         @copydoc PACE2_s3_return_state::PACE2_S3_FAILURE
 *                                  See the note.
 *
 * @note The value @ref PACE2_ALL_THREADS for thread_ID is supported only at the moment.
 */
PACE2_s3_return_state pace2_s3_set_client_server_indication(PACE2_module * const pace2_module,
                                                            int const thread_ID,
                                                            PACE2_boolean const enable_csi);

/**
 * @brief This function forces all further packets of the flow to pass the classification through the fastpath
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       @arg >= 0: The ID of the current thread.
 *
 * @note For further packets the classification results will not change.
 */
PACE2_s3_return_state pace2_s3_force_current_flow_to_fastpath(PACE2_module * const pace2_module,
                                                              int const thread_ID);

#endif /* PACE2_S3_CLASSIFICATION_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/

