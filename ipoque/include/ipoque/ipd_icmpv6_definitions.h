/********************************************************************************/
/**
 ** \file       ipd_icmpv6_definitions.h
 ** \brief      Structures and enumerations for all events of the ICMPv6 Protocol.
 **/
/********************************************************************************/

#ifndef __IPOQUE_DECODER_ICMPV6_INCLUDE_FILE__
#define __IPOQUE_DECODER_ICMPV6_INCLUDE_FILE__

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif

/**
 * Structure describing an ICMPv6 router solicitation event.
 */
struct ipd_icmpv6_router_solicit
{
	/** \brief IPv6 source address (IPv6 header)
        \details Address of the sending interface, or the unspecified address (::) if no address is assigned
        to the sending interface */
    struct in6_addr source_address;

    /** \brief IPv6 destination address (IPv6 header)
        \details This is typically the all-routers multicast address (FF02::2) */
    struct in6_addr dest_address;

    /** \brief source link-layer address
        \details If the message did not contain a "source link-layer address" option this field is set to <tt>{ NULL, 0 }</tt> */
    struct ipd_string source_l2_address;
};

/**
 * Structure describing the prefix information option.
 */
struct ipd_ra_prefix_info {
    /** \brief prefix length
        \details The number of leading bits in the Prefix that are valid */
    u8 prefix_length;

    /** \brief on-link flag
        \details When set to 1, indicates that this prefix can be used for on-link determination. When set to
        0, the advertisement makes no statement about on-link or off-link properties of the prefix. */
    u8 onlink_flag;

    /** \brief autonomous address-configuration flag
        \details When set to 1, indicates that this prefix can be used for stateless address configuration (SLAAC). */
    u8 autoconf_flag;

    /** \brief valid lifetime
        \details The length of time in seconds (relative to the time the packet is sent) that the prefix is
        valid for the purpose of on-link determination.  A value of 0xffffffff represents infinity. */
    u32 valid_lifetime;

    /** \brief preferred lifetime
        \details The length of time in seconds (relative to the time the packet is sent) that addresses
        generated from the prefix via stateless address autoconfiguration remain preferred.  A value of
        0xffffffff represents infinity. */
    u32 preferred_lifetime;

    /** \brief an IP address or a prefix of an IP address.
        \details The #prefix_length field contains the number of valid leading bits in the prefix. */
    struct in6_addr prefix;
};

/**
 * Structure describing the rdnss option.
 */
struct ipd_rdnss_option {
    /** \brief number of addresses in #rdnss_addresses */
    u64 rdnss_address_count;
    /** \brief array of IPv6 addresses of recursive DNS servers */
    struct in6_addr *rdnss_addresses;
    /** \brief lifetime
        \details The maximum time, in seconds (relative to the time the packet is sent), over which this RDNSS
        address MAY be used for name resolution. */
    u32 rdnss_lifetime;
};

struct ipd_icmpv6_router_advert {
	/** \brief IPv6 source address (IPv6 header)
        \details This is the router's link-local address assigned to one of its interfaces. */
    struct in6_addr source_address;
    
    /** \brief IPv6 destination address (IPv6 header)
        \details This is typically the all-modes multicast address FF02::1. */
    struct in6_addr dest_address;

    /** \brief hop limit
        \details The default value that should be placed in the Hop Count field of the IP header for outgoing
        IP packets.  A value of zero means unspecified (by this router). */
    u8 cur_hop_limit;

    /** \brief managed address configuration flag
        \details When set, it indicates that addresses are available via Dynamic Host Configuration
        Protocol. If the M flag is set, the O flag is redundant and can be ignored because DHCPv6 will return
        all available configuration information. */
    u8 managed_addr_conf;

    /** \brief other configuration flag
        \details When set, it indicates that other configuration information is available via DHCPv6.
        Examples of such information are DNS-related information or information on other servers within the
        network. Note: If neither M nor O flags are set, this indicates that no information is available via
        DHCPv6. */
    u8 other_addr_conf;

    /** \brief router lifetime
        \details The lifetime associated with the default router in units of seconds. */
    u16 router_lifetime;

    /** \brief reachable time
        \details The time, in milliseconds, that a node assumes a neighbor is reachable after having received
        a reachability confirmation. */
    u32 reachable_time;

    /** \brief retrans timer
        \details The time, in milliseconds, between retransmitted Neighbor Solicitation messages. */
    u32 retrans_timer;

    /** \copydoc ipd_icmpv6_router_solicit::source_l2_address */
    struct ipd_string source_l2_address;

    /** \brief maximum transmission unit (MTU) for the network
        \details If the message did not contain an MTU option, this field is set to 0 */
    u32 mtu;

    /** \brief number of prefix options in #prefixes */
    u64 prefix_count;

    /** \brief array of prefix information options
        \details These options (each represented by a struct ipd_ra_prefix_info) specify the prefixes that are
        on-link and/or are used for stateless address autoconfiguration. */
    struct ipd_ra_prefix_info *prefixes;

    /** \brief number of RDNSS options in #rdnss_options */
    u64 rdnss_option_count;

    /** \brief array of Recursive DNS server (RDNSS) options
        \details Each RDNSS option (represented by a struct ipd_rdnss_option) contains one or more IPv6
        addresses of recursive DNS servers, along with a lifetime value. */
    struct ipd_rdnss_option *rdnss_options;
};

struct ipd_icmpv6_neighbor_solicit
{
	/** \brief IPv6 source address (IPv6 header)
        \details This is either an address assigned to the interface from which this message is sent or (if
        Duplicate Address Detection is in progress) the unspecified address (::) */
    struct in6_addr source_address;
    
    /** \brief IPv6 destination address (IPv6 header)
        \details This is either the solicited-node multicast address corresponding to the target address
        (FF02::1:FF<lower 24 bits of the target address>), or the target address. */
    struct in6_addr dest_address;

    /** \brief The IPv6 address of the target of the solicitation. */
    struct in6_addr target_address;

    /** \copydoc ipd_icmpv6_router_solicit::source_l2_address */
    struct ipd_string source_l2_address;
};

struct ipd_icmpv6_neighbor_advert
{
	/** \brief IPv6 source address (IPv6 header) */
    struct in6_addr source_address;
    /** \brief IPv6 destination address (IPv6 header)
        \details For solicited advertisements, the destination address is the source address of an invoking
        Neighbor Solicitation or, if the solicitation's source address is the unspecified address, the
        all-nodes multicast address.  For unsolicited advertisements typically the all-nodes multicast
        address. */
    struct in6_addr dest_address;

    /** \brief router flag
        \details When set to 1, it indicates that the sender is a router. */
    u8 router_flag;

    /** \brief solicited flag
        \details When set, the S-flag indicates that the advertisement was sent in response to a Neighbor
        Solicitation from the destination address. */
    u8 solicited_flag;

    /** \brief override flag
        \details When set, the O-flag indicates that the advertisement should override an existing cache entry
        and update the cached link-layer address. When it is not set the advertisement will not update a
        cached link-layer address though it will update an existing Neighbor Cache entry for which no
        link-layer address is known. */
    u8 override_flag;

    /** \brief target address
        \details For solicited advertisements, the Target Address field in the Neighbor Solicitation message
        that prompted this advertisement.  For an unsolicited advertisement, the address whose link-layer
        address has changed. */
    struct in6_addr target_address;

    /** \copydoc ipd_icmpv6_router_solicit::source_l2_address */
    struct ipd_string target_l2_address;
};

struct ipd_icmpv6_redirect
{
	/** \brief IPv6 source address (IPv6 header) */
    struct in6_addr source_address;
    /** \brief IPv6 destination address (IPv6 header)
        \details This is the source address of the packet that triggered the redirect message. */
    struct in6_addr dest_address;

    /** \brief target address
        \details The IPv6 address that is a better first hop to use. */
    struct in6_addr target_address;

    /** \brief redirected destination address
        \details The IPv6 address of the destination that has been redirected to the target address, ie. the
        destination address from the IPv6 header of the packet that triggered the redirect message. */
    struct in6_addr redirected_dest_address;

    /** \brief target link-layer address
        \details The link-layer address of the target address, the recommended next-hop router. If the "target
        link-layer address" option is not present this field is set to <tt>{ NULL, 0 }</tt> */
    struct ipd_string target_l2_address;

    /** \brief redirected header
        \details As much as possible of the IP packet that triggered the sending of the Redirect without
        making the redirect packet exceed the minimum MTU. If the "redirected header" option is not present
        this field is set to <tt>{ NULL, 0 }</tt>. */
    struct ipd_string redirected_header;
};


/**
 * Enumeration for simple ICMPv6 events. This is passed as \c type to the \ref ipd_decoder_event_callback.
 */
enum ipd_event_icmpv6_enum
{
    /** The event is issued when receiving an ICMPv6 Router Solicitation message; the payload type is struct ipd_icmpv6_router_solicit*/
    IPD_EVENT_ICMPV6_ROUTER_SOLICIT,
    /** The event is issued when receiving an ICMPv6 Router Advertisement message; the payload type is struct ipd_icmpv6_router_advert */
    IPD_EVENT_ICMPV6_ROUTER_ADVERT,
    /** The event is issued when receiving an ICMPv6 Neighbor Solicitation message; the payload type is struct ipd_icmpv6_neighbor_solicit */
    IPD_EVENT_ICMPV6_NEIGHBOR_SOLICIT,
    /** The event is issued when receiving an ICMPv6 Neighbor Advertisement message; the payload type struct ipd_icmpv6_neighbor_advert */
    IPD_EVENT_ICMPV6_NEIGHBOR_ADVERT,
    /** The event is issued when receiving an ICMPv6 Redirect message; the payload type struct ipd_icmpv6_redirect */
    IPD_EVENT_ICMPV6_REDIRECT,

    IPD_NUMBER_OF_ICMPV6_EVENTS
};

#endif                          /* __IPOQUE_DECODER_ICMPV6_INCLUDE_FILE__ */
