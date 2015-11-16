/********************************************************************************/
/**
 ** \file       ipd_dns_definitions.h
 ** \brief      Event definitions for the DNS Protocol.
 **/
/********************************************************************************/

#ifndef __IPOQUE_DECODER_DNS_INCLUDE_FILE__
#define __IPOQUE_DECODER_DNS_INCLUDE_FILE__

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif


/** Enumeration for DNS answer types.
 */
enum ipd_dns_answer_type_enum
{
    /** A host address. */
    IPD_DNS_RESOURCE_RECORD_TYPE_A     =  1,    
    /** An authoritative name server. */
    IPD_DNS_RESOURCE_RECORD_TYPE_NS    =  2,    
    /** The canonical name for an alias. */
    IPD_DNS_RESOURCE_RECORD_TYPE_CNAME =  5,    
    /** Marks the start of a zone of authority. */
    IPD_DNS_RESOURCE_RECORD_TYPE_SOA   =  6,    
    /** A well known service description. */ 
    IPD_DNS_RESOURCE_RECORD_TYPE_WKS   = 11,    
    /** A domain name pointer. */
    IPD_DNS_RESOURCE_RECORD_TYPE_PTR   = 12,    
    /** Host information. */ 
    IPD_DNS_RESOURCE_RECORD_TYPE_HINFO = 13,    
    /** Mailbox or mail list information. */
    IPD_DNS_RESOURCE_RECORD_TYPE_MINFO = 14,    
    /** Mail exchange. */
    IPD_DNS_RESOURCE_RECORD_TYPE_MX    = 15,    
    /** Text string. */
    IPD_DNS_RESOURCE_RECORD_TYPE_TXT   = 16,    
    /** IPv6. */
    IPD_DNS_RESOURCE_RECORD_TYPE_AAAA  = 28,    
};

enum ipd_dns_response_code {
    IPD_DNS_RESPONSE_CODE_NO_ERROR = 0,
    IPD_DNS_RESPONSE_CODE_FORMAT_ERROR = 1,
    IPD_DNS_RESPONSE_CODE_SERVER_FAILURE = 2,
    IPD_DNS_RESPONSE_CODE_NON_EXISTENT_DOMAIN = 3,
    IPD_DNS_RESPONSE_CODE_NOT_IMPLEMENTED = 4,
    IPD_DNS_RESPONSE_CODE_QUERY_REFUSED = 5,
    IPD_DNS_RESPONSE_CODE_NAME_EXISTS_WHEN_IT_SHOULD_NOT = 6,
    IPD_DNS_RESPONSE_CODE_RR_SET_EXISTS_WHEN_IT_SHOULD_NOT = 7,
    IPD_DNS_RESPONSE_CODE_RR_SET_THAT_SHOULD_EXISTS_DOES_NOT = 8,
    IPD_DNS_RESPONSE_CODE_NOT_AUTHORIZED = 9,
    IPD_DNS_RESPONSE_CODE_NAME_NOT_CONTAINED_IN_ZONE = 10,
};

/** This structure provides information for DNS query events. */
struct ipd_dns_query
{
	/** The transaction ID of the query. */
	u16 transaction_id;
	/** The type field of the query, e.g. 1 (A) for IPv4 address query. */
	u16 type;
	/** The class field of the query, always 1 (IN) for internet. */
	u16 qclass;
	/** The flag field of the dns query/response */
	u16 flag;
	/** The reply code of the response. Only set if it is a response. */
	enum ipd_dns_response_code rcode;
	/** The queried domain name. */
	struct ipd_charset_string name;
};

/** This structure provides information for DNS IPv4 answer events. */
struct ipd_dns_answer_ipv4
{
	/** The transaction ID of the IPv4 answer. */
	u16 transaction_id;
	/** The type field of the resource record, always 1 (A). */
	u16 type;
	/** The class field of the resource record, always 1 (IN) for internet. */
	u16 rr_class;
	/** The time to live of the IPv4 answer. */
	u32 ttl;
	/** The IPv4 address of the IPv4 answer. */
	u32 ipv4_address;
	/** The domain name of the IPv4 answer. */
	struct ipd_charset_string name;
};

/** This structure provides information for DNS IPv6 answer events. */
struct ipd_dns_answer_ipv6
{
	/** The transaction ID of the IPv6 answer. */
	u16 transaction_id;
	/** The type field of the resource record, always 28 (AAAA). */
	u16 type;
	/** The class field of the resource record, always 1 (IN) for internet. */
	u16 rr_class;
	/** The time to live of the IPv6 answer. */
	u32 ttl;
	/** The IPv6 address of the IPv6 answer. */
	struct in6_addr ipv6_address;
	/** The domain name of the IPv6 answer. */
	struct ipd_charset_string name;
};

/** This structure provides information for DNS canonical name answer events. */
struct ipd_dns_answer_canonical_name
{
	/** The transaction ID of the canonical name answer. */
	u16 transaction_id;
	/** The type field of the resource record, always 5 (CNAME). */
	u16 type;
	/** The class field of the resource record, always 1 (IN) for internet. */
	u16 rr_class;
	/** The time to live of the canonical name answer. */
	u32 ttl;
	/** The domain name of the canonical name answer. */
	struct ipd_charset_string name;
	/** The canonical name of the canonical name answer. */
	struct ipd_charset_string canonical_name;
};

/** This structure provides information for DNS mail exchange answer events. */
struct ipd_dns_answer_mail_exchange
{
	/** The transaction ID of the mail exchange answer. */
	u16 transaction_id;
	/** The type field of the resource record, always 15 (MX). */
	u16 type;
	/** The class field of the resource record, always 1 (IN) for internet. */
	u16 rr_class;
	/** The preference of the mail exchange answer. */
	u16 preference;
	/** The time to live of the mail exchange answer. */
	u32 ttl;
	/** The domain name of the mail exchange answer. */
	struct ipd_charset_string name;
	/** The mail exchange name of the mail exchange answer. */
	struct ipd_charset_string mail_exchange_name;
};

/** This structure provides information for not implemented / other answer events. */
struct ipd_dns_answer_other
{
	/** The transaction ID of a unimplemented answer. */
	u16 transaction_id;
	/** The type field of the resource record, refer to IANA's
     * <a href="http://www.iana.org/assignments/dns-parameters">DNS TYPE registry</a>
     * for a current list of resource record types. */
	u16 type;
    /** The class field of the resource record, always 1 (IN) for internet. */
	u16 rr_class;
	/** The time to live of the unimplemented answer. */
	u32 ttl;
	/** The domain name of the unimplemented answer. */
	struct ipd_charset_string name;
	/** The generic data of the unimplemented answer. */
	struct ipd_charset_string generic_data;
};


/** Enumeration for simple DNS events.
 */
enum ipd_simple_event_dns_enumeration
{
	/** Provides a struct ipd_dns_query * with the transaction id, name, type and class of a query.  */
    IPD_EVENT_DNS_QUERY,
    /** Provides a struct ipd_dns_query * with the transacrion id, name, type and class of a query from a server response packet. */
    IPD_EVENT_DNS_QUERY_RESPONSE,
    /** Provides a struct ipd_dns_answer_ipv4 * with the transaction id, name, type, class, time to live and IPv4 address of an IPv4 answer.  */
    IPD_EVENT_DNS_ANSWER_IPV4,
    /** Provides a struct ipd_dns_answer_ipv6 * with the transaction id, name, type, class, time to live and IPv6 address of an IPv6 answer.  */
    IPD_EVENT_DNS_ANSWER_IPV6,
    /** Provides a struct ipd_dns_answer_canonical_name * with the transaction id, name, type, class, time to live and canonical name of a canonical name answer.  */
    IPD_EVENT_DNS_ANSWER_CANONICAL_NAME,
    /** Provides a struct ipd_dns_answer_mail_exchange * with the transaction id, name, type, class, time to live, preference and mail exchange name of a mail exchange answer.  */
    IPD_EVENT_DNS_ANSWER_MAIL_EXCHANGE,
    /** Provides a struct ipd_dns_answer_other * with the transaction id, name, type, class, time to live and generic data of an unimplemented answer.  */
    IPD_EVENT_DNS_ANSWER_OTHER,
    /** This event is issued when decoding of an TCP DNS connection fails. It provides a const char * to a message describing the failure reason. */
    IPD_EVENT_DNS_INVALID,

    IPD_NUMBER_OF_DNS_EVENTS,
};

#endif                          /* __IPOQUE_DECODER_DNS_INCLUDE_FILE__ */

