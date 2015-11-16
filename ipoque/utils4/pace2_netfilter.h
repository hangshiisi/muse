#ifndef PACE2_NETFILTER_H
#define PACE2_NETFILTER_H

#include <stdint.h>

#define IPQ_BUFSIZE 65535
#define IPQ_SOCKET_BUFFER_SIZE (10 * 1024 * 1024)

#include <errno.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <linux/netfilter.h>
#include <libnetfilter_queue/libnetfilter_queue.h>
#include <libnetfilter_queue/linux_nfnetlink_queue.h>

#define PACE2_NF_ACCEPT NF_ACCEPT
#define PACE2_NF_DROP NF_DROP


#ifdef __cplusplus
extern "C" {
#endif

typedef void ( *pace2_netfilter_callback_t )( const struct timeval * const time,
                                               const void * const payload,
                                               uint16_t payload_len,
                                               const uint64_t * const packet_id,
                                               const uint8_t layer,
                                               void * user_data );

struct pace2_netfilter {
    struct nfq_handle * nfq_h;
    struct nfq_q_handle *nfq_q_h;
    pace2_netfilter_callback_t callback;
    void * user_data;
};

char pace2_netfilter_initialize( struct pace2_netfilter * const netfilter ,
                                  pace2_netfilter_callback_t callback,
                                  void * const user_data );

void pace2_netfilter_exit( struct pace2_netfilter * const netfilter );

void pace2_netfilter_packet_loop( struct pace2_netfilter * const netfilter,
                                   const uint8_t * const running );

void pace2_netfilter_set_verdict( struct pace2_netfilter * const netfilter,
                                   const uint64_t packet_id,
                                   const uint32_t verdict );

#ifdef __cplusplus
}
#endif

#endif
