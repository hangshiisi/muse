/********************************************************************************/
/**
 ** \file       ipd_class_http_definitions.h
 ** \brief      Structures and enumerations for all events of class http.
 **/
/********************************************************************************/

#ifndef IPD_CLASS_HTTP_DEFINITIONS_H_
#define IPD_CLASS_HTTP_DEFINITIONS_H_

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif



/** Enumerator for possible class types of a HTTP class event.
 *
 */


/** Main HTTP session structure, each HTTP connection session has this event as initial event.
 */

/** Enumerator for possible states of a HTTP transaction */
enum ipd_http_class_transaction_state_enum
{
    IPD_HTTP_CLASS_TRANSACTION_STATE_REQUEST,			/**< the request part of the transaction is currently processed */

    IPD_HTTP_CLASS_TRANSACTION_STATE_RESPONSE,			/**< the response part of the transaction is currently processed */
};


/**
 * Event for each HTTP request-response pair.
 * This event might be flushed multiple times in the future when HUGE POSTs happens.
 */
/** events for each http request - response pair
 */

#endif                          /* IPD_CLASS_HTTP_DEFINITIONS_H_ */

