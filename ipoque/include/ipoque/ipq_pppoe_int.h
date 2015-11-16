/* all rights by ipoque */

#ifndef __IPQ_PPPOE_INT_H__
#define __IPQ_PPPOE_INT_H__

#ifndef __IPQ_PPPOE_H__
    #error "Please include ipq_pppoe.h."
#endif

#define IPOQUE_PPPOE_IPV4       0x0021
#define IPOQUE_PPPOE_IPV6       0x0057
#define IPOQUE_PPPOE_MPLS_U     0x0281
#define IPOQUE_PPPOE_MPLS_M     0x0283

#define IPOQUE_ETH_P_8021Q      0x8100
#define IPOQUE_ETH_P_IP         0x0800
#define IPOQUE_ETH_P_IPV6       0x86DD
#define IPOQUE_ETH_P_MPLS_UC    0x8847
#define IPOQUE_ETH_P_MPLS_MC    0x8848
#define IPOQUE_ETH_P_PPP_DISC   0x8863
#define IPOQUE_ETH_P_PPP_SES    0x8864

#define IPOQUE_ETH_HEADER_SIZE  14
#define IPOQUE_IPV4_HEADER_SIZE 20
#define IPOQUE_IPV6_HEADER_SIZE 40

#include <stddef.h>

#ifdef __linux__
#   include <endian.h>
#endif

/* byte order specific */
#ifdef __APPLE__

#   define __BYTE_ORDER BYTE_ORDER
#   define __LITTLE_ENDIAN LITTLE_ENDIAN

#endif	/* __APPLE__ */

#ifdef __SVR4	/* Solaris */

#   include <sys/isa_defs.h> 
#   define LITTLE_ENDIAN 1234
#   define BIG_ENDIAN 4321

#   ifdef _LITTLE_ENDIAN
#       define BYTE_ORDER LITTLE_ENDIAN
#   else
#       define BYTE_ORDER BIG_ENDIAN
#   endif

#   define __BYTE_ORDER BYTE_ORDER
#   define __LITTLE_ENDIAN LITTLE_ENDIAN

#endif /* __SVR4 */

#if BYTE_ORDER == LITTLE_ENDIAN
#   define ipoque_int_ntohs(x) ((((x) >> 8) & 0xff) | (((x) & 0xff) << 8))
#   define ipoque_int_htons(x) (ipoque_int_ntohs((x)))
#elif BYTE_ORDER == BIG_ENDIAN
#   define ipoque_int_ntohs(x) (x)
#   define ipoque_int_htons(x) (x)
#else
#   error "BYTE_ORDER must be defined"
#endif

#define ipoque_int_get_u16(X,O)  (*(u16 *)(((u8 *)X) + O))

static void ipoque_int_skip_vlan_and_mpls(const u8 ** const data,
                                           u16 * const data_length_ptr,
                                           u16 * const ether_type_ptr,
                                           const u32 decaps_level)
{
    u8 tag_found;
    u32 decaps_count = 0;
    u16 data_length = *data_length_ptr;
    u16 ether_type = *ether_type_ptr;

    if (decaps_level == 0) { return; }

    do {
        tag_found = 0;
        
        if (ether_type == ipoque_int_htons(IPOQUE_ETH_P_8021Q)) {
            /* vlan */

            if (data_length < 5) {
                *ether_type_ptr = 0;
                *data_length_ptr = data_length;
                return;
            }

            ether_type = ipoque_int_get_u16(*data, 2);
            *data = *data + 4;
            data_length -= 4;

            decaps_count++;
            tag_found = 1;
        } else if (ether_type == ipoque_int_htons(IPOQUE_ETH_P_MPLS_UC)) {
            /* mpls */

            if (data_length < 5) {
                *ether_type_ptr = 0;
                *data_length_ptr = data_length;
                return;
            }

            /* skip labels */
            while (data_length > 4) {
                const u8 last_label = ((*data)[2] & 1);

                *data = *data + 4;
                data_length -= 4;

                decaps_count++;

                if (last_label) {
                    break;
                } else if (decaps_count >= decaps_level) {
                    *ether_type_ptr = 0;
                    *data_length_ptr = data_length;
                    return;
                }
            }

            /* check for IP */
            if(data_length >= IPOQUE_IPV4_HEADER_SIZE) {
                const u8 ip_version = (*data)[0] >> 4;

                if (ip_version == 4) {
                    if (ipoque_int_ntohs(ipoque_int_get_u16(*data, 2)) <= data_length) {
                        /* looks like an IPv4 header */
                        *ether_type_ptr = ipoque_int_htons(IPOQUE_ETH_P_IP);
                        *data_length_ptr = data_length;
                        return;
                    }
                } else if (ip_version == 6 && data_length >= IPOQUE_IPV6_HEADER_SIZE) {
                    if ((u32)ipoque_int_ntohs(ipoque_int_get_u16(*data, 4)) + IPOQUE_IPV6_HEADER_SIZE <= data_length) {
                        /* looks like an IPv6 header */
                        *ether_type_ptr = ipoque_int_htons(IPOQUE_ETH_P_IPV6);
                        *data_length_ptr = data_length;
                        return;
                    }
                }
            }

            /* no IP found, assume ethernet */
            if (data_length >= IPOQUE_ETH_HEADER_SIZE) {
                ether_type = ipoque_int_get_u16(*data, IPOQUE_ETH_HEADER_SIZE - 2);
                *data += IPOQUE_ETH_HEADER_SIZE;
                data_length -= IPOQUE_ETH_HEADER_SIZE;
            } else {
                /* unknown payload */
                *ether_type_ptr = 0;
                *data_length_ptr = data_length;
                return;
            }

            tag_found = 1;
        }
    } while (tag_found == 1 && decaps_count < decaps_level);

    *ether_type_ptr = ether_type;
    *data_length_ptr = data_length;
}

ALWAYS_INLINE static inline ipoque_pppoe_result_t ipoque_pace_handle_pppoe_frame(const void * const l2_data,
                                                                                 u16 l2_data_length,
                                                                                 u16 l2_ether_type,
                                                                                 PPPoEEvent * const return_info,
                                                                                 const u32 decaps_level)
{
    const u8 * data = (u8 *)l2_data;

    ipoque_int_skip_vlan_and_mpls(&data, &l2_data_length, &l2_ether_type, decaps_level);

    if (l2_ether_type == ipoque_int_htons(IPOQUE_ETH_P_PPP_SES)) {
        /* PPPoE Session */
        if (l2_data_length > 8 &&
            data[0] == 0x11 &&
            data[1] == 0x00 /* Session code */) {

            const u16 pppoe_payload_len = ipoque_int_ntohs(ipoque_int_get_u16(data, 4));

            if (pppoe_payload_len < 3 /* protocol and atleast one data byte */ ||
                pppoe_payload_len > l2_data_length - 6 ||
                (data[7] & 1) == 0 /* low byte of payload type must be odd */) {

                return PPPOE_ERROR;
            }

            return_info->session_id = ipoque_int_get_u16(data, 2);
            return_info->payload_type = ipoque_int_get_u16(data, 6);
            return_info->payload_length = pppoe_payload_len - 2;
            return_info->payload_data = &data[8];

            /* check the high byte of the payload type, 0x80 and up are control protocols */
            if (data[6] >= 0x80) {
                return_info->type = PPPOE_CONTROL_EVENT;
            } else {
                return_info->type = PPPOE_DATA_EVENT;
            }

            return PPPOE_FOUND;
        }

        return PPPOE_ERROR;
    } else if (l2_ether_type == ipoque_int_htons(IPOQUE_ETH_P_PPP_DISC)) {
        /* PPPoE Discovery */
        if (l2_data_length >= 8 &&
            data[0] == 0x11 &&
            (data[1] == 0x07 /* PADO */ ||
             data[1] == 0x09 /* PADI */ ||
             data[1] == 0x19 /* PADR */ ||
             data[1] == 0x65 /* PADS */ ||
             data[1] == 0xa7 /* PADT */ )) {

            const u16 pppoe_payload_len = ipoque_int_ntohs(ipoque_int_get_u16(data, 4));

            if (pppoe_payload_len > l2_data_length - 6) {
                return PPPOE_ERROR; /* bad payload length */
            }

            return_info->type = PPPOE_CONTROL_EVENT;
            return_info->session_id = ipoque_int_get_u16(data, 2);
            return_info->payload_type = 0;

            if (pppoe_payload_len > 0) {
                return_info->payload_length = pppoe_payload_len;
                return_info->payload_data = &data[6];
            } else {
                return_info->payload_length = 0;
                return_info->payload_data = NULL;
            }

            return PPPOE_FOUND;
        }

        return PPPOE_ERROR;        
    }

    return PPPOE_NOT_FOUND;
}

ALWAYS_INLINE static inline int ipoque_pace_get_pppoe_ip_header(const PPPoEEvent * const pppoe_event,
                                                                const void ** const return_l3_data,
                                                                u16 * const return_l3_length,
                                                                u8 * const return_is_ipv6,
                                                                const u32 decaps_level)
{
    if (pppoe_event->type == PPPOE_DATA_EVENT && pppoe_event->payload_data != NULL) {
        u16 l2_ether_type = 0;
        const u8 * data = (u8 *)pppoe_event->payload_data;
        u16 data_length = pppoe_event->payload_length;

        switch (pppoe_event->payload_type) {
            case ipoque_int_htons(IPOQUE_PPPOE_IPV4):
                l2_ether_type = ipoque_int_htons(IPOQUE_ETH_P_IP);
                break;
            case ipoque_int_htons(IPOQUE_PPPOE_IPV6):
                l2_ether_type = ipoque_int_htons(IPOQUE_ETH_P_IPV6);
                break;
            case ipoque_int_htons(IPOQUE_PPPOE_MPLS_U):
                l2_ether_type = ipoque_int_htons(IPOQUE_ETH_P_MPLS_UC);
                break;
            case ipoque_int_htons(IPOQUE_PPPOE_MPLS_M):
                l2_ether_type = ipoque_int_htons(IPOQUE_ETH_P_MPLS_MC);
                break;
            default:
                return 0;
        }

        ipoque_int_skip_vlan_and_mpls(&data, &data_length, &l2_ether_type, decaps_level);

        switch (l2_ether_type) {
            case ipoque_int_htons(IPOQUE_ETH_P_IP):
                *return_is_ipv6 = 0;
                break;
            case ipoque_int_htons(IPOQUE_ETH_P_IPV6):
                *return_is_ipv6 = 1;
                break;
            default:
                return 0;
        }

        *return_l3_data = data;
        *return_l3_length = data_length;

        return 1;
    }

    return 0;
}

#endif
