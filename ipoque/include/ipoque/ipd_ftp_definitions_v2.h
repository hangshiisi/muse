/********************************************************************************/
/**
 ** \file       ipd_ftp_definitions_v2.h
 ** \brief      Structures and enumerations for all events of FTP in PACE2.
 **/
/********************************************************************************/

#ifndef __IPOQUE_DECODER_FTPV2_INCLUDE_FILE__
#define __IPOQUE_DECODER_FTPV2_INCLUDE_FILE__

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif
/**
 * Structure for a command in FTP.
 */
struct ipd_ftp_command
{
    /** The sent command code as enumeration code. @see ipd_ftp_command_enum*/
    enum ipd_ftp_command_enum code;
    /** The command name as string */
    struct ipd_charset_string name;
    /** The given argument for this command as string.*/
    struct ipd_charset_string argument;
};

typedef struct ipd_ftp_command ipd_ftp_command_int_t;


#endif /* __IPOQUE_DECODER_FTP_INCLUDE_FILE__ */
