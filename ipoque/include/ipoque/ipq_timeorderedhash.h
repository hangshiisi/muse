/* written by klaus degner, ipoque GmbH
 * klaus.degner@ipoque.com
 */

#ifndef __IPOQUE_API_INCLUDE_FILE__
#error CANNOT INCLUDE THIS .H FILE, INCLUDE IPQ_API.H
#endif

#ifndef __IPQ_TIMEORDEREDHASH_H__
#define __IPQ_TIMEORDEREDHASH_H__

#ifdef __cplusplus
extern "C" {
#endif

	/* obsolete define, this feature is always available. This defines is only here to not break old code */
#define IPOQUE_TOH_MULTI_TIMEOUT

/** basic 5 tuple which is used for connection tracking
 */

	typedef struct ipoque_unique_flow_struct {
		u32 lower_ip;
					/**< the lower ip address of the two ip addresses */
		u32 upper_ip;
					/**< the upper ip address of the two ip addresses */
		u16 lower_port;
					/**< the port of the lower ip address */
		u16 upper_port;
					/**< the port of the upper ip address */
		u32 protocol;
					/**< the protocol, for alignment reason, protocol is 32 bit, not 8 bit */
	} ipoque_unique_flow_struct_t;

/** macro to compare 2 IPv6 addresses with each other to identify the "smaller" IPv6 address  */
#define IPOQUE_COMPARE_IPV6_ADDRESS_STRUCTS(x,y)  \
  ((((u64 *)(x))[0]) < (((u64 *)(y))[0]) || ( (((u64 *)(x))[0]) == (((u64 *)(y))[0]) && (((u64 *)(x))[1]) < (((u64 *)(y))[1])) )

/** definition for the structure of the timeorderedhash table */
	typedef struct timeorderedhash timeorderedhash_t;

/** definition of the infinite timeout */
#define IPQ_TOH_TIMEOUT_INFINITE	0xFFFFFFFF


/** deprecated hash create function, please use ipoque_to_hash_create2
 * @see ipoque_to_hash_create2
 */

/** Time ordered hash create function
 * This function creates a time ordered hash. The Hash table will be allocated by this call. As long as no hash resize is allowed, the hash table allocates the memory only by this call.
 * @param memory the allocated amount of bytes which can be used by the hash create function. It is possible that a small amount more bytes are allocated.
 * To determine the amount of memory needed for a certain number of elements use ipoque_to_calculate_hash_size.
 * When the memory given is below the size of an element the allocation will fail and the function returns NULL.
 * To remove the hash table, ipoque_to_hash_destroy() has to be called.
 * @param UserBufferSize size of data which is stored per key
 * @param UniqueBufferSize size of the key, must be a multiple of 4
 * @param timeout the timeout for every element, can be IPQ_TOH_TIMEOUT_INFINITE for infinite timeouts
 * @param timeout_callback callback function. Function will be called for every element removed from the hash table because of timeout, overflow, or explicit removal.
 *        The parameters are the last access time of the element, a pointer to the key, the data and a global user pointer. Can be NULL
 * @param timeout_userptr The userptr which is passed to the callback function
 * @param ipq_malloc Allocator function, including the allocation user-pointer, not NULL
 * @param ipq_free Freeing function with the allocation user-pinter, not NULL
 * @param allocation_userptr user pointer for the allocation and free function.
 * @return The initialized pointer to the hash table. It returns NULL for an error ( for example a failed memory allocation )
 */
	struct timeorderedhash *ipoque_to_hash_create2(unsigned long memory,
												   u32 UserBufferSize,
												   u32 UniqueBufferSize,
												   IPOQUE_TIMESTAMP_COUNTER_SIZE timeout, void (*timeout_callback)
												    (IPOQUE_TIMESTAMP_COUNTER_SIZE lasttime, u8 * unique_buffer,
													 u8 * user_data, void *userptr), void *timeout_userptr,
												   void *(*ipq_malloc) (unsigned long size, void *userptr),
												   void (*ipq_free) (void *ptr, void *userptr),
												   void *allocation_userptr);

    /** Time ordered hash create function
     * This function creates a time ordered hash. The Hash table will be allocated by this call. As long as no hash resize is allowed, the hash table allocates the memory only by this call.
     * @param memory the allocated amount of bytes which can be used by the hash create function. It is possible that a small amount more bytes are allocated.
     * To determine the amount of memory needed for a certain number of elements use ipoque_to_calculate_hash_size.
     * When the memory given is below the size of an element the allocation will fail and the function returns NULL.
     * To remove the hash table, ipoque_to_hash_destroy() has to be called.
     * @param UserBufferSize size of data which is stored per key
     * @param UniqueBufferSize size of the key, must be a multiple of 4
     * @param timeout the timeout for every element, can be IPQ_TOH_TIMEOUT_INFINITE for infinite timeouts
     * @param timeout_callback callback function. Function will be called for every element removed from the hash table because of timeout, overflow, or explicit removal.
     *        The parameters are the last access time of the element, a pointer to the key, the data and a global user pointer. Can be NULL
     * @param timeout_userptr The userptr which is passed to the callback function
     * @param ipq_malloc Allocator function, including the allocation user-pointer, not NULL
     * @param ipq_free Freeing function with the allocation user-pinter, not NULL
     * @param thread_ID thread ID passed to the allocation and free functions
     * @param allocation_userptr user pointer for the allocation and free function.
     * @return The initialized pointer to the hash table. It returns NULL for an error ( for example a failed memory allocation )
     */
    struct timeorderedhash *pace2_toh_create(unsigned long memory,
                                             u32 UserBufferSize,
                                             u32 UniqueBufferSize,
                                             IPOQUE_TIMESTAMP_COUNTER_SIZE timeout,
                                             void (*timeout_callback)
                                             (IPOQUE_TIMESTAMP_COUNTER_SIZE lasttime, u8 * unique_buffer,
                                              u8 * user_data, void *userptr),
                                             void *timeout_userptr,
                                             pace2_malloc pace2_malloc,
                                             pace2_free pace2_free,
                                             int thread_ID,
                                             void *allocation_userptr);

/* hash table lookup
 * @param toh the pointer to the hash table, not NULL
 * @param unique the pointer to the key, not NULL
 * @param last_access_ts a pointer to a variable where the successful lookup should store the last insert call for this element, not NULL
 * @return returns the pointer to the user data, NULL if the lookup has failed
 */
	void *ipoque_to_hash_lookup_ts(struct timeorderedhash *toh, const u8 * unique,
								   IPOQUE_TIMESTAMP_COUNTER_SIZE * last_access_ts);

/* hash table lookup, wrapper for lookups without using the access time stamp
 * @param toh the pointer to the hash table, not NULL
 * @param unique the pointer to the key, not NULL
 * @return returns the pointer to the user data, NULL if the lookup has failed
 */

	static inline void *ipoque_to_hash_lookup(struct timeorderedhash *toh, const u8 * unique) {
		IPOQUE_TIMESTAMP_COUNTER_SIZE ts;
		 return ipoque_to_hash_lookup_ts(toh, unique, &ts);
	}

/*
 * update timestamp for an element retrieved by a lookup call
 * @param toh the pointer to the hash table, not NULL
 * @param user_data pointer to user data
 * @return 0 on success, !0 on error
 */
	u32 ipoque_to_hash_update_ts_of_element(struct timeorderedhash *toh, void *user_data);

/**
 * hash table insert/update operation
 *
 * In default insertion mode this operation cannot fail because if the
 * hash table is full, the oldest element is deleted.
 *
 * In case of an insert of an already inserted element its timestamp
 * will get updated with value of the last call of
 * ipoque_to_hash_set_timestamp().
 *
 * The call may return NULL if the insertion mode is set to
 * INSERT_FAILS_IF_FULL and not space is available in the hash table
 * (and the optional resize fails).
 *
 * @param toh the pointer to the hash table, not NULL
 * @param unique the pointer to the key, not NULL
 * @param new pointer to an u8, not NULL. This will be set to != 0 when the insert has created a new entry in the hash table. The value is undefined if a NULL pointer is returned.
 * @return returns the pointer to the user data.
 * @see ipoque_to_hash_set_insertion_mode
 */
	void *ipoque_to_hash_insert(struct timeorderedhash *toh, const u8 * unique, u8 * new_entry);

/** removes one element from the hash table. If a callback is initialized, it will be called during this call.
 * @param toh the pointer to the hash table, not NULL
 * @param unique the pointer to the key, not NULL
 * @return returns nothing
 */
	void ipoque_to_hash_delete(struct timeorderedhash *toh, const u8 * unique);



/** frees all memory which has been allocated for a hash table
 * It does NOT clean up all elements, please use ipoque_to_hash_clear if required
 * @param toh the pointer to the hash table, can be NULL
 * @see ipoque_to_hash_clear
 */
	void ipoque_to_hash_destroy2(struct timeorderedhash *toh);


/** set the time stamp of the hash table. It should be called before any insert operation with the timestamp of the inserted element.
 * Be aware that the time stamp MUST grow monotonic. The time stamp can wrap around.
 * @param toh The pointer to the hash table, not NULL
 * @param timestamp The current time stamp of the hash table.
 * @see ipoque_to_hash_clear
 */
	void ipoque_to_hash_set_timestamp(struct timeorderedhash *toh, IPOQUE_TIMESTAMP_COUNTER_SIZE timestamp);

/** set or change the timeout of a timeout queue
 * @param toh The pointer to the hash table, NULL returns
 * @param timeout The current time stamp of the hash table. Can be IPQ_TOH_TIMEOUT_INFINITE for infinite timeouts.
 * @param queue the affected queue. Multi queues must be enabled if the queue is not 0
 * @return returns 0 for success or not 0 for an error
 */
	u8 ipoque_to_hash_set_timeout_ext(struct timeorderedhash *toh, IPOQUE_TIMESTAMP_COUNTER_SIZE timeout, u32 queue);

/** get the timestamp of a timeout queue
 * @param toh The pointer to the hash table, NULL returns 0
 * @param queue the affected queue. Multi queues must be enabled if the queue is not 0
 * @return returns the timeout.
 */
	IPOQUE_TIMESTAMP_COUNTER_SIZE ipoque_to_hash_get_timeout_ext(struct timeorderedhash *toh, u32 queue);

/** set or change the timeout of the default timeout queue
 * @param toh The pointer to the hash table, NULL returns 0
 * @param timeout The current time stamp of the hash table. Can be IPQ_TOH_TIMEOUT_INFINITE for infinite timeouts.
 * @return returns 0 for succes or not 0 for an error
 */
	static inline u8 ipoque_to_hash_set_timeout(struct timeorderedhash *toh, IPOQUE_TIMESTAMP_COUNTER_SIZE timestamp) {
		return ipoque_to_hash_set_timeout_ext(toh, timestamp, 0);
	}

/** get the timestamp of the default timeout queue
 * @param toh The pointer to the hash table, NULL returns 0
 * @param queue the affected queue. Multi queues must be enabled if the queue is not 0
 * @return returns the timeout.
 */
	static inline IPOQUE_TIMESTAMP_COUNTER_SIZE ipoque_to_hash_get_timeout(struct timeorderedhash *toh) {
		return ipoque_to_hash_get_timeout_ext(toh, 0);
	}


/** set the callback function called for removed elements due to timeout, overflow, or explicit removal.
 * @param toh The pointer to the hash table, not NULL
 * @param timeout_callback callback function. The parameters are the last access time of the element, a pointer to the key, the data and a global user pointer. Can be NULL
 * @param timeout_userptr The userptr which is passed to the callback function
 * @return returns nothing
 */
	void ipoque_to_hash_set_timeout_callback(struct timeorderedhash *toh, void (*timeout_callback)
											  (IPOQUE_TIMESTAMP_COUNTER_SIZE
											   lasttime, u8 * unique_buffer, u8 * user_data, void *userptr),
											 void *userptr);


/** enum listing reasons why an item was removed from the toh */
	typedef enum toh_removal_reason {
		TOH_DELETED,			/**< item was removed due to requested delete */
		TOH_TIMEDOUT,			/**< item was removed due to timeout */
		TOH_OVERFLOWED			/**< item was removed as oldest entry of a full toh */
	} toh_removal_reason_t;

/** get the reason for the last remove operation. It can be a timeout, a delete or an hash table overflow. The result is undefined if called before any element has been removed.
 * @param toh The pointer to the hash table, not NULL
 * @return returns the timeout reason
 */
	enum toh_removal_reason ipoque_to_hash_get_last_removal_reason(struct timeorderedhash *toh);

/** Delete all entries from the hash table. If a callback is given, it will be called for every element.
 * @param toh The pointer to the hash table, not NULL
 * @return returns nothing
 */
	void ipoque_to_hash_clear(struct timeorderedhash *toh);

/** dump the hash table for each inserted element
 * @param toh The pointer to the hash table, not NULL
 * @param callback callback function this dump. It is called for each element. If callback return != 0, the element will be deleted (nothing happens otherwise), not NULL
 * @param user_data A user defined pointer that is passed to the callback function
 * @return returns nothing
 */
	void ipoque_to_hash_foreach(struct timeorderedhash *toh,
								u8(*callback) (u8 * unique_buffer,
											   u8 * user_buffer,
											   IPOQUE_TIMESTAMP_COUNTER_SIZE
											   last_timestamp, void *user_data), void *user_data);
/** Function to activate an automatic hash resize operation. This will automatically resize the hash table when the hash table is full.
 * @param toh The pointer to the hash table, not NULL
 * @param ipq_realloc Reallocator function, including the allocation user-pointer. This function will be called in a reallocation event. It uses the useptr from the function ipoque_to_hash_create2, not NULL
 * @see ipoque_to_hash_create2
 */
	void ipoque_to_hash_enable_hash_resize(struct timeorderedhash *toh,
										   void *(*ipq_realloc) (void *ptr, unsigned long size, void *userptr));

/** If hash resize is enabled, this function ensures that the given
 * number of elements can be inserted. The hash table will be resized
 * if necessary or, if the resize fails, the oldest elements are
 * removed until enough space is available.
 *
 * If hash resize is disabled, this function does nothing.
 *
 * Since reallocations might move the memory area used for the user
 * data, pointers might be invalidated during multiple inserts.  For
 * example, consider a function which does two inserts into a hash
 * table and uses both pointer afterwards. In this case, this function
 * must be called before the two inserts with an argument of "2".
 *
 * @param toh The pointer to the hash table, not NULL
 * @param min_free_elements number of elements which must be available before the next resize operation
 */
	void ipoque_to_hash_check_hash_resize(struct timeorderedhash *toh, u32 min_free_elements);

/** this function will decapsulate the IPv4 header and build the 5 tuple from the inner header. The maximum tunnel decapsulation level is used from the ipoque detection module struct
 * @param ipoque_struct main ipoque detection struct, NULL allowed
 * @param iphdr pointer to the ipv4 header, not NULL
 * @param ipsize accessable bytes from the iphdr
 * @param unique_flow pointer to the 5 tuple structure. will be set by this call, not NULL
 * @return returns 0 for success and != 0 if an error happened
 */
	u8 ipoque_build_ipv4_decapsulate_unique(struct
											ipoque_detection_module_struct
											*ipoque_struct, const void
											*iphdr, u16 ipsize, struct ipoque_unique_flow_struct *unique_flow);

/** this function will decapsulate the IPv4 header and do an insert operation on a hash table with the 5 tuple. The maximum tunnel decapsulation level is used from the ipoque detection module struct
 *
 * if the hash table allows inserts to fail, the return value can be NULL.
 *
 * @param ipoque_struct main ipoque detection struct, NULL allowed
 * @param toh the hash table, not NULL
 * @param iphdr pointer to the ipv4 header, not NULL
 * @param ipsize accessable bytes from the iphdr
 * @param new_connection set to != 0 for a new element
 * @return returns a pointer to the flow (may be NULL if hash insert or flow key building fails)
 */
	void *ipoque_get_current_flow_decapsulate(struct
											  ipoque_detection_module_struct
											  *ipoque_struct, struct
											  timeorderedhash
											  *toh, const void
											  *iphdr, u16 ipsize, u8 * new_connection);


/** DEPRECATED, DO NOT USE
 * this function does an insert operation on a hash table with the 5 tuple without tunnel decapsulation.
 * @param ipoque_struct main ipoque detection struct
 * @param toh the hash table
 * @param iphdr pointer to the ipv4 header
 * @param ipsize accessable bytes from the iphdr
 * @return returns 0 for success and != 0 if an error happened
 */
	void *ipoque_get_current_flow(struct timeorderedhash *toh, const void *iphdr, u16 l3len)
		__attribute__ ((deprecated));



#ifdef IPOQUE_DETECTION_SUPPORT_IPV6
/** this function will decapsulate the IPv4 or IPv6 header and build the 5 tuple from the inner header. The maximum tunnel decapsulation level is used from the ipoque detection module struct
 * @param ipoque_struct main ipoque detection struct, NULL allowed
 * @param iphdr pointer to the ipv4 header, not NULL
 * @param ipsize accessable bytes from the iphdr, when NULL returns 1
 * @param unique_flow pointer to the 5 tuple structure. will be set by this call
 * @return returns 0 for success and != 0 if an error happened
 */
	u8 ipoque_build_ipv4_6_decapsulate_unique(struct
											  ipoque_detection_module_struct
											  *ipoque_struct, const void
											  *ipv4_ptr, u16 ipsize,
											  struct ipoque_unique_flow_ipv4_and_6_struct *unique_flow);

/** this function will decapsulate the IPv4 or IPv6 header and do an insert operation on a hash table with the 5 tuple. The maximum tunnel decapsulation level is used from the ipoque detection module struct.
 * Additionally the pointer to the flow is returned.
 *
 * if the hash table allows inserts to fail, the return value can be NULL.
 *
 * @param ipoque_struct main ipoque detection struct, NULL allowed
 * @param toh the hash table, not NULL
 * @param ip_ptr pointer to the ipv4 header, not NULL
 * @param ipsize accessable bytes from the iphdr
 * @param new_connection set to != 0 for a new element, not NULL
 * @return returns a pointer to the flow (may be NULL if hash insert or flow key building fails)
 */
	void *ipoque_get_current_flow_ip_v4_v6_decapsulate(struct
													   ipoque_detection_module_struct
													   *ipoque_struct, struct
													   timeorderedhash
													   *toh, const void
													   *ip_ptr, u16 ipsize, u8 * new_connection);
#endif

/** helper function to calculate the hash size by a known number of elements and buffer sizes
 * @param elements number of elements
 * @param userbuffersize size of the key element
 * @param uniquebuffersize size of the data per key element
 * @return returns the amount of required memory
 */
	unsigned long ipoque_to_calculate_hash_size(u32 elements, u32 userbuffersize, u32 uniquebuffersize);


/** enables multi timeout handling, this function must be called before any insert operation !
 * @param toh the hash table, NULL allowed
 * @param queues the number of used queues, must be >= 1. If > 1, the hash table must have been created with ipoque_to_hash_create2(...)
 * @return returns 0 for success, != 0 for error.
 */
	u8 ipoque_to_hash_enable_multiple_timeout(struct timeorderedhash *toh, u32 queues);


/* Get the queue of the last insert operation
 * @param toh the hash table, NULL allowed
 * @return returns the queue of the last insert operation ( NOT lookup)
 * */
	u32 ipoque_to_hash_get_timeout_queue(struct timeorderedhash *toh);

/** sets the queue of the last insert operation ( NOT lookup),
 * @param toh the hash table, NULL allowed
 * @param queue new queue for this element
 * @return returns 0 for success, != 0 for failure */
	u8 ipoque_to_hash_set_timeout_queue(struct timeorderedhash *toh, u32 queue);

/** old hash table dump function, deprecated, do not use
 * @see ipoque_to_hash_foreach */
	u32 ipoque_to_hash_dump(struct timeorderedhash *, u32, IPOQUE_TIMESTAMP_COUNTER_SIZE **, u8 **, u8 **)
		__attribute__ ((deprecated));

/** memory boundary checks for the user memory. This function can be called after an insert operation to check whether the code has written more bytes than allowed.
 * @param toh the hash table
 */
#ifdef IPQ_MEMCHECK_HASH_USER_BUFFER
	void toh_debug_check_last_accessed_memory(struct timeorderedhash *toh);
#else
	static inline void toh_debug_check_last_accessed_memory(struct timeorderedhash *toh __attribute__ ((unused))) {
	};
#endif

/** deprecated function, automatic hash table health check is done already */
	static inline void ipoque_to_hash_check_fill_percentage(struct timeorderedhash *toh
															__attribute__ ((unused)), u8 percentage
															__attribute__ ((unused)))
		__attribute__ ((deprecated));
	static inline void ipoque_to_hash_check_fill_percentage(struct timeorderedhash *toh
															__attribute__ ((unused)), u8 percentage
															__attribute__ ((unused))) {
	};

/** Deprecated macro, do not use anymore */
#define TOH_FILL(HSize, UBSize, UsBSize) \
        (((HSize) / ((UBSize) + (UsBSize))) / 2)

/** Deprecated macro, do not use anymore */
#define TOH2TOH(HElements, DElements, UBSize, UsBSize) \
        ((HElements) * sizeof(u8*) + (DElements) * ((UBsize) + (UsBSize)))

/** Deprecated macro, do not use anymore */
#define TOH2TOH2(HSize, UBSize, UsBSize) \
        (((HSize) - ((UBSize) - (UsBSize)) * (TOH_FILL)) / sizeof(u8*))


/** returns the number of available elements for a hash table
 * @param toh The pointer to the hash table, not NULL
 * @return The number of available elements
 */
	u32 ipoque_to_hash_number_of_elements(struct timeorderedhash *toh);

/** returns the number of used elements for a hash table
 * @param toh The pointer to the hash table, not NULL
 * @return The number of used elements
 */
	u32 ipoque_to_hash_used_elements(struct timeorderedhash *toh);

	/**
	 * returns the maximum number of elements used in the hash table
	 * @param toh The pointer to the hash table, not NULL
	 * @return The number of maximum used elements
	 */
	u32 ipoque_to_hash_maximum_number_of_used_elements(struct timeorderedhash *toh);


#define IPOQUE_TOH_QUEUE_LEN(toh) ipoque_to_hash_used_elements(toh)
#define IPOQUE_TOH_ELEMENTS(toh) ipoque_to_hash_number_of_elements(toh)

/** returns the raw insert pointer from the last insert operation. This can be used to retrieve the last accessed unique and the last accessed user data pointer
 * @param toh The pointer to the hash table, not NULL
 * @return the raw insert pointer
 */
	void *ipoque_to_hash_get_last_raw_insert_pointer(struct timeorderedhash *toh);

#define IPOQUE_TOH_GET_NEWEST_FLOW_ID(toh) ipoque_to_hash_get_last_raw_insert_pointer(toh)


/** returns the pointer to the unique data from a raw pointer
 * @param toh The pointer to the hash table, not NULL
 * @param ptr the pointer from e.g. ipoque_to_hash_get_last_raw_insert_pointer, not NULL
 * @return pointer to the unique data
 */

	void *ipoque_to_hash_raw_to_unique(struct timeorderedhash *toh, void *ptr);

/** returns the pointer to the user data from a raw pointer
 * @param toh The pointer to the hash table, not NULL
 * @param ptr the pointer from e.g. ipoque_to_hash_get_last_raw_insert_pointer, not NULL
 * @return pointer to the user data
 */
	void *ipoque_to_hash_raw_to_user(struct timeorderedhash *toh, void *ptr);

/** old deprected macro, please use the function */
#define IPOQUE_TOH_FLOW_ID_TO_UNIQUE(toh,ptr) ipoque_to_hash_raw_to_unique(toh,ptr)

/** old deprected macro, please use the function */
#define IPOQUE_TOH_FLOW_ID_TO_USER(toh,ptr) ipoque_to_hash_raw_to_user(toh,ptr)

/** returns the size of the key element as initialized from ipoque_to_hash_create2
 * @param toh The pointer to the hash table, not NULL
 * @return the key element size
 * @see ipoque_to_hash_create2
 */
	u32 ipoque_to_hash_get_unique_buffer_size(struct timeorderedhash *toh);

/** returns the size of the user data as initialized from ipoque_to_hash_create2
 * @param toh The pointer to the hash table, not NULL
 * @return the user data size per element
 * @see ipoque_to_hash_create2
 */
	u32 ipoque_to_hash_get_user_buffer_size(struct timeorderedhash *toh);

/** set the userptr for the timeout callback
 * @param toh The pointer to the hash table, just returns when toh is NULL
 * @param new_value The new userptr, NULL allowed
 */
	void ipoque_to_hash_set_timeout_userptr(struct timeorderedhash *toh, void *new_value);

/** returns the userptr for the timeout callback
 * @param toh The pointer to the hash table, just returns when toh is NULL
 * @return the current userptr
 */
	void *ipoque_to_hash_get_timeout_userptr(struct timeorderedhash *toh);

#ifdef IPQ_TOH_LOCKABLE
	void ipq_toh_set_lock_function(struct timeorderedhash *toh, void *(*func) (void *), void *userdata);
	void ipq_toh_set_unlock_function(struct timeorderedhash *toh, void *(*func) (void *), void *userdata);
#endif

	/**
	 * this function returns the timestamp of the oldest entry in the hash table.
	 *
	 * @param toh The pointer to the hash table
	 * @return the timestamp of the oldest entry or 0 if there is no entry.
	 */
	IPOQUE_TIMESTAMP_COUNTER_SIZE ipoque_to_hash_get_timestamp_of_oldest_entry(struct timeorderedhash *toh);


	/**
	 * this function returns a pointer to the unique key for the given user data pointer
	 *
	 * @param toh The pointer to the initialized hash table
	 * @param user The pointer to the user data as returned by insert/lookup. user must be a valid element,
	               the pointer will not be validated.
	 * @return the pointer to the unique key
	 */
	const void *ipoque_to_hash_get_unique_key_from_user_data(struct timeorderedhash *toh, const void *user);

	enum toh_insertion_mode {
		/** if the hash table is full and cannot be resized to store
			more entries, the oldest element is removed to make space
			for the insert. This is the default behavior/ */
		REMOVE_OLDEST_IF_FULL = 0,

		/** An insert operation may fail if not space is available,
			that means old entries are only removed in case of
			timeouts */
		INSERT_FAILS_IF_FULL = 1
	};

	/**
	 * this function sets the mode of the insert operation. By
	 * default, inserts are always successful and will remove the
	 * oldest entry if not enough space is available in the hash
	 * table.  When setting the mode to INSERT_FAILS_IF_FULL, an
	 * insert will fail, no old elements are removed * (except when
	 * timeouts occur)
	 *
	 * @param toh The pointer to the initialized hash table.
	 * @param mode the insertion mode, either REMOVE_OLDEST_IF_FULL or INSERT_FAILS_IF_FULL.
	 */
	void ipoque_to_hash_set_insertion_mode(struct timeorderedhash *toh,
										   enum toh_insertion_mode mode);

#ifdef __cplusplus
}
#endif

#endif
