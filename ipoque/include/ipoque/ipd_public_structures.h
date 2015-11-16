/********************************************************************************/
/**
 ** \file       ipd_public_structures.h
 ** \brief      Basic structures for all PADE events.
 **/
/********************************************************************************/

#ifndef __IPOQUE_DECODER_PUBLIC_STRUCURES_INCLUDE_FILE__
#define __IPOQUE_DECODER_PUBLIC_STRUCURES_INCLUDE_FILE__

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif



typedef u64 IPOQUE_POSTPROC_PROTOCOL_BITMASK;


#define IPD_POSTPROC_PROTOCOL_ENABLED(bitmask, index) (bitmask & ((u64)1 << (index - 0x10000))) != 0
#define IPD_POSTPROC_PROTOCOL_ENABLE(bitmask, index) (bitmask) = (bitmask | ((u64)1 << (index - 0x10000)))
#define IPD_POSTPROC_PROTOCOL_ENABLE_ALL(bitmask)  (bitmask) = ((IPOQUE_POSTPROC_PROTOCOL_BITMASK)0xFFFFFFFFFFFFFFFFULL)
#define IPD_POSTPROC_PROTOCOL_DISABLE(bitmask, index) (bitmask) = (bitmask & ~((u64)1 << (index - 0x10000)))
#define IPD_POSTPROC_PROTOCOL_DISABLE_ALL(bitmask) (bitmask) = 0


typedef u64 IPOQUE_CLASS_DECODER_BITMASK;

#define IPD_CLASS_DECODER_ENABLED(bitmask, index) (bitmask & ((u64)1 << (index))) != 0
#define IPD_CLASS_DECODER_ENABLE(bitmask, index) (bitmask) = (bitmask | ((u64)1 << (index)))
#define IPD_CLASS_DECODER_ENABLE_ALL(bitmask)  (bitmask) = ((IPOQUE_CLASS_DECODER_BITMASK)0xFFFFFFFFFFFFFFFFULL)
#define IPD_CLASS_DECODER_DISABLE(bitmask, index) (bitmask) = (bitmask & ~((u64)1 << (index)))
#define IPD_CLASS_DECODER_DISABLE_ALL(bitmask) (bitmask) = 0



struct ipd_string
{
	u8 *buffer;
	u64 length;
};

union ip_v4_v6_addr {
    struct in_addr ipv4;
    struct in6_addr ipv6;
};

/**
 * 3-tuple identifying one end of an IP flow
 */
struct ipd_address_port {
    u8 is_ip_v6;                 /**< if set, the #address field contains an IPv6 address */
    u8 l4_protocol;              /**< transport-layer protocol (IPPROTO_UDP or IPPROTO_TCP) */
    u16 port;                    /**< port in network byte order */
    union ip_v4_v6_addr address; /**< IP address in network byte order */
};

/**
 * 5-tuple identifying an IP flow
 */
struct ipd_5tuple {
    u16 is_ip_v6;
    u8 protocol;               // transport-layer protocol

    union ip_v4_v6_addr client_ip; // network byte order
    union ip_v4_v6_addr server_ip; // network byte order

    u16 client_port;            // network byte order
    u16 server_port;            // network byte order
};

/**
 * an IP packet decapsulated from a tunnel
 */
struct ipd_tunnelled_ip_packet {
	u64 tunnel_id;              /**< the ID of the tunnel */
	u16 tunnel_depth;           /**< the depth of the tunnel */
	struct ipd_string data;		/**< buffer containing the decapsulated IP packet */
};



/** Hooks for integrating an AMR or AMR-WB codec that can be used in the RTP decoder to detect DTMF tones inside audio streams.
 */
struct ipd_amr_decoder {
    /** @brief Initialization
        @details Initialize a codec state and return a pointer to it. PADE will request a separate codec state for each direction
        of each flow containing AMR- or AMR-WB-encoded RTP payloads.
        If initialization fails, NULL should be returned. */
    void* (*init)(void);

    /** @brief Shutdown
        @details Will be called to clean up a codec state after the flow ends.
        @param state codec state that should be freed */
    void (*exit)(void *state);

    /** @brief Decode one AMR or AMR-WB frame
        @param state codec state, as returned by init
        @param compressed_frame pointer to one table-of-contents byte (containing the frame type index in bits 3..6), followed by the
          compressed speech data. This is the layout that is also expected by the \c Decoder_Interface_Decode and
          \c D_IF_decode functions of the OpenCore-AMR package. PADE guarantees that the input buffer is long enough for
          one frame with the given frame type.
        @param output Points to a buffer that shall be filled with 160 (AMR) or 320 (AMR-WB) signed 16-bit audio samples
    */
    void (*decode)(void *state, const u8 *compressed_frame, short *output);
};



enum ipd_ip_checksumming
{
    IPD_IP_CHECKSUM_IGNORE = 0,
    IPD_IP_CHECKSUM_DISCARD,
};

enum ipd_tcp_checksumming
{
    IPD_TCP_CHECKSUM_IGNORE = 0,
    IPD_TCP_CHECKSUM_DISCARD,
    IPD_TCP_CHECKSUM_WAIT_FOR_TCP_RETRANSMISSION,
};


#endif /* __IPOQUE_DECODER_PUBLIC_STRUCURES_INCLUDE_FILE__ */
