/* written by klaus degner, ipoque GmbH
 * klaus.degner@ipoque.com
 */
/* OSDPI-START */
#ifndef __IPOQUE_API_INCLUDE_FILE__
#error CANNOT INCLUDE THIS .H FILE, INCLUDE IPQ_API.H
#endif

#ifndef __IPQ_BASIC_DEF_H__
#define __IPQ_BASIC_DEF_H__

#ifdef __cplusplus
extern "C" {
#endif

/* define u64, u32, here
 * this is used for compatibility restrictions on different platforms
 *
 */

#ifndef IPOQUE_USE_OSDPI_ONLY

#ifndef IPOQUE_INTEGER_TYPEDEFS_DONE
#ifndef __KERNEL__
	typedef unsigned long long u64;
	typedef unsigned int u32;
	typedef unsigned short u16;
	typedef unsigned char u8;
#endif
#define IPOQUE_INTEGER_TYPEDEFS_DONE
#endif

/* WIN32 definitions and redefinitions
 * to enable compilation with the VisualC compiler
 */
#ifdef WIN32
	typedef u8 uint8_t;
	typedef u16 uint16_t;
	typedef u32 uint32_t;
	typedef u64 uint64_t;

#define inline __inline
#define __attribute__(arg)

#ifndef snprintf
#define snprintf sprintf_s
#endif
#endif							/* WIN32 */

#else							/* IPOQUE_USE_OSDPI_ONLY */
#ifndef u64
#define u64 	unsigned long long
#endif
#ifndef u32
#define u32 	unsigned int
#endif
#ifndef u16
#define u16 	unsigned short
#endif
#ifndef u8
#define u8 	unsigned char
#endif
#endif							/* IPOQUE_USE_OSDPI_ONLY */


/* generic timestamp counter size */
#define IPOQUE_TIMESTAMP_COUNTER_SIZE		u32
/* OSDPI-END */
/* http proxy detection before initial protocol handshake handling */
#define IPOQUE_IGNORE_PROXY_SETUP
	/* OSDPI-START */
#ifdef __cplusplus
}
#endif
#endif
/* OSDPI-END */
