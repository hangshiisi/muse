/********************************************************************************/
/**
 ** \file       pace2_config.h
 ** \brief      PACE 2 configuration definitions
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef PACE2_CONFIG_H
#define PACE2_CONFIG_H

/* Includes *********************************************************************/
#include "pace2_protocols.h"
#include "pace2_protocols_bitmask.h"
#include "pace2_s3_cdc.h"
#include "pace2_s4_cdd.h"

/* Public Types *****************************************************************/

/**
 * @brief Amount of timeout queues to use for internal tracking. +1 for the default queue.
 */
#define PACE2_INT_FLOW_DEFAULT_TIMEOUT_QUEUES ( 32 + 1 )

/**
 * @brief Definition to distinguish tracking type.
 */
typedef enum {
    INTERNAL,                                       /*!< Usage of internal tracking. */
    EXTERNAL                                        /*!< Usage of external tracking. */
} PACE2_tracking_type;

/**
 * @brief Definition to distinguish safe and aggressive detection modes.
 */
typedef enum {
    SAFE_CLASSIFICATION = 0,                        /*!< Usage of safe mode. */
    AGGRESSIVE_CLASSIFICATION                       /*!< Usage of aggressive mode. */
} PACE2_classification_mode;

/**
 * @brief Definition to distinguish the tracked subscriber direction.
 *
 * The initiating direction will be direction 0, whereas the other direction
 * has the index 1.
 *
 */
typedef enum {
    ALL,                                            /*!< Track all directions. */
    SRC_DIR_0,                                      /*!< Track directions 0 only. */
    SRC_DIR_1,                                      /*!< Track directions 1 only. */
    NONE,                                           /*!< Track no direction. */
} PACE2_tracking_subscriber_side;

/**
 * @brief Definition to distinguish the memory basis of the table.
 *
 * Use @ref ELEMENT_NUMBER to initialize the table with
 * space for the specified number of elements or use @ref MEMORY_SIZE
 * to initialize the table with the given memory size.
 */
typedef enum {
    ELEMENT_NUMBER = 0,                             /*!< Initialize table with given element number */
    MEMORY_SIZE                                     /*!< Initialize table with given memory size */
} PACE2_tracking_mem_basis;

/**
 * @brief Definition of the maximum size of a hash table.
 */
typedef struct {
    PACE2_tracking_mem_basis mem_basis;             /*!< Basis type on which the memory for table will be
                                                         reserved, default: @ref MEMORY_SIZE. */
    u64 element_number;                             /*!< Number of elements for which table will be
                                                         initialized. Must be set if @ref mem_basis
                                                         is @ref ELEMENT_NUMBER. Value will be set automatically
                                                         if @ref mem_basis is @ref MEMORY_SIZE. */
    u64 memory_size;                                /*!< Memory size for initialization of the table,
                                                         default: 4 MiByte. Value will be set automatically if @ref mem_basis is
                                                         @ref ELEMENT_NUMBER. */
} PACE2_table_max_size;

/**
 * @brief Definition of generic tracking configuration parameters.
 */
typedef struct {
    PACE2_tracking_type type;                       /*!< Tracking type mechanism, default: @ref INTERNAL. */
    PACE2_table_max_size max_size;                  /*!< The maximum size of the hash table which is given by an element number or maximum memory size */
    PACE2_timestamp timeout;                        /*!< Timeout of a hash table element, default: 600 s x @ref PACE2_config_general::clock_ticks_per_second. */
    u32 user_data_size;                             /*!< User-data size of a hash table element, default: 0 Byte. */
    u16 custom_key_size;                            /*!< only used with internal tracking. If not 0 the flow key generation is expected to
                                                         be done by the user and passed to the engine. Default 0 (off) */
    u8 enable_tracking_statistics;                  /*!< Activates the statistical tracking of transferred bytes available through the events PACE2_FLOW_PROCESS_EVENT
                                                         and PACE2_SUBSCRIBER_PROCESS_EVENT. This feature requires additional memory per flow/subscriber and
                                                         lowers the performance. default: 0 (disabled). */
    u8 tracking_statistics_per_packet;              /*!< If \ref enable_tracking_statistics is enabled and this is set to "1", then the PACE2_FLOW_PROCESS_EVENT
                                                         or PACE2_SUBSCRIBER_PROCESS_EVENT will be thrown for every packet. Otherwise only at the end of a
                                                         flow/subscriber. default: 1 (enabled). */
    u8 enable_tunnel_tracking;                      /*!< automatically use both IPs in tunnel traffic for internal tracking, default disabled */
} PACE2_tracking_generic_params;

/**
 * @brief Structure definition of tracking configuration.
 */
struct PACE2_config_tracking {
    struct flow_params {
        PACE2_tracking_generic_params generic;      /*!< Generic flow tracking parameters. */

        struct flow_tracking_specific_params {
            PACE2_timestamp timeout_queue_timeouts[PACE2_INT_FLOW_DEFAULT_TIMEOUT_QUEUES];
                                                    /*!< Timeout values for the timeout queues. By default three additional queues are
                                                         configured with the timeouts 5 seconds, 15 minutes and 60 minutes. */

        } specific;                                 /*!< Specific flow tracking parameters. */
    } flow;                                         /*!< Flow tracking configuration. */

    struct subscriber_params {
        PACE2_tracking_generic_params generic;      /*!< Generic subscriber tracking parameters. */
        struct sub_tracking_specific_params {
            PACE2_tracking_subscriber_side side;    /*!< Tracked subscriber directions, default: ALL. */
        } specific;                                 /*!< Specific subscriber tracking parameters. */
    } subscriber;                                   /*!< Subscriber tracking configuration. */
};

/**
 * @brief Definition of Session ID Tracking configuration parameters.
 */
typedef struct {
    u32 memory;                                     /*!< The size of the internal memory buffer for session IDs in bytes,
                                                         can be 0 (if 0, the number of elements is used to determine
                                                         the memory size), default: 1048576.*/
    u32 number_of_elements;                         /*!< The number of session IDs that should be stored. Can be 0. Will only be used if
                                                         the memory argument is zero, default: 0 */
    u16 key_reduce_factor;                          /*!< The factor will be used to reduce the
	                                                     session ID and related key information to reduce memory usage
	                                                     while accepting a larger false positive ratio. Can 1, 2, or 4
	                                                     (1 means no reduction, use complete session ID), default: 1. */
    u8 enabled;                                     /*!< Flag to indicate the enabled Session ID Tracking, default: @ref IPQ_FALSE. */
} PACE2_sit_params;

/**
 * @brief Definition of IP defragmentation configuration parameters.
 */
typedef struct {
    u8 enabled;                                     /*!< Flag to indicate the enabled IP defragmentation, default: @ref IPQ_FALSE. */
    u64 memory_size;                                /*!< Maximum memory size used by the IP defragmentation, default: 1 MiByte.
                                                         Regard that the memory size is used by each thread */
    u8 enabled_memory_growth;                       /*!< Flag to indicate an enabled growing of the consumed memory, default: @ref IPQ_FALSE.
                                                         Requires a set function pointer of @ref pace2_realloc. */
    PACE2_timestamp timeout;                            /*!< Timeout of each fragment, default: 1 s x @ref PACE2_config_general::clock_ticks_per_second.
                                                         It is recommended to keep this as low as possible (maximum 1 second).
                                                         A value of 0 will mark every packet as too old. */
    enum ipoqe_defrag_checksum_enum checksum;       /*!< Checksum handling of the IP defragmentation engine, default
                                                         IPOQUE_DEFRAG_CHECKSUM_IGNORE_WRONG_IP_CHECKSUM. */
} PACE2_s1_defrag_params;

/**
 * @brief Structure definition of packet preparing configuration parameters.
 */
struct PACE2_config_s1_preparing {
    u32 max_framing_depth;                          /*!< Maximum framing depth, default: 10. */
    u32 max_decaps_level;                           /*!< Maximum decapsulation level, default: 0. */
    PACE2_s1_defrag_params defrag;                  /*!< IP defragmentation specific configuration parameters. */
};

/**
 * @brief Structure definition of packet reordering configuration parameters.
 */
struct PACE2_config_s2_reordering {
    u8 enabled;                                     /*!< Flag to indicate the enabled packet reordering, default: @ref IPQ_FALSE. */
    u64 packet_buffer_size;                         /*!< Maximum packet buffer size used by the packet reordering, default: 16 MiByte. */
    enum ipoque_paro_core_mode mode;                /*!< Memory management operation mode, default: @ref IPOQUE_PARO_PACKET_DYNAMIC.*/
    PACE2_timestamp packet_timeout;                 /*!< Timeout of each packet, default: 5 s x @ref PACE2_config_general::clock_ticks_per_second. */
};

/**
 * @brief Structure definition for one custom defined classification
 */
struct PACE2_config_s3_cdc {
    pace2_cdc_callback_t callback;                   /*!< Callback for the custom defined classification */
    void *callback_userptr;                          /*!< User pointer provided to the custom classification */
    u32 flow_area_size;                              /*!< bytes provided to the custom classification on the flow */
    u32 subscriber_area_size;                        /*!< bytes provided to the custom classification on the subscriber */
};

/**
 * @brief Structure definition of SECA configuration parameters.
 */
struct PACE2_config_seca {
    u8 enabled;
    PACE2_table_max_size memory;                                /*!< Main hash table memory. */
    PACE2_timestamp timeout;                                    /*!< Global hash table timeout. Default: 1h */
};

/**
 * @brief Structure definition of DECA ip whitelist configuration parameters.
 */
struct PACE2_config_deca_whitelist {
    PACE2_ip_address ip;                                        /*!< Allowed DNS server. */
    PACE2_ip_address mask;                                      /*!< Subnet mask to allow DNS server. */
};

/**
 * @brief Structure definition of DECA configuration parameters.
 */
struct PACE2_config_deca {
    u8 enabled;                                                 /*!< Flag to indicate the enabled deca engine, default: @ref IPQ_FALSE. */
    const struct PACE2_config_deca_whitelist * whitelist;       /*!< Pointer to an array of whitelisted IP entries. */
    u8 whitelist_count;                                         /*!< Amount of whitelisted IPs. */
    PACE2_table_max_size memory;                                /*!< Main hash table memory. */
    PACE2_timestamp timeout;                                    /*!< Global hash table timeout.
                                                                     The DNS timeout value will
                                                                     be used if not set. */
};

struct PACE2_config_s3_pa_tags {
    u8 enabled;                                     /*!< Flag to indicate the enabled protocol and application grouping, default: @ref IPQ_FALSE. */
    const char **tag_strings;                       /*!< Array of strings connected to protocol and application tag implementation, default NULL. */
    u16 number_of_tags;                             /*!< Size of the @ref tag_strings array. */
};

/**
 * @brief Structure definition of packet classification configuration parameters.
 */
struct PACE2_config_s3_classification {
    u8 enabled;                                     /*!< Flag to indicate the enabled packet classification, default: @ref IPQ_TRUE. */
    PACE2_protocols_mask active_classifications;    /*!< Struct defining classification of which protocols shall be activated, default: all. */
    u8 csi_enabled;                                 /*!< Flag to indicate the enabled client-server indication, default: @ref IPQ_FALSE. */
    u8 nat_enabled;                                 /*!< Flag to indicate the enabled NAT detection, default: @ref IPQ_FALSE. */
    u8 os_enabled;                                  /*!< Flag to indicate the enabled operating system detection, default: @ref IPQ_FALSE. */
    u8 asym_detection_enabled;                      /*!< Flag to indicate the enabled asymmetric detection mode, default: @ref IPQ_FALSE. */
    /** OpenVPN detection mode, default: @ref AGGRESSIVE_CLASSIFICATION.
     *  @arg Use @ref AGGRESSIVE_CLASSIFICATION mode to detect all known OpenVPN handshakes.
     *       This might cause a higher false positive rate.
     *  @arg Use  @ref SAFE_CLASSIFICATION mode to minimize false positive rate. */
    PACE2_classification_mode openvpn_mode;
    /** Skype detection mode, default @ref SAFE_CLASSIFICATION.
     *  @arg Use @ref AGGRESSIVE_CLASSIFICATION mode to detect all Skype flows. This might cause a higher false positive rate.
     *  @arg Use @ref SAFE_CLASSIFICATION mode to minimize false positive rate. */
    PACE2_classification_mode skype_mode;
    /** Radius detection mode, default: @ref SAFE_CLASSIFICATION.
     *  @arg Use @ref AGGRESSIVE_CLASSIFICATION mode to detect radius flows on all ports, which causes higher computational costs.
     *  @arg Use @ref SAFE_CLASSIFICATION mode to detection radius flows on standard ports only. */
    PACE2_classification_mode radius_mode;
    PACE2_sit_params sit;                           /*!< SSL Session ID Tracking specific configuration parameters. */
    u8 cdn_caching_enabled;                         /*!< Flag to indicate the enabled content delivery network caching
                                                         algorithm, default: @ref IPQ_FALSE. */
    u8 rtp_performance_enabled;                     /*!< Flag to indicate the enabled rtp performance measurements, default: @ref IPQ_FALSE. */

    struct PACE2_config_s3_cdc *cdc_conf_array;     /*!< Pointer to an array of custom defined classifications configuration parameters. */
    u32 cdc_number;                                 /*!< Number of custom defined classification. */

    u32 unclassified_after_mseconds;                /*!< Timeout in ms after which a flow get classified as protocol unclassified, default: 0 (off)  */

    struct dissector_config metadata_dissector_config;
                                                    /*!< Configuration structure to enable different dissector metadata @ref  */
    struct PACE2_config_seca seca;                  /*!< SECA configuration parameters. */
    struct PACE2_config_deca deca;                  /*!< DECA configuration parameters. */

    struct PACE2_config_s3_pa_tags pa_tags;         /*!< Structure of configuration parameters for protocol and application grouping. */
};

/**
 * @brief Definition for one custom defined decoder.
 */
struct PACE2_config_s4_cdd {
    pace2_cdd_callback_t callback;                  /*!< Callback for the custom defined decoder to process PACE2 events. */
    void *callback_userptr;                         /*!< Pointer to user-specified data provided to the custom decoder. */
    u32 number_of_events;                           /*!< Number of different events this CDD will throw. */
    /** Array with number_of_events entries. Each entry reflects the size of the data for the specific event generated by the CDD. */
    u32 * event_size;
};

/**
 * @brief Enumeration to define the processing method for stage 4. See also @ref PACE2_config_s4_decoding.processing_method
 */
enum PACE2_config_s4_processing_method {
    PACE2_PROCESS_PACKETS,                          /*!< Signals the usage of pace2_s4_process_packet or pace2_s5_process_packet function for the stages 4 and 5 */
    PACE2_PROCESS_STREAM,                           /*!< Signals the usage of pace2_s4_process_stream or pace2_s5_process_stream function for the stages 4 and 5 */
};

#ifndef PACE2_DISABLE_DECODER
/**
 * @brief Structure definition of packet decoding configuration parameters.
 */
struct PACE2_config_s4_decoding {
    u8 enabled;                                     /*!< Flag to indicate the enabled packet decoding, default: @ref IPQ_FALSE. */

    /**
     * Signals, which processing method will be used during runtime.
     * PACE2_PROCESS_STREAM means that stage 4 and 5 is called with the pace2_s4_process_stream or pace2_s5_process_stream function
     * PACE2_PROCESS_PACKETS means that stage 4 and 5 is called with the pace2_s4_process_packet or pace2_s5_process_packet function
     */
    enum PACE2_config_s4_processing_method processing_method;

    PACE2_protocols_mask active_advanced_decoders;      /*!< Struct defining decoding of which protocols shall be activated, default: all. */
    IPOQUE_CLASS_DECODER_BITMASK active_class_decoders; /*!< Struct defining which class decoders shall be activated, default: all. */

    u32 http_gzip_buffer_size;                          /*!< maximum buffer size for HTTP gzip decompression and HTTP deflate operation */

    /* checksumming */
    enum ipd_ip_checksumming ip_checksum;               /*!< activates the IP checksumming used by the TCP reassembly engine */
    enum ipd_tcp_checksumming tcp_checksum;             /*!< activates the TCP checksumming used by the TCP reassembly engine */
    u8 enable_ip_or_tcp_checksumming;                   /*!< activates the IPv4 OR TCP checksumming used by the TCP reassembly engine */

    /* tcp reassembly values */
    u32 tcp_out_of_order_timeout;                       /*!< how long should the decoder wait for missing or bad TCP packets in timestamp ticks, default is 8 * ticks_per_second */
    u32 tcp_asymmetric_timeout;                         /*!< a flow is marked as asymmetric if, after the first packet, there comes no packet in the opposite direction for this period of time; 0 disabled asymmetry detection (this is the default) */
    u32 tcp_max_skew;                                   /*!< longest time an acknowledgment may precede the actual data that is acked (in timestamp ticks); 0 disables message ordering (this is the default) */
    u32 tcp_max_window_size;                            /*!< maximum TCP window size, default is 16MB, might be bigger on very very very high speed connections */
    u8 tcp_hole_memory_fill_value;                      /*!< fill value for holes to mark them as bad data, recommended to keep it as default (which is 0) */

    /* dummy decoder */
    u64 dummy_decoder_max_buffer_size;                  /*!< maximum amount of data the dummy decoder will allow to buffer for unknown connections */

    /* http */
    /**
     * The maximum amount of data that is buffered for one direction when the decoder is waiting for data from the other direction.
     * When the limit is reached the decoder switches to asymmetric decoding trying to decode the direction with data available.
     */
    u32 http_max_direction_buffer_size;
    /** Defines how much HTTP payload data is buffered for each transaction before a
     *  PACE2_CLASS_HTTP_REQUEST_DATA_TRANSFER / PACE2_CLASS_HTTP_RESPONSE_DATA_TRANSFER event is issued.
     *  If set to zero the payload data will be buffered until the request/response is complete or the time
     *  limitation described below is reached.*/
    u64 http_class_payload_size_max;
    /** Defines how long HTTP payload data is buffered for each transaction before a
     *  PACE2_CLASS_HTTP_REQUEST_DATA_TRANSFER / PACE2_CLASS_HTTP_RESPONSE_DATA_TRANSFER event is issued.
     *  If set to zero the payload data will be buffered until the request/response is complete or the payload
     *  limitation described above is reached. */
    u32 http_class_payload_timeout;

    /* mail */
    /** Defines how much mail body payload data is buffered for each transaction before a
     *  PACE2_CLASS_MAIL_SESSION_BODY_TRANSFER event is issued.
     *  If set to zero the payload data will be buffered until the mail body is complete or the time
     *  limitation described below is reached.*/
    u64 mail_class_body_size_max;
    /** Defines how long mail body payload data is buffered for each transaction before a
     *  PACE2_CLASS_MAIL_SESSION_BODY_TRANSFER event is issued.
     *  If set to zero the payload data will be buffered until the mail body is complete or the payload
     *  limitation described above is reached. */
    u32 mail_class_body_timeout;
    /** Enable transcoding of message headers encoded according to the "MIME Message Header Extensions for
     *  Non-ASCII Text" (RFC 2047) to UTF-8. */
    u8 mail_class_enable_utf8_headers;
    /** Output attachments found in MIME messages (transported over IMAP, POP3, SMTP) through
     * ATTACHMENT_INFO/ATTACHMENT_CONTENT events, instead of through BODY_TRANSFER events, and base64-
     * decode attachment contents. */
    u8 mail_class_enable_mime_attachments;
    /** Also generate PACE2_CLASS_MAIL_ATTACHMENT_CONTENT_EXT events combining
     * PACE2_CLASS_MAIL_ATTACHMENT_CONTENT with the according PACE2_CLASS_MAIL_ATTACHMENT_INFO
     * event. Default: disabled.*/
    u8 mail_class_enable_extended_attachment_content_events;


    /* chat */
    /** Defines how long chat file transfer data is buffered for each file transfer before a
     *  IPD_CHAT_CLASS_CHATROOM_TRANSFER event with a segment of file transfer data is issued.
     *  If set to zero the file transfer data will be buffered until the file transfer is complete
     *  or the data size limitation described below is reached. */
    u64 chat_class_filetransfer_dump_timeout;
    /** Defines how much chat file transfer data is buffered for each file transfer before a
     *  IPD_CHAT_CLASS_CHATROOM_TRANSFER event with a segment of file transfer data is issued.
     *  If set to zero the file transfer data will be buffered until the the file transfer is complete or the time
     *  limitation described above is reached.*/
    u64 chat_class_filetransfer_dump_max_size;

    /* rtp reorder buffer */
    /** number of slots in the RTP reorder pool (needs to be >1 to enable RTP packet reordering) */
    u64 rtp_buffer_global_packet_limit;
    /** maximum number of RTP packets that will be buffered in one direction of one flow */
    u64 rtp_buffer_flow_packet_limit;
    /** size in bytes of one slot in the RTP reorder pool */
    u64 rtp_buffer_max_packet_size;

    /* dtmf */
    /** Enable decoding of DTMF signals in RTP flows */
    u8 rtp_decode_dtmf_signals;
    /** Force decoding of in-band DTMF audio signals in RTP flows */
    u8 rtp_force_decode_dtmf_audio;
    /** integration point for an external AMR decoder */
    struct ipd_amr_decoder amr_decoder;
    /** integration point for an external AMR-WB decoder */
    struct ipd_amr_decoder amrwb_decoder;

    /* FTP */
    /** Defines how much file transfer data is buffered for each file transfer before a
     *  PACE2_ADVANCED_FTP_DATA event with a segment of file transfer data is issued.
     *  If set to zero the file transfer data will be buffered until the the file transfer is complete or the time
     *  limitation described below is reached.*/
    u64 ftp_class_data_dump_size_max;
    /** Defines how long file transfer data is buffered for each file transfer before a
     *  PACE2_ADVANCED_FTP_DATA event with a segment of file transfer data is issued.
     *  If set to zero the file transfer data will be buffered until the file transfer is complete
     *  or the data size limitation described above is reached. */
    u32 ftp_class_data_dump_timeout;

    /* BitTorrent decoder */
    /** Maximum BitTorrent message length. If the length field of a message is larger than this, the
     * respective direction of the flow is set into the invalid state. 'piece' messages are exempt from this
     * limit as their contents are not buffered until a message is complete. The largest variable-length
     * messages that need to be processed are 'bitfield' messages at
     * <tt>1&nbsp;+&nbsp;number_of_pieces_in_torrent/8</tt> bytes (rounded up). */
    u32 bittorrent_max_message_length;

    /* tls handling */
    u8 tls_enforce_processing;                      /*!< When off, encrypted tls data are ignored. Off by default. */

    u32 cdd_number;                                 /*!< Number of custom defined decoder. */
    struct PACE2_config_s4_cdd * cdd_conf_array;    /*!< Pointer to an array of custom defined decoder configurations. */
};
#endif
/**
 * @brief Structure definition of dynamic upgrade configuration parameters.
 */
struct PACE2_config_dynamic_upgrade {
    u8 enabled;                                     /*!< Flag to indicate the enabled dynamic upgrade, default: @ref IPQ_FALSE. */
    u32 reserve_bytes;                              /*!< Amount of bytes to reserve for library upgrades. A value of 0 defaults to 10% of the corresponding structure. */
    pace2_dlopen pace2_dlopen;                      /*!< Function pointer to a POSIX compatible dlopen function, default: NULL. */
    pace2_dlsym pace2_dlsym;                        /*!< Function pointer to a POSIX compatible dlsym function, default NULL. */
    pace2_dlclose pace2_dlclose;                    /*!< Function pointer to a POSIX compatible dlclose function, default NULL. */
    /** Maximum lifetime of flows and subscribers. Should be the higher value of either the flow timeout or subscriber
     *  timeout. Is set automatically when internal tracking is used for both. Has to be set in cases of external tracking. */
    PACE2_timestamp release_memory_age;
};

/**
 * @brief Structure definition of general configuration parameters.
 */
struct PACE2_config_general {
    u32 clock_ticks_per_second;                                 /*!< Timestamp resolution, default: 1000. */
    u32 number_of_threads;                                      /*!< Number of running threads, default: 1. */
    PACE2_table_max_size max_number_of_events;                  /*!< Maximum number of thrown events by element number or memory size for one thread, default: 100 elements. */
    struct global_epol {
        PACE2_epol_structure policy;                            /*!< Global event policy which indicates the enabled events,
                                                                     default: all events are enabled. */
        PACE2_epol_operation_mode policy_op_mode;               /*!< Operation mode of the event policy, default @ref PACE2_PROGRESSIVE. */
    } event;                                                    /*!< Structure to bind all policy variables. */

    pace2_malloc pace2_alloc;                                   /*!< Function pointer to a memory allocation function, default: NULL.
                                                                     Must be set by the application. */
    pace2_free pace2_free;                                      /*!< Function pointer to a memory free function, default: NULL.
                                                                     Must be set by the application. */
    pace2_realloc pace2_realloc;                                /*!< Function pointer to a memory free function, default: NULL.
                                                                     Must be set by the application. */
    void *memory_callback_user_ptr;                             /*!< Pointer to allocation function user data: will be passed as the
                                                                     \c user_ptr argument to the the allocation functions defined above;
                                                                     default: NULL. */

    pace2_process_information_callback process_information;     /*!< Callback function pointer to handle some debug and process informations from PACE2, default: pace2_default_process_information_callback. */
    void *process_information_callback_user_ptr;                /*!< User definable pointer, which is available inside the process_information callback, default: NULL. */
};

#ifdef IPOQUE_ENABLE_LICENSING
struct PACE2_config_licensing
{
    const char *license_file;
};
#endif

/**
 * @brief Structure definition of PACE 2 configuration parameters.
 */
struct PACE2_global_config
{
    struct PACE2_config_general             general;            /*!< General configuration parameters. */
    struct PACE2_config_tracking            tracking;           /*!< Tracking specific configuration parameters. */
    struct PACE2_config_dynamic_upgrade     dynamic_upgrade;    /*!< Dynamic upgrade specific configuration parameters. */
    struct PACE2_config_s1_preparing        s1_preparing;       /*!< Stage 1 specific configuration parameters. */
    struct PACE2_config_s2_reordering       s2_reordering;      /*!< Stage 2 specific configuration parameters. */
    struct PACE2_config_s3_classification   s3_classification;  /*!< Stage 3 specific configuration parameters. */
#ifndef PACE2_DISABLE_DECODER
    struct PACE2_config_s4_decoding         s4_decoding;        /*!< Stage 4 specific configuration parameters. */
#endif
#ifdef IPOQUE_ENABLE_LICENSING
    struct PACE2_config_licensing           licensing;          /*!< licensing configuration parameters. */
#endif
};

/* Public Prototypes ************************************************************/

/**
 * \brief Initialize a configuration structure with default values.
 *
 * The function initializes a configuration structure with default values.
 * The default values can be found in the descriptions of the configuration parameters.
 *
 * \param[in]   config  Constant pointer to a configuration structure.
 * \returns     None
 */
void pace2_init_default_config(struct PACE2_global_config * const config);

/**
 * \brief Initialize license configuration structure with the given license file.
 *
 * The function initializes a license configuration structure with the given license file.
 *
 * \param[in]   config  Constant pointer to a configuration structure.
 * \param[in]   license_file path to the license file
 * \returns     None
 */
void pace2_set_license_config(struct PACE2_global_config * const config,
                              const char *license_file);

#endif /* PACE2_CONFIG_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
