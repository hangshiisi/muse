/********************************************************************************/
/**
 ** \file       pace2_cpi_classification.h
 ** \brief      PACE 2 component programming interface of the classification.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef PACE2_CPI_CLASSIFICATION_FUNC_H
#define PACE2_CPI_CLASSIFICATION_FUNC_H

/* Public Types *****************************************************************/

/**
 * @brief Return state of component programming interface functions.
 */
typedef enum {
    PACE2_CPI_SUCCESS = 0,              /**< Function returned successfully, returned data is valid. */
    PACE2_CPI_PARAM_MISSING,            /**< Function parameter is missing. */
    PACE2_CPI_NOT_AVAILABLE,            /**< The requested data are not available. */
    PACE2_CPI_FAILURE,                  /*!< Processing failed. */
    PACE2_CPI_CALL_AGAIN                /*!< Indcates that the function needs to be called again. */
} PACE2_CPI_return_state;

/* Public Prototypes ************************************************************/

/**
 * @brief Get the SSL server hello data of the last processed packet.
 *
 * This function returns the SSL server hello metadata for the last packet given to the classification stage.
 *
 * @note    The data of the structure is valid as long as no further packet processing of stage 1 to 5 is done.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       Identifier of a thread.
 * @param[out]  ssl_data        Pointer to a variable, which is used to store the pointer to the data.
 * @retval PACE2_CPI_SUCCESS            @copydoc PACE2_CPI_return_state::PACE2_CPI_SUCCESS
 * @retval PACE2_CPI_PARAM_MISSING      @copydoc PACE2_CPI_return_state::PACE2_CPI_PARAM_MISSING
 * @retval PACE2_CPI_NOT_AVAILABLE      @copydoc PACE2_CPI_return_state::PACE2_CPI_NOT_AVAILABLE
 * @retval PACE2_CPI_FAILURE            @copydoc PACE2_CPI_return_state::PACE2_CPI_FAILURE
 */
PACE2_CPI_return_state pace2_cpi_get_ssl_server_hello_data(PACE2_module * const pace2_module,
                                                           int const thread_ID,
                                                           PACE2_SSL_server_hello_event ** ssl_data);

/**
 * @brief Get the SSL client hello data of the last processed packet.
 *
 * This function returns the SSL client hello metadata for the last packet given to the classification stage.
 *
 * @note    The data of the structure is valid as long as no further packet processing of stage 1 to 5 is done.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       Identifier of a thread.
 * @param[out]  ssl_data        Pointer to a variable, which is used to store the pointer to the data.
 * @retval PACE2_CPI_SUCCESS            @copydoc PACE2_CPI_return_state::PACE2_CPI_SUCCESS
 * @retval PACE2_CPI_PARAM_MISSING      @copydoc PACE2_CPI_return_state::PACE2_CPI_PARAM_MISSING
 * @retval PACE2_CPI_NOT_AVAILABLE      @copydoc PACE2_CPI_return_state::PACE2_CPI_NOT_AVAILABLE
 * @retval PACE2_CPI_FAILURE            @copydoc PACE2_CPI_return_state::PACE2_CPI_FAILURE
 */
PACE2_CPI_return_state pace2_cpi_get_ssl_client_hello_data(PACE2_module * const pace2_module,
                                                           int const thread_ID,
                                                           PACE2_SSL_client_hello_event ** ssl_data);

/**
 * @brief Get the SIP data of the last processed packet.
 *
 * This function returns the SIP metadata for the last packet given to the classification stage.
 *
 * @note    The data of the structure is valid as long as no further packet processing of stage 1 to 5 is done.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       Identifier of a thread.
 * @param[out]  sip_data        Pointer to a variable, which is used to store the pointer to the data.
 * @retval PACE2_CPI_SUCCESS            @copydoc PACE2_CPI_return_state::PACE2_CPI_SUCCESS
 * @retval PACE2_CPI_PARAM_MISSING      @copydoc PACE2_CPI_return_state::PACE2_CPI_PARAM_MISSING
 * @retval PACE2_CPI_NOT_AVAILABLE      @copydoc PACE2_CPI_return_state::PACE2_CPI_NOT_AVAILABLE
 * @retval PACE2_CPI_FAILURE            @copydoc PACE2_CPI_return_state::PACE2_CPI_FAILURE
 */
PACE2_CPI_return_state pace2_cpi_get_sip_data(PACE2_module * const pace2_module,
                                              int const thread_ID,
                                              PACE2_basic_SIP_event ** sip_data);

/**
 * @brief Get the DHCPv4 data of the last processed packet.
 *
 * This function returns the DHCPv4 metadata for the last packet given to the classification stage.
 *
 * @note    The data of the structure is valid as long as no further packet processing of stage 1 to 5 is done.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       Identifier of a thread.
 * @param[out]  dhcp_data       Pointer to a variable, which is used to store the pointer to the data.
 * @retval PACE2_CPI_SUCCESS            @copydoc PACE2_CPI_return_state::PACE2_CPI_SUCCESS
 * @retval PACE2_CPI_PARAM_MISSING      @copydoc PACE2_CPI_return_state::PACE2_CPI_PARAM_MISSING
 * @retval PACE2_CPI_NOT_AVAILABLE      @copydoc PACE2_CPI_return_state::PACE2_CPI_NOT_AVAILABLE
 * @retval PACE2_CPI_FAILURE            @copydoc PACE2_CPI_return_state::PACE2_CPI_FAILURE
 */
PACE2_CPI_return_state pace2_cpi_get_dhcp_data(PACE2_module * const pace2_module,
                                               int const thread_ID,
                                               PACE2_basic_DHCP_event ** dhcp_data);

/**
 * @brief Get the HTTP request data of the last processed packet.
 *
 * This function returns the HTTP request metadata for the last packet given to the classification stage.
 *
 * @note    The data of the structure is valid as long as no further packet processing of stage 1 to 5 is done.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       Identifier of a thread.
 * @param[out]  http_request_data   Pointer to a variable, which is used to store the pointer to the data.
 * @retval PACE2_CPI_SUCCESS            @copydoc PACE2_CPI_return_state::PACE2_CPI_SUCCESS
 * @retval PACE2_CPI_PARAM_MISSING      @copydoc PACE2_CPI_return_state::PACE2_CPI_PARAM_MISSING
 * @retval PACE2_CPI_NOT_AVAILABLE      @copydoc PACE2_CPI_return_state::PACE2_CPI_NOT_AVAILABLE
 * @retval PACE2_CPI_FAILURE           PACE2_OS_event @copydoc PACE2_CPI_return_state::PACE2_CPI_FAILURE
 */
PACE2_CPI_return_state pace2_cpi_get_http_request_data(PACE2_module * const pace2_module,
                                                       int const thread_ID,
                                                       PACE2_basic_HTTP_request_event ** http_request_data);

/**
 * @brief Get the HTTP response data of the last processed packet.
 *
 * This function returns the HTTP response metadata for the last packet given to the classification stage.
 *
 * @note    The data of the structure is valid as long as no further packet processing of stage 1 to 5 is done.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       Identifier of a thread.
 * @param[out]  http_response_data  Pointer to a variable, which is used to store the pointer to the data.
 * @retval PACE2_CPI_SUCCESS            @copydoc PACE2_CPI_return_state::PACE2_CPI_SUCCESS
 * @retval PACE2_CPI_PARAM_MISSING      @copydoc PACE2_CPI_return_state::PACE2_CPI_PARAM_MISSING
 * @retval PACE2_CPI_NOT_AVAILABLE      @copydoc PACE2_CPI_return_state::PACE2_CPI_NOT_AVAILABLE
 * @retval PACE2_CPI_FAILURE            @copydoc PACE2_CPI_return_state::PACE2_CPI_FAILURE
 */
PACE2_CPI_return_state pace2_cpi_get_http_response_data(PACE2_module * const pace2_module,
                                                        int const thread_ID,
                                                        PACE2_basic_HTTP_response_event ** http_response_data);

/**
 * @brief Get the OS detection data of the last processed packet.
 *
 * This function returns the OS detection metadata for the last packet given to the classification stage.
 *
 * @note    The data of the structure is valid as long as no further packet processing of stage 1 to 5 is done.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       Identifier of a thread.
 * @param[out]  os_detection_data   Pointer to a variable, which is used to store the pointer to the data.
 * @retval PACE2_CPI_SUCCESS            @copydoc PACE2_CPI_return_state::PACE2_CPI_SUCCESS
 * @retval PACE2_CPI_PARAM_MISSING      @copydoc PACE2_CPI_return_state::PACE2_CPI_PARAM_MISSING
 * @retval PACE2_CPI_NOT_AVAILABLE      @copydoc PACE2_CPI_return_state::PACE2_CPI_NOT_AVAILABLE
 * @retval PACE2_CPI_FAILURE            @copydoc PACE2_CPI_return_state::PACE2_CPI_FAILURE
 */
PACE2_CPI_return_state pace2_cpi_get_os_detection_data(PACE2_module * const pace2_module,
                                                       int const thread_ID,
                                                       PACE2_OS_event ** os_detection_data);

/**
 * @brief Get the client-server indication packet direction data of the last processed packet.
 *
 * This function returns the packet direction metadata for the last packet given to the classification stage.
 *
 * @note    The data of the structure is valid as long as no further packet processing of stage 1 to 5 is done.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       Identifier of a thread.
 * @param[out]  packet_direction_data   Pointer to a variable, which is used to store the pointer to the data.
 * @retval PACE2_CPI_SUCCESS            @copydoc PACE2_CPI_return_state::PACE2_CPI_SUCCESS
 * @retval PACE2_CPI_PARAM_MISSING      @copydoc PACE2_CPI_return_state::PACE2_CPI_PARAM_MISSING
 * @retval PACE2_CPI_NOT_AVAILABLE      @copydoc PACE2_CPI_return_state::PACE2_CPI_NOT_AVAILABLE
 * The function returns this value in different cases:
 *  @arg    CSI module is disabled via configuration.
 *  @arg    The fastpath of the detection  was used, requested data is not available.
 *  @arg    The client-server indication is not available.
 * @retval PACE2_CPI_FAILURE            @copydoc PACE2_CPI_return_state::PACE2_CPI_FAILURE
 */
PACE2_CPI_return_state pace2_cpi_get_packet_direction_data(PACE2_module * const pace2_module,
                                                           int const thread_ID,
                                                           PACE2_csi_packet_dir_event ** packet_direction_data);

/**
 * @brief Get the out-of-order statistics of the last TCP flow process by the classification stage.
 *
 * This function returns the out-of-order and retransmission counter values of the last TCP flow
 * processed by the detection.
 *
 * @note    The data of the structure is valid as long as no further packet processing of stage 1 to 5 is done.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       Identifier of a thread.
 * @param[out]  tcp_ooo_data    Pointer to a variable, which is used to store the pointer to the data.
 * @retval PACE2_CPI_SUCCESS            @copydoc PACE2_CPI_return_state::PACE2_CPI_SUCCESS
 * @retval PACE2_CPI_PARAM_MISSING      @copydoc PACE2_CPI_return_state::PACE2_CPI_PARAM_MISSING
 * @retval PACE2_CPI_NOT_AVAILABLE      @copydoc PACE2_CPI_return_state::PACE2_CPI_NOT_AVAILABLE
 * @retval PACE2_CPI_FAILURE            @copydoc PACE2_CPI_return_state::PACE2_CPI_FAILURE
 */
PACE2_CPI_return_state pace2_cpi_get_tcp_out_of_order_data(PACE2_module * const pace2_module,
                                                           int const thread_ID,
                                                           PACE2_TCP_event ** tcp_ooo_data);


/**
 * @brief Reset the given metadata dissector state.
 *
 * This function reset the meta dissector internal state.
 * It can be called anytime however not all dissectors allow a reset.
 *
 * @note this function is usable with internal and external flow tracking.
 * For internal tracking the flow pointer should be NULL in order to indicate to
 * use the internal flow pointer.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       Identifier of a thread.
 * @param[in]   flow            pointer to the flow to reset metadata for, can be NULL for internal tracking
 * @param[in]   type            dissector type for the specific flow data should get reset for
 * @param[out]  status          status of the dissector @ref enum metadata_status, the pointer must not be NULL
 * @return: METADATA_DISSECTOR_SUCCESS on success or an enum value indicating the error type
 */

PACE2_CPI_return_state pace2_cpi_reset_metadata_dissector(PACE2_module * const pace2_module,
                                                          int const thread_ID,
                                                          void * const flow,
                                                          enum dissector_metadata_type const type,
                                                          enum metadata_status *status);

/**
 * @brief Get current metadata dissector result
 *
 * This function returns the current metadata dissector result.
 * The corresponding meta data dissector which needs to be enabled.
 *
 * @note this function is usable with internal and external flow tracking.
 * For internal flow tracking the flow pointer can be NULL
 * This function can also be used with @ref pace2_pht_foreach with external tracking.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       Identifier of a thread.
 * @param[in]   flow            pointer to the flow to reset metadata for, can be NULL for internal tracking
 * @param[in]   type            dissector type to query event for
 * @param[out]  metadata_event  event to the metadata type that got queried
 * @return: METADATA_DISSECTOR_SUCCESS on success or an enum value indicating the error type
 */

PACE2_CPI_return_state pace2_cpi_get_dissector_metadata(PACE2_module * const pace2_module,
                                                        int const thread_ID,
                                                        void * const flow,
                                                        enum dissector_metadata_type const type,
                                                        PACE2_dissector_metadata_event *metadata_event);

/**
 * @brief Reset the metadata dissector state for all flows.
 *
 * This function reset the meta dissector internal state.
 * It can be called anytime however not all dissectors allow a reset.
 *
 * @note this function is only usable with internal flow tracking.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       Identifier of a thread.
 * @param[in]   type            dissector type for the specific flow data should get reset for
 * @param[out]  status          status of the dissector @ref enum metadata_status, the pointer must not be NULL
 * @return: METADATA_DISSECTOR_SUCCESS on success or an enum value indicating the error type
 */

PACE2_CPI_return_state pace2_cpi_reset_all_metadata_dissector_int_tracking(PACE2_module * const pace2_module,
                                                                           int const thread_ID,
                                                                           enum dissector_metadata_type const type,
                                                                           enum metadata_status *status);


/**
 * @brief Prepare internal flow table to retreive dissector meta data for each flow.
 *
 * @note this function is only usable with internal flow tracking.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       Identifier of a thread.
 * @return: METADATA_DISSECTOR_SUCCESS on success or an enum value indicating the error type
 */

PACE2_CPI_return_state pace2_cpi_init_foreach_int_metadata_dissector(PACE2_module * const pace2_module,
                                                                     int const thread_ID);


typedef struct {
    u8 *key;                          /*<! pointer to the lookup key for the flow */
    u64 flow_id;                      /*<! PACE2 flow ID */
    PACE2_timestamp last_updated_ts;  /*<! last time the flow got updated */
} PACE2_dissector_foreach_flowinfo;

/**
 * @brief Get the next metadata dissector result
 *
 * This function returns the next metadata dissector result.
 *
 * @note this function is only usable with internal flow tracking.
 * It needs to get called after \ref pace2_cpi_init_foreach_int_metadata_dissector was called.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       Identifier of a thread.
 * @param[in]   type            dissector type to query event for
 * @param[out]  metadata_event  event to the metadata type that got queried
 * @param[out]  flow_info       contains information about the flow see @ref PACE2_dissector_foreach_flowinfo, can be NULL
 * @param type metadata dissector id to get
 * @return: METADATA_DISSECTOR_SUCCESS when finished. If further flows are available the function returns
 * PACE2_CPI_CALL_AGAIN.  on success or an enum value indicating the error type
 */

PACE2_CPI_return_state pace2_cpi_foreach_int_get_next_dissector_metadata(PACE2_module * const pace2_module,
                                                                         int const thread_ID,
                                                                         enum dissector_metadata_type const type,
                                                                         PACE2_dissector_metadata_event *metadata_event,
                                                                         PACE2_dissector_foreach_flowinfo *flow_info);


#endif // PACE2_CPI_CLASSIFICATION_FUNC_H

/*********************************************************************************
 ** EOF
 ********************************************************************************/
