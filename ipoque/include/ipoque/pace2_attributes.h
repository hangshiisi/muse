/********************************************************************************/
/**
 ** \file       pace2_attributes.h
 ** \brief      PACE 2 attributes definitions
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef PACE2_ATTRIBUTES_H
#define PACE2_ATTRIBUTES_H

/* Includes *********************************************************************/
#include "pace2_basic_def.h"

/* Public Types *****************************************************************/

/**
 * @brief Enum defining all available application attributes.
**/
typedef enum pace2_application_attributes {
    PACE2_APPLICATION_ATTRIBUTE_NONE = 0,
    PACE2_APPLICATION_ATTRIBUTE_ENCRYPTED,
    PACE2_APPLICATION_ATTRIBUTE_AUDIO,
    PACE2_APPLICATION_ATTRIBUTE_LANDLINECALL,
    PACE2_APPLICATION_ATTRIBUTE_VIDEO,
    PACE2_APPLICATION_ATTRIBUTE_FILE_TRANSFER,
    PACE2_APPLICATION_ATTRIBUTE_WEB,
    PACE2_APPLICATION_ATTRIBUTE_CHAT,
    PACE2_APPLICATION_ATTRIBUTE_MAIL,
    PACE2_APPLICATION_ATTRIBUTE_STREAM,
    PACE2_APPLICATION_ATTRIBUTE_OS_ANDROID,
    PACE2_APPLICATION_ATTRIBUTE_OS_IOS,
    PACE2_APPLICATION_ATTRIBUTE_OS_WINDOWS_MOBILE,
    PACE2_APPLICATION_ATTRIBUTE_OS_BLACKBERRY,
    PACE2_APPLICATION_ATTRIBUTE_PICTURE,
    PACE2_APPLICATION_ATTRIBUTE_DDL,
    PACE2_APPLICATION_ATTRIBUTE_GOOGLE,
    PACE2_APPLICATION_ATTRIBUTE_MSEXCHANGE_OUTLOOK_WEB_ACCESS,
    PACE2_APPLICATION_ATTRIBUTE_AMAZON_CLOUD,
    PACE2_APPLICATION_ATTRIBUTE_APACHE,
    PACE2_APPLICATION_ATTRIBUTE_MYSQL_SERVER,
    PACE2_APPLICATION_ATTRIBUTE_MARIADB_SERVER,

    PACE2_APPLICATION_ATTRIBUTES_COUNT

} PACE2_application_attributes;

#define PACE2_APPLICATION_ATTRIBUTES_STRINGS \
    "none",\
    "encrypted",\
    "audio",\
    "out",\
    "video",\
    "file-transfer",\
    "web",\
    "chat",\
    "mail",\
    "stream",\
    "android",\
    "ios",\
    "windows-mobile",\
    "blackberry",\
    "picture",\
    "ddl",\
    "google",\
    "outlook_web_access",\
    "amazon-cloud",\
    "apache",\
    "mysql-server",\
    "mariadb-server"


/**
 * @brief Enum defining all available protocol attributes.
**/
typedef enum pace2_protocol_attributes {
    PACE2_PROTOCOL_ATTRIBUTE_NONE = 0,
    PACE2_PROTOCOL_ATTRIBUTE_IPSEC_PAYLOAD,
    PACE2_PROTOCOL_ATTRIBUTE_IPSEC_ISAKMP,
    PACE2_PROTOCOL_ATTRIBUTE_FTP_CONTROL,
    PACE2_PROTOCOL_ATTRIBUTE_FTP_DATA,
    PACE2_PROTOCOL_ATTRIBUTE_GTP_UP,
    PACE2_PROTOCOL_ATTRIBUTE_GTP_CP,
    PACE2_PROTOCOL_ATTRIBUTE_GTP_PRIME,
    PACE2_PROTOCOL_ATTRIBUTE_GTP_V1,
    PACE2_PROTOCOL_ATTRIBUTE_GTP_V2,
    PACE2_PROTOCOL_ATTRIBUTE_SOCKS_V4,
    PACE2_PROTOCOL_ATTRIBUTE_SOCKS_V5,
    PACE2_PROTOCOL_ATTRIBUTE_MEDIA,
    PACE2_PROTOCOL_ATTRIBUTE_UTP,
    PACE2_PROTOCOL_ATTRIBUTE_DIRECTCONNECT_HUB,
    PACE2_PROTOCOL_ATTRIBUTE_DIRECTCONNECT_PEER,
    PACE2_PROTOCOL_ATTRIBUTE_DIRECTCONNECT_ADC_PEER,
    PACE2_PROTOCOL_ATTRIBUTE_SPDY,
    PACE2_PROTOCOL_ATTRIBUTE_TELNET_TN3270,
    PACE2_PROTOCOL_ATTRIBUTE_TCP_WO_HANDSHAKE,
    PACE2_PROTOCOL_ATTRIBUTE_IEC61850_GOOSE,
    PACE2_PROTOCOL_ATTRIBUTE_IEC61850_MMS,
    PACE2_PROTOCOL_ATTRIBUTE_IEC61850_SV,

    PACE2_PROTOCOL_ATTRIBUTES_COUNT

} PACE2_protocol_attributes;

#define PACE2_PROTOCOL_ATTRIBUTES_STRINGS \
    "none",\
    "ipsec_payload",\
    "ipsec_isakmp",\
    "ftp_control",\
    "ftp_data",\
    "gtp_up",\
    "gtp_cp",\
    "gtp_prime",\
    "gtp_v1",\
    "gtp_v2",\
    "socks_v4",\
    "socks_v5",\
    "media",\
    "uTP",\
    "hub",\
    "peer",\
    "adc-peer",\
    "spdy",\
    "tn3270",\
    "tcp_wo_hs",\
    "iec61850_goose",\
    "iec61850_manufacturing-message",\
    "iec61850_sampled-values"


#endif /* PACE2_ATTRIBUTES_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
