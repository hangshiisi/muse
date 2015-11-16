/********************************************************************************/
/**
 ** \file       dhcp_events.h
 ** \brief      DHCP event definitions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef DHCP_EVENTS_H
#define DHCP_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the basic DHCP event.
 */
#define PACE2_BASIC_DHCP_EVENT_GROUP PACE2_POLLING_PROTOCOL_META_DATA_GROUP

/**
 * @brief Public define for the assigned meta data group of the advanced DHCP event.
 */
#define PACE2_ADVANCED_DHCP_EVENT_GROUP PACE2_ADVANCED_PROTOCOL_META_DATA_GROUP

/* Event Types ******************************************************************/

/**
 * @brief DHCP meta data flags of a basic DHCP event.
 */
enum PACE2_basic_DHCP_event_mask {
    PACE2_BASIC_DHCP_YOUR_IP_ADDR = 0,          /**< Host IP-address flag. */
    PACE2_BASIC_DHCP_CLIENT_MAC_ADDR,           /**< Client MAC-address flag. */
    PACE2_BASIC_DHCP_ADDR_LEASE_TIME,           /**< DHCP lease time flag. */
    PACE2_BASIC_DHCP_MESSAGE_TYPE,              /**< DHCP message type flag. */

    PACE2_NUMBER_OF_BASIC_DHCP_FLAGS            /**< Number of implemented basic DHCP flags. */
};

/**
 * @brief Types of advanced DHCP events.
 */
typedef enum {
    PACE2_ADVANCED_DHCP_GENERAL_PACKET_INFORMATION,   /**< @ref IPD_EVENT_DHCP_GENERAL_PACKET_INFORMATION */
    PACE2_ADVANCED_DHCP_OPTION,                       /**< @ref IPD_EVENT_DHCP_OPTION */
    PACE2_ADVANCED_DHCPV6_MESSAGE,                    /**< @ref IPD_EVENT_DHCPV6_MESSAGE */

    PACE2_NUMBER_OF_ADVANCED_DHCP_EVENT_SUBTYPES /**< Number of implemented advanced DHCP events. */
} PACE2_advanced_DHCP_event_type;

/* Event Structures *************************************************************/

/**
 * @brief Data structure of a basic DHCP events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_BASIC_DHCP_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_bitmask meta_data_mask;                   /**< Bitmask, which states the available DHCP meta data */
    u32 your_ip_addr;                               /**< Variable of the @ref PACE2_BASIC_DHCP_YOUR_IP_ADDR flag.
                                                         Contains a IPv4-address in network byte order. */
    PACE2_byte_buffer client_mac_addr;              /**< Data structure of the @ref PACE2_BASIC_DHCP_CLIENT_MAC_ADDR flag. */
    u32 addr_lease_time;                            /**< Variable of the @ref PACE2_BASIC_DHCP_ADDR_LEASE_TIME flag. */
    u8 message_type;                                /**< Variable of the @ref PACE2_BASIC_DHCP_MESSAGE_TYPE flag. */
} PACE2_basic_DHCP_event;

#ifndef PACE2_DISABLE_DECODER

typedef struct {
    /** Global event type, has to be @ref PACE2_ADVANCED_DHCP_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_advanced_DHCP_event_type meta_data_type;  /**< Advanced DHCP event subtype. */
    PACE2_ADVANCED_META_DATA_EVENT_EXTRA_FIELDS;
    union {
        struct ipd_dhcp_general_packet_information gpi; /**< Contains data for a @ref PACE2_ADVANCED_DHCP_GENERAL_PACKET_INFORMATION event. */
        struct ipd_dhcp_option option;                  /**< Contains data for a @ref PACE2_ADVANCED_DHCP_OPTION event. */
        struct ipd_dhcpv6_message dhcpv6_message;       /**< Contains data for a @ref PACE2_ADVANCED_DHCPV6_MESSAGE event. */
    };
} PACE2_advanced_DHCP_event;

#endif

#endif /* DHCP_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
