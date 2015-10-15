
/*
 * linux-like definitions of network protocol header structures
 * and some ethernet payload types
 */

#ifndef __IPOQUE_LINUX_COMPAT_H__
#define __IPOQUE_LINUX_COMPAT_H__

#ifndef WIN32

#if defined(__APPLE__) || defined(__FreeBSD__)

#define __BYTE_ORDER BYTE_ORDER
#define __LITTLE_ENDIAN LITTLE_ENDIAN

#endif	/* APPLE */


#ifdef __SVR4	// Solaris

# include <sys/isa_defs.h> 
# define LITTLE_ENDIAN 1234
# define BIG_ENDIAN 4321

# ifdef _LITTLE_ENDIAN
#  define BYTE_ORDER LITTLE_ENDIAN
# else
#  define BYTE_ORDER BIG_ENDIAN
# endif

#define __BYTE_ORDER BYTE_ORDER
#define __LITTLE_ENDIAN LITTLE_ENDIAN

#endif /* SVR4 */


#define IP_MF 0x2000
#define IP_OFFMASK 0x1fff
#define IPPROTO_SCTP 132

struct iphdr {
#if BYTE_ORDER == LITTLE_ENDIAN
	u8 ihl:4, version:4;
#elif BYTE_ORDER == BIG_ENDIAN
	u8 version:4, ihl:4;
#else
# error "BYTE_ORDER must be defined"
#endif
	u8 tos;
	u16 tot_len;
	u16 id;
	u16 frag_off;
	u8 ttl;
	u8 protocol;
	u16 check;
	u32 saddr;
	u32 daddr;
};

#include <arpa/inet.h>
#if defined(__FreeBSD__)
#include <netinet/in.h>
#endif
#define s6_addr16		__u6_addr.__u6_addr16
#define s6_addr32		__u6_addr.__u6_addr32

struct ip6_hdr {
	union {
		struct ip6_hdrctl {
			uint32_t ip6_un1_flow;
			uint16_t ip6_un1_plen;
			uint8_t ip6_un1_nxt;
			uint8_t ip6_un1_hlim;
		} ip6_un1;
		uint8_t ip6_un2_vfc;
	} ip6_ctlun;
	struct in6_addr ip6_src;
	struct in6_addr ip6_dst;
};


struct tcphdr {
	u16 source;
	u16 dest;
	u32 seq;
	u32 ack_seq;
#if BYTE_ORDER == LITTLE_ENDIAN
	u16 res1:4, doff:4, fin:1, syn:1, rst:1, psh:1, ack:1, urg:1, ece:1, cwr:1;
#elif BYTE_ORDER == BIG_ENDIAN
	u16 doff:4, res1:4, cwr:1, ece:1, urg:1, ack:1, psh:1, rst:1, syn:1, fin:1;
#else
# error "BYTE_ORDER must be defined"
#endif
	u16 window;
	u16 check;
	u16 urg_ptr;
};


struct udphdr {
	u16 source;
	u16 dest;
	u16 len;
	u16 check;
};

#define ETH_P_8021Q	0x8100
#define ETH_P_IP	0x0800
#define ETH_P_IPV6	0x86DD
#define ETH_P_MPLS_UC   0x8847
#define ETH_P_PPP_SES	0x8864

#if defined(__APPLE__) || defined(__sun) || defined(__FreeBSD__)
#  if defined(__APPLE__) || defined(__FreeBSD__)
#    include <sys/types.h>
#    include <net/ethernet.h>
#  elif defined(__sun)
#    include <sys/ethernet.h>
#  endif
#define ETH_ALEN 6
struct ethhdr {
	unsigned char h_dest[ETH_ALEN];
	unsigned char h_source[ETH_ALEN];
	unsigned short h_proto;
} __attribute__((packed));
#endif

#endif
#ifdef WIN32
struct iphdr {
#if BYTE_ORDER == LITTLE_ENDIAN
      u8 ihl:4, version:4;
#elif BYTE_ORDER == BIG_ENDIAN
      u8 version:4, ihl:4;
#else
# error "BYTE_ORDER must be defined"
#endif
      u8 tos;
      u16 tot_len;
      u16 id;
      u16 frag_off;
      u8 ttl;
      u8 protocol;
      u16 check;
      u32 saddr;
      u32 daddr;
};


#ifdef __MINGW32__
struct in6_addr
{
	union
	{
		uint8_t	__u6_addr8[16];
	} __in6_u;
	#define s6_addr			__in6_u.__u6_addr8
};
#endif

struct ip6_hdr {
	union
	{
		struct ip6_hdrctl
		{
			uint32_t ip6_un1_flow;
			uint16_t ip6_un1_plen;
			uint8_t  ip6_un1_nxt;
			uint8_t  ip6_un1_hlim;
		} ip6_un1;
		uint8_t ip6_un2_vfc;
	} ip6_ctlun;
	struct in6_addr ip6_src;
	struct in6_addr ip6_dst;
};


struct tcphdr {
    u16 source;
    u16 dest;
    u32 seq;
    u32 ack_seq;
#if BYTE_ORDER == LITTLE_ENDIAN
    u16 res1:4, doff:4, fin:1, syn:1, rst:1, psh:1, ack:1, urg:1, ece:1, cwr:1;
#elif BYTE_ORDER == BIG_ENDIAN
    u16 doff:4, res1:4, cwr:1, ece:1, urg:1, ack:1, psh:1, rst:1, syn:1, fin:1;
#else
# error "BYTE_ORDER must be defined"
#endif  
    u16 window;
    u16 check;
    u16 urg_ptr;
};


struct udphdr {
    u16 source;
    u16 dest;
    u16 len;
    u16 check;
};


#define ETH_P_8021Q	0x8100
#define ETH_P_IP	0x0800
#define ETH_P_IPV6	0x86DD


/* define byteswap macros */

#if BYTE_ORDER == LITTLE_ENDIAN

#define ntohl(x) \
	((((x) & 0xff000000) >> 24) | (((x) & 0x00ff0000) >>  8) |	\
	(((x) & 0x0000ff00) <<  8) | (((x) & 0x000000ff) << 24))

#define htonl(x) \
	((((x) & 0xff000000) >> 24) | (((x) & 0x00ff0000) >>  8) |	\
	(((x) & 0x0000ff00) <<  8) | (((x) & 0x000000ff) << 24))

#define ntohs(x) \
	((((x) >> 8) & 0xff) | (((x) & 0xff) << 8))

#define htons(x) \
	((((x) >> 8) & 0xff) | (((x) & 0xff) << 8))

#elif BYTE_ORDER == BIG_ENDIAN

#define ntohl(x) (x)
#define htonl(x) (x)
#define ntohs(x) (x)
#define htons(x) (x)
	
#else
# error "BYTE_ORDER must be defined"
#endif

static int inet_aton(const char *cp, struct in_addr *inp)
{
	if ( cp == NULL || inp == NULL ) return 0;

	inp->s_addr = inet_addr( cp );

	if ( inp->s_addr == INADDR_NONE ) {
		return 0;
	}

	return 1;
}

#endif
#endif
