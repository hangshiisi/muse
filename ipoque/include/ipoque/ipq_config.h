/* ipoque GmbH
 * info@ipoque.com
 */

#ifndef __IPOQUE_API_INCLUDE_FILE__
#error CANNOT INCLUDE THIS .H FILE, INCLUDE IPQ_API.H
#endif

#ifndef IPQ_CONFIG_H
#define IPQ_CONFIG_H

#undef IPOQUE_PACE_API_MK1
#undef IPOQUE_PACE_API_MK2
#define IPOQUE_PACE_API_MK3

/* if defined: add support for OS detection */
#define IPOQUE_SUPPORT_OS_DETECTION

/* if defined: build library that requires a license to work */
#define IPOQUE_ENABLE_LICENSING

/* if defined: build demo library */
#define IPOQUE_DEMO_VERSION

/* if defined: library for kernel space */
/* #undef PACE_KERNEL_LIB */


/* if defined: build PACE 2 with rtp performance measurement. */
#define IPOQUE_MEASURE_RTP_PERFORMANCE

#endif /* IPQ_CONFIG_H */
