/********************************************************************************/
/**
 ** \file       ipd_dhcpv6_definitions.h
 ** \brief      Event definitions for the Dynamic Host Configuration Protocol for IPv6
 **/
/********************************************************************************/

#ifndef IPD_DHCPV6_DEFINITIONS_H_
#define IPD_DHCPV6_DEFINITIONS_H_

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif

/** \brief Enumeration of the DHCPv6 decoder event types
    \details These are the possible values of the `type` argument of an \ref ipd_decoder_event_callback
    function when the `protocol` is `IPOQUE_PROTOCOL_DHCPV6`.
*/
enum ipd_dhcpv6_event_type
{
    IPD_EVENT_DHCPV6_MESSAGE,
    IPD_NUMBER_OF_DHCPV6_EVENTS
};


/** \anchor dhcpv6_msg_types
    \name DHCPv6 message type values
    As listed in <a href="http://tools.ietf.org/html/rfc3315#section-5.3">RFC 3315, section 5.3</a>
    \see ipd_dhcpv6_message::msg_type
    @{
*/

#define IPD_DHCPV6_MSG_SOLICIT 1
#define IPD_DHCPV6_MSG_ADVERTISE 2
#define IPD_DHCPV6_MSG_REQUEST 3
#define IPD_DHCPV6_MSG_CONFIRM 4
#define IPD_DHCPV6_MSG_RENEW 5
#define IPD_DHCPV6_MSG_REBIND 6
#define IPD_DHCPV6_MSG_REPLY 7
#define IPD_DHCPV6_MSG_RELEASE 8
#define IPD_DHCPV6_MSG_DECLINE 9
#define IPD_DHCPV6_MSG_RECONFIGURE 10
#define IPD_DHCPV6_MSG_INFORMATION_REQUEST 11
#define IPD_DHCPV6_MSG_RELAY_FORW 12
#define IPD_DHCPV6_MSG_RELAY_REPL 13
/** @} */


/** \anchor dhcpv6_status_codes
    \name DHCPv6 status codes
    As listed in <a href="http://tools.ietf.org/html/rfc3315#section-24.4">RFC 3315, section 24.4</a>
    \see ipd_dhcpv6_status::status_code
    @{
*/
#define IPD_DHCPV6_STATUS_SUCCESS 0
#define IPD_DHCPV6_STATUS_UNSPEC_FAIL 1
#define IPD_DHCPV6_STATUS_NO_ADDRS_AVAIL 2
#define IPD_DHCPV6_STATUS_NO_BINDING 3
#define IPD_DHCPV6_STATUS_NOT_ON_LINK 4
#define IPD_DHCPV6_STATUS_USE_MULTICAST 5
/** @} */


/** \brief representation of a Status Code option
    \details If no Status Code option is present, #status_code is set to IPD_DHCPV6_STATUS_SUCCESS, and
    #status_message is set to <tt>{ { NULL, 0 }, CHARSET_STRING_CHARSET_UNKNOWN }</tt>.
*/
struct ipd_dhcpv6_status {
    /** \brief status code
        \details The status-code field of the option; the values defined in RFC 3315 are available as
        \ref dhcpv6_status_codes "preprocessor defines"
    */
    u8 status_code;

    /** \brief message
        \details The status-message field of the option, a UTF-8 encoded text string
    */
    struct ipd_charset_string status_message;
};


/** \brief representation of an IA Address option */
struct ipd_dhcpv6_address {
    struct in6_addr address;    /**< \brief an IPv6 address */
    u32 preferred_lifetime;     /**< \brief the preferred lifetime (in seconds) for the address */
    u32 valid_lifetime;         /**< \brief the valid lifetime (in seconds) for the address */

    /** \brief status indication
        \details contents of the Status Code option contained within the IA Address option
    */
    struct ipd_dhcpv6_status status;
};

/** \brief identity association types */
enum ipd_dhcpv6_ia_type {
    IPD_DHCPV6_IA_NA,           /**< \brief Identity association for non-temporary addresses (IA_NA option) */
    IPD_DHCPV6_IA_TA,            /**< \brief Identity association for temporary addresses (IA_TA option) */
};

/** \brief representation of an Identity Association (IA_NA or IA_TA) option
*/
struct ipd_dhcpv6_identity_assoc {
    
    u32 ia_id;                  /**< \brief the unique identifier for this IA */
    enum ipd_dhcpv6_ia_type ia_type; /**< \brief kind of identity association (for non-temporary or for temporary addresses) */

    /** \brief T1 parameter (IA_NA only)
        \details time at which the client sends a Renew message to the server originating this IA_NA (in
        seconds, relative to current time); 0 lets the client choose a time, 0xffffffff stands for "never"
    */
    u32 t1;

    /** \brief T2 parameter (IA_NA only)
        \details time at which the client sends a Rebind message to any available server (in seconds, relative
        to current time); 0 lets the client choose a time, 0xffffffff stands for "never"
    */
    u32 t2;

    /** \brief pointer to an array containing the IA Address options */
    const struct ipd_dhcpv6_address *addresses;
    /** \brief number of elements in #addresses */
    u64 number_of_addresses;

    /** \brief status indiction
        \details contents of the Status Code option contained within the IA_NA option
    */
    struct ipd_dhcpv6_status status;
};

/** \brief representation of an DHCPv6 message
*/
struct ipd_dhcpv6_message {
    /* common header */

    /** \brief message type
        \details msg-type field of the DHCPv6 message; the values defined in RFC 3315 are available as
        \ref dhcpv6_msg_types "preprocessor defines"
    */
    u8 msg_type;

    /** \brief transaction ID */
    u32 transaction_id;

    /** \brief the DHCP unique identifier (DUID) of the client
        \details empty if the message contains no Client Identifier option
    */
    struct ipd_string client_identifier;

    /** \brief the link-layer address of the client
        \details extracted from the client DUID (types DUID-LLT oder DUID-LL); empty if the client identifier
        is not present or of an other type
    */
    struct ipd_string client_l2_address;

    /** \brief the DHCP unique identifier (DUID) of the server
        \details empty if the message contains no Server Identifier option
    */
    struct ipd_string server_identifier;

    /** \brief the link-layer address of the server
        \details extracted from the server DUID (types DUID-LLT oder DUID-LL); empty if the server identifier
        is not present or of an other type
    */
    struct ipd_string server_l2_address;

    /** \brief status indication
        \details contents of the message-level Status Code option
    */
    struct ipd_dhcpv6_status status;

    /** \brief rapid commit flag
        \details set to 1 if the message contains a Rapid Commit option, 0 otherwise */
    u8 rapid_commit;

    /** \brief pointer to an array containing the Identity Association options */
    const struct ipd_dhcpv6_identity_assoc *ia_options;
    /** \brief number of elements in #ia_options */
    u64 number_of_ia_options;
};

#endif /* IPD_DHCPV6_DEFINITIONS_H_ */
