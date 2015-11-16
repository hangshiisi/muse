/********************************************************************************/
/**
 ** \file       h323_events.h
 ** \brief      h323 stage4 event definitions
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef H323_EVENTS_H
#define H323_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Group ******************************************************************/
/**
 * @brief Public define for the assigned meta data group of the advanced H.323 event.
 */
#define PACE2_ADVANCED_H323_EVENT_GROUP PACE2_ADVANCED_PROTOCOL_META_DATA_GROUP

/* Event Types ******************************************************************/
/**
 * @brief Types for advanced H.323 events.
 */
typedef enum {
    PACE2_ADVANCED_H323_MESSAGE,                    /**< @ref IPD_EVENT_H323_MESSAGE */
    PACE2_ADVANCED_H323_END_OF_FLOW,                /**< @ref IPD_EVENT_H323_END_OF_FLOW */
    PACE2_ADVANCED_H323_INVALID,                    /**< @ref IPD_EVENT_H323_INVALID */
    PACE2_ADVANCED_H323_RTP_DATA,                   /**< @ref IPD_EVENT_H323_DATA */
    PACE2_ADVANCED_H323_RTP_END_OF_FLOW,            /**< @ref IPD_EVENT_H323_RTP_END_OF_FLOW */
    PACE2_ADVANCED_H323_RTP_INVALID,                /**< @ref IPD_EVENT_H323_RTP_INVALID */
    PACE2_ADVANCED_H323_RTP_SSRC,                   /**< @ref IPD_EVENT_H323_RTP_SSRC */

    PACE2_NUMBER_OF_ADVANCED_H323_EVENT_TYPES       /**< Number of implemented event types. */
} PACE2_advanced_h323_event_type;

/* Event Structures *************************************************************/

#ifndef PACE2_DISABLE_DECODER

/**
 * @brief Data structure for advanced H.323 events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_ADVANCED_H323_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_advanced_h323_event_type meta_data_type;           /**< H.323 event subtype. */
    PACE2_ADVANCED_META_DATA_EVENT_EXTRA_FIELDS;
    union {
        struct h323_state_struct h323_message;              /**< Contains data for a @ref PACE2_ADVANCED_H323_MESSAGE event. */
        struct ipd_rtp_data rtp_data;                       /**< Contains data for a @ref PACE2_ADVANCED_H323_RTP_DATA event. */
        const char *invalid;                                /**< Contains data for a @ref PACE2_ADVANCED_H323_INVALID event. */
        const char *rtp_invalid;                            /**< Contains data for a @ref PACE2_ADVANCED_H323_RTP_INVALID event. */
        struct ipd_rtp_ssrc rtp_ssrc;                       /**< Contains data for a @ref PACE2_ADVANCED_H323_RTP_SSRC event. */
    } event_data;                                           /**< Named union which contains the data of the sub-event types. */
} PACE2_advanced_h323_event;


#endif

#endif /* H323_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
