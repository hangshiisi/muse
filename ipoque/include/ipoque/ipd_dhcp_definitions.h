/********************************************************************************/
/**
 ** \file       ipd_dhcp_definitions.h
 ** \brief      Structures and enumerations for all events of DHCP.
 **/
/********************************************************************************/

#ifndef IPD_DHCP_DEFINITIONS_H_
#define IPD_DHCP_DEFINITIONS_H_

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif

/** enumeration for DHCP Message Types */
enum ipd_dhcp_message_type_enum
{
    IPD_DHCP_MESSAGE_TYPE_REQUEST = 1,
    IPD_DHCP_MESSAGE_TYPE_REPLY = 2,
};

/** Hardware Types, equates to the OSI-Model Layer 1 */
enum ipd_dhcp_hardware_type_enum
{
    IPD_DHCP_HARDWARE_TYPE_ETHERNET = 1,
};

/** enumeration of option message types */
enum ipd_dhcp_option_message_type_enum
{
    IPD_DHCP_OPTION_MESSAGE_TYPE_DISCOVER = 1,
    IPD_DHCP_OPTION_MESSAGE_TYPE_OFFER = 2,
    IPD_DHCP_OPTION_MESSAGE_TYPE_REQUEST = 3,
    IPD_DHCP_OPTION_MESSAGE_TYPE_DECLINE = 4,
    IPD_DHCP_OPTION_MESSAGE_TYPE_ACK = 5,
    IPD_DHCP_OPTION_MESSAGE_TYPE_NACK = 6,
    IPD_DHCP_OPTION_MESSAGE_TYPE_RELEASE = 7,
    IPD_DHCP_OPTION_MESSAGE_TYPE_INFORM = 8,
};

/** enumerates the different option types */
enum ipd_dhcp_option_type_enum
{
    IPD_DHCP_OPTION_TYPE_SUBNET_MASK = 1,           /**< Subnet Mask */
    IPD_DHCP_OPTION_TYPE_REQ_IP = 50,               /**< Requested IP Address */
    IPD_DHCP_OPTION_TYPE_IP_LEASE_TIME = 51,        /**< IP Address Lease Time */
    IPD_DHCP_OPTION_TYPE_DHCP_MESSAGE_TYPE = 53,    /**< DHCP Message Type */
    IPD_DHCP_OPTION_TYPE_DHCP_SERVER_IP = 54,       /**< Server Identifier */
    IPD_DHCP_OPTION_TYPE_PARAMETER_REQ_LIST = 55,   /**< Parameter Request List */
    IPD_DHCP_OPTION_TYPE_RENEWAL_TIME_VAL = 58,     /**< Renewal (T1) Time Value */
    IPD_DHCP_OPTION_TYPE_REBINDING_TIME_VAL = 59,   /**< Rebinding (T2) Time Value */
    IPD_DHCP_OPTION_TYPE_CLIENT_IDENTIFIER = 61,    /**< Client-identifier */
    IPD_DHCP_OPTION_TYPE_RELAY_AGENT = 82,          /**< Relay Agent Information; one ::IPD_EVENT_DHCP_OPTION event is sent
                                                     * for each sub-option */
};

/** this event contains the information sent with every single DHCP packet */
struct ipd_dhcp_general_packet_information
{
    /** message op code/message type - Request and Reply */
    enum ipd_dhcp_message_type_enum message_type;
    /** hardware address type */
    enum ipd_dhcp_hardware_type_enum hardware_type;
    /** client hardware address */
    struct ipd_string client_hardware_address;
    /** transaction ID (in network byte order) */
    u32 transaction_id;
};


/** normal enumeration of events thrown by the DHCP decoder */
enum ipd_simple_event_dhcp_enumeration
{
    /** Fields extracted from the header of each DHCP message; \c data points to a */
    IPD_EVENT_DHCP_GENERAL_PACKET_INFORMATION, /**< struct ipd_dhcp_general_packet_information. */
    
    /** Represents one option or sub-option inside a DHCP message; \c data points to a */
    IPD_EVENT_DHCP_OPTION,      /**< struct ipd_dhcp_option. */

    /** Number of events the DHCP Decoder throws */
    IPD_NUMBER_OF_DHCP_EVENTS,
};

#endif /* IPD_DHCP_DEFINITIONS_H_ */
