/********************************************************************************/
/**
 ** \file       common_event_defs.h
 ** \brief      Common event structure field definitions.
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef COMMON_EVENT_DEFS_H
#define COMMON_EVENT_DEFS_H

/* Public Macros ****************************************************************/

/** Macro for the common structure fields of all events. */
#define PACE2_EVENT_COMMON_FIELDS \
    int type; \
    /** pointer to user data for the flow this event belongs to */ \
    void *flow_user_data

/** Macro for extra structure fields of a class event. */
#define PACE2_CLASS_META_DATA_EVENT_EXTRA_FIELDS PACE2_timestamp timestamp; /*!< Timestamp of the packet leading to this event. */      \
                                                 /** ID of the packet leading to this event. */     \
                                                 u64 external_packet_id

/** Macro for extra structure fields of a advanced event. */
#define PACE2_ADVANCED_META_DATA_EVENT_EXTRA_FIELDS PACE2_timestamp timestamp;  /*!< Timestamp of the packet leading to this event. */  \
                                                    /** ID of the packet leading to this event. */  \
                                                    u64 external_packet_id;                         \
                                                    /** ID of the flow of this event. */            \
                                                    u64 flow_id

#endif /* COMMON_EVENT_DEFS_H */
