/********************************************************************************/
/**
 ** \file       irc_events.h
 ** \brief      IRC stage4 event definitions
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef IRC_EVENTS_H
#define IRC_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Group ******************************************************************/
/**
 * @brief Public define for the assigned meta data group of the advanced IRC event.
 */
#define PACE2_ADVANCED_IRC_EVENT_GROUP PACE2_ADVANCED_PROTOCOL_META_DATA_GROUP

/* Event Types ******************************************************************/

#ifndef PACE2_DISABLE_DECODER
/**
 * @brief Types for advanced IRC events.
 */
typedef enum {
    PACE2_ADVANCED_IRC_NICK_USER,                   /**< @ref IPD_EVENT_IRC_NICK_USER */
    PACE2_ADVANCED_IRC_NICK_OTHER,                  /**< @ref IPD_EVENT_IRC_NICK_OTHER */
    PACE2_ADVANCED_IRC_PRIMSG,                      /**< @ref IPD_EVENT_IRC_PRIMSG */
    PACE2_ADVANCED_IRC_LOGIN_USER,                  /**< @ref IPD_EVENT_IRC_LOGIN_USER */
    PACE2_ADVANCED_IRC_PASS,                        /**< @ref IPD_EVENT_IRC_PASS */
    PACE2_ADVANCED_IRC_LOGIN_HOST,                  /**< @ref IPD_EVENT_IRC_LOGIN_HOST */
    PACE2_ADVANCED_IRC_LOGIN_SERVERNAME,            /**< @ref IPD_EVENT_IRC_LOGIN_SERVERNAME */
    PACE2_ADVANCED_IRC_LOGIN_REALNAME,              /**< @ref IPD_EVENT_IRC_LOGIN_REALNAME */
    PACE2_ADVANCED_IRC_QUIT_USER,                   /**< @ref IPD_EVENT_IRC_QUIT_USER */
    PACE2_ADVANCED_IRC_QUIT_OTHER,                  /**< @ref IPD_EVENT_IRC_QUIT_OTHER */
    PACE2_ADVANCED_IRC_JOIN,                        /**< @ref IPD_EVENT_IRC_JOIN */
    PACE2_ADVANCED_IRC_PART,                        /**< @ref IPD_EVENT_IRC_PART */
    PACE2_ADVANCED_IRC_TOPIC,                       /**< @ref IPD_EVENT_IRC_TOPIC */
    PACE2_ADVANCED_IRC_FT_ANNOUNCE,                 /**< @ref IPD_EVENT_IRC_FT_ANNOUNCE */
    PACE2_ADVANCED_IRC_FT_DATA,                     /**< @ref IPD_EVENT_IRC_FT_DATA */
    PACE2_ADVANCED_IRC_COMMAND,                     /**< @ref IPD_EVENT_IRC_COMMAND */
    PACE2_ADVANCED_IRC_INVALID,                     /**< @ref IPD_EVENT_IRC_INVALID */
    PACE2_ADVANCED_IRC_END_OF_FLOW,                 /**< @ref IPD_EVENT_IRC_END_OF_FLOW */

    PACE2_NUMBER_OF_ADVANCED_IRC_EVENT_TYPES        /**< Number of implemented event types. */
} PACE2_advanced_irc_event_type;

/* Event Structures *************************************************************/

/**
 * @brief Data structure for advanced IRC events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_ADVANCED_IRC_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_advanced_irc_event_type meta_data_type;           /**< IRC event subtype. */
    PACE2_ADVANCED_META_DATA_EVENT_EXTRA_FIELDS;
    union {
        struct ipd_irc_nick_data nick_user;                 /**< Contains data for a @ref PACE2_ADVANCED_IRC_NICK_USER event. */
        struct ipd_irc_nick_data nick_other;                /**< Contains data for a @ref PACE2_ADVANCED_IRC_NICK_OTHER event. */
        struct ipd_irc_chat_data primsg;                    /**< Contains data for a @ref PACE2_ADVANCED_IRC_PRIMSG event. */
        struct ipd_charset_string login_user;               /**< Contains data for a @ref PACE2_ADVANCED_IRC_LOGIN_USER event. */
        struct ipd_charset_string pass;                     /**< Contains data for a @ref PACE2_ADVANCED_IRC_PASS event. */
        struct ipd_charset_string login_host;               /**< Contains data for a @ref PACE2_ADVANCED_IRC_LOGIN_HOST event. */
        struct ipd_charset_string login_servername;         /**< Contains data for a @ref PACE2_ADVANCED_IRC_LOGIN_SERVERNAME event. */
        struct ipd_charset_string login_realname;           /**< Contains data for a @ref PACE2_ADVANCED_IRC_LOGIN_REALNAME event. */
        struct ipd_irc_chat_data quit_other;                /**< Contains data for a @ref PACE2_ADVANCED_IRC_QUIT_OTHER event. */
        struct ipd_irc_chat_data join;                      /**< Contains data for a @ref PACE2_ADVANCED_IRC_JOIN event. */
        struct ipd_irc_chat_data part;                      /**< Contains data for a @ref PACE2_ADVANCED_IRC_PART event. */
        struct ipd_irc_chat_data topic;                     /**< Contains data for a @ref PACE2_ADVANCED_IRC_TOPIC event. */
        struct ipd_irc_ft_data ft_announce;                 /**< Contains data for a @ref PACE2_ADVANCED_IRC_FT_ANNOUNCE event. */
        struct ipd_irc_ft_data ft_data;                     /**< Contains data for a @ref PACE2_ADVANCED_IRC_FT_DATA event. */
        struct ipd_irc_command command;                     /**< Contains data for a @ref PACE2_ADVANCED_IRC_COMMAND event. */
        const char * invalid;                               /**< Contains data for a @ref PACE2_ADVANCED_IRC_INVALID event. */
    } event_data;                                       /**< Named union which contains the data of the sub-event types. */
} PACE2_advanced_irc_event;

#endif /* PACE2_DISABLE_DECODER */

#endif /* IRC_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
