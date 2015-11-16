/********************************************************************************/
/**
 ** \file       citrix_events.h
 ** \brief      Citrix meta data event definitions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef CITRIX_EVENTS_H
#define CITRIX_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the basic citrix event.
 */
#define PACE2_BASIC_CITRIX_EVENT_GROUP PACE2_BASIC_PROTOCOL_META_DATA_GROUP

/* Event Flags ******************************************************************/

/**
 * @brief Citrix meta data flags.
 */
enum PACE2_citrix_data_flags {
    PACE2_CITRIX_INITIAL_PROGRAM = 0,       /**< Initial program flag. */
    PACE2_CITRIX_USERNAME,                  /**< Username flag. */
    PACE2_CITRIX_ADDRESS,                   /**< Address flag. */
    PACE2_CITRIX_PORT,                      /**< Port flag. */
    PACE2_CITRIX_CGP_PORT,                  /**< CGP-port flag. */

    PACE2_NUMBER_OF_CITRIX_DATA_FLAGS       /**< Number of implemented flags. */
};

/* Event Structures *************************************************************/

/**
 * @brief Data structure of a citrix meta data event.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_BASIC_CITRIX_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_bitmask meta_data_mask;           /**< Bitmask, which states the available citrix meta data. */
    PACE2_byte_buffer initial_program;      /**< Data structure of the @ref PACE2_CITRIX_INITIAL_PROGRAM flag. */
    PACE2_byte_buffer username;             /**< Data structure of the @ref PACE2_CITRIX_USERNAME flag. */
    u32 address;                            /**< Variable of the @ref PACE2_CITRIX_ADDRESS flag. */
    u16 port;                               /**< Variable of the @ref PACE2_CITRIX_PORT flag. */
    u16 cgp_port;                           /**< Variable of the @ref PACE2_CITRIX_CGP_PORT flag. */
} PACE2_citrix_event;

#endif /* CITRIX_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
