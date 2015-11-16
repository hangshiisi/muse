
#ifndef _READ_PCAP_H_
#define _READ_PCAP_H_

#include <pcap.h>
#ifndef WIN32
#ifndef __linux__
#include <netinet/in.h>
#endif

#include <netinet/ip.h>
#include <stdint.h>

#ifndef __linux__
#include <ipq_api.h>
#include "linux_compat.h"
#endif

#include <arpa/inet.h>
#else
#include <assert.h>

#endif
#ifdef __cplusplus
extern "C" {
#endif

/* simple ethernet definition for libpcap packet parsing */
typedef struct ether {
	unsigned char dst_mac[6];
	unsigned char src_mac[6];
	unsigned short int type;
} ether_t;

/* running number of frames that have been returned by libpcap
   (corresponds to the packet numbers displayed by Wireshark and tcpdump) */
extern unsigned long long raw_pcap_packet_count;

uint8_t read_pcap_loop(const char * const _pcap_file,
					   uint64_t tick_resolution,
				       void (*packet_processing)(const uint64_t time, const struct iphdr *iph, uint16_t ipsize));

uint8_t run_pcap_loop(pcap_t * _pcap_file,
                      uint64_t tick_resolution,
                      void (*packet_processing)(const uint64_t time, const struct iphdr *iph, uint16_t ipsize));

#ifdef __cplusplus
}
#endif

#endif
