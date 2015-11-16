/********************************************************************************/
/**
 ** \file       socks_events.h
 ** \brief      socks stage4 event definitions
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef SOCKS_EVENTS_H
#define SOCKS_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Group ******************************************************************/
/**
 * @brief Public define for the assigned meta data group of the advanced SOCKS event.
 */
#define PACE2_ADVANCED_SOCKS_EVENT_GROUP PACE2_ADVANCED_PROTOCOL_META_DATA_GROUP

/* Event Types ******************************************************************/
/**
 * @brief Types for advanced socks events.
 */
typedef enum {
    PACE2_ADVANCED_SOCKS_NEW_CONNECTION,                            /**< @ref IPD_EVENT_SOCKS_NEW_CONNECTION */
    PACE2_ADVANCED_SOCKS_REQUEST,                                   /**< @ref IPD_EVENT_SOCKS_REQUEST */
    PACE2_ADVANCED_SOCKS_RESPONSE,                                  /**< @ref IPD_EVENT_SOCKS_RESPONSE */
    PACE2_ADVANCED_SOCKS_V5_CLIENT_ANNOUNCEMENT,                    /**< @ref IPD_EVENT_SOCKS_V5_CLIENT_ANNOUNCEMENT */
    PACE2_ADVANCED_SOCKS_V5_SERVER_ANNOUNCEMENT_RESPONSE,           /**< @ref IPD_EVENT_SOCKS_V5_SERVER_ANNOUNCEMENT_RESPONSE */
    PACE2_ADVANCED_SOCKS_V5_USERNAME_AUTHENTICATION_REQUEST,        /**< @ref IPD_EVENT_SOCKS_V5_USERNAME_AUTHENTICATION_REQUEST */
    PACE2_ADVANCED_SOCKS_V5_USERNAME_AUTHENTICATION_RESPONSE,       /**< @ref IPD_EVENT_SOCKS_V5_USERNAME_AUTHENTICATION_RESPONSE */
    PACE2_ADVANCED_SOCKS_END_OF_FLOW,                               /**< @ref IPD_EVENT_SOCKS_END_OF_FLOW */
    PACE2_ADVANCED_SOCKS_INVALID,                                   /**< @ref IPD_EVENT_SOCKS_INVALID */

    PACE2_NUMBER_OF_ADVANCED_SOCKS_EVENT_TYPES                      /**< Number of implemented event types. */
} PACE2_advanced_socks_event_type;

/* Event Structures *************************************************************/

#ifndef PACE2_DISABLE_DECODER

/**
 * @brief Data structure for advanced SOCKS events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_ADVANCED_SOCKS_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_advanced_socks_event_type meta_data_type;                                                     /**< SOCKS event subtype. */
    PACE2_ADVANCED_META_DATA_EVENT_EXTRA_FIELDS;
    union {
        struct ipd_socks_request socks_request;                                                         /**< Contains data for a @ref PACE2_ADVANCED_SOCKS_REQUEST event. */
        struct ipd_socks_response ipd_socks_response;                                                   /**< Contains data for a @ref PACE2_ADVANCED_SOCKS_RESPONSE event. */
        struct ipd_socks_v5_authentication_method v5_authentication_method_announcement;                /**< Contains data for a @ref PACE2_ADVANCED_SOCKS_V5_CLIENT_ANNOUNCEMENT event. */
        struct ipd_socks_v5_authentication_method v5_authentication_method_response;                    /**< Contains data for a @ref PACE2_ADVANCED_SOCKS_V5_SERVER_ANNOUNCEMENT_RESPONSE event. */
        struct ipd_socks_v5_username_authentication_request v5_username_authentication_request;         /**< Contains data for a @ref PACE2_ADVANCED_SOCKS_V5_USERNAME_AUTHENTICATION_REQUEST event. */
        struct ipd_socks_v5_username_authentication_response v5_username_authentication_response;       /**< Contains data for a @ref PACE2_ADVANCED_SOCKS_V5_USERNAME_AUTHENTICATION_RESPONSE event. */
        const char *invalid;                                                                            /**< Contains data for a @ref PACE2_ADVANCED_SOCKS_INVALID event. */
    } event_data;                                                                                       /**< Named union which contains the data of the sub-event types. */
} PACE2_advanced_socks_event;


#endif

#endif /* SOCKS_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
