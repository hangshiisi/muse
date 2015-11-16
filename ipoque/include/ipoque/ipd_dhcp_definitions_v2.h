/********************************************************************************/
/**
 ** \file       ipd_dhcp_definitions_v2.h
 ** \brief      Structures and enumerations for all events of DHCP on PACE2.
 **/
/********************************************************************************/

#ifndef IPD_DHCP_DEFINITIONS_V2_H_
#define IPD_DHCP_DEFINITIONS_V2_H_

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif

/** Enumeration for the content type of a DHCP option */
enum ipd_dhcp_content_type
{
    /** Signals that the content type of the DHCP option is unknown. The field content.data is set. */
    IPD_DHCP_CONTENT_TYPE_UNKNOWN,
    /** Signals that the content type of the DHCP option is an IP. The field content.ip is set */
    IPD_DHCP_CONTENT_TYPE_IP,
    /** Signals that the content type of the DHCP option is a message type. The field content.message_type is set */
    IPD_DHCP_CONTENT_TYPE_MESSAGE_TYPE,
    /** Signals that the content type of the DHCP option is a time value. The field content.ip_time_value is set */
    IPD_DHCP_CONTENT_TYPE_TIME,
    /** Signals that the content type of the DHCP option is a suboption. The field content.suboption is set */
    IPD_DHCP_CONTENT_TYPE_SUBOPTION,
    /** Signals that the content type of the DHCP option is uninterpreted. The field content.data is set. */
    IPD_DHCP_CONTENT_TYPE_UNINTERPRETED,
    /** Signals that the DHCP option has no explicit content. No content field is set. */
    IPD_DHCP_CONTENT_TYPE_NONE,
};

/** data decoded from one option or sub-option in a DHCP message; */
struct ipd_dhcp_option
{
    /** transaction ID (in network byte order), ie. the xid field of the DHCP message */
    u32 transaction_id;

    /** option type */
    enum ipd_dhcp_option_type_enum option_type;

    /** length of the option or sub-option value in bytes (without the type and length byte) */
    u8 option_length;

    /** type of the options content */
    enum ipd_dhcp_content_type content_type;

    union
    {
        /** option value: DHCP message type (option type ::IPD_DHCP_OPTION_TYPE_DHCP_MESSAGE_TYPE) */
        enum ipd_dhcp_option_message_type_enum message_type;

        struct
        {
            /** sub-option type (option type ::IPD_DHCP_OPTION_TYPE_RELAY_AGENT) */
            u8 type;

            /** uninterpreted byte array (sub-option value for ::IPD_DHCP_OPTION_TYPE_RELAY_AGENT's sub-options) */
            struct ipd_string data;

        } suboption;

        /** uninterpreted byte array (option value for
         * ::IPD_DHCP_OPTION_TYPE_PARAMETER_REQ_LIST, ::IPD_DHCP_OPTION_TYPE_CLIENT_IDENTIFIER,
         * and option types not explicitly listed in ::ipd_dhcp_option_type_enum) */
        struct ipd_string data;

        /** option value: IP address in network byte order
         * (option types ::IPD_DHCP_OPTION_TYPE_SUBNET_MASK, ::IPD_DHCP_OPTION_TYPE_REQ_IP, ::IPD_DHCP_OPTION_TYPE_DHCP_SERVER_IP) */
        struct in_addr ip;

        /** option value: time in seconds (option types ::IPD_DHCP_OPTION_TYPE_IP_LEASE_TIME,
         * ::IPD_DHCP_OPTION_TYPE_RENEWAL_TIME_VAL, ::IPD_DHCP_OPTION_TYPE_REBINDING_TIME_VAL) */
        u32 ip_time_value;
    } content;
};

typedef struct ipd_dhcp_option ipd_dhcp_option_int_t;

#endif /* IPD_DHCP_DEFINITIONS_V2_H_ */
