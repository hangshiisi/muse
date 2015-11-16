
#include <unistd.h>
#include "read_pcap.h"
#ifndef WIN32
#include <arpa/inet.h>
#else
//#include <winsock2.h>
#include <ipq_api.h>
#include "linux_compat.h"
#define sleep Sleep
#endif

/* variables needed for libpcap */
static pcap_t *_pcap_handle = NULL;
static char _pcap_error_buffer[PCAP_ERRBUF_SIZE];
static int _pcap_datalink_type = 0;
static void (*_packet_processing_callback)(const uint64_t time, const struct iphdr *iph, uint16_t ipsize) = NULL;
static uint64_t _tick_resolution = 1000;
static uint64_t _lasttime = 0;

unsigned long long raw_pcap_packet_count;

/* 
 * PCAP callback, will be called for every packet in the pcap file
 */
static void pcap_packet_callback(u_char * args, const struct pcap_pkthdr *header, const u_char * packet)
{
	const struct ether *ethernet = (struct ether *) packet;
    uint64_t time;
	raw_pcap_packet_count++;

	/* calculate correction timestamp in given resolution */
	 time =		((uint64_t) header->ts.tv_sec) * _tick_resolution + header->ts.tv_usec / (1000000 / _tick_resolution);

	/* check for non-monotonous timestamps */
	if (_lasttime > time) {
		fprintf(stderr, "\n\nWarning, timestamp bug in the pcap file (ts delta < 0, repairing)\n\n");
		time = _lasttime;
	}
	_lasttime = time;


	if (_pcap_datalink_type == DLT_EN10MB) {

        if ((ethernet->type == htons(0x0800) ||     /* IPv4 */
             ethernet->type == htons(0x86DD)) &&    /* IPv6 */
            header->caplen >= sizeof(struct ether)) {

            /* ethernet packet, mostly recorded from a real link */
            if (header->caplen < header->len) {
                static uint8_t cap_warning_used = 0;
                if (cap_warning_used == 0) {
                    uint32_t a;
                    fprintf(stderr, "\n\nWarning, packet capture size is smaller than packet size, DETECTION MIGHT NOT WORK CORRECTLY OR EVEN CRASH\n\n");
                    for (a = 5; a > 0; a--) {
                        fprintf(stderr, "Continuing in %u seconds\n", a);
                        sleep(1);
                    }
                    cap_warning_used = 1;
                }
            }

            /* call process function with timestamp, iph pointer and length */
            (*_packet_processing_callback)(time, (struct iphdr *) &packet[sizeof(struct ether)], header->len - sizeof(struct ether));

        } else if (ethernet->type == htons(0x8100) &&
                   header->caplen >= sizeof(struct ether) + 4) {

            /* skip standard vlan tag size */
            (*_packet_processing_callback)(time, (struct iphdr *) &packet[sizeof(struct ether) + 4], header->len - sizeof(struct ether) - 4);

        } else {
            fprintf(stderr, "Warning, this ethertype will not be processed: %#.4x (packet number %llu)\n", ethernet->type, raw_pcap_packet_count);
        }

	} else if (_pcap_datalink_type == DLT_LINUX_SLL && ((packet[14] == 0x08 && packet[15] == 0x00)||(packet[14] == 0x86 && packet[15] == 0xdd))) {
		/* ethernet packet, mostly recoreded from a loopback device, just skip the first 16 bytes */
		(*_packet_processing_callback)(time, (struct iphdr *) &packet[16], header->len - 16);
    } else if (_pcap_datalink_type == DLT_RAW) {
        if (header->len < sizeof(struct iphdr)) { return; }

        (*_packet_processing_callback)(time, (struct iphdr *) packet, header->len);
    }
}

uint8_t run_pcap_loop(pcap_t * _pcap_file,
                      uint64_t tick_resolution,
                      void (*packet_processing)(const uint64_t time, const struct iphdr *iph, uint16_t ipsize))
{
    /* open the pcap file */
    _pcap_handle = _pcap_file;

    if (_pcap_handle == NULL) {
        return 1;
    }

    raw_pcap_packet_count = 0;
	_tick_resolution = tick_resolution;
    _lasttime = 0;
    _packet_processing_callback = packet_processing;
    _pcap_datalink_type = pcap_datalink(_pcap_handle);
    pcap_loop(_pcap_handle, -1, pcap_packet_callback, NULL);
    pcap_close(_pcap_handle);

    return 0;
}

uint8_t read_pcap_loop(const char * const _pcap_file,
                       uint64_t tick_resolution,
                       void (*packet_processing)(const uint64_t time, const struct iphdr *iph, uint16_t ipsize))
{
    /* open the pcap file */
    _pcap_handle = pcap_open_offline(_pcap_file, _pcap_error_buffer);

    if (_pcap_handle == NULL) {
        return 1;
    }

    return run_pcap_loop(_pcap_handle, tick_resolution, packet_processing);
}
