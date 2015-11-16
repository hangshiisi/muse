/*
 * event_handler.c
 *
 *  Created on: Mar 18, 2014
 */

/* Includes *********************************************************************/

#include <stdio.h>
#include <string.h>

#ifndef WIN32
#include <arpa/inet.h>

#ifndef __linux__
#include <sys/socket.h>
#endif

#else
#include <WinSock2.h>
#include <WS2tcpip.h>

#endif

#include <assert.h>
#include "event_handler.h"

/* Private Constants ************************************************************/

static char const * const pace_event_type_to_string[] = {
    IPQ_ENUM_TO_STRING(PACE2_NO_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_DETECTION_RESULT),
    IPQ_ENUM_TO_STRING(PACE2_FLOW_STARTED_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_FLOW_DROPPED_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_SUBSCRIBER_STARTED_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_SUBSCRIBER_DROPPED_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_BASIC_HTTP_REQUEST_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_BASIC_HTTP_RESPONSE_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_ADVANCED_HTTP_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_CLASS_HTTP_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_BASIC_CITRIX_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_BASIC_DHCP_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_ADVANCED_DHCP_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_OS_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_NAT_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_BASIC_SIP_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_ADVANCED_SIP_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_CLASS_VOIP_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_BASIC_SSL_CLIENT_HELLO_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_BASIC_SSL_SERVER_HELLO_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_BASIC_SIT_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_CSI_PACKET_DIR_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_CSI_HOST_TYPE_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_BASIC_RTP_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_RTCP_REPORT),
    IPQ_ENUM_TO_STRING(PACE2_TCP_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_CLASSIFICATION_STATUS),
    IPQ_ENUM_TO_STRING(PACE2_FASTPATH_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_APP_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_ADVANCED_DIAMETER_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_ADVANCED_DNS_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_ADVANCED_FTP_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_ADVANCED_RADIUS_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_ADVANCED_ICMPV6_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_ADVANCED_POP_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_ADVANCED_IMAP_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_ADVANCED_SMTP_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_ADVANCED_GTP_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_ADVANCED_WAP_WSP_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_ADVANCED_UNENCRYPED_JABBER_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_ADVANCED_PPTP_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_CLASS_MAIL_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_CLASSIFICATION_RESULT),
    IPQ_ENUM_TO_STRING(PACE2_CDC_RESULT),
    IPQ_ENUM_TO_STRING(PACE2_LICENSE_EXCEEDED_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_ADVANCED_IRC_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_FLOW_INFO_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_FLOW_PROCESS_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_SUBSCRIBER_PROCESS_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_CDD_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_ADVANCED_H323_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_TCP_STARTED_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_TCP_CLOSED_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_ADVANCED_HI5_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_BASIC_SSL_DNS_ALT_NAMES_EVENT),
    IPQ_ENUM_TO_STRING(PACE2_BASIC_DISSECTOR_METADATA_EVENT),

    IPQ_ENUM_TO_STRING(PACE2_NUMBER_OF_EVENTS)
};

static char const * const pace2_http_request_line_to_string[] = {
    "PACE2_HTTP_REQUEST_METHOD",
    "PACE2_HTTP_REQUEST_URI",
    "PACE2_HTTP_HOST",
    "PACE2_HTTP_USER_AGENT",
    "PACE2_HTTP_REFERER",
    "PACE2_HTTP_CONTENT_TYPE",
    "PACE2_HTTP_CONTENT_LENGTH",
    "PACE2_HTTP_ACCEPT",
    "PACE2_HTTP_ORIGIN",
    "PACE2_HTTP_COOKIE",
    "PACE2_HTTP_SOAP_ACTION",
    "PACE2_HTTP_X_FORWARDED_FOR",
    "PACE2_HTTP_X_SESSION_TYPE",
    "PACE2_HTTP_X_STREAM_TYPE",
    "PACE2_HTTP_X_ONLINE_HOST"
};

static char const * const pace2_http_response_line_to_string[] = {
    "PACE2_HTTP_SERVER_RESPONSE",
    "PACE2_HTTP_SERVER_CONTENT_TYPE",
    "PACE2_HTTP_SERVER_CONTENT_ENCODING",
    "PACE2_HTTP_SERVER_CONTENT_LENGTH",
    "PACE2_HTTP_TRANSFER_ENCODING",
    "PACE2_HTTP_SERVER",
    "PACE2_HTTP_SET_COOKIE_LINE"
};

static char const * const pace2_citrix_event_type_to_string[] = {
    "PACE2_CITRIX_INITIAL_PROGRAM",
    "PACE2_CITRIX_USERNAME",
    "PACE2_CITRIX_ADDRESS",
    "PACE2_CITRIX_PORT",
    "PACE2_CITRIX_CGP_PORT"
};

static char const * const pace2_basic_dhcp_event_type_to_string[] = {
    "PACE2_DHCP_BASIC_YOUR_IP_ADDR",
    "PACE2_DHCP_BASIC_CLIENT_MAC_ADDR",
    "PACE2_DHCP_BASIC_ADDR_LEASE_TIME",
    "PACE2_DHCP_BASIC_MESSAGE_TYPE"
};

static char const * const pace2_os_event_type_to_string[] = {
    "PACE2_OS_TYPE",
    "PACE2_OS_VERSION_STRING"
};

static char const * const pace2_os_det_os_type_to_string[] = {
    "PACE2_OS_NOT_YET_DETECTED",
    "PACE2_OS_NOT_DETECTED",
    "PACE2_OS_OTHER",
    "PACE2_OS_WINDOWS",
    "PACE2_OS_LINUX",
    "PACE2_OS_MACOS",
    "PACE2_OS_IOS",
    "PACE2_OS_SYMBIAN",
    "PACE2_OS_ANDROID",
    "PACE2_OS_BLACKBERRY",
    "PACE2_OS_WINDOWS_MOBILE"
};

static char const * const pace2_nat_event_type_to_string[] = {
    "PACE2_NAT_MAIN_OS",
    "PACE2_NAT_DECISION"
};

static char const * const pace2_nat_detected_to_string[] = {
    "NAT_NOT_DETECTED",
    "NAT_DETECTED"
};

static char const * const pace2_nat_direction_to_string[] = {
    "DESTINATION_SUBSCRIBER",
    "SOURCE_SUBSCRIBER"
};

static char const * const pace2_sip_event_type_to_string[] = {
    "PACE2_SIP_CALL_STATE",
    "PACE2_SIP_CALL_ATTR"
};

static char const * const pace2_sip_call_state_type_to_string[] = {
    "PACE2_SIP_CALL_UNKNOWN",
    "PACE2_SIP_CALL_SETUP",
    "PACE2_SIP_CALL_START",
    "PACE2_SIP_CALL_END"
};

static char const * const pace2_ssl_client_hello_to_string[] = {
    "PACE2_SSL_SERVER_NAME",
    "PACE2_SSL_CLIENT_SESSION_ID"
};

static char const * const pace2_ssl_server_hello_to_string[] = {
    "PACE2_SSL_SERIAL_NUMBER",
    "PACE2_SSL_VALIDITY_NOT_BEFORE",
    "PACE2_SSL_VALIDITY_NOT_AFTER",
    "PACE2_SSL_COUNTRY_NAME",
    "PACE2_SSL_POSTAL_CODE",
    "PACE2_SSL_STATE_OR_PROVINCE_NAME",
    "PACE2_SSL_LOCALITY_NAME",
    "PACE2_SSL_STREET_ADDRESS",
    "PACE2_SSL_ORGANIZATION_NAME",
    "PACE2_SSL_ORGANIZATIONAL_UNIT_NAME",
    "PACE2_SSL_COMMON_NAME",
    "PACE2_SSL_SERVER_SESSION_ID",
    "PACE2_SSL_CIPHER_SUITE"
};

static char const * const pace2_csi_packet_dir_to_string[] = {
    "IPOQUE_DIRECTION_UNKNOWN",
    "IPOQUE_DIRECTION_NOT_YET_DECIDED",
    "IPOQUE_CLIENT_TO_SERVER",
    "IPOQUE_SERVER_TO_CLIENT",
    "IPOQUE_CLIENT_TO_CLIENT",
    "IPOQUE_SERVER_TO_SERVER"
};

static char const * const pace2_csi_host_type_to_string[] = {
    "IPOQUE_HOST_TYPE_UNKNOWN",
    "IPOQUE_HOST_IS_SERVER",
    "IPOQUE_HOST_IS_CLIENT"
};

static char const * const pace2_rtp_event_type_to_string[] = {
    "PACE2_RTP_FLOW_STATS"
};

static char const * const pace2_tcp_event_type_to_string[] = {
    "PACE2_TCP_LATENCY_STATS",
    "PACE2_TCP_OUT_OF_ORDER_STATS",
    "PACE2_TCP_RETRANSMISSION_STATS"
};

static char const * const pace2_det_event_type_to_string[] = {
    "PACE2_DET_API_VERSION"
    "PACE2_DET_VERSION",
    "PACE2_DET_LICENSE"
};

static char const * const pace2_fp_state_to_string[] = {
    "IPOQUE_FP_NO_PACKET_NEEDED",
    "IPOQUE_FP_NEXT_PACKET_NEEDED",
    "IPOQUE_FP_NEXT_PACKET_WITH_CONSTRAINT"
};

static char const * const pace2_fp_dir_constraint_to_string[] = {
    "IPOQUE_FP_ANY_DIRECTION",
    "IPOQUE_FP_NEXT_PAYLOAD_PACKET_SAME_DIRECTION",
    "IPOQUE_FP_NEXT_PAYLOAD_PACKET_OTHER_DIRECTION"
};

/* Private Prototypes ***********************************************************/

static inline void ipq_pace2_print_event_string (FILE * f, PACE2_byte_buffer const * const string);
static inline void ipq_pace2_print_event_ipv4 (FILE * f, u32 ipv4_bnf);
static inline void ipq_pace2_print_event_mac_addr (FILE * f, PACE2_byte_buffer const * const buffer);
static inline void ipq_pace2_print_event_value (FILE * f, u64 value);
static inline void ipq_pace2_print_event_value_hex (FILE * f, u64 value);
static inline void ipq_pace2_print_event_raw (FILE * f, PACE2_byte_buffer const * const buffer);
static inline void ipq_pace2_print_translated (FILE * f, u8 value, char const * const * string_array, u8 array_len);
static inline void ipq_pace2_print_meta_type (FILE * f, u8 value, char const * const * string_array, u8 array_len);

static inline void ipq_pace2_subscriber_timeout_handler (FILE * f, PACE2_subscriber_dropped const * const subscriber_data);
static inline void ipq_pace2_http_request_event_handler (FILE * f, PACE2_basic_HTTP_request_event const * const http_meta_data);
static inline void ipq_pace2_http_response_event_handler (FILE * f, PACE2_basic_HTTP_response_event const * const http_meta_data);
static inline void ipq_pace2_citrix_event_handler (FILE * f, PACE2_citrix_event const * const citrix_meta_data);
static inline void ipq_pace2_basic_dhcp_event_handler (FILE * f, PACE2_basic_DHCP_event const * const dhcp_basic_meta_data);
static inline void ipq_pace2_os_event_handler (FILE * f, PACE2_OS_event const * const os_meta_data);
static inline void ipq_pace2_nat_event_handler (FILE * f, PACE2_NAT_event const * const nat_meta_data);
static inline void ipq_pace2_sip_event_handler (FILE * f, PACE2_basic_SIP_event const * const sip_meta_data);
static inline void ipq_pace2_ssl_client_hello_event_handler (FILE * f, PACE2_SSL_client_hello_event const * const ssl_meta_data);
static inline void ipq_pace2_ssl_server_hello_event_handler (FILE * f, PACE2_SSL_server_hello_event const * const ssl_meta_data);
static inline void ipq_pace2_ssl_dns_alt_names_event_handler (FILE * f, PACE2_SSL_dns_alt_names_event const * const ssl_meta_data);
static inline void ipq_pace2_sit_event_handler (FILE * f, PACE2_SIT_event const * const sit_meta_data);
static inline void ipq_pace2_csi_packet_dir_event_handler (FILE * f, PACE2_csi_packet_dir_event const * const csi_meta_data);
static inline void ipq_pace2_csi_host_type_event_handler (FILE * f, PACE2_csi_host_type_event const * const csi_meta_data);
static inline void ipq_pace2_rtp_event_handler (FILE * f, PACE2_RTP_event const * const rtp_meta_data);
static inline void ipq_pace2_rtcp_event_handler (FILE * f, PACE2_RTCP_event const * const rtcp_meta_data);
static inline void ipq_pace2_tcp_event_handler (FILE * f, PACE2_TCP_event const * const tcp_meta_data);
static inline void ipq_pace2_det_event_handler (FILE * f, PACE2_classification_status_event const * const det_meta_data);
static inline void ipq_pace2_fastpath_event_handler (FILE * f, PACE2_fastpath_event const * const fastpath_meta_data);
static inline void ipq_pace2_app_event_handler (FILE * f, PACE2_app_event const * const app_meta_data);
static inline void ipq_pace2_classification_handler (FILE * f, PACE2_classification_result_event const * const pace2_results);
static inline void ipq_pace2_license_handler (FILE * f, PACE2_license_event const * const pace2_results);
static inline void ipq_pace2_basic_dissector_metadata_event(FILE * f, PACE2_dissector_metadata_event const * const dissector_metadata);

/* Private Definitions **********************************************************/

static inline void ipq_pace2_print_event_string (FILE * f, PACE2_byte_buffer const * const string)
{
    if (string->len != 0 && string->ptr != NULL) {
        fprintf(f, "\tcontent: %.*s\n\tlength: %u\n", (u32) string->len, string->ptr, string->len);
    } else {
        fprintf(f, "\tno content available\n");
    }
}

static inline void ipq_pace2_print_event_ipv4 (FILE * f, u32 ipv4_bnf)
{
    struct in_addr ipv4 = {ipv4_bnf};
    PACE2_byte_buffer ipv4_str = {NULL, 0};

    ipv4_str.ptr = inet_ntoa(ipv4);
    ipv4_str.len = strlen(ipv4_str.ptr);

    ipq_pace2_print_event_string(f, &ipv4_str);
}

static inline void ipq_pace2_print_event_mac_addr (FILE * f, PACE2_byte_buffer const * const buffer)
{
    if (buffer != NULL && buffer->len == 6) {
        fprintf(f, "\tlength: %u\n\tcontent: %02x:%02x:%02x:%02x:%02x:%02x\n", buffer->len,
               (u8)buffer->ptr[0], (u8)buffer->ptr[1], (u8)buffer->ptr[2], (u8)buffer->ptr[3], (u8)buffer->ptr[4], (u8)buffer->ptr[5]);
    } else {
        fprintf(f, "\tno address or unsupported format\n");
    }

}

static inline void ipq_pace2_print_event_value (FILE * f, u64 value)
{
    fprintf(f, "\tvalue: %llu\n", value);
}

static inline void ipq_pace2_print_event_value_hex (FILE * f, u64 value)
{
    fprintf(f, "\tvalue: 0x%llx\n", value);
}

static inline void ipq_pace2_print_event_raw (FILE * f, PACE2_byte_buffer const * const buffer)
{
    if (buffer->len != 0 && buffer != NULL) {
        u32 i = 0;
        fprintf(f, "\tlength: %u\n\tcontent: 0x", buffer->len);
        for (i = 0; i < buffer->len; i++) {
            fprintf(f, "%02hhx", buffer->ptr[i]);
        }
        fprintf(f, "\n");
    }
}

static inline void ipq_pace2_print_translated (FILE * f, u8 value, char const * const * string_array, u8 array_len)
{
    if (value < array_len) {
        fprintf(f, "\ttranslated: %s\n", string_array[value]);
    } else {
        fprintf(f, "\ttranslated: unknown string\n");
    }
}

static inline void ipq_pace2_print_meta_type (FILE * f, u8 value, char const * const * string_array, u8 array_len)
{
    if (value < array_len) {
        fprintf(f, "\tmeta type: %s\n", string_array[value]);
    } else {
        fprintf(f, "\tmeta type: unknown\n");
    }
}

static inline char *ipq_pace2_ip_to_string(const PACE2_ip_address *ip, char *buffer)
{
    if (inet_ntop(ip->is_ip_v6?AF_INET6:AF_INET, &ip->address.ipv6, buffer, INET6_ADDRSTRLEN) == NULL) {
        buffer[0] = 0;
    }

    return buffer;
}

static inline void ipq_pace2_flow_info_handler(FILE * f, PACE2_flow_info const * const flow_info_data)
{
    if(flow_info_data == NULL) {
        return;
    }

    fprintf(f, "\tflow id: %llu\n", flow_info_data->flow_id);
    fprintf(f, "\tsrc id: %llu\n", flow_info_data->src_id);
    if(flow_info_data->src_port != 0)   fprintf(f, "\tsrc port: %u\n", ntohs(flow_info_data->src_port));
    fprintf(f, "\tdst id: %llu\n", flow_info_data->dst_id);
    if(flow_info_data->dst_port != 0)   fprintf(f, "\tdst port: %u\n", ntohs(flow_info_data->dst_port));
}

static inline void ipq_pace2_flow_process_handler(FILE * f, PACE2_flow_process const * const flow_process_data)
{
    if(flow_process_data == NULL) {
        return;
    }

    fprintf(f, "\tflow id: %llu\n", flow_process_data->flow_id);
    fprintf(f, "\ttotal bytes: %llu\n", flow_process_data->total_bytes);
    fprintf(f, "\ttotal payload: %llu\n", flow_process_data->bytes);
    fprintf(f, "\tmissing bytes: %llu\n", flow_process_data->missing_bytes);
    fprintf(f, "\tstart timestamp: %llu\n", flow_process_data->start_ts);
    fprintf(f, "\ttimestamp of last seen packet: %llu\n", flow_process_data->last_packet_ts);
}

static inline void ipq_pace2_subscriber_process_handler(FILE * f, PACE2_subscriber_process const * const subscriber_process_data)
{
    if(subscriber_process_data == NULL) {
        return;
    }

    fprintf(f, "\tsubscriber id: %llu\n", subscriber_process_data->subscriber_id);
    fprintf(f, "\ttotal bytes: %llu\n", subscriber_process_data->total_bytes);
    fprintf(f, "\tupload: %llu\n", subscriber_process_data->bytes_up);
    fprintf(f, "\tdownload: %llu\n", subscriber_process_data->bytes_down);
}

static inline void ipq_pace2_subscriber_timeout_handler (FILE * f, PACE2_subscriber_dropped const * const subscriber_data)
{
    if (subscriber_data == NULL) {
        return;
    }

    fprintf(f, "\tsubscriber id: %llu\n", subscriber_data->subscriber_id);
    fprintf(f, "\tsubscriber data: %p\n", subscriber_data->subscriber_user_data );
    fprintf(f, "\tReason: %d\n", subscriber_data->removal_reason );
}

static inline void ipq_pace2_detection_event_handler (FILE * f, PACE2DetectionResult const * const classification_result)
{
    if (classification_result == NULL) {
        return;
    }

    fprintf(f, "\tDetection result: proto: %u, subproto: %u, app: %u\n",
           classification_result->effective_protocol,
           classification_result->effective_subprotocol,
           classification_result->application_id);
}

static inline void ipq_pace2_http_request_event_handler (FILE * f, PACE2_basic_HTTP_request_event const * const http_meta_data)
{
    u8 iter = 0;
    if (http_meta_data == NULL || 0 == http_meta_data->meta_data_mask) {
        return;
    }


    for (iter = 0; iter < PACE2_NUMBER_OF_HTTP_REQUEST_FLAGS; iter++) {
        if (PACE2_MASK_INCLUDES_FLAG(http_meta_data->meta_data_mask, iter)) {
            ipq_pace2_print_meta_type(f, http_meta_data->line[iter].type,
                                      pace2_http_request_line_to_string,
                                      PACE2_STATIC_ARRAY_SIZE(pace2_http_request_line_to_string));
            ipq_pace2_print_event_string(f, &http_meta_data->line[iter].content);
        }
    }
}

static inline void ipq_pace2_http_response_event_handler (FILE * f, PACE2_basic_HTTP_response_event const * const http_meta_data)
{
    u8 iter = 0;
    if (http_meta_data == NULL || 0 == http_meta_data->meta_data_mask) {
        return;
    }


    for (iter = 0; iter < PACE2_NUMBER_OF_HTTP_RESPONSE_FLAGS; iter++) {
        if (PACE2_MASK_INCLUDES_FLAG(http_meta_data->meta_data_mask, iter)) {
            ipq_pace2_print_meta_type(f, http_meta_data->line[iter].type,
                                      pace2_http_response_line_to_string,
                                      PACE2_STATIC_ARRAY_SIZE(pace2_http_response_line_to_string));
            ipq_pace2_print_event_string(f, &http_meta_data->line[iter].content);
        }
    }
}

static inline void ipq_pace2_citrix_event_handler (FILE * f, PACE2_citrix_event const * const citrix_meta_data)
{
    if (citrix_meta_data == NULL || citrix_meta_data->meta_data_mask == 0) {
        return;
    }

    if (PACE2_MASK_INCLUDES_FLAG(citrix_meta_data->meta_data_mask, PACE2_CITRIX_INITIAL_PROGRAM)) {
        ipq_pace2_print_meta_type(f, PACE2_CITRIX_INITIAL_PROGRAM,
                                  pace2_citrix_event_type_to_string,
                                  PACE2_STATIC_ARRAY_SIZE(pace2_citrix_event_type_to_string));
        ipq_pace2_print_event_string(f, &citrix_meta_data->initial_program);
    }
    if (PACE2_MASK_INCLUDES_FLAG(citrix_meta_data->meta_data_mask, PACE2_CITRIX_USERNAME)) {
        ipq_pace2_print_meta_type(f, PACE2_CITRIX_USERNAME,
                                  pace2_citrix_event_type_to_string,
                                  PACE2_STATIC_ARRAY_SIZE(pace2_citrix_event_type_to_string));
        ipq_pace2_print_event_string(f, &citrix_meta_data->username);
    }
    if (PACE2_MASK_INCLUDES_FLAG(citrix_meta_data->meta_data_mask, PACE2_CITRIX_ADDRESS)) {
        ipq_pace2_print_meta_type(f, PACE2_CITRIX_ADDRESS,
                                  pace2_citrix_event_type_to_string,
                                  PACE2_STATIC_ARRAY_SIZE(pace2_citrix_event_type_to_string));
        ipq_pace2_print_event_ipv4(f, citrix_meta_data->address);
    }
    if (PACE2_MASK_INCLUDES_FLAG(citrix_meta_data->meta_data_mask, PACE2_CITRIX_PORT)) {
        ipq_pace2_print_meta_type(f, PACE2_CITRIX_PORT,
                                  pace2_citrix_event_type_to_string,
                                  PACE2_STATIC_ARRAY_SIZE(pace2_citrix_event_type_to_string));
        ipq_pace2_print_event_value(f, ntohs(citrix_meta_data->port));
    }
    if (PACE2_MASK_INCLUDES_FLAG(citrix_meta_data->meta_data_mask, PACE2_CITRIX_CGP_PORT)) {
        ipq_pace2_print_meta_type(f, PACE2_CITRIX_CGP_PORT,
                                  pace2_citrix_event_type_to_string,
                                  PACE2_STATIC_ARRAY_SIZE(pace2_citrix_event_type_to_string));
        ipq_pace2_print_event_value(f, ntohs(citrix_meta_data->cgp_port));
    }
}

static inline void ipq_pace2_basic_dhcp_event_handler (FILE * f, PACE2_basic_DHCP_event const * const dhcp_basic_meta_data)
{
    if (dhcp_basic_meta_data == NULL || dhcp_basic_meta_data->meta_data_mask == 0) {
        return;
    }

    if (PACE2_MASK_INCLUDES_FLAG(dhcp_basic_meta_data->meta_data_mask, PACE2_BASIC_DHCP_YOUR_IP_ADDR)) {
        ipq_pace2_print_meta_type(f, PACE2_BASIC_DHCP_YOUR_IP_ADDR,
                                  pace2_basic_dhcp_event_type_to_string,
                                  PACE2_STATIC_ARRAY_SIZE(pace2_basic_dhcp_event_type_to_string));
        ipq_pace2_print_event_ipv4(f, dhcp_basic_meta_data->your_ip_addr);
    }
    if (PACE2_MASK_INCLUDES_FLAG(dhcp_basic_meta_data->meta_data_mask, PACE2_BASIC_DHCP_CLIENT_MAC_ADDR)) {
        ipq_pace2_print_meta_type(f, PACE2_BASIC_DHCP_CLIENT_MAC_ADDR,
                                  pace2_basic_dhcp_event_type_to_string,
                                  PACE2_STATIC_ARRAY_SIZE(pace2_basic_dhcp_event_type_to_string));
        ipq_pace2_print_event_mac_addr(f, &dhcp_basic_meta_data->client_mac_addr);
    }
    if (PACE2_MASK_INCLUDES_FLAG(dhcp_basic_meta_data->meta_data_mask, PACE2_BASIC_DHCP_ADDR_LEASE_TIME)) {
        ipq_pace2_print_meta_type(f, PACE2_BASIC_DHCP_ADDR_LEASE_TIME,
                                  pace2_basic_dhcp_event_type_to_string,
                                  PACE2_STATIC_ARRAY_SIZE(pace2_basic_dhcp_event_type_to_string));
        ipq_pace2_print_event_value(f, ntohl(dhcp_basic_meta_data->addr_lease_time));
    }
    if (PACE2_MASK_INCLUDES_FLAG(dhcp_basic_meta_data->meta_data_mask, PACE2_BASIC_DHCP_MESSAGE_TYPE)) {
        ipq_pace2_print_meta_type(f, PACE2_BASIC_DHCP_MESSAGE_TYPE,
                                  pace2_basic_dhcp_event_type_to_string,
                                  PACE2_STATIC_ARRAY_SIZE(pace2_basic_dhcp_event_type_to_string));
        ipq_pace2_print_event_value(f, dhcp_basic_meta_data->message_type);
    }
}

static inline void ipq_pace2_os_event_handler (FILE * f, PACE2_OS_event const * const os_meta_data)
{
    if (os_meta_data == NULL || os_meta_data->meta_data_mask == 0) {
        return;
    }

    if (PACE2_MASK_INCLUDES_FLAG(os_meta_data->meta_data_mask, PACE2_OS_TYPE)) {
        ipq_pace2_print_meta_type(f, PACE2_OS_TYPE,
                                  pace2_os_event_type_to_string,
                                  PACE2_STATIC_ARRAY_SIZE(pace2_os_event_type_to_string));
        ipq_pace2_print_event_value(f, os_meta_data->os_type);
        ipq_pace2_print_translated(f, os_meta_data->os_type,
                                   pace2_os_det_os_type_to_string,
                                   PACE2_STATIC_ARRAY_SIZE(pace2_os_det_os_type_to_string));
    }
    if (PACE2_MASK_INCLUDES_FLAG(os_meta_data->meta_data_mask, PACE2_OS_VERSION_STRING)) {
        ipq_pace2_print_meta_type(f, PACE2_OS_VERSION_STRING,
                                  pace2_os_event_type_to_string,
                                  PACE2_STATIC_ARRAY_SIZE(pace2_os_event_type_to_string));
        ipq_pace2_print_event_string(f, &os_meta_data->os_version_string);
    }
}

static inline void ipq_pace2_nat_event_handler (FILE * f, PACE2_NAT_event const * const nat_meta_data)
{

    if (nat_meta_data == NULL || nat_meta_data->meta_data_mask == 0) {
        return;
    }

    if (PACE2_MASK_INCLUDES_FLAG(nat_meta_data->meta_data_mask, PACE2_NAT_MAIN_OS)) {
        ipq_pace2_print_meta_type(f, PACE2_NAT_MAIN_OS,
                                  pace2_nat_event_type_to_string,
                                  PACE2_STATIC_ARRAY_SIZE(pace2_nat_event_type_to_string));
        ipq_pace2_print_event_value(f, nat_meta_data->nat_main_os);
        ipq_pace2_print_translated(f, nat_meta_data->nat_main_os,
                                   pace2_os_det_os_type_to_string,
                                   PACE2_STATIC_ARRAY_SIZE(pace2_os_det_os_type_to_string));
    }
    if (PACE2_MASK_INCLUDES_FLAG(nat_meta_data->meta_data_mask, PACE2_NAT_DECISION)) {
        ipq_pace2_print_meta_type(f, PACE2_NAT_DECISION,
                                  pace2_nat_event_type_to_string,
                                  PACE2_STATIC_ARRAY_SIZE(pace2_nat_event_type_to_string));
        ipq_pace2_print_translated(f, nat_meta_data->nat_decision.detected_nat,
                                   pace2_nat_detected_to_string,
                                   PACE2_STATIC_ARRAY_SIZE(pace2_nat_detected_to_string));
        ipq_pace2_print_translated(f, nat_meta_data->nat_decision.of_source,
                                   pace2_nat_direction_to_string,
                                   PACE2_STATIC_ARRAY_SIZE(pace2_nat_direction_to_string));
    }
}

static inline void ipq_pace2_sip_event_handler (FILE * f, PACE2_basic_SIP_event const * const sip_meta_data)
{
    if (sip_meta_data == NULL || sip_meta_data->meta_data_mask == 0) {
        return;
    }

    if (PACE2_MASK_INCLUDES_FLAG(sip_meta_data->meta_data_mask, PACE2_SIP_CALL_STATE)) {
        ipq_pace2_print_meta_type(f, PACE2_SIP_CALL_STATE,
                                  pace2_sip_event_type_to_string,
                                  PACE2_STATIC_ARRAY_SIZE(pace2_sip_event_type_to_string));
        ipq_pace2_print_event_value(f, sip_meta_data->call_state);
        ipq_pace2_print_translated(f, sip_meta_data->call_state,
                                   pace2_sip_call_state_type_to_string,
                                   PACE2_STATIC_ARRAY_SIZE(pace2_sip_call_state_type_to_string));
    }
    if (PACE2_MASK_INCLUDES_FLAG(sip_meta_data->meta_data_mask, PACE2_SIP_CALL_ATTR)) {
        ipq_pace2_print_meta_type(f, PACE2_SIP_CALL_ATTR,
                                  pace2_sip_event_type_to_string,
                                  PACE2_STATIC_ARRAY_SIZE(pace2_sip_event_type_to_string));
        fprintf(f, "\tcall from:\n");
        ipq_pace2_print_event_string(f, &sip_meta_data->call_attr.from);
        fprintf(f, "\tcall to:\n");
        ipq_pace2_print_event_string(f, &sip_meta_data->call_attr.to);
        fprintf(f, "\tcall id:\n");
        ipq_pace2_print_event_string(f, &sip_meta_data->call_attr.id);
    }
}

static inline void ipq_pace2_ssl_client_hello_event_handler (FILE * f, PACE2_SSL_client_hello_event const * const ssl_meta_data)
{
    u8 iter = 0;
    if (ssl_meta_data == NULL || ssl_meta_data->meta_data_mask == 0) {
        return;
    }

    for (iter = 0; iter < PACE2_NUMBER_OF_CLIENT_HELLO_LINES; iter++) {
        if (PACE2_MASK_INCLUDES_FLAG(ssl_meta_data->meta_data_mask, iter)) {
            ipq_pace2_print_meta_type(f, ssl_meta_data->line[iter].type,
                                      pace2_ssl_client_hello_to_string,
                                      PACE2_STATIC_ARRAY_SIZE(pace2_ssl_client_hello_to_string));
            if (ssl_meta_data->line[iter].type == PACE2_SSL_CLIENT_SESSION_ID) {
                ipq_pace2_print_event_raw(f, &ssl_meta_data->line[iter].content);
            } else {
                ipq_pace2_print_event_string(f, &ssl_meta_data->line[iter].content);
            }
        }
    }
}

static inline void ipq_pace2_ssl_server_hello_event_handler (FILE * f, PACE2_SSL_server_hello_event const * const ssl_meta_data)
{
    u8 iter = 0;
    if (ssl_meta_data == NULL || ssl_meta_data->meta_data_mask == 0) {
        return;
    }

    for (iter = 0; iter < PACE2_NUMBER_OF_SERVER_HELLO_LINES; iter++) {
        if (PACE2_MASK_INCLUDES_FLAG(ssl_meta_data->meta_data_mask, iter)) {
            ipq_pace2_print_meta_type(f, ssl_meta_data->line[iter].type,
                                      pace2_ssl_server_hello_to_string,
                                      PACE2_STATIC_ARRAY_SIZE(pace2_ssl_server_hello_to_string));
            if (ssl_meta_data->line[iter].type == PACE2_SSL_SERIAL_NUMBER ||
                ssl_meta_data->line[iter].type == PACE2_SSL_SERVER_SESSION_ID)
            {
                ipq_pace2_print_event_raw(f, &ssl_meta_data->line[iter].content);
            } else if (ssl_meta_data->line[iter].type == PACE2_SSL_CIPHER_SUITE) {
                ipq_pace2_print_event_value_hex(f, *((u64 *)ssl_meta_data->line[iter].content.ptr));
            } else {
                ipq_pace2_print_event_string(f, &ssl_meta_data->line[iter].content);
            }
        }
    }
}

static inline void ipq_pace2_ssl_dns_alt_names_event_handler (FILE * f, PACE2_SSL_dns_alt_names_event const * const ssl_meta_data)
{
    u16 iter = 0;
    if (ssl_meta_data == NULL) {
        return;
    }

    for (iter = 0; iter < ssl_meta_data->number_of_entries; iter++) {
        ipq_pace2_print_event_string(f, &ssl_meta_data->entries[iter]);
    }
}

static inline void ipq_pace2_sit_event_handler (FILE * f, PACE2_SIT_event const * const sit_meta_data)
{
    if (sit_meta_data == NULL) {
        return;
    }

    fprintf(f, "\tinserted ID's:\n");
    ipq_pace2_print_event_value(f, sit_meta_data->sit_stats.id_inserts);
    fprintf(f, "\tsuccessful ID lookups:\n");
    ipq_pace2_print_event_value(f, sit_meta_data->sit_stats.id_lookup_successful);
    fprintf(f, "\tfailed ID lookups:\n");
    ipq_pace2_print_event_value(f, sit_meta_data->sit_stats.id_lookup_failed);
    fprintf(f, "\tmaximum number of elements:\n");
    ipq_pace2_print_event_value(f, sit_meta_data->sit_stats.maximum_number_of_elements);
    fprintf(f, "\tused elements:\n");
    ipq_pace2_print_event_value(f, sit_meta_data->sit_stats.currently_used_elements);
    fprintf(f, "\ttimestamp of oldest element:\n");
    ipq_pace2_print_event_value(f, sit_meta_data->sit_stats.ts_of_oldest_entry);
}

static inline void ipq_pace2_csi_packet_dir_event_handler (FILE * f, PACE2_csi_packet_dir_event const * const csi_meta_data)
{
    if (csi_meta_data == NULL) {
        return;
    }

    ipq_pace2_print_event_value(f, csi_meta_data->packet_dir);
    ipq_pace2_print_translated(f, csi_meta_data->packet_dir,
                               pace2_csi_packet_dir_to_string,
                               PACE2_STATIC_ARRAY_SIZE(pace2_csi_packet_dir_to_string));
}

static inline void ipq_pace2_csi_host_type_event_handler (FILE * f, PACE2_csi_host_type_event const * const csi_meta_data)
{
    if (csi_meta_data == NULL) {
        return;
    }

    fprintf(f, "\tsource host type:\n");
    ipq_pace2_print_event_value(f, csi_meta_data->src.host_type);
    ipq_pace2_print_translated(f, csi_meta_data->src.host_type,
                               pace2_csi_host_type_to_string,
                               PACE2_STATIC_ARRAY_SIZE(pace2_csi_host_type_to_string));
    fprintf(f, "\tratio of client connections: %i\n", csi_meta_data->src.percentage_of_client_connections);

    fprintf(f, "\tdestination host type:\n");
    ipq_pace2_print_event_value(f, csi_meta_data->dst.host_type);
    ipq_pace2_print_translated(f, csi_meta_data->dst.host_type,
                               pace2_csi_host_type_to_string,
                               PACE2_STATIC_ARRAY_SIZE(pace2_csi_host_type_to_string));
    fprintf(f, "\tratio of client connections: %i\n", csi_meta_data->dst.percentage_of_client_connections);
}

static inline void ipq_pace2_rtp_event_handler (FILE * f, PACE2_RTP_event const * const rtp_meta_data)
{
    if (rtp_meta_data == NULL || rtp_meta_data->meta_data_mask == 0) {
        return;
    }

    if (PACE2_MASK_INCLUDES_FLAG(rtp_meta_data->meta_data_mask, PACE2_RTP_FLOW_STATS)) {
        ipq_pace2_print_meta_type(f, PACE2_RTP_FLOW_STATS,
                                  pace2_rtp_event_type_to_string,
                                  PACE2_STATIC_ARRAY_SIZE(pace2_rtp_event_type_to_string));
        fprintf(f, "\tpackets_sent[0]: %i packets_sent[1]: %i\n", rtp_meta_data->flow_stats.packets_sent[0], rtp_meta_data->flow_stats.packets_sent[1]);
        fprintf(f, "\tpackets_lost[0]: %i packets_lost[1]: %i\n", rtp_meta_data->flow_stats.packets_lost[0], rtp_meta_data->flow_stats.packets_lost[1]);
        fprintf(f, "\tcurrent_jitter[0]: %i current_jitter[1]: %i\n", rtp_meta_data->flow_stats.current_jitter[0], rtp_meta_data->flow_stats.current_jitter[1]);
        fprintf(f, "\tcurrent_frequency[0]: %i current_frequency[1]: %i\n", rtp_meta_data->flow_stats.current_frequency[0], rtp_meta_data->flow_stats.current_frequency[1]);
        fprintf(f, "\tpayload_type: %i\n", rtp_meta_data->flow_stats.payload_type);
        fprintf(f, "\tpackets_overhead[0]: %i packets_overhead[1]: %i\n", rtp_meta_data->flow_stats.packets_overhead[0], rtp_meta_data->flow_stats.packets_overhead[1]);
    }
}

static inline void ipq_pace2_rtcp_event_handler (FILE * f, PACE2_RTCP_event const * const rtcp_meta_data)
{
    if (rtcp_meta_data == NULL) {
        return;
    }

    fprintf(f, "\tdirection: %i\n", rtcp_meta_data->rtcp_report.direction);
    fprintf(f, "\tfraction_lost: %i\n", rtcp_meta_data->rtcp_report.fraction_lost);
    fprintf(f, "\tpackets_lost: %i\n", rtcp_meta_data->rtcp_report.packets_lost);
    fprintf(f, "\tjitter: %i\n", rtcp_meta_data->rtcp_report.jitter);
    fprintf(f, "\tlsr: %i\n", rtcp_meta_data->rtcp_report.lsr);
    fprintf(f, "\tdlsr: %i\n", rtcp_meta_data->rtcp_report.dlsr);
}

static inline void ipq_pace2_tcp_event_handler (FILE * f, PACE2_TCP_event const * const tcp_meta_data)
{
    if (tcp_meta_data == NULL || tcp_meta_data->meta_data_mask == 0) {
        return;
    }

    if (PACE2_MASK_INCLUDES_FLAG(tcp_meta_data->meta_data_mask, PACE2_TCP_LATENCY_STATS)) {
        ipq_pace2_print_meta_type(f, PACE2_TCP_LATENCY_STATS,
                                  pace2_tcp_event_type_to_string,
                                  PACE2_STATIC_ARRAY_SIZE(pace2_tcp_event_type_to_string));
        if (tcp_meta_data->latency_stats.diff_syn_synack_possible == 1) {
            fprintf(f, "\tdiff_syn_synack: %i\n", tcp_meta_data->latency_stats.diff_syn_synack);
        }
        if (tcp_meta_data->latency_stats.diff_synack_ack_possible == 1) {
            fprintf(f, "\tdiff_synack_ack: %i\n", tcp_meta_data->latency_stats.diff_synack_ack);
        }
    }
    if (PACE2_MASK_INCLUDES_FLAG(tcp_meta_data->meta_data_mask, PACE2_TCP_OUT_OF_ORDER_STATS)) {
        ipq_pace2_print_meta_type(f, PACE2_TCP_OUT_OF_ORDER_STATS,
                                  pace2_tcp_event_type_to_string,
                                  PACE2_STATIC_ARRAY_SIZE(pace2_tcp_event_type_to_string));
        fprintf(f, "\tflow_ooo_counter: %i\n", tcp_meta_data->out_of_order_stats.flow_ooo_counter);
        fprintf(f, "\tflow_retransmission_counter: %i\n", tcp_meta_data->out_of_order_stats.flow_retransmission_counter);
    }
    if (PACE2_MASK_INCLUDES_FLAG(tcp_meta_data->meta_data_mask, PACE2_TCP_RETRANSMISSION_STATS)) {
        ipq_pace2_print_meta_type(f, PACE2_TCP_RETRANSMISSION_STATS,
                                  pace2_tcp_event_type_to_string,
                                  PACE2_STATIC_ARRAY_SIZE(pace2_tcp_event_type_to_string));
        ipq_pace2_print_event_value(f, tcp_meta_data->retransmission_stats);
    }
}

static inline void ipq_pace2_det_event_handler (FILE * f, PACE2_classification_status_event const * const det_meta_data)
{
    PACE2_byte_buffer string = {NULL, 0};
    if (det_meta_data == NULL || det_meta_data->meta_data_mask == 0) {
        return;
    }

    if (PACE2_MASK_INCLUDES_FLAG(det_meta_data->meta_data_mask, PACE2_CLASSIFICATION_API_VERSION)) {
        ipq_pace2_print_meta_type(f, PACE2_CLASSIFICATION_API_VERSION,
                                  pace2_det_event_type_to_string,
                                  PACE2_STATIC_ARRAY_SIZE(pace2_det_event_type_to_string));
        ipq_pace2_print_event_value(f, det_meta_data->api_version);
    }
    if (PACE2_MASK_INCLUDES_FLAG(det_meta_data->meta_data_mask, PACE2_CLASSIFICATION_VERSION)) {
        ipq_pace2_print_meta_type(f, PACE2_CLASSIFICATION_VERSION,
                                  pace2_det_event_type_to_string,
                                  PACE2_STATIC_ARRAY_SIZE(pace2_det_event_type_to_string));
        IPQ_INIT_STRING_BUF(string, det_meta_data->version.build_string);
        ipq_pace2_print_event_string(f, &string);
    }
    if (PACE2_MASK_INCLUDES_FLAG(det_meta_data->meta_data_mask, PACE2_CLASSIFICATION_LICENSE)) {
        ipq_pace2_print_meta_type(f, PACE2_CLASSIFICATION_LICENSE,
                                  pace2_det_event_type_to_string,
                                  PACE2_STATIC_ARRAY_SIZE(pace2_det_event_type_to_string));
        fprintf(f, "\tinit error:\n");
        ipq_pace2_print_event_value(f, det_meta_data->license.init_error_code);
        IPQ_INIT_STRING_BUF(string, det_meta_data->license.init_error_reason);
        ipq_pace2_print_event_string(f, &string);

        fprintf(f, "\tload error:\n");
        ipq_pace2_print_event_value(f, det_meta_data->license.load_error_code);
        IPQ_INIT_STRING_BUF(string, det_meta_data->license.load_error_reason);
        ipq_pace2_print_event_string(f, &string);

        fprintf(f, "\tvalidation error:\n");
        ipq_pace2_print_event_value(f, det_meta_data->license.validation_error_code);
        IPQ_INIT_STRING_BUF(string, det_meta_data->license.validation_error_reason);
        ipq_pace2_print_event_string(f, &string);

        fprintf(f, "\tlimitation error:\n");
        ipq_pace2_print_event_value(f, det_meta_data->license.limitation_error_code);
        IPQ_INIT_STRING_BUF(string, det_meta_data->license.limitation_error_reason);
        ipq_pace2_print_event_string(f, &string);

        fprintf(f, "\tnumber of valid mac addresses:\n");
        ipq_pace2_print_event_value(f, det_meta_data->license.no_of_mac_addresses_found);

        fprintf(f, "\tratio of current bandwidth to the bandwidth limit:\n");
        ipq_pace2_print_event_value(f, det_meta_data->license.current_percentage_bandwidth_limit_usage);
    }
}

static inline void ipq_pace2_fastpath_event_handler (FILE * f, PACE2_fastpath_event const * const fastpath_meta_data)
{
    if (fastpath_meta_data == NULL) {
        return;
    }

    ipq_pace2_print_event_value(f, fastpath_meta_data->fastpath.state);
    ipq_pace2_print_translated(f, fastpath_meta_data->fastpath.state,
                               pace2_fp_state_to_string,
                               PACE2_STATIC_ARRAY_SIZE(pace2_fp_state_to_string));
    fprintf(f, "\tfastpath direction constraint:\n");
    ipq_pace2_print_event_value(f, fastpath_meta_data->fastpath.state);
    ipq_pace2_print_translated(f, fastpath_meta_data->fastpath.direction,
                               pace2_fp_dir_constraint_to_string,
                               PACE2_STATIC_ARRAY_SIZE(pace2_fp_dir_constraint_to_string));
    fprintf(f, "\tskip_time_set: %u\n", fastpath_meta_data->fastpath.skip_time_set);
    fprintf(f, "\tskip_until_time: %u\n", fastpath_meta_data->fastpath.skip_until_time);
}

static inline void ipq_pace2_app_event_handler (FILE * f, PACE2_app_event const * const app_meta_data)
{
    if (app_meta_data == NULL) {
        return;
    }

    ipq_pace2_print_event_string(f, &app_meta_data->app_version);
}

static inline void ipq_pace2_classification_handler (FILE * f, PACE2_classification_result_event const * const pace2_results)
{
    u8 i;
    char const * c_string = NULL;

    if (pace2_results == NULL) {
        return;
    }

    fprintf(f, "PACE Classification resuls\n");
    fprintf(f, "\tProtocol-Stack: ");
    for (i = 0; i < pace2_results->protocol.stack.length; ++i) {
        c_string = pace2_get_protocol_short_str(pace2_results->protocol.stack.entry[i]);
        if ( i > 0 ) {
            fprintf( f, ", " );
        }
        if (c_string != NULL) {
            fprintf(f, "%s", c_string);
        }
    }
    fprintf( f, "\n" );

    c_string = pace2_get_application_short_str(pace2_results->application.type);
    if (c_string != NULL) {
        fprintf(f, "\tApplication: %s\n", c_string);
    }

    fprintf( f, "\tApplication Attributes: ");
    for ( i = 0; i < PACE2_APPLICATION_ATTRIBUTE_LIST_MAX_SIZE; ++i) {
        /* only print attribute none once */
        if ( i > 0 ) {
            if (pace2_results->application.attributes.list[i] == PACE2_APPLICATION_ATTRIBUTE_NONE) {
                break;
            }
            fprintf( f, ", " );
        }
        c_string = pace2_get_application_attribute_str(pace2_results->application.attributes.list[i]);
        if (c_string != NULL) {
            fprintf(f, "%s", c_string);
        }
    }
    fprintf( f, "\n");

    fprintf( f, "\tProtocol Attributes: ");
    for ( i = 0; i < PACE2_PROTOCOL_ATTRIBUTE_LIST_MAX_SIZE; ++i) {
        /* only print attribute none once */
        if ( i > 0 ) {
            if (pace2_results->protocol.attributes.list[i] == PACE2_PROTOCOL_ATTRIBUTE_NONE) {
                break;
            }
            fprintf( f, ", " );
        }
        c_string = pace2_get_protocol_attribute_str(pace2_results->protocol.attributes.list[i]);
        if (c_string != NULL) {
            fprintf(f, "%s", c_string);
        }
    }
    fprintf( f, "\n");
}

static inline void ipq_pace2_license_handler (FILE * f, PACE2_license_event const * const pace2_results)
{
    PACE2_byte_buffer string = {NULL, 0};

    fprintf(f, "\tinit error:\n");
    ipq_pace2_print_event_value(f, pace2_results->license.init_error_code);
    IPQ_INIT_STRING_BUF(string, pace2_results->license.init_error_reason);
    ipq_pace2_print_event_string(f, &string);

    fprintf(f, "\tload error:\n");
    ipq_pace2_print_event_value(f, pace2_results->license.load_error_code);
    IPQ_INIT_STRING_BUF(string, pace2_results->license.load_error_reason);
    ipq_pace2_print_event_string(f, &string);

    fprintf(f, "\tvalidation error:\n");
    ipq_pace2_print_event_value(f, pace2_results->license.validation_error_code);
    IPQ_INIT_STRING_BUF(string, pace2_results->license.validation_error_reason);
    ipq_pace2_print_event_string(f, &string);

    fprintf(f, "\tlimitation error:\n");
    ipq_pace2_print_event_value(f, pace2_results->license.limitation_error_code);
    IPQ_INIT_STRING_BUF(string, pace2_results->license.limitation_error_reason);
    ipq_pace2_print_event_string(f, &string);

    fprintf(f, "\tnumber of valid mac addresses:\n");
    ipq_pace2_print_event_value(f, pace2_results->license.no_of_mac_addresses_found);

    fprintf(f, "\tratio of current bandwidth to the bandwidth limit:\n");
    ipq_pace2_print_event_value(f, pace2_results->license.current_percentage_bandwidth_limit_usage);
}

static inline void ipq_pace2_basic_dissector_metadata_event(FILE * f,
                                                            PACE2_dissector_metadata_event const * const dissector_metadata)
{
    if (dissector_metadata == NULL) {
        return;
    }

    switch (dissector_metadata->metadata_type) {
    case DISSECTOR_IP:
    {
        u8 dir;

        for (dir = 0; dir < 2; dir++) {
            fprintf(f, "\tChecksum dir %u: (Invalid: %u)\n", dir, dissector_metadata->metadata.ip.invalid_checksums[dir]);
            fprintf(f, "\tPacket size dir %u: (Min: %u Bytes Max: %u Bytes Avg: %u Bytes)\n ",
                    dir,
                    dissector_metadata->metadata.ip.packet_size[dir].min,
                    dissector_metadata->metadata.ip.packet_size[dir].max,
                    dissector_metadata->metadata.ip.packet_size[dir].avg);

            fprintf(f, "\tThroughput Total dir %u: (Min: %llu Bytes/s Max: %llu Bytes/s Avg: %llu Bytes/s)\n",
                    dir, dissector_metadata->metadata.ip.throughput[dir].min,
                    dissector_metadata->metadata.ip.throughput[dir].max,
                    dissector_metadata->metadata.ip.throughput[dir].avg);

            fprintf(f, "\tThroughput interval dir %u: (%llu Bytes/s Duration %u s)\n", dir,
                    dissector_metadata->metadata.ip.throughput_interval[dir],
                    dissector_metadata->metadata.ip.interval_duration[dir]);
        }

        break;
    }
    case DISSECTOR_TCP:
    {
        fprintf(f, "\tWindow sizes current: %u - %u\n",
                dissector_metadata->metadata.tcp.window_size[0].cur,
                dissector_metadata->metadata.tcp.window_size[1].cur);
        fprintf(f, "\tWindow sizes min: %u - %u\n",
                dissector_metadata->metadata.tcp.window_size[0].min,
                dissector_metadata->metadata.tcp.window_size[1].min);
        fprintf(f, "\tWindow sizes max: %u - %u\n",
                dissector_metadata->metadata.tcp.window_size[0].max,
                dissector_metadata->metadata.tcp.window_size[1].max);
        fprintf(f, "\tWindow sizes avg: %u - %u\n",
                dissector_metadata->metadata.tcp.window_size[0].avg,
                dissector_metadata->metadata.tcp.window_size[1].avg);
        fprintf(f, "\tWindow scales: %u - %u\n",
                dissector_metadata->metadata.tcp.window_scale[0].value,
                dissector_metadata->metadata.tcp.window_scale[0].value);
        fprintf(f, "\tInvalid checksums: %u - %u\n",
                dissector_metadata->metadata.tcp.invalid_checksums[0],
                dissector_metadata->metadata.tcp.invalid_checksums[1]);
        fprintf(f, "\tOOO packets: %u \n",
                dissector_metadata->metadata.tcp.ooo_packets);
        fprintf(f, "\tRetransmission: %u \n",
                dissector_metadata->metadata.tcp.retransmissions);
        fprintf(f, "\tMSS: %u \n",
                dissector_metadata->metadata.tcp.max_segment_size);
        fprintf(f, "\tNetwork limit: %llu Bps\n",
                dissector_metadata->metadata.tcp.network_limit);
        fprintf(f, "\tMax Throughput: %llu / %llu Bps\n",
                dissector_metadata->metadata.tcp.throughput_max[0],
                dissector_metadata->metadata.tcp.throughput_max[1]);

        fprintf(f, "\tRTT cur: %u\n", dissector_metadata->metadata.tcp.round_trip_time.cur);
        fprintf(f, "\tRTT min: %u\n", dissector_metadata->metadata.tcp.round_trip_time.min);
        fprintf(f, "\tRTT max: %u\n", dissector_metadata->metadata.tcp.round_trip_time.max);
        fprintf(f, "\tRTT avg: %u\n", dissector_metadata->metadata.tcp.round_trip_time.avg);

        break;
    }
    case DISSECTOR_H264:
    {
        u8 dir;

        for (dir = 0; dir < 2; dir++) {
            fprintf(f, "\tDirection %u\n", dir);
            fprintf(f, "\t\tBitrate: %.2f kbit/s\n", (double)dissector_metadata->metadata.h264.bitrate[dir] / 1000);
            fprintf(f, "\t\tFramerate: %u fps\n", dissector_metadata->metadata.h264.frame_rate[dir]);
            fprintf(f, "\t\tAvg. Framerate: %u fps\n", dissector_metadata->metadata.h264.avg_frame_rate[dir]);
            fprintf(f, "\t\tFrame count: %u (%u i-frames)\n",
                    dissector_metadata->metadata.h264.frame_count[dir],
                    dissector_metadata->metadata.h264.iframe_count[dir]);
            fprintf(f, "\t\tResolution: %ux%u\n",
                    dissector_metadata->metadata.h264.picture_width[dir],
                    dissector_metadata->metadata.h264.picture_height[dir]);
            fprintf(f, "\t\tAspect Ratio: %u:%u\n",
                    dissector_metadata->metadata.h264.aspect_ratio[dir].numerator,
                    dissector_metadata->metadata.h264.aspect_ratio[dir].divisor);
        }
        break;
    }
    case DISSECTOR_AMR:
    {
        u8 dir;

        for (dir = 0; dir < 2; dir++) {
            fprintf(f, "\tDirection %u\n", dir);
            fprintf(f, "\t\tBitrate: %.2f kbit/s\n", (double)dissector_metadata->metadata.amr.bitrate[dir] / 1000);
            fprintf(f, "\t\tDTX Silence: %s\n",
                    dissector_metadata->metadata.amr.dtx_silence_active[dir] == 1 ? "Active" : "Inactive");
        }

        break;
    }
    case DISSECTOR_RTP:
    {
        u8 dir;

        for (dir = 0; dir < 2; dir++) {
            fprintf(f, "\tDirection %u\n", dir);
            fprintf(f, "\t\tCodec: %s\n", dissector_metadata->metadata.rtp.codec_str[dir]);
            fprintf(f, "\t\tStream type: %s\n", dissector_metadata->metadata.rtp.stream_type_str[dir]);
        }

        break;
    }
    case DISSECTOR_ID3:
    {
        if (dissector_metadata->metadata.id3.frames.talb.ptr != NULL) {
            fprintf(f, "\t\tAlbum title: %.*s\n",
                    dissector_metadata->metadata.id3.frames.talb.len,
                    dissector_metadata->metadata.id3.frames.talb.ptr);
        }
        if (dissector_metadata->metadata.id3.frames.tit1.ptr != NULL) {
            fprintf(f, "\t\tContent group description: %.*s\n",
                    dissector_metadata->metadata.id3.frames.tit1.len,
                    dissector_metadata->metadata.id3.frames.tit1.ptr);
        }
        if (dissector_metadata->metadata.id3.frames.tit2.ptr != NULL) {
            fprintf(f, "\t\tTitle: %.*s\n",
                    dissector_metadata->metadata.id3.frames.tit2.len,
                    dissector_metadata->metadata.id3.frames.tit2.ptr);
        }
        if (dissector_metadata->metadata.id3.frames.tit3.ptr != NULL) {
            fprintf(f, "\t\tSubtitle: %.*s\n",
                    dissector_metadata->metadata.id3.frames.tit3.len,
                    dissector_metadata->metadata.id3.frames.tit3.ptr);
        }
        if (dissector_metadata->metadata.id3.frames.trck.ptr != NULL) {
            fprintf(f, "\t\tTrack number/Position in set: %.*s\n",
                    dissector_metadata->metadata.id3.frames.trck.len,
                    dissector_metadata->metadata.id3.frames.trck.ptr);
        }
        if (dissector_metadata->metadata.id3.frames.tpe1.ptr != NULL) {
            fprintf(f, "\t\tLead performer(s)/Soloist(s): %.*s\n",
                    dissector_metadata->metadata.id3.frames.tpe1.len,
                    dissector_metadata->metadata.id3.frames.tpe1.ptr);
        }
        if (dissector_metadata->metadata.id3.frames.tpe2.ptr != NULL) {
            fprintf(f, "\t\tBand/orchestra/accompaniment: %.*s\n",
                    dissector_metadata->metadata.id3.frames.tpe2.len,
                    dissector_metadata->metadata.id3.frames.tpe2.ptr);
        }
        if (dissector_metadata->metadata.id3.frames.tpe3.ptr != NULL) {
            fprintf(f, "\t\tConductor/performer refinement: %.*s\n",
                    dissector_metadata->metadata.id3.frames.tpe3.len,
                    dissector_metadata->metadata.id3.frames.tpe3.ptr);
        }
        if (dissector_metadata->metadata.id3.frames.tpe4.ptr != NULL) {
            fprintf(f, "\t\tInterpreted, remixed, or otherwise modified by: %.*s\n",
                    dissector_metadata->metadata.id3.frames.tpe4.len,
                    dissector_metadata->metadata.id3.frames.tpe4.ptr);
        }
        if (dissector_metadata->metadata.id3.frames.tcon.ptr != NULL) {
            fprintf(f, "\t\tContent type: %.*s\n",
                    dissector_metadata->metadata.id3.frames.tcon.len,
                    dissector_metadata->metadata.id3.frames.tcon.ptr);
        }

        break;
    }
    case DISSECTOR_MP3:
    {
        u8 dir;
        for (dir = 0; dir < 2; dir++) {
            if (dissector_metadata->metadata.mp3.audio[dir].sampling_rate != 0 &&
                dissector_metadata->metadata.mp3.audio[dir].bitrate != 0) {
                fprintf(f, "\tDirection %u\n", dir);
                fprintf(f, "\t\tSampling rate: %u\n", dissector_metadata->metadata.mp3.audio[dir].sampling_rate);
                fprintf(f, "\t\tBitrate kbit/s: %u\n", dissector_metadata->metadata.mp3.audio[dir].bitrate / 1000);
                fprintf(f, "\t\tChannel mode: %u\n", dissector_metadata->metadata.mp3.audio[dir].channel_mode);
                fprintf(f, "\t\tCopyright: %u\n", dissector_metadata->metadata.mp3.audio[dir].copyright);
                fprintf(f, "\t\tOriginal: %u\n", dissector_metadata->metadata.mp3.audio[dir].original);
                fprintf(f, "\t\tMPEG version ID: %u\n", dissector_metadata->metadata.mp3.audio[dir].version);
            }
        }
        break;
    }
    case DISSECTOR_HTTP:
    {
        if (dissector_metadata->metadata.http.content.done == 1 && dissector_metadata->metadata.http.content.type != 0) {
            fprintf(f, "HTTP dissector:\n");
            fprintf(f, "\t\tContent: %s\n", dissector_metadata->metadata.http.content.type_str);
        }
        break;
    }
    case DISSECTOR_MP4:
    {
        u8 dir;

        if (dissector_metadata->metadata.mp4.type[0] == STREAM_TYPE_UNKNOWN &&
            dissector_metadata->metadata.mp4.type[1] == STREAM_TYPE_UNKNOWN) {
            return;
        }

        for (dir = 0; dir < 2; dir++) {
            if (dissector_metadata->metadata.mp4.type[dir] == STREAM_TYPE_UNKNOWN) {
                continue;
            }

            fprintf(f, "\tDirection: %u\n", dir);
            fprintf(f, "\t\tStream type: %s\n", dissector_metadata->metadata.mp4.stream_type_str[dir]);
            fprintf(f, "\t\tDuration: %llus\n", dissector_metadata->metadata.mp4.duration[dir]);

            if (dissector_metadata->metadata.mp4.type[dir] == STREAM_TYPE_AUDIO ||
                dissector_metadata->metadata.mp4.type[dir] == STREAM_TYPE_AUDIO_VIDEO) {
                fprintf(f, "\t\tAudio data:\n");
                fprintf(f, "\t\t\tBitrate: %.2f kBit/s\n", (double)dissector_metadata->metadata.mp4.audio[dir].bitrate / 1000);
                fprintf(f, "\t\t\tCodec: %s\n", dissector_metadata->metadata.mp4.audio[dir].codec_str);
                fprintf(f, "\t\t\tSampling rate: %.2f kHz\n", (double)dissector_metadata->metadata.mp4.audio[dir].sampling_rate / 1000);
                fprintf(f, "\t\t\tChannels: %u\n", dissector_metadata->metadata.mp4.audio[dir].channels);
            }
            if (dissector_metadata->metadata.mp4.type[dir] == STREAM_TYPE_VIDEO ||
                dissector_metadata->metadata.mp4.type[dir] == STREAM_TYPE_AUDIO_VIDEO) {
                fprintf(f, "\t\tVideo data:\n");
                fprintf(f, "\t\t\tBitrate: %.2f kBit/s\n",
                        (double)dissector_metadata->metadata.mp4.video[dir].bitrate / 1000);
                fprintf(f, "\t\t\tCodec: %s\n", dissector_metadata->metadata.mp4.video[dir].codec_str);
                fprintf(f, "\t\t\tFrames: %u fps\n", dissector_metadata->metadata.mp4.video[dir].fps);
                fprintf(f, "\t\t\tResolution: %ux%u\n",
                        dissector_metadata->metadata.mp4.video[dir].width,
                        dissector_metadata->metadata.mp4.video[dir].height);
                fprintf(f, "\t\t\tColor depth: %u Bit\n", dissector_metadata->metadata.mp4.video[dir].color_depth);
                fprintf(f, "\t\t\tAspect ratio: %u:%u\n",
                        dissector_metadata->metadata.mp4.video[dir].aspect.numerator,
                        dissector_metadata->metadata.mp4.video[dir].aspect.divisor);
            }

        }
        break;
    }
#ifdef IPOQUE_ENABLE_MOS_CUST
    case DISSECTOR_MOS_CUST:
    {
        u8 dir;
        for (dir = 0; dir < 2; dir++) {
            if (dissector_metadata->metadata.mos_cust.type[dir] == 1) {
                fprintf(f, "\nMOS Cust Dissector:\n");
                fprintf(f, "\tDirection %u\n", dir);
                fprintf(f, "\t\tRTP based MOS:\n");

                if (dissector_metadata->metadata.mos_cust.values[dir].rtp.jitter != 0) {
                    fprintf(f, "\t\t\tJitter MOS:\t %d\n", dissector_metadata->metadata.mos_cust.values[dir].rtp.jitter);
                }
                if (dissector_metadata->metadata.mos_cust.values[dir].rtp.codec != 0) {
                    fprintf(f, "\t\t\tCodec MOS:\t %d\n", dissector_metadata->metadata.mos_cust.values[dir].rtp.codec);
                }
                if (dissector_metadata->metadata.mos_cust.values[dir].rtp.packetloss != 0) {
                    fprintf(f, "\t\t\tPacketloss MOS:\t %d\n", dissector_metadata->metadata.mos_cust.values[dir].rtp.packetloss);
                }
                if (dissector_metadata->metadata.mos_cust.values[dir].rtp.overall != 0) {
                    fprintf(f, "\t\t\tOverall MOS:\t %d\n", dissector_metadata->metadata.mos_cust.values[dir].rtp.overall);
                }
            } else if (dissector_metadata->metadata.mos_cust.type[dir] == 2) {
                fprintf(f, "\nMOS Cust Dissector:\n");
                fprintf(f, "\tDirection %u\n", dir);
                fprintf(f, "\t\tBuffered streaming based MOS:\n");

                if (dissector_metadata->metadata.mos_cust.values[dir].buffered.buffer != 0) {
                    fprintf(f, "\t\t\tBuffer MOS:\t %d\n", dissector_metadata->metadata.mos_cust.values[dir].buffered.buffer);
                }
                if (dissector_metadata->metadata.mos_cust.values[dir].buffered.codec != 0) {
                    fprintf(f, "\t\t\tCodec MOS:\t %d\n", dissector_metadata->metadata.mos_cust.values[dir].buffered.codec);
                }
                if (dissector_metadata->metadata.mos_cust.values[dir].buffered.overall != 0) {
                    fprintf(f, "\t\t\tOverall MOS:\t %d\n", dissector_metadata->metadata.mos_cust.values[dir].buffered.overall);
                }
            }
        }
        break;
    }
#endif
    default:
        break;
    }

}


/* Public Definitions ***********************************************************/

void pace2_debug_event(FILE * f, PACE2_event const * const event)
{
    if (event == NULL) {
        return;
    }

#ifdef static_assert
static_assert((int)PACE2_STATIC_ARRAY_SIZE(pace_event_type_to_string) == PACE2_NUMBER_OF_EVENTS + 1,
              "Size of pace_event_type_to_string is different to implemented events.");
#endif

    if (0 <= event->header.type && event->header.type < (int)PACE2_STATIC_ARRAY_SIZE(pace_event_type_to_string)) {
        fprintf(f, "got event: %s\n", pace_event_type_to_string[event->header.type]);
    } else {
        fprintf(f, "got unknown event: %i\n", event->header.type);
    }

    switch (event->header.type) {
    case PACE2_FLOW_STARTED_EVENT:
        fprintf(f, "\tflow id: %llu\n", ((const PACE2_flow_started*)event)->flow_id);
        return;
    case PACE2_FLOW_DROPPED_EVENT:
        fprintf(f, "\tflow id: %llu\n", ((const PACE2_flow_dropped*)event)->flow_id);
        fprintf(f, "\tReason : %d\n", ((const PACE2_flow_dropped*)event)->removal_reason);
        return;
    case PACE2_FLOW_INFO_EVENT:
        ipq_pace2_flow_info_handler(f, &event->flow_info);
        return;
    case PACE2_FLOW_PROCESS_EVENT:
        ipq_pace2_flow_process_handler(f, &event->flow_process);
        return;
    case PACE2_SUBSCRIBER_STARTED_EVENT:
    {
        char buffer[INET6_ADDRSTRLEN];
        fprintf(f, "\tsubscriber id: %llu\n", ((const PACE2_subscriber_started*)event)->subscriber_id);
        fprintf(f, "\tip: %s\n", ipq_pace2_ip_to_string(&((const PACE2_subscriber_started*)event)->ip, buffer));
        fprintf(f, "\tuse dst: %u\n", ((const PACE2_subscriber_started*)event)->track_dst);
    }
        return;
    case PACE2_SUBSCRIBER_DROPPED_EVENT:
        ipq_pace2_subscriber_timeout_handler(f, &event->subscriber_dropped);
        return;
    case PACE2_SUBSCRIBER_PROCESS_EVENT:
        ipq_pace2_subscriber_process_handler(f, &event->subscriber_process);
        return;
    case PACE2_DETECTION_RESULT:
        ipq_pace2_detection_event_handler(f, &event->detection_result);
        return;
    case PACE2_BASIC_HTTP_REQUEST_EVENT:
        ipq_pace2_http_request_event_handler(f, &event->http_basic_request_meta_data);
        return;
    case PACE2_BASIC_HTTP_RESPONSE_EVENT:
        ipq_pace2_http_response_event_handler(f, &event->http_basic_response_meta_data);
        return;
    case PACE2_BASIC_CITRIX_EVENT:
        ipq_pace2_citrix_event_handler(f, &event->citrix_meta_data);
        return;
    case PACE2_BASIC_DHCP_EVENT:
        ipq_pace2_basic_dhcp_event_handler(f, &event->dhcp_basic_meta_data);
        return;
    case PACE2_OS_EVENT:
        ipq_pace2_os_event_handler(f, &event->os_meta_data);
        return;
    case PACE2_NAT_EVENT:
        ipq_pace2_nat_event_handler(f, &event->nat_meta_data);
        return;
    case PACE2_BASIC_SIP_EVENT:
        ipq_pace2_sip_event_handler(f, &event->sip_basic_meta_data);
        return;
    case PACE2_BASIC_SSL_CLIENT_HELLO_EVENT:
        ipq_pace2_ssl_client_hello_event_handler(f, &event->ssl_client_hello_meta_data);
        return;
    case PACE2_BASIC_SSL_SERVER_HELLO_EVENT:
        ipq_pace2_ssl_server_hello_event_handler(f, &event->ssl_server_hello_meta_data);
        return;
    case PACE2_BASIC_SSL_DNS_ALT_NAMES_EVENT:
        ipq_pace2_ssl_dns_alt_names_event_handler(f, &event->ssl_dns_alt_names_meta_data);
        return;
    case PACE2_BASIC_SIT_EVENT:
        ipq_pace2_sit_event_handler(f, &event->sit_meta_data);
        return;
    case PACE2_CSI_PACKET_DIR_EVENT:
        ipq_pace2_csi_packet_dir_event_handler(f, &event->csi_packet_dir_meta_data);
        return;
    case PACE2_CSI_HOST_TYPE_EVENT:
        ipq_pace2_csi_host_type_event_handler(f, &event->csi_host_type_meta_data);
        return;
    case PACE2_BASIC_RTP_EVENT:
        ipq_pace2_rtp_event_handler(f, &event->rtp_meta_data);
        return;
    case PACE2_BASIC_RTCP_EVENT:
        ipq_pace2_rtcp_event_handler(f, &event->rtcp_meta_data);
        return;
    case PACE2_TCP_EVENT:
        ipq_pace2_tcp_event_handler(f, &event->tcp_meta_data);
        return;
    case PACE2_CLASSIFICATION_STATUS:
        ipq_pace2_det_event_handler(f, &event->classification_status_data);
        return;
    case PACE2_FASTPATH_EVENT:
        ipq_pace2_fastpath_event_handler(f, &event->fastpath_meta_data);
        return;
    case PACE2_APP_EVENT:
        ipq_pace2_app_event_handler(f, &event->app_meta_data);
        return;
    case PACE2_CLASSIFICATION_RESULT:
        ipq_pace2_classification_handler(f, &event->classification_result_data);
        return;
    case PACE2_LICENSE_EXCEEDED_EVENT:
        ipq_pace2_license_handler(f, &event->license_event);
        return;
    case PACE2_TCP_CLOSED_EVENT:
        fprintf(f, "\tTCP connection closed.\n");
        fprintf(f, "\tflow id: %llu\n", ((const PACE2_TCP_closed_event*)event)->flow_id);
        fprintf(f, "\tReason: %d\n", ((const PACE2_TCP_closed_event*)event)->close_reason);
        return;
    case PACE2_TCP_STARTED_EVENT:
        fprintf(f, "\tTCP connection started.\n");
        fprintf(f, "\tflow id: %llu\n", ((const PACE2_TCP_started_event*)event)->flow_id);
        return;
    case PACE2_BASIC_DISSECTOR_METADATA_EVENT:
        ipq_pace2_basic_dissector_metadata_event(f, &event->dissector_metadata);
        return;
    }

    // Print out advanced & class events
    pace2_debug_advanced_event(f, event);

}
