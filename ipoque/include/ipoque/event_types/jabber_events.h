/********************************************************************************/
/**
 ** \file       jabber_events.h
 ** \brief      Jabber stage4 event definitions
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef JABBER_EVENTS_H
#define JABBER_EVENTS_H

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the advanced jabber event.
 */
#define PACE2_ADVANCED_JABBER_EVENT_GROUP PACE2_ADVANCED_PROTOCOL_META_DATA_GROUP

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Types ******************************************************************/

/**
 * @brief Types for advanced jabber events.
 */
typedef enum {
    PACE2_ADVANCED_JABBER_NEW_CONNECTION,          /**< @ref IPD_EVENT_JABBER_NEW_CONNECTION */
    PACE2_ADVANCED_JABBER_CLOSE_CONNECTION,        /**< @ref IPD_EVENT_JABBER_CLOSE_CONNECTION */
    PACE2_ADVANCED_JABBER_STARTTLS,                /**< @ref IPD_EVENT_JABBER_STARTTLS */
    PACE2_ADVANCED_JABBER_LOG_ON,                  /**< @ref IPD_EVENT_JABBER_LOG_ON */
    PACE2_ADVANCED_JABBER_BUDDY_ADD,               /**< @ref IPD_EVENT_JABBER_BUDDY_ADD */
    PACE2_ADVANCED_JABBER_ADD_NEW_BUDDY,           /**< @ref IPD_EVENT_JABBER_ADD_NEW_BUDDY */
    PACE2_ADVANCED_JABBER_NEW_BUDDY_ACCEPT,        /**< @ref IPD_EVENT_JABBER_NEW_BUDDY_ACCEPT */
    PACE2_ADVANCED_JABBER_NEW_BUDDY_CANCEL,        /**< @ref IPD_EVENT_JABBER_NEW_BUDDY_CANCEL */
    PACE2_ADVANCED_JABBER_USER_ON,                 /**< @ref IPD_EVENT_JABBER_USER_ON */
    PACE2_ADVANCED_JABBER_USER_OFF,                /**< @ref IPD_EVENT_JABBER_USER_OFF */
    PACE2_ADVANCED_JABBER_USER_DO_NOT_DISTURB,     /**< @ref IPD_EVENT_JABBER_USER_DO_NOT_DISTURB */
    PACE2_ADVANCED_JABBER_MESSAGE_OUT,             /**< @ref IPD_EVENT_JABBER_MESSAGE_OUT */
    PACE2_ADVANCED_JABBER_MESSAGE_IN,              /**< @ref IPD_EVENT_JABBER_MESSAGE_IN */
    PACE2_ADVANCED_JABBER_BUDDY_CHANGE_STATUS,     /**< @ref IPD_EVENT_JABBER_BUDDY_CHANGE_STATUS */
    PACE2_ADVANCED_JABBER_CHANGE_STATUS,           /**< @ref IPD_EVENT_JABBER_CHANGE_STATUS */
    PACE2_ADVANCED_JABBER_VOIP_ANNOUNCE,           /**< @ref IPD_EVENT_JABBER_VOIP_ANNOUNCE */
    PACE2_ADVANCED_JABBER_VOIP_ACCEPT,             /**< @ref IPD_EVENT_JABBER_VOIP_ACCEPT */
    PACE2_ADVANCED_JABBER_VOIP_REJECT,             /**< @ref IPD_EVENT_JABBER_VOIP_REJECT */
    PACE2_ADVANCED_JABBER_VOIP_END,                /**< @ref IPD_EVENT_JABBER_VOIP_END */
    PACE2_ADVANCED_JABBER_RTP_DATA,                /**< @ref IPD_EVENT_JABBER_RTP_DATA */
    PACE2_ADVANCED_JABBER_INVALID,                 /**< @ref IPD_EVENT_JABBER_INVALID */
    PACE2_ADVANCED_JABBER_STREAM_COMPRESSED,       /**< @ref IPD_EVENT_JABBER_STREAM_COMPRESSED */
    PACE2_ADVANCED_JABBER_COMPRESSED_DATA,         /**< @ref IPD_EVENT_JABBER_COMPRESSED_DATA */
    PACE2_ADVANCED_JABBER_END_OF_FLOW,             /**< @ref IPD_EVENT_JABBER_END_OF_FLOW */
    PACE2_ADVANCED_JABBER_RTP_SSRC,                /**< @ref IPD_EVENT_JABBER_RTP_SSRC */
    PACE2_ADVANCED_JABBER_IBB_ANNOUNCEMENT,        /**< @ref IPD_EVENT_JABBER_IBB_ANNOUNCEMENT */
    PACE2_ADVANCED_JABBER_IBB_OPEN_FILETRANSFER,   /**< @ref IPD_EVENT_JABBER_IBB_OPEN_FILETRANSFER */
    PACE2_ADVANCED_JABBER_IBB_CLOSE_FILETRANSFER,  /**< @ref IPD_EVENT_JABBER_IBB_CLOSE_FILETRANSFER */
    PACE2_ADVANCED_JABBER_IBB_REJECT_FILETRANSFER, /**< @ref IPD_EVENT_JABBER_IBB_REJECT_FILETRANSFER */
    PACE2_ADVANCED_JABBER_IBB_DATA,                /**< @ref IPD_EVENT_JABBER_IBB_DATA */

    PACE2_NUMBER_OF_ADVANCED_JABBER_EVENT_TYPES    /**< Number of implemented event types. */
} PACE2_advanced_Jabber_event_type;

/* Event Structures *************************************************************/

#ifndef PACE2_DISABLE_DECODER

/**
 * @brief Data structure for advanced jabber events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_ADVANCED_UNENCRYPTED_JABBER_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_advanced_Jabber_event_type meta_data_type;    /**< Jabber event subtype. */
    PACE2_ADVANCED_META_DATA_EVENT_EXTRA_FIELDS;
    union {
        struct ipd_charset_string log_on;                                         /**< Contains data for a @ref PACE2_ADVANCED_JABBER_LOG_ON event. */
        struct ipd_charset_string buddy_add;                                      /**< Contains data for a @ref PACE2_ADVANCED_JABBER_BUDDY_ADD event. */
        struct ipd_charset_string add_new_buddy;                                  /**< Contains data for a @ref PACE2_ADVANCED_JABBER_ADD_NEW_BUDDY event. */
        struct ipd_charset_string new_buddy_accept;                               /**< Contains data for a @ref PACE2_ADVANCED_JABBER_NEW_BUDDY_ACCEPT event. */
        struct ipd_charset_string new_buddy_cancel;                               /**< Contains data for a @ref PACE2_ADVANCED_JABBER_NEW_BUDDY_CANCEL event. */
        struct ipd_charset_string user_on;                                        /**< Contains data for a @ref PACE2_ADVANCED_JABBER_USER_ON event. */
        struct ipd_charset_string user_off;                                       /**< Contains data for a @ref PACE2_ADVANCED_JABBER_USER_OFF event. */
        struct ipd_charset_string user_do_not_disturb;                            /**< Contains data for a @ref PACE2_ADVANCED_JABBER_USER_DO_NOT_DISTURB event. */
        struct ipd_jabber_message_struct message_out;                             /**< Contains data for a @ref PACE2_ADVANCED_JABBER_MESSAGE_OUT event. */
        struct ipd_jabber_message_struct message_in;                              /**< Contains data for a @ref PACE2_ADVANCED_JABBER_MESSAGE_IN event. */
        struct ipd_jabber_message_struct buddy_ch_status;                         /**< Contains data for a @ref PACE2_ADVANCED_JABBER_BUDDY_CHANGE_STATUS event. */
        struct ipd_charset_string change_status;                                  /**< Contains data for a @ref PACE2_ADVANCED_JABBER_CHANGE_STATUS event. */
        struct ipd_jabber_voip_struct voip_announce;                              /**< Contains data for a @ref PACE2_ADVANCED_JABBER_VOIP_ANNOUNCE event. */
        struct ipd_jabber_voip_struct voip_accept;                                /**< Contains data for a @ref PACE2_ADVANCED_JABBER_VOIP_ACCEPT event. */
        struct ipd_jabber_voip_struct voip_reject;                                /**< Contains data for a @ref PACE2_ADVANCED_JABBER_VOIP_REJECT event. */
        struct ipd_jabber_voip_struct voip_end;                                   /**< Contains data for a @ref PACE2_ADVANCED_JABBER_VOIP_END event. */
        struct ipd_rtp_data rtp_data;                                             /**< Contains data for a @ref PACE2_ADVANCED_JABBER_RTP_DATA event. */
        const char * invalid;                                                     /**< Contains data for a @ref PACE2_ADVANCED_JABBER_INVALID event. */
        struct ipd_charset_string compression_type;                               /**< Contains data for a @ref PACE2_ADVANCED_JABBER_STREAM_COMPRESSED event. */
        struct ipd_charset_string compressed_data;                                /**< Contains data for a @ref PACE2_ADVANCED_JABBER_COMPRESSED_DATA event. */
        struct ipd_rtp_ssrc rtp_ssrc;                                             /**< Contains data for a @ref PACE2_ADVANCED_JABBER_RTP_SSRC event. */
        struct ipd_jabber_ibb_announcement_struct ibb_announcement;               /**< Contains data for a @ref PACE2_ADVANCED_JABBER_IBB_ANNOUNCEMENT event. */
        struct ipd_jabber_ibb_open_filetransfer_struct ibb_open_filetransfer;     /**< Contains data for a @ref PACE2_ADVANCED_JABBER_IBB_OPEN_FILETRANSFER event. */
        struct ipd_jabber_ibb_announcement_struct ibb_close_filetransfer;         /**< Contains data for a @ref PACE2_ADVANCED_JABBER_IBB_CLOSE_FILETRANSFER event. */
        struct ipd_jabber_ibb_announcement_struct ibb_reject_filetransfer;        /**< Contains data for a @ref PACE2_ADVANCED_JABBER_IBB_REJECT_FILETRANSFER event. */
        struct ipd_jabber_ibb_data_struct ibb_data;                               /**< Contains data for a @ref PACE2_ADVANCED_JABBER_IBB_DATA event. */
    } event_data;                                       /**< Named union which contains the data of the sub-event types. */
} PACE2_advanced_jabber_event;

#endif

#endif /* JABBER_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
