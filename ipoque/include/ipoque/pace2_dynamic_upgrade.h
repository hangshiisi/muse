/********************************************************************************/
/**
 ** \file       pace2_dynamic_upgrade.h
 ** \brief      PACE 2 dynamic upgrade definitions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef PACE2_DYNAMIC_UPGRADE_H
#define PACE2_DYNAMIC_UPGRADE_H

#include "pace2_basic_def.h"

/* Public Types *****************************************************************/

/**
 * @brief Return values of pace2_dynamic_upgrade_load_library.
 */
typedef enum {
    PACE2_DYNAMIC_UPGRADE_LOAD_SUCCESSFUL,                      /*!< New library was successfully loaded. */
    PACE2_DYNAMIC_UPGRADE_LOAD_FAILURE,                         /*!< New library could not be loaded. */
    PACE2_DYNAMIC_UPGRADE_LOAD_ALLOCATION_FAILED,               /*!< Memory allocation error. */
    PACE2_DYNAMIC_UPGRADE_LOAD_LIBRARY_NOT_FOUND,               /*!< The given library file could not be opened. */
    PACE2_DYNAMIC_UPGRADE_LOAD_LIBRARY_INCOMPLETE,              /*!< Symbols are missing in the new library file. */
    PACE2_DYNAMIC_UPGRADE_LOAD_LIBRARY_INITIALIZATION_FAILED,   /*!< Module initialization for the new library failed. */
    PACE2_DYNAMIC_UPGRADE_LOAD_LIBRARY_NOT_NEWER,               /*!< The given library file is not a newer version. */
    PACE2_DYNAMIC_UPGRADE_LOAD_LIBRARY_STATE_MACHINE_TOO_BIG,   /*!< Not enough reserved flow/subscriber memory left. An upgrade is not possible */
    PACE2_DYNAMIC_UPGRADE_LOAD_NOT_COMPATIBLE                   /*!< The given library file is not compatible with this version of PACE 2. */
} PACE2_dynamic_upgrade_load_state;

/**
 * @brief Return values of pace2_dynamic_upgrade_activate_loaded_library.
 */
typedef enum {
    PACE2_DYNAMIC_UPGRADE_ACTIVATE_SUCCESSFUL,                      /*!< New library was successfully activated. */
    PACE2_DYNAMIC_UPGRADE_ACTIVATE_NEWEST_VERSION_ALREADY_RUNNING,  /*!< The newest version is already running. */
    PACE2_DYNAMIC_UPGRADE_ACTIVATE_FAILURE                          /*!< An error occurred. */
} PACE2_dynamic_upgrade_activate_state;

/* Public Prototypes ************************************************************/

/**
 * @brief Load a new library file for dynamic upgrade.
 *
 * @param[in]   pace2_module        Pointer to the PACE 2 module.
 * @param[in]   new_library_file    Path to the new library file.
 * @param[in]   force_upgrade       If enabled the new library is loaded even if it is not newer than the current one.
 * @retval  PACE2_DYNAMIC_UPGRADE_LOAD_SUCCESSFUL                       @copydoc PACE2_dynamic_upgrade_load_state::PACE2_DYNAMIC_UPGRADE_LOAD_SUCCESSFUL
 * @retval  PACE2_DYNAMIC_UPGRADE_LOAD_FAILURE                          @copydoc PACE2_dynamic_upgrade_load_state::PACE2_DYNAMIC_UPGRADE_LOAD_FAILURE
 * @retval  PACE2_DYNAMIC_UPGRADE_LOAD_ALLOCATION_FAILED                @copydoc PACE2_dynamic_upgrade_load_state::PACE2_DYNAMIC_UPGRADE_LOAD_ALLOCATION_FAILED
 * @retval  PACE2_DYNAMIC_UPGRADE_LOAD_LIBRARY_NOT_FOUND                @copydoc PACE2_dynamic_upgrade_load_state::PACE2_DYNAMIC_UPGRADE_LOAD_LIBRARY_NOT_FOUND
 * @retval  PACE2_DYNAMIC_UPGRADE_LOAD_LIBRARY_INCOMPLETE               @copydoc PACE2_dynamic_upgrade_load_state::PACE2_DYNAMIC_UPGRADE_LOAD_LIBRARY_INCOMPLETE
 * @retval  PACE2_DYNAMIC_UPGRADE_LOAD_LIBRARY_INITIALIZATION_FAILED    @copydoc PACE2_dynamic_upgrade_load_state::PACE2_DYNAMIC_UPGRADE_LOAD_LIBRARY_INITIALIZATION_FAILED
 * @retval  PACE2_DYNAMIC_UPGRADE_LOAD_LIBRARY_NOT_NEWER                @copydoc PACE2_dynamic_upgrade_load_state::PACE2_DYNAMIC_UPGRADE_LOAD_LIBRARY_NOT_NEWER
 * @retval  PACE2_DYNAMIC_UPGRADE_LOAD_LIBRARY_STATE_MACHINE_TOO_BIG    @copydoc PACE2_dynamic_upgrade_load_state::PACE2_DYNAMIC_UPGRADE_LOAD_LIBRARY_STATE_MACHINE_TOO_BIG
 * @retval  PACE2_DYNAMIC_UPGRADE_LOAD_NOT_COMPATIBLE                   @copydoc PACE2_dynamic_upgrade_load_state::PACE2_DYNAMIC_UPGRADE_LOAD_NOT_COMPATIBLE
 */
PACE2_dynamic_upgrade_load_state pace2_dynamic_upgrade_load_library(PACE2_module * const pace2_module,
                                                                    const char * const new_library_file,
                                                                    const u8 force_upgrade);

/**
 * @brief Activate a previously loaded library file.
 *
 * @param[in]   pace2_module        Pointer to the PACE 2 module.
 * @retval  PACE2_DYNAMIC_UPGRADE_ACTIVATE_SUCCESSFUL                       @copydoc PACE2_dynamic_upgrade_activate_state::PACE2_DYNAMIC_UPGRADE_ACTIVATE_SUCCESSFUL
 * @retval  PACE2_DYNAMIC_UPGRADE_ACTIVATE_NEWEST_VERSION_ALREADY_RUNNING   @copydoc PACE2_dynamic_upgrade_activate_state::PACE2_DYNAMIC_UPGRADE_ACTIVATE_NEWEST_VERSION_ALREADY_RUNNING
 * @retval  PACE2_DYNAMIC_UPGRADE_ACTIVATE_FAILURE                          @copydoc PACE2_dynamic_upgrade_activate_state::PACE2_DYNAMIC_UPGRADE_ACTIVATE_FAILURE
 */
PACE2_dynamic_upgrade_activate_state pace2_dynamic_upgrade_activate_loaded_library(PACE2_module * const pace2_module);

#endif /* PACE2_DYNAMIC_UPGRADE_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
