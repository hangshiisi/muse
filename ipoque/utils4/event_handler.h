/*
 * event_handler.h
 *
 *  Created on: Mar 18, 2014
 */

#ifndef EVENT_HANDLER_H_
#define EVENT_HANDLER_H_


/* Includes *********************************************************************/

#include <pace2.h>

/* Public Macros ****************************************************************/

/* initialize variable of type PACE2ByteBuffer_t with specific c-string */
#define IPQ_INIT_STRING_BUF(buffer, string) {   \
    buffer.ptr = string;                        \
    buffer.len = strlen(string);                \
}

#define IPQ_ENUM_TO_STRING(val) #val

/** Helper function to write an event to a file pointer for debugging reasons.
 * @param f a FILE pointer with write access. stderr or stdout can be used too.
 * @param event pointer to the event to write.
 */
void pace2_debug_event(FILE * f, PACE2_event const * const event);

#endif /* EVENT_HANDLER_H_ */
