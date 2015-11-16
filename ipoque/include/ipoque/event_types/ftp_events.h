/********************************************************************************/
/**
 ** \file       ftp_events.h
 ** \brief      FTP stage4 event definitions
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef FTP_EVENTS_H
#define FTP_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the advanced FTP event.
 */
#define PACE2_ADVANCED_FTP_EVENT_GROUP PACE2_ADVANCED_PROTOCOL_META_DATA_GROUP

/* Event Types ******************************************************************/

/**
 * @brief Types for advanced FTP events.
 */
typedef enum {
    PACE2_ADVANCED_FTP_NEW_CONTROL_CONNECTION,    /**< @ref IPD_EVENT_FTP_NEW_CONTROL_CONNECTION */
    PACE2_ADVANCED_FTP_NEW_DATA_CONNECTION,       /**< @ref IPD_EVENT_FTP_NEW_DATA_CONNECTION */
    PACE2_ADVANCED_FTP_TRANSFER_END,              /**< @ref IPD_EVENT_FTP_TRANSFER_END */
    PACE2_ADVANCED_FTP_TRANSFER_CANCELED,         /**< @ref IPD_EVENT_FTP_TRANSFER_CANCELED */
    PACE2_ADVANCED_FTP_DATA,                      /**< @ref IPD_EVENT_FTP_DATA */
    PACE2_ADVANCED_FTP_END_OF_CONTROL_FLOW,       /**< @ref IPD_EVENT_FTP_END_OF_CONTROL_FLOW */
    PACE2_ADVANCED_FTP_END_OF_DATA_FLOW,          /**< @ref IPD_EVENT_FTP_END_OF_DATA_FLOW */
    PACE2_ADVANCED_FTP_INVALID,                   /**< @ref IPD_EVENT_FTP_INVALID */
    PACE2_ADVANCED_FTP_COMMAND,                   /**< @ref IPD_EVENT_FTP_COMMAND */
    PACE2_ADVANCED_FTP_REPLY,                     /**< @ref IPD_EVENT_FTP_REPLY */
    PACE2_ADVANCED_FTP_TRANSFER_INIT,             /**< @ref IPD_EVENT_FTP_TRANSFER_INIT */

    PACE2_NUMBER_OF_ADVANCED_FTP_EVENT_TYPES      /**< Number of implemented event types. */
} PACE2_advanced_FTP_event_type;

/* Event Structures *************************************************************/

#ifndef PACE2_DISABLE_DECODER

/**
 * @brief Data structure for advanced FTP events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_ADVANCED_FTP_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_advanced_FTP_event_type meta_data_type;   /**< FTP event subtype. */
    PACE2_ADVANCED_META_DATA_EVENT_EXTRA_FIELDS;
    union {
        struct ipd_ftp_data_flow_info new_data_connection;  /**< Contains data for a @ref PACE2_ADVANCED_FTP_NEW_CONTROL_CONNECTION event. */
        u64 transfer_end;                                   /**< Contains data for a @ref PACE2_ADVANCED_FTP_TRANSFER_END event. */
        u64 transfer_cancelled;                             /**< Contains data for a @ref PACE2_ADVANCED_FTP_TRANSFER_CANCELED event. */
        struct ipd_ftp_data data;                           /**< Contains data for a @ref PACE2_ADVANCED_FTP_DATA event. */
        struct ipd_ftp_data_flow_info end_of_data_flow;     /**< Contains data for a @ref PACE2_ADVANCED_FTP_END_OF_DATA_FLOW event. */
        const char *invalid;                                /**< Contains data for a @ref PACE2_ADVANCED_FTP_INVALID event. */
        struct ipd_ftp_command command;                     /**< Contains data for a @ref PACE2_ADVANCED_FTP_COMMAND event. */
        struct ipd_ftp_reply reply;                         /**< Contains data for a @ref PACE2_ADVANCED_FTP_REPLY event. */
        struct ipd_ftp_transfer_info transfer_init;         /**< Contains data for a @ref PACE2_ADVANCED_FTP_TRANSFER_INIT event. */
    } event_data;                                   /**< Named union which contains the data of the sub-event types. */
} PACE2_advanced_FTP_event;

#endif

#endif /* FTP_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
