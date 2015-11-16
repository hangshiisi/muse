/********************************************************************************/
/**
 ** \file       pace2_basic_def.h
 ** \brief      PACE 2 basic type definitions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef PACE2_BASIC_DEF_H
#define PACE2_BASIC_DEF_H

/* Includes *********************************************************************/
#ifdef __KERNEL__
    #include <linux/in.h>
#else
#ifdef _WIN32
#else
    #include <netinet/in.h>
#endif // _WIN32
#endif // __KERNEL__

#include <ipq_api.h>
#include <stdarg.h>

/* Public Macros ****************************************************************/
#define PACE2_ALL_THREADS (-1)                      /*!< Thread ID value which references all threads. */

/**
 * @brief Macro for getting the size of an array.
 */
#define PACE2_STATIC_ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

/**
 * @brief Macro to add a flag to the bitmask.
 *
 * @param   mask    Bitmask to which the flag should be added.
 * @param   flag    Flag which should be added.
 */
#define PACE2_MASK_ADD_FLAG(mask, flag)             ( (mask) |= 1LL << (flag) )

/**
 * @brief Macro to removes a flag from a bitmask.
 *
 * @param   mask    Bitmask from which the flag should be removed.
 * @param   flag    Flag which should be removed.
 */
#define PACE2_MASK_REMOVE_FLAG(mask, flag)          ( (mask) &= ~(1LL << (flag) ))

/**
 * @brief Macro to check a set flag inside a bitmask.
 *
 * The check returns 1 in cases the checked flag is set.
 * @param   mask    Bitmask which includes all flags.
 * @param   flag    Flag which should be checked.
 */
#define PACE2_MASK_INCLUDES_FLAG(mask, flag)        (( (mask) & (1LL << (flag) )) != 0)

/**
 * @brief Macro to add a flag to an array bitmask.
 *
 * @param   mask    Bitmask array to which the flag should be added.
 * @param   flag    Flag which should be added.
 */
#define PACE2_ARRAY_MASK_ADD_FLAG(mask, flag)       PACE2_MASK_ADD_FLAG( (mask)[(flag >> 6)], ( (flag) & 0x3F))

/**
 * @brief Macro to removes a flag from an array bitmask.
 *
 * @param   mask    Bitmask array from which the flag should be removed.
 * @param   flag    Flag which should be removed.
 */
#define PACE2_ARRAY_MASK_REMOVE_FLAG(mask, flag)    PACE2_MASK_REMOVE_FLAG( (mask)[(flag >> 6)],( (flag) & 0x3F))

/**
 * @brief Macro to check a set flag inside an array bitmask.
 *
 * The check returns 1 in cases the checked flag is set.
 * @param   mask    Bitmask array which includes all flags.
 * @param   flag    Flag which should be checked.
 */
#define PACE2_ARRAY_MASK_INCLUDES_FLAG(mask, flag)  PACE2_MASK_INCLUDES_FLAG( (mask)[(flag >> 6)], ( (flag) & 0x3F))

/* Public Types *****************************************************************/

typedef struct pace2_module PACE2_module;           /*!< Public type definition of a PACE 2 module. */
typedef struct pace2_flow_struct PACE2_flow_data;   /*!< Public type definition of PACE 2 flow data. */
typedef void PACE2_subscriber_data;                 /*!< Public type definition of PACE 2 subscriber data. */

typedef u64 PACE2_bitmask;                          /*!< Unified type definition for a PACE 2 bitmask. */
typedef u64 PACE2_timestamp;                        /*!< Unified type definition for a PACE 2 timestamp. */

/**
 * @brief Unified type definition for a PACE 2 byte buffer.
 *
 * This type has to be used for a byte buffer or character string with a given length.
 */
typedef struct {
    const char *ptr;                                /*!< Pointer to the first byte of the buffer. */
    u32 len;                                        /*!< Length of the buffer. */
} PACE2_byte_buffer;

/**
 * @brief Unified type definition for a PACE 2 boolean value.
 */
typedef enum {
    IPQ_FALSE = 0,                                  /*!< Represents false. */
    IPQ_TRUE = 1                                    /*!< Represents true */
} PACE2_boolean;

/**
 * @brief Type definition for a unique subscriber key structure.
 */
typedef struct {
    u8 buffer[16];             /*!< Buffer to store the unique key. Size of a IPv6 address. */
} PACE2_subscriber_key;

/**
 * @brief Type definition for a IP address. Covers IPv4 and IPv6.
 */
typedef struct {
    u8 is_ip_v6;                    /**< Signals that ip is an IPv4 or an IPv6 address. */
    union {
        struct in_addr ipv4;        /**< The IPv4 address. Only use this, if is_ipv6 == "0". */
        struct in6_addr ipv6;       /**< The IPv6 address. Only use this, if is_ipv6 == "1". */
    } address;                      /**< The IP address. */
} PACE2_ip_address;

/**
 * @brief Definition of a packet frame type.
 */
typedef enum {
    IPv4,                                           /*!< IPv4 frame. */
    IPv6,                                           /*!< IPv6 frame. */
    TCP,                                            /*!< TCP frame. */
    UDP,                                            /*!< UDP frame. */
    L2,                                             /*!< Generic layer 2 frame. */
    L3,                                             /*!< Generic layer 3 frame. */
    L4,                                             /*!< Generic layer 4 frame. */
    L7,                                             /*!< Generic layer 7 frame. */
    OTHER                                           /*!< Any other frame type. */
} PACE2_packet_frame_type;

/**
 * @brief Definition of a frame descriptor.
 */
typedef struct pace2_packet_frame_descriptor {
    union tt{
        const struct iphdr *ipv4;                   /*!< Pointer to IPv4 frame data. */
        const struct ip6_hdr *ipv6;                 /*!< Pointer to IPv6 frame data. */
        const struct tcphdr *tcp;                   /*!< Pointer to TCP frame data. */
        const struct udphdr *udp;                   /*!< Pointer to UDP frame data. */
        const void *l2_data;                        /*!< Pointer to OSI layer 2 frame data. */
        const void *l3_data;                        /*!< Pointer to OSI layer 3 frame data. */
        const void *l4_data;                        /*!< Pointer to OSI layer 4 frame data. */
        const void *l7_data;                        /*!< Pointer to OSI layer 7 frame data. */
        const void *other_data;                     /*!< Pointer to any other frame data. */
    } frame_data;                                   /*!< Named union which contains the data pointer of the frame type. */
    u16 frame_length;                               /*!< Frame data length. */
    u16 frame_layer_protocol;                       /*!< The layer 4 protocol type. */
    PACE2_packet_frame_type type;                   /*!< Frame type. */
} PACE2_packet_frame_descriptor;

/**
 * @brief Definition of a frame stack, which contains the frame descriptors.
 */
typedef struct pace2_packet_stack {
    PACE2_packet_frame_descriptor *stack;           /*!< Pointer to the frame stack. */
    u32 stack_size;                                 /*!< Frame stack size. */
    u8 inner_ip_index;                              /*!< index of the most inner IP layer */
    u8 outer_ip_index;                              /*!< index of the most outer IP layer */
} PACE2_packet_stack;

/**
 * @brief Definition of the PACE 2 packet descriptor, which joins all necessary information
 * required during packet processing.
 *
 * Please refer to the manual for a more detailed description of the possible usage of each field.
 */
typedef struct pace2_packet_descriptor {
    /* pointer variables */
    PACE2_packet_stack *framing;                    /*!< Pointer to the describing packet frame stack. */
    void *flow_data;                                /*!< Pointer to the related flow of the packet. */
    void *flow_user_data;                           /*!< Pointer to the related flow user data of the packet. */
    void *packet_user_data;                         /*!< Pointer to the user data of the packet. */
    void *src_stage3;                               /*!< Pointer to the classification source subscriber data. */
    void *src_stage3_user_data;                     /*!< Pointer to the classification source subscriber user data. */
    void *dst_stage3;                               /*!< Pointer to the classification destination subscriber data. */
    void *dst_stage3_user_data;                     /*!< Pointer to the classification destination subscriber user data. */
    void *flow_custom_key;                          /*!< Pointer to the flow key area used for user provided lookup keys */
    void *src_custom_key;                           /*!< Pointer to the source subscriber key area used for user provided lookup keys */
    void *dst_custom_key;                           /*!< Pointer to the destination subscriber key area used for user provided lookup keys */

    /* 64 bit variables */
    PACE2_timestamp packet_ts;                      /*!< Packet timestamp. */
    u64 packet_id;                                  /*!< Externally assigned packet ID. */
    u64 flow_id;                                    /*!< ID of the related flow of the packet. Is calculated internally. */

    /* 32 bit variables */
    enum ipoque_asymmetric_connection_status_enum asymmetric_connection_status; /*!< Current status of asymmetry detection. */

    /* 16 bit variables */
    u16 packet_user_data_len;                       /*!< Length of the user data, which is available through @ref packet_user_data. */

    /* 8 bit variables */
    u8 direction;                                   /*!< Packet direction. */

    /* bit field variables */
    u32 copied_by_paro:1;                           /*!< Flag will be set if the packet got copied by paro. */
    u32 new_flow:1;                                 /*!< Flag will be set if the packet triggers a new flow. */
    u32 fast_path_used_in_s3:1;                     /*!< Flag will be set if the classification fastpath was used.
                                                         Will be set only when using internal tracking. */
} PACE2_packet_descriptor;

/**
 * @brief Contains data generated in stage 3 which is required in stage 4
 */
typedef struct pace2_classifier_token {
    void *token_content;
    u16 token_length;
} PACE2_classifier_token;

/**
 * @brief Definition of the PACE 2 stream descriptor, which joins all necessary information
 * required during stream processing.
 *
 * PACE 2 currently offers processing of streams only in stage 4. A data stream here is
 * the a reassembled representation of the payload of all packets belonging to the same flow, where each direction
 * is treated separately.
 *
 * Please refer to the manual for a more detailed description of the possible usage of each field.
 */
typedef struct pace2_stream_descriptor {
    void *flow_data;                                            /*!< Pointer to the related flow. */
    void *flow_user_data;                                       /*!< Pointer to the related flow user data of the stream. */

    PACE2_timestamp ts;                                         /*!< Timestamp of most current data fragment. */

    const ipoque_unique_flow_ipv4_and_6_struct_t *flow_tuple;   /*!< Pointer to a structure identifying the flow. */

    u64 packet_id;                                              /*!< Externally assigned ID of the latest packet of the flow. */
    u64 flow_id;                                                /*!< ID of the related flow. Is set from packet descriptor. */

    u8 flow_is_asym:1;                                          /*!< Is set if flow is asymmetric. */
    u8 asym_dir:1;                                              /*!< Contains the side of the flow that contains data,
                                                                     if flow is asymmetric. */

    const void *stream[2];                                      /*!< Array containing one pointer per direction of the flow,
                                                                     pointing to the reassembled data of that direction. */
    u64 stream_length[2];                                       /*!< Contains the number of bytes of data available in the
                                                                     @ref stream pointers per direction. */

    u64 stream_remove[2];                                       /*!< Contains the number of bytes to remove from each direction
                                                                     of the input stream buffer. */
}PACE2_stream_descriptor;


/**
 * @brief Defines the constant values for the level of a process_nformation.
 */
typedef enum {
    PACE2_PROCESS_INFORMATION_LEVEL_DEBUG,      /*!< Signals that the call of the process information callback is a debug information. */
    PACE2_PROCESS_INFORMATION_LEVEL_WARNING,    /*!< Signals that the call of the process information callback is a warning information. */
    PACE2_PROCESS_INFORMATION_LEVEL_ERROR,      /*!< Signals that the call of the process information callback is a error information. */

    NUMBER_OF_PACE2_PROCESS_INFORMATION_LEVEL
} PACE2_process_information_level;

/**
 * @brief Typedef for a function, which can be used as process information callback in the PACE2_global_config.
 *        A default implementation for this callback is the pace2_default_process_information_callback function of PACE2.
 *
 * @param[in]   thread_ID   The thread ID of the thread, from which this callback was called.
 * @param[in]   level       The kind of information for which this callback was called. see also @ref PACE2_process_information_level.
 * @param[in]   user_ptr    Is a pointer which can be defined from the user over @ref PACE2_config_general::process_information_callback_user_ptr
 *                          and is available in every call of this callback function. This can be useful to get access
 *                          to own data structures or keys, which are needed to handle this callback.
 * @param[in]   format      Is a format string like in printf, which describes the process information.
 * @param[in]   args        The set of variable arguments, which are passed to this function. Contains the values
 *                          for the format string like for printf.
 */
typedef void (*pace2_process_information_callback)( u32 thread_ID,
                                                    PACE2_process_information_level level,
                                                    void * user_ptr,
                                                    const char *format,
                                                    va_list args);

#define PACE2_RETURN_VALUES(X) \
        X(PACE2_SUCCESS,                                            Everything worked fine.) \
        X(PACE2_PARAM_MISSING,                                      Some parameter is missing.) \
        X(PACE2_TIMEOUT_REACHED,                                    Timeout has been reached.) \
        X(PACE2_POINTER_NULL,                                       Usage of an invalid pointer.) \
        X(PACE2_OUT_OF_MEMORY,                                      Memory allocation failed.) \
        X(PACE2_TRACKING_FLOW_TIMEOUT_TOO_SMALL,                    The tracking flow timeout is smaller than reordering packet timeout.) \
        X(PACE2_INVALID_CONFIGURATION_POINTER,                      Usage of an invalid configuration pointer.) \
        X(PACE2_INVALID_MODULE_POINTER,                             Usage of an invalid module pointer.) \
        X(PACE2_S2_REORDERING_PACKET_BUFFER_SIZE_TOO_SMALL,         The s2 reordering packet buffer size is smaller than the minimum value.) \
        X(PACE2_NO_DYNAMIC_UPGRADE,                                 Dynamic upgrade is not available in this build.) \
        X(PACE2_INVALID_GENERAL_ALLOC_FUNCTION_PTR,                 The config general pace2_alloc function ptr is invalid.) \
        X(PACE2_INVALID_GENERAL_FREE_FUNCTION_PTR,                  The config general pace2_free function ptr is invalid.) \
        X(PACE2_INVALID_GENERAL_REALLOC_FUNCTION_PTR,               The config general pace2_realloc function ptr is invalid.) \
        X(PACE2_INVALID_DYNAMIC_UPGRADE_DLOPEN_FUNCTION_PTR,        The config dynamic upgrade dlopen function ptr is invalid.) \
        X(PACE2_INVALID_DYNAMIC_UPGRADE_DLSYM_FUNCTION_PTR,         The config dynamic upgrade dlsym function ptr is invalid.) \
        X(PACE2_INVALID_DYNAMIC_UPGRADE_DLCLOSE_FUNCTION_PTR,       The config dynamic upgrade dlclose function ptr is invalid.) \
        X(PACE2_DYNAMIC_UPGRADE_RELEASE_MEMORY_AGE_TOO_SMALL,       The dynamic upgrade memory age is smaller than flow or subscriber timeout.) \
        X(PACE2_NO_FLOW_MEMORY_AGE_SET,                             The config tracking flow type is EXTERNAL and no memory age is set.) \
        X(PACE2_NO_SUBSCRIBER_MEMORY_AGE_SET,                       The config tracking subscriber type is EXTERNAL and no memory age is set.) \
        X(PACE2_EVENT_DECLINED,                                     Allocation of event slot is rejected.) \
        X(PACE2_EVENT_QUEUE_EMPTY,                                  The event queue is empty.) \
        X(PACE2_CDD_INVALID_FUNCTION_CALL,                          Invalid function call of CDD event allocation.) \
        X(PACE2_CDD_DECODER_DISABLED,                               CDD are configured but the decoding stage is disabled.) \
        X(PACE2_CDD_CONFIG_ARRAY_NOT_SET,                           The pointer to the CDD configuration is missing.) \
        X(PACE2_CDD_CALLBACK_NOT_SET,                               The callback of a CDD is not set.) \
        X(PACE2_CDD_EVENT_SIZE_NOT_SET,                             The event size of a CDD is not set.) \
        X(PACE2_INDEX_OUTSIDE_ARRAY_BOUNDS,                         The index for array access is outside the array bounds.) \
        X(PACE2_INVALID_TAG,                                        The tag is not valid because it is outside of the maximal amount of tags.) \
        X(PACE2_FAILURE,                                            An unknown error occured.)


#define GENERATE_ENUM(enum, string)     enum, /*!< string */
#define GENERATE_STRING(enum, string)   #string,

/**
 * @brief Return state of generic PACE2 functions.
 */
typedef enum {
    PACE2_RETURN_VALUES(GENERATE_ENUM)
} PACE2_return_state;

/**
 * @brief Return state of load license function.
 */
typedef enum {
    PACE2_LICENSING_LOAD_SUCCESS = 0,       /*!< License has been successfully loaded. */
    PACE2_LICENSING_UNSUPPORTED_FORMAT,     /*!< Format of the input file is not valid. */
    PACE2_LICENSING_LOAD_FAILED,            /*!< Loading of input file failed. */
    PACE2_LICENSING_NOT_AVAILABLE           /*!< Licensing feature is not enabled. */
} PACE2_licensing_state;

#endif /* PACE2_BASIC_DEF_H */
