/********************************************************************************/
/**
 ** \file       pace2_debug.h
 ** \brief      PACE 2 debug advanced event definition.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef PACE2_DEBUG_H
#define PACE2_DEBUG_H

#ifndef PACE_KERNEL_LIB

/* Includes *********************************************************************/
#include <stdio.h>

/* Public Prototypes ************************************************************/

/** Helper function to write an advanced/class event to a file pointer for debugging reasons.
 * @param f a FILE pointer with write access. stderr or stdout can be used too.
 * @param event pointer to the event to write.
 */
void pace2_debug_advanced_event(FILE * f, PACE2_event const * const event);

/**
 * @brief Default implementation of the @ref PACE2_config_general.process_information callback. Makes a simple printf to stderr of
 * the given format string and it's arguments.
 *
 * @param thread_ID The thread ID of the thread, from which this callback was called.
 * @param level The kind of information for which this callback was called. see also @ref PACE2_process_information_level.
 * @param user_ptr Is a user_ptr which can be defined from the user over struct PACE2_config_general.process_information_callback_user_ptr
 *                 and is available in every call of this callback function. This can be useful to get access to own data structures or
 *                 keys, which are needed to handle this callback.
 * @param format Is a format string like in printf, which describes the process information.
 * @param args The set of variable arguments, which are passed to this function. Contains the values for the format string like for printf.
 */
void pace2_default_process_information_callback_impl(u32 thread_ID,
                                                     PACE2_process_information_level level,
                                                     void * user_ptr,
                                                     const char *format,
                                                     va_list args);

#endif
#endif /* PACE2_DEBUG_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
