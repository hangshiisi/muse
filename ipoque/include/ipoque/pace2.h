/********************************************************************************/
/**
 ** \file       pace2.h
 ** \brief      PACE 2 general include file.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef IPOQUE_PACE2_H
#define IPOQUE_PACE2_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes *********************************************************************/
/* PACE specific includes */
#include <ipq_api.h>

#ifdef PACE_KERNEL_LIB
    #ifndef PACE2_DISABLE_DECODER
        #define PACE2_DISABLE_DECODER
    #endif
#else
    #include <ipd.h>
#endif

/* PACE2 Version defines */
#undef IPOQUE_PACE_VERSION
#undef IPOQUE_PACE_VERSION_NUMBER
#undef IPOQUE_PACE_API_VERSION
#undef IPOQUE_PACE_DYNAMIC_UPGRADE_COMPATIBLE_VERSION_NUMBER

#define IPOQUE_PACE_VERSION "15.09.25"
#define IPOQUE_PACE_VERSION_NUMBER 1500090025
#define IPOQUE_PACE_API_VERSION 7
#define IPOQUE_PACE_DYNAMIC_UPGRADE_COMPATIBLE_VERSION_NUMBER 1500060001

/* Generic PACE2 includes */
#include "pace2_basic_def.h"
#include "pace2_event_policy.h"
#include "pace2_config.h"
#include "pace2_classification_results.h"
#include "pace2_dynamic_upgrade.h"
#include "pace2_pa_tags.h"

/* Stage processing specific includes */
#include "pace2_s1_preparing.h"
#include "pace2_s2_reordering.h"
#include "pace2_s3_classification.h"
#include "pace2_s4_decoding.h"
#include "pace2_s5_timeout.h"

/* Event specific includes */
#include "pace2_event_types.h"
#include "pace2_status_csi.h"
#include "pace2_status_classification.h"
#include "pace2_status_dhcp.h"
#include "pace2_status_fastpath.h"
#include "pace2_status_rtcp.h"
#include "pace2_status_rtp.h"
#include "pace2_status_sit.h"
#include "pace2_status_tcp.h"

/* CPI specific includes */
#include "pace2_cpi_classification.h"

/* hash table specific include */
#include "pace2_pht.h"

#include "pace2_generic_func.h"
#include "pace2_debug.h"

#ifdef __cplusplus
}
#endif

#endif /* IPOQUE_PACE2_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
