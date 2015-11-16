/* SPECIFIC COMPILE DIRECTIVES
 * if IPOQUE_CUST1 is defined,
 *    this module will compile this module for customer 1 only
 * if IPOQUE_USE_PRX_PROTOCOLS_ONLY is defined, this module will compile PRX detections only
 * with no definitions, this will be compiled for all protocols (also all beta/testing modules)
 */

#ifndef __IPOQUE_API_INCLUDE_FILE__
#define __IPOQUE_API_INCLUDE_FILE__
#ifdef __cplusplus
extern "C" {
#endif

#define IPOQUE_PACE_VERSION "15.09.25"
#define IPOQUE_PACE_VERSION_NUMBER 1500090025

	/**
	 * API version number
	 *
	 * the version is increased whenever the API changes, it may or
	 * may not be binary compatible if the number changes
	 */
#define IPOQUE_PACE_API_VERSION 47

    /*
     * special compilation flag:
     * IPOQUE_FIXED_DETECTION_PROTOCOL
     * IPOQUE_CUSTOM_PACE_VERSION
     * IPOQUE_CUSTOM_PACE_VERSION_NUMBER
     */

#ifdef IPOQUE_CUSTOM_PACE_VERSION
#  undef IPOQUE_PACE_VERSION
#  undef IPOQUE_PACE_VERSION_NUMBER
#  define IPOQUE_PACE_VERSION IPOQUE_CUSTOM_PACE_VERSION
#  define IPOQUE_PACE_VERSION_NUMBER IPOQUE_CUSTOM_PACE_VERSION_NUMBER
#endif

/* basic definitions (u64, u32, timestamp size,...) */
#include "ipq_basic_def.h"

/* protocol definitions for customers who need a subset of protocols only */
#if defined( IPOQUE_CUST1 )
#  include "ipq_protocols_cust1.h"
#elif defined( IPOQUE_USE_CUST2_PROTOCOLS_ONLY )
#  include "ipq_protocols_cust2.h"
#elif defined( IPOQUE_USE_PRX_PROTOCOLS_ONLY )

#  ifdef IPOQUE_PRX_USE_PACE_DYNAMIC_UPGRADE
#    define IPOQUE_PACE_API_MK2     /* use Mk2 if DU is enabled for PRX */
#  else
#    define IPOQUE_PACE_API_MK1     /* uses Mk1 if PRX is build without DU (default) */
#  endif
#  include "ipq_protocols_prx.h"

#elif defined( IPOQUE_USE_CUST3_PROTOCOLS_ONLY )
#  include "ipq_protocols_cust3.h"
#elif defined( IPOQUE_USE_CUST4_PROTOCOLS_ONLY )
#  include "ipq_protocols_cust4.h"
#else
#  include "ipq_protocols_default.h"
#endif

#ifdef IPOQUE_PACE_API_MK1
#  define IPOQUE_PACE_API_VARIANT 1
#elif defined(IPOQUE_PACE_API_MK2)
#  define IPOQUE_PACE_API_VARIANT 2
#elif defined(IPOQUE_PACE_API_MK3)
#  define IPOQUE_PACE_API_VARIANT 3
#else
#  error "API variant not defined"
#endif

    /* this number indicates that the current library must not be loaded
     * by a PACE version older than this number */
#define IPOQUE_PACE_DYNAMIC_UPGRADE_COMPATIBLE_VERSION_NUMBER 100520003

#include "ipq_protocol_subtypes.h"

#include "ipq_protocol_groups.h"

#include "ipq_applications.h"

/* macros for protocol / bitmask conversation if needed */
#include "ipq_macros.h"

/* this include file is deprecated with using the library with > 64 protocols */
#include "ipq_bitmask_definitions.h"

#include "ipq_wrapper.h"

#include "ipq_public_functions.h"



#include "ipq_timeorderedhash.h"

#include "ipq_paro.h"



#include "ipq_metadata_public.h"









//#ifdef IPOQUE_USER_DEFINED_PROTOCOLS
#include "ipq_user_defined_protocols.h"
//#endif                                /* IPOQUE_USER_DEFINED_PROTOCOLS */



#ifdef __cplusplus
}
#endif
#endif							/* __IPOQUE_API_INCLUDE_FILE__ */
