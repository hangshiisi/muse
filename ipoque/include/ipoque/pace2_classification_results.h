/********************************************************************************/
/**
 ** \file       pace2_classification_results.h
 ** \brief      PACE 2 classification results definitions
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef PACE2_CLASSIFICATION_RESULTS_H
#define PACE2_CLASSIFICATION_RESULTS_H

/* Includes *********************************************************************/

#include "pace2_applications.h"
#include "pace2_attributes.h"
#include "pace2_protocols.h"
#include "pace2_protocols_bitmask.h"

/* Public Macros ****************************************************************/

#define PACE2_PROTOCOL_STACK_MAX_DEPTH 4                /**< Depth of the classification protocol stack inclusive
                                                             the field of the transfered content.*/
#define PACE2_APPLICATION_ATTRIBUTE_LIST_MAX_SIZE 3     /**< Maximum number of set application attributes. */
#define PACE2_PROTOCOL_ATTRIBUTE_LIST_MAX_SIZE 2        /**< Maximum number of set protocol attributes. */

/* Public Types *****************************************************************/

/**
 * @brief Enumeration defining the indices into the protocol stack for specific layers.
 */
typedef enum {
    PACE2_RESULT_PROTOCOL_LAYER_3 = 0,
    PACE2_RESULT_PROTOCOL_LAYER_4 = 1,
    PACE2_RESULT_PROTOCOL_LAYER_7 = 2,
    PACE2_RESULT_TRANSFERRED_CONTENT = 3
} PACE2_result_protocol_layer_indexes;

/**
 * @brief Definition of the classification protocol stack.
 */
typedef struct {
    PACE2_protocols entry[PACE2_PROTOCOL_STACK_MAX_DEPTH];  /**< Protocol stack entries. Use  the defined enumerations
                                                                 of @ref PACE2_result_protocol_layer_indexes to access
                                                                 the specific layers. */
    u8 length;                                              /**< Number of set protocol stack entries. */
} PACE2_protocol_stack;

/**
 * @brief Definition of the protocol attribute list.
 */
typedef struct {
    PACE2_protocol_attributes list[PACE2_PROTOCOL_ATTRIBUTE_LIST_MAX_SIZE]; /**< List of set protocol attributes. */
    u8 length;                                              /**< Number of set protocol attributes. */
} PACE2_protocol_attribute_list;

/**
 * @brief Definition of the application attribute list.
 */
typedef struct {
    PACE2_application_attributes list[PACE2_APPLICATION_ATTRIBUTE_LIST_MAX_SIZE];   /**< List of set application attributes. */
    u8 length;                                              /**< Number of set application attributes. */
} PACE2_application_attribute_list;

/* Public Prototypes ************************************************************/

/**
 * @brief This function checks, if a given application attribute is set.
 *
 * @param[in]   attr_list   Pointer to an application attribute list which should get tested.
 * @param[in]   attr        The application attribute to check if it is set.
 * @returns 1 if attribute is set, 0 otherwise.
 */
int pace2_classification_is_application_attribute_set(PACE2_application_attribute_list const * const attr_list,
                                                      PACE2_application_attributes const attr);

/**
 * @brief This function checks, if a given protocol attribute is set.
 *
 * @param[in]   attr_list   Pointer to a protocol attribute list which should get tested.
 * @param[in]   attr        The protocol attribute to check if it is set.
 * @returns 1 if attribute is set, 0 otherwise.
 */
int pace2_classification_is_protocol_attribute_set(PACE2_protocol_attribute_list const * const attr_list,
                                                   PACE2_protocol_attributes const attr);

/**
 * @brief Returns a short string representing the given application.
 *
 * @param[in]   app_id  ID of the application to retrieve the short string for.
 * @retval      !=NULL  Zero-terminated string representing the given application.
 * @retval      NULL    Given application ID is unknown.
 */
char const *pace2_get_application_short_str(PACE2_applications const app_id);

/**
 * @brief Returns a long string representing the given application.
 *
 * @param[in]   app_id  ID of the application to retrieve the long string for.
 * @retval      !=NULL  Zero-terminated string representing the given application.
 * @retval      NULL    Given application ID is unknown.
 */
char const *pace2_get_application_long_str(PACE2_applications const app_id);

/**
 * @brief Returns a short string representing the given protocol.
 *
 * @param[in]   proto_id    ID of the protocol to retrieve the short string for.
 * @retval      !=NULL      Zero-terminated string representing the given protocol.
 * @retval      NULL        Given protocol ID is unknown.
 */
char const *pace2_get_protocol_short_str(PACE2_protocols const proto_id);

/**
 * @brief Returns a long string representing the given protocol.
 *
 * @param[in]   proto_id    ID of the protocol to retrieve the long string for.
 * @retval      !=NULL      Zero-terminated string representing the given protocol.
 * @retval      NULL        Given protocol ID is unknown.
 */
char const *pace2_get_protocol_long_str(PACE2_protocols const proto_id);

/**
 * @brief Returns a string describing the given protocol.
 *
 * @param[in]   proto_id    ID of the protocol to retrieve the description for.
 * @retval      !=NULL      Zero-terminated string containing the description of the given protocol.
 * @retval      NULL        Given protocol ID is unknown.
 */
char const *pace2_get_protocol_descr_str(PACE2_protocols const proto_id);

/**
 * @brief Returns a string representing the given application attribute.
 *
 * @param[in]   attribute_id    ID of the application attribute to retrieve the string for.
 * @retval      !=NULL          Zero-terminated string representing the given application attribute.
 * @retval      NULL            Given attribute ID is unknown.
 */
char const *pace2_get_application_attribute_str(PACE2_application_attributes const attribute_id);

/**
 * @brief Returns a string representing the given protocol attribute.
 *
 * @param[in]   attribute_id    ID of the protocol attribute to retrieve the string for.
 * @retval      !=NULL          Zero-terminated string representing the given protocol attribute.
 * @retval      NULL            Given attribute ID is unknown.
 */
char const *pace2_get_protocol_attribute_str(PACE2_protocol_attributes const attribute_id);

#endif /* PACE2_CLASSIFICATION_RESULTS_H */
