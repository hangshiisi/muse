/********************************************************************************/
/**
 ** \file       ssl_events.h
 ** \brief      SSL event definitions
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef SSL_EVENTS_H
#define SSL_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Groups *****************************************************************/
/**
 * @brief Public define for the assigned meta data group of the basic SSL client hello event.
 */
#define PACE2_BASIC_SSL_CLIENT_HELLO_EVENT_GROUP PACE2_BASIC_PROTOCOL_META_DATA_GROUP

/**
 * @brief Public define for the assigned meta data group of the basic SSL server hello event.
 */
#define PACE2_BASIC_SSL_SERVER_HELLO_EVENT_GROUP PACE2_BASIC_PROTOCOL_META_DATA_GROUP

/**
 * @brief Public define for the assigned meta data group of the basic SSL dns alt names event.
 */
#define PACE2_BASIC_SSL_DNS_ALT_NAMES_EVENT_GROUP PACE2_BASIC_PROTOCOL_META_DATA_GROUP

/* Event Types ******************************************************************/

/**
 * @brief Meta data flags of SSL client hello events.
 */
typedef enum {
    PACE2_SSL_SERVER_NAME = 0,          /**< Server name line. */
    PACE2_SSL_CLIENT_SESSION_ID,        /**< Session ID line. */

    PACE2_NUMBER_OF_CLIENT_HELLO_LINES  /**< Number of implemented client hello lines. */
} PACE2_SSL_client_hello_line;

/**
 * @brief Meta data flags of SSL server hello events.
 */
typedef enum {
    PACE2_SSL_SERIAL_NUMBER = 0,        /**< Serial number line. */
    PACE2_SSL_VALIDITY_NOT_BEFORE,      /**< Validity-not-before line. */
    PACE2_SSL_VALIDITY_NOT_AFTER,       /**< Validity-not-after line. */
    PACE2_SSL_COUNTRY_NAME,             /**< Country name line. */
    PACE2_SSL_POSTAL_CODE,              /**< Postal code line. */
    PACE2_SSL_STATE_OR_PROVINCE_NAME,   /**< State name line. */
    PACE2_SSL_LOCALITY_NAME,            /**< Locality name line. */
    PACE2_SSL_STREET_ADDRESS,           /**< Street address line. */
    PACE2_SSL_ORGANIZATION_NAME,        /**< Organization name line. */
    PACE2_SSL_ORGANIZATIONAL_UNIT_NAME, /**< Organizational unit name line. */
    PACE2_SSL_COMMON_NAME,              /**< Common name line. */
    PACE2_SSL_SERVER_SESSION_ID,        /**< Session ID line. */
    PACE2_SSL_CIPHER_SUITE,             /**< SSL Cipher Suite. */

    PACE2_NUMBER_OF_SERVER_HELLO_LINES  /**< Number of implemented server hello lines. */
} PACE2_SSL_server_hello_line;

/* Event Structures *************************************************************/

/**
 * @brief Data structure of a SSL client hello meta data event.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_BASIC_SSL_CLIENT_HELLO_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_bitmask meta_data_mask;       /**< Bitmask, which states the available SSL client hello meta data */
    struct {
        PACE2_SSL_client_hello_line type;       /**< Client hello line of type @ref PACE2_SSL_client_hello_line .*/
        PACE2_byte_buffer content;              /**< Client hello line content. */
    } line[PACE2_NUMBER_OF_CLIENT_HELLO_LINES]; /**< Data structure for a event of type @ref PACE2_BASIC_SSL_CLIENT_HELLO_EVENT .
                                                     Contains content for each available line of type @ref PACE2_SSL_client_hello_line */
} PACE2_SSL_client_hello_event;

/**
 * @brief Data structure of a SSL server hello meta data event.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_BASIC_SSL_SERVER_HELLO_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_bitmask meta_data_mask;       /**< Bitmask, which states the available SSL server hello meta data */
    struct {
        PACE2_SSL_server_hello_line type;       /**< Server hello line of type @ref PACE2_SSL_server_hello_line .*/
        PACE2_byte_buffer content;              /**< Server hello line content. */
    } line[PACE2_NUMBER_OF_SERVER_HELLO_LINES]; /**< Data structure for a event of type @ref PACE2_BASIC_SSL_SERVER_HELLO_EVENT.
                                                     Contains the content for each available line of type @ref PACE2_SSL_server_hello_line */
} PACE2_SSL_server_hello_event;

/**
 * @brief Data structure of a SSL DNS alternative names meta data event.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_BASIC_SSL_DNS_ALT_NAMES_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_byte_buffer entries[IPOQUE_MAX_PARSE_SSL_DNS_ALT_NAMES];
    u16 number_of_entries;
} PACE2_SSL_dns_alt_names_event;

#endif /* SSL_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
