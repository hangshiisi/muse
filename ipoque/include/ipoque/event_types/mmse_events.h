/********************************************************************************/
/**
 ** \file       mmse_events.h
 ** \brief      mmse stage4 event definitions
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef MMSE_EVENTS_H
#define MMSE_EVENTS_H

/* Includes *********************************************************************/
#include "common_event_defs.h"

/* Event Group ******************************************************************/
/**
 * @brief Public define for the assigned meta data group of the advanced MMSE event.
 */
#define PACE2_ADVANCED_MMSE_EVENT_GROUP PACE2_ADVANCED_PROTOCOL_META_DATA_GROUP

/* Event Types ******************************************************************/
/**
 * @brief Types for advanced MMSE events.
 */
typedef enum {
    PACE2_ADVANCED_MMSE_NEW_CONNECTION,                         /**< @ref IPD_EVENT_MMSE_NEW_CONNECTION */
    PACE2_ADVANCED_MMSE_PDU_MESSAGE_TYPE,                       /**< @ref IPD_EVENT_MMSE_PDU_MESSAGE_TYPE */
    PACE2_ADVANCED_MMSE_PDU_HEADERLINE,                         /**< @ref IPD_EVENT_MMSE_PDU_HEADERLINE */
    PACE2_ADVANCED_MMSE_PDU_HEADER_END,                         /**< @ref IPD_EVENT_MMSE_PDU_HEADER_END */
    PACE2_ADVANCED_MMSE_PDU_DATA_MULTIPART_START,               /**< @ref IPD_EVENT_MMSE_PDU_DATA_MULTIPART_START */
    PACE2_ADVANCED_MMSE_PDU_DATA_MULTIPART_PART_CONTENT_TYPE,   /**< @ref IPD_EVENT_MMSE_PDU_DATA_MULTIPART_PART_CONTENT_TYPE */
    PACE2_ADVANCED_MMSE_PDU_DATA_MULTIPART_PART_HEADERLINE,     /**< @ref IPD_EVENT_MMSE_PDU_DATA_MULTIPART_PART_HEADERLINE */
    PACE2_ADVANCED_MMSE_PDU_DATA_MULTIPART_PART_CONTENT,        /**< @ref IPD_EVENT_MMSE_PDU_DATA_MULTIPART_PART_CONTENT */
    PACE2_ADVANCED_MMSE_PDU_DATA_MULTIPART_PART_END,            /**< @ref IPD_EVENT_MMSE_PDU_DATA_MULTIPART_PART_END */
    PACE2_ADVANCED_MMSE_PDU_MESSAGE_END,                        /**< @ref IPD_EVENT_MMSE_PDU_MESSAGE_END */
    PACE2_ADVANCED_MMSE_END_CONNECTION,                         /**< @ref IPD_EVENT_MMSE_END_CONNECTION */
    PACE2_ADVANCED_MMSE_INVALID,                                /**< @ref IPD_EVENT_MMSE_INVALID */

    PACE2_NUMBER_OF_ADVANCED_MMSE_EVENT_TYPES       /**< Number of implemented event types. */
} PACE2_advanced_mmse_event_type;

/* Event Structures *************************************************************/

#ifndef PACE2_DISABLE_DECODER

/**
 * @brief Data structure for advanced MMSE events.
 */
typedef struct {
    /** Global event type, has to be @ref PACE2_ADVANCED_MMSE_EVENT for this structure. */
    PACE2_EVENT_COMMON_FIELDS;
    PACE2_advanced_mmse_event_type meta_data_type;           /**< MMSE event subtype. */
    PACE2_ADVANCED_META_DATA_EVENT_EXTRA_FIELDS;
    union {
        struct ipd_5tuple connection_5tupel;                                    /**< Contains data for a @ref PACE2_ADVANCED_MMSE_NEW_CONNECTION event. */
        struct ipd_mmse_message_type_struct message_type;                       /**< Contains data for a @ref PACE2_ADVANCED_MMSE_PDU_MESSAGE_TYPE event. */
        struct ipd_mmse_pdu_value headerline;                                   /**< Contains data for a @ref PACE2_ADVANCED_MMSE_PDU_HEADERLINE event. */
        struct ipd_mmse_header_end_struct header_end;                           /**< Contains data for a @ref PACE2_ADVANCED_MMSE_PDU_HEADER_END event. */
        struct ipd_mmse_multipart_start_struct multipart_start;                 /**< Contains data for a @ref PACE2_ADVANCED_MMSE_PDU_DATA_MULTIPART_START event. */
        struct ipd_mmse_multipart_content_type_struct multipart_content_type;   /**< Contains data for a @ref PACE2_ADVANCED_MMSE_PDU_DATA_MULTIPART_PART_CONTENT_TYPE event. */
        struct ipd_mmse_multipart_header_struct multipart_headerline;           /**< Contains data for a @ref PACE2_ADVANCED_MMSE_PDU_DATA_MULTIPART_PART_HEADERLINE event. */
        struct ipd_mmse_multipart_content_struct multipart_content;             /**< Contains data for a @ref PACE2_ADVANCED_MMSE_PDU_DATA_MULTIPART_PART_CONTENT event. */
        struct ipd_mmse_multipart_end_struct multipart_end;                     /**< Contains data for a @ref PACE2_ADVANCED_MMSE_PDU_DATA_MULTIPART_PART_END event. */
        struct ipd_mmse_message_end_struct message_end;                         /**< Contains data for a @ref PACE2_ADVANCED_MMSE_PDU_MESSAGE_END event. */
        const char *invalid;                                                    /**< Contains data for a @ref PACE2_ADVANCED_MMSE_INVALID event. */
    } event_data;                                                               /**< Named union which contains the data of the sub-event types. */
} PACE2_advanced_mmse_event;


#endif /* PACE2_DISABLE_DECODER */

#endif /* MMSE_EVENTS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
