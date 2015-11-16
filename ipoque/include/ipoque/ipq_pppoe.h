/* all rights by ipoque */

#ifndef __IPQ_PPPOE_H__
#define __IPQ_PPPOE_H__

#ifndef __IPOQUE_API_INCLUDE_FILE__
#   define __IPOQUE_API_INCLUDE_FILE__
#   include "ipq_basic_def.h"
#   undef __IPOQUE_API_INCLUDE_FILE__
#endif

#ifdef __GNUC__
#   define ALWAYS_INLINE __attribute__ ((always_inline))
#else
#   define ALWAYS_INLINE
#endif

typedef enum {
    PPPOE_CONTROL_EVENT = 1,
    PPPOE_DATA_EVENT = 2,
} ipoque_pppoe_event_type_t;

typedef enum {
    PPPOE_NOT_FOUND = 0,
    PPPOE_FOUND,
    PPPOE_ERROR,
} ipoque_pppoe_result_t;

typedef struct {
    ipoque_pppoe_event_type_t type; /* event type, either PPPOE_CONTROL_EVENT or PPPOE_DATA_EVENT */
    u16 session_id;                 /* pppoe session id in network byte order */
    const void *payload_data;       /* pointer to inner payload (may be NULL for discovery stage) */
    u16 payload_length;             /* length of inner payload */
    u16 payload_type;               /* PPP DDL type (can be ip,ipv6,mpls,lcp) */
} PPPoEEvent;

/**
 * Skips VLAN and MPLS headers by adjusting the given pointers
 * to the following payload data.
 * @param data pointer to the current payload pointer, NOT NULL
 * @param data_length pointer to the payload length, NOT NULL
 * @param decaps_level maximum amount of vlan headers/mpls labels to skip
 * @param ether_type pointer to the current ethertype, NOT NULL
 */

static void ipoque_int_skip_vlan_and_mpls(const u8 ** const data,
                                          u16 * const data_length_ptr,
                                          u16 * const ether_type_ptr,
                                          const u32 decaps_level);

/**
 * Fills the given event structure with PPPoE information of the given packet.
 * The event structure will only be valid when PPPOE_FOUND is returned and should
 * not be used otherwise.
 *
 * @param l2_data pointer to the l2 payload, NOT NULL
 * @param l2_data_length length of the l2 payload
 * @param return_info pointer to the PPPoEEvent structure to be filled, NOT NULL
 * @param decaps_level maximum amount of vlan headers/mpls labels to skip
 * @return PPPOE_NOT_FOUND - packet is not PPPOE
 *         PPPOE_FOUND     - PPPOE packet, the event structure has been filled
 *         PPPOE_ERROR     - PPPOE packet with unexpected content/structure
 */

ALWAYS_INLINE static inline ipoque_pppoe_result_t ipoque_pace_handle_pppoe_frame(const void * const l2_data,
                                                                                 u16 l2_data_length,
                                                                                 u16 l2_ether_type,
                                                                                 PPPoEEvent * const return_info,
                                                                                 const u32 decaps_level);

/**
 * Sets the given pointers to the IP header of the PPPoE packet.
 *
 * @param pppoe_event pointer to a PPPoEEvent structure previously initialized with ipoque_pace_handle_pppoe_frame, NOT NULL
 * @param return_l3_data pointer to the payload pointer that will be set, NOT NULL
 * @param return_l3_length pointer to the payload length to be set, NOT NULL
 * @param return_is_ipv6 pointer to ip type return variable, NOT NULL
 * @param decaps_level maximum amount of vlan headers/mpls labels to skip
 * @return 0 - no IP found, pointers are unchanged.
 *         1 - IP found, pointers were modified.
 */

ALWAYS_INLINE static inline int ipoque_pace_get_pppoe_ip_header(const PPPoEEvent * const pppoe_event,
                                                                const void ** const return_l3_data,
                                                                u16 * const return_l3_length,
                                                                u8 * const return_is_ipv6,
                                                                const u32 decaps_level);

#include "ipq_pppoe_int.h"

#endif
