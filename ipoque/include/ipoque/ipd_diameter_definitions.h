/********************************************************************************/
/**
 ** \file       ipd_diameter_definitions.h
 ** \brief      Event definitions for the Diameter Protocol.
 **/
/********************************************************************************/

#ifndef __IPOQUE_DECODER_DIAMETER_INCLUDE_FILE__
#define __IPOQUE_DECODER_DIAMETER_INCLUDE_FILE__

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif

/** Enum of supported Diameter Vendor.
 * */
enum ipd_diameter_supported_vendors
{
    IPD_DIAMETER_VEN_3GPP                        = 10415     /*IANA assigned Vendor ID for 3GPP*/
};

/** Enum of  diameter message type.
 * */
enum ipd_diameter_message_type
{
    IPD_DIAMETER_MESSAGE_TYPE_RESPONSE                       = 0,/*Message is a response to a request*/
    IPD_DIAMETER_MESSAGE_TYPE_REQUEST                       = 1/*Message is a request*/
};
/** Enum of  diameter message flags.
 * */
enum ipd_diameter_message_flags
{
    IPD_DIAMETER_MESSAGE_FLAG_REQUEST                       = 0x80,/*Message is a request*/
    IPD_DIAMETER_MESSAGE_FLAG_ERROR                       = 0x20,/*Message is a response to an erroneous request or an error has occurred*/
    IPD_DIAMETER_MESSAGE_FLAG_PROXIABLE                       = 0x40,/*Message is proxiable*/
    IPD_DIAMETER_MESSAGE_FLAG_RE_TRANSMIT                       = 0x10/*Message is a retransmission*/
};
/** Enum of  diameter AVP flags.
 * */
enum ipd_diameter_avp_flags
{
    IPD_DIAMETER_AVP_FLAG_VENDOR                       = 0x80,/*AVP is vendor specific*/
    IPD_DIAMETER_AVP_FLAG_MANDATORY                       = 0x40,/*AVP is part of mandatory specifications*/
    IPD_DIAMETER_AVP_FLAG_ENCRYPTED                       = 0x20/*AVP should be encrypted.*/

};
/** Enum of supported Diameter AVP types.
 * */
enum ipd_diameter_attr_types
{
    IPD_DIAMETER_ATTR_USER_NAME                        = 1,      /*Text string/UTF-8*/
    IPD_DIAMETER_ATTR_USER_PASSWORD                    = 2,      /*Hexadecimal/UTF-8*/
    IPD_DIAMETER_ATTR_CHAP_PASSWORD                    = 3,      /*Hexadecimal string*/
    IPD_DIAMETER_ATTR_NAS_IP_ADDRESS                   = 4,      /*IPv4 style Address*/
    IPD_DIAMETER_ATTR_NAS_PORT                         = 5,      /*Unsigned32*/
    IPD_DIAMETER_ATTR_SERVICE_TYPE                     = 6,      /*Unsigned32 */
    IPD_DIAMETER_ATTR_FRAMED_PROTOCOL                  = 7,      /*Unsigned32 */
    IPD_DIAMETER_ATTR_FRAMED_IP_ADDRESS                = 8,      /*IPv4 style Address*/
    IPD_DIAMETER_ATTR_FRAMED_IP_NETMASK                = 9,      /*IPv4 style Address*/
    IPD_DIAMETER_ATTR_FRAMED_ROUTING                   = 10,     /*Unsigned32 */
    IPD_DIAMETER_ATTR_FILTER_ID                        = 11,     /*Text string/UTF-8*/
    IPD_DIAMETER_ATTR_FRAMED_MTU                       = 12,     /*Unsigned32*/
    IPD_DIAMETER_ATTR_FRAMED_COMPRESSION               = 13,     /*Unsigned32 */
    IPD_DIAMETER_ATTR_LOGIN_IP_HOST                    = 14,     /*IPv4 style Address*/
    IPD_DIAMETER_ATTR_LOGIN_SERVICE                    = 15,     /*Unsigned32 */
    IPD_DIAMETER_ATTR_LOGIN_TCP_PORT                   = 16,     /*Unsigned32*/
    IPD_DIAMETER_ATTR_REPLY_MESSAGE                    = 18,     /*Text string/UTF-8*/
    IPD_DIAMETER_ATTR_CALLBACK_NUMBER                  = 19,     /*Hexadecimal string*/
    IPD_DIAMETER_ATTR_CALLBACK_ID                      = 20,     /*Hexadecimal string*/
    IPD_DIAMETER_ATTR_FRAMED_ROUTE                     = 22,     /*Text string/UTF-8*/
    IPD_DIAMETER_ATTR_FRAMED_IPX_NETWORK               = 23,     /*IPv4 style Address*/
    IPD_DIAMETER_ATTR_STATE                            = 24,     /*Hexadecimal string*/
    IPD_DIAMETER_ATTR_CLASS                            = 25,     /*Hexadecimal string*/
    IPD_DIAMETER_ATTR_VENDOR_SPECIFIC                  = 26,     /*Hexadecimal string*/
    IPD_DIAMETER_ATTR_SESSION_TIMEOUT                  = 27,     /*Unsigned32 Time */
    IPD_DIAMETER_ATTR_IDLE_TIMEOUT                     = 28,     /*Unsigned32 Time*/
    IPD_DIAMETER_ATTR_TERMINATION_ACTION               = 29,     /*Unsigned32 */
    IPD_DIAMETER_ATTR_CALLED_STATION_ID                = 30,     /*Hexadecimal string*/
    IPD_DIAMETER_ATTR_CALLING_STATION_ID               = 31,     /*Hexadecimal string*/
    IPD_DIAMETER_ATTR_NAS_IDENTIFIER                   = 32,     /*Hexadecimal string*/
    IPD_DIAMETER_ATTR_PROXY_STATE                      = 33,     /*Hexadecimal string*/
    IPD_DIAMETER_ATTR_LOGIN_LAT_SERVICE                = 34,     /*Text string/UTF-8*/
    IPD_DIAMETER_ATTR_LOGIN_LAT_NODE                   = 35,     /*Text string/UTF-8*/
    IPD_DIAMETER_ATTR_LOGIN_LAT_GROUP                  = 36,     /*Hexadecimal string*/
    IPD_DIAMETER_ATTR_FRAMED_APPLETALK_LINK            = 37,     /*Unsigned32*/
    IPD_DIAMETER_ATTR_FRAMED_APPLETALK_NETWORK         = 38,     /*Unsigned32*/
    IPD_DIAMETER_ATTR_FRAMED_APPLETALK_ZONE            = 39,     /*Text string/UTF-8*/
    IPD_DIAMETER_ATTR_ACCT_STATUS_TYPE                 = 40,     /*Unsigned32 */
    IPD_DIAMETER_ATTR_ACCT_DELAY_TIME                  = 41,     /*Unsigned32 Time*/
    IPD_DIAMETER_ATTR_ACCT_INPUT_OCTETS                = 42,     /*Unsigned32*/
    IPD_DIAMETER_ATTR_ACCT_OUTPUT_OCTETS               = 43,     /*Unsigned32*/
    IPD_DIAMETER_ATTR_ACCT_SESSION_ID                  = 44,     /*Text string/UTF-8*/
    IPD_DIAMETER_ATTR_ACCT_AUTHENTIC                   = 45,     /*Unsigned32 */
    IPD_DIAMETER_ATTR_ACCT_SESSION_TIME                = 46,     /*Unsigned32 */
    IPD_DIAMETER_ATTR_ACCT_INPUT_PACKETS               = 47,     /*Unsigned32*/
    IPD_DIAMETER_ATTR_ACCT_OUTPUT_PACKETS              = 48,     /*Unsigned32*/
    IPD_DIAMETER_ATTR_ACCT_TERMINATE_CAUSE             = 49,     /*Unsigned32 */
    IPD_DIAMETER_ATTR_ACCT_MULTI_SESSION_ID            = 50,     /*Text string/UTF-8*/
    IPD_DIAMETER_ATTR_ACCT_LINK_COUNT                  = 51,     /*Unsigned32*/
    IPD_DIAMETER_ATTR_CHAP_CHALLENGE                   = 60,     /*Hexadecimal string*/
    IPD_DIAMETER_ATTR_NAS_PORT_TYPE                    = 61,     /*Unsigned32 */
    IPD_DIAMETER_ATTR_PORT_LIMIT                       = 62,     /*Unsigned32*/
    IPD_DIAMETER_ATTR_LOGIN_LAT_PORT                   = 63,     /*Text string/UTF-8*/
    IPD_DIAMETER_ATTR_FRAMED_IPV6_PREFIX               = 97,     /*IPv6 style Address*/
    IPD_DIAMETER_ATTR_FRAMED_IPV6_ROUTE                = 99,     /*Text string/UTF-8*/
    IPD_DIAMETER_ATTR_DELEGATED_IPV6_PREFIX            = 123,    /*Hexadecimal string*/
    IPD_DIAMETER_ATTR_HOST_IP_ADDRESS                  = 257,    /* Derived IPv4/IPv6 address.*/
    IPD_DIAMETER_ATTR_AUTH_APPLICATION_ID              = 258,    /*Unsigned32*/
    IPD_DIAMETER_ATTR_ACCT_APPLICATION_ID              = 259,    /*Unsigned32*/
    IPD_DIAMETER_ATTR_VENDOR_SPECIFIC_APPLICATION_ID   = 260,    /*Grouped AVP's*/
    IPD_DIAMETER_ATTR_REDIRECT_HOST_USAGE              = 261,    /*DiameterURI*/
    IPD_DIAMETER_ATTR_REDIRECT_MAX_CACHE_TIME          = 262,    /*Unsigned32 */
    IPD_DIAMETER_ATTR_SESSION_ID                       = 263,    /*Text string/UTF-8  */
    IPD_DIAMETER_ATTR_ORIGIN_HOST                      = 264,    /*DiameterIdentity: Human readable text string*/
    IPD_DIAMETER_ATTR_SUPPORTED_VENDOR_ID              = 265,    /*Unsigned32 */
    IPD_DIAMETER_ATTR_VENDOR_ID                        = 266,    /*Unsigned32 */
    IPD_DIAMETER_ATTR_RESULT_CODE                      = 268,    /*Unsigned32 */
    IPD_DIAMETER_ATTR_SESSION_BINDING                  = 270,    /*Unsigned32*/
    IPD_DIAMETER_ATTR_DISCONNECT_CAUSE                 = 273,    /*Unsigned32 */
    IPD_DIAMETER_ATTR_AUTH_REQUEST_TYPE                = 274,    /*Unsigned32 */
    IPD_DIAMETER_ATTR_AUTH_SESSION_STATE               = 277,    /*Unsigned32 */
    IPD_DIAMETER_ATTR_PROXY_HOST                       = 280,    /*DiameterIdentity.*/
    IPD_DIAMETER_ATTR_DESTINATION_REALM                = 283,    /*DiameterIdentity.*/
    IPD_DIAMETER_ATTR_RE_AUTH_REQUEST_TYPE             = 285,    /*Unsigned32 */
    IPD_DIAMETER_ATTR_DESTINATION_HOST                 = 293,    /*DiameterIdentity.*/
    IPD_DIAMETER_ATTR_TERMINATION_CAUSE                = 295,    /*Unsigned32 */
    IPD_DIAMETER_ATTR_ORIGIN_REALM                     = 296,    /*DiameterIdentity.*/
    IPD_DIAMETER_ATTR_CC_INPUT_OCTETS                  = 412,    /*Unsigned64 */
    IPD_DIAMETER_ATTR_CC_OUTPUT_OCTETS                 = 414,    /*Unsigned64 */
    IPD_DIAMETER_ATTR_CC_REQUEST_NUMBER                = 415,    /*Unsigned32 */
    IPD_DIAMETER_ATTR_CC_REQUEST_TYPE                  = 416,    /*Unsigned32 */
    IPD_DIAMETER_ATTR_CC_TOTAL_OCTETS                  = 421,    /*Unsigned64 */
    IPD_DIAMETER_ATTR_FINAL_UNIT_INDICATION            = 430,    /*Grouped AVP's*/
    IPD_DIAMETER_ATTR_GRANTED_SERVICE_UNIT             = 431,    /*Grouped AVP's*/
    IPD_DIAMETER_ATTR_RATING_GROUP                     = 432,    /*Unsigned32 */
    IPD_DIAMETER_ATTR_REQUESTED_SERVICE_UNIT           = 437,    /*Grouped AVP's */
    IPD_DIAMETER_ATTR_SERVICE_IDENTIFIER               = 439,    /*Unsigned32*/
    IPD_DIAMETER_ATTR_SUBSCRIPTION_ID                  = 443,    /*Grouped AVP's { Subscription-Id-Type } { Subscription-Id-Data }*/
    IPD_DIAMETER_ATTR_SUBSCRIPTION_ID_DATA             = 444,    /*Text string/UTF-8  */
    IPD_DIAMETER_ATTR_USED_SERVICE_UNITV               = 446,    /*Grouped AVP's*/
    IPD_DIAMETER_ATTR_VALIDITY_TIME                    = 448,    /*Unsigned32 time */
    IPD_DIAMETER_ATTR_FINAL_UNIT_ACTION                = 449,    /*Unsigned32 */
    IPD_DIAMETER_ATTR_SUBSCRIPTION_ID_TYPE             = 450,    /*Unsigned32 */
    IPD_DIAMETER_ATTR_MULTIPLE_SERVICES_INDICATOR      = 455,    /*Unsigned32 */
    IPD_DIAMETER_ATTR_MULTIPLE_SERVICES_CREDIT_CONTROL = 456,    /*Grouped AVP's */
    IPD_DIAMETER_ATTR_ACCOUNTING_RECORD_TYPE           = 480,    /*Unsigned32 */
    IPD_DIAMETER_ATTR_FLOW_STATUS                      = 511,    /*Unsigned32 */
    IPD_DIAMETER_ATTR_VOLUME_QUOTA_THRESHOLD           = 869,    /*Unsigned32  {V,3GPP(10415)}*/
    IPD_DIAMETER_ATTR_QUOTA_HOLDING_TIME               = 871,    /*Unsigned32   {V,3GPP(10415)}*/
    IPD_DIAMETER_ATTR_REPORTING_REASON                 = 872,    /*Unsigned32 */
    IPD_DIAMETER_ATTR_CHARGING_RULE_INSTALL            = 1001,   /*Grouped AVP's {V,3GPP(10415)}*/
    IPD_DIAMETER_ATTR_CHARGING_RULE_REMOVE             = 1002,   /*Grouped AVP's {V,3GPP(10415)}*/
    IPD_DIAMETER_ATTR_CHARGING_RULE_DEFINITION         = 1003,   /*Grouped AVP's {V,3GPP(10415)}*/
    IPD_DIAMETER_ATTR_CHARGING_RULE_NAME               = 1005,   /*Hexadecimal string {V,3GPP(10415)}*/
    IPD_DIAMETER_ATTR_EVENT_TRIGGER                    = 1006,   /*Unsigned32 */
    IPD_DIAMETER_ATTR_ONLINE                           = 1009,   /*Unsigned32 */
    IPD_DIAMETER_ATTR_REPORTING_LEVEL                  = 1011,   /*Unsigned32 */
    IPD_DIAMETER_ATTR_QOS_INFORMATION                  = 1016,   /*Grouped AVP's {V,3GPP(10415)}*/
    IPD_DIAMETER_ATTR_GUARANTED_BITRATE_DL             = 1025,   /*Unsigned32  {V,3GPP(10415)}*/
    IPD_DIAMETER_ATTR_GUARANTED_BITRATE_UL             = 1026,   /*Unsigned32  {V,3GPP(10415)}*/
    IPD_DIAMETER_ATTR_FLOW_INFORMATION                 = 1058,   /*Grouped AVP's {V,3GPP(10415)}*/
    IPD_DIAMETER_ATTR_MONITORING_KEY                   = 1066,   /*Hexadecimal string {V,3GPP(10415)}*/
    IPD_DIAMETER_ATTR_USAGE_MONITORING_INFORMATION     = 1067,   /*Grouped AVP's {V,3GPP(10415)}*/
    IPD_DIAMETER_ATTR_USAGE_MONITORING_REPORT          = 1069,   /*Unsigned32 */
    IPD_DIAMETER_ATTR_USAGE_MONITORING_SUPPORT         = 1070,   /*Unsigned32 */
    IPD_DIAMETER_ATTR_MONITORING_TIME                  = 2810    /*Unsigned32 Time {V,3GPP(10415)}*/
};
/** Enumeration for simple diameter events. This is given by the \c type at \ref ipd_decoder_event_callback
 */
enum ipd_simple_event_diameter_enumeration
{
    /** Provides a structure with message header information.*/
    IPD_EVENT_DIAMETER_GENERAL_PACKET_INFORMATION,/*struct ipd_diameter_general_packet_information*/
    /** Provides a structure with single attribute information of a message.*/
    IPD_EVENT_DIAMETER_ATTRIBUTE, /*struct ipd_diameter_avp_information*/
    /** Provides information about error in data stream */
    IPD_EVENT_DIAMETER_INVALID, /*Error message*/
    /** Provides information about diameter TCP Connection termination*/
    IPD_EVENT_DIAMETER_CONNECTION_TERMINATION,/*struct ipd_diameter_connection_end*/
    /** Provides information about diameter TCP Connection termination*/
    IPD_EVENT_DIAMETER_MESSAGE_TERMINATION,/*struct ipd_diameter_message_end*/
    /** Number of events the Radius Decoder throws */
    IPD_NUMBER_OF_DIAMETER_EVENTS,
};
/** Enumeration for diameter data types.
 */
enum ipd_diameter_avp_datatype_enumeration
{

    /** AVP Data type hexadecimal octet string.,contains ipd_string*/
    IPD_DIAMETER_TYPE_OCTET_STRING = 1,
    /** AVP Data type signed 64 bit integer.*/
    IPD_DIAMETER_TYPE_INT64 = 2,
    /** AVP Data type  signed 32 bit integer*/
    IPD_DIAMETER_TYPE_INT32 = 3,
    /** AVP Data type unsigned 64 bit integer*/
    IPD_DIAMETER_TYPE_UINT64 = 4,
    /** AVP Data type  unsigned 32 bit integer*/
    IPD_DIAMETER_TYPE_UINT32 = 5,
    /** AVP Data type 64 bit floating point number*/
    IPD_DIAMETER_TYPE_FLOAT64 = 6,
    /** AVP Data type  32 bit floating point number*/
    IPD_DIAMETER_TYPE_FLOAT32 = 7,
    /** AVP Data type grouped,contains two or more nested AVPs,contains ipd_string.*/
    IPD_DIAMETER_TYPE_GROUPED = 8,
    /** AVP Data type IPv6 address,contains IPv4 address in ip_v4_v6_addr*/
    IPD_DIAMETER_TYPE_IPV4_ADDR = 10,
    /** AVP Data type IPv6 address,contains IPv6 address in ip_v4_v6_addr*/
    IPD_DIAMETER_TYPE_IPV6_ADDR = 11,
    /** AVP Data type Time,contains 4 byte UTC time*/
    IPD_DIAMETER_TYPE_TIME = 12,
    /** AVP Data type UTF8 string, contains data in ipd_Charset_string structure*/
    IPD_DIAMETER_TYPE_UTF8_STR = 13,
    /** AVP Data type Diameter ID, contains data in ipd_string: :aaa://" FQDN [ port ] [ transport ] [ protocol ]*/
    IPD_DIAMETER_TYPE_DIAMETER_ID = 14,
    /** AVP Data type Diameter URI,contains data in ipd_string :aaa://" FQDN [ port ] [ transport ] [ protocol ]*/
    IPD_DIAMETER_TYPE_DIAMETER_URI = 15,
    /** AVP Data type IP filter rule from freebsd,contains data in ipd_string:pass out quick on dc0 proto tcp from any to any port = 443 flags S keep state*/
    IPD_DIAMETER_TYPE_IP_FILTER_RULE = 16,
    /**AVP Data type  raw,contains data in ipd_string.The data type of this AVP is unknown,AVP not supported. */
    IPD_DIAMETER_TYPE_RAW = -1,
    /**AVP type Unknown,AVP content is too big o handle and therefore not supported. */
    IPD_DIAMETER_TYPE_UNKNOWN = -2,
};
/** contains the Information sent with every diameter message*/
struct ipd_diameter_general_packet_information
{
    /** Command code of diameter message */
    u32 command_code;
    /** Diameter protocol version used by the diameter message we support only version 1 */
    u8 version;
    /** Diameter message type IPD_DIAMETER_MESSAGE_TYPE_RESPONSE or IPD_DIAMETER_MESSAGE_TYPE_REQUEST*/
    u8 type;
    /**Diameter message flags see enum ipd_diameter_message_flags */
    u8 flags;
    /**Application for which the diameter message is intended*/
    u32 application_id;
    /**Diameter message Hop-by-Hop  id field*/
    u32 hop_by_hop_id;
    /**Diameter message End-to-end id field*/
    u32 end_to_end_id;
    /**Diameter message length*/
    u32 message_length;
    /**Unique message id for every Diameter message to correlate message header with AVP events*/
    u64 local_message_id;
};
struct ipd_diameter_message_end
{
    /** Command code of diameter message */
    u32 command_code;
    /** Diameter message type IPD_DIAMETER_MESSAGE_TYPE_RESPONSE or IPD_DIAMETER_MESSAGE_TYPE_REQUEST*/
    u8 type;
    /**Diameter message flags see enum ipd_diameter_message_flags */
    u8 flags;
    /**Application for which the diameter message is intended*/
    u32 application_id;
    /**Diameter message Hop-by-Hop  id field*/
    u32 hop_by_hop_id;
    /**Diameter message End-to-end id field*/
    u32 end_to_end_id;
    /**Diameter message length*/
    u32 message_length;
    /**Unique message id for every Diameter message to correlate message header with AVP events*/
    u64 local_message_id;
    /**Number of AVPs in the message*/
    u32 avp_counts;

};

struct ipd_diameter_connection_end
{
    /** Total Diameter messages received */
    u64 total_messages;
    /** Total Diameter request messages received */
    u64 request_count;
    /** Total Diameter responses messages received */
    u64 response_count;
};
/** contains the Information sent with every diameter AVP*/
struct ipd_diameter_avp_information
{
    /**Unique message id for every Diameter message to correlate message header with AVP events*/
    u64 local_message_id;
    /**Diameter AVP code*/
    u32 attribute_code;
    /**Vendor ID  if vendor specific AVP.valid if vendor flag is set else 0*/
    u32 vendor_id;
    /**AVP flags see enum ipd_diameter_avp_flags*/
    u8 flags;
    /**depth of current AVP in nested AVP stack.*/
    u16 avp_depth;
    /**AVP data type defined by ipd_diameter_data_types */
    short data_type;
    /**AVP data length*/
    u32 data_length;
    u32 remaining_len;

    union
    {
        /**IPD_DIAMETER_TYPE_OCTET_STRING */
        struct ipd_string octet_string;
        /**IPD_DIAMETER_TYPE_INT64*/
        long long int64;
        /**IPD_DIAMETER_TYPE_INT32*/
        int int32;
        /**IPD_DIAMETER_TYPE_UINT64*/
        u64 uint64;
        /**IPD_DIAMETER_TYPE_UINT32*/
        u32 uint32;
        /**IPD_DIAMETER_TYPE_FLOAT64*/
        double float64;
        /**IPD_DIAMETER_TYPE_FLOAT32*/
        float float32;
        /**IPD_DIAMETER_TYPE_GROUPED*/
        struct ipd_string grouped;
        /**IPD_DIAMETER_TYPE_IPV4_ADDR and IPD_DIAMETER_TYPE_IPV6_ADDR */
        union ip_v4_v6_addr ipv4_v6addr;
        /**IPD_DIAMETER_TYPE_TIME*/
        u32 time;
        /**IPD_DIAMETER_TYPE_UTF8_STR*/
        struct ipd_charset_string utf8_str;
        /**IPD_DIAMETER_TYPE_DIAMETER_ID*/
        struct ipd_string diameter_id;
        /**IPD_DIAMETER_TYPE_DIAMETER_URI*/
        struct ipd_string diameter_uri;
        /**IPD_DIAMETER_TYPE_IP_FILTER_RULE*/
        struct ipd_string ip_filter_rule;
        /**IPD_DIAMETER_TYPE_RAW*/
        struct ipd_string raw_data;
    } content;
};

#endif

