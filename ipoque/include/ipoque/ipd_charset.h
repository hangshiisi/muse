/********************************************************************************/
/**
 ** \file       ipd_charset.h
 ** \brief      Definition for the structure ipd_charset_string and declaration
                of some helper functions for it.
 **/
/********************************************************************************/

/* DO NOT EDIT
 * This file has been automatically generated from the registered charset list maintained by IANA
 * (http://www.iana.org/assignments/character-sets).
 */

#ifndef __IPOQUE_DECODER_CHARSET_INCLUDE_FILE__
#define __IPOQUE_DECODER_CHARSET_INCLUDE_FILE__

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif

enum ipd_charset {
    CHARSET_STRING_CHARSET_UNKNOWN = 0,
    CHARSET_STRING_CHARSET_BINARY = 1,
    CHARSET_STRING_CHARSET_ASCII = 2,
    CHARSET_STRING_CHARSET_ISO8859_1 = 3,
    CHARSET_STRING_CHARSET_UTF8 = 105,
    CHARSET_STRING_CHARSET_UTF16BE = 129,
    CHARSET_STRING_CHARSET_UTF16LE = 130,
    CHARSET_STRING_CHARSET_UTF16 = 131,

    IPD_NUMBER_OF_CHARSETS = 255
};

struct ipd_charset_string {
    struct ipd_string content;
    enum ipd_charset charset;
};
typedef struct ipd_charset_string charset_string;

/* given a charset name (eg, "UTF-8" or "latin1"), return a character set code that can be used in the
 * charset_string.charset field */
enum ipd_charset ipd_charset_for_name(const struct ipd_string *name);

/* Given a MIME content-type line (eg, "text/xml; charset=utf-8"), return a character set code that can be
 * used in the charset_string.charset field.
 *
 * If contenttype is empty, the return value is CHARSET_STRING_CHARSET_UNKNOWN.
 * If contenttype is non-empty but contains no charset parameter
 *   and starts with "text/", the return value is CHARSET_STRING_CHARSET_UNKNOWN,
 *   otherwise, the return value is CHARSET_STRING_CHARSET_BINARY.
 * Otherwise, the value of the charset parameter is used to look up a charset code.
 */
enum ipd_charset ipd_charset_for_contenttype(const struct ipd_string *contenttype);

const char *ipd_charset_name(enum ipd_charset cs);
const char *ipd_charset_name_from_iana_no(u64 val);
void ipd_csprint(FILE *f, const struct ipd_charset_string *s);

#endif
