/********************************************************************************/
/**
 ** \file       pace2_generic_func.h
 ** \brief      PACE 2 generic function definitions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef PACE2_GENERIC_FUNC_H
#define PACE2_GENERIC_FUNC_H

/* Public Prototypes ************************************************************/

/**
 * @brief Initialize a PACE 2 module.
 *
 * @deprecated The usage of this function is deprecated, because the reporting capability
 * for a failed initialization is limited. The function @ref pace2_init should be used
 * instead.
 *
 * @param[in]   config          Pointer to the module configuration structure.
 * @returns     Pointer to the initialized module in the case of success, else NULL.
 */
PACE2_module *pace2_init_module(struct PACE2_global_config * const config);

/**
 * @brief Initialize a PACE 2 module.
 *
 * @param[in]   config          Pointer to the module configuration structure.
 * @param[out]  pace2_module    Pointer-pointer to the module structure
 * @retval  PACE2_SUCCESS                                       @copydoc PACE2_return_state::PACE2_SUCCESS
 * @retval  PACE2_TRACKING_FLOW_TIMEOUT_TOO_SMALL               @copydoc PACE2_return_state::PACE2_TRACKING_FLOW_TIMEOUT_TOO_SMALL
 * @retval  PACE2_INVALID_CONFIGURATION_POINTER                 @copydoc PACE2_return_state::PACE2_INVALID_CONFIGURATION_POINTER
 * @retval  PACE2_INVALID_MODULE_POINTER                        @copydoc PACE2_return_state::PACE2_INVALID_MODULE_POINTER
 * @retval  PACE2_S2_REORDERING_PACKET_BUFFER_SIZE_TOO_SMALL    @copydoc PACE2_return_state::PACE2_S2_REORDERING_PACKET_BUFFER_SIZE_TOO_SMALL
 * @retval  PACE2_NO_DYNAMIC_UPGRADE                            @copydoc PACE2_return_state::PACE2_NO_DYNAMIC_UPGRADE
 * @retval  PACE2_INVALID_GENERAL_ALLOC_FUNCTION_PTR            @copydoc PACE2_return_state::PACE2_INVALID_GENERAL_ALLOC_FUNCTION_PTR
 * @retval  PACE2_INVALID_GENERAL_FREE_FUNCTION_PTR             @copydoc PACE2_return_state::PACE2_INVALID_GENERAL_FREE_FUNCTION_PTR
 * @retval  PACE2_INVALID_GENERAL_REALLOC_FUNCTION_PTR          @copydoc PACE2_return_state::PACE2_INVALID_GENERAL_REALLOC_FUNCTION_PTR
 * @retval  PACE2_INVALID_DYNAMIC_UPGRADE_DLOPEN_FUNCTION_PTR   @copydoc PACE2_return_state::PACE2_INVALID_DYNAMIC_UPGRADE_DLOPEN_FUNCTION_PTR
 * @retval  PACE2_INVALID_DYNAMIC_UPGRADE_DLSYM_FUNCTION_PTR    @copydoc PACE2_return_state::PACE2_INVALID_DYNAMIC_UPGRADE_DLSYM_FUNCTION_PTR
 * @retval  PACE2_INVALID_DYNAMIC_UPGRADE_DLCLOSE_FUNCTION_PTR  @copydoc PACE2_return_state::PACE2_INVALID_DYNAMIC_UPGRADE_DLCLOSE_FUNCTION_PTR
 * @retval  PACE2_DYNAMIC_UPGRADE_RELEASE_MEMORY_AGE_TOO_SMALL  @copydoc PACE2_return_state::PACE2_DYNAMIC_UPGRADE_RELEASE_MEMORY_AGE_TOO_SMALL
 * @retval  PACE2_NO_FLOW_MEMORY_AGE_SET                        @copydoc PACE2_return_state::PACE2_NO_FLOW_MEMORY_AGE_SET
 * @retval  PACE2_NO_SUBSCRIBER_MEMORY_AGE_SET                  @copydoc PACE2_return_state::PACE2_NO_SUBSCRIBER_MEMORY_AGE_SET
 * @retval  PACE2_FAILURE                                       @copydoc PACE2_return_state::PACE2_FAILURE
 */
PACE2_return_state pace2_init(struct PACE2_global_config * const config, PACE2_module ** const pace2_module);

/**
 * @brief Returns a PACE2_return_state as more detailed string representation
 *
 * @param[in] return_state The PACE2_return_state code
 * @returns A string representation of return_state
 */
const char* pace2_return_state_str(PACE2_return_state const return_state);

/**
 * @brief Shut down the PACE 2 module.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module, which should be shut down.
 * @retval  PACE2_SUCCESS       @copydoc PACE2_return_state::PACE2_SUCCESS
 * @retval  PACE2_PARAM_MISSING @copydoc PACE2_return_state::PACE2_PARAM_MISSING
 * @retval  PACE2_FAILURE       Pace 2 module was not freed completely.
 */
PACE2_return_state pace2_exit_module(PACE2_module * pace2_module);

/**
 * @brief Flush all buffered packets for a final processing.
 *
 * This function flushes all buffered packets of the engine.
 * After calling this function, the stored packets are released and should
 * be processed by stage 3 to 5. To get the released packet a call of
 * @ref pace2_s2_get_next_packet is necessary.
 *
 * This function can be used to do a separate call of flushing packets and
 * flushing the internal tracking tables. This is useful to iterate over all
 * PHT entries after processing all packets. In all other cases, the function
 * @ref pace2_flush_engine can be used to do a combined call of functions
 * @ref pace2_flush_packets and @ref pace2_flush_tables.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module, which should be shut down.
 * @param[in]   thread_ID       The ID of the thread currently processing.
 * @retval  PACE2_SUCCESS       @copydoc PACE2_return_state::PACE2_SUCCESS
 * @retval  PACE2_PARAM_MISSING @copydoc PACE2_return_state::PACE2_PARAM_MISSING
 * @retval  PACE2_FAILURE       Given thread ID is not valid.
 */
PACE2_return_state pace2_flush_packets(PACE2_module * const pace2_module, int const thread_ID);

/**
 * @brief Flush all polling hash tables entries.
 *
 * This function clears all polling hash tables entries of the engine.
 * After calling this function, a call of @ref pace2_s5_handle_timeout
 * is necessary to perform the timeout handling.
 *
 * This function can be used to do a separate call of flushing packets and
 * flushing the internal tracking tables. This is useful to iterate over all
 * PHT entries after processing all packets. In all other cases, the function
 * @ref pace2_flush_engine can be used to do a combined call of the functions
 * @ref pace2_flush_packets and @ref pace2_flush_tables.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module, which should be shut down.
 * @param[in]   thread_ID       The ID of the thread currently processing.
 * @retval  PACE2_SUCCESS       @copydoc PACE2_return_state::PACE2_SUCCESS
 * @retval  PACE2_PARAM_MISSING @copydoc PACE2_return_state::PACE2_PARAM_MISSING
 * @retval  PACE2_FAILURE       Given thread ID is not valid.
 */
PACE2_return_state pace2_flush_tables(PACE2_module * const pace2_module, int const thread_ID);

/**
 * @brief Flush PACE 2 engine.
 *
 * The function flushes the PACE 2 engine and clears all polling hash tables in cases
 * the @ref INTERNAL tracking is used for flow or subscriber tracking.
 *
 * This function calls @ref pace2_flush_packets and @ref pace2_flush_tables.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       The ID of the thread currently processing.
 * @retval  PACE2_SUCCESS       @copydoc PACE2_return_state::PACE2_SUCCESS
 * @retval  PACE2_PARAM_MISSING @copydoc PACE2_return_state::PACE2_PARAM_MISSING
 */
PACE2_return_state pace2_flush_engine(PACE2_module * const pace2_module, int thread_ID);

/**
 * @brief Free flow from PACE 2 engine.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       The ID of the thread currently processing.
 * @param[in]   flow            Pointer to flow data,
 * @retval  PACE2_SUCCESS       @copydoc PACE2_return_state::PACE2_SUCCESS
 * @retval  PACE2_PARAM_MISSING @copydoc PACE2_return_state::PACE2_PARAM_MISSING
 */
PACE2_return_state pace2_release_flow(PACE2_module * const pace2_module, int thread_ID, void *flow);

/**
 * @brief Get next pending event from the event queue.
 *
 * The function returns the next pending event from the event queue.
 * The received event is not longer part of the event queue after the function returned.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       The ID of the thread currently processing.
 * @returns     Pointer to the global event structure on success, else NULL.
 */
PACE2_event *pace2_get_next_event(PACE2_module * const pace2_module, int thread_ID);

/**
 * @brief Get total number of pending event still available in the queue.
 *
 * The function returns the number of pending events in the queue.It returns 0
 * if there are no more events in the queue.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       The ID of the thread currently processing.
 * @returns     Number of available events in the event queue.
 */
u32 pace2_get_number_of_pending_events(PACE2_module * const pace2_module, int thread_ID);

/**
 * @brief Get n number of pending event still available in the queue.
 *
 * The function returns an array of PACE2_event pointers containing pointers to pending events.
 * The num_events parameter specifies the number of events requested while recieved_events represents the
 * actual number of events present in the array. The actual received events (*recieved_events) can be less
 * than the number of requested events (num_events). The returned list of events must be freed using
 * @ref pace2_free_event_list
 * This function returns null in case of failure.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       The ID of the thread currently processing.
 * @param[in]   num_events      The number of pending events which should be returned.
 * @param[out]  recieved_events The actual number of events which are present in the list.
 * @returns     Pointer to array of PACE2_event pointers if successful, else NULL.
 */
PACE2_event** pace2_get_next_n_events(PACE2_module * const pace2_module, int thread_ID, u32 num_events, u32 * recieved_events);

/**
 * @brief Free the list of events after use.
 *
 * The function frees the memory allocated for the list of pointers to the @ref PACE2_event.
 * This function doesn't return anything.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       The ID of the thread currently processing.
 * @param[in]   event_list      Pointer to the list of pointers to PACE2_event structures.
 * @returns     void
 */
void pace2_free_event_list(PACE2_module * const pace2_module, int thread_ID, PACE2_event ** event_list);

/**
 * @brief Get number of implemented sub-protocols of a given PACE 1.x protocol.
 *
 * @deprecated The function is marked as deprecated, because it processes PACE 1.x protocol IDs.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       The ID of the thread currently processing.
 * @param[in]   protocol        PACE 1.x Protocol ID for which the number of sub-protocols should be returned.
 * @retval      0               Will be returned in cases:
 *                              \arg Pointer to the PACE 2 module is NULL
 *                              \arg The protocol has no implemented sub-protocols
 * @retval      > 0             Number of implemented sub-protocols.
 */
u16 pace2_get_number_of_subprotocols(PACE2_module const * const pace2_module, int const thread_ID, u16 const protocol);

/**
 * @brief Get the sub-protocol name of a given PACE 1.x sub-protocol ID.
 *
 * @deprecated The function is marked as deprecated, because it processes PACE 1.x protocol IDs.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       The ID of the thread currently processing.
 * @param[in]   protocol        PACE 1.x Protocol ID for which the sub-protocol name should be returned.
 * @param[in]   subprotocol     PACE 1.x Sub-protocol ID for which the name should be returned.
 * @retval      NULL            Will be returned in cases:
 *                              \arg Pointer to the PACE 2 module is NULL.
 *                              \arg The protocol has no implemented sub-protocols.
 * @retval      != NULL         C-string pointer to the sub-protocol name.
 */
char const *pace2_get_subprotocol_name(PACE2_module const * const pace2_module,
                                       int const thread_ID,
                                       u16 const protocol,
                                       u16 const subprotocol);

/**
 * @brief Get the amount of memory in bytes required per flow.
 *
 * Returns the amount of memory in bytes required per flow including the size of user data.
 * Has to be called after initialization of the given PACE 2 module.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       The ID of the thread currently processing.
 * @retval      0               Pointer to the PACE 2 module is NULL
 * @retval      > 0             Amount of memory per flow.
 */
u32 pace2_get_flow_memory_size(PACE2_module const * const pace2_module, const int thread_ID);


/**
 * @brief Get the amount of memory in bytes required per subscriber.
 *
 * Returns the amount of memory in bytes required per subscriber including the size of user data.
 * Has to be called after initialization of the given PACE 2 module.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       The ID of the thread currently processing.
 * @retval      0               Pointer to the PACE 2 module is NULL
 * @retval      > 0             Amount of memory per subscriber.
 */
u32 pace2_get_subscriber_memory_size(PACE2_module const * const pace2_module, int const thread_ID);

/**
 * @brief Get the unique key of a flow.
 *
 * @param[in]   packet_descriptor Pointer to the packet descriptor of a flow packet.
 * @param[out]  key               Pointer to the created unique flow key.
 * @param[out]  dir               Pointer to the direction flag. Can be NULL;
 * @param[in]   start_stack       Start frame of the stack to get the layer 3 or 4 frame.
 *                                Has to be 0, if all frames should be checked.
 * @retval  PACE2_SUCCESS         @copydoc PACE2_return_state::PACE2_SUCCESS
 * @retval  PACE2_PARAM_MISSING   @copydoc PACE2_return_state::PACE2_PARAM_MISSING
 * @retval  PACE2_FAILURE         @copydoc PACE2_return_state::PACE2_FAILURE
 */
PACE2_return_state pace2_build_flow_key(PACE2_packet_descriptor const * const packet_descriptor,
                                        ipoque_unique_flow_ipv4_and_6_struct_t * const key,
                                        u8 * const dir,
                                        int const start_stack);

/**
 * @brief Get the unique key of the subscriber of a packet.
 *
 * The function builds a unique subscriber key based on a given packet descriptor.
 *
 * @param[in]   packet_descriptor Pointer to the packet descriptor.
 * @param[out]  key               Pointer to the created unique subscriber key.
 * @param[in]   start_stack       Start frame of the stack to get the layer 3 or 4 frame.
 *                                Has to be 0, if all frames should be checked.
 * @param[in]   use_dst           Flag, which indicates that the key should be build on the basis
 *                                of the destination subscriber of the packet.
 * @retval  PACE2_SUCCESS         @copydoc PACE2_return_state::PACE2_SUCCESS
 * @retval  PACE2_PARAM_MISSING   @copydoc PACE2_return_state::PACE2_PARAM_MISSING
 * @retval  PACE2_FAILURE         @copydoc PACE2_return_state::PACE2_FAILURE
 */
PACE2_return_state pace2_build_subscriber_key(PACE2_packet_descriptor const * const packet_descriptor,
                                              PACE2_subscriber_key * const key,
                                              int const start_stack,
                                              PACE2_boolean const use_dst);

/**
 * @brief Enumeration for the possible return values of a foreach callback.
 */
typedef enum pace2_foreach_callback_retval_enum {
    PACE2_FOREACH_NEXT,             /*!< Signals, that the foreach callback wants the next entry, if one more is available. */
    PACE2_FOREACH_BREAK,            /*!< Signals, that the foreach loop can be stopped. */
    PACE2_FOREACH_DELETE_AND_NEXT,  /*!< Signals, that the foreach callback wants to delete the given entry and the next entry is needed, if one more is available. */
} PACE2_foreach_callback_return_state;

/**
 * @brief Type definition for a callback which can be called from the pace2_foreach_flow function.
 *
 * @param[in] pace              The global PACE2 module
 * @param[in] thread_ID         The ID of the thread for which this function is called.
 * @param[in] key               The key data of this flow.
 * @param[in] flow_data         The stored user data for this flow.
 * @param[in] last_timestamp    The timestamp at which the entry has been accessed the last time.
 * @param[in] userptr           The user pointer which was given to pace2_foreach_flow.
 *
 * @retval  PACE2_FOREACH_NEXT              @copydoc pace2_foreach_callback_retval_enum::PACE2_FOREACH_NEXT
 * @retval  PACE2_FOREACH_BREAK             @copydoc pace2_foreach_callback_retval_enum::PACE2_FOREACH_BREAK
 * @retval  PACE2_FOREACH_DELETE_AND_NEXT   @copydoc pace2_foreach_callback_retval_enum::PACE2_FOREACH_DELETE_AND_NEXT
 */
typedef
enum pace2_foreach_callback_retval_enum (*pace2_foreach_flow_callback)(
        PACE2_module *pace,
        const int thread_ID,
        const ipoque_unique_flow_ipv4_and_6_struct_t * const key,
        void *flow_data,
        const PACE2_timestamp last_timestamp,
        void *userptr);

/**
 * @brief Run the given callback for every internal tracked flow.
 *
 * The function calls "callback" for every tracked flow in the internal hash tables. This
 * function is only available if internal flow tracking is enabled.
 *
 * @param[in] pace              The global PACE2 module
 * @param[in] thread_ID         The ID of the thread for which this function is called.
 * @param[in] callback          The callback function which should be called for every entry (tracked flow).
 * @param[in] userptr           A user pointer which is given to the callback function.
 *
 * @retval  PACE2_SUCCESS       @copydoc PACE2_return_state::PACE2_SUCCESS
 * @retval  PACE2_PARAM_MISSING @copydoc PACE2_return_state::PACE2_PARAM_MISSING
 * @retval  PACE2_FAILURE       @copydoc PACE2_return_state::PACE2_FAILURE
 */
PACE2_return_state pace2_foreach_flow(PACE2_module *pace,
                                      const int thread_ID,
                                      pace2_foreach_flow_callback callback,
                                      void *userptr);

/**
 * @brief Type definition for a callback which can be called from the pace2_foreach_subscriber function.
 *
 * @param[in] pace              The global PACE2 module
 * @param[in] thread_ID         The ID of the thread for which this function is called.
 * @param[in] key               The key data of this flow.
 * @param[in] subscriber_data   The stored user data for this subscriber.
 * @param[in] last_timestamp    The timestamp at which the entry has been accessed the last time.
 * @param[in] userptr           The user pointer which was given to pace2_foreach_subscriber.
 *
 * @retval  PACE2_FOREACH_NEXT              @copydoc pace2_foreach_callback_retval_enum::PACE2_FOREACH_NEXT
 * @retval  PACE2_FOREACH_BREAK             @copydoc pace2_foreach_callback_retval_enum::PACE2_FOREACH_BREAK
 * @retval  PACE2_FOREACH_DELETE_AND_NEXT   @copydoc pace2_foreach_callback_retval_enum::PACE2_FOREACH_DELETE_AND_NEXT
 */
typedef
enum pace2_foreach_callback_retval_enum (*pace2_foreach_subscriber_callback)(
        PACE2_module *pace,
        const int thread_ID,
        const PACE2_subscriber_key * const key,
        void *subscriber_data,
        const PACE2_timestamp last_timestamp,
        void *userptr);

/**
 * @brief Run the given callback for every internal tracked subscriber.
 *
 * The function calls "callback" for every tracked subscriber in the internal hash tables. This
 * function is only available, if internal subscriber tracking is enabled.
 *
 * @param[in] pace              The global PACE2 module
 * @param[in] thread_ID         The ID of the thread for which this function is called.
 * @param[in] callback          The callback function which should be called for every entry (tracked subscriber).
 * @param[in] userptr           A user pointer which is given to the callback function.
 *
 * @retval  PACE2_SUCCESS       @copydoc PACE2_return_state::PACE2_SUCCESS
 * @retval  PACE2_PARAM_MISSING @copydoc PACE2_return_state::PACE2_PARAM_MISSING
 * @retval  PACE2_FAILURE       @copydoc PACE2_return_state::PACE2_FAILURE
 */
PACE2_return_state pace2_foreach_subscriber(PACE2_module *pace,
                                            const int thread_ID,
                                            pace2_foreach_subscriber_callback callback,
                                            void *userptr);

/**
 * @brief Generate a classifier token.
 *
 * This function returns the address of a @ref PACE2_classifier_token to be later used by stage 4 processing
 * with a different PACE 2 instance.
 *
 * Please note that the content of the returned @ref PACE2_classifier_token is only valid until the next call to this
 * function with the same pace2_module and thread_ID given.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   thread_ID       The ID of the thread currently processing.
 * @param[out]  token           Pointer variable to return the token address.
 * @retval  PACE2_SUCCESS       @copydoc PACE2_return_state::PACE2_SUCCESS
 * @retval  PACE2_PARAM_MISSING @copydoc PACE2_return_state::PACE2_PARAM_MISSING
 */
PACE2_return_state pace2_generate_classifier_token(PACE2_module * const pace2_module,
                                                   int thread_ID,
                                                   PACE2_classifier_token const **token);

/**
 * @brief Returns the license information for the given thread.
 *
 * This function returns the pointer to a @ref ipoque_pace_license_information_t to get the current license status
 *
 * Please note that the content of the returned @ref ipoque_pace_license_information_t is only valid until the next call of this
 * function with the same pace2_module and thread_ID given.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   license_info    Pointer to a license information structure
 * @param[in]   thread_ID       The ID of the thread currently processing.
 * @retval  PACE2_SUCCESS       @copydoc PACE2_return_state::PACE2_SUCCESS
 * @retval  PACE2_PARAM_MISSING @copydoc PACE2_return_state::PACE2_PARAM_MISSING
 * @retval  PACE2_FAILURE       @copydoc PACE2_return_state::PACE2_FAILURE
 */
PACE2_return_state pace2_get_license_information( PACE2_module * const pace2_module,
                                                  const ipoque_pace_license_information_t **license_info,
                                                  int thread_ID );

/**
 * @brief Set the timeout queue for the last inserted flow operation.
 *
 * This function is only usable with internal tracking
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   queue           ID of the timeout queue to be active for the current flow.
 * @param[in]   thread_id       The ID of the thread currently processing.
 * @retval    PACE2_PHT_SUCCESS         @copydoc PACE2_pht_return_state::PACE2_PHT_SUCCESS
 * @retval    PACE2_PHT_PARAM_MISSING   @copydoc PACE2_pht_return_state::PACE2_PHT_PARAM_MISSING
 * @retval    PACE2_PHT_FAILURE         @copydoc PACE2_pht_return_state::PACE2_PHT_FAILURE
 *                                      \arg Pointer to the PACE 2 module is NULL.
 *                                      \arg External tracking is used.
 *                                      \arg Timeout queue is not configured.
 */
PACE2_pht_return_state pace2_set_internal_flow_timeout_queue( PACE2_module * const pace2_module,
                                                              u16 queue, int thread_id );

#endif /* PACE2_GENERIC_FUNC_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
