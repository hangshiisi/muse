/********************************************************************************/
/**
 ** \file       sip_events.h
 ** \brief      SIP event definitions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef SIP_EVENTS_H
#define SIP_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the basic SIP event.
 */
#define PACE2_BASIC_SIP_EVENT_GROUP PACE2_BASIC_PROTOCOL_META_DATA_GROUP

/**
 * @brief Public define for the assigned meta data group of the advanced SIP event.
 */
#define PACE2_ADVANCED_SIP_EVENT_GROUP PACE2_ADVANCED_PROTOCOL_META_DATA_GROUP

/**
 * @brief Public define for the assigned meta data group of the VoIP class event.
 */
#define PACE2_CLASS_VOIP_EVENT_GROUP PACE2_CLASS_PROTOCOL_META_DATA_GROUP

/* Event Types ******************************************************************/

/**
 * @brief SIP meta data flags.
 */
enum PACE2_SIP_data_flags {
    PACE2_SIP_CALL_STATE = 0,           /**< SIP call state flag. */
    PACE2_SIP_CALL_ATTR,                /**< SIP call attribute flag. */

    PACE2_NUMBER_OF_SIP_DATA_FLAGS      /**< Number of implemented SIP data flags. */
};

/**
 * @brief Types for advanced SIP events.
 */
typedef enum {
    PACE2_ADVANCED_SIP_MESSAGE,         /**< @ref IPD_EVENT_SIP_MESSAGE */
    PACE2_ADVANCED_SIP_END_OF_FLOW,     /**< @ref IPD_EVENT_SIP_END_OF_FLOW */
    PACE2_ADVANCED_SIP_INVALID,         /**< @ref IPD_EVENT_SIP_INVALID */
    PACE2_ADVANCED_SIP_RTP_DATA,        /**< @ref IPD_EVENT_SIP_RTP_DATA */
    PACE2_ADVANCED_SIP_RTP_END_OF_FLOW, /**< @ref IPD_EVENT_SIP_RTP_END_OF_FLOW */
    PACE2_ADVANCED_SIP_RTP_INVALID,     /**< @ref IPD_EVENT_SIP_RTP_INVALID */
    PACE2_ADVANCED_SIP_RTP_SSRC,        /**< @ref IPD_EVENT_SIP_RTP_SSRC */

    PACE2_NUMBER_OF_ADVANCED_SIP_EVENT_TYPES /**< Number of implemented event types. */
} PACE2_advanced_SIP_event_type;

/**
 * @brief Types for class VOIP events.
 */
typedef enum {
    PACE2_CLASS_VOIP_SESSION,               /**< @ref IPD_EVENT_SIP_MESSAGE */
    PACE2_CLASS_VOIP_CALL,                  /**< @ref IPD_EVENT_SIP_END_OF_FLOW */
    PACE2_CLASS_VOIP_RTP_DATA,              /**< @ref IPD_EVENT_SIP_INVALID */
    PACE2_CLASS_VOIP_SESSION_END,           /**< @ref IPD_CLASS_EVENT_VOIP_SESSION_END */
    PACE2_CLASS_VOIP_RTP_SESSION,           /**< @ref IPD_CLASS_EVENT_VOIP_RTP_SESSION */
    PACE2_CLASS_VOIP_RTP_SESSION_END,       /**< @ref IPD_CLASS_EVENT_VOIP_RTP_SESSION_END */
    PACE2_CLASS_VOIP_INVALID,               /**< @ref IPD_CLASS_EVENT_VOIP_INVALID */
    PACE2_CLASS_VOIP_RTP_INVALID,           /**< @ref IPD_CLASS_EVENT_VOIP_RTP_INVALID */
    PACE2_NUMBER_OF_CLASS_VOIP_EVENT_TYPES  /**< Number of implemented event types. */
} PACE2_class_VOIP_event_type;

/**
 * @brief SIP call states.
 */
typedef enum {
    PACE2_SIP_CALL_UNKNOWN = 0,         /**< Unknown SIP call state. */
    PACE2_SIP_CALL_SETUP,               /**< Setup of a SIP call. */
    PACE2_SIP_CALL_START,               /**< Start of a SIP call. */
    PACE2_SIP_CALL_END,                 /**< End of a SIP call. */

    PACE2_NUMBER_OF_SIP_CALL_STATES     /**< Number of implemented event types. */
} PACE2_SIP_call_state;

/* Event Structures *************************************************************/

/**
 * @brief Data structure for SIP events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_BASIC_SIP_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_bitmask meta_data_mask;       /**< Bitmask, which states the available SIP meta data */
    PACE2_SIP_call_state call_state;    /**< Variable of the @ref PACE2_SIP_CALL_STATE flag. */
    struct {
        PACE2_byte_buffer from;             /**< SIP caller attribute. */
        PACE2_byte_buffer to;               /**< SIP callee attribute. */
        PACE2_byte_buffer id;               /**< SIP call ID. */
    } call_attr;                        /**< Data structure of the @ref PACE2_SIP_CALL_ATTR flag. */
} PACE2_basic_SIP_event;

#ifndef PACE2_DISABLE_DECODER

/**
 * @brief Data structure for advanced SIP events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_ADVANCED_SIP_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_advanced_SIP_event_type meta_data_type;   /**< SIP event subtype. */
    PACE2_ADVANCED_META_DATA_EVENT_EXTRA_FIELDS;
    union {
        struct ipd_sip_message sip_message;             /**< Contains data for a @ref PACE2_ADVANCED_SIP_MESSAGE event. */
        struct ipd_rtp_data rtp_data;                   /**< Contains data for a @ref PACE2_ADVANCED_SIP_RTP_DATA event. */
        const char *invalid;                            /**< Contains data for a @ref PACE2_ADVANCED_SIP_INVALID event. */
        const char *rtp_invalid;                        /**< Contains data for a @ref PACE2_ADVANCED_SIP_RTP_INVALID event. */
        struct ipd_rtp_ssrc rtp_ssrc;                   /**< Contains data for a @ref PACE2_ADVANCED_SIP_RTP_SSRC event. */
    } event_data;                       /**< Named union which contains the data of the sub-event types. */
} PACE2_advanced_SIP_event;

/**
 * @brief Data structure for class VOIP events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_CLASS_VOIP_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_class_VOIP_event_type meta_data_type;         /**< VOIP event type. */
    PACE2_CLASS_META_DATA_EVENT_EXTRA_FIELDS;
    union {
        struct ipd_class_voip_session_struct session;                   /**< Contains data for a @ref IPD_CLASS_EVENT_VOIP_SESSION event. */
        struct ipd_class_voip_call_struct call;                         /**< Contains data for a @ref IPD_CLASS_EVENT_VOIP_CALL event. */
        struct ipd_voip_class_rtp_data rtp_data;                        /**< Contains data for a @ref IPD_CLASS_EVENT_VOIP_RTP_DATA event. */
        struct ipd_class_voip_session_end_struct session_end;           /**< Contains data for a @ref IPD_CLASS_EVENT_VOIP_SESSION_END event. */
        struct ipd_voip_class_rtp_session_struct rtp_session;           /**< Contains data for a @ref IPD_CLASS_EVENT_VOIP_RTP_SESSION event. */
        struct ipd_voip_class_rtp_session_end_struct rtp_session_end;   /**< Contains data for a @ref IPD_CLASS_EVENT_VOIP_RTP_SESSION_END event. */
        struct ipd_class_voip_invalid_struct invalid;                   /**< Contains data for a @ref IPD_CLASS_EVENT_VOIP_INVALID event. */
        struct ipd_voip_class_rtp_invalid_struct rtp_invalid;           /**< Contains data for a @ref IPD_CLASS_EVENT_VOIP_RTP_INVALID event. */
    } event_data;                       /**< Named union which contains the data of the sub-event types. */
} PACE2_class_VOIP_event;

#endif

#endif /* SIP_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
