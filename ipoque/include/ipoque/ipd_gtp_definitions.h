/********************************************************************************/
/**
 ** \file       ipd_gtp_definitions.h
 ** \brief      Structures and enumerations for all events of the GTP Protocol.
 **/
/********************************************************************************/

#ifndef __IPOQUE_DECODER_GTP_INCLUDE_FILE__
#define __IPOQUE_DECODER_GTP_INCLUDE_FILE__

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif


/**
 * Enumeration for message types of GTPv1 and GTP'. For more details see TS 29060 and TS 32295.
 */
enum ipd_gtp_v1_message_type_enum
{
    IPD_GTP_V1_MESSAGE_TYPE_ECHO_REQUEST = 1,
    IPD_GTP_V1_MESSAGE_TYPE_ECHO_RESPONSE = 2,
    IPD_GTP_V1_MESSAGE_TYPE_VERSION_NOT_SUPPORTED = 3,
    IPD_GTP_V1_MESSAGE_TYPE_NODE_ALIVE_REQ = 4,
    IPD_GTP_V1_MESSAGE_TYPE_NODE_ALIVE_RESP = 5,
    IPD_GTP_V1_MESSAGE_TYPE_REDIRECT_REQ = 6,
    IPD_GTP_V1_MESSAGE_TYPE_REDIRECT_RESP = 7,
    IPD_GTP_V1_MESSAGE_TYPE_CREATE_PDU_CONTEXT_REQ = 16,
    IPD_GTP_V1_MESSAGE_TYPE_CREATE_PDU_CONTEXT_RESP = 17,
    IPD_GTP_V1_MESSAGE_TYPE_UPDATE_PDU_CONTEXT_REQ = 18,
    IPD_GTP_V1_MESSAGE_TYPE_UPDATE_PDU_CONTEXT_RESP = 19,
    IPD_GTP_V1_MESSAGE_TYPE_DELETE_PDU_CONTEXT_REQ = 20,
    IPD_GTP_V1_MESSAGE_TYPE_DELETE_PDU_CONTEXT_RESP = 21,
    IPD_GTP_V1_MESSAGE_TYPE_INIT_PDU_CONTEXT_ACT_REQ = 22,
    IPD_GTP_V1_MESSAGE_TYPE_INIT_PDU_CONTEXT_ACT_RESP = 23,
    IPD_GTP_V1_MESSAGE_TYPE_ERROR_INDICATION = 26,
    IPD_GTP_V1_MESSAGE_TYPE_PDU_NOTIF_REQ = 27,
    IPD_GTP_V1_MESSAGE_TYPE_PDU_NOTIF_RESP = 28,
    IPD_GTP_V1_MESSAGE_TYPE_PDU_NOTIF_REJECT_REQ = 29,
    IPD_GTP_V1_MESSAGE_TYPE_PDU_NOTIF_REJECT_RESP = 30,
    IPD_GTP_V1_MESSAGE_TYPE_SUPPORTED_EXT_NOTIF_HEADER = 31,
    IPD_GTP_V1_MESSAGE_TYPE_SEND_ROUTE_INFO_GPRS_REQ = 32,
    IPD_GTP_V1_MESSAGE_TYPE_SEND_ROUTE_INFO_GPRS_RESP = 33,
    IPD_GTP_V1_MESSAGE_TYPE_FAILURE_REPORT_REQ = 34,
    IPD_GTP_V1_MESSAGE_TYPE_FAILURE_REPORT_RESP = 35,
    IPD_GTP_V1_MESSAGE_TYPE_NOTE_MS_GPRS_PRESENT_REQ = 36,
    IPD_GTP_V1_MESSAGE_TYPE_NOTE_MS_GPRS_PRESENT_RESP = 37,
    IPD_GTP_V1_MESSAGE_TYPE_IDENT_REQ = 48,
    IPD_GTP_V1_MESSAGE_TYPE_IDENT_RESP = 49,
    IPD_GTP_V1_MESSAGE_TYPE_SGSN_CONTEXT_REQ = 50,
    IPD_GTP_V1_MESSAGE_TYPE_SGSN_CONTEXT_RESP = 51,
    IPD_GTP_V1_MESSAGE_TYPE_SGSN_CONTEXT_ACK = 52,
    IPD_GTP_V1_MESSAGE_TYPE_FORWARD_RELOC_REQ = 53,
    IPD_GTP_V1_MESSAGE_TYPE_FORWARD_RELOC_RESP = 54,
    IPD_GTP_V1_MESSAGE_TYPE_FORWARD_RELOC_COMPLETE = 55,
    IPD_GTP_V1_MESSAGE_TYPE_RELOC_CANCEL_REQ = 56,
    IPD_GTP_V1_MESSAGE_TYPE_RELOC_CANCEL_RESP = 57,
    IPD_GTP_V1_MESSAGE_TYPE_FORWARD_SRNS_CONTEXT = 58,
    IPD_GTP_V1_MESSAGE_TYPE_FORWARD_RELOC_COMPLETE_ACK = 59,
    IPD_GTP_V1_MESSAGE_TYPE_FORWARD_SRNS_CONTEXT_ACK = 60,
    IPD_GTP_V1_MESSAGE_TYPE_RAN_INFO_RELAY = 70,
    IPD_GTP_V1_MESSAGE_TYPE_MBMS_NOTIF_REQ = 96,
    IPD_GTP_V1_MESSAGE_TYPE_MBMS_NOTIF_RESP = 97,
    IPD_GTP_V1_MESSAGE_TYPE_MBMS_NOTIF_REJECT_REQ = 98,
    IPD_GTP_V1_MESSAGE_TYPE_MBMS_NOTIF_REJECT_RESP = 99,
    IPD_GTP_V1_MESSAGE_TYPE_CREATE_MBMS_CONTEXT_REQ = 100,
    IPD_GTP_V1_MESSAGE_TYPE_CREATE_MBMS_CONTEXT_RESP = 101,
    IPD_GTP_V1_MESSAGE_TYPE_UPDATE_MBMS_CONTEXT_REQ = 102,
    IPD_GTP_V1_MESSAGE_TYPE_UPDATE_MBMS_CONTEXT_RESP = 103,
    IPD_GTP_V1_MESSAGE_TYPE_DELETE_MBMS_CONTEXT_REQ = 104,
    IPD_GTP_V1_MESSAGE_TYPE_DELETE_MBMS_CONTEXT_RESP = 105,
    IPD_GTP_V1_MESSAGE_TYPE_MBMS_REGISTER_REQ = 112,
    IPD_GTP_V1_MESSAGE_TYPE_MBMS_REGISTER_RESP = 113,
    IPD_GTP_V1_MESSAGE_TYPE_MBMS_DE_REGISTER_REQ = 114,
    IPD_GTP_V1_MESSAGE_TYPE_MBMS_DE_REGISTER_RESP = 115,
    IPD_GTP_V1_MESSAGE_TYPE_MBMS_SESSION_START_REQ = 116,
    IPD_GTP_V1_MESSAGE_TYPE_MBMS_SESSION_START_RESP = 117,
    IPD_GTP_V1_MESSAGE_TYPE_MBMS_SESSION_STOP_REQ = 118,
    IPD_GTP_V1_MESSAGE_TYPE_MBMS_SESSION_STOP_RESP = 119,
    IPD_GTP_V1_MESSAGE_TYPE_MBMS_SESSION_UPDATE_REQ = 120,
    IPD_GTP_V1_MESSAGE_TYPE_MBMS_SESSION_UPDATE_RESP = 121,
    IPD_GTP_V1_MESSAGE_TYPE_MS_INFO_CHANGE_NOTIF_REQ = 128,
    IPD_GTP_V1_MESSAGE_TYPE_MS_INFO_CHANGE_NOTIF_RESP = 129,
    IPD_GTP_V1_MESSAGE_TYPE_DATA_RECORD_TRANSFER_REQ = 240,
    IPD_GTP_V1_MESSAGE_TYPE_DATA_RECORD_TRANSFER_RESP = 241,
    IPD_GTP_V1_MESSAGE_TYPE_END_MARKER = 254,
    IPD_GTP_V1_MESSAGE_TYPE_G_PDU = 255,
};


/**
 * Enumeration for message types of GTPv2. For more details see TS 29274.
 */
enum ipd_gtp_v2_message_type_enum
{
    IPD_GTP_V2_MESSAGE_TYPE_ECHO_REQUEST = 1,
    IPD_GTP_V2_MESSAGE_TYPE_ECHO_RESPONSE = 2,
    IPD_GTP_V2_MESSAGE_TYPE_CREATE_SESSION_REQ = 32,
    IPD_GTP_V2_MESSAGE_TYPE_CREATE_SESSION_RESP = 33,
    IPD_GTP_V2_MESSAGE_TYPE_MODIFY_BEARER_REQ = 34,
    IPD_GTP_V2_MESSAGE_TYPE_MODIFY_BEARER_RESP = 35,
    IPD_GTP_V2_MESSAGE_TYPE_DELETE_SESSION_REQ = 36,
    IPD_GTP_V2_MESSAGE_TYPE_DELETE_SESSION_RESP = 37,
    IPD_GTP_V2_MESSAGE_TYPE_CHANGE_NOTIF_REQ = 38,
    IPD_GTP_V2_MESSAGE_TYPE_CHANGE_NOTIF_RESP = 39,
    IPD_GTP_V2_MESSAGE_TYPE_MODIFY_BEARER_CMD = 64,
    IPD_GTP_V2_MESSAGE_TYPE_MODIFY_BEARER_FAILURE_IND = 65,
    IPD_GTP_V2_MESSAGE_TYPE_DELETE_BEARER_CMD = 66,
    IPD_GTP_V2_MESSAGE_TYPE_DELETE_BEARER_FAILURE_IND = 67,
    IPD_GTP_V2_MESSAGE_TYPE_BEARER_RES_CMD = 68,
    IPD_GTP_V2_MESSAGE_TYPE_BEARER_RES_FAILURE_IND = 69,
    IPD_GTP_V2_MESSAGE_TYPE_DOWNLINK_DATA_NOTIF_FAILURE_IND = 70,
    IPD_GTP_V2_MESSAGE_TYPE_TRACE_SESSION_ACTIVATION = 71,
    IPD_GTP_V2_MESSAGE_TYPE_TRACE_SESSION_DE_ACTIVATION = 72,
    IPD_GTP_V2_MESSAGE_TYPE_STOP_PAGING_IND = 73,
    IPD_GTP_V2_MESSAGE_TYPE_CREATE_BEARER_REQ = 95,
    IPD_GTP_V2_MESSAGE_TYPE_CREATE_BEARER_RESP = 96,
    IPD_GTP_V2_MESSAGE_TYPE_UPDATE_BEARER_REQ = 97,
    IPD_GTP_V2_MESSAGE_TYPE_UPDATE_BEARER_RESP = 98,
    IPD_GTP_V2_MESSAGE_TYPE_DELETE_BEARER_REQ = 99,
    IPD_GTP_V2_MESSAGE_TYPE_DELETE_BEARER_RESP = 100,
    IPD_GTP_V2_MESSAGE_TYPE_DELETE_PDN_CONNECTION_SET_REQ = 101,
    IPD_GTP_V2_MESSAGE_TYPE_DELETE_PDN_CONNECTION_SET_RESP = 102,
    IPD_GTP_V2_MESSAGE_TYPE_PGW_DOWNLINK_TRIGGER_NOTIF = 103,
    IPD_GTP_V2_MESSAGE_TYPE_PGW_DOWNLINK_TRIGGER_ACK = 104,
    IPD_GTP_V2_MESSAGE_TYPE_IDENT_REQ = 128,
    IPD_GTP_V2_MESSAGE_TYPE_IDENT_RESP = 129,
    IPD_GTP_V2_MESSAGE_TYPE_CONTEXT_REQ = 130,
    IPD_GTP_V2_MESSAGE_TYPE_CONTEXT_RESP = 131,
    IPD_GTP_V2_MESSAGE_TYPE_CONTEXT_ACK = 132,
    IPD_GTP_V2_MESSAGE_TYPE_FORWARD_RELOC_REQ = 133,
    IPD_GTP_V2_MESSAGE_TYPE_FORWARD_RELOC_RESP = 134,
    IPD_GTP_V2_MESSAGE_TYPE_FORWARD_RELOC_COMPLETE_NOTIF = 135,
    IPD_GTP_V2_MESSAGE_TYPE_FORWARD_RELOC_COMPLETE_ACK = 136,
    IPD_GTP_V2_MESSAGE_TYPE_FORWARD_ACCESS_CONTEXT_NOTIF = 137,
    IPD_GTP_V2_MESSAGE_TYPE_FORWARD_ACCESS_CONTEXT_ACK = 138,
    IPD_GTP_V2_MESSAGE_TYPE_RELOC_CANCEL_REQ = 139,
    IPD_GTP_V2_MESSAGE_TYPE_RELOC_CANCEL_RESP = 140,
    IPD_GTP_V2_MESSAGE_TYPE_CONFIGURATION_TRANSFER_TUNNEL = 141,
    IPD_GTP_V2_MESSAGE_TYPE_DETACH_NOTIF = 149,
    IPD_GTP_V2_MESSAGE_TYPE_DETACH_ACK = 150,
    IPD_GTP_V2_MESSAGE_TYPE_CS_PAGING_IND = 151,
    IPD_GTP_V2_MESSAGE_TYPE_RAN_INFO_RELAY = 152,
    IPD_GTP_V2_MESSAGE_TYPE_ALERT_MME_NOTIF = 153,
    IPD_GTP_V2_MESSAGE_TYPE_ALERT_MME_ACK = 154,
    IPD_GTP_V2_MESSAGE_TYPE_UE_ACTIVITY_NOTIF = 155,
    IPD_GTP_V2_MESSAGE_TYPE_UE_ACTIVITY_ACK = 156,
    IPD_GTP_V2_MESSAGE_TYPE_ISR_STATUS_IND = 157,
    IPD_GTP_V2_MESSAGE_TYPE_CREATE_FORWARDING_TUNNEL_REQ = 160,
    IPD_GTP_V2_MESSAGE_TYPE_CREATE_FORWARDING_TUNNEL_RESP = 161,
    IPD_GTP_V2_MESSAGE_TYPE_SUSPEND_NOTIF = 162,
    IPD_GTP_V2_MESSAGE_TYPE_SUSPEND_ACK = 163,
    IPD_GTP_V2_MESSAGE_TYPE_RESUME_NOTIF = 164,
    IPD_GTP_V2_MESSAGE_TYPE_RESUME_ACK = 165,
    IPD_GTP_V2_MESSAGE_TYPE_CREATE_INDIRECT_DATA_FORWARDING_TUNNEL_REQ = 166,
    IPD_GTP_V2_MESSAGE_TYPE_CREATE_INDIRECT_DATA_FORWARDING_TUNNEL_RESP = 167,
    IPD_GTP_V2_MESSAGE_TYPE_DELETE_INDIRECT_DATA_FORWARDING_TUNNEL_REQ = 168,
    IPD_GTP_V2_MESSAGE_TYPE_DELETE_INDIRECT_DATA_FORWARDING_TUNNEL_RESP = 169,
    IPD_GTP_V2_MESSAGE_TYPE_RELEASE_ACCESS_BEARER_REQ = 170,
    IPD_GTP_V2_MESSAGE_TYPE_RELEASE_ACCESS_BEARER_RESP = 171,
    IPD_GTP_V2_MESSAGE_TYPE_DOWNLINK_DATA_NOTIF = 176,
    IPD_GTP_V2_MESSAGE_TYPE_DOWNLINK_DATA_NOTIF_ACK = 177,
    IPD_GTP_V2_MESSAGE_TYPE_PGW_RESTART_NOTIF = 179,
    IPD_GTP_V2_MESSAGE_TYPE_PGW_RESTART_NOTIF_ACK = 180,
    IPD_GTP_V2_MESSAGE_TYPE_UPDATE_PDN_CONNECTION_SET_REQ = 200,
    IPD_GTP_V2_MESSAGE_TYPE_UPDATE_PDN_CONNECTION_SET_RESP = 201,
    IPD_GTP_V2_MESSAGE_TYPE_MODIFY_ACCESS_BEARER_REQ = 211,
    IPD_GTP_V2_MESSAGE_TYPE_MODIFY_ACCESS_BEARER_RESP = 212,
    IPD_GTP_V2_MESSAGE_TYPE_MBMS_SESSION_START_REQ = 231,
    IPD_GTP_V2_MESSAGE_TYPE_MBMS_SESSION_START_RESP = 232,
    IPD_GTP_V2_MESSAGE_TYPE_MBMS_SESSION_UPDATE_REQ = 233,
    IPD_GTP_V2_MESSAGE_TYPE_MBMS_SESSION_UPDATE_RESP = 234,
    IPD_GTP_V2_MESSAGE_TYPE_MBMS_SESSION_STOP_REQ = 235,
    IPD_GTP_V2_MESSAGE_TYPE_MBMS_SESSION_STOP_RESP = 236,
};

/**
 * Enumeration for the different protocol versions of GTP
 */
enum ipd_gtp_protocol_type_enum
{
    /** signals that this event correlates to a GTPv0 packet. */
    IPD_GTP_PROTOCOL_TYPE_V0,
    /** signals that this event correlates to a GTPv1 packet. */
    IPD_GTP_PROTOCOL_TYPE_V1,
    /** signals that this event correlates to a GTPv2 packet. */
    IPD_GTP_PROTOCOL_TYPE_V2,
    /** signals that this event correlates to a GTP' packet. */
    IPD_GTP_PROTOCOL_TYPE_PRIME,
};

/**
 * Structure for a GTP message.
 */
struct ipd_gtp_message
{
    /**
     * A PADE internal ID for this message. It can be used to correlate corresponding GTP events to this message.
     */
    u64 message_id;
    /**
     * If a TEID is contained in the message, then this field will contain it. Otherwise it is set to "0".
     */
    u32 teid;
    /**
     * Message sequence number. If it is not in the packet (GTPv0 and GTPv1 if the sequence number flag is not set), it is set to "0".
     */
    u32 sequence_number;
    /**
     * The value of the contained message type. Together with struct ipd_gtp_message.protocol_type,
     * enum ipd_gtp_v1_message_type_enum and enum ipd_gtp_v2_message_type_enum it is possible to get
     * a more detailed description as a enum variable for this message type. A string representation
     * are available over the ipd_gtp_get_message_type_description function.
     */
    u8 message_type;
    /**
     * The protocol type in which this message was encoded.
     */
    enum ipd_gtp_protocol_type_enum protocol_type;
    /**
     * The completely byte stream which forms the GTP message.
     */
    struct ipd_charset_string message;
    /**
     * The part of the byte stream, which forms the header of this GTP message.
     */
    struct ipd_charset_string header;
    /**
     * The part of the byte stream, which follows of the header of the GTP message.
     */
    struct ipd_charset_string data;
};

/**
 * Structure for a subset of a byte stream of a GTP message.
 */
struct ipd_gtp_message_data
{
    /**
     * Correlating message id, to which this data/extension header correlate.
     */
    u64 message_id;
    /**
     * The bytes of the data/extension header.
     */
    struct ipd_charset_string data;
};

/**
 * Enumeration for Information Element types of GTPv1 and GTP'. For more details see TS 29060 and TS 32295.
 */
enum ipd_gtp_v1_information_type_enum
{
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_CAUSE = 1,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_IMSI = 2,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_RAI = 3,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_TLLI = 4,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_TMSI = 5,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_REORDERING_REQUIRED = 8,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_AUTH_TRIPLET = 9,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_MAP_CAUSE = 11,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_TMSI_SIG = 12,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_MS_VALID = 13,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_RECOVERY = 14,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_SELECT_MODE = 15,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_TEID_DATA1 = 16,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_TEID_CONTROL = 17,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_TEID_DATA2 = 18,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_TEARDOWN = 19,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_NSAPI = 20,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_RANAP_CAUSE = 21,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_RAB_CONTEXT = 22,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_RADIO_PRIO_SMS = 23,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_RADIO_PRIO = 24,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_PACKET_FLOW_ID = 25,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_CHARGING_CHAR = 26,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_TRACE_REF = 27,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_TRACE_TYPE = 28,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_MS_NOT_REACHABLE_REASON = 29,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_PACKET_TRANSFER_CMD = 126,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_CHARGING_ID = 127,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_END_USER_ADDR = 128,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_MM_CONTEXT = 129,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_PDP_CONTEXT = 130,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_ACCESS_POINT_NAME = 131,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_PROT_CONFIG = 132,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_GSN_ADDR = 133,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_MSISDN = 134,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_QOS_PROFILE = 135,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_AUTH_QUINTUPLET = 136,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_TRAFFIC_FLOW_TEMP = 137,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_TARGET_IDENT = 138,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_UTRAN_TRANSPORT_CONTAINER = 139,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_RAB_SETUP_INFO = 140,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_EXTENSION_HEADER_LIST = 141,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_TRIGGER_ID = 142,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_OMC_IDENT = 143,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_RAN_TRANSPORT_CONTAINER = 144,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_PDP_CONTEXT_PRIO = 145,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_RAB_SETUP_INFO_ADD = 146,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_SGSN = 147,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_COMMON_FLAGS = 148,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_APN_REST = 149,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_RADIO_PRIO_LCS = 150,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_RAT_TYPE = 151,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_USER_LOC_INFO = 152,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_MS_TIME_ZONE = 153,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_IMEI = 154,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_CAMEL_CHARGING_INFO = 155,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_MBMS_UE_CONTEXT = 156,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_TMGI = 157,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_RIM_ROUTE_ADDR = 158,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_MBMS_PROT_CONF_OPTION = 159,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_MBMS_SERVICE_AREA = 160,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_SRC_RNC_PDCP_CONTEXT = 161,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_TRACE_INFO_ADD = 162,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_HOP_COUNT = 163,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_SELECT_PLMN_ID = 164,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_MBMS_SESSION_IDENT = 165,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_MBMS_2G_3G_INDICATOR = 166,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_NSAPI_ENH = 167,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_MBMS_SESSION_DURATION = 168,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_MBMS_TRACE_INFO_ADD = 169,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_MBMS_SESSION_REP = 170,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_MBMS_TIME_TO_DATA_TRANS = 171,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_BSS_CONTAINER = 173,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_CELL_IDENT = 174,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_PDU_NUMBER = 175,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_BSSGP_CAUSE = 176,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_MBMS_REQ_BEARER_CAPA = 177,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_RIM_ROUTE_ADDR_DISC = 178,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_PFC_SETUP_LIST = 179,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_PS_HANDOVER_XID_PARA = 180,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_MS_INFO_CHANGE_REPORT_ACTION = 181,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_DIRECT_TUNNEL_FLAGS = 182,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_CORRELATION_ID = 183,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_BEARER_CONTROL_MODE = 184,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_MBMS_FLOW_IDENT = 185,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_MBMS_IP_MCAST_DIST = 186,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_MBMS_DIST_ACK = 187,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_RAT_HANDOVER_INFO = 188,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_RFSP_INDEX = 189,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_FQDN = 190,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_E_ALLOC_RETENTION_PRIO1 = 191,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_E_ALLOC_RETENTION_PRIO2 = 192,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_COMMON_FLAGS_EXT = 193,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_UCI = 194,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_CSG_INFO_REPORT_ACTION = 195,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_CSG_ID = 196,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_CMI = 197,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_AMBR = 198,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_UE_NETWORK_CAPA = 199,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_UE_AMBR = 200,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_APN_AMBR = 201,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_GGSN_BACKOFF_TIME = 202,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_SIGNAL_PRIO_INDICATION = 203,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_SIGNAL_PRIO_INDICATION_NSAPI = 204,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_HIGHER_16MBPS_BITRATE_FLAG = 205,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_MM_CONTEXT_ADD = 207,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_SRVCC_ADD_FLAGS = 208,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_STN_SR = 209,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_C_MSISDN = 210,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_RANAP_CAUSE_EXT = 211,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_ENODEB_ID = 212,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_SELECT_MODE_NSAPI = 213,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_ULI_TIMESTAMP = 214,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_LHN_ID_NSAPI = 215,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_CN_OP_SELECT_ENTITY = 216,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_SEQ_NUM_OF_RELEASED_PACKETS = 249,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_SEQ_NUM_OF_CANCELLED_PACKETS = 250,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_CHARGING_GATEWAY_ADDR = 251,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_DATA_RECORD_PACKET = 252,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_REQUESTS_RESPONDED = 253,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_ADDR_OF_RECOMMENDED_NODE = 254,
    IPD_GTP_V1_INFORMATION_ELEMENT_TYPE_PRIVATE_EXTENSION = 255,
};


/**
 * Enumeration for Information Element types of GTPv2. For more details see TS 29274.
 */
enum ipd_gtp_v2_information_type_enum
{
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_IMSI = 1,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_CAUSE = 2,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_RECOVERY = 3,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_STN_SR = 51,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_APN = 71,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_AMBR = 72,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_EBI = 73,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_IP_ADDR = 74,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_MEI = 75,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_MSISDN = 76,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_INDICATION = 77,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_PCO = 78,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_PAA = 79,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_BEARER_QOS = 80,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_FLOW_QOS = 81,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_RAT_TYPE = 82,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_SERVING_NETWORK = 83,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_BEARER_TFT = 84,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_TAD = 85,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_ULI = 86,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_F_TEID = 87,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_TMSI = 88,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_GLOBAL_CN_ID = 89,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_S103PDF = 90,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_S1UDF = 91,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_DELAY_VALUE = 92,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_BEARER_CONTEXT = 93,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_CHARGING_ID = 94,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_CHARGING_CHAR = 95,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_TRACE_INFO = 96,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_BEARER_FLAGS = 97,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_PDN_TYPE = 99,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_PROCEDURE_TRANSACTION_ID = 100,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_MM_CONTEXT_GSM_KEY_T = 103,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_MM_CONTEXT_UMTS_KEY_UC_Q = 104,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_MM_CONTEXT_GSM_KEY_UC_Q = 105,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_MM_CONTEXT_UMTS_KEY_Q = 106,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_MM_CONTEXT_EPS_QUAD_Q = 107,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_MM_CONTEXT_UMTS_KEY_QUAD_Q = 108,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_PDN_CONNECTION = 109,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_PDN_NUMBERS = 110,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_P_TMSI = 111,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_P_TMSI_SIGNATURE = 112,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_HOP_COUNTER = 113,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_UE_TIME_ZONE = 114,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_TRACE_REF = 115,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_COMPLETE_REQ_MESSAGE = 116,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_GUTI = 117,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_F_CONTAINER = 118,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_F_CAUSE = 119,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_PLMN_ID = 120,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_TARGET_IDENT = 121,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_PACKET_FLOW_ID = 123,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_RAB_CONTEXT = 124,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_SRC_RNC_PDCP_CONTEXT_INFO = 125,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_UDP_SRC_PORT_NUMBER = 126,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_APN_RESTRICTION = 127,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_SELECT_MODE = 128,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_SRC_IDENT = 129,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_CHANGE_REPORT_ACTION = 131,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_FQ_CSID = 132,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_CHANNEL_NEEDED = 133,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_E_MLPP_PRIO = 134,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_NODE_TYPE = 135,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_FQDN = 136,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_TI = 137,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_MBMS_SESSION_DURATION = 138,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_MBMS_SERVICE_AREA = 139,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_MBMS_SESSION_IDENT = 140,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_MBMS_FLOW_IDENT = 141,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_MBMS_IP_MULTICAT_DIST = 142,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_MBMS_DIST_ACK = 143,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_RFSP_INDEX = 144,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_UCI = 145,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_CSG_INFO_REPORT_ACTION = 146,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_CSG_ID = 147,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_CMI = 148,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_SERVICE_INDICATOR = 149,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_DETACH_TYPE = 150,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_LDN = 151,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_NODE_FEATURES = 152,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_MBMS_TIME_TO_DATA_TRANSFER = 153,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_THROTTLING = 154,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_ARP = 155,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_EPC_TIMER = 156,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_SIGNAL_PRIO_IND = 157,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_TMGI = 158,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_SRVCC_ADD_MM_CONTEXT = 159,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_SRVCC_ADD_FLAGS = 160,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_MDT_CONFIGURATION = 162,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_APCO = 163,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_ABSOLUTE_TIME_OF_MBMS_DATA_TRANSFER = 164,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_HNB_INFO_REPORT = 165,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_IP4CP = 166,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_CHANGE_TO_REPORT_FLAGS = 167,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_ACTION_IND = 168,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_TWAN_IDENT = 169,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_ULI_TIMESTAMP = 170,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_MBMS_FLAGS = 171,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_RAN_NAS_CAUSE = 172,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_CN_OP_SELECT_MODE = 173,
    IPD_GTP_V2_INFORMATION_ELEMENT_TYPE_PRIVATE_EXTENSION = 255,
};

/**
 * Structure for a GTP information Element.
 */
struct ipd_gtp_information
{
    /**
     * Correlating message or group id, to which this data/extension header correlate.
     */
    u64 message_id;
    /**
     * The value of the contained information element type. Together with struct ipd_gtp_message.protocol_type,
     * enum ipd_gtp_v1_information_type_enum and enum ipd_gtp_v1_information_type_enum it is possible to get
     * a more detailed description as a enum variable for this information element type. A string representation
     * are available over the ipd_gtp_get_information_element_description function.
     */
    u8 information_type;
    /**
     * The part of the byte stream of a GTP message, which contains the completely information element.
     */
    struct ipd_charset_string information;
    /**
     * The part of the byte stream of a GTP message, which contains the data of the information element.
     */
    struct ipd_charset_string data;
    /**
     * The protocol type in which this message was encoded.
     */
    enum ipd_gtp_protocol_type_enum protocol_type;
};

/**
 * Structure for a parsed GTP information element, which contains a String (TBCD or not) as value.
 */
struct ipd_gtp_information_string
{
    /**
     * Correlating message or group id, to which this information element correlate.
     */
    u64 message_id;
    /**
     * The contained string of this information element.
     */
    struct ipd_charset_string data;
};

/**
 * Structure for a parsed GTP information element, which contains a number as value.
 */
struct ipd_gtp_information_value
{
    /**
     * Correlating message or group id, to which this information element correlate.
     */
    u64 message_id;
    /**
     * The contained number of this information element.
     */
    u64 data;
};

/**
 * Structure for a parsed GTP information element, which groups sub information elements.
 */
struct ipd_gtp_information_group
{
    /**
     * Correlating message or group id, to which this information element correlate.
     */
    u64 message_id;
    /**
     * A PADE internal ID for this group. It can be used to correlate corresponding GTP events to this group.
     */
    u64 group_id;
    /**
     * The part of the byte stream of a GTP message, which contains the data of the information group.
     */
    struct ipd_charset_string data;
};

/**
 * Enumeration for the type of a source cell identifier.
 */
enum ipd_gtp_cell_ident_type
{
    IPD_GTP_CELL_IDENT_TYPE_CELL_ID = 0,
    IPD_GTP_CELL_IDENT_TYPE_RNC_ID = 1,
};

/**
 * Structure for a parsed GTP information element, which contains a cell identifier as value.
 */
struct ipd_gtp_information_cell_ident
{
    /**
     * Correlating message or group id, to which this information element correlate.
     */
    u64 message_id;
    /**
     * The type of the source.
     */
    enum ipd_gtp_cell_ident_type source_type;
    /**
     * The ID of the source
     */
    u64 source_id;
    /**
     * The ID of the target
     */
    u64 target_id;
};

/**
 * Enumeration for the type of a RAT information element value.
 *
 * The information element itself will be reported as struct ipd_gtp_information_value and
 * it's struct ipd_gtp_information_value.data can be casted to this enumeration.
 */
enum ipd_gtp_rat_type
{
    IPD_GTP_RAT_TYPE_UTRAN = 1,
    IPD_GTP_RAT_TYPE_GERAN = 2,
    IPD_GTP_RAT_TYPE_WLAN = 3,
    IPD_GTP_RAT_TYPE_GAN = 4,
    IPD_GTP_RAT_TYPE_HSPA_EVOLUTION = 5,
    IPD_GTP_RAT_TYPE_E_UTRAN = 6,
    IPD_GTP_RAT_TYPE_VIRTUAL = 7,
};

/**
 * Structure for a parsed GTP information element, which contains a IP address (IPv4, IPv6) as value.
 */
struct ipd_gtp_information_address
{
    /**
     * Correlating message or group id, to which this information element correlate.
     */
    u64 message_id;
    /**
     * Flag to signal if it is a IPv4 or a IPv6 address
     */
    u8 is_ip_v6;
    /**
     * The contained IP address of this information element.
     */
    union ip_v4_v6_addr address;
};

/**
 * GTP decoder event types (used as values of the \c type argument of a \ref ipd_decoder_event_callback function)
 */
enum ipd_simple_event_gtp_enumeration
{
    /** This event is sent when a new flow/connection is detected by PACE and handled by PADE as GTP. */
    IPD_EVENT_GTP_NEW_CONNECTION,          /* NULL */
    /** This event signals the end or timeout of a known GTP connection. */
    IPD_EVENT_GTP_CONNECTION_END,          /* NULL */
    /** This event signals that this GTP connection can't be decoded. Provides a char * with information about the problems. */
    IPD_EVENT_GTP_INVALID,                 /* char* */
    /** This event is sent for every GTP message. Provides a struct ipd_gtp_message * with information about the message. */
    IPD_EVENT_GTP_MESSAGE,                 /* struct ipd_gtp_message */
    /** This event is sent for every GTP message extension header. Provides a struct ipd_gtp_message_data * with information about the extension header. */
    IPD_EVENT_GTP_EXTENSION,               /* struct ipd_gtp_message_data */
    /** This event is sent for every GTP message data part. Provides a struct ipd_gtp_message_data * with information about the data. */
    IPD_EVENT_GTP_DATA,                    /* struct ipd_gtp_message_data */
    /** This event is sent for every GTP message information element. Provides a struct ipd_gtp_information * with information about the information element. */
    IPD_EVENT_GTP_INFORMATION,             /* struct ipd_gtp_information */


    /** This event is sent for every GTP message information element, which contains a IMSI. Provides a struct ipd_gtp_information_string * with information about the IMSI. */
    IPD_EVENT_GTP_INFORMATION_IMSI,        /* struct ipd_gtp_information_string */
    /** This event is sent for every GTP message information element, which contains a IMEI. Provides a struct ipd_gtp_information_string * with information about the IMEI. */
    IPD_EVENT_GTP_INFORMATION_IMEI,        /* struct ipd_gtp_information_string */
    /** This event is sent for every GTP message information element, which contains a MSISDN. Provides a struct ipd_gtp_information_string * with information about the MSISDN. */
    IPD_EVENT_GTP_INFORMATION_MSISDN,      /* struct ipd_gtp_information_string */
    /** This event is sent for every GTP message information element, which contains a APN. Provides a struct ipd_gtp_information_string * with information about the APN. */
    IPD_EVENT_GTP_INFORMATION_APN,         /* struct ipd_gtp_information_string */

    /** This event is sent for every GTP message information element, which contains a TEID data plane part I. Provides a struct ipd_gtp_information_value * with information about the TEID. */
    IPD_EVENT_GTP_INFORMATION_TEID_DATA_I, /* struct ipd_gtp_information_value */
    /** This event is sent for every GTP message information element, which contains a TEID data plane part II. Provides a struct ipd_gtp_information_value * with information about the TEID. */
    IPD_EVENT_GTP_INFORMATION_TEID_DATA_II,/* struct ipd_gtp_information_value */
    /** This event is sent for every GTP message information element, which contains a TEID control plane. Provides a struct ipd_gtp_information_value * with information about the TEID. */
    IPD_EVENT_GTP_INFORMATION_TEID_CONTROL,/* struct ipd_gtp_information_value */
    /** This event is sent for every GTP message information element, which contains a RAT. Provides a struct ipd_gtp_information_value * with information about the RAT.
     *  The contained field struct ipd_gtp_information_value.data can be casted into a enum ipd_gtp_rat_type */
    IPD_EVENT_GTP_INFORMATION_RAT,         /* struct ipd_gtp_information_value */
    /** This event is sent for every GTP message information element, which contains a LAC. Provides a struct ipd_gtp_information_value * with information about the LAC. */
    IPD_EVENT_GTP_INFORMATION_LAC,         /* struct ipd_gtp_information_value */
    /** This event is sent for every GTP message information element, which contains a RAC. Provides a struct ipd_gtp_information_value * with information about the RAC. */
    IPD_EVENT_GTP_INFORMATION_RAC,         /* struct ipd_gtp_information_value */
    /** This event is sent for every GTP message information element, which contains a EBI. Provides a struct ipd_gtp_information_value * with information about the bearer id. */
    IPD_EVENT_GTP_INFORMATION_EBI,         /* struct ipd_gtp_information_value */
    /** This event is sent for every GTP message information element, which contains a QCI from a QoS profile. Provides a struct ipd_gtp_information_value * with information about the QCI. */
    IPD_EVENT_GTP_INFORMATION_QCI,         /* struct ipd_gtp_information_value */
    /** This event is sent for every GTP message information element, which contains a ARP from a QoS profile. Provides a struct ipd_gtp_information_value * with information about the ARP. */
    IPD_EVENT_GTP_INFORMATION_ARP,         /* struct ipd_gtp_information_value */
    /** This event is sent for every GTP message information element, which contains the upload GBR from a QoS profile. Provides a struct ipd_gtp_information_value * with information about the GBR. */
    IPD_EVENT_GTP_INFORMATION_GBR_UP,      /* struct ipd_gtp_information_value */
    /** This event is sent for every GTP message information element, which contains the download GBR from a QoS profile. Provides a struct ipd_gtp_information_value * with information about the GBR. */
    IPD_EVENT_GTP_INFORMATION_GBR_DOWN,    /* struct ipd_gtp_information_value */
    /** This event is sent for every GTP message information element, which contains the upload MBR from a QoS profile. Provides a struct ipd_gtp_information_value * with information about the MBR. */
    IPD_EVENT_GTP_INFORMATION_MBR_UP,      /* struct ipd_gtp_information_value */
    /** This event is sent for every GTP message information element, which contains the download MBR from a QoS profile. Provides a struct ipd_gtp_information_value * with information about the MBR. */
    IPD_EVENT_GTP_INFORMATION_MBR_DOWN,    /* struct ipd_gtp_information_value */
    /** This event is sent for every GTP message information element, which contains a Cell identifier. Provides a struct ipd_gtp_information_cell_ident * with information about the CID. */
    IPD_EVENT_GTP_INFORMATION_CID,         /* struct ipd_gtp_information_cell_ident */
    /** This event is sent for every GTP message information element, which contains a IP address. Provides a struct ipd_gtp_information_address * with information about the IP address. */
    IPD_EVENT_GTP_INFORMATION_ADDRESS,     /* struct ipd_gtp_information_address */
    /** This event is sent for every GTP message information element, which groups sub information elements. Provides a struct ipd_gtp_information_group * with information about the group. */
    IPD_EVENT_GTP_INFORMATION_GROUP,       /* struct ipd_gtp_information_group */

    /** This event signals that for the correlating GTP message no more events will follow. This event is only thrown if no #IPD_EVENT_GTP_INVALID event was before.
     * Provides a u64 * with the message id of the correlating GTP message. */
    IPD_EVENT_GTP_MESSAGE_END,             /* u64 */
    /** This event signals that for the correlating GTP information element group no more events will follow. Provides a u64 * with the group id of the correlating GTP group. */
    IPD_EVENT_GTP_INFORMATION_GROUP_END,   /* u64 */

    IPD_NUMBER_OF_GTP_EVENTS,
};

/**
 * Function to get a String with a short description of the given message type.
 */
const char *ipd_gtp_get_message_type_description(enum ipd_gtp_protocol_type_enum protocol_type, u8 type);

/**
 * Function to get a String with a short description of the given information element type.
 */
const char *ipd_gtp_get_information_element_description(enum ipd_gtp_protocol_type_enum protocol_type, u8 type);


#endif /* __IPOQUE_DECODER_GTP_INCLUDE_FILE__ */
