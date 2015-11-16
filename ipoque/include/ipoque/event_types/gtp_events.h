/********************************************************************************/
/**
 ** \file       gtp_events.h
 ** \brief      GTP event definitions
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef GTP_EVENTS_H
#define GTP_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the advanced GTP event.
 */
#define PACE2_ADVANCED_GTP_EVENT_GROUP PACE2_ADVANCED_PROTOCOL_META_DATA_GROUP

/* Event Types ******************************************************************/

/**
 * @brief Types for advanced GTP events.
 */
typedef enum {
    ///standard informations
    PACE2_ADVANCED_GTP_NEW_CONNECTION,                  /**< @ref IPD_EVENT_GTP_NEW_CONNECTION */
    PACE2_ADVANCED_GTP_CONNECTION_END,                  /**< @ref IPD_EVENT_GTP_CONNECTION_END */
    PACE2_ADVANCED_GTP_INVALID,                         /**< @ref IPD_EVENT_GTP_INVALID */
    PACE2_ADVANCED_GTP_MESSAGE,                         /**< @ref IPD_EVENT_GTP_MESSAGE */
    PACE2_ADVANCED_GTP_EXTENSION,                       /**< @ref IPD_EVENT_GTP_EXTENSION */
    PACE2_ADVANCED_GTP_DATA,                            /**< @ref IPD_EVENT_GTP_DATA */
    PACE2_ADVANCED_GTP_INFORMATION,                     /**< @ref IPD_EVENT_GTP_INFORMATION */
    PACE2_ADVANCED_GTP_INFORMATION_GROUP,               /**< @ref IPD_EVENT_GTP_INFORMATION_GROUP */
    PACE2_ADVANCED_GTP_MESSAGE_END,                     /**< @ref IPD_EVENT_GTP_MESSAGE_END */
    PACE2_ADVANCED_GTP_INFORMATION_GROUP_END,           /**< @ref IPD_EVENT_GTP_INFORMATION_GROUP_END */

    ///additional informations
    PACE2_ADVANCED_GTP_INFORMATION_IMSI,                /**< @ref IPD_EVENT_GTP_INFORMATION_IMSI */
    PACE2_ADVANCED_GTP_INFORMATION_IMEI,                /**< @ref IPD_EVENT_GTP_INFORMATION_IMEI */
    PACE2_ADVANCED_GTP_INFORMATION_MSISDN,              /**< @ref IPD_EVENT_GTP_INFORMATION_MSISDN */
    PACE2_ADVANCED_GTP_INFORMATION_APN,                 /**< @ref IPD_EVENT_GTP_INFORMATION_APN */
    PACE2_ADVANCED_GTP_INFORMATION_TEID_DATA_I,         /**< @ref IPD_EVENT_GTP_INFORMATION_TEID_DATA_I */
    PACE2_ADVANCED_GTP_INFORMATION_TEID_DATA_II,        /**< @ref IPD_EVENT_GTP_INFORMATION_TEID_DATA_II */
    PACE2_ADVANCED_GTP_INFORMATION_TEID_CONTROL,        /**< @ref IPD_EVENT_GTP_INFORMATION_TEID_CONTROL */
    PACE2_ADVANCED_GTP_INFORMATION_LAC,                 /**< @ref IPD_EVENT_GTP_INFORMATION_LAC */
    PACE2_ADVANCED_GTP_INFORMATION_RAC,                 /**< @ref IPD_EVENT_GTP_INFORMATION_RAC */
    PACE2_ADVANCED_GTP_INFORMATION_RAT,                 /**< @ref IPD_EVENT_GTP_INFORMATION_RAT */
    PACE2_ADVANCED_GTP_INFORMATION_EBI,                 /**< @ref IPD_EVENT_GTP_INFORMATION_EBI */
    PACE2_ADVANCED_GTP_INFORMATION_CID,                 /**< @ref IPD_EVENT_GTP_INFORMATION_CID */
    PACE2_ADVANCED_GTP_INFORMATION_ADDRESS,             /**< @ref IPD_EVENT_GTP_INFORMATION_ADDRESS */
    PACE2_ADVANCED_GTP_INFORMATION_ARP,                 /**< @ref IPD_EVENT_GTP_INFORMATION_ARP */
    PACE2_ADVANCED_GTP_INFORMATION_QCI,                 /**< @ref IPD_EVENT_GTP_INFORMATION_QCI */
    PACE2_ADVANCED_GTP_INFORMATION_MBR_UP,              /**< @ref IPD_EVENT_GTP_INFORMATION_MBR_UP */
    PACE2_ADVANCED_GTP_INFORMATION_MBR_DOWN,            /**< @ref IPD_EVENT_GTP_INFORMATION_MBR_DOWN */
    PACE2_ADVANCED_GTP_INFORMATION_GBR_UP,              /**< @ref IPD_EVENT_GTP_INFORMATION_GBR_UP */
    PACE2_ADVANCED_GTP_INFORMATION_GBR_DOWN,            /**< @ref IPD_EVENT_GTP_INFORMATION_GBR_DOWN */

    PACE2_NUMBER_OF_ADVANCED_GTP_EVENT_TYPES      /**< Number of implemented event types. */
} PACE2_advanced_GTP_event_type;

/* Event Structures *************************************************************/

#ifndef PACE2_DISABLE_DECODER

/**
 * @brief Data structure for advanced GTP events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_ADVANCED_GTP_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_advanced_GTP_event_type meta_data_type;       /**< GTP event subtype. */
    PACE2_ADVANCED_META_DATA_EVENT_EXTRA_FIELDS;
    union {
        struct ipd_gtp_message message;                 /**< Contains data for a @ref PACE2_ADVANCED_GTP_MESSAGE event. */
        struct ipd_gtp_message_data extension;          /**< Contains data for a @ref PACE2_ADVANCED_GTP_EXTENSION event. */
        struct ipd_gtp_message_data data;               /**< Contains data for a @ref PACE2_ADVANCED_GTP_DATA event. */
        u64 message_end;                                /**< Contains data for a @ref PACE2_ADVANCED_GTP_MESSAGE_END event. */
        struct ipd_gtp_information information;         /**< Contains data for a @ref PACE2_ADVANCED_GTP_INFORMATION event. */
        struct ipd_gtp_information_string imsi;         /**< Contains data for a @ref PACE2_ADVANCED_GTP_INFORMATION_IMSI event. */
        struct ipd_gtp_information_string imei;         /**< Contains data for a @ref PACE2_ADVANCED_GTP_INFORMATION_IMEI event. */
        struct ipd_gtp_information_string msisdn;       /**< Contains data for a @ref PACE2_ADVANCED_GTP_INFORMATION_MSISDN event. */
        struct ipd_gtp_information_string apn;          /**< Contains data for a @ref PACE2_ADVANCED_GTP_INFORMATION_APN event. */
        struct ipd_gtp_information_value teid_data_1;   /**< Contains data for a @ref PACE2_ADVANCED_GTP_INFORMATION_TEID_DATA_I event. */
        struct ipd_gtp_information_value teid_data_2;   /**< Contains data for a @ref PACE2_ADVANCED_GTP_INFORMATION_TEID_DATA_II event. */
        struct ipd_gtp_information_value teid_control;  /**< Contains data for a @ref PACE2_ADVANCED_GTP_INFORMATION_TEID_CONTROL event. */
        struct ipd_gtp_information_value rat;           /**< Contains data for a @ref PACE2_ADVANCED_GTP_INFORMATION_RAT event. */
        struct ipd_gtp_information_value lac;           /**< Contains data for a @ref PACE2_ADVANCED_GTP_INFORMATION_LAC event. */
        struct ipd_gtp_information_value rac;           /**< Contains data for a @ref PACE2_ADVANCED_GTP_INFORMATION_RAC event. */
        struct ipd_gtp_information_value ebi;           /**< Contains data for a @ref PACE2_ADVANCED_GTP_INFORMATION_EBI event. */
        struct ipd_gtp_information_cell_ident cid;      /**< Contains data for a @ref PACE2_ADVANCED_GTP_INFORMATION_CID event. */
        struct ipd_gtp_information_address address;     /**< Contains data for a @ref PACE2_ADVANCED_GTP_INFORMATION_ADDRESS event. */
        struct ipd_gtp_information_group group;         /**< Contains data for a @ref PACE2_ADVANCED_GTP_INFORMATION_GROUP. */
        struct ipd_gtp_information_value arp;           /**< Contains data for a @ref PACE2_ADVANCED_GTP_INFORMATION_ARP event. */
        struct ipd_gtp_information_value qci;           /**< Contains data for a @ref PACE2_ADVANCED_GTP_INFORMATION_QCI event. */
        struct ipd_gtp_information_value mbr_up;        /**< Contains data for a @ref PACE2_ADVANCED_GTP_INFORMATION_MBR_UP event. */
        struct ipd_gtp_information_value mbr_down;      /**< Contains data for a @ref PACE2_ADVANCED_GTP_INFORMATION_MBR_DOWN event. */
        struct ipd_gtp_information_value gbr_up;        /**< Contains data for a @ref PACE2_ADVANCED_GTP_INFORMATION_GBR_UP event. */
        struct ipd_gtp_information_value gbr_down;      /**< Contains data for a @ref PACE2_ADVANCED_GTP_INFORMATION_GBR_DOWN event. */
        u64 group_end;                                  /**< Contains data for a @ref PACE2_ADVANCED_GTP_INFORMATION_GROUP_END. */
        const char *invalid;                            /**< Contains data for a @ref PACE2_ADVANCED_GTP_INVALID event. */
    } event_data;                                       /**< Named union which contains the data of the sub-event types. */
} PACE2_advanced_GTP_event;

#endif

#endif /* GTP_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
