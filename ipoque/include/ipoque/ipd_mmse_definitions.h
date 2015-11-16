#ifndef __IPOQUE_DECODER_MMSE_INCLUDE_FILE__
#define __IPOQUE_DECODER_MMSE_INCLUDE_FILE__

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif

/**
 * MMSE decoder event types (used as values of the \c type argument of a \ref ipd_decoder_event_callback function)
 */
enum ipd_simple_event_mmse_enumeration
{
    IPD_EVENT_MMSE_NEW_CONNECTION,                                          /**< Start of a new flow with MMSE traffic; payload: struct ipd_5tuple */
    IPD_EVENT_MMSE_PDU_MESSAGE_TYPE,                                        /**< The message type of the current message. payload: struct ipd_mmse_message_type_struct */
    IPD_EVENT_MMSE_PDU_HEADERLINE,                                          /**< One header field of the intercepted Mms-Message-Type; payload: struct ipd_mmse_pdu_value */
    IPD_EVENT_MMSE_PDU_HEADER_END,                                          /**< End of header fields; payload: struct ipd_mmse_header_end_struct */
    IPD_EVENT_MMSE_PDU_DATA_MULTIPART_START,                                /**< Start of multiparts with information of multipart_amount; payload: struct ipd_mmse_multipart_start_struct */
    IPD_EVENT_MMSE_PDU_DATA_MULTIPART_PART_CONTENT_TYPE,                    /**< The content type of this multipart; payload: struct ipd_mmse_multipart_content_type_struct */
    IPD_EVENT_MMSE_PDU_DATA_MULTIPART_PART_HEADERLINE,                      /**< One multipart header field of this multipart; payload: struct ipd_mmse_multipart_header_struct */
    IPD_EVENT_MMSE_PDU_DATA_MULTIPART_PART_CONTENT,                         /**< The content field of this multipart; payload: struct ipd_mmse_multipart_content_struct */
    IPD_EVENT_MMSE_PDU_DATA_MULTIPART_PART_END,                             /**< End of this multipart; payload: struct ipd_mmse_multipart_end_struct */
    IPD_EVENT_MMSE_PDU_MESSAGE_END,                                         /**< End of this MMSE message; payload: struct ipd_mmse_message_end_struct */
    IPD_EVENT_MMSE_END_CONNECTION,                                          /**< End of the MMSE flow; no payload. */
    IPD_EVENT_MMSE_INVALID,                                                 /**< The MMSE flow is set to invalid. The error message is passed as a <tt>char *</tt> in the \c data argument. */

    IPD_NUMBER_OF_MMSE_EVENTS
};

/** MMSE PDU Header field types */
enum ipd_mmse_pdu_type_enum
{
    IPD_MMSE_PDU_MM_BCC = 0x01,                         ///< The BCC value. The value will be a struct ipd_charset_string.
    IPD_MMSE_PDU_MM_CC = 0x02,                          ///< The CC value. The value will be a struct ipd_charset_string.
    IPD_MMSE_PDU_MM_CONTENT_LOCATION = 0x03,            /**< The content location. The value will be a struct ipd_mmse_pdu_content_location_struct.
                                                             Only if the field "message_type_is_mbox_delete_conf" is set, the field "status_count_value" is valid. */
    IPD_MMSE_PDU_MM_CONTENT_TYPE = 0x04,                ///< The content type. The value will be a struct ipd_mmse_pdu_content_type_struct with the given type is placed in a buffer and an enumeration. */
    IPD_MMSE_PDU_MM_DATE = 0x05,                        ///< The date value. This will be a u64 integer with the timestamp to the date.
    IPD_MMSE_PDU_MM_DELIVERY_REPORT = 0x06,             ///< The value of the delivery report will be an enum ipd_mmse_status_enum with "yes" or "no".
    IPD_MMSE_PDU_MM_DELIVERY_TIME = 0x07,               /**< The value of the delivery time will be a struct ipd_mmse_pdu_delivery_time_struct.
                                                             The enumeration token decides whether in the union "delivery_time" is a date (timestamp) or a delta in seconds.*/
    IPD_MMSE_PDU_MM_EXPIRY = 0x08,                      /**< The value of the expiry will be a struct ipd_mmse_pdu_expiry_struct.
                                                             The enumeration token decides whether in the union "expiry" is a date (timestamp) or a delta in seconds.*/
    IPD_MMSE_PDU_MM_FROM = 0x09,                        ///< The from value. This will be a struct ipd_mmse_pdu_from_struct. If the enumeration is set to "insert address", the field "from_value" will be empty.
    IPD_MMSE_PDU_MM_MESSAGE_CLASS = 0x0A,               /**< The message class value will be a struct ipd_mmse_pdu_message_class_struct. The enumeration corresponds the value.
                                                             If the enumeration is set to token text, the "token_text" field will be set with a string value. */
    IPD_MMSE_PDU_MM_MESSAGE_ID = 0x0B,                  ///< The message id will be a struct ipd_string value. */
    IPD_MMSE_PDU_MM_MESSAGE_TYPE = 0x0C,                ///< The message type value will be a struct ipd_mmse_message_type_struct and will be thrown in a IPD_EVENT_MMSE_PDU_MESSAGE_TYPE event.
    IPD_MMSE_PDU_MM_VERSION = 0x0D,                     /**< The version will be a struct ipd_mmse_version_struct. There will be a major and a minor number.
                                                             The flag "is_minor_version_set" indicates whether the minor number is present or not. */
    IPD_MMSE_PDU_MM_MESSAGE_SIZE = 0x0E,                ///< The message size value will be a u64.
    IPD_MMSE_PDU_MM_PRIORITY = 0x0F,                    ///< The priority will be an enumeration ipd_mmse_priority_enum.
    IPD_MMSE_PDU_MM_READ_REPORT = 0x10,                 ///< The value of read repowrt will be an enum ipd_mmse_status_enum with "yes" or "no".
    IPD_MMSE_PDU_MM_REPORT_ALLOWED = 0x11,              ///< The value of report allowed will be an enum ipd_mmse_status_enum with "yes" or "no".
    IPD_MMSE_PDU_MM_RESPONSE_STATUS = 0x12,             ///< The response status value will be an enum ipd_mmse_response_status_enum.
    IPD_MMSE_PDU_MM_RESPONSE_TEXT = 0x13,               /**< The response text. The value will be a struct ipd_mmse_pdu_response_text_struct.
                                                             Only if the field "message_type_is_mbox_delete_conf" is set, the field "status_count_value" is valid. */
    IPD_MMSE_PDU_MM_SENDER_VISIBILITY = 0x14,           ///< The sender visibility will be an enum ipd_mmse_sender_visibility_enum.
    IPD_MMSE_PDU_MM_STATUS = 0x15,                      ///< The status value will be an enum ipd_mmse_message_status_enum
    IPD_MMSE_PDU_MM_SUBJECT = 0x16,                     ///< The subject will be a struct ipd_charset_string.
    IPD_MMSE_PDU_MM_TO = 0x17,                          ///< The to value will be a struct ipd_charset_string.
    IPD_MMSE_PDU_MM_TRANSACTION_ID = 0x18,              ///< The transaction id will be a struct ipd_string.
    IPD_MMSE_PDU_MM_RETRIEVE_STATUS = 0x19,             ///< The retrieve status will be an enum ipd_mmse_retrieve_status_enum.
    IPD_MMSE_PDU_MM_RETRIEVE_TEXT = 0x1A,               ///< The retrieve text will be a struct ipd_charset_string.
    IPD_MMSE_PDU_MM_READ_STATUS = 0x1B,                 ///< The read status value will be an enum ipd_mmse_read_status_enum.
    IPD_MMSE_PDU_MM_REPLY_CHARGING = 0x1C,              ///< The reply charging value will be an enum ipd_mmse_reply_charging_enum.
    IPD_MMSE_PDU_MM_REPLY_CHARGING_DEADLINE = 0x1D,     /**< The value of the reply charging deadline will be a struct ipd_mmse_pdu_reply_charging_deadline_struct.
                                                             The enumeration token decides whether in the union "reply_charging_deadline" is a date (timestamp) or a delta in seconds.*/
    IPD_MMSE_PDU_MM_REPLY_CHARGING_ID = 0x1E,           ///< The reply charging id will be a struct ipd_string.
    IPD_MMSE_PDU_MM_REPLY_CHARGING_SIZE = 0x1F,         ///< The reply charging size will be a u64.
    IPD_MMSE_PDU_MM_PREV_SENT_BY = 0x20,                ///< The previously send by value will be a struct ipd_mmse_pdu_previously_sent_by_struct.
    IPD_MMSE_PDU_MM_PREV_SENT_DATE = 0x21,              ///< The previously send date value will be a struct ipd_mmse_pdu_previously_sent_date_struct.
    IPD_MMSE_PDU_MM_STORE = 0x22,                       ///< The value of store will be an enum ipd_mmse_status_enum with "yes" or "no".
    IPD_MMSE_PDU_MM_STATE = 0x23,                       ///< The value of state will be an enum ipd_mmse_pdu_state_enum.
    IPD_MMSE_PDU_MM_FLAGS = 0x24,                       ///< The value of flags will be a struct ipd_mmse_pdu_flags_struct.
    IPD_MMSE_PDU_MM_STORE_STATUS = 0x25,                ///< The value of store status will be an enum ipd_mmse_store_status_enum,
    IPD_MMSE_PDU_MM_STORE_STATUS_TEXT = 0x26,           ///< The store status text will be a struct ipd_charset_string.
    IPD_MMSE_PDU_MM_STORED = 0x27,                      ///< The value of stored will be an enum ipd_mmse_status_enum with "yes" or "no".
    IPD_MMSE_PDU_MM_ATTRIBUTES = 0x28,                  ///< The attributes will be an enum ipd_mmse_pdu_type_enum.
    IPD_MMSE_PDU_MM_TOTALS = 0x29,                      ///< The value of totals will be an enum ipd_mmse_status_enum with "yes" or "no".
    IPD_MMSE_PDU_MM_MBOX_TOTALS = 0x2A,                 ///< The mbox totals will be a struct ipd_mmse_pdu_mbox_totals_struct.
    IPD_MMSE_PDU_MM_QUOTAS = 0x2B,                      ///< The value of quotas will be an enum ipd_mmse_status_enum with "yes" or "no".
    IPD_MMSE_PDU_MM_MBOX_QUOTAS = 0x2C,                 ///< The mbox quotas will be a struct ipd_mmse_pdu_mbox_quotas_struct.
    IPD_MMSE_PDU_MM_MESSAGE_COUNT = 0x2D,               ///< The message count will be a u64.
    IPD_MMSE_PDU_MM_CONTENT = 0x2E,                     ///< The content value will not be thrown in any event.
    IPD_MMSE_PDU_MM_START = 0x2F,                       ///< The start value will be a u64.
    IPD_MMSE_PDU_MM_ADDITIONAL_HEADERS = 0x30,          ///< The additional headers will not be thrown in any event.
    IPD_MMSE_PDU_MM_DISTRIBUTION_INDICATOR = 0x31,      ///< The value of distribution indicator will be an enum ipd_mmse_status_enum with "yes" or "no".
    IPD_MMSE_PDU_MM_ELEMENT_DESCRIPTOR = 0x32,          ///< The element descriptor will be a struct ipd_mmse_pdu_element_descriptor_struct
    IPD_MMSE_PDU_MM_LIMIT = 0x33,                       ///< The limit will be a u64.
    IPD_NUMBER_OF_MMSE_PDUS,
};

/** MMS message types.*/
enum ipd_mmse_message_type_enum
{
    IPD_MMSE_MESSAGE_TYPE_M_SEND_REQ = 0x80,            ///< Indicates that a MM message is sent.
    IPD_MMSE_MESSAGE_TYPE_M_SEND_CONF = 0x81,           ///< The acknowledgement of the server that the MM message was sent to the receiver.
    IPD_MMSE_MESSAGE_TYPE_M_NOTIFICATION_IND = 0x82,    ///< The server indicates the client that there are messages on the server.
    IPD_MMSE_MESSAGE_TYPE_M_NOTIFYRESP_IND = 0x83,      ///< The acknowledgement of the client to the server, that the notifications has arrived.
    IPD_MMSE_MESSAGE_TYPE_M_RETRIEVE_CONF = 0x84,       ///< The server sends the MM message to the client, who requested the MM message.
    IPD_MMSE_MESSAGE_TYPE_M_ACKNOWLEDGE_IND = 0x85,     ///< The client confirms the delivery of the MM message.
    IPD_MMSE_MESSAGE_TYPE_M_DELIVERY_IND = 0x86,        ///< The server sends a delivery report to the sending client, if this report was not denied.
    IPD_MMSE_MESSAGE_TYPE_M_READ_REC_IND = 0x87,        ///< The receiver of a message sends a read report.
    IPD_MMSE_MESSAGE_TYPE_M_READ_ORIG_IND = 0x88,       ///< The originating side of the message sends a read report.
    IPD_MMSE_MESSAGE_TYPE_M_FORWARD_REQ = 0x89,         ///< The client requests a forwarding of a MM message.
    IPD_MMSE_MESSAGE_TYPE_M_FORWARD_CONF = 0x8A,        ///< The server indicates the status of the forwarding to the client.
    IPD_MMSE_MESSAGE_TYPE_M_MBOX_STORE_REQ = 0x8B,      ///< The client requests the storing of a message which was not retrieved yet.
    IPD_MMSE_MESSAGE_TYPE_M_MBOX_STORE_CONF = 0x8C,     ///< The acknowledgement of the server that the message was stored.
    IPD_MMSE_MESSAGE_TYPE_M_MBOX_VIEW_REQ = 0x8D,       ///< The client requests information about all stored messages in the mbox.
    IPD_MMSE_MESSAGE_TYPE_M_MBOX_VIEW_CONF = 0x8E,      ///< The server sends the requested information to the client.
    IPD_MMSE_MESSAGE_TYPE_M_MBOX_UPLOAD_REQ = 0x8F,     ///< The client uploads a message to the mbox.
    IPD_MMSE_MESSAGE_TYPE_M_MBOX_UPLOAD_CONF = 0x90,    ///< The acknowledgement of the server that the message was stored.
    IPD_MMSE_MESSAGE_TYPE_M_MBOX_DELETE_REQ = 0x91,     ///< The client deletes messages from the mbox.
    IPD_MMSE_MESSAGE_TYPE_M_MBOX_DELETE_CONF = 0x92,    ///< The acknowledgement of the server that the messages were delted.
    IPD_MMSE_MESSAGE_TYPE_M_MBOX_DESCR = 0x93,          ///< This type can be used with a M-Mbox-View.conf and a M-Mbox-Upload.req to describe the messages.
};

/**
 * Structure for a MMSE message type event
 */
struct ipd_mmse_message_type_struct {
    u64 message_id;                                                     ///< The Id of the current message.
    enum ipd_mmse_message_type_enum message_type;                       ///< The enumeration of the message type.
};

/**
 * Structure for a MMSE header end event
 */
struct ipd_mmse_header_end_struct {
    u64 message_id;                                                     ///< The Id of the current message.
};

/**
 * Structure for a MMSE header end event
 */
struct ipd_mmse_multipart_start_struct {
    u64 message_id;                                                     ///< The Id of the current message.
    u32 count_of_multiparts;                                            ///< The amount of the multiparts in the content of the MMSE-message
};

/**
 * Structure for a MMSE multipart end event
 */
struct ipd_mmse_multipart_end_struct {
    u64 message_id;                                                    ///< The Id of the current message.
    u64 multipart_id;                                                  ///< The Id of the current multipart.
};

/**
 * Structure for a MMSE message end event
 */
struct ipd_mmse_message_end_struct {
    u64 message_id;                                                    ///< The Id of the current message.
};

/** Enumeration for a "yes"/"no" choice. */
enum ipd_mmse_status_enum
{
    IPD_MMSE_STATUS_YES = 0x80,
    IPD_MMSE_STATUS_NO = 0x81,
};

/** MMS message class types */
enum ipd_mmse_message_class_enum
{
    IPD_MMSE_MESSAGE_CLASS_PERSONAL = 0x80,
    IPD_MMSE_MESSAGE_CLASS_ADVERTISEMENT = 0x81,
    IPD_MMSE_MESSAGE_CLASS_INFORMATIONAL = 0x82,
    IPD_MMSE_MESSAGE_CLASS_AUTO = 0x83,
    IPD_MMSE_MESSAGE_CLASS_TOKEN_TEXT = 0xFF,
};

/** MMS priority types */
enum ipd_mmse_priority_enum
{
    IPD_MMSE_PRIORITY_LOW = 0x80,
    IPD_MMSE_PRIORITY_NORMAL = 0x81,
    IPD_MMSE_PRIORITY_HIGH = 0x82,
};

/** MMS responce status types */
enum ipd_mmse_response_status_enum
{
    IPD_MMSE_RESPONSE_STATUS_OK = 0x80,
    IPD_MMSE_RESPONSE_STATUS_UNSPECIFIED = 0x81,
    IPD_MMSE_RESPONSE_STATUS_SERVICE_DENIED = 0x82,
    IPD_MMSE_RESPONSE_STATUS_MESSAGE_FORMAT_CORRUPT = 0x83,
    IPD_MMSE_RESPONSE_STATUS_SENDING_ADDRESS_UNRESOLVED = 0x84,
    IPD_MMSE_RESPONSE_STATUS_MESSAGE_NOT_FOUND = 0x85,
    IPD_MMSE_RESPONSE_STATUS_NETWORK_PROBLEM = 0x86,
    IPD_MMSE_RESPONSE_STATUS_CONTENT_NOT_ACCEPTED = 0x87,
    IPD_MMSE_RESPONSE_STATUS_UNSUPPORTED_MESSAGE = 0x88,
    IPD_MMSE_RESPONSE_STATUS_TRANSIENT_FAILURE = 0xc0,
    IPD_MMSE_RESPONSE_STATUS_TRANSIENT_SENDING_ADDRESS_UNRESOLVED = 0xc1,
    IPD_MMSE_RESPONSE_STATUS_TRANSIENT_MESSAGE_NOT_FOUND = 0xc2,
    IPD_MMSE_RESPONSE_STATUS_TRANSIENT_NETWORK_PROBLEM = 0xc3,
    IPD_MMSE_RESPONSE_STATUS_TRANSIENT_PARTIAL_SUCCESS = 0xc4,
    IPD_MMSE_RESPONSE_STATUS_PERMANENT_FAILURE = 0xe0,
    IPD_MMSE_RESPONSE_STATUS_PERMANENT_SERVICE_DENIED = 0xe1,
    IPD_MMSE_RESPONSE_STATUS_PERMANENT_MESSAGE_FORMAT_CORRUPT = 0xe2,
    IPD_MMSE_RESPONSE_STATUS_PERMANENT_SENDING_ADDRESS_UNRESOLVED = 0xe3,
    IPD_MMSE_RESPONSE_STATUS_PERMANENT_MESSAGE_NOT_FOUND = 0xe4,
    IPD_MMSE_RESPONSE_STATUS_PERMANENT_CONTENT_NOT_ACCEPTED = 0xe5,
    IPD_MMSE_RESPONSE_STATUS_PERMANENT_REPLY_CHARGING_LIMITATION_NOT_MET = 0xe6,
    IPD_MMSE_RESPONSE_STATUS_PERMANENT_REPLY_CHARGING_REQUEST_NOT_ACCEPTED = 0xe7,
    IPD_MMSE_RESPONSE_STATUS_PERMANENT_REPLY_CHARGING_FORWARDING_DENIED = 0xe8,
    IPD_MMSE_RESPONSE_STATUS_PERMANENT_REPLY_CHARGING_NOT_SUPPORTED = 0xe9,
    IPD_MMSE_RESPONSE_STATUS_PERMANENT_ADDRESS_HIDING_NOT_SUPPORTED = 0xea
};

/** MMS sender visibility types */
enum ipd_mmse_sender_visibility_enum {
    IPD_MMSE_SENDER_VISIBILITY_HIDE = 0x80,
    IPD_MMSE_SENDER_VISIBILITY_SHOW = 0x81,
};

/** MMS retrieve status types */
enum ipd_mmse_retrieve_status_enum
{
    IPD_MMSE_RETRIEVE_STATUS_OK = 0x80,
    IPD_MMSE_RETRIEVE_STATUS_TRANSIENT_FAILURE = 0xc0,
    IPD_MMSE_RETRIEVE_STATUS_TRANSIENT_MESSAGE_NOT_FOUND = 0xc1,
    IPD_MMSE_RETRIEVE_STATUS_TRANSIENT_NETWORK_PROBLEM = 0xc2,
    IPD_MMSE_RETRIEVE_STATUS_PERMANENT_FAILURE = 0xe0,
    IPD_MMSE_RETRIEVE_STATUS_PERMANENT_SERVICE_DENIED = 0xe1,
    IPD_MMSE_RETRIEVE_STATUS_PERMANENT_MESSAGE_NOT_FOUND = 0xe2,
    IPD_MMSE_RETRIEVE_STATUS_PERMANENT_CONTENT_UNSUPPORTED = 0xe3
};

/** MMS read status types */
enum ipd_mmse_read_status_enum
{
    IPD_MMSE_READ_STATUS_READ = 0x80,
    IPD_MMSE_READ_STATUS_DELETED_WITHOUT_BEING_READ = 0x81,
};

/** MMS reply charging types */
enum ipd_mmse_reply_charging_enum
{
    IPD_MMSE_REPLY_CHARGING_REQUESTED = 0x80,
    IPD_MMSE_REPLY_CHARGING_REQUESTED_TEXT_ONLY = 0x81,
    IPD_MMSE_REPLY_CHARGING_ACCEPTED = 0x82,
    IPD_MMSE_REPLY_CHARGING_ACCEPTED_TEXT_ONLY = 0x83,
};

/** MMS message status types */
enum ipd_mmse_message_status_enum
{
    IPD_MMSE_MESSAGE_STATUS_EXPIRED = 0x80,
    IPD_MMSE_MESSAGE_STATUS_RETRIEVED = 0x81,
    IPD_MMSE_MESSAGE_STATUS_REJECTED = 0x82,
    IPD_MMSE_MESSAGE_STATUS_DEFERRED = 0x83,
    IPD_MMSE_MESSAGE_STATUS_UNRECOGNIZED = 0x84,
    IPD_MMSE_MESSAGE_STATUS_INDETERMINATE = 0x85,
    IPD_MMSE_MESSAGE_STATUS_FORWARDED = 0x86,
    IPD_MMSE_MESSAGE_STATUS_UNREACHABLE = 0x87,
};

/** MMS Content types defined in WAPWSP 8.4.2.24 April 30 1998 (Appendix A, table 40) */
enum ipd_wap_content_type_enum
{
    IPD_MMSE_MMS_CONTENT_TYPE_ALL = 0x00,                                       ///< indicates '*/*'
    IPD_MMSE_MMS_CONTENT_TYPE_TEXT_ALL = 0x01,                                  ///< indicates 'text/*'
    IPD_MMSE_MMS_CONTENT_TYPE_TEXT_HTML = 0x02,									///< indicates 'text/html'
    IPD_MMSE_MMS_CONTENT_TYPE_TEXT_PLAIN = 0x03,								///< indicates 'text/plain'
    IPD_MMSE_MMS_CONTENT_TYPE_TEXT_X_HDML = 0x04,								///< indicates 'text/x-hdml'
    IPD_MMSE_MMS_CONTENT_TYPE_TEXT_X_TTML = 0x05,								///< indicates 'text/x-ttml'
    IPD_MMSE_MMS_CONTENT_TYPE_TEXT_X_CALENDAR = 0x06,							///< indicates 'text/x-vCalendar'
    IPD_MMSE_MMS_CONTENT_TYPE_TEXT_V_CARD = 0x07,								///< indicates 'text/x-vCard'
    IPD_MMSE_MMS_CONTENT_TYPE_TEXT_VND_WAP_WML = 0x08,							///< indicates 'text/vnd.wap.wml'
    IPD_MMSE_MMS_CONTENT_TYPE_TEXT_VND_WAP_WMLSCRIPT = 0x09,					///< indicates 'text/vnd.wap.wmlscript'
    IPD_MMSE_MMS_CONTENT_TYPE_TEXT_VND_WAP_EVENT = 0x0A,						///< indicates 'text/vnd.wap.wta-event'
    IPD_MMSE_MMS_CONTENT_TYPE_MULTIPART_ALL = 0x0B,								///< indicates 'multipart/*'
    IPD_MMSE_MMS_CONTENT_TYPE_MULTIPART_MIXED = 0x0C,							///< indicates 'multipart/mixed'
    IPD_MMSE_MMS_CONTENT_TYPE_MULTIPART_FORM_DATA = 0x0D,						///< indicates 'multipart/form-data'
    IPD_MMSE_MMS_CONTENT_TYPE_MULTIPART_BYTERANGES = 0x0E,						///< indicates 'multipart/byteranges'
    IPD_MMSE_MMS_CONTENT_TYPE_MULTIPART_ALTERNATIVE = 0x0F,						///< indicates 'multipart/alternative'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_ALL = 0x10,							///< indicates 'application/*'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_JAVA_VM = 0x11,						///< indicates 'application/java-vm'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_X_WWW_FORM_URLENCODED = 0x12,			///< indicates 'application/x-www-form-urlencoded'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_X_HDMLC = 0x13,       				///< indicates 'application/x-hdmlc'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_WAP_WMLC = 0x14,					///< indicates 'application/vnd.wap.wmlc'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_WAP_WMLSCRIPTC = 0x15,			///< indicates 'application/vnd.wap.wmlscriptc'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_WAP_WTA_EVENTC = 0x16,			///< indicates 'application/vnd.wap.wta-eventc'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_WAP_UAPROF = 0x17,				///< indicates 'application/vnd.wap.uaprof'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_WAP_WTLS_CA_CERTIFICATE = 0x18,	///< indicates 'application/vnd.wap.wtls-ca-certificate'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_WAP_WTLS_USER_CERTIFICATE = 0x19,	///< indicates 'application/vnd.wap.wtls-user-certificate'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_X_X509_CA_CERT = 0x1A,				///< indicates 'application/x-x509-ca-cert'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_X_X509_USER_CERT = 0x1B,				///< indicates 'application/x-x509-user-cert'
    IPD_MMSE_MMS_CONTENT_TYPE_IMAGE_ALL = 0x1C,									///< indicates 'image/*'
    IPD_MMSE_MMS_CONTENT_TYPE_IMAGE_GIF = 0x1D,									///< indicates 'image/gif'
    IPD_MMSE_MMS_CONTENT_TYPE_IMAGE_JPEG = 0x1E,								///< indicates 'image/jpeg'
    IPD_MMSE_MMS_CONTENT_TYPE_IMAGE_TIFF = 0x1F,								///< indicates 'image/tiff'
    IPD_MMSE_MMS_CONTENT_TYPE_IMAGE_PNG = 0x20,									///< indicates 'image/png'
    IPD_MMSE_MMS_CONTENT_TYPE_IMAGE_VND_WAP_WBMP = 0x21,						///< indicates 'image/vnd.wap.wbmp'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_WAP_MULTIPART_ALL = 0x22,			///< indicates 'application/vnd.wap.multipart.*'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_WAP_MULTIPART_MIXED = 0x23,		///< indicates 'application/vnd.wap.multipart.mixed'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_WAP_MULTIPART_FORM_DATA = 0x24,	///< indicates 'application/vnd.wap.multipart.form-data'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_WAP_MULTIPART_BYTERANGES = 0x25,	///< indicates 'application/vnd.wap.multipart.byteranges'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_WAP_MULTIPART_ALTERNATIVE = 0x26,	///< indicates 'application/vnd.wap.multipart.alternative'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_TEXT_XML = 0x27,						///< indicates 'application/xml'
    IPD_MMSE_MMS_CONTENT_TYPE_TEXT_XML = 0x28,									///< indicates 'text/xml'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_WAP_WBXML = 0x29,					///< indicates 'application/vnd.wap.wbxml'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_X_X968_CROSS_CERT = 0x2A,				///< indicates 'application/x-x968-cross-cert'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_X_X968_CA_CERT = 0x2B,				///< indicates 'application/x-x968-ca-cert'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_X_X968_USER_CERT = 0x2C,				///< indicates 'application/x-x968-user-cert'
    IPD_MMSE_MMS_CONTENT_TYPE_TEXT_VND_WAP_SI = 0x2D,							///< indicates 'text/vnd.wap.si'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_WAP_SIC = 0x2E,					///< indicates 'application/vnd.wap.sic'
    IPD_MMSE_MMS_CONTENT_TYPE_TEXT_VND_WAP_SL = 0x2F,							///< indicates 'text/vnd.wap.sl'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_WAP_SLC = 0x30,					///< indicates 'application/vnd.wap.slc',
    IPD_MMSE_MMS_CONTENT_TYPE_TEXT_VND_WAP_CO = 0x31,							///< indicates 'text/vnd.wap.co'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_WAP_COC = 0x32,					///< indicates 'application/vnd.wap.coc'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_WAP_MULTIPART_RELATED = 0x33,		///< indicates 'application/vnd.wap.multipart.related'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_WAP_SIA = 0x34,					///< indicates 'application/vnd.wap.sia'
    IPD_MMSE_MMS_CONTENT_TYPE_TEXT_VND_WAP_CONNECTIVITY_XML = 0x35,				///< indicates 'text/vnd.wap.connectivity-xml'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_WAP_CONNECTIVITY_WBXML = 0x36,	///< indicates 'application/vnd.wap.connectivity-wbxml'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_PKCS7_MIME = 0x37,					///< indicates 'application/pkcs7-mime'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_WAP_HASHED_CERTIFICATE = 0x38,	///< indicates 'application/vnd.wap.hashed-certificate'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_WAP_SIGNED_CERTIFICATE = 0x39,	///< indicates 'application/vnd.wap.signed-certificate'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_WAP_CERT_RESPONSE = 0x3A,			///< indicates 'application/vnd.wap.cert-response'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_XHTML_XML = 0x3B,						///< indicates 'application/xhtml+xml'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_WML_XML = 0x3C,						///< indicates 'application/wml+xml'
    IPD_MMSE_MMS_CONTENT_TYPE_TEXT_CSS = 0x3D,									///< indicates 'text/css'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_WAP_MMS_MESSAGE = 0x3E,			///< indicates 'application/vnd.wap.mms-message'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_WAP_ROLLOVER_CERTIFICATE = 0x3F,	///< indicates 'application/vnd.wap.rollover-certificate'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_WAP_LOCC_WBXML = 0x40,			///< indicates 'application/vnd.wap.locc+wbxml'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_WAP_LOC_XML = 0x41,				///< indicates 'application/vnd.wap.loc+xml'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_SYNCML_DM_WBXML = 0x42,			///< indicates 'application/vnd.syncml.dm+wbxml'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_SYNCML_DM_XML = 0x43,				///< indicates 'application/vnd.syncml.dm+xml'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_SYNCML_NOTIFICATION = 0x44,		///< indicates 'application/vnd.syncml.notification'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_WAP_XHTML_XML = 0x45,				///< indicates 'application/vnd.wap.xhtml+xml'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_WV_CSP_CIR = 0x46,				///< indicates 'application/vnd.wv.csp.cir'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_OMA_DD_XML = 0x47,				///< indicates 'application/vnd.oma.dd+xml'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_OMA_DRM_MESSAGE = 0x48,			///< indicates 'application/vnd.oma.drm.message'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_OMA_DRM_CONTENT = 0x49,			///< indicates 'application/vnd.oma.drm.content'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_OMA_DRM_RIGHT_XML = 0x4A,			///< indicates 'application/vnd.oma.drm.rights+xml'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_OMA_DRM_RIGHT_WBXML = 0x4B,		///< indicates 'application/vnd.oma.drm.rights+wbxml'
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_WV_CSP_XML = 0x4C,                ///< indicates application/vnd.wv.csp+xml
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_WV_CSP_WBXML = 0x4D,              ///< indicates application/vnd.wv.csp+wbxml
    IPD_MMSE_MMS_CONTENT_TYPE_APPLICATION_VND_SYNCML_DS_NOTIFICATION = 0x4E,    ///< indicates application/vnd.syncml.ds.notification
    IPD_MMSE_MMS_CONTENT_TYPE_AUDIO = 0x4F,                                     ///< indicates audio/*
    IPD_MMSE_MMS_CONTENT_TYPE_VIDEO = 0x50,                                     ///< indicates video/*
    IPD_MMSE_MMS_CONTENT_TYPE_UNKNOWN = 0xFF,                                   // should be last.
};

/** Enumeration for the parameter types. */
enum ipd_wap_content_parameters_enum
{
    IPD_MMSE_MMS_PARAMETER_Q = 0x00,
    IPD_MMSE_MMS_PARAMETER_CHARSET = 0x01,
    IPD_MMSE_MMS_PARAMETER_LEVEL = 0x02,
    IPD_MMSE_MMS_PARAMETER_TYPE_DEP = 0x03,
    IPD_MMSE_MMS_PARAMETER_UAPROF = 0x04,
    IPD_MMSE_MMS_PARAMETER_NAME = 0x05,
    IPD_MMSE_MMS_PARAMETER_FILENAME = 0x06,
    IPD_MMSE_MMS_PARAMETER_DIFFERENCES = 0x07,
    IPD_MMSE_MMS_PARAMETER_PADDING = 0x08,
    IPD_MMSE_MMS_PARAMETER_TYPE_TEXT = 0x09,
    IPD_MMSE_MMS_PARAMETER_START = 0xA,
    IPD_MMSE_MMS_PARAMETER_START_INFO = 0xB,
    IPD_MMSE_MMS_PARAMETER_UNKNOWN = 0xFF,
};

/** Enumeration of the WSP header fields in the multiparts. */
enum ipd_wap_wsp_header_field_enum
{
    IPD_MMSE_MMS_WSP_HEADER_CONTENT_ID = 0x40,
    IPD_MMSE_MMS_WSP_HEADER_CONTENT_LOCATION = 0x0E,
    IPD_MMSE_MMS_WSP_HEADER_CONTENT_DISPOSITION_OBSOLETE = 0x2E,
    IPD_MMSE_MMS_WSP_HEADER_CONTENT_DISPOSITION = 0x45,
    IPD_MMSE_MMS_WSP_HEADER_UNKNOWN = 0xFF
};

/** Structure for a MMSE version. */
struct ipd_mmse_version_struct {
    u8 major_version_number;                                                ///< The major version number. This has to be between 1 and 7.
    u8 minor_version_number;                                                ///< The minor version number. This has to be between 0 and 14.
    u8 is_minor_version_set;                                                ///< Indicates whether the minor number is valid or not.
};

/** Structure for a parameter value. */
struct ipd_mmse_pdu_parameter {
    struct ipd_string parameter_type_buffer;                                ///< The parameter type as a buffer.
    enum ipd_wap_content_parameters_enum parameter_type_enum;               ///< The corresponding enumeration.
    union {
        u8 untyped_type;                                                    ///< Indicates whether the integer_value (0) or the text_value (1) is used with an untyped type..
        u8 version_type;                                                    ///< Indicates whether the version value as a struct (0) or the version_string (1) is used with the version type.
        u8 differences_type;                                                ///< Indicates whether the integer_value (0) or the text_value (1) is used with the differences type.
        u8 type_text_type;                                                  ///< Indicates whether the integer_value (0) or the text_value (1) is used with the type_text type.
    } ext_value_type;                                                       ///< Union of the indicatores of some parameter values.
    union {
        struct ipd_string text_value;                                       ///< The text value as a struct ipd_string.
        u64 integer_value;                                                  ///< The integer value as a u64.
        u64 date_value;                                                     ///< The timestamp to a date as a u64.
        u64 delta_seconds_value;                                            ///< The delta in seconds as a u64.
        u32 q_value;                                                        ///< The Q-value as a u32.
        struct ipd_string uri_value;                                        ///< The URI value as a struct ipd_string.
        union {
            struct ipd_mmse_version_struct version;                         ///< The version as a struct ipd_mmse_version_struct.
            struct ipd_string version_string;                               ///< The string version.
        } version_value;                                                    ///< Union of the version value.
        enum ipd_charset charset_value;                                     ///< The charset value as an enumeration.
    } parameter_value;                                                      ///< Union of the parameter values.
};

/** Structure for a parameter list */
struct ipd_mmse_parameter_struct {
    struct ipd_mmse_pdu_parameter* parameters;                              ///< The list of all parameters.
    u64 parameter_length;                                                   ///< The length of the list.
};

/** Structure for a content type. */
struct ipd_mmse_pdu_content_type_struct {
    struct ipd_string content_type_buffer;                                  ///< The content type as a buffer.
    enum ipd_wap_content_type_enum content_type_enum;                       ///< The corresponding enumeration.
    struct ipd_mmse_parameter_struct parameter;                             ///< The parameter list as a struct ipd_mmse_parameter_struct.
};

/** Structure for a content location. */
struct ipd_mmse_pdu_content_location_struct {
    u8 message_type_is_mbox_delete_conf;                                    ///< Indicates whether the message type is M-Mbox-Delete.conf or not.
    u64 status_count_value;                                                 ///< The status count is set only if the flag "message_type_is_mbox_delete_conf" is set to 1.
    struct ipd_string content_location;                                     ///< The content location as a struct ipd_string.
};

/** Enumeration for the distinction of absolute or relative values. */
enum ipd_mmse_pdu_token_enum {
    IPD_MMSE_ABSOLUTE_TOKEN = 0x80,
    IPD_MMSE_RELATIVE_TOKEN = 0x81,
};

/** Structure for a delivery time value. */
struct ipd_mmse_pdu_delivery_time_struct {
    enum ipd_mmse_pdu_token_enum token;                                     ///< Indicates whether the date_value (IPD_MMSE_ABSOLUTE_TOKEN) or the delta_seconds_value (IPD_MMSE_RELATIVE_TOKEN) is used.
    union {
        u64 date_value;                                                     ///< The timestamp to the date as a u64.
        u64 delta_seconds_value;                                            ///< The delta in seconds as a u64.
    } delivery_time;                                                        ///< The union for the delivery time.
};

/** Structure for a element descriptor. */
struct ipd_mmse_pdu_element_descriptor_struct {
    struct ipd_string content_reference_value;                              ///< The content reference value as a struct ipd_string.
    struct ipd_mmse_parameter_struct parameter;                             ///< The parameter list as a struct ipd_mmse_parameter_struct.
};

/** Structure for a expiry value. */
struct ipd_mmse_pdu_expiry_struct {
    enum ipd_mmse_pdu_token_enum token;                                     ///< Indicates whether the date_value (IPD_MMSE_ABSOLUTE_TOKEN) or the delta_seconds_value (IPD_MMSE_RELATIVE_TOKEN) is used.
    union {
        u64 date_value;                                                     ///< The timestamp to the date as a u64.
        u64 delta_seconds_value;                                            ///< The delta in seconds as a u64.
    } expiry;                                                               ///< The union for the expiry.
};

/** Enumeration whether a address value is present or has to be inserted. */
enum ipd_mmse_pdu_address_enum {
    IPD_MMSE_ADDRESS_PRESENT_TOKEN = 0x80,
    IPD_MMSE_INSERT_ADDRESS_TOKEN = 0x81,
};

/** Structure of a from value */
struct ipd_mmse_pdu_from_struct {
    enum ipd_mmse_pdu_address_enum address_type;                            ///< Indicates whether the from value is present (IPD_MMSE_ADDRESS_PRESENT_TOKEN) or has to be inserted (IPD_MMSE_INSERT_ADDRESS_TOKEN).
    struct ipd_charset_string from_value;                                   ///< The from value if IPD_MMSE_ADDRESS_PRESENT_TOKEN is present.
};

/** Structure of a previously sent by value */
struct ipd_mmse_pdu_previously_sent_by_struct {
    u64 forwarded_count_value;                                              ///< The forwarded count value as a u64.
    struct ipd_charset_string string;                                       ///< The string value as a struct ipd_charset_string.
};

/** Structure of a previously sent date value */
struct ipd_mmse_pdu_previously_sent_date_struct {
    u64 forwarded_count_value;                                              ///< The forwarded count value as a u64.
    u64 date;                                                               ///< The timestamp to the date as a u64.
};

/** Enumeration for a quotas value. */
enum ipd_mmse_pdu_quota_enum {
    IPD_MMSE_MESSAGE_QUOTA_TOKEN = 0x80,
    IPD_MMSE_SIZE_QUOTA_TOKEN = 0x81
};

/** Structure for a mbox quotas value. */
struct ipd_mmse_pdu_mbox_quotas_struct {
    enum ipd_mmse_pdu_quota_enum quota;                                     ///< Indicates the type of the quota as an enumeration.
    u64 integer_value;                                                      ///< The integer value as a u64.
};

/** Enumeration for a totals value. */
enum ipd_mmse_pdu_total_enum {
    IPD_MMSE_MESSAGE_TOTAL_TOKEN = 0x80,
    IPD_MMSE_SIZE_TOTAL_TOKEN = 0x81
};

/** Structure for a mbox totals value. */
struct ipd_mmse_pdu_mbox_totals_struct {
    enum ipd_mmse_pdu_total_enum total;                                     ///< Indicates the type of the totals as an enumeration.
    u64 integer_value;                                                      ///< The integer value as a u64.
};

/** Structure for a message class value. */
struct ipd_mmse_pdu_message_class_struct {
    enum ipd_mmse_message_class_enum message_class;                         ///< The message class value as an enumeration. Indicates if the field token_text is set.
    struct ipd_string token_text;                                           ///< The value of the message class if the enumeration is set to IPD_MMSE_MESSAGE_CLASS_TOKEN_TEXT.
};

/** Enumeration for an action. */
enum ipd_mmse_pdu_token_action_enum {
    IPD_MMSE_ADD_TOKEN = 0x80,
    IPD_MMSE_REMOVE_TOKEN = 0x81,
    IPD_MMSE_FILTER_TOKEN = 0x82,
};

/** Structure for a flag value. */
struct ipd_mmse_pdu_flags_struct {
    enum ipd_mmse_pdu_token_action_enum token;                              ///< The action as an enumeration.
    struct ipd_charset_string flags;                                        ///< The flags as a struct ipd_charset_string.
};

/** Enumeration for the state value. */
enum ipd_mmse_pdu_state_enum {
    IPD_MMSE_STATE_DRAFT = 0x80,
    IPD_MMSE_STATE_SENT = 0x81,
    IPD_MMSE_STATE_NEW = 0x82,
    IPD_MMSE_STATE_RETRIEVED = 0x83,
    IPD_MMSE_STATE_FORWARDED = 0x84,
};

/** Structure for a reply charging deadline value. */
struct ipd_mmse_pdu_reply_charging_deadline_struct {
    enum ipd_mmse_pdu_token_enum token;                                     ///< Indicates whether the date_value (IPD_MMSE_ABSOLUTE_TOKEN) or the delta_seconds_value (IPD_MMSE_RELATIVE_TOKEN) is used.
    union {
        u64 date_value;                                                     ///< The timestamp to the date as a u64.
        u64 delta_seconds_value;                                            ///< The delta in seconds as a u64.
    } reply_charging_deadline;                                              ///< The union for the reply charging deadline.
};

/** Strucuture for a response text value. */
struct ipd_mmse_pdu_response_text_struct {
    u8 message_type_is_mbox_delete_conf;                                    ///< Indicates whether the message type is M-Mbox-Delete.conf or not.
    u64 status_count_value;                                                 ///< The status count is set only if the flag "message_type_is_mbox_delete_conf" is set to 1.
    struct ipd_charset_string response_text;                                ///< The content location as a struct ipd_charset_string.
};

/** Enumeration of the store status. */
enum ipd_mmse_store_status_enum {
    IPD_MMSE_STORE_STATUS_SUCCESS = 0x80,
    IPD_MMSE_STORE_STATUS_TRANSIENT_FAILURE = 0xC0,
    IPD_MMSE_STORE_STATUS_TRANSIENT_NETWORK_PROBLEM = 0xC1,
    IPD_MMSE_STORE_STATUS_PERMANENT_FAILURE = 0xE0,
    IPD_MMSE_STORE_STATUS_PERMANENT_SERVICE_DENIED = 0xE1,
    IPD_MMSE_STORE_STATUS_PERMANENT_MESSAGE_FORMAT_CORRUPT = 0xE2,
    IPD_MMSE_STORE_STATUS_PERMANENT_MESSAGE_NOT_FOUND = 0xE3,
    IPD_MMSE_STORE_STATUS_PERMANENT_MMBOX_FULL = 0xE4,
};

/** Enumeration of the disposition status. */
enum ipd_mmse_disposition_enum {
    IPD_MMSE_DISPOSITION_FORM_DATA = 0x80,
    IPD_MMSE_DISPOSITION_ATTACHMENT = 0x81,
    IPD_MMSE_DISPOSITION_INLINE = 0x82,
    IPD_MMSE_DISPOSITION_TOKEN_TEXT = 0xFF,
};

/** Structure for a content disposition value. */
struct ipd_mmse_content_disposition_struct {
    enum ipd_mmse_disposition_enum disposition;                                     ///< The disposition value as an enumeration. Indicates whether the field disposition_text is set or not.
    struct ipd_string disposition_text;                                             ///< The disposition value if the enumeration is set to IPD_MMSE_DISPOSITION_TOKEN_TEXT.
    struct ipd_mmse_parameter_struct parameter;                                     ///< The parameter list as a struct ipd_mmse_parameter_struct.
};

/** Structure for a pdu mmse header field value. */
struct ipd_mmse_pdu_value {
    u64 message_id;                                                                 ///< The Id of the current message.
    enum ipd_mmse_pdu_type_enum pdu_type;                                           ///< The enumeration of the header field value.
    union {
        enum ipd_mmse_pdu_type_enum attributes;                                     ///< The attributes as an enumeration.
        struct ipd_charset_string bcc;                                              ///< The BCC value as a struct ipd_charset_string.
        struct ipd_charset_string cc;                                               ///< The CC value as a struct ipd_charset_string.
        struct ipd_mmse_pdu_content_location_struct content_location;               ///< The content location as a struct ipd_mmse_pdu_content_location_struct.
        struct ipd_mmse_pdu_content_type_struct content_type;                       ///< The content type as a struct ipd_mmse_pdu_content_type_struct.
        u64 date;                                                                   ///< The timstamp to the date as a u64.
        enum ipd_mmse_status_enum delivery_report;                                  ///< The delivery report as an enumeration.
        struct ipd_mmse_pdu_delivery_time_struct delivery_time;                     ///< The delivery time as a struct ipd_mmse_pdu_delivery_time_struct.
        enum ipd_mmse_status_enum distribution_indicator;                           ///< The distribution indicator as an enumeration.
        struct ipd_mmse_pdu_element_descriptor_struct element_descriptor;           ///< The element descriptor as a struct ipd_mmse_pdu_element_descriptor_struct.
        struct ipd_mmse_pdu_expiry_struct expiry;                                   ///< The expiry as a struct ipd_mmse_pdu_expiry_struct.
        struct ipd_mmse_pdu_from_struct from;                                       ///< The from value as a struct ipd_mmse_pdu_from_struct.
        u64 limit;                                                                  ///< The limit as a u64.
        struct ipd_mmse_pdu_previously_sent_by_struct previously_sent_by;           ///< The previously sent by value as a struct ipd_mmse_pdu_previously_sent_by_struct.
        struct ipd_mmse_pdu_previously_sent_date_struct previously_sent_date;       ///< The previously sent date as a struct ipd_mmse_pdu_previously_sent_date_struct.
        struct ipd_mmse_pdu_mbox_quotas_struct mbox_quotas;                         ///< The mbox quotas as a struct ipd_mmse_pdu_mbox_quotas_struct.
        struct ipd_mmse_pdu_mbox_totals_struct mbox_totals;                         ///< The mbox totals as a struct ipd_mmse_pdu_mbox_totals_struct.
        struct ipd_mmse_pdu_message_class_struct message_class;                     ///< The message_class as a struct ipd_mmse_pdu_message_class_struct.
        u64 message_count;                                                          ///< The message count as a u64.
        struct ipd_string message_id;                                               ///< The message id as a struct ipd_string.
        u64 message_size;                                                           ///< The message size as a u64.
        struct ipd_mmse_pdu_flags_struct flags;                                     ///< The flags as a struct ipd_mmse_pdu_flags_struct.
        enum ipd_mmse_pdu_state_enum state;                                         ///< The state value as an enumeration.
        struct ipd_mmse_version_struct version;                                     ///< The version value as a struct ipd_mmse_version_struct.
        enum ipd_mmse_priority_enum priority;                                       ///< The priority as an enumeration.
        enum ipd_mmse_status_enum quotas;                                           ///< The quotas as an enumeration.
        enum ipd_mmse_status_enum read_report;                                      ///< The read report value as an enumeration.
        enum ipd_mmse_read_status_enum read_status;                                 ///< The read status as an enumeration.
        enum ipd_mmse_reply_charging_enum reply_charging;                           ///< The reply charging value as an enumeration.
        struct ipd_mmse_pdu_reply_charging_deadline_struct reply_charging_deadline; ///< The reply charging deadline as a struct ipd_mmse_pdu_reply_charging_deadline_struct.
        struct ipd_string reply_charging_id;                                        ///< The reply charging id as a struct ipd_string.
        u64 reply_charging_size;                                                    ///< The reply charging size as a u64.
        enum ipd_mmse_status_enum report_allowed;                                   ///< The report allowed value as an enumeration.
        enum ipd_mmse_response_status_enum response_status;                         ///< The response status value as an enumeration.
        struct ipd_mmse_pdu_response_text_struct response_text;                     ///< The response text as a struct ipd_mmse_pdu_response_text_struct.
        enum ipd_mmse_retrieve_status_enum retrieve_status;                         ///< The retrieve status as an enumeration.
        struct ipd_charset_string retrieve_text;                                    ///< The retrive text as a struct ipd_charset_string.
        enum ipd_mmse_sender_visibility_enum sender_visibility;                     ///< The sender visibility as an enumeration.
        u64 start;                                                                  ///< The start value as a u64.
        enum ipd_mmse_message_status_enum status;                                   ///< The status value as an enumeration.
        enum ipd_mmse_status_enum store;                                            ///< The store value as an enumeration.
        enum ipd_mmse_status_enum stored;                                           ///< The stored value as an enumeration.
        enum ipd_mmse_store_status_enum store_status;                               ///< The store_status as an enumeration.
        struct ipd_charset_string store_status_text;                                ///< The store status text as a struct ipd_charset_string.
        struct ipd_charset_string subject;                                          ///< The subject as a struct ipd_charset_string.
        struct ipd_charset_string to;                                               ///< The to value as a struct ipd_charset_string.
        enum ipd_mmse_status_enum totals;                                           ///< The totals as an enumeration.
        struct ipd_string transaction_id;                                           ///< The transaction id as a struct ipd_string.
    } pdu_value;                                                                    ///< The union of the pdu header values.
};

/**
 * Structure for a MMSE multipart header field value.
 */
struct ipd_mmse_multipart_header_struct {
    u64 message_id;                                                                 ///< The Id of the current message.
    u64 multipart_id;                                                               ///< The Id of the current multipart.
    enum ipd_wap_wsp_header_field_enum header_field;                                ///< The multipart header field enumeration.
    union {
        struct ipd_string content_id;                                               ///< The content id as a struct ipd_string.
        struct ipd_string content_location;                                         ///< The content location as a struct ipd_string.
        struct ipd_mmse_content_disposition_struct content_disposition;             ///< The content disposition as a struct ipd_mmse_content_disposition_struct.
    } header_value;                                                                 ///< The union of the multipart header value
};

/**
 * Structure for a MMSE multipart content type
 */
struct ipd_mmse_multipart_content_type_struct {
    u64 message_id;                                                                 ///< The Id of the current message.
    u64 multipart_id;                                                               ///< The Id of the current multipart.
    struct ipd_mmse_pdu_content_type_struct content_type;                           ///< The content type
};

/**
 * Structure for a MMSE multipart content.
 */
struct ipd_mmse_multipart_content_struct
{
    u64 message_id;                                                                 ///< The Id of the current message.
    u64 multipart_id;                                                               ///< The Id of the current multipart.
    struct ipd_string content;                                                      ///< The multipart data content.
};
#endif /* __IPOQUE_DECODER_MMSE_INCLUDE_FILE__ */
