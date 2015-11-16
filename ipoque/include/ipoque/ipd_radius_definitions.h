/********************************************************************************/
/**
 ** \file       ipd_radius_definitions.h
 ** \brief      Structures and enumerations for all events of the Radius Protocol.
 **/
/********************************************************************************/

#ifndef __IPOQUE_DECODER_RADIUS_INCLUDE_FILE__
#define __IPOQUE_DECODER_RADIUS_INCLUDE_FILE__

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif


/** enumerates the type of packet */
enum ipd_radius_packet_code
{
    IPD_RADIUS_PACKET_CODE_ACCESS_REQUEST = 1,
    IPD_RADIUS_PACKET_CODE_ACCESS_ACCEPT = 2,
    IPD_RADIUS_PACKET_CODE_ACCESS_REJECT = 3,
    IPD_RADIUS_PACKET_CODE_ACCOUNTING_REQUEST = 4,
    IPD_RADIUS_PACKET_CODE_ACCOUNTING_RESPONSE = 5,
    IPD_RADIUS_PACKET_CODE_ACCESS_CHALLENGE = 11,
    IPD_RADIUS_PACKET_CODE_STATUS_SERVER = 12,
    IPD_RADIUS_PACKET_CODE_STATUS_CLIENT = 13,
};


/** RADIUS attribute types (RFC 2865 and 2866) */
enum ipd_radius_attributes
{
    IPD_RADIUS_ATTRIBUTES_USER_NAME = 1,                        /**< User-Name */
    IPD_RADIUS_ATTRIBUTES_PASSWORD = 2,                         /**< User-Password */
    IPD_RADIUS_ATTRIBUTES_CHAP_PASSWORD = 3,                    /**< CHAP-Password */
    IPD_RADIUS_ATTRIBUTES_NAS_IP_ADDRESS = 4,                   /**< NAS-IP-Address */
    IPD_RADIUS_ATTRIBUTES_NAS_PORT = 5,                         /**< NAS-Port */
    IPD_RADIUS_ATTRIBUTES_SERVICE_TYPE = 6,                     /**< Service-Type */
    IPD_RADIUS_ATTRIBUTES_FRAMED_PROTOCOL = 7,                  /**< Framed-Protocol */
    IPD_RADIUS_ATTRIBUTES_FRAMED_IP_ADDRESS = 8,                /**< Framed-IP-Address */
    IPD_RADIUS_ATTRIBUTES_FRAMED_IP_NETMASK = 9,                /**< Framed-IP-Netmask */
    IPD_RADIUS_ATTRIBUTES_FRAMED_ROUTING = 10,                  /**< Framed-Routing */
    IPD_RADIUS_ATTRIBUTES_FILTER_ID = 11,                       /**< Filter-Id */
    IPD_RADIUS_ATTRIBUTES_FRAMED_MTU = 12,                      /**< Framed-MTU */
    IPD_RADIUS_ATTRIBUTES_FRAMED_COMPRESSION = 13,              /**< Framed-Compression */
    IPD_RADIUS_ATTRIBUTES_LOGIN_IP_HOST = 14,                   /**< Login-IP-Host */
    IPD_RADIUS_ATTRIBUTES_LOGIN_SERVICE = 15,                   /**< Login-Service */
    IPD_RADIUS_ATTRIBUTES_LOGIN_TCP_PORT = 16,                  /**< Login-TCP-Port */

    IPD_RADIUS_ATTRIBUTES_REPLY_MESSAGE = 18,                   /**< Reply-Message */
    IPD_RADIUS_ATTRIBUTES_CALLBACK_NUMBER = 19,                 /**< Callback-Number */
    IPD_RADIUS_ATTRIBUTES_CALLBACK_ID = 20,                     /**< Callback-Id */

    IPD_RADIUS_ATTRIBUTES_FRAMED_ROUTE = 22,                    /**< Framed-Route */
    IPD_RADIUS_ATTRIBUTES_FRAMED_IPX_NETWORK = 23,              /**< Framed-IPX-Network */
    IPD_RADIUS_ATTRIBUTES_STATE = 24,                           /**< State */
    IPD_RADIUS_ATTRIBUTES_CLASS = 25,                           /**< Class */
    IPD_RADIUS_ATTRIBUTES_VENDOR_SPECIFIC = 26,                 /**< Vendor-Specific */
    IPD_RADIUS_ATTRIBUTES_SESSION_TIMEOUT = 27,                 /**< Session-Timeout */
    IPD_RADIUS_ATTRIBUTES_IDLE_TIMEOUT = 28,                    /**< Idle-Timeout */
    IPD_RADIUS_ATTRIBUTES_TERMINATION_ACTION = 29,              /**< Termination-Action */
    IPD_RADIUS_ATTRIBUTES_CALLED_STATION_ID = 30,               /**< Called-Station-Id */
    IPD_RADIUS_ATTRIBUTES_CALLING_STATION_ID = 31,              /**< Calling-Station-Id */
    IPD_RADIUS_ATTRIBUTES_NAS_IDENTIFIER = 32,                  /**< NAS-Identifier */
    IPD_RADIUS_ATTRIBUTES_PROXY_STATE = 33,                     /**< Proxy-State */
    IPD_RADIUS_ATTRIBUTES_LOGIN_LAT_SERVICE = 34,               /**< Login-LAT-Service */
    IPD_RADIUS_ATTRIBUTES_LOGIN_LAT_NODE = 35,                  /**< Login-LAT-Node */
    IPD_RADIUS_ATTRIBUTES_LOGIN_LAT_GROUP = 36,                 /**< Login-LAT-Group */
    IPD_RADIUS_ATTRIBUTES_FRAMED_APPLETALK_LINK = 37,           /**< Framed-AppleTalk-Link */
    IPD_RADIUS_ATTRIBUTES_FRAMED_APPLETALK_NETWORK = 38,        /**< Framed-AppleTalk-Network */
    IPD_RADIUS_ATTRIBUTES_FRAMED_APPLETALK_ZONE = 39,           /**< Framed-AppleTalk-Zone */

    IPD_RADIUS_ATTRIBUTES_STATUS_TYPE = 40,                     /**< Acct-Status-Type */
    IPD_RADIUS_ATTRIBUTES_DELAY_TIME = 41,                      /**< Acct-Delay-Time */
    IPD_RADIUS_ATTRIBUTES_INPUT_OCTETS = 42,                    /**< Acct-Input-Octets */
    IPD_RADIUS_ATTRIBUTES_OUTPUT_OCTETS = 43,                   /**< Acct-Output-Octets */
    IPD_RADIUS_ATTRIBUTES_SESSION_ID = 44,                      /**< Acct-Session-Id */
    IPD_RADIUS_ATTRIBUTES_AUTHENTIC = 45,                       /**< Acct-Authentic */
    IPD_RADIUS_ATTRIBUTES_SESSION_TIME = 46,                    /**< Acct-Session-Time */
    IPD_RADIUS_ATTRIBUTES_INPUT_PACKETS = 47,                   /**< Acct-Input-Packets */
    IPD_RADIUS_ATTRIBUTES_OUTPUT_PACKETS = 48,                  /**< Acct-Output-Packets */
    IPD_RADIUS_ATTRIBUTES_TERMINATE_CAUSE = 49,                 /**< Acct-Terminate-Cause */
    IPD_RADIUS_ATTRIBUTES_MULTI_SESSION_ID = 50,                /**< Acct-Multi-Session-Id */
    IPD_RADIUS_ATTRIBUTES_LINK_COUNT = 51,                      /**< Acct-Link-Count */

    IPD_RADIUS_ATTRIBUTES_CHAP_CHALLENGE = 60,                  /**< CHAP-Challenge */
    IPD_RADIUS_ATTRIBUTES_NAS_PORT_TYPE = 61,                   /**< NAS-Port-Type */
    IPD_RADIUS_ATTRIBUTES_PORT_LIMIT = 62,                      /**< Port-Limit */
    IPD_RADIUS_ATTRIBUTES_LOGIN_LAT_PORT = 63,                  /**< Login-LAT-Port */

    IPD_RADIUS_ATTRIBUTES_FRAMED_IPV6_PREFIX = 97,              /**< Framed-IPv6-Prefix */
    IPD_RADIUS_ATTRIBUTES_FRAMED_IPV6_ROUTE = 99,               /**< Framed-IPv6-Route */
    IPD_RADIUS_ATTRIBUTES_DELEGATED_IPV6_PREFIX = 123,          /**< Delegated-IPv6-Prefix */
};

/** enumerates the status types packets can have */
enum ipd_radius_status_types
{
    IPD_RADIUS_STATUS_TYPE_START = 1,
    IPD_RADIUS_STATUS_TYPE_STOP = 2,
    IPD_RADIUS_STATUS_TYPE_ACCOUNTING_ON = 7,
    IPD_RADIUS_STATUS_TYPE_ACCOUNTING_OFF = 8,
};

/** contains the Information send with every Packet */
struct ipd_radius_general_packet_information
{
    /** reason why the packet is send - enumerated in ipd_radius_packet_code */
    u8 code;
    /** Packet identifier - part of the MD5 - authenticator */
    u8 pkg_id;

    /** contains the general packet length */
    u32 pkg_len;

    /** struct contains the MD5 authenticator which is unique to a packet (so duplicates can be detected) */
    struct ipd_charset_string md5_authenticator;
};

/** Enumeration for the content type of a radius attribute */
enum ipd_radius_content_type
{
    /** Signals that the content type of the radius attribute is unknown. Only data is set. */
    IPD_RADIUS_TYPE_UNKNOWN,
    /** Signals that the content type of the radius attribute is a IP. The fields content.ip and data are set */
    IPD_RADIUS_TYPE_IP,
    /** Signals that the content type of the radius attribute is a String. The fields content.string and data are set */
    IPD_RADIUS_TYPE_TEXT,
    /** Signals that the content type of the radius attribute is a Integer. The fields content.integer and data are set */
    IPD_RADIUS_TYPE_INTEGER,
    /** Signals that the content type of the radius attribute is a IPv6-Prefix. The fields content.ipv6_prefix and data are set */
    IPD_RADIUS_TYPE_IPV6_PREFIX,
};

struct ipd_ipv6_prefix {
    /** the IPv6 content in network byte order*/
    struct in6_addr prefix;
    u8 prefix_length;
};

/** contains Information which are possibly send with a packet */
struct ipd_radius_attribute
{
    /** type of Attribute - enumerated in ipd_radius_attributes */
    u8 type;
    /** length of Attribute payload (length of attribute without the type and length) */
    u64 length;

    /** the type of the attribute content */
    enum ipd_radius_content_type content_type;
    union {
        /** the integer content (host byte order) */
        u32 integer;
        /** the string content */
        struct ipd_charset_string string;
        /** the IP content in network byte order */
        struct in_addr ip;
        /** the IPv6 prefix length and the IPv6 prefix content in network byte order */
        struct ipd_ipv6_prefix ipv6_prefix;
    } content;

    /** struct provide space for different options like Password or unknown content */
    struct ipd_charset_string data;
    /** struct contains the MD5 authenticator which is unique to a packet (so duplicates can be detected) */
    struct ipd_charset_string md5_authenticator;
};

enum ipd_simple_event_radius_enumeration
{
    /** Event throwing general information */
    IPD_EVENT_RADIUS_GENERAL_PACKET_INFORMATION,
    /** event throwing the attributes of an packet */
    IPD_EVENT_RADIUS_ATTRIBUTE,

    /** Number of events the Radius Decoder throws */
    IPD_NUMBER_OF_RADIUS_EVENTS,
};

#endif

