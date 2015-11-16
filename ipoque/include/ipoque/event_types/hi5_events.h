/********************************************************************************/
/**
 ** \file       hi5_events.h
 ** \brief      hi5 stage4 event definitions
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef HI5_EVENTS_H
#define HI5_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Group ******************************************************************/
/**
 * @brief Public define for the assigned meta data group of the advanced Hi5 event.
 */
#define PACE2_ADVANCED_HI5_EVENT_GROUP PACE2_ADVANCED_PROTOCOL_META_DATA_GROUP

#ifndef PACE2_DISABLE_DECODER

/* Event Types ******************************************************************/
/**
 * @brief Types for advanced hi5 events.
 */
typedef enum {
PACE2_ADVANCED_HI5_LOGON,                                   /**< @ref IPD_EVENT_HI5_LOGON */
PACE2_ADVANCED_HI5_LOGOFF,                                  /**< @ref IPD_EVENT_HI5_LOGOFF */
PACE2_ADVANCED_HI5_STATUS_UPDATE,                           /**< @ref IPD_EVENT_HI5_STATUS_UPDATE */
PACE2_ADVANCED_HI5_RECENT_UPDATES,                          /**< @ref IPD_EVENT_HI5_RECENT_UPDATES */
PACE2_ADVANCED_HI5_COMMENT_UPDATE,                          /**< @ref IPD_EVENT_HI5_COMMENT_UPDATE */
PACE2_ADVANCED_HI5_COMMENT_PROFILE,                         /**< @ref IPD_EVENT_HI5_COMMENT_PROFILE*/
PACE2_ADVANCED_HI5_COMMENT_STATUS,                          /**< @ref IPD_EVENT_HI5_COMMENT_STATUS */
PACE2_ADVANCED_HI5_FRIEND_SEARCH_BY_NAME,                   /**< @ref IPD_EVENT_HI5_FRIEND_SEARCH_BY_NAME */
PACE2_ADVANCED_HI5_FRIEND_SEARCH_BY_EMAIL,                  /**< @ref IPD_EVENT_HI5_FRIEND_SEARCH_BY_EMAIL */
PACE2_ADVANCED_HI5_FRIEND_SEARCH,                           /**< @ref IPD_EVENT_HI5_FRIEND_SEARCH */
PACE2_ADVANCED_HI5_FRIENDSHIP_REQUEST,                      /**< @ref IPD_EVENT_HI5_FRIENDSHIP_REQUEST */
PACE2_ADVANCED_HI5_FRIEND_REMOVE,                           /**< @ref IPD_EVENT_HI5_FRIEND_REMOVE */
PACE2_ADVANCED_HI5_VIEW_FRIENDS,                            /**< @ref IPD_EVENT_HI5_VIEW_FRIENDS */
PACE2_ADVANCED_HI5_MAILBOX,                                 /**< @ref IPD_EVENT_HI5_MAILBOX */
PACE2_ADVANCED_HI5_MAIL_SEND,                               /**< @ref IPD_EVENT_HI5_MAIL_SEND */
PACE2_ADVANCED_HI5_MAIL_VIEW,                               /**< @ref IPD_EVENT_HI5_MAIL_VIEW */
PACE2_ADVANCED_HI5_MAIL_RECEIVE,                            /**< @ref IPD_EVENT_HI5_MAIL_RECEIVE */
PACE2_ADVANCED_HI5_MAILTHREAD_VIEW,                         /**< @ref IPD_EVENT_HI5_MAILTHREAD_VIEW */
PACE2_ADVANCED_HI5_GROUP_CREATE,                            /**< @ref IPD_EVENT_HI5_GROUP_CREATE */
PACE2_ADVANCED_HI5_GROUP_JOIN,                              /**< @ref IPD_EVENT_HI5_GROUP_JOIN */
PACE2_ADVANCED_HI5_GROUP_LEAVE,                             /**< @ref IPD_EVENT_HI5_GROUP_LEAVE */
PACE2_ADVANCED_HI5_GROUP_ADD_TOPIC,                         /**< @ref IPD_EVENT_HI5_GROUP_ADD_TOPIC */
PACE2_ADVANCED_HI5_GROUP_ADD_MESSAGE,                       /**< @ref IPD_EVENT_HI5_GROUP_ADD_MESSAGE */
PACE2_ADVANCED_HI5_GROUP_LIST_THREADS,                      /**< @ref IPD_EVENT_HI5_GROUP_LIST_THREADS */
PACE2_ADVANCED_HI5_VISIT_PROFILE,                           /**< @ref IPD_EVENT_HI5_VISIT_PROFILE */
PACE2_ADVANCED_HI5_GROUP_VISIT,                             /**< @ref IPD_EVENT_HI5_GROUP_VISIT */

PACE2_NUMBER_OF_ADVANCED_HI5_EVENT_TYPES                    /**< Number of implemented event types. */
} PACE2_advanced_hi5_event_type;

/* Event Structures *************************************************************/

/**
 * @brief Data structure for advanced Hi5 events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_ADVANCED_HI5_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_advanced_hi5_event_type meta_data_type;                       /**< HI5 event subtype. */
    PACE2_ADVANCED_META_DATA_EVENT_EXTRA_FIELDS;
    union {
        struct ipd_hi5_logon logon;                                     /**< Contains data for a @ref PACE2_ADVANCED_HI5_LOGON event. */
        struct ipd_hi5_generic logoff;                                  /**< Contains data for a @ref PACE2_ADVANCED_HI5_LOGOFF event. */
        struct ipd_hi5_status_update status_update;                     /**< Contains data for a @ref PACE2_ADVANCED_HI5_STATUS_UPDATE event. */
        struct ipd_hi5_recent_updates recent_updates;                   /**< Contains data for a @ref PACE2_ADVANCED_HI5_RECENT_UPDATES event. */
        struct ipd_hi5_comment comment_update;                          /**< Contains data for a @ref PACE2_ADVANCED_HI5_COMMENT_UPDATE event. */
        struct ipd_hi5_comment comment_profile;                         /**< Contains data for a @ref PACE2_ADVANCED_HI5_COMMENT_PROFILE event. */
        struct ipd_hi5_comment comment_status;                          /**< Contains data for a @ref PACE2_ADVANCED_HI5_COMMENT_STATUS event. */
        struct ipd_hi5_friend_search_by_name friend_search_by_name;     /**< Contains data for a @ref PACE2_ADVANCED_HI5_FRIEND_SEARCH_BY_NAME event. */
        struct ipd_hi5_friend_search_by_email friend_search_by_email;   /**< Contains data for a @ref PACE2_ADVANCED_HI5_FRIEND_SEARCH_BY_EMAIL event. */
        struct ipd_hi5_friend_search friend_search;                     /**< Contains data for a @ref PACE2_ADVANCED_HI5_FRIEND_SEARCH event. */
        struct ipd_hi5_friendship_request friendship_request;           /**< Contains data for a @ref PACE2_ADVANCED_HI5_FRIENDSHIP_REQUEST event. */
        struct ipd_hi5_friend_remove friend_remove;                     /**< Contains data for a @ref PACE2_ADVANCED_HI5_FRIEND_REMOVE event. */
        struct ipd_hi5_view_friends view_friends;                       /**< Contains data for a @ref PACE2_ADVANCED_HI5_VIEW_FRIENDS event. */
        struct ipd_hi5_mailbox mailbox;                                 /**< Contains data for a @ref PACE2_ADVANCED_HI5_MAILBOX event. */
        struct ipd_hi5_message mail_send;                               /**< Contains data for a @ref PACE2_ADVANCED_HI5_MAIL_SEND event. */
        struct ipd_hi5_message mail_view;                               /**< Contains data for a @ref PACE2_ADVANCED_HI5_MAIL_VIEW event. */
        struct ipd_hi5_message mail_receive;                            /**< Contains data for a @ref PACE2_ADVANCED_HI5_MAIL_RECEIVE event. */
        struct ipd_hi5_message_thread mailthread_view;                  /**< Contains data for a @ref PACE2_ADVANCED_HI5_MAILTHREAD_VIEW event. */
        struct ipd_hi5_group_create group_create;                       /**< Contains data for a @ref PACE2_ADVANCED_HI5_GROUP_CREATE event. */
        struct ipd_hi5_group_join group_join;                           /**< Contains data for a @ref PACE2_ADVANCED_HI5_GROUP_JOIN event. */
        struct ipd_hi5_group_leave group_leave;                         /**< Contains data for a @ref PACE2_ADVANCED_HI5_GROUP_LEAVE event. */
        struct ipd_hi5_thread group_add_topic;                          /**< Contains data for a @ref PACE2_ADVANCED_HI5_GROUP_ADD_TOPIC event. */
        struct ipd_hi5_thread group_add_message;                        /**< Contains data for a @ref PACE2_ADVANCED_HI5_GROUP_ADD_MESSAGE event. */
        struct ipd_hi5_thread_list list;                                /**< Contains data for a @ref PACE2_ADVANCED_HI5_GROUP_LIST_THREADS event. */
        struct ipd_hi5_visit_profile visit_profile;                     /**< Contains data for a @ref PACE2_ADVANCED_HI5_VISIT_PROFILE event. */
        struct ipd_hi5_group_visit group_visit;                         /**< Contains data for a @ref PACE2_ADVANCED_HI5_GROUP_VISIT event. */
    } event_data;                                                       /**< Named union which contains the data of the sub-event types. */
} PACE2_advanced_hi5_event;

#endif /* PACE2_DISABLE_DECODER */

#endif /* HI5_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
