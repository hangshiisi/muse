/********************************************************************************/
/**
 ** \file         pace2_s4_cdd.h
 ** \brief        Custom Defined Decoder related API
 ** \copyright    ipoque GmbH
 **/
/********************************************************************************/

#ifndef PACE2_S4_CDD_H
#define PACE2_S4_CDD_H

/* Includes *********************************************************************/
#include "pace2_basic_def.h"

/* Public Types *****************************************************************/

/**
 * @brief Defines the values which type of descriptor is set within the CDD callback data.
 */
enum PACE2_cdd_descriptor_set {
    PACE2_CDD_DESCRIPTOR_SET_PACKET = 0,            /*!< The packet descriptor pointer is set. */
    PACE2_CDD_DESCRIPTOR_SET_STREAM,                /*!< The stream descriptor pointer is set. */
    PACE2_CDD_DESCRIPTOR_NOT_SET                    /*!< A descriptor is not available. */
};

/**
 * @brief Type to define the data which is passed to the CDD callback.
 */
struct PACE2_cdd_callback_data {
    union {
        struct pace2_packet_descriptor *packet;     /*!< Pointer to the packet descriptor. */
        struct pace2_stream_descriptor *stream;     /*!< Pointer to the stream descriptor. */
    } descriptor;                                   /*!< Named union which stores the available descriptor pointer. */
    enum PACE2_cdd_descriptor_set descriptor_set;        /*!< Variable which indicates the available descriptor pointer. */
    void *cdd_userptr;                              /*!< Pointer to user defined data storage. */
};

/* Public Prototypes ************************************************************/

/**
 * @brief Type which defines the structure of custom defined decoder callback function pointer.
 *
 * @param[in]   pace2_module        Pointer to the pace 2 module.
 * @param[in]   thread_ID           The ID of the thread currently processing.
 * @param[in]   event               Pointer to the event, which triggered calling the CDD callback.
 * @param[in]   callback_data       Pointer to the callback data, see @ref PACE2_cdd_callback_data for details.
 * @returns     Return value is reserved for future extensions. CDD should return @ref PACE2_SUCCESS on success.
 */
typedef PACE2_return_state (*pace2_cdd_callback_t)
                                (PACE2_module * const pace2_module,
                                 int const thread_ID,
                                 PACE2_event const * const event,
                                 struct PACE2_cdd_callback_data * const callback_data);

/**
 * @brief Function to reserve an event slot for a custom defined decoder meta data event.
 *
 * A call to this function reserves a slot inside the event queue to throw an event of
 * type @ref PACE2_CDD_EVENT. The function sets the values of the event members @ref PACE2_cdd_event::cdd_id
 * and @ref PACE2_cdd_event::cdd_event_id. The memory space of the structure member @ref PACE2_cdd_event::cdd_data
 * is not initialized and therefore it contains undefined content. Calling this function is
 * valid only inside the scope of the CDD callback. In all other cases, the
 * function returns without reserving a slot.
 *
 * @param[in]   pace2_module            Pointer to the pace 2 module.
 * @param[in]   thread_ID               The ID of the thread currently processing.
 * @param[in]   cdd_event_id            ID of the custom defined decoder event.
 * @param[out]  new_event               Pointer to store the pointer to the reserved event slot.
 * @retval      PACE2_SUCCESS           @copydoc PACE2_return_state::PACE2_SUCCESS
 * @retval      PACE2_PARAM_MISSING     @copydoc PACE2_return_state::PACE2_PARAM_MISSING
 *                                      The pace2_module or the new_event are not set.
 * @retval      PACE2_CDD_INVALID_FUNCTION_CALL @copydoc PACE2_return_state::PACE2_CDD_INVALID_FUNCTION_CALL
 *                                      @arg Function is not called within CDD callback scope.
 *                                      @arg Decoding stage is disabled or no custom decoder is configured.
 * @retval      PACE2_OUT_OF_MEMORY     @copydoc PACE2_return_state::PACE2_OUT_OF_MEMORY
 *                                      No space left for reserving a slot inside the event queue.
 * @retval      PACE2_EVENT_DECLINED    @copydoc PACE2_return_state::PACE2_EVENT_DECLINED
 *                                      Event policy rules declined event type.
 * @retval      PACE2_FAILURE           @copydoc PACE2_return_state::PACE2_FAILURE
 */
PACE2_return_state pace2_cdd_allocate_event(PACE2_module * const pace2_module,
                                            int const thread_ID,
                                            uint32_t cdd_event_id,
                                            PACE2_event ** new_event);

/**
 * @brief Function to throw an event of a custom defined decoder.
 *
 * A call to this function pushes an event of type @ref PACE2_CDD_EVENT inside the previously reserved slot.
 * It is necessary to allocate an event slot by calling the function @ref pace2_cdd_allocate_event,
 * otherwise the function will return with the value @ref PACE2_FAILURE.
 *
 * @param[in]   pace2_module            Pointer to the pace 2 module.
 * @param[in]   thread_ID               The ID of the thread currently processing.
 * @param[in]   event                   Pointer to the event with the custom defined decoder meta data.
 * @retval      PACE2_SUCCESS           @copydoc PACE2_return_state::PACE2_SUCCESS
 * @retval      PACE2_PARAM_MISSING     @copydoc PACE2_return_state::PACE2_PARAM_MISSING
 *                                      The pace2_module or the event are not set.
 * @retval      PACE2_CDD_INVALID_FUNCTION_CALL @copydoc PACE2_return_state::PACE2_CDD_INVALID_FUNCTION_CALL
 *                                      @arg Function is not called within CDD callback scope.
 *                                      @arg Decoding stage is disabled or no custom decoder is configured.
 * @retval      PACE2_EVENT_DECLINED    @copydoc PACE2_return_state::PACE2_EVENT_DECLINED
 *                                      @arg Event policy rules declined event type.
 *                                      @arg The event type is not @ref PACE2_CDD_EVENT
 * @retval      PACE2_FAILURE           @copydoc PACE2_return_state::PACE2_FAILURE
 *                                      No reserved event slot available.
 */
PACE2_return_state pace2_cdd_throw_event(PACE2_module * const pace2_module,
                                         int const thread_ID,
                                         PACE2_event * event);

#endif // PACE2_S4_CDD_H
