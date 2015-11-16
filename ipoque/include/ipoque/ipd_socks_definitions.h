/********************************************************************************/
/**
 ** \file       ipd_socks_definitions.h
 ** \brief      Structures and enumerations for all events of the SOCKS protocol.
 **/
/********************************************************************************/

#ifndef __IPOQUE_DECODER_SOCKS_INCLUDE_FILE__
#define __IPOQUE_DECODER_SOCKS_INCLUDE_FILE__

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif

/**
 * SOCKS versions.
 */
enum ipd_socks_version_type {
    IPD_SOCKS_VERSION_4,
    IPD_SOCKS_VERSION_4A,
    IPD_SOCKS_VERSION_5,
};

/**
 * Address types.
 */
enum ipd_socks_address_type {
    IPD_SOCKS_ADDRESS_TYPE_IPv4,
    IPD_SOCKS_ADDRESS_TYPE_IPv6,
    IPD_SOCKS_ADDRESS_TYPE_DOMAIN,
};

/**
 * Types of SOCKS request messages.
 */
enum ipd_socks_request_message_type {
    IPD_SOCKS_REQUEST_MESSAGE_ESTABLISH_TCP_IP_STREAM_CONNECTION,
    IPD_SOCKS_REQUEST_MESSAGE_ESTABLISH_TCP_IP_PORT_BINDING,
    IPD_SOCKS_REQUEST_MESSAGE_ASSOCIATE_UDP_PORT,
};

/**
 * Types of SOCKS response messages.
 */
enum ipd_socks_response_message_type {
    IPD_SOCKS_RESPONSE_MESSAGE_REQUEST_GRANTED,
    IPD_SOCKS_RESPONSE_MESSAGE_REQUEST_REJECTED_OR_FAILED,
    IPD_SOCKS_RESPONSE_MESSAGE_REQUEST_FAILED_BECAUSE_CLIENT_IS_NOT_RUNNING_IDENTD_OR_NOT_REACHABLE,
    IPD_SOCKS_RESPONSE_MESSAGE_REQUEST_FAILED_BECAUSE_CLIENT_IDENTD_COULD_NOT_CONFIRM_USER_ID_STRING_IN_REQUEST,
    IPD_SOCKS_RESPONSE_MESSAGE_GENERAL_FAILURE,
    IPD_SOCKS_RESPONSE_MESSAGE_CONNECTION_NOT_ALLOWED_BY_RULESET,
    IPD_SOCKS_RESPONSE_MESSAGE_NETWORK_UNREACHABLE,
    IPD_SOCKS_RESPONSE_MESSAGE_HOST_UNREACHABLE,
    IPD_SOCKS_RESPONSE_MESSAGE_CONNECTION_REFUSED_BY_DESTINATION_HOST,
    IPD_SOCKS_RESPONSE_MESSAGE_TTL_EXPIRED,
    IPD_SOCKS_RESPONSE_MESSAGE_COMMAND_NOT_SUPPORTED_OR_PROTOCOL_ERROR,
    IPD_SOCKS_RESPONSE_MESSAGE_ADDRESS_TYPE_NOT_SUPPORTED,
};

/**
 * Types of SOCKS authentication mechanisms.
 */
enum ipd_socks_authentication_type {
    IPD_SOCKS_AUTHENTICATION_NO_AUTHENTICATION,
    IPD_SOCKS_AUTHENTICATION_GSSAPI,
    IPD_SOCKS_AUTHENTICATION_USERNAME_PASSWORD,
    IPD_SOCKS_AUTHENTICATION_METHOD_ASSIGNED_BY_IANA,
    IPD_SOCKS_AUTHENTICATION_METHOD_RESERVED_FOR_PRIVATE_USE,
};

/**
 * SOCKS v4 and v5 requests.
 */
struct ipd_socks_request {
    enum ipd_socks_version_type socks_version;          /**< SOCKS protocol version. */
    enum ipd_socks_request_message_type request_type;   /**< Type of the SOCKS request. */
    union {
        struct {
            u16 port;                                   /**< Port to which the user wants to connect. */
            struct in_addr ipv4_address;                /**< IPv4 address to which the user wants to connect.*/
            struct ipd_charset_string user_id;          /**< Id specified by the user connecting to the SOCKS proxy. */
        } v4;
        struct {
            u16 port;                                   /**< Port to which the user wants to connect. */
            struct ipd_charset_string user_id;          /**< Id specified by the user connecting to the SOCKS proxy. */
            struct ipd_charset_string domain_name;      /**< Domain name to which the user wants to connect. */
        } v4a;
        struct {
            u16 port;                                   /**< Port to which the user wants to connect. */
            enum ipd_socks_address_type address_type;   /**< Type of the address. */
            union {
                struct in_addr ipv4_address;            /**< IPv4 address to which the user wants to connect. */
                struct ipd_charset_string domain_name;  /**< Domain name to which the user wants to connect. */
                struct in6_addr ipv6_address;           /**< IPv6 address to which the user wants to connect. */
            } address;
        } v5;
    };
};

/**
 * SOCKS v4 and v5 responses.
 */
struct ipd_socks_response {
    enum ipd_socks_version_type socks_version;          /**< SOCKS protocol version. */
    enum ipd_socks_response_message_type response_type; /**< Type of the SOCKS response. */
    union {
        struct {
            u16 port;                                   /**< Bind port. */
            struct in_addr ipv4_address;                /**< Bind IPv4 address. */
        } v4a;
        struct {
            u16 port;                                   /**< Bind port. */
            enum ipd_socks_address_type address_type;   /**< Type of the address. */
            union {
                struct in_addr ipv4_address;            /**< Bind IPv4 address. */
                struct in6_addr ipv6_address;           /**< Bind IPv6 address. */
                struct ipd_charset_string domain_name;  /**< Bind domain name. */
            } address;
        } v5;
    };
};

/**
 * Thrown SOCKS v5 authentication method.
 */
struct ipd_socks_v5_authentication_method {
    enum ipd_socks_authentication_type authentication_method; /**< Authentication method. */
};

/**
 * SOCKS v5 user name authentication request.
 */
struct ipd_socks_v5_username_authentication_request {
    u8 request_version_number;          /**< Request version number. */
    struct ipd_charset_string username; /**< User name. */
    struct ipd_charset_string password; /**< Password. */
};

/**
 * SOCKS v5 user name authentication response.
 */
struct ipd_socks_v5_username_authentication_response {
    u8 response_version_number;                         /**< Response version number. */
    enum ipd_socks_response_message_type response_type; /**< Type of the SOCKS response. */
};

/**
 * Enumeration for simple SOCKS events. This is given by the \c type at \ref ipd_decoder_event_callback
 */
enum ipd_simple_event_socks_enumeration {

    /***********************************************
     * General events related to the SOCKS flow    *
     ***********************************************/

    /**
     * New SOCKS connection is observed.<br />
     * NULL.
     */
    IPD_EVENT_SOCKS_NEW_CONNECTION,

    /**
     * Decoding of a SOCKS connection fails.
     * const char * : message describing the failure reason.
     */
    IPD_EVENT_SOCKS_INVALID,

    /**
     * SOCKS connection ends.
     * NULL.
     */
    IPD_EVENT_SOCKS_END_OF_FLOW,


    /***********************************************************
     * Events related to various commands and responses        *
     ***********************************************************/

    /**
     * SOCKS v4, v4a, or v5 request.
     * struct ipd_socks_request * : client request.
     */
    IPD_EVENT_SOCKS_REQUEST,

    /**
     * SOCKS v4, v4a, or v5 response.
     * struct ipd_socks_response * : server response.
     */
    IPD_EVENT_SOCKS_RESPONSE,

    /**
     * Supported authentication method announced by client.
     * struct ipd_socks_v5_authentication_method * : supported authentication method.
     */
    IPD_EVENT_SOCKS_V5_CLIENT_ANNOUNCEMENT,

    /**
     * Authentication method selected by server.
     * struct ipd_socks_v5_authentication_method * : selected authentication method.
     */
    IPD_EVENT_SOCKS_V5_SERVER_ANNOUNCEMENT_RESPONSE,

    /**
     * SOCKS v5 username authentication request.
     * struct ipd_socks_v5_username_authentication_request * : client request.
     */
    IPD_EVENT_SOCKS_V5_USERNAME_AUTHENTICATION_REQUEST,

    /**
     * SOCKS v5 username authentication response.
     * struct ipd_socks_v5_username_authentication_response * : server response.
     */
    IPD_EVENT_SOCKS_V5_USERNAME_AUTHENTICATION_RESPONSE,


    /*********************************************************
     * A dummy event to signal the end of the event list     *
     *********************************************************/

    /**
     * A dummy event to signal the end of the event list.
     */
    IPD_NUMBER_OF_SOCKS_EVENTS,
};

#endif                          /* __IPOQUE_DECODER_SOCKS_INCLUDE_FILE__ */
