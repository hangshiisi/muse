/********************************************************************************/
/**
 ** \file         pace2_pht.h
 ** \brief        Hash table related API functions
 ** \copyright    ipoque GmbH
 **/
/********************************************************************************/

#ifndef PACE2_PHT_H
#define PACE2_PHT_H

/* Includes *********************************************************************/
#include "pace2_basic_def.h"

/* Public Types *****************************************************************/

/**
 * @brief Size of one flow or subscriber dump.
 */
#define PACE2_PHT_DUMP_DATA_SIZE 128

/**
 * @brief Hash table resize mode
 */
enum PACE2_pht_resize_mode
{
    PACE2_PHT_RESIZE_DISABLED, /*!< Disabled hash table resize. Old elements
                                    will automatically be removed. */
    PACE2_PHT_RESIZE_ENABLED   /*!< The hash table will resize automatically
                                    if it is full. */
};

/**
 * @brief Return state of pht PACE2 functions.
 */
typedef enum {
    PACE2_PHT_SUCCESS = 0,              /*!< Processing was successful. */
    PACE2_PHT_PARAM_MISSING,            /*!< Function parameter is missing. */
    PACE2_PHT_OUT_OF_MEMORY,            /*!< Processing failed, because no more memory available. */
    PACE2_PHT_FAILURE,                  /*!< Processing failed. */
    PACE2_PHT_MORE_ELEMENTS             /*!< More elements are available. */
} PACE2_pht_return_state;

/**
 * @brief The reason for a hash table element removal
 */
typedef enum pace2_pht_removal_reason {
    PHT_NONE,     /*!< Default value. The item was removed without a reason. This should not happen.*/
    PHT_TIMEOUT,  /*!< the item was removed because of a timeout */
    PHT_OVERFLOW, /*!< the item was removed because the hash table was full */
    PHT_DELETED,  /*!< the item was manually removed from the hash table */

    PTH_NUMBER_OF_REASONS   /*!< Number of removal reasons and not a reason itself. */
} PACE2_pht_removal_reason;

/**
 * @brief Hash table configuration structure
 */
struct PACE2_pht_config
{
    u64 memory_size;                        /*!< Amount of memory to allocate
                                                 in bytes. If dynamic resizing is
                                                 enabled this will be the initial
                                                 amount. */
    u32 unique_key_size;                    /*!< Size of the hash table key in
                                                 bytes. Must be multiple of 4. */
    u32 user_buffer_size;                   /*!< Size of a single element to be
                                                 stored. */
    PACE2_timestamp timeout;                /*!< Element timeout in ticks per
                                                 second. */
    pace2_malloc ipq_malloc;                /*!< Pointer to the memory allocation
                                                 function. */
    pace2_free ipq_free;                    /*!< Pointer to the memory
                                                 deallocation function. */
    void *allocation_userptr;               /*!< User pointer that will be given
                                                 to the memory functions */
    enum PACE2_pht_resize_mode resize_mode; /*!< Allow dynamic resizing or not */
    u64 max_memory_size;                    /*!< Maximum amount of memory in
                                                 bytes. Has no effect if
                                                 resizing is disabled. */
    u16 timeout_queues;                     /*!< Number of registered timeout
                                                 queues. */
};

/* Public Prototypes ************************************************************/

/**
 * @brief Apply a default configuration structure to the hash table.
 *
 * @param[in] config    pointer to the configuration structure
 */
void pace2_pht_init_default_config(struct PACE2_pht_config *config);

/**
 * @brief Create a PACE2 hash table.
 *
 * @param[in] config    pointer to the configuration structure
 * @param[in] thread_id hash table thread identifier
 * @retval    pace2_pht pointer to the hash table
 * @retval    NULL      hash table initialization failed
 */
struct pace2_pht * pace2_pht_create(struct PACE2_pht_config *config,
                                    int thread_id);

/**
 * @brief Get the hash table element for a given timestamp.
 *
 * @param[in] pht             pointer to the hash table
 * @param[in] unique_key      pointer to the key
 * @param[in] last_access_ts  a pointer to a variable where the successful
 *                            lookup should store the last insert call for this
 *                            element
 * @retval    the pointer to the hash table data
 * @retval    NULL            failed lookup
 */
void * pace2_pht_lookup_ts(struct pace2_pht *pht, const u8 * unique_key,
                           PACE2_timestamp * last_access_ts);

/**
 * @brief Get the hash table element without using a timestamp.
 *
 * @param[in] pht             pointer to the hash table
 * @param[in] unique_key      pointer to the key
 * @retval    the pointer to the hash table data
 * @retval    NULL            failed lookup
 */
void * pace2_pht_lookup(struct pace2_pht *pht, const u8 * unique_key);

/**
 * @brief Update the timestamp for an element retrieved by a lookup call
 *
 * @param[in] pht                       pointer to the hash table
 * @param[in] user_buffer               pointer to the user data
 * @retval    PACE2_PHT_SUCCESS         @copydoc PACE2_pht_return_state::PACE2_PHT_SUCCESS
 * @retval    PACE2_PHT_PARAM_MISSING   @copydoc PACE2_pht_return_state::PACE2_PHT_PARAM_MISSING
 * @retval    PACE2_PHT_FAILURE         @copydoc PACE2_pht_return_state::PACE2_PHT_FAILURE
 */
PACE2_pht_return_state pace2_pht_update_ts_of_element(struct pace2_pht *pht, void *user_buffer);

/**
 * @brief Insert/update an element into the hash table.
 *
 * This operation cannot fail because the oldest element will be removed if the
 * hash table is full.
 *
 * In case of an insert of an already inserted element its timestamp
 * will get updated.
 *
 * @param[in] pht             pointer to the hash table
 * @param[in] unique_key      pointer to the lookup key
 * @param[out] new_entry      pointer to an u8, will be set to != 0 when the
 *                            insert has created a new entry in the hash table,
 *                            otherwise NULL
 * @retval                    the pointer to the hash table data
 * @retval                    NULL on failure
 */
void * pace2_pht_insert(struct pace2_pht *pht, const u8 * unique_key,
                        u8 * new_entry);

/**
 * @brief Remove one element from the hash table.
 *
 * @param[in] pht             pointer to the hash table
 * @param[in] unique_key                pointer to the lookup key
 * @retval    PACE2_PHT_SUCCESS         @copydoc PACE2_pht_return_state::PACE2_PHT_SUCCESS
 * @retval    PACE2_PHT_PARAM_MISSING   @copydoc PACE2_pht_return_state::PACE2_PHT_PARAM_MISSING
 */
PACE2_pht_return_state pace2_pht_delete(struct pace2_pht *pht, const u8 * unique_key);

/**
 * @brief Free all memory which has been allocated for a hash table.
 *
 * @param[in] pht                       pointer to the hash table
 * @retval    PACE2_PHT_SUCCESS         @copydoc PACE2_pht_return_state::PACE2_PHT_SUCCESS
 * @retval    PACE2_PHT_PARAM_MISSING   @copydoc PACE2_pht_return_state::PACE2_PHT_PARAM_MISSING
 */
PACE2_pht_return_state pace2_pht_destroy(struct pace2_pht *pht);

/**
 * @brief Set the timestamp on the hash table. Should be done before any
 *        insertion or lookup operation.
 *
 * @param[in] pht                       pointer to the hash table
 * @param[in] timestamp                 the timestamp in ticks
 * @retval    PACE2_PHT_SUCCESS         @copydoc PACE2_pht_return_state::PACE2_PHT_SUCCESS
 * @retval    PACE2_PHT_PARAM_MISSING   @copydoc PACE2_pht_return_state::PACE2_PHT_PARAM_MISSING
 */
PACE2_pht_return_state pace2_pht_set_timestamp(struct pace2_pht *pht,
                                               PACE2_timestamp timestamp);

/**
 * @brief Set or change the timeout of a timeout queue.
 *
 * @param[in] pht                       pointer to the hash table
 * @param[in] timeout                   the current timestamp of the hash table can be
 *                                      @ref IPQ_TOH_TIMEOUT_INFINITE for infinite
 *                                      timeouts
 * @param[in] queue                     The event queue for the timeout
 * @retval    PACE2_PHT_SUCCESS         @copydoc PACE2_pht_return_state::PACE2_PHT_SUCCESS
 * @retval    PACE2_PHT_PARAM_MISSING   @copydoc PACE2_pht_return_state::PACE2_PHT_PARAM_MISSING
 * @retval    PACE2_PHT_FAILURE         @copydoc PACE2_pht_return_state::PACE2_PHT_FAILURE
 */
PACE2_pht_return_state pace2_pht_set_timeout(struct pace2_pht *pht,
                                             PACE2_timestamp timeout, u16 queue);

/**
 * @brief Set the timeout queue for the last insert operation.
 *
 * @param[in] pht                       pointer to the hash table
 * @param[in] queue                     the new timeout queue for the element
 * @retval    PACE2_PHT_SUCCESS         @copydoc PACE2_pht_return_state::PACE2_PHT_SUCCESS
 * @retval    PACE2_PHT_PARAM_MISSING   @copydoc PACE2_pht_return_state::PACE2_PHT_PARAM_MISSING
 * @retval    PACE2_PHT_FAILURE         @copydoc PACE2_pht_return_state::PACE2_PHT_FAILURE
 */
PACE2_pht_return_state pace2_pht_set_timeout_queue(struct pace2_pht *pht, u16 queue);

/**
 * @brief Delete all entries from the hash table.
 *
 * @param[in] pht             pointer to the hash table
 */
void pace2_pht_clear(struct pace2_pht *pht);

/**
 * @brief Retrieve the current timeout for a specific queue.
 *
 * @param[in] pht             pointer to the hash table
 * @param[in] queue           the timeout queue
 * @retval                    the timeout value
 */
PACE2_timestamp pace2_pht_get_timeout(struct pace2_pht *pht, u16 queue);

/**
 * @brief Initialize a foreach operation on the hash table. Should be done
 *        before calling @ref pace2_pht_foreach_get_next_element
 *
 * @param[in] pht                       pointer to the hash table
 * @retval    PACE2_PHT_SUCCESS         @copydoc PACE2_pht_return_state::PACE2_PHT_SUCCESS
 * @retval    PACE2_PHT_PARAM_MISSING   @copydoc PACE2_pht_return_state::PACE2_PHT_PARAM_MISSING
 */
PACE2_pht_return_state pace2_pht_foreach_init(struct pace2_pht *pht);

/**
 * @brief Get the next hash table element.
 *
 * @param[in] pht                           pointer to the hash table
 * @param[out] unique_key                   pointer to the hash table element
 * @param[out] user_buffer                  pointer to the user pointer
 * @param[out] last_timestamp               timestamp of the current element
 * @retval     PACE2_PHT_SUCCESS            the foreach operation is done
 * @retval     PACE2_PHT_PARAM_MISSING      @copydoc PACE2_pht_return_state::PACE2_PHT_PARAM_MISSING
 * @retval     PACE2_PHT_MORE_ELEMENTS      @copydoc PACE2_pht_return_state::PACE2_PHT_MORE_ELEMENTS
 */
PACE2_pht_return_state pace2_pht_foreach_get_next_element(struct pace2_pht *pht,
                                u8 **unique_key, void **user_buffer,
                                PACE2_timestamp *last_timestamp);

/**
 * @brief Get the size of a hash table.
 *
 * @param[in] elements         number of elements
 * @param[in] unique_key_size  size of the key element
 * @param[in] user_buffer_size size of the data per key element
 * @retval                     the memory size in bytes
 */
unsigned long pace2_pht_calculate_hash_size(u32 elements, u32 unique_key_size,
                                            u32 user_buffer_size);

/**
 * @brief Get the current active timeout queue.
 *
 * @param[in] pht   pointer to the hash table
 * @retval          the queue of the last insert operation
 */
u16 pace2_pht_get_timeout_queue(struct pace2_pht *pht);

/**
 * @brief Get the number of elements in the hash table.
 *
 * @param[in] pht   pointer to the hash table
 * @retval          number of hash table elements
 */
u32 pace2_pht_number_of_elements(struct pace2_pht *pht);

/**
 * @brief Get the number of used elements for a hash table.
 *
 * @param[in] pht   pointer to the hash table
 * @retval          number of used hash table elements
 */
u32 pace2_pht_used_elements(struct pace2_pht *pht);

/**
 * @brief Get the maximum number of used elements in the hash table.
 *
 * @param[in] pht   pointer to the hash table
 * @retval          number of maximum used elements
 */
u32 pace2_pht_maximum_number_of_used_elements(struct pace2_pht *pht);

/**
 * @brief Get the raw insert pointer from the last insert operation.
 *
 * This can be used to retrieve the last accessed unique and the last accessed
 * user data pointer.
 *
 * @param[in] pht                   pointer to the hash table
 * @retval    pace2_pht_raw_element pointer to the raw insert element
 * @retval                          NULL on failure
 */
struct pace2_pht_raw_element *pace2_pht_get_last_inserted_raw_element(
                                                    struct pace2_pht *pht);

/**
 * @brief Get the size of the key element as initialized from
 *        @ref pace2_pht_create
 *
 * @param[in] pht   pointer to the hash table
 * @retval          the key element size
 */
u32 pace2_pht_get_unique_key_size(struct pace2_pht *pht);

/**
 * @brief Get the size of the user data as initialized from
 *        @ref pace2_pht_create
 *
 * @param[in] pht   pointer to the hash table
 * @retval          the user data size per element
 */
u32 pace2_pht_get_user_buffer_size(struct pace2_pht *pht);

/**
 * @brief Get the timestamp of the oldest entry in the hash table.
 *
 * @param[in] pht   pointer to the hash table
 * @retval          timestamp of the oldest entry or 0 if there is none
 */
PACE2_timestamp pace2_pht_get_timestamp_of_oldest_entry(struct pace2_pht *pht);

/**
 * @brief Get the pointer to the unique key for the given user data pointer.
 *
 * @param[in] pht          pointer to the hash table
 * @param[in] user_buffer  pointer to the user data, must be a valid element
 * @retval                 the pointer to the unique key
 * @retval                 NULL on failure
 */
const void * pace2_pht_get_unique_key_from_user_buffer(struct pace2_pht *pht,
                                                       const void *user_buffer);

/**
 * @brief Reserve elements in the hash table.
 *
 * It is possible to check whether enough space is available for new elements
 * so that the next insert is guaranteed to succeed without removing an element.
 * This is useful when processing needs to be done before removing the elements.
 * If an element is overwritten by the insert operation the memory contents of the
 * previous element are no longer accessible. By reserving the required amount of
 * elements before the insert it is still possible to access the memory of the
 * elements that will be removed.
 *
 * This function adds the number of elements to be reserved to an internal reservation list.
 * The function @ref pace2_pht_get_next_element_to_remove has to be called to
 * remove elements in the case this functions returns with the value @ref PACE2_PHT_OUT_OF_MEMORY
 * to have enough space for new elements.
 *
 * @param[in] pht                       pointer to the hash table
 * @param[in] elements                  number of elements to be reserved
 * @retval    PACE2_PHT_SUCCESS         enough free element space is available
 * @retval    PACE2_PHT_PARAM_MISSING   @copydoc PACE2_pht_return_state::PACE2_PHT_PARAM_MISSING
 * @retval    PACE2_PHT_OUT_OF_MEMORY   @copydoc PACE2_pht_return_state::PACE2_PHT_OUT_OF_MEMORY
 */
PACE2_pht_return_state pace2_pht_reserve_elements(struct pace2_pht *pht, u32 elements);

/**
 * @brief Get the next elements which will be removed.
 *
 * Useful when iterating over removed elements is needed.
 *
 * @param[in]  pht              pointer to the hash table
 * @param[out] call_again       1 if more elements will be removed
 *                              0 otherwise (optional)
 * @param[out] removal_reason   The reason for the removal (optional)
 * @retval                      pointer to the user data of the next removed
 *                              element
 * @retval                      NULL if no elements are left
 * @retval                      NULL if an error occured
 */
void * pace2_pht_get_next_element_to_remove(struct pace2_pht *pht, u8 *call_again,
                                enum pace2_pht_removal_reason *removal_reason);

/**
 * @brief Decapsulate the IPv4 or IPv6 header and do an insert operation on a
 *        hash table with the 5 tuple.
 *
 * The maximum tunnel decapsulation level is used from the PACE2 configuration.
 *
 * @param[in] module          pointer to the detection module
 * @param[in] pht             pointer to the hash table
 * @param[in] thread_id       hash table thread identifier
 * @param[in] ip_ptr          pointer to the ip header
 * @param[in] ipsize          length of the ip packet
 * @param[out] new_connection set to != 0 for a new element
 * @retval                    pointer to the flow structure
 * @retval                    NULL on failure
 */
void * pace2_pht_get_current_flow_v4_v6_decapsulate(PACE2_module *module,
                            u16 thread_id, struct pace2_pht *pht,
                            const void *ip_ptr, u16 ipsize, u8 * new_connection);

/**
 * @brief Dump the flow information in the given buffer.
 *
 * @param[in]  module          pointer to the detection module
 * @param[in]  thread_id       hash table thread identifier
 * @param[in]  flow            a void pointer to the flow
 * @param[out] buffer          the buffer where to dump in,
 *                             needs the minimum size of
 *                             @ref PACE2_PHT_DUMP_DATA_SIZE
 */
void pace2_pht_dump_flow_data(PACE2_module *module, int thread_id,
                              const void *flow, u8 *buffer);

/**
 * @brief Load the flow information from the given flow dump.
 *
 * @param[in]  module          pointer to the detection module
 * @param[in]  thread_id       hash table thread identifier
 * @param[in]  flow            a void pointer to the flow
 * @param[in]  flow_dump       the dump from which the flow
 *                             information are loaded
 */
void pace2_pht_load_flow_dump(PACE2_module *module, int thread_id,
                              void *flow, const u8 *flow_dump);

/**
 * @brief Dump the subscriber information in the given buffer.
 *
 * @param[in]  module          pointer to the detection module
 * @param[in]  thread_id       hash table thread identifier
 * @param[in]  id              a void pointer to the subscriber
 * @param[out] buffer          the buffer where to dump in,
 *                             needs the minimum size of
 *                             @ref PACE2_PHT_DUMP_DATA_SIZE
 */
void pace2_pht_dump_id_data(PACE2_module *module, int thread_id,
                            void *id, u8 *buffer);

/**
 * @brief Load the subscriber information from the given id dump.
 *
 * @param[in]  module          pointer to the detection module
 * @param[in]  thread_id       hash table thread identifier
 * @param[in]  id              a void pointer to the subscriber
 * @param[in]  id_dump         the dump from which the subscriber
 *                             information are loaded
 */
void pace2_pht_load_id_dump(PACE2_module *module, int thread_id,
                            void *id, const u8 *id_dump);

#endif /* PACE2_PHT_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
