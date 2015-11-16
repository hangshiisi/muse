/********************************************************************************/
/**
 ** \file       ipd_class_mail_definitions.h
 ** \brief      Structures and enumerations for all events of class mail.
 **/
/********************************************************************************/

#ifndef IPD_CLASS_MAIL_DEFINITIONS_H_
#define IPD_CLASS_MAIL_DEFINITIONS_H_

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif

/** Enumeration for the mail protocol type*/
enum ipd_mail_class_type
{
	/** Indicates a POP3 mail class type.*/
    IPD_MAIL_PROTOCOL_CLASS_POP3,
    /** Indicates a SMTP mail class type.*/
    IPD_MAIL_PROTOCOL_CLASS_SMTP,
    /** Indicates a IMAP mail class type.*/
    IPD_MAIL_PROTOCOL_CLASS_IMAP,
    /** Indicates a YAHOO WEBMAIL mail class type.*/
    IPD_MAIL_PROTOCOL_CLASS_WEBMAIL_YAHOO,
    /** Indicates a GAWAB WEBMAIL mail class type.*/
    IPD_MAIL_PROTOCOL_CLASS_WEBMAIL_GAWAB,
    /** Indicates a MAKTOOB WEBMAIL mail class type.*/
    IPD_MAIL_PROTOCOL_CLASS_WEBMAIL_MAKTOOB,
    /** Indicates a MAIL_DOT_COM mail class type.*/
    IPD_MAIL_PROTOCOL_CLASS_WEBMAIL_MAIL_DOT_COM,
    /** Indicates a GMX mail class type */
    IPD_MAIL_PROTOCOL_CLASS_WEBMAIL_GMX,
    /** Indicates a Hotmail mail class type */
    IPD_MAIL_PROTOCOL_CLASS_WEBMAIL_HOTMAIL,
    /** Indicates a Mail.ru mail class type.*/
    IPD_MAIL_PROTOCOL_CLASS_WEBMAIL_MAIL_DOT_RU,
};

/** Enumeration for the mail session status*/
enum ipd_mail_class_session_status
{
	/** Indicates that the session is started.*/
	IPD_MAIL_CLASS_SESSION_START,
	/** Indicates that the session is ended.*/
	IPD_MAIL_CLASS_SESSION_END,
};

/**
 * Enumeration for class mail events. This is passed as type to the ipd_decoder_class_event_callback.
 * @see ipd_decoder_class_event_callback
 */
enum ipd_mail_class_struct_enum
{
	/** Indicates an update for a mail session or a new mail session and provides a struct ipd_class_mail_session_struct * with the generic, protocol type, status and a ID for the correlating connection.*/
    IPD_MAIL_CLASS_SESSION,						// ipd_class_mail_session_struct
    /** Provides a struct ipd_class_mail_session_string_struct * with the generic, the session ID for the correlating session and the login name of the user.*/
    IPD_MAIL_CLASS_LOGIN,						// ipd_class_mail_session_string_struct
    /** Provides a struct ipd_class_mail_session_string_struct * with the generic, the session ID for the correlating session and the password of the user.*/
    IPD_MAIL_CLASS_PASS,						// ipd_class_mail_session_string_struct
    /** Indicates an update for a mail transfer or a new mail transfer and provides a struct ipd_class_mail_transfer_struct * with all information about the transfer.*/
    IPD_MAIL_CLASS_SESSION_TRANSFER,			// ipd_class_mail_transfer_struct
    /** Provides a struct ipd_class_mail_transfer_body_struct * with the next part of the body by a mail transfer.*/
    IPD_MAIL_CLASS_SESSION_BODY_TRANSFER,		// ipd_class_mail_transfer_body_struct

    /** Indicates that the mail transfer with the ID specified in the argument is done. For the webmail, POP3,
     * and SMTP decoders this means that the transfer ID won't be referenced in further events. The IMAP
     * decoder will use this ID again if the same message (identified by its message sequence number in the
     * mailbox) is referenced by another command. Webmail decoders are not guaranteed to emit a TRANSFER_END
     * event for all mail transfers. \c data points to a */
    IPD_MAIL_CLASS_SESSION_TRANSFER_END,        /**< u64. */

    /* new event types for webmail */

    /** Provides a struct ipd_class_mail_attachment_info_struct * with information about an attachment. Can be thrown more than one time for a update of some values.*/
    IPD_MAIL_CLASS_ATTACHMENT_INFO,				// ipd_class_mail_attachment_info_struct
    /** Provides a struct ipd_class_mail_attachment_content_struct * with one segment of a mail attachment.*/
    IPD_MAIL_CLASS_ATTACHMENT_CONTENT,			// ipd_class_mail_attachment_content_struct
    /** Provides a struct ipd_class_mail_list_folder_struct * with content about the mail folder content in a webmail session.*/
    IPD_MAIL_CLASS_LIST_FOLDER,					// ipd_class_mail_list_folder_struct

    IPD_NUMBER_OF_MAIL_CLASS_EVENTS,
};

/**
 * Enumeration for the direction of a mail transfer.
 */
enum ipd_mail_class_direction_enum
{
    IPD_MAIL_CLASS_DIRECTION_FETCH,
    IPD_MAIL_CLASS_DIRECTION_SEND,
    IPD_MAIL_CLASS_DIRECTION_STORE
};

/**
 * Structure for a mail session update \n
 * used for: \n
 * #IPD_MAIL_CLASS_SESSION \n
 */
struct ipd_class_mail_session_struct
{
	/** The generic. Contains the unique ID of this event @see ipd_class_generic_header*/
    struct ipd_class_generic_header generic;

    /** The type of this mail session (protocol type) @see ipd_mail_class_type*/
    enum ipd_mail_class_type type;
    /** The status of this mail session @see ipd_mail_class_session_status*/
    enum ipd_mail_class_session_status status;

    /** The unique ID of the corresponding tcp connection of the mail.*/
    u64 connection_id;          // reference to (tcp) connection id, TODO: mail protocols with multiple connections ??
};

/**
 * Structure for a information about the user, like login name and password \n
 * used for: \n
 * #IPD_MAIL_CLASS_LOGIN \n
 * #IPD_MAIL_CLASS_PASS \n
 */
struct ipd_class_mail_session_string_struct
{
	/** The generic. Contains the ID of this event @see ipd_class_generic_header*/
    struct ipd_class_generic_header generic;
    /** The ID of the correlating session.*/
    u64 mail_session_id;
    /** The information, which is send.*/
    struct ipd_charset_string string;
};

/**
 * Structure for a mail transfer.\n
 * used for: \n
 * #IPD_MAIL_CLASS_SESSION_TRANSFER \n
 */
struct ipd_class_mail_transfer_struct
{
	/** The generic. Contains the ID of this event @see ipd_class_generic_header*/
    struct ipd_class_generic_header generic;
    /** The ID of the correlating session.*/
    u64 mail_session_id;
    /** The direction of this transfer @see ipd_mail_class_direction_enum. */
    enum ipd_mail_class_direction_enum direction;


    /** The sender sender provided by the server (SMTP MAIL FROM). */
    struct ipd_charset_string envelope_from;
    /** The length of the envelope_to array.*/
    u64 envelope_to_array_len;
    /** The array containing the recipients provided by the server (SMTP RCPT TO). */
    struct ipd_charset_string *envelope_to;

    /** The sender of the mail. */
    struct ipd_imf_address from;

    /* array of "to" recipients */
    /** The length of the to array.*/
    u64 to_array_len;
    /** The array containing the "to" recipients of the mail.*/
    struct ipd_imf_address *to;

    /* array of cc'ed recipients */
    /** The length of the cc array.*/
    u64 cc_array_len;
    /** The array containing the "cc" recipients of the mail.*/
    struct ipd_imf_address *cc;

    /* array of bcc'ed recipients */
    /** The length of the bcc array.*/
    u64 bcc_array_len;
    /** The array containing the "bcc" recipients of the mail.*/
    struct ipd_imf_address *bcc;

    /* array of imf received lines */
	/** The length of the imf_received array.*/
	u64 imf_received_array_len;
	/** The array containing the "imf received lines" of the mail.*/
	struct ipd_charset_string *imf_received;

    /** The return-path contained in the header.*/
    struct ipd_charset_string return_path;

    /* array of imf other lines */
	/** The length of the imf_other array.*/
	u64 imf_others_array_len;
	/** The array containing the "imf other lines" of the mail.*/
	struct ipd_charset_string *imf_others;

    /** The date in the protocol headerline.*/
    struct ipd_charset_string date_headerline;

    /** The subject of the mail.*/
    struct ipd_charset_string subject;

    /** The sender of the mail. */
    struct ipd_imf_address sender;

    /** The reply_to address of the mail. */
    struct ipd_imf_address reply_to;

    /** The message id of the mail. */
    struct ipd_charset_string message_id;

    /** The in_reply_to address of the mail. */
    struct ipd_charset_string in_reply_to;

    /** The references header line of the mail. */
    struct ipd_charset_string references;

    /** The comments header line of the mail. */
    struct ipd_charset_string comments;

    /** The keywords header line of the mail. */
    struct ipd_charset_string keywords;

    /** The trace header line of the mail. */
    struct ipd_charset_string trace;

    /** The resent_date header line of the mail. */
    struct ipd_charset_string resent_date;

    /** The resent_from header line of the mail. */
    struct ipd_imf_address resent_from;

    /** The resent_sender header line of the mail. */
    struct ipd_imf_address resent_sender;

	/** The length of the resent_to array.*/
	u64 resent_to_array_len;
	/** The array containing the "resent to" header lines of the mail.*/
	struct ipd_imf_address *resent_to;

	/** The length of the resent_cc array.*/
	u64 resent_cc_array_len;
	/** The array containing the "resent cc" header lines of the mail.*/
	struct ipd_imf_address *resent_cc;

	/** The length of the resent_bcc array.*/
	u64 resent_bcc_array_len;
	/** The array containing the "resent bcc" header lines of the mail.*/
	struct ipd_imf_address *resent_bcc;

    /** The resent_message_id header line of the mail. */
    struct ipd_charset_string resent_message_id;
};

/**
 * Structure for a body transfer.\n
 * used for:\n
 * #IPD_MAIL_CLASS_SESSION_BODY_TRANSFER\n
 */
struct ipd_class_mail_transfer_body_struct
{
	/** The generic. Contains the ID of this event @see ipd_class_generic_header*/
    struct ipd_class_generic_header generic;
    /** the ID of the mail session */
    u64 mail_session_id;
    /** The ID of the correlating mail transfer.*/
    u64 mail_transfer_id;

    /** The offset of this part of from the mail body.*/
    u64 body_offset;
    /** The part of the body, which is send in this event.*/
    struct ipd_charset_string body;

	/** The MIME content-type of this mail part */
	struct ipd_charset_string content_type;
    /** The content-transfer-encoding of the data delivered in #body */
    struct ipd_charset_string transfer_encoding;

    /** direction of the mail transfer */
    enum ipd_mail_class_direction_enum direction;

    /** A Flag that is set when the present event contains the final segment of the body data. */
    u8 body_transfer_finished;
};

/** The possible causes of an #IPD_MAIL_CLASS_ATTACHMENT_INFO event. */
enum ipd_mail_class_attachment_info_origin
{
    /** Information \em about an attachment (meta-information) has been observed. */
    IPD_MAIL_CLASS_ATTACHMENT_INFO_FROM_REFERENCE,
    /** The attachment content itself is transmitted. */
    IPD_MAIL_CLASS_ATTACHMENT_INFO_FROM_TRANSFER
};

/**
 * Structure for information about a mail attachment.\n
 * used for:\n
 * #IPD_MAIL_CLASS_ATTACHMENT_INFO\n
 *
 * Apart from the key (#generic) and the origin (#info_origin), all fields are optional and may be set to the empty string or 0,
 * respectively, if they are not known at the time the event is reported. If at a later time, more information
 * about the attachment becomes known, another #IPD_MAIL_CLASS_ATTACHMENT_INFO event with the same generic.id
 * will be sent, where some of the previously unknown fields will be defined.
 */
struct ipd_class_mail_attachment_info_struct
{
	/** The generic. Contains the ID of this event @see ipd_class_generic_header*/
    struct ipd_class_generic_header generic;

    /** \brief The cause of this INFO event
        \details PADE generates ATTACHMENT_INFO events on two different occasions:
          \li When information \em about an attachment is observed (meta-information; for instance, a list of
              attachments in a "view message" window).
          \li When the attachment content itself is transmitted.

          In the former case, this field contains #IPD_MAIL_CLASS_ATTACHMENT_INFO_FROM_REFERENCE, in the
          latter case, #IPD_MAIL_CLASS_ATTACHMENT_INFO_FROM_TRANSFER
    */
    enum ipd_mail_class_attachment_info_origin info_origin;
    /** the ID of the mail session */
    u64 mail_session_id;
    /** The ID of the correlating mail transfer.*/
	u64 mail_transfer_id;
    /** direction of the mail transfer */
    enum ipd_mail_class_direction_enum direction;

	/** A unique identifier string*/
	struct ipd_charset_string identifier_string;

    /** A flag that states whether or not the #size field of this ipd_class_mail_attachment_info_struct is set. */
    u8 size_is_set:1;
	/** The size of the attachment. Is set, if this information is available and not a approximated value\n*/
	u64 size;
	/** The MIME content-type of the attachment */
	struct ipd_charset_string content_type;
    /** The content-transfer-encoding of the data delivered in the ATTACHMENT_CONTENT event */
    struct ipd_charset_string transfer_encoding;
	/** The file name of the attachment*/
	struct ipd_charset_string file_name;
};

/**
 * Structure for one segment of a mail attachment content transfer\n
 * used for:\n
 * #IPD_MAIL_CLASS_ATTACHMENT_CONTENT\n
 */
struct ipd_class_mail_attachment_content_struct
{
	/** The generic. Contains the same ID like the correlating IPD_MAIL_CLASS_ATTACHMENT_INFO event @see ipd_class_generic_header */
    struct ipd_class_generic_header generic;

    /** the ID of the mail session */
    u64 mail_session_id;

    /** direction of the mail transfer */
    enum ipd_mail_class_direction_enum direction;

    /** offset (relative to the start of the entire attachment) of the data in #content */
    u64 offset;

    /** one segment of the mail attachment*/
    struct ipd_charset_string content;

    /** a flag that is set when the present event contains the final segment of the attachment data. */
    u8 attachment_transfer_finished;
};

/**
 * Structure for a mail list folder entry\n
 * used for:\n
 * ipd_class_mail_list_folder_struct \n
 */
struct ipd_class_mail_list_folder_entry
{
	/** The name of the folder*/
	struct ipd_charset_string folder_name;
	/** The subject of the entry*/
	struct ipd_charset_string subject;
	/** The information about from (name)*/
	struct ipd_charset_string from_name;
	/** The information about from (mail address)*/
	struct ipd_charset_string from_email;
	/** This flag signals, if a mail is unreaded or not*/
	u8 unread;
	/** The size of the mail, is set, if the information is available and not a approximated value.*/
	u64 size;
	/** The timestamp of the mail, is set, if the information is available*/
	u64 timestamp;
};

/**
 * Structure for a mail list folder content\n
 * used for:\n
 * #IPD_MAIL_CLASS_LIST_FOLDER\n
 */
struct ipd_class_mail_list_folder_struct
{
	/** The generic. Contains the ID of this event @see ipd_class_generic_header*/
    struct ipd_class_generic_header generic;
    /** The ID of the correlating mail session.*/
    u64 mail_session_id;

	/** The name of the folder*/
	struct ipd_charset_string folder_name;
    /** The length of the entry array*/
    u64 entry_array_len;
    /** The array containing the mail summaries of the mails in this folder.\n @see ipd_class_mail_list_folder_entry*/
    struct ipd_class_mail_list_folder_entry *entry;
};

#endif                          /* IPD_CLASS_MAIL_DEFINITIONS_H_ */
