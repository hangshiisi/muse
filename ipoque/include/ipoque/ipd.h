/********************************************************************************/
/**
 ** \file       ipd.h
 ** \brief      main decoder include file.
 **/
/********************************************************************************/


#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#define __IPOQUE_DECODER_INCLUDE_FILE__
#ifdef __cplusplus
extern "C"
{
#endif

#ifdef WIN32
#include <WinSock2.h>
#include <in6addr.h>
#include <stdio.h>
#else /*WIN32*/

#include <netinet/in.h>

#if !defined(__APPLE__) && !defined(__FreeBSD__)
#include <netinet/ip.h>
#include <netinet/ip6.h>
#endif	/* not (APPLE || FreeBSD) */

#include <stdio.h>
#if defined(__APPLE__) || defined(__FreeBSD__)
// #include <byte_order.h> /* not needed */
#elif defined __sun
#include <sys/byteorder.h>

#ifdef _BIG_ENDIAN
#define bswap_8  BSWAP_8
#define bswap_16 BSWAP_16
#define bswap_32 BSWAP_32
#define bswap_64 BSWAP_64
#endif

#else /* !APPLE & !Solaris & !FreeBSD */
#include <byteswap.h>
#endif

#endif /*WIN32*/
// include PACE here
#include "ipq_api.h"

#define IPOQUE_DECODER_VERSION "15.09.25"
#define IPOQUE_DECODER_VERSION_NUMBER 1500090025

#include "ipd_custom_definitions.h"

#include "ipd_public_structures.h"

#include "ipd_charset.h"




/* protocol specific includes */
#include "ipd_http_definitions.h"
#include "ipd_imf_definitions.h"
#include "ipd_pop3_definitions.h"
#include "ipd_imap_definitions.h"
#include "ipd_smtp_definitions.h"
#include "ipd_irc_definitions.h"
#include "ipd_ftp_definitions.h"
#include "ipd_ftp_definitions_v2.h"
#include "ipd_telnet_definitions.h"
#include "ipd_jabber_definitions.h"
#include "ipd_sip_definitions.h"
#include "ipd_h323_definitions.h"
#include "ipd_socks_definitions.h"
#include "ipd_rtp_definitions.h"
#include "ipd_hi5_definitions.h"
#include "ipd_dns_definitions.h"
#include "ipd_dhcp_definitions.h"
#include "ipd_dhcp_definitions_v2.h"
#include "ipd_dhcpv6_definitions.h"
#include "ipd_radius_definitions.h"
#include "ipd_l2tp_definitions.h"
#include "ipd_pptp_definitions.h"
#include "ipd_icmpv6_definitions.h"
#include "ipd_wsp_definitions.h"
#include "ipd_diameter_definitions.h"
#include "ipd_gtp_definitions.h"
#include "ipd_mmse_definitions.h"
/* protocol class specific includes */
#include "ipd_class_generic_definitions.h"
#include "ipd_class_mail_definitions.h"
#include "ipd_class_http_definitions.h"
#include "ipd_class_http_definitions_v2.h"
#include "ipd_class_voip_definitions.h"




#ifdef __cplusplus
}
#endif
#endif                          /* __IPOQUE_API_INCLUDE_FILE__ */
