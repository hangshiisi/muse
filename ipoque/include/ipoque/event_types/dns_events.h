/********************************************************************************/
/**
 ** \file       dns_events.h
 ** \brief      DNS stage4 event definitions
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef DNS_EVENTS_H
#define DNS_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the advanced DNS event.
 */
#define PACE2_ADVANCED_DNS_EVENT_GROUP PACE2_ADVANCED_PROTOCOL_META_DATA_GROUP

/* Event Types ******************************************************************/

/**
 * @brief Types for advanced DNS events.
 */
typedef enum {
    PACE2_ADVANCED_DNS_QUERY,                    /**< @ref IPD_EVENT_DNS_QUERY */
    PACE2_ADVANCED_DNS_QUERY_RESPONSE,           /**< @ref IPD_EVENT_DNS_QUERY_RESPONSE */
    PACE2_ADVANCED_DNS_ANSWER_IPV4,              /**< @ref IPD_EVENT_DNS_ANSWER_IPV4 */
    PACE2_ADVANCED_DNS_ANSWER_IPV6,              /**< @ref IPD_EVENT_DNS_ANSWER_IPV6 */
    PACE2_ADVANCED_DNS_ANSWER_CANONICAL_NAME,    /**< @ref IPD_EVENT_DNS_ANSWER_CANONICAL_NAME */
    PACE2_ADVANCED_DNS_ANSWER_MAIL_EXCHANGE,     /**< @ref IPD_EVENT_DNS_ANSWER_MAIL_EXCHANGE */
    PACE2_ADVANCED_DNS_ANSWER_OTHER,             /**< @ref IPD_EVENT_DNS_ANSWER_OTHER */
    PACE2_ADVANCED_DNS_INVALID,                  /**< @ref IPD_EVENT_DNS_INVALID */

    PACE2_NUMBER_OF_ADVANCED_DNS_EVENT_TYPES     /**< Number of implemented event types. */
} PACE2_advanced_DNS_event_type;

/* Event Structures *************************************************************/

#ifndef PACE2_DISABLE_DECODER

/**
 * @brief Data structure for advanced DNS events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_ADVANCED_DNS_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_advanced_DNS_event_type meta_data_type;   /**< DNS event subtype. */
    PACE2_ADVANCED_META_DATA_EVENT_EXTRA_FIELDS;
    union {
        struct ipd_dns_query query;                                 /**< Contains data for a @ref PACE2_ADVANCED_DNS_QUERY event. */
        struct ipd_dns_query query_response;                        /**< Contains data for a @ref PACE2_ADVANCED_DNS_QUERY_RESPONSE event. */
        struct ipd_dns_answer_ipv4 answer_ipv4;                     /**< Contains data for a @ref PACE2_ADVANCED_DNS_ANSWER_IPV4 event. */
        struct ipd_dns_answer_ipv6 answer_ipv6;                     /**< Contains data for a @ref PACE2_ADVANCED_DNS_ANSWER_IPV6 event. */
        struct ipd_dns_answer_canonical_name answer_canonical_name; /**< Contains data for a @ref PACE2_ADVANCED_DNS_ANSWER_CANONICAL_NAME event. */
        struct ipd_dns_answer_mail_exchange answer_mail_exchange;   /**< Contains data for a @ref PACE2_ADVANCED_DNS_ANSWER_MAIL_EXCHANGE event. */
        struct ipd_dns_answer_other answer_other;                   /**< Contains data for a @ref PACE2_ADVANCED_DNS_ANSWER_OTHER event. */
        const char *  invalid;                                      /**< Contains data for a @ref PACE2_ADVANCED_DNS_INVALID event. */
    } event_data;                                   /**< Named union which contains the data of the sub-event types. */
} PACE2_advanced_DNS_event;

#endif

#endif /* DNS_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
