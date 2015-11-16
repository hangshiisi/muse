/********************************************************************************/
/**
 ** \file       os_events.h
 ** \brief      Operating system detection event definitions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef OS_EVENTS_H
#define OS_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the OS event.
 */
#define PACE2_OS_EVENT_GROUP PACE2_ENGINE_META_DATA_GROUP

/* Public Types *****************************************************************/

/**
 * @brief Supported operating systems of the OS detection.
 */
typedef enum {
    PACE2_OS_NOT_YET_DETECTED = 0,      /**< OS detection is still active and more packets have to be analyzed.*/
    PACE2_OS_NOT_DETECTED,              /**< OS detection is finished and the operating system could not be found.*/
    PACE2_OS_OTHER,                     /**< Found operating system is not known.*/
    PACE2_OS_WINDOWS,                   /**< Any Windows operating system */
    PACE2_OS_LINUX,                     /**< Any Linux operating system */
    PACE2_OS_MACOS,                     /**< Any MacOS operating system */
    PACE2_OS_IOS,                       /**< Any iOS operating system */
    PACE2_OS_SYMBIAN,                   /**< Any Symbian operating system */
    PACE2_OS_ANDROID,                   /**< Any Android operating system */
    PACE2_OS_BLACKBERRY,                /**< Any Blackberry operating system */
    PACE2_OS_WINDOWS_MOBILE,            /**< Any Windows Mobile operating system */

    PACE2_NUMBER_OF_OS_TYPES            /**< Number of implemented OS types. */
} PACE2_OS_type;

/* Event Flags ******************************************************************/

/**
 * @brief OS detection meta data flags.
 */
enum PACE2_OS_data_flags {
    PACE2_OS_TYPE = 0,                  /**< Operating system type flag. */
    PACE2_OS_VERSION_STRING,            /**< OS version string flag. */

    PACE2_NUMBER_OF_OS_DATA_FLAGS       /**< Number of implemented OS detection data flags. */
};

/* Event Structure **************************************************************/

/**
 * @brief Data structure for OS detection events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_OS_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_bitmask meta_data_mask;       /**< Bitmask, which states the available OS meta data. */
    PACE2_OS_type os_type;              /**< Variable of the @ref PACE2_OS_TYPE flag. */
    PACE2_byte_buffer os_version_string;/**< Data structure of the @ref PACE2_OS_VERSION_STRING flag. */
} PACE2_OS_event;

#endif /* OS_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
