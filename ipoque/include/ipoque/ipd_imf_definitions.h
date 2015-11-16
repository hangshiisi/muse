/********************************************************************************/
/**
 ** \file       ipd_imf_definitions.h
 ** \brief      Help structures for Mail Protocols with IMF content.
 **/
/********************************************************************************/

#ifndef __IPOQUE_DECODER_IMF_INCLUDE_FILE__
#define __IPOQUE_DECODER_IMF_INCLUDE_FILE__

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif

/** an IMF address */
struct ipd_imf_address {
    struct ipd_charset_string email;		/**< the actual email address */
    struct ipd_charset_string full;			/**< complete text of the address as it appeared in the IMF header field */
};

struct ipd_imf_content_type {
    /** section number as used in IMAP, e.g. "1.2" for the second sub-part of the first part of the mail
     * message; empty for the Content-Type line in the message header */
    struct ipd_charset_string part;
    struct ipd_charset_string full;     /**< complete text of the Content-Type field value */

    struct ipd_charset_string type;     /**< MIME media type */
    struct ipd_charset_string subtype;  /**< MIME media subtype */
    struct ipd_charset_string boundary; /**< value of the "boundary" parameter (for multipart types) */
    struct ipd_charset_string charset;  /**< value of the "charset" parameter, if available */
};


/** a string associated with a specific MIME part */
struct ipd_imf_part_data {
    /** section number as used in IMAP, e.g. "1.2" for the second sub-part of the first part of the mail
     * message; empty for non-MIME mails */
    struct ipd_charset_string part;

    struct ipd_charset_string data;
};

#endif                          /* __IPOQUE_DECODER_IMF_INCLUDE_FILE__ */
