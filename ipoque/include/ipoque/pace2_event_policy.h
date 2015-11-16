/********************************************************************************/
/**
 ** \file       pace2_event_policy.h
 ** \brief      PACE 2 event restriction policy.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef PACE2_EVENT_POLICY_H
#define PACE2_EVENT_POLICY_H

/* Includes *********************************************************************/
#include "pace2_event_types.h"

/* Public Types *****************************************************************/

/**
 * @brief Event policy operation modes.
 */
typedef enum {
    PACE2_PROGRESSIVE = 0,              /*!< Flow or global policy have to match to accept event. */
    PACE2_CONSERVATIVE,                 /*!< Flow and global policy have to match to accept event. */
    PACE2_GLOBAL_LEADING,               /*!< Global policy has to match to accept event. */
    PACE2_FLOW_LEADING                  /*!< Flow policy has to match to accept event. */
} PACE2_epol_operation_mode;

/**
 * @brief Return state of event policy functions.
 */
typedef enum {
    PACE2_EPOL_SUCCESS,                 /*!< Processing was successful. */
    PACE2_EPOL_EVENT_ACCEPTED,          /*!< Policy matched and the event is accepted. */
    PACE2_EPOL_EVENT_REFUSED,           /*!< Event declined. */
    PACE2_EPOL_PARAM_MISSING,           /*!< Function parameter is missing. */
    PACE2_EPOL_CONFIG_INVALID,          /*!< Configuration not available or invalid. */
    PACE2_EPOL_UNKNOWN_ERROR            /*!< Processing failed. */
} PACE2_epol_return_state;

/**
 * @brief Event policy data structure.
 */
typedef struct {
    PACE2_bitmask event_types: PACE2_NUMBER_OF_EVENTS;  /*!< Bitmask to state the enabled events. */
} PACE2_epol_structure;

/* Public Prototypes ************************************************************/

#include "pace2_config.h"

/**
 * @brief Copy the given policy to the config event policy of PACE2.
 *
 * @param[in]   pace2_config    Pointer to the PACE 2 module configuration.
 * @param[in]   policy          Pointer to the PACE 2 event policy.
 * @retval  PACE2_EPOL_SUCCESS          @copydoc PACE2_epol_return_state::PACE2_EPOL_SUCCESS
 * @retval  PACE2_EPOL_PARAM_MISSING    @copydoc PACE2_epol_return_state::PACE2_EPOL_PARAM_MISSING
 */
PACE2_epol_return_state pace2_epol_copy_config_policy(struct PACE2_global_config * const pace2_config,
                                                      PACE2_epol_structure * const policy);

/**
 * @brief Deploy the given policy to the global event policy of PACE2.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   policy          Pointer to the PACE 2 event policy.
 * @retval  PACE2_EPOL_SUCCESS          @copydoc PACE2_epol_return_state::PACE2_EPOL_SUCCESS
 * @retval  PACE2_EPOL_PARAM_MISSING    @copydoc PACE2_epol_return_state::PACE2_EPOL_PARAM_MISSING
 */
PACE2_epol_return_state pace2_epol_deploy_global_policy(PACE2_module * const pace2_module,
                                                        PACE2_epol_structure * const policy);

/**
 * @brief Deploy the given policy to the given flow event policy of PACE2.
 *
 * @param[in]   pace2_flow      Pointer to the PACE 2 flow information.
 * @param[in]   policy          Pointer to the PACE 2 event policy.
 * @retval  PACE2_EPOL_SUCCESS          @copydoc PACE2_epol_return_state::PACE2_EPOL_SUCCESS
 * @retval  PACE2_EPOL_PARAM_MISSING    @copydoc PACE2_epol_return_state::PACE2_EPOL_PARAM_MISSING
 */
PACE2_epol_return_state pace2_epol_deploy_flow_policy(void * const pace2_flow,
                                                      PACE2_epol_structure * const policy);

/**
 * @brief Enable/Disable all events for the given event policy.
 *
 * @param[in]   policy          Pointer to the PACE 2 event policy.
 * @param[in]   enable_all      @arg If @ref IPQ_TRUE all events will be enabled.
 *                              @arg If @ref IPQ_FALSE all events will be disabled.
 * @retval  PACE2_EPOL_SUCCESS          @copydoc PACE2_epol_return_state::PACE2_EPOL_SUCCESS
 * @retval  PACE2_EPOL_PARAM_MISSING    @copydoc PACE2_epol_return_state::PACE2_EPOL_PARAM_MISSING
 */
PACE2_epol_return_state pace2_epol_set_policy(PACE2_epol_structure * const policy,
                                              PACE2_boolean const enable_all);

/**
 * @brief Set the config event policy for all events.
 *
 * @param[in]   pace2_config    Pointer to the PACE 2 module configuration.
 * @param[in]   enable_all      @arg If @ref IPQ_TRUE all events will be enabled.
 *                              @arg If @ref IPQ_FALSE all events will be disabled.
 * @retval  PACE2_EPOL_SUCCESS          @copydoc PACE2_epol_return_state::PACE2_EPOL_SUCCESS
 * @retval  PACE2_EPOL_PARAM_MISSING    @copydoc PACE2_epol_return_state::PACE2_EPOL_PARAM_MISSING
 */
PACE2_epol_return_state pace2_epol_set_config_policy(struct PACE2_global_config * const pace2_config,
                                                     PACE2_boolean const enable_all);

/**
 * @brief Set the global event policy for all events.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   enable_all      @arg If @ref IPQ_TRUE all events will be enabled.
 *                              @arg If @ref IPQ_FALSE all events will be disabled.
 * @retval  PACE2_EPOL_SUCCESS          @copydoc PACE2_epol_return_state::PACE2_EPOL_SUCCESS
 * @retval  PACE2_EPOL_PARAM_MISSING    @copydoc PACE2_epol_return_state::PACE2_EPOL_PARAM_MISSING
 */
PACE2_epol_return_state pace2_epol_set_global_policy(PACE2_module * const pace2_module,
                                                     PACE2_boolean const enable_all);

/**
 * @brief Set the flow event policy for all events.
 *
 * @param[in]   pace2_flow      Pointer to the PACE 2 flow information.
 * @param[in]   enable_all      @arg If @ref IPQ_TRUE all events will be enabled.
 *                              @arg If @ref IPQ_FALSE all events will be disabled.
 * @retval  PACE2_EPOL_SUCCESS          @copydoc PACE2_epol_return_state::PACE2_EPOL_SUCCESS
 * @retval  PACE2_EPOL_PARAM_MISSING    @copydoc PACE2_epol_return_state::PACE2_EPOL_PARAM_MISSING
 */
PACE2_epol_return_state pace2_epol_set_flow_policy(void * const pace2_flow,
                                                   PACE2_boolean const enable_all);

/**
 * @brief Enable/Disable all events for of the given group in the given event policy.
 *
 * @param[in]   policy          Pointer to the PACE 2 event policy.
 * @param[in]   event_group     Event group for which the operation has to be performed.
 * @param[in]   enable_group    @arg If @ref IPQ_TRUE the events of the given group will be enabled.
 *                              @arg If @ref IPQ_FALSE the events of the given group will be disabled.
 * @retval  PACE2_EPOL_SUCCESS          @copydoc PACE2_epol_return_state::PACE2_EPOL_SUCCESS
 * @retval  PACE2_EPOL_UNKNOWN_ERROR    @copydoc PACE2_epol_return_state::PACE2_EPOL_UNKNOWN_ERROR
 * @retval  PACE2_EPOL_PARAM_MISSING    @copydoc PACE2_epol_return_state::PACE2_EPOL_PARAM_MISSING
 */
PACE2_epol_return_state pace2_epol_set_policy_of_group(PACE2_epol_structure * const policy,
                                                       PACE2_event_groups const event_group,
                                                       PACE2_boolean const enable_group);

/**
 * @brief Set the config event policy for a group of events.
 *
 * @param[in]   pace2_config    Pointer to the PACE 2 module configuration.
 * @param[in]   event_group     Event group for which the operation has to be performed.
 * @param[in]   enable_group    @arg If @ref IPQ_TRUE the events of the given group will be enabled.
 *                              @arg If @ref IPQ_FALSE the events of the given group will be disabled.
 * @retval  PACE2_EPOL_SUCCESS          @copydoc PACE2_epol_return_state::PACE2_EPOL_SUCCESS
 * @retval  PACE2_EPOL_UNKNOWN_ERROR    @copydoc PACE2_epol_return_state::PACE2_EPOL_UNKNOWN_ERROR
 * @retval  PACE2_EPOL_PARAM_MISSING    @copydoc PACE2_epol_return_state::PACE2_EPOL_PARAM_MISSING
 * @retval  PACE2_EPOL_UNKNOWN_ERROR    Given event group is unknown.
 */
PACE2_epol_return_state pace2_epol_set_config_policy_of_group(struct PACE2_global_config * const pace2_config,
                                                              PACE2_event_groups const event_group,
                                                              PACE2_boolean const enable_group);

/**
 * @brief Set the global event policy for a group of events.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   event_group     Event group for which the operation has to be performed.
 * @param[in]   enable_group    @arg If @ref IPQ_TRUE the events of the given group will be enabled.
 *                              @arg If @ref IPQ_FALSE the events of the given group will be disabled.
 * @retval  PACE2_EPOL_SUCCESS          @copydoc PACE2_epol_return_state::PACE2_EPOL_SUCCESS
 * @retval  PACE2_EPOL_UNKNOWN_ERROR    @copydoc PACE2_epol_return_state::PACE2_EPOL_UNKNOWN_ERROR
 * @retval  PACE2_EPOL_PARAM_MISSING    @copydoc PACE2_epol_return_state::PACE2_EPOL_PARAM_MISSING
 * @retval  PACE2_EPOL_UNKNOWN_ERROR    Given event group is unknown.
 */
PACE2_epol_return_state pace2_epol_set_global_policy_of_group(PACE2_module * const pace2_module,
                                                              PACE2_event_groups const event_group,
                                                              PACE2_boolean const enable_group);

/**
 * @brief Set the flow event policy for a group of events.
 *
 * @param[in]   pace2_flow      Pointer to the PACE 2 flow information.
 * @param[in]   event_group     Event group for which the operation has to be performed.
 * @param[in]   enable_group    @arg If @ref IPQ_TRUE the events of the given group will be enabled.
 *                              @arg If @ref IPQ_FALSE the events of the given group will be disabled.
 * @retval  PACE2_EPOL_SUCCESS          @copydoc PACE2_epol_return_state::PACE2_EPOL_SUCCESS
 * @retval  PACE2_EPOL_UNKNOWN_ERROR    @copydoc PACE2_epol_return_state::PACE2_EPOL_UNKNOWN_ERROR
 * @retval  PACE2_EPOL_PARAM_MISSING    @copydoc PACE2_epol_return_state::PACE2_EPOL_PARAM_MISSING
 * @retval  PACE2_EPOL_UNKNOWN_ERROR    Given event group is unknown.
 */
PACE2_epol_return_state pace2_epol_set_flow_policy_of_group(void * const pace2_flow,
                                                            PACE2_event_groups const event_group,
                                                            PACE2_boolean const enable_group);

/**
 * @brief Enable/Disable the given event in the given event policy.
 *
 * @param[in]   policy          Pointer to the PACE 2 event policy.
 * @param[in]   event_type      Event type for which the operation has to be performed.
 * @param[in]   enable_event    @arg If @ref IPQ_TRUE the event will be enabled.
 *                              @arg If @ref IPQ_FALSE the event will be disabled.
 * @retval  PACE2_EPOL_SUCCESS          @copydoc PACE2_epol_return_state::PACE2_EPOL_SUCCESS
 * @retval  PACE2_EPOL_PARAM_MISSING    @copydoc PACE2_epol_return_state::PACE2_EPOL_PARAM_MISSING
 */
PACE2_epol_return_state pace2_epol_set_policy_of_event(PACE2_epol_structure * const policy,
                                                       PACE2_event_type const event_type,
                                                       PACE2_boolean const enable_event);

/**
 * @brief Set the config event policy for an event.
 *
 * @param[in]   pace2_config    Pointer to the PACE 2 module configuration.
 * @param[in]   event_type      Event type for which the operation has to be performed.
 * @param[in]   enable_event    @arg If @ref IPQ_TRUE the event will be enabled.
 *                              @arg If @ref IPQ_FALSE the event will be disabled.
 * @retval  PACE2_EPOL_SUCCESS          @copydoc PACE2_epol_return_state::PACE2_EPOL_SUCCESS
 * @retval  PACE2_EPOL_PARAM_MISSING    @copydoc PACE2_epol_return_state::PACE2_EPOL_PARAM_MISSING
 */
PACE2_epol_return_state pace2_epol_set_config_policy_of_event(struct PACE2_global_config * const pace2_config,
                                                              PACE2_event_type const event_type,
                                                              PACE2_boolean const enable_event);

/**
 * @brief Set the global event policy for an event.
 *
 * @param[in]   pace2_module    Pointer to the PACE 2 module.
 * @param[in]   event_type      Event type for which the operation has to be performed.
 * @param[in]   enable_event    @arg If @ref IPQ_TRUE the event will be enabled.
 *                              @arg If @ref IPQ_FALSE the event will be disabled.
 * @retval  PACE2_EPOL_SUCCESS          @copydoc PACE2_epol_return_state::PACE2_EPOL_SUCCESS
 * @retval  PACE2_EPOL_PARAM_MISSING    @copydoc PACE2_epol_return_state::PACE2_EPOL_PARAM_MISSING
 */
PACE2_epol_return_state pace2_epol_set_global_policy_of_event(PACE2_module * const pace2_module,
                                                              PACE2_event_type const event_type,
                                                              PACE2_boolean const enable_event);

/**
 * @brief Set the flow event policy for an event.
 *
 * @param[in]   pace2_flow      Pointer to the PACE 2 flow information.
 * @param[in]   event_type      Event type for which the operation has to be performed.
 * @param[in]   enable_event    @arg If @ref IPQ_TRUE the event will be enabled.
 *                              @arg If @ref IPQ_FALSE the event will be disabled.
 * @retval  PACE2_EPOL_SUCCESS          @copydoc PACE2_epol_return_state::PACE2_EPOL_SUCCESS
 * @retval  PACE2_EPOL_PARAM_MISSING    @copydoc PACE2_epol_return_state::PACE2_EPOL_PARAM_MISSING
 */
PACE2_epol_return_state pace2_epol_set_flow_policy_of_event(void * const pace2_flow,
                                                            PACE2_event_type const event_type,
                                                            PACE2_boolean const enable_event);

#endif /* PACE2_EVENT_POLICY_H */
