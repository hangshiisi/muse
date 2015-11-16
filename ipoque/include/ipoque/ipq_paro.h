/* written by Ralf Hoffmann, ipoque GmbH
 * ralf.hoffmann@ipoque.com
 */

#ifndef __IPOQUE_API_INCLUDE_FILE__
#error CANNOT INCLUDE THIS .H FILE, INCLUDE IPQ_API.H
#endif

#ifndef IPQ_PARO_H
#define IPQ_PARO_H

#ifdef __cplusplus
extern "C" {
#endif

	/*
	 * The packet reordering engine offers two interface.
	 *
	 * The high level interface does all memory management by itself
	 * and only needs the packet as input.
	 *
	 * The low level interface manages the memory for the packet
	 * buffer itself but does not contain flow tracking.
	 */


    /**
     * This is the definition of the extended callback with additional
     * user data
     */
    typedef void (*ipoque_paro_callback_ext)(const u8 *ptr, const u16 len,
                                             const u16 l3_offset, const u16 l3_len,
                                             const IPOQUE_TIMESTAMP_COUNTER_SIZE
                                             original_ts,
                                             const IPOQUE_TIMESTAMP_COUNTER_SIZE
                                             current_ts, const u8 dir,
                                             const void **packet_user_data_array,
                                             const u16* packet_user_data_array_lengths,
                                             u16 packet_user_data_array_count,
                                             void *callback_userptr);

	/*************************
	 * The high level engine *
	 *************************/

	enum ipoque_paro_mode {
		IPOQUE_PARO_HASH_STATIC_PACKET_DYNAMIC,	/* the only supported
												   mode right now, uses a
												   static hash table size
												   and dynamic memory
												   allocation for packet buffer */

		/* CURRENTLY NOT SUPPORTED */
		IPOQUE_PARO_HASH_DYNAMIC_PACKET_DYNAMIC,
		IPOQUE_PARO_HASH_STATIC_PACKET_STATIC
	};

	/**
	 * The high level initialization function
	 *
	 * @param max_hash_memory the maximum hash table size for flow tracking
	 * @param max_packet_memory the maxmimum memory used for the packet buffer
	 * @param mode the memory management mode
	 * @param packet_timeout the number of ticks after which a packet leaves the engine again at the latest
	 * @param flow_timeout the flow timeout after which a flow is removed from the hash table
	 * @param callback the packet callback when a packet leaves the engine
	 * @param callback_userptr an arbitrary pointer for custom data, it's given to the callback function
	 * @param alloc_function memory allocator function
	 * @param realloc_function memory reallocator function
	 * @param free_function memory free function
	 * @param memory_userptr arbitrary data given to the memory functions
	 * @return NULL in case the init failed, otherwise an initialized structure
	 */
	struct ipoque_paro_struct *ipoque_paro_init(unsigned long max_hash_memory,	/* maximum memory for allocation in bytes, 0 is infinite */
												unsigned long max_packet_memory, enum ipoque_paro_mode mode, IPOQUE_TIMESTAMP_COUNTER_SIZE packet_timeout,	/* timeout in resolution ticks */
												IPOQUE_TIMESTAMP_COUNTER_SIZE flow_timeout,
												void (*callback) (const u8 * ptr, const u16 len, const u16 l3_offset,
																  const u16 l3_len,
																  const IPOQUE_TIMESTAMP_COUNTER_SIZE original_ts,
																  const IPOQUE_TIMESTAMP_COUNTER_SIZE current_ts,
																  const u8 dir, void *callback_userptr),
												void *callback_userptr, void *(*alloc_function) (unsigned long size,
																								 void *memory_userptr),
												void *(*realloc_function) (void *ptr, unsigned long size,
																		   void *memory_userptr),
												void (*free_function) (void *ptr, void *memory_userptr),
												void *memory_userptr);

	/**
	 * The high level initialization function, with extended meta-data
	 *
	 * @param max_hash_memory the maximum hash table size for flow tracking
	 * @param max_packet_memory the maxmimum memory used for the packet buffer
	 * @param mode the memory management mode
	 * @param packet_timeout the number of ticks after which a packet leaves the engine again at the latest
	 * @param flow_timeout the flow timeout after which a flow is removed from the hash table
	 * @param callback the packet callback when a packet leaves the engine
	 * @param callback_userptr an arbitrary pointer for custom data, it's given to the callback function
	 * @param alloc_function memory allocator function
	 * @param realloc_function memory reallocator function
	 * @param free_function memory free function
	 * @param memory_userptr arbitrary data given to the memory functions
	 * @return NULL in case the init failed, otherwise an initialized structure
	 */
	struct ipoque_paro_struct *ipoque_paro_init_ext(unsigned long max_hash_memory,	/* maximum memory for allocation in bytes, 0 is infinite */
                                                    unsigned long max_packet_memory, enum ipoque_paro_mode mode, IPOQUE_TIMESTAMP_COUNTER_SIZE packet_timeout,	/* timeout in resolution ticks */
                                                    IPOQUE_TIMESTAMP_COUNTER_SIZE flow_timeout,
                                                    ipoque_paro_callback_ext callback,
                                                    void *callback_userptr, void *(*alloc_function) (unsigned long size,
                                                                                                     void *memory_userptr),
                                                    void *(*realloc_function) (void *ptr, unsigned long size,
                                                                               void *memory_userptr),
                                                    void (*free_function) (void *ptr, void *memory_userptr),
                                                    void *memory_userptr);

#define IPOQUE_PARO_L3_LEN_NON_IP 0
#define IPOQUE_PARO_L3_LEN_REST_OF_DATA 1

	/**
	 * add a packet to the engine
	 *
	 * @param ipoque_paro the pointer to the initialized PARO structure
	 * @param ptr the pointer to the packet data
	 * @param len the length of the whole packet data
	 * @param l3_offset the offset of the l3 header inside the packet
	 * @param l3_len the length of the l3 data (IPOQUE_PARO_L3_LEN_NON_IP if packet is not an IP packet,
	 *        IPOQUE_PARO_L3_LEN_REST_OF_DATA if the anything left in *ptr is the l3 data)
	 * @param ts the timestamp of the packet
	 * @return == 0 if the packet has been handled successful, != 0 otherwise
	 */
	u8 ipoque_paro_handle_packet(struct ipoque_paro_struct *ipoque_paro, const u8 * ptr, const u16 len,
								 const u16 l3_offset, const u16 l3_len, const IPOQUE_TIMESTAMP_COUNTER_SIZE ts);

    /**
     * add a packet to the engine, additional user-data per packet
     *
     * @param ipoque_paro the pointer to the initialized PARO structure
     * @param ptr the pointer to the packet data
     * @param len the length of the whole packet data
     * @param l3_offset the offset of the l3 header inside the packet
     * @param l3_len the length of the l3 data (IPOQUE_PARO_L3_LEN_NON_IP if packet is not an IP packet,
     *        IPOQUE_PARO_L3_LEN_REST_OF_DATA if the anything left in *ptr is the l3 data)
     * @param ts the timestamp of the packet
     * @param packet_user_data arbitrary user data, will be given back to callback originally or copied, otherwise ignore by PARO
     * @param packet_user_data_len length of user data block
     * @return == 0 if the packet has been handled successful, != 0 otherwise
     */
	u8 ipoque_paro_handle_packet_ext(struct ipoque_paro_struct *ipoque_paro, const u8 * ptr, const u16 len,
                                     const u16 l3_offset, const u16 l3_len, const IPOQUE_TIMESTAMP_COUNTER_SIZE ts,
                                     const void *packet_user_data,
                                     const u16 packet_user_data_len);

	/**
	 * sets the internal timestamp and flushes old packets
	 *
	 * @param ipoque_paro the pointer to the initialized PARO structure
	 * @param ts the timestamp
	 */
	void ipoque_paro_set_timestamp(struct ipoque_paro_struct *ipoque_paro, const IPOQUE_TIMESTAMP_COUNTER_SIZE ts);

	/**
	 * clears the hash table and therefore flushes all packets
	 *
	 * @param ipoque_paro the pointer to the initialized PARO structure
	 */
	void ipoque_paro_cleanup(struct ipoque_paro_struct *ipoque_paro);

	/**
	 * destroy the PARO structure, flushes all packets before freeing
	 * all memory
	 *
	 * @param ipoque_paro the pointer to the initialized PARO structure
	 */
	void ipoque_paro_destroy(struct ipoque_paro_struct *ipoque_paro);

	/**
	 * get current statistics
	 */
	const struct ipoque_paro_statistics *ipoque_paro_get_statistics(struct ipoque_paro_struct *ipoque_paro);

	/**
	 * sets the maximum tunnel decapsulation level
	 *
	 * @param ipoque_paro the pointer to the initialized PARO structure
	 * @param max_level maximum number of tunnels to decapsulate
	 */
	void ipoque_paro_set_plain_tunnel_decapsulation_level(struct ipoque_paro_struct *ipoque_paro, const u16 max_level);

	/**
	 * the per-flow statistics struct
	 */
	struct ipoque_paro_flow_statistics {
		/**
		 * The number of bytes missing in the flow
		 */
		u64 missing_bytes;
	};

	/**
	 * get current statistics of the flow of the last packet given to the engine
	 *
	 * @param ipoque_paro the pointer to the initialized PARO structure
	 * @param stats_return pointer to a flow statistic structure which will be filled
	 * @return 0 on success, != 0 otherwise
	 */
	u8 ipoque_paro_get_flow_statistics(struct ipoque_paro_struct *ipoque_paro,
									   struct ipoque_paro_flow_statistics *stats_return);

	/************************
	 * The low level engine *
	 ************************/

	enum ipoque_paro_core_mode {
		IPOQUE_PARO_PACKET_DYNAMIC,	/* only supported mode right now */

		/* CURRENTLY NOT SUPPORTED */
		IPOQUE_PARO_PACKET_STATIC
	};

	/**
	 * the initialization function of the reordering core
	 *
	 * @param max_memory the maxmimum memory used for the packet buffer
	 * @param mode the memory management mode
	 * @param packet_timeout the number of ticks after which a packet leaves the engine again at the latest
	 * @param callback the packet callback when a packet leaves the engine
	 * @param callback_userptr an arbitrary pointer for custom data, it's given to the callback function
	 * @param alloc_function memory allocator function
	 * @param realloc_function memory reallocator function
	 * @param free_function memory free function
	 * @param memory_userptr arbitrary data given to the memory functions
	 * @return NULL in case the init failed, otherwise an initialized structure
	 */
	struct ipoque_paro_core_struct *ipoque_paro_core_init(const unsigned long max_memory,
														  const enum ipoque_paro_core_mode mode,
														  const IPOQUE_TIMESTAMP_COUNTER_SIZE packet_timeout,
														  void (*callback) (const u8 * ptr, const u16 len,
																			const u16 l3_offset, const u16 l3_len,
																			const IPOQUE_TIMESTAMP_COUNTER_SIZE
																			original_ts,
																			const IPOQUE_TIMESTAMP_COUNTER_SIZE
																			current_ts, const u8 dir,
																			void *callback_userptr),
														  void *callback_userptr,
														  void *(*alloc_function) (unsigned long size,
																				   void *memory_userptr),
														  void *(*realloc_function) (void *ptr, unsigned long size,
																					 void *memory_userptr),
														  void (*free_function) (void *ptr, void *memory_userptr),
														  void *memory_userptr);

	/**
	 * the initialization function of the reordering core, extended API for additional meta-data
	 *
	 * @param max_memory the maxmimum memory used for the packet buffer
	 * @param mode the memory management mode
	 * @param packet_timeout the number of ticks after which a packet leaves the engine again at the latest
	 * @param callback the packet callback when a packet leaves the engine
	 * @param callback_userptr an arbitrary pointer for custom data, it's given to the callback function
	 * @param alloc_function memory allocator function
	 * @param realloc_function memory reallocator function
	 * @param free_function memory free function
	 * @param memory_userptr arbitrary data given to the memory functions
	 * @return NULL in case the init failed, otherwise an initialized structure
	 */
    struct ipoque_paro_core_struct *ipoque_paro_core_init_ext(const unsigned long max_memory,
                                                              const enum ipoque_paro_core_mode mode,
                                                              const IPOQUE_TIMESTAMP_COUNTER_SIZE packet_timeout,
                                                              ipoque_paro_callback_ext callback,
                                                              void *callback_userptr,
                                                              void *(*alloc_function) (unsigned long size,
                                                                                       void *memory_userptr),
                                                              void *(*realloc_function) (void *ptr, unsigned long size,
                                                                                         void *memory_userptr),
                                                              void (*free_function) (void *ptr, void *memory_userptr),
                                                              void *memory_userptr);


    /**
     * the initialization function of the reordering core, extended API for additional meta-data
     *
     * @param max_memory the maxmimum memory used for the packet buffer
     * @param mode the memory management mode
     * @param packet_timeout the number of ticks after which a packet leaves the engine again at the latest
     * @param callback the packet callback when a packet leaves the engine
     * @param callback_userptr an arbitrary pointer for custom data, it's given to the callback function
     * @param alloc_function memory allocator function
     * @param realloc_function memory reallocator function
     * @param free_function memory free function
     * @param thread_ID id which is passed to malloc and free functions
     * @param memory_userptr arbitrary data given to the memory functions
     * @return NULL in case the init failed, otherwise an initialized structure
     */
    struct ipoque_paro_core_struct *ipoque_pace2_paro_core_init(const unsigned long max_memory,
                                                                const enum ipoque_paro_core_mode mode,
                                                                const IPOQUE_TIMESTAMP_COUNTER_SIZE packet_timeout,
                                                                ipoque_paro_callback_ext callback,
                                                                void *callback_userptr,
                                                                pace2_malloc pace2_malloc,
                                                                pace_realloc_t realloc_function,
                                                                pace2_free pace2_free,
                                                                int thread_ID,
                                                                void *memory_userptr);

	/**
	 * returns the size of the internal flow_state structure
	 */
	unsigned long ipoque_paro_core_get_sizeof_flow_state_struct(void);

	/**
	 * handles a single packet
	 *
	 * @param ipoque_paro_core the pointer to the initialized PARO core structure
	 * @param ptr the pointer to the packet data
	 * @param len the length of the whole packet data
	 * @param l3_offset the offset of the l3 header inside the packet
	 * @param l3_len the length of the l3 data (IPOQUE_PARO_L3_LEN_NON_IP if packet is not an IP packet,
	 *        IPOQUE_PARO_L3_LEN_REST_OF_DATA if the anything left in *ptr is the l3 data)
	 * @param tcph_offset the offset to the tcph, 0 if not a TCP packet
	 * @param tcp_payload_length the length of the tcp payload (without the tcp header) (for tcp packets only)
	 * @param ts the timestamp of the packet
	 * @param dir the direction flag, must be 0 or 1 and must be consistent within a flow
	 * @param flow_state the pointer to the flow structure
	 * @return == 0 if the packet has been handled successful, != 0 otherwise
	 */
	u8 ipoque_paro_core_handle_packet(struct ipoque_paro_core_struct *ipoque_paro_core,
									  const u8 * ptr, const u16 len, const u16 l3_offset, const u16 l3_len,
									  const u16 tcph_offset, const u16 tcp_payload_length,
									  const IPOQUE_TIMESTAMP_COUNTER_SIZE ts, const u8 dir, void *flow_state);

    /**
     * handles a single packet, extended interface with additional user data
     *
     * @param ipoque_paro_core the pointer to the initialized PARO core structure
     * @param ptr the pointer to the packet data
     * @param len the length of the whole packet data
     * @param l3_offset the offset of the l3 header inside the packet
     * @param l3_len the length of the l3 data (IPOQUE_PARO_L3_LEN_NON_IP if packet is not an IP packet,
     *        IPOQUE_PARO_L3_LEN_REST_OF_DATA if the anything left in *ptr is the l3 data)
     * @param tcph_offset the offset to the tcph, 0 if not a TCP packet
     * @param tcp_payload_length the length of the tcp payload (without the tcp header) (for tcp packets only)
     * @param ts the timestamp of the packet
     * @param dir the direction flag, must be 0 or 1 and must be consistent within a flow
     * @param packet_user_data arbitrary user data, will be given back to callback originally or copied, otherwise ignore by PARO
     * @param packet_user_data_len length of user data block
     * @param flow_state the pointer to the flow structure
     * @return == 0 if the packet has been handled successful, != 0 otherwise
     */
	u8 ipoque_paro_core_handle_packet_ext(struct ipoque_paro_core_struct *ipoque_paro_core,
                                          const u8 * ptr, const u16 len, const u16 l3_offset, const u16 l3_len,
                                          const u16 tcph_offset, const u16 tcp_payload_length,
                                          const IPOQUE_TIMESTAMP_COUNTER_SIZE ts, const u8 dir,
                                          const void *packet_user_data,
                                          const u16 packet_user_data_len,
                                          void *flow_state);

	/**
	 * sets the internal timestamp and flushes old packets
	 *
	 * @param ipoque_paro_core the pointer to the initialized PARO core structure
	 * @param ts the timestamp
	 */
	void ipoque_paro_core_set_timestamp(struct ipoque_paro_core_struct *ipoque_paro_core,
										const IPOQUE_TIMESTAMP_COUNTER_SIZE ts);

	/**
	 * flushes all pending packets of a flow
	 *
	 * @param ipoque_paro_core the pointer to the initialized PARO core structure
	 * @param flow_state the pointer to the flow structure
	 */
	void ipoque_paro_core_flush_flow(struct ipoque_paro_core_struct *ipoque_paro_core, void *flow_state);
	/**
	 * destroys the reordering core
	 *
	 * will flush all pending packets
	 *
	 * @param ipoque_paro_core the pointer to the initialized PARO core structure
	 */
	void ipoque_paro_core_destroy(struct ipoque_paro_core_struct *ipoque_paro_core);

	/**
	 * get current statistics
	 *
	 * @param ipoque_paro_core the pointer to the initialized PARO core structure
	 * @return pointer to a static statistics buffer
	 */
	const struct ipoque_paro_statistics *ipoque_paro_core_get_statistics(struct ipoque_paro_core_struct
																		 *ipoque_paro_core);

	/**
	 * get current statistics of the given flow
	 *
	 * @param ipoque_paro_core the pointer to the initialized PARO core structure
	 * @param flow_state the pointer to the flow structure
	 * @param stats_return pointer to a flow statistic structure which will be filled
	 * @return 0 on success, != 0 otherwise
	 */
	u8 ipoque_paro_core_get_flow_statistics(struct ipoque_paro_core_struct
											*ipoque_paro_core, void *flow_state,
											struct ipoque_paro_flow_statistics *stats_return);

	/*******************
	 * PARO statistics *
	 *******************/

	struct ipoque_paro_statistics {
		u64 no_of_unhandled_packets;

		u64 no_of_packets_in_order;

		u64 no_of_packets_out_of_order_and_buffered;

		/**
		 * The number of packets that are out-of-order but could not
		 * be buffered due to memory limits
		 */
		u64 no_of_packets_out_of_order_and_not_buffered;

		/**
		 * The number of events the order of a flow could not be fixed
		 * (essential packets missing after timeout)
		 */
		u64 no_of_unfixable_events;

		u64 max_no_of_buffered_packets;

		/**
		 * The number of events a flow has been flushed since another packet
		 * needs to be buffered (a flow might be counted multiple times)
		 */
		u64 no_of_flows_flushed_due_to_memory_limit;

		u64 max_memory_usage;

		/**
		 * The maximum number of ticks after which a flow could be
		 * successfully reordered
		 */
		u64 max_ticks_for_reordering;

		/**
		 * The average number of ticks after which a flow could be
		 * successfully reordered
		 */
		u64 avg_ticks_for_reordering;
	};

#ifdef __cplusplus
}
#endif
#endif							/* IPQ_PARO_H */
