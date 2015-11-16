/* written by klaus degner, ipoque GmbH
 * klaus.degner@ipoque.com
 */
#ifndef __IPOQUE_API_INCLUDE_FILE__
#error CANNOT INCLUDE THIS .H FILE, INCLUDE IPQ_API.H
#endif

#ifndef __IPQ_PUBLIC_FUNCTIONS_H__
#define __IPQ_PUBLIC_FUNCTIONS_H__

#ifdef __cplusplus
extern "C" {
#endif

/* get flow and id size */

/* PUBLIC FUNCTIONS, API DOCUMENTATION IN MANPAGES ONLY !! */

	/**
	 * struct for a unique ipv4 flow address
	 */
	typedef struct ipoque_unique_flow_ipv4_address_struct {
		/**
		 * lower ip
		 */
		u32 lower_ip;
		/**
		 * upper ip
		 */
		u32 upper_ip;
		/* we need 3 dummies to fill up to ipv6 address size */
		/**
		 * this is only needed to become the same size like a unique ipv6 struct
		 */
		u64 dummy[3];
	} ipoque_unique_flow_ipv4_address_struct_t;

	/**
	 * struct for a unique ipv6 flow address
	 */
	typedef struct ipoque_unique_flow_ipv6_address_struct {
		/**
		 * lower ip
		 */
		u64 lower_ip[2];
		/**
		 * upper ip
		 */
		u64 upper_ip[2];
	} ipoque_unique_flow_ipv6_address_struct_t;

	/**
	 * struct for a unique ipv4 and ipv6 5-tuple (ip,ip,port,port,protocol)
	 */
	typedef struct ipoque_unique_flow_ipv4_and_6_struct {
		/* only ip addresses are different, to minimize compare operations for hash tables, store ipv4 or ipv6 always in the first bit */
		/**
		 * saves if it is a ipv6, if it false so it is a ipv4
		 */
		u16 is_ip_v6;
		/**
		 * the protocol, 16 bit wide for alignemt reasons
		 */
		u16 protocol;			/* for alignment reason, protocol is 16 bit, not 8 bit */
		/**
		 * the port of the lower ip address
		 */
		u16 lower_port;
		/**
		 * the port of the upper ip address
		 */
		u16 upper_port;
		union {
			/**
			 * the ipv4 flow address struct. use the same memory area like ipv6 (union)
			 */
			struct ipoque_unique_flow_ipv4_address_struct ipv4;
			/**
			 * the ipv6 flow address struct. use the same memory area like ipv4 (union)
			 */
			struct ipoque_unique_flow_ipv6_address_struct ipv6;
		} ip;
	} ipoque_unique_flow_ipv4_and_6_struct_t;

	typedef enum {

		IPQ_LOG_ERROR,
		IPQ_LOG_TRACE,
		IPQ_LOG_DEBUG
	} ipq_log_level_t;

	typedef void (*ipoque_debug_function_ptr) (u32 protocol,
											   void *module_struct, ipq_log_level_t log_level, const char *format, ...);

#define MEDIA_LIST(M) M(NOT_SET,                        The HTTP content type is not set.) \
                      M(UNKNOWN,                        The HTTP content type is unknown.) \
                      M(MPEG,                           The HTTP content type is MPEG.) \
                      M(FLASH,                          The HTTP content type is FLASH.) \
                      M(QUICKTIME,                      The HTTP content type is QUICKTIME.) \
                      M(REALMEDIA,                      The HTTP content type is REALMEDIA.) \
                      M(WINDOWSMEDIA,                   The HTTP content type is WINDOWSMEDIA.) \
                      M(CITRIX,                         The HTTP content type is Citrix.) \
                      M(MICROSOFT_MEDIA_STREAMING,      The HTTP content type is Microsoft Media Streaming (MMS).) \
                      M(MULTIMEDIA_MESSAGE,             The HTTP content type is Multimedia Messaging Service.) \
                      M(OFF,                            The HTTP content type is OFF.) \
                      M(OGG,                            The HTTP content type is OGG.) \
                      M(MP3,                            The HTTP content type is MP3.) \
                      M(AVI,                            The HTTP content type is AVI.) \
                      M(MOVE,                           The HTTP content type is MOVE.) \
                      M(MATROSKA,                       The HTTP content type is Matroska.) \
                      M(AUDIO_INTERCHANGE_FILE,         The HTTP content type is Audio Interchange File.) \
                      M(THREE_GPP,                      The HTTP content type is 3GPP.)

#define LIST_TO_MEDIA_ENUM(NAME, ...) PACE_CT_ ## NAME,
#define LIST_TO_MEDIA_STR(NAME, ...) #NAME,

    enum pace_http_content_type {
        MEDIA_LIST(LIST_TO_MEDIA_ENUM)

        NUMBER_OF_MEDIA_TYPES
    };



    /**
     * This function returns a clone of the root detection module for
     * SMP handling. It's an extended function which also requires a
     * free function pointer. It is recommended to use always use
     * function instead of ipoque_clone_root_detection_module, and it
     * is required to use this function if the dynamic upgrade feature
     * is used.
     *
     * @param root the root detection module, not NULL
     * @param ipoque_malloc function pointer to a memory allocator
     * @param ipoque_free function pointer to a memory free funciton
     * @param userptr pointer to memory functions
     * @return the clone of the root detection module or NULL if failed. It must be freed
       by ipoque_exit_detection_module at cleanup.
     */
    struct ipoque_detection_module_struct *ipoque_clone_root_pace2_module(struct ipoque_detection_module_struct *root,
                                                                          pace2_malloc pace2_malloc,
                                                                          pace2_free pace2_free, int thread_ID,
                                                                          void *userptr);


    /**
     * This function destroys the detection module
     * @param ipoque_struct the to clearing detection module, can be NULL
     * @param userptr user defined pointer for allocation function, not NULL
     * @param ipoque_free function pointer to a memory free function, see validity of userptr
     *
     * works with IPOQUE_PACE_DYNAMIC_UPGRADE
     */
    void ipoque_exit_pace2_module(struct ipoque_detection_module_struct *ipoque_struct,
                                  pace2_free pace2_free,
                                  int thread_ID,
                                  void *userptr);








#ifdef IPOQUE_SUPPORT_FLOW_ID_CORRELATION
    typedef enum ipoque_flow_id_correlation_activation_mode {
        IPOQUE_FLOW_ID_CORRELATION_DISABLED = 0,
        IPOQUE_FLOW_ID_CORRELATION_ENABLED,
    } ipoque_flow_id_correlation_activation_mode_t;


    typedef struct ipoque_flow_id_correlation_subscriber_data {
        u64 last_rtsp_flow_id;
        u64 last_sip_flow_id;
    } ipoque_flow_id_correlation_subscriber_data_t;

    /**
     * This function enables/disables the Flow Correlation Feature.
     * @param ipoque_struct the detection module, not NULL
     * @param mode the mode can be IPOQUE_FLOW_ID_CORRELATION_DISABLED or IPOQUE_FLOW_ID_CORRELATION_ENABLED.
     * @param ipoque_malloc function pointer to memory allocator, not NULL
     * @param ipoque_free function pointer to memory free function, not NULL
     */
    u8 ipoque_pace2_set_flow_id_correlation_mode(struct ipoque_detection_module_struct * const ipoque_struct,
                                                 const ipoque_flow_id_correlation_activation_mode_t mode,
                                                 pace2_malloc_t pace2_malloc,
                                                 pace2_free_t pace2_free, int thread_ID);
#endif





	/**
	 * This is the struct for storing information about the latency of a flow.
	 */
	typedef struct flow_latency_struct {
		/**
		 * diff_syn_synack_possible a flag that shows if a syn command and the current synack was seen
		 */
		u32 diff_syn_synack_possible:1;
		/**
		 * diff_synack_ack_possible a flag that shows if a synack command and the current ack was seen
		 */
		u32 diff_synack_ack_possible:1;
		/**
		 * diff_syn_synack time difference between syn and synack command
		 */
		IPOQUE_TIMESTAMP_COUNTER_SIZE diff_syn_synack;
		/**
		 * diff_synack_ack time difference between synack and ack command
		 */
		IPOQUE_TIMESTAMP_COUNTER_SIZE diff_synack_ack;
	} flow_latency_struct_t;


	/**
	 * Struct containing counter for tcp retransmission and ooo-packets of a flow
	 */
	typedef struct ipoque_flow_ooo_counter_struct {
		/**
		 * flow_ooo_counter number of out of order packets
		 */
		u16 flow_ooo_counter;

		/**
		 * flow_retransmission_counter number of retransmission packets
		 */
		u16 flow_retransmission_counter;
	} ipoque_flow_ooo_count_struct_t;






#if defined (IPOQUE_DETECTION_MEASURE_ASYMETRIC_CONNECTION_SETUP) && defined(IPOQUE_DETECTION_SUPPORT_ASYMETRIC_DETECTION)

	enum ipoque_asymmetric_connection_status_enum {
		IPOQUE_CONNECTION_STATUS_SYMMETRIC = 0,
		IPOQUE_CONNECTION_STATUS_ASYMMETRIC = 1,
		IPOQUE_CONNECTION_STATUS_UNKNOWN = 2,
	};

	/**
	 * This function returns whether it is an asymmetric or symmetric connection
	 * it is recommended to call this at connection end
	 * it uses a complex heuristic for tcp connections and a basic one for all other protocols
	 * @param ipoque_struct the detection module, not NULL
	 * @param flow pointer to the connection state machine, not NULL
     *
     * works with IPOQUE_PACE_DYNAMIC_UPGRADE
	 */
	enum ipoque_asymmetric_connection_status_enum ipoque_get_asymmetric_connection_status(const struct
																						  ipoque_detection_module_struct
																						  *ipoque_struct,
																						  const void *flow);

#endif



	/* the following function gives a report in terms of the following struct
	 * telling about the quality of an rtp connection */

	/**
	 * struct for rtp performance data
	 */
	struct ipoque_rtp_performance_data_struct {

		/* these values are calculated with the help of the rtcp packets. */
		/**
		 * this value gives the percent part of the max lost packets
		 */
		u32 max_packets_lost_percentual;
		/**
		 * this value gives the percent part of the min lost packets
		 */
		u32 min_packets_lost_percentual;
		/**
		 * this value gives the percent part of the average lost packets
		 */
		u32 average_packets_lost_percentual;
		/**
		 * this value gives the max jitter
		 */
		u32 max_jitter;
		/**
		 * this value gives the min jitter
		 */
		u32 min_jitter;
		/**
		 * this value gives the average jitter
		 */
		u32 average_jitter;
		/**
		 * this value gives the number of packets
		 */
		u32 packet_number;
		/* theses values are calculated with the help of the rtp packets */
		/**
		 * this value gives the average rtp jitter
		 */
		u32 rtp_average_jitter;
		/**
		 * this value gives the rtp fraction
		 */
		u8 rtp_fraction;

	};

    struct ipoque_rtp_flow_stats_struct {
        u32 packets_sent[2];    /**< number of packets sent, for each direction */
        u32 packets_lost[2];    /**< number of packets lost, for each direction */
        u32 current_jitter[2];      /**< jitter, for each direction */
        u32 current_frequency[2];   /**< frequency used for jitter calculation, for each direction */
        u8 payload_type;        /**< payload type of most recent packet */
        u32 packets_overhead[2]; /**< number of overhead packets for each direction */
    };

	/** structure containing the data from a reception report block in an RTCP sender or receiver report
     * packet (see RFC3550, section 6.4, for the meaning of the fields)
     *
     * all fields use host by order */
    struct ipoque_rtcp_reception_report_struct {
        u32 direction;          /**< direction of the SR/RR packet */
        u8 fraction_lost;       /**< fraction of RTP packets lost since last SR or RR (scaled to 0..255) */
        u32 packets_lost;       /**< number of RTP packets since beginning of reception */
        u32 jitter;             /**< interarrival jitter */
        u32 lsr;                /**< last sender report timestamp */
        u32 dlsr;               /**< delay since (reception of) last sender report */
    };


#define IPOQUE_MAX_PARSE_SSL_DNS_ALT_NAMES 50







#ifdef IPOQUE_ENABLE_DEFRAG_ENGINE

	enum ipoqe_defrag_checksum_enum {
		IPOQUE_DEFRAG_CHECKSUM_IGNORE_WRONG_IP_CHECKSUM,
		IPOQUE_DEFRAG_CHECKSUM_DISCARD_WRONG_IP_CHECKSUM,
		IPOQUE_DEFRAG_CHECKSUM_MARK_WRONG_IP_CHECKSUM_AS_WRONG,
	};

    /**
     * Initializes the pace defrag engine with additional user defined key
     * @param ipoque_struct the detection module, not NULL
     * @param memory maximum memory in Bytes for defrag engine, if realloc is set to != NULL, it is the initial memory
     * @param timeout timeout in ticks for each fragment. It is recommended to keep this as low as possible ( maximum 1 second )
     * a value of 0 will mark every packet as too old
     * @param checksum checksum setting for defrag engine
     * @param additional_user_key_len number of bytes for the additional key
     * @param hash_malloc allocation function for hash table, not NULL
     * @param hash_realloc reallocation function for hash table, if set to != NULL, reallocation will be enabled
     * @param hash_free free function for hash table, not NULL
     * @param thread_ID id which is passed to the allocation and free functions
     * @param allocation_userptr allocation for defrag engine, not NULL
     * @return returns 0 for success, otherwise for any initialization error
     */
    u8 ipoque_pace2_init_defragment_engine_ext(struct ipoque_detection_module_struct *ipoque_struct,
                                               u64 memory, u32 timeout, enum ipoqe_defrag_checksum_enum checksum,
                                               u32 additional_user_key_len,
                                               pace2_malloc pace2_malloc,
                                               pace_realloc_t hash_realloc,
                                               pace2_free pace2_free,
                                               int thread_ID,
                                               void *allocation_userptr);
#endif


	/************************************************
	 * API and library version                      *
	 ************************************************/

	typedef struct ipoque_pace_api_version {
		/**
		 * API version, increased whenever the API changes
		 */
		u32 api_version;
	} ipoque_pace_api_version_t;

	/**
	 * query API version. The API version will be increased if the API
	 * has been changed, i.e., some public functions or structures have
	 * been changed.
	 *
	 * @return API version structure
	 */
	ipoque_pace_api_version_t ipoque_pace_get_api_version(void);

	typedef struct ipoque_pace_version {
		/**
		 * the major PACE version
		 */
		u16 major_version;

		/**
		 * the minor PACE version
		 */
		u16 minor_version;

		/**
		 * an optional patch version
		 */
		u16 patch_version;

		/**
		 * a string representation "MAJOR.MINOR.PATCH"
		 */
		char version_string[32];

		/**
		 * same as version_string but a build ID may be appended
		 */
		char build_string[32];
	} ipoque_pace_version_t;




#ifdef IPOQUE_PACE_DYNAMIC_UPGRADE

	enum ipoque_dynamic_upgrade_mode_enum {
		IPOQUE_DYNAMIC_UPGRADE_DISABLED = 0,
		IPOQUE_DYNAMIC_UPGRADE_ENABLED
	};

    /**
     * This function will activate the dynamic upgrade feature
     * @param ipoque_struct the detection module
     * @param mode @see ipoque_dynamic_upgrade_mode_enum
     * @param ipoque_dlopen function pointer to POSIX compatible dlopen function
     * @param ipoque_dlsym function pointer to POSIX compatible dlsym function
     * @param ipoque_dlclose function pointer to POSIX compatible dlclose function
     * @param ipoque_malloc function pointer to memory allocator, not NULL
     * @param ipoque_free function pointer to memory free function, not NULL
     * @param thread_ID id which is passed to malloc and free functions
     * @param userptr pointer given to all function pointer function as additional argument
     * @return returns 0 on success, != 0 on error
     * 1: ipoque_struct == NULL
     * 2: POSIX compatible functions not initialized
     * 3: failed to initialize memory
     */
    u8 ipoque_pace2_dynamic_upgrade_set_mode(struct ipoque_detection_module_struct *ipoque_struct,
                                             enum ipoque_dynamic_upgrade_mode_enum mode,
                                             pace2_dlopen pace2_dlopen,
                                             pace2_dlsym pace2_dlsym,
                                             pace2_dlclose pace2_dlclose,
                                             pace2_malloc pace2_malloc, pace2_free pace2_free,
                                             int thread_ID,
                                             void *userptr);

	enum ipoque_dynamic_load_return_enum {
		IPOQUE_DYNAMIC_LOAD_RET_SUCCESSFUL,
		IPOQUE_DYNAMIC_LOAD_RET_FAILURE,
		IPOQUE_DYNAMIC_LOAD_RET_ALLOCATION_FAILED,
		IPOQUE_DYNAMIC_LOAD_RET_LIBRARY_NOT_FOUND,
		IPOQUE_DYNAMIC_LOAD_RET_LIBRARY_INCOMPLETE,
		IPOQUE_DYNAMIC_LOAD_RET_LIBRARY_INITIALIZATION_FAILED,
		IPOQUE_DYNAMIC_LOAD_RET_LIBRARY_NOT_NEWER,
		IPOQUE_DYNAMIC_LOAD_RET_LIBRARY_STATE_MACHINE_TOO_BIG,
		IPOQUE_DYNAMIC_LOAD_RET_NOT_COMPATIBLE
	};

    /**
     * This function will try to load a given library
     * @param ipoque_struct the detection module, not NULL
     * @param filename the filename of the library, point to existing library
     * @param ipoque_malloc function pointer to memory allocator, not NULL
     * @param ipoque_free function pointer to memory free function, not NULL
     * @param thread_ID id which is passed to malloc and free functions
     * @param userptr pointer given to all function pointer function as additional argument
     * @param force_upgrade set to 1 to force upgrade even if given library is not newer, 0 for normal operation with version check
     * @return returns enum ipoque_dynamic_load_return_enum indicating success or failure
     */
    enum ipoque_dynamic_load_return_enum ipoque_pace2_dynamic_upgrade_load_library(struct ipoque_detection_module_struct *ipoque_struct,
                                                                                   const char *filename,
                                                                                   pace2_malloc pace2_malloc,
                                                                                   pace2_free pace2_free,
                                                                                   int thread_ID,
                                                                                   void *userptr, u8 force_upgrade);


    /**
     * This function will use the newly loaded library version from the master instance to update a cloned instance.
     * @param cloned_ipoque_struct the cloned detection module, not NULL
     * @param master_ipoque_struct the master detection module, not NULL
     * @param ipoque_malloc function pointer to memory allocator, not NULL
     * @param ipoque_free function pointer to memory free function, not NULL
     * @param thread_ID id which is passed to malloc and free functions
     * @param userptr pointer given to all function pointer function as additional argument
     * @return returns enum ipoque_dynamic_load_return_enum indicating success or failure
     */
    enum ipoque_dynamic_load_return_enum
            ipoque_pace2_update_cloned_library(struct ipoque_detection_module_struct *cloned_ipoque_struct,
                                               struct ipoque_detection_module_struct *master_ipoque_struct,
                                               pace2_malloc pace2_malloc,
                                               pace2_free pace2_free,
                                               int thread_ID,
                                               void *userptr);


	enum ipoque_dynamic_activate_return_enum {
		IPOQUE_DYNAMIC_ACTIVATE_RET_SUCCESSFUL,
		IPOQUE_DYNAMIC_ACTIVATE_RET_NEWEST_VERSION_ALREADY_RUNNING,
	};

	/**
	 * This function will activate the previously loaded library
	 * @param ipoque_struct the detection module, not NULL
	 * @return returns enum ipoque_dynamic_activate_return_enum indicating success or failure
	 */
	enum ipoque_dynamic_activate_return_enum ipoque_pace_dynamic_upgrade_activate_loaded_library(struct
																								 ipoque_detection_module_struct
																								 *ipoque_struct);

	/**
	 * this function sets the amount of bytes reserved for future
	 * updates in the flow and id data structure.
	 *
	 * The default value is about 10% of the size of the
	 * corresponding structures.
	 * 
	 * This function must be called before enabling the dynamic
	 * upgrade. It will fail if it will be called after enabling the
	 * upgrade.
	 *
	 * @param ipoque_struct the detection module
	 * @param reserve_bytes the number of bytes reserved for dynamic upgrades
	 * @return 0 if values has been set successfully, != 0 otherwise
	 * 1: ipoque_struct == NULL
	 * 2: dynamic upgrade already enabled
	 */
	u8 ipoque_pace_set_dynamic_reserve_space(struct ipoque_detection_module_struct *ipoque_struct, u32 reserve_bytes);

	struct ipoque_free_du_space {
		u32 total_flow_reserve_bytes;
		u32 total_id_reserve_bytes;
		u32 unused_flow_reserve_bytes;
		u32 unused_id_reserve_bytes;
	};

	/**
	 * this function queries the amount of bytes currently still available
	 * for future updates. It takes all loaded libraries into account that
	 * have not been released yet.
	 *
	 * @param ipoque_struct the detection module
	 * @param return_info a pointer to a struct that will be filled with the requested information
	 * @return 0 on success, != 0 on error (return_info is unchanged)
	 */
	u8 ipoque_pace_get_available_dynamic_reserve_space(struct ipoque_detection_module_struct *ipoque_struct,
													   struct ipoque_free_du_space *return_info);

	/**
	 * this function releases the library code from unused libraries
	 * by calling dlclose and freeing some no longer used memory. This
	 * function can be called at any time. If cloned detection modules
	 * are used, this function must be called for each clone first
	 * before calling it for the master instance.
	 *
	 * @param ipoque_struct the detection module
	 * @param ipoque_free function pointer to memory free function, not NULL
	 * @param userptr pointer given to all function pointer function as additional argument
	 * @return returns the number of released libraries or -1 on error
	 */

	int pace2_remove_inactive_libraries( struct ipoque_detection_module_struct * const ipoque_struct,
                                         pace2_free pace2_free,
                                         const int thread_ID,
                                         void * const userptr );

	/**
	 * This function releases all memory from old libraries
	 * considering a given age. There must not exists any flow, or
	 * subscriber that is older than the given age. Due to timestamp
	 * wraparound it is recommended to call this function on a regular
	 * basis (once per day or similar large intervals which are still
	 * at least two times smaller than the wraparound cycle.
	 *
	 * @param ipoque_struct the detection module
	 * @param ipoque_free function pointer to memory free function, not NULL
	 * @param userptr pointer given to all function pointer function as additional argument
	 * @param age the timestamp of the oldest flow or subscriber. Flows/subscriber older than this
	 *        timestamp can no longer be handled.
	 * @return returns the number of released libraries or -1 on error
	 */
	int pace2_release_memory_from_old_libraries( struct ipoque_detection_module_struct * const ipoque_struct,
                                                 pace2_free pace2_free,
                                                 const int thread_ID,
                                                 void * const userptr,
                                                 const IPOQUE_TIMESTAMP_COUNTER_SIZE age );

#ifdef __KERNEL__
	typedef void *(*ipoque_pace_lookup_function_t) (const char *symbol_name, void *user_ptr);

	int ipoque_pace_register_function_lookup(ipoque_pace_lookup_function_t f,
											 void *user_ptr);
	
	/**
	 * register one function that is called if a new upgrade module was loaded and registered
	 *
	 * The callback takes the version of the loaded module as argument.
	 *
	 * @param cb_funct pointer to the callback function
	 * @return 0 if callback registered, -1 on error
	 */
	int ipoque_pace_attach_function_lookup_change_callback(void (*cb_funct)(ipoque_pace_version_t *version));
	
	/**
	 * detach a callback function
	 * @return 0 if okay, -1 on error
	 */
	int ipoque_pace_detach_function_lookup_change_callback(void);
#endif

#endif




#ifdef IPOQUE_CUSTOM_DEFINED_PROTOCOLS_2_0
	enum ipoque_cdp_return {
		IPOQUE_CDP_EXCLUDE = 0,
		IPOQUE_CDP_MATCH = 1,
		IPOQUE_CDP_MATCH_BUT_NEED_NEXT_PACKET = 2,
		IPOQUE_CDP_NEED_NEXT_PACKET = 3
	};

	/**
	 * This is the prototype for protocol detection callbacks
	 *
	 * @param ipoque_struct the detection module
	 * @param userptr the user pointer set when the corresponding protocol has been registered
	 * @param flow_area the pointer to the dedicated flow area (the size is as requested at registration), might be NULL
	 * @param src_area the pointer to the dedicated subscriber area of the source of the packet (the size is as requested at registration), can be NULL
	 * @param dst_area the pointer to the dedicated subscriber area of the destination of the packet (the size is as requested at registration), can be NULL
	 * @return indicates if the protocol has matched, excluded or more packets are required
	 */
	typedef enum ipoque_cdp_return (*ipoque_cdp_detection_function_t) (struct ipoque_detection_module_struct *
																	   ipoque_struct, void *userptr, void *flow_area,
																	   void *src_area, void *dst_area);
    /**
     * this function sets the number of CDPs available
     * for registration.
     *
     * This function must be called AFTER the initialization of the
     * detection module but BEFORE querying information about flow and
     * subscriber sizes
     * (ipoque_detection_get_sizeof_dynamic_ipoque_flow_struct...)
     * since the value returned by this function depend on this
     * setting.
     *
     * Also, this function can only be called once, it is not
     * possible to change this value later on.
     *
     * @param ipoque_struct the detection module, can be NULL
     * @param number_of_protocols the number of protocols, not 0
     * @param ipoque_malloc a pointer to an allocator function, not NULL
     * @param ipoque_free a pointer to a deallocator function, not NULL
     * @param thread_ID id which is passed to malloc and free functions
     * @param a user pointer for the memory function
     * @return 0 for success, != 0 in case of errors
     */
    u8 ipoque_pace_cdp_set_number_of_protocols(struct ipoque_detection_module_struct *ipoque_struct,
                                               u32 number_of_protocols,
                                               pace2_malloc pace2_malloc,
                                               pace2_free pace2_free,
                                               int thread_ID, void *userptr);

	/**
	 * This function returns the number of registered CDPs.
	 *
	 * @param ipoque_struct the detection module, not NULL
	 * @return number of registered CDPs
	 *
	 * works with IPOQUE_PACE_DYNAMIC_UPGRADE
	 */
	u32 ipoque_pace_cdp_get_number_of_protocols(struct ipoque_detection_module_struct * ipoque_struct);


	/**
	 * returns the CDP excluded bitmask for the flow of the last processed packet.
	 *
	 * @param ipoque_struct the detection module, can be NULL but function just returns
	 * @return pointer to the bitmask or NULL in case of errors
     *
     * works with IPOQUE_PACE_DYNAMIC_UPGRADE
	 */
    const u32 *ipoque_pace_cdp_get_excluded_bm( struct ipoque_detection_module_struct * const ipoque_struct );
#endif

	/**
	 * this function sets the protocol offset used when returning CDP
	 * protocol IDs.  The default value is 0 which means the CDP
	 * counting starts at LAST_IMPLEMENTED_PROTOCOL+1. By setting the
	 * offset it is possible to have constant protocol IDs even in
	 * case new native protocols have been added.
	 * 
	 * @param ipoque_struct the detection module, not NULL
	 * @param start_offset the start offset for counting
	 *        CDPs. Possible values are zero for start counting at
	 *        LAST_IMPLEMENTED_PROTOCOL+1 or any value >
	 *        LAST_IMPLEMENTED_PROTOCOL and value < 65535 - CDP.NUMBER_OF_PROTOCOLS.
	 * @return 0 for success, != 0 in case of errors
	 */
	u8 ipoque_pace_cdp_set_offset(struct ipoque_detection_module_struct *ipoque_struct, u32 start_offset);

#ifdef IPOQUE_CUSTOM_DEFINED_PROTOCOLS_2_0
	enum ipoque_l3_type {
		IPOQUE_L3_UNKNOWN,
		IPOQUE_L3_IPV4,
		IPOQUE_L3_IPV6
	};

	struct ipoque_cdp_l3_info {
		const void *l3_start;	/* the start of the layer 3 payload */
		u16 l3_length;			/* the length of the layer 3 payload (including all other layers) */
		enum ipoque_l3_type l3_type;	/* the type of the layer 3 header */

		/* this struct may grow in later versions but the previous fields will not change */
	};

	struct ipoque_cdp_l4_info {
		const void *l4_start;	/* the start of the layer 4 payload */
		u16 l4_length;			/* the length of the layer 4 payload (including all other layers) */
		u8 l4_type;				/* the type of the layer 4 header (the IP protocol type) */

		/* this struct may grow in later versions but the previous fields will not change */
	};

	struct ipoque_cdp_l7_info {
		const void *l7_start;	/* the start of the layer 7 payload */
		u16 l7_length;			/* the length of the layer 7 payload */

		/* this struct may grow in later versions but the previous fields will not change */
	};

	struct ipoque_cdp_generic_info {
		u32 protocol;			/* the current detected protocol ID */
		u16 flow_packet_counter[2];	/* the packet counters for both directions */
		u8 packet_direction;	/* the packet direction (0 or 1) */
		u8 initial_packet_direction;	/* the direction of the first packet of the flow (0 or 1) */

		/* this struct may grow in later versions but the previous fields will not change */
	};

	/**
	 * this function can be used in CDP to query the layer 3 information.
	 *
	 * @param ipoque_struct the detection module, can be NULL
	 * @return a pointer to a static area containing the layer 3 information
	 */
	const struct ipoque_cdp_l3_info *ipoque_pace_cdp_get_l3_info(struct ipoque_detection_module_struct *ipoque_struct);

	/**
	 * this function can be used in CDP to query the layer 4 information.
	 *
	 * @param ipoque_struct the detection module, can be NULL
	 * @return a pointer to a static area containing the layer 4 information
	 */
	const struct ipoque_cdp_l4_info *ipoque_pace_cdp_get_l4_info(struct ipoque_detection_module_struct *ipoque_struct);

	/**
	 * this function can be used in CDP to query the layer 7 information.
	 *
	 * @param ipoque_struct the detection module, can be NULL
	 * @return a pointer to a static area containing the layer 7 information
	 */
	const struct ipoque_cdp_l7_info *ipoque_pace_cdp_get_l7_info(struct ipoque_detection_module_struct *ipoque_struct);

	/**
	 * this function can be used in CDP to query generic flow information.
	 *
	 * @param ipoque_struct the detection module, can be NULL
	 * @return a pointer to a static area containing the generic information
	 */
	const struct ipoque_cdp_generic_info *ipoque_pace_cdp_get_generic_info(struct ipoque_detection_module_struct
																		   *ipoque_struct);
#endif



	/**
	 * the statistic structure for the Session ID tracker
	 */
	struct ipoque_pace_sit_stats {
		/**
		 * number of session ID inserts
		 */
		u64 id_inserts;

		/**
		 * number of successful ID lookup
		 */
		u64 id_lookup_successful;

		/**
		 * number of failed ID lookups
		 */
		u64 id_lookup_failed;

		/**
		 * this is the maximum number of session IDs that can be stored
		 */
		unsigned long maximum_number_of_elements;

		/**
		 * this is the number of currently stored session IDs
		 */
		unsigned long currently_used_elements;

		/**
		 * this is the timestamp of the oldest entry in the session ID
		 * table. It gives a hint about which period of time is
		 * covered by the session ID tracker.
		 */
		IPOQUE_TIMESTAMP_COUNTER_SIZE ts_of_oldest_entry;
	};



	enum ipoque_client_server_indication_packet_type {
		IPOQUE_DIRECTION_UNKNOWN = 0,       /**< packet direction could not be detected */
		IPOQUE_DIRECTION_NOT_YET_DECIDED,   /**< packet direction is not yet decided */
		IPOQUE_CLIENT_TO_SERVER,            /**< packet goes from client to server */
		IPOQUE_SERVER_TO_CLIENT,            /**< packet goes from server to client */
		IPOQUE_CLIENT_TO_CLIENT,            /**< packet is between two clients */
		IPOQUE_SERVER_TO_SERVER             /**< packet is between two servers */
	};

	enum ipoque_client_server_indication_host_type {
		IPOQUE_HOST_TYPE_UNKNOWN = 0,       /**< it is not known whether host is client or server */
		IPOQUE_HOST_IS_SERVER,              /**< the host is mainly used as a server */
		IPOQUE_HOST_IS_CLIENT,              /**< the host is a client */
	};

	struct ipoque_pace_client_server_indication_host_status {
		enum ipoque_client_server_indication_host_type host_type;     /**< host type enum */
		int percentage_of_client_connections;                         /**< percentage of client connections, 0 means no client connection or value not known,
																		 anything between 1 and 100 gives the rate of client connections over server connections.
																		 The value will change over time. */
	};


	enum ipoque_fastpath_state {
		IPOQUE_FP_NO_PACKET_NEEDED,                               /**< no packet from this flow is needed anymore */
		IPOQUE_FP_NEXT_PACKET_NEEDED,                             /**< the next packet of this flow is needed */
		IPOQUE_FP_NEXT_PACKET_WITH_CONSTRAINT,                    /**< the next packet only with additional constraint (direction and/or time) */
	};

	enum ipoque_fastpath_direction_constraint {
		IPOQUE_FP_ANY_DIRECTION,                                  /**< no direction limit applies */
		IPOQUE_FP_NEXT_PAYLOAD_PACKET_SAME_DIRECTION,             /**< the next packet with payload for the current direction is needed */
		IPOQUE_FP_NEXT_PAYLOAD_PACKET_OTHER_DIRECTION,            /**< the next packet with payload for the other direction is needed */
	};

	struct ipoque_fastpath_information
	{
		enum ipoque_fastpath_state state;                         /**< the state of the fastpath stating whether additional packets are required */
		u8 skip_time_set;                                         /**< 1 if a time is set until all packets can be skipped, 0 if no time limit applies */
		u32 skip_until_time;                                      /**< time until all packets can be skipped for the state IPOQUE_FP_NEXT_PACKET_WITH_CONSTRAINT */
		enum ipoque_fastpath_direction_constraint direction;      /**< only packets with given direction */
	};

	/**
	 * this function returns information about whether packets of the same flow as the last packet are required by PACE to
	 * correctly identify traffic and manage protocol changes within flows.
	 * @param ipoque_struct the detection module, not NULL
	 *
	 * @param fp_information a pointer to a structure which will be filled with the available information, not NULL.
	 * @return 0 if successful, != 0 in case of an error
	 */
	u8 ipoque_pace_get_fastpath_information(struct ipoque_detection_module_struct *ipoque_struct,
											struct ipoque_fastpath_information *fp_information);

	enum ipoque_flow_timeout_class {
		IPOQUE_MEDIUM_FLOW_TIMEOUT = 0,
		IPOQUE_SHORT_FLOW_TIMEOUT,
		IPOQUE_LARGE_FLOW_TIMEOUT
	};




    typedef struct ipoque_pace_license_information {
        /**
         * @brief init_error_code internal initialisation error code
         */
        u32 init_error_code;
        /**
         * @brief init_error_reason verbose initialisation error string
         */
        const char *init_error_reason;
        /**
         * @brief load_error_code internal license loading error code
         */
        u32 load_error_code;
        /**
         * @brief load_error_reason verbose license loading error string
         */
        const char *load_error_reason;
        /**
         * @brief validation_error_code internal validation error code
         */
        u32 validation_error_code;
        /**
         * @brief validation_error_reason verbose validation error string
         */
        const char *validation_error_reason;
        /**
         * @brief limitation_error_code internal limitation error code
         */
        u32 limitation_error_code;
        /**
         * @brief limitation_error_reason verbose limitation error string
         */
        const char *limitation_error_reason;
        /**
         * @brief no_of_mac_addresses_found number of valid mac addresses on the system
         */
        u32 no_of_mac_addresses_found;
        /**
         * @brief current_percentage_bandwidth_limit_usage percentage value which shows the current bandwidth in relation to the bandwidth limit
         */
        u32 current_percentage_bandwidth_limit_usage;

    } ipoque_pace_license_information_t;


#ifdef IPOQUE_SUPPORT_OS_DETECTION
	/**
	 * These are the currently supported operating systems for the OS
	 * detection
	 */
	enum ipoque_os_type {
        /**
         * @brief IPOQUE_OS_NOT_YET_DETECTED indicates that the OS
         * detection is still active but no decision has been made so
         * far. More packets must be analyzed.
         */
		IPOQUE_OS_NOT_YET_DETECTED = 0,

        /**
         * @brief IPOQUE_OS_NOT_DETECTED indicates that the OS
         * detection is finished and the operating system could not be
         * found for the current flow.
         */
		IPOQUE_OS_NOT_DETECTED,

        /**
         * @brief IPOQUE_OS_OTHER is used when an OS information could
         * be found but the actual operating system is not
         * known to PACE.
         */
		IPOQUE_OS_OTHER,
		IPOQUE_OS_WINDOWS,
		IPOQUE_OS_LINUX,
		IPOQUE_OS_MACOS,
		IPOQUE_OS_IOS,
		IPOQUE_OS_SYMBIAN,
		IPOQUE_OS_ANDROID,
		IPOQUE_OS_BLACKBERRY,
		IPOQUE_OS_WINDOWS_MOBILE,
        IPOQUE_OS_WINDOWS_PHONE,

        /* must be last entry */
        IPOQUE_NUMBER_OF_OS
	};

	/**
	 * This structure contains the result of the OS detection.
	 */
	struct ipoque_os_detection_result {
		enum ipoque_os_type os_type;  /**< the OS type is always set for all packets to one of the supported values */
		const u8 *os_version_string;  /**< the version is available only once at the packet where the version has been found.
										 Otherwise it will be NULL */
		u16 os_version_string_len;    /**< the length will set if the version is available, otherwise it will be 0 */
	};

	/**
	 * query the OS detection result for the last processed packet
	 *
	 * @param ipoque_struct the detection module
	 * @return a pointer to a static structure filled with the OS result, NULL in case of an error
	 *
	 * works with IPOQUE_PACE_DYNAMIC_UPGRADE
	 */
	const struct ipoque_os_detection_result *ipoque_pace_get_os_detection_result(struct ipoque_detection_module_struct *ipoque_struct);

	/**
	 * query the name of an OS type value
	 *
	 * @param ipoque_struct the detection module
	 * @return a pointer to a static string with the name of the given OS type. Returns empty string for wrong type.
	 *
	 * works with IPOQUE_PACE_DYNAMIC_UPGRADE
	 */
	const char *ipoque_pace_get_name_of_os_type(struct ipoque_detection_module_struct *ipoque_struct, enum ipoque_os_type os_type);

	enum ipoque_os_detection_mode {
		IPOQUE_OS_DETECTION_DISABLED = 0,
		IPOQUE_OS_DETECTION_ENABLED
	};

	/**
	 * This function enables or disables the OS detection
	 * default is DISABLED
	 * @param ipoque_struct the detection module, not NULL
	 * @param param 1 ENABLES and 0 DISABLES the OS detection, other values have no effect
	 *
	 * works with IPOQUE_PACE_DYNAMIC_UPGRADE
	 */
	void ipoque_pace_set_os_detection_mode(struct ipoque_detection_module_struct *ipoque_struct,
										   enum ipoque_os_detection_mode param);

	/**
	 * This structure contains the result of the nat detection.
	 */
	struct ipoque_nat_detection_result {
		enum ipoque_os_type main_os;  /**< the primary os used */
		u8 nat_flag;                   /**< indicates whether nat is detected for this subscriber or not */
	};

	enum ipoque_nat_detection_mode {
		IPOQUE_NAT_DETECTION_DISABLED = 0,
		IPOQUE_NAT_DETECTION_ENABLED
	};

    /**
     * This function enables or disables the nat detection.
     * OS detection and client server indication must be enabled before
     * calling this. Function must be called AFTER the initialization of the
     * detection module but BEFORE querying information about subscriber sizes.
     *
     * default is IPOQUE_NAT_DETECTION_DISABLED
     * @param ipoque_struct the detection module, not NULL
     * @param mode          either IPOQUE_NAT_DETECTION_ENABLED or IPOQUE_NAT_DETECTION_DISABLED
     * @param pace2_malloc  function pointer to a memory allocator
     * @param pace2_free    function pointer to a memory free function
     * @param thread_ID     id which is passed to malloc and free
     * @return 0 on success
     *         1 os detection is not enabled
     *         2 memory allocation failed
     * works with IPOQUE_PACE_DYNAMIC_UPGRADE
     */
    u8 ipoque_pace_set_nat_detection_mode(struct ipoque_detection_module_struct * const ipoque_struct,
                                          const enum ipoque_nat_detection_mode mode,
                                          pace2_malloc pace2_malloc,
                                          pace2_free pace2_free,
                                          int thread_ID);

	/**
	 * This function resets the internal nat detection state for the given
     * subscriber and returns the last values.
	 * @param ipoque_struct the detection module, not NULL
     * @param subscriber the subscriber to get and reset the statistics for
     * @return result structure pointer or NULL on error
	 * works with IPOQUE_PACE_DYNAMIC_UPGRADE
	 */
    const struct ipoque_nat_detection_result *ipoque_pace_reset_nat_detection_state(struct ipoque_detection_module_struct * const ipoque_struct,
                                                                                    void * subscriber);

	/**
	 * This function retrieves the nat detection result for the given
     * subscriber.
	 * @param ipoque_struct the detection module, not NULL
     * @param subscriber the subscriber to get the statistics for
     * @return result structure pointer or NULL on error
	 * works with IPOQUE_PACE_DYNAMIC_UPGRADE
	 */
    const struct ipoque_nat_detection_result *ipoque_pace_get_nat_detection_result(struct ipoque_detection_module_struct * const ipoque_struct,
                                                                                   void * subscriber);

#endif // IPOQUE_SUPPORT_OS_DETECTION

    /**
     * This function initializes the content delivery network (cdn) caching.
     * The cache will be initialized with a 1 MB large hash table to cache host addresses.
     * At the moment, the netflix detection is the only one which uses the cache.
     * The function has to be called after the initialization of the detection module.
     *
     * @param[in] ipoque_struct     the detection module, not NULL
     * @param[in] pace2_malloc       function pointer to a memory allocator
     * @param[in] pace2_free         function pointer to a memory free function
     * @param[in] thread_ID id which is passed to malloc and free
     * @return 0    initialization was successful
     *         1    initialization of the hash table failed
     */
    u8 ipoque_pace_init_cdn_caching(struct ipoque_detection_module_struct * const ipoque_struct,
                                    pace2_malloc pace2_malloc,
                                    pace2_free pace2_free,
                                    int thread_ID);

/* END PUBLIC FUNCTIONS, API DOCUMENTATION IN MANPAGES ONLY !! */
#ifdef __cplusplus
}
#endif // __cplusplus
#endif // __IPQ_PUBLIC_FUNCTIONS_H__
