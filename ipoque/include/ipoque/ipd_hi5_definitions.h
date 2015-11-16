/********************************************************************************/
/**
 ** \file       ipd_hi5_definitions.h
 ** \brief      Structures and enumerations for all events of the social network
 **             HI5.
 **/
/********************************************************************************/

#ifndef __IPOQUE_DECODER_HI5_INCLUDE_FILE__
#define __IPOQUE_DECODER_HI5_INCLUDE_FILE__

#ifndef __IPOQUE_DECODER_INCLUDE_FILE__
#error please include ipd.h instead of this file
#endif


/**
 * Structure describing the generic hi5 event.
 */
struct ipd_hi5_generic {
    /** The correlating http transfer id **/
    u64 http_transaction_id;
    /** The correlating http session id **/
    u64 http_session_id;
    /** The main user of this hi5 session. **/
    struct ipd_hi5_user *user;
};

/**
 * Structure describing a hi5 user.\n
 *
 * Only the ID of the hi5 user is always provided. Full name is only provided if available.\n
 */
struct ipd_hi5_user {
    /** The hi5 ID of the user. **/
    u64 id;
    /** The full name of the hi5 user. **/
    struct ipd_charset_string name;     /* only if the value given */
    /** The url of user's profile photo. Only used in the IPD_EVENT_HI5_VIEW_FRIENDS event. **/
    struct ipd_charset_string profile_photo_url; /* only if the value given */
    /** The url of the users profile. **/
    struct ipd_charset_string profile_url; /* only if the value given */
};

/** Structure of a status update event **/
struct ipd_hi5_status_update {
    /** The generic hi5 event description **/
    struct ipd_hi5_generic generic;
    /** text of the status update message **/
    struct ipd_charset_string status_message;
};

/** Structure of update entry comments **/
struct ipd_hi5_recent_update_entry_comment {
    /** the author of the comment **/
    struct ipd_hi5_user author;
    /** the comment text **/
    struct ipd_charset_string comment;
};

/** Structure for an entry for the recent update list **/
struct ipd_hi5_recent_update_entry {
    /** the author of the update **/
    struct ipd_hi5_user author;
    /** the type of the update as used by hi5 internally **/
    struct ipd_charset_string type;
    /** the text associated with the update, only if the value is given **/
    struct ipd_charset_string content;
    /** the list length of updates **/
    u32 comment_list_length;
    /** the list of comments **/
    struct ipd_hi5_recent_update_entry_comment *comment_list;
    /** the photo count that belongs to the update **/
    u32 photo_list_length;
    /** the photo urls of the update **/
    struct ipd_charset_string *photo_list;
};

/** Structure of the recent updates messages **/
struct ipd_hi5_recent_updates {
    /** The generic hi5 event description **/
    struct ipd_hi5_generic generic;
    /** Owner of the profile **/
    struct ipd_hi5_user owner;
    /** An array that contains the updates **/
    struct ipd_hi5_recent_update_entry *update_list;
    /** The number of entries in the update message list **/
    u32 update_array_length;
};

/** Structure of the visit profile event **/
struct ipd_hi5_visit_profile {
    /** The generic hi5 event description **/
    struct ipd_hi5_generic generic;
    /** Owner of the profile **/
    struct ipd_hi5_user owner;
    /** The url of the visited profile **/
    struct ipd_charset_string profile_url;
    /** Sex of the profile owner **/
    struct ipd_charset_string sex;  /* only if available */
    /** The age of the profile owner **/
    struct ipd_charset_string age;  /* only if available */
    /** The Birthday of the profile owner **/
    struct ipd_charset_string birthday;  /* only if available */
    /** The location resp. the country **/
    struct ipd_charset_string location;  /* only if available */
    /** The name of the city **/
    struct ipd_charset_string city;  /* only if available */
    /** The url of profile owners's profile photo **/
    struct ipd_charset_string profile_photo_url;  /* only if available */
};

/** Structure of a hi5 comment **/
struct ipd_hi5_comment {
    /** The generic hi5 event description **/
    struct ipd_hi5_generic generic;
    /** Owner of the profile **/
    struct ipd_hi5_user profile_owner;
        /** Text of the comment **/
    struct ipd_charset_string comment;
};

/** Structure of a friend search event if the friend was searched by his name **/
struct ipd_hi5_friend_search {
    /** The generic hi5 event description **/
    struct ipd_hi5_generic generic;
    /** The name of the friend **/
    struct ipd_charset_string search_text;
};

/** Structure of a friend search event if the friend was searched by his name. Obsolete since 05.2012. **/
struct ipd_hi5_friend_search_by_name {
    /** The generic hi5 event description **/
    struct ipd_hi5_generic generic;
    /** The name of the friend **/
    struct ipd_charset_string name;
};

/** Structure of a friend search event if the friends was searched by their email addresses. Obsolete since 05.2012. **/
struct ipd_hi5_friend_search_by_email {
    /** The generic hi5 event description **/
    struct ipd_hi5_generic generic;
    /** An array the contains all email addresses **/
    struct ipd_charset_string *email_list;
    /** The number of elements in the email list **/
    u32 email_array_length;
};

/** Enumeration of answers that are possible for friendship requests **/
enum ipd_hi5_friendship_request_answer {
    /** Accept the friendship request **/
    IPD_HI5_FRIENDSHIP_REQUEST_ANSWER_ACCEPT,
    /** Reject the request for friendship **/
    IPD_HI5_FRIENDSHIP_REQUEST_ANSWER_REJECT,
};

/** Enumeration of friendship request types **/
enum ipd_hi5_friendship_request_type {
    /** Accept the friendship request **/
    IPD_HI5_FRIENDSHIP_REQUEST_TYPE_REQUEST,
    /** Reject the request for friendship **/
    IPD_HI5_FRIENDSHIP_REQUEST_TYPE_RESPONSE,
};


/** Structure of a hi5 friendship request **/
struct ipd_hi5_friendship_request {
    /** The generic hi5 event description **/
    struct ipd_hi5_generic generic;
    /** The type of friendship request **/
    enum ipd_hi5_friendship_request_type type;
    /** The id of the new friend **/
    u64 friend_id;
    /** The answer to the friendship request. The request can be accepted or rejected.
        It is only available if type is IPD_HI5_FRIENDSHIP_REQUEST_RESPONSE **/
    enum ipd_hi5_friendship_request_answer answer;
};

/** Structure of an event to remove a friend from the list of friends **/
struct ipd_hi5_friend_remove {
    /** The generic hi5 event description **/
    struct ipd_hi5_generic generic;
    /** The id of the friend to remove **/
    u64 friend_id;
};

/** Structure of the list of friends that can be seen if the user browse any friend list **/
struct ipd_hi5_view_friends {
    /** The generic hi5 event description **/
    struct ipd_hi5_generic generic;
    /** Owner of the profile **/
    struct ipd_hi5_user owner;
    /** An array containing all users that will be shown **/
    struct ipd_hi5_user *friend_list;
    /** The number of entries in the list of friends **/
    u32 friend_array_length;
};

/** Structure of a hi5 message thread between two users **/
struct ipd_hi5_message_thread {
    /** The generic hi5 event description. **/
    struct ipd_hi5_generic generic;
    /** An array containing the messages in the thread as shown to the user. **/
    struct ipd_hi5_message *message_list;
    /** The number of elements in the message list **/
    u32 message_array_length;
};

/** Structure of a hi5 message **/
struct ipd_hi5_message {
    /** The generic hi5 event description. \n
     It is not used if the message is part of a message list of a ipd_hi5_mailbox structure. **/
    struct ipd_hi5_generic generic;
    /** The sender of the message **/
    struct ipd_hi5_user sender;
    /** The subject of the message **/
    struct ipd_charset_string subject;      /* only if the value given */
    /** An array of all recipients of the message **/
    struct ipd_hi5_user* recipients;
    /** The number of elements in the recipients list **/
    u32 recipients_array_length;
    /** The date of the message as shown to the user **/
    struct ipd_charset_string date;
    /** the timestamp as submitted with the data **/
    u64 timestamp;
    /** the message_id as submitted with the data. Obsolete since 05.2012 **/
    u64 message_id;
    /** The text of the message. It is only provided if available. **/
    struct ipd_charset_string text;
};

/** Enumeration of the mailbox types **/
enum ipd_hi5_mailbox_type {
    IPD_HI5_MAILBOX_TYPE_INBOX,
    IPD_HI5_MAILBOX_TYPE_BULK,
    IPD_HI5_MAILBOX_TYPE_SENT,
};

/** Structure of a hi5 mailbox **/
struct ipd_hi5_mailbox {
    /** The generic hi5 event description **/
    struct ipd_hi5_generic generic;
    /** The type of mailbox **/
    enum ipd_hi5_mailbox_type type;
    /** An array containing the messages in the mailbox as shown to the user. \n
    It is only provided if available. **/
    struct ipd_hi5_message *message_list;
    /** The number of elements in the message list **/
    u32 message_array_length;
};

/** Structure of a group create event **/
struct ipd_hi5_group_create {
    /** The generic hi5 event description **/
    struct ipd_hi5_generic generic;
    /** The name of the new group **/
    struct ipd_charset_string group_name;
    /** The id of the chosen category **/
    u32 category_id;
    /** The text to describe the topic of the new group **/
    struct ipd_charset_string short_description;        /* only if the value given */
    /** The text to describe the topic of the new group that can contain HTML-tags, obsolete **/
    struct ipd_charset_string html_description;     /* only if the value given */
    /** A shortcut of the language e.g. 'de', 'en', 'it' etc **/
    struct ipd_charset_string language;
    /** The id of the country **/
    long long int country;
    /** The name of the city **/
    struct ipd_charset_string city;     /* only if the value given */
    /** The access policy of the group, obsolete **/
    u32 access_policy;
    /** Notify abuse report: 0 no, 1 yes - obsolete **/
    u8 notify_abuse_report;
    /** Notify join requests: 0 no, 1 yes - obsolete **/
    u8 notify_join_request;
    /** The access policy like setting to make the group private: 1 = group is private, 0 = group is public **/
    u8 is_private;
};

/** Structure of a group joint event **/
struct ipd_hi5_group_join {
    /** The generic hi5 event description **/
    struct ipd_hi5_generic generic;
    /** The id of the group to join **/
    u64 group_id;
};

/** Structure of a group leave event **/
struct ipd_hi5_group_leave {
    /** The generic hi5 event description **/
    struct ipd_hi5_generic generic;
    /** The id of the group to leave **/
    u64 group_id;
};

/** Structure of a group visit event **/
struct ipd_hi5_group_visit {
    /** The generic hi5 event description **/
    struct ipd_hi5_generic generic;
    /** The id of the group **/
    u64 group_id;
    /** The name of the group **/
    struct ipd_charset_string group_name;
};

/** Structure of a message for a thread of a group **/
struct ipd_hi5_thread {
    /** The generic hi5 event description. Not used if this structure is part of ipd_hi5_thread_list. **/
    struct ipd_hi5_generic generic;
    /** The id of the thread **/
    u64 thread_id;
    /** The id of the group **/
    u64 group_id;
    /** The subject/title of the message **/
    struct ipd_charset_string subject;      /* only if the value given */
    /** The text of the message **/
    struct ipd_charset_string message;      /* only if the value given */
};

/** Structure of a list of thread messages **/
struct ipd_hi5_thread_list {
    /** The generic hi5 event description **/
    struct ipd_hi5_generic generic;
    /** An array of threads that is shown to the user if he/she visit a group **/
    struct ipd_hi5_thread* thread_list;
    /** The number of elements in the thread list **/
    u32 thread_array_length;
};

struct ipd_hi5_logon {
    /** The generic hi5 event description **/
    struct ipd_hi5_generic generic;
    /** email address of the user, obsolete **/
    struct ipd_charset_string email_address;
    /** logon password, obsolete **/
    struct ipd_charset_string password;
};

/**
 * Enumeration for simple hi5 events. This is passed as \c type to the \ref ipd_decoder_event_callback.
 */
enum ipd_event_hi5_enum
{
        /** Signals the login of a user on Hi5 website. Provides a struct ipd_hi5_logon with 
     information about the user. */
    IPD_EVENT_HI5_LOGON,
    
        /** Signals the logout of a user. Provides a struct ipd_hi5_generic with information 
     about the user. **/
    IPD_EVENT_HI5_LOGOFF,
    
    /** Signals that the user updated its status. Provides a ipd_hi5_status_update structure with
     the update message. **/
    IPD_EVENT_HI5_STATUS_UPDATE,

    /** Provides a struct ipd_hi5_recent_updates that contain recent updates of a user. **/
    IPD_EVENT_HI5_RECENT_UPDATES,
    
    /** Signals the comment of an update. Provides a ipd_hi5_comment structure that provides
    the update message. This is obsolete since 05.2012.**/
    IPD_EVENT_HI5_COMMENT_UPDATE,
    
    /** Signals the comment of an user profile. Provides a ipd_hi5_comment structure that provides
    the comment message. **/
    IPD_EVENT_HI5_COMMENT_PROFILE,
    
    /** Signals the comment of a status message. Provides a ipd_hi5_comment structure that provides
    the comment message. **/
    IPD_EVENT_HI5_COMMENT_STATUS,
    
    /** Signals that a user search for a friend by its name. Provides a ipd_hi5_friend_search_by_name
    structure wiht the name of the friend. This is obsolete since 05.2012. **/
    IPD_EVENT_HI5_FRIEND_SEARCH_BY_NAME,
    
    /** Signals that a user search for friends by their email addresses. Provides a
     ipd_hi5_friend_search_by_email structure with a list of email addresses.  This is obsolete since 05.2012. **/
    IPD_EVENT_HI5_FRIEND_SEARCH_BY_EMAIL,
    
    /** Signals that a user search for a friend. Provides a ipd_hi5_friend_search
    structure wiht the search phrase **/
    IPD_EVENT_HI5_FRIEND_SEARCH,

    /** Signals a friendship request. Provides a ipd_hi5_friendship_request structure with
    the id of the friend and the decision of the user (accept/reject). **/
    IPD_EVENT_HI5_FRIENDSHIP_REQUEST,
    
    /** Signals that a user removed a friend of his/her list of friends. Provides a ipd_hi5_friend_remove
    structure with the id of the friend to remove. **/
    IPD_EVENT_HI5_FRIEND_REMOVE,
    
    /** Provides a ipd_hi5_view_friends structure that provide a list of user's friends
    as shown to the user. **/
    IPD_EVENT_HI5_VIEW_FRIENDS,
    
    /** Provides a ipd_hi5_mailbox structure with information about a mailbox of a user and contains
    a list of messages stored in the mailbox. **/
    IPD_EVENT_HI5_MAILBOX,

    /** Signals that the user send a mail. Provides a ipd_hi5_message structure with information
    about the message. **/
    IPD_EVENT_HI5_MAIL_SEND,

    /** Provides a ipd_hi5_message structure with information and content of the message which
    is viewed by the user. Obsolete. **/
    IPD_EVENT_HI5_MAIL_VIEW,

    /** Provides a ipd_hi5_message structure with information and content of the message which
    is received by the user in a chat.**/
    IPD_EVENT_HI5_MAIL_RECEIVE,

    /** Provides a ipd_hi5_message_thread structure with the messages which are viewed by the user. **/
    IPD_EVENT_HI5_MAILTHREAD_VIEW,

    /** Signals that the user has created a new group. Provides a ipd_hi5_group_create with
    information about the new group. **/
    IPD_EVENT_HI5_GROUP_CREATE,

    /** Signals that a user joined a group. Provides a ipd_hi5_group_join structure with the
    id of the group. **/
    IPD_EVENT_HI5_GROUP_JOIN,

    /** Signals that a user leaved a group. Provides a ipd_hi5_group_leave structure with the
    id of the group. **/
    IPD_EVENT_HI5_GROUP_LEAVE,

    /** Signals that the user add a new thread/topic to a group. Provides a ipd_hi5_thread
    structure with information about the new thread/topic. **/
    IPD_EVENT_HI5_GROUP_ADD_TOPIC,

    /** Signals that a user add a message to a thread/topic of a group. Provides a ipd_hi5_thread
    structure with information of the thread and the content of the message. **/
    IPD_EVENT_HI5_GROUP_ADD_MESSAGE,

    /** Provides a ipd_hi5_thread_list structure which contains a list of threads/topics of
    a group. **/
    IPD_EVENT_HI5_GROUP_LIST_THREADS,
    
        /** Signals that a user visit a profile, its own or another. Provides a ipd_hi5_visit_profile
     structure with information about the user and the visited profile. **/
    IPD_EVENT_HI5_VISIT_PROFILE,
    
        /** Signals that a user visit a group. Provides a ipd_hi5_group_visit structure with information
     about the user and the group. **/
    IPD_EVENT_HI5_GROUP_VISIT,

    IPD_NUMBER_OF_HI5_EVENTS,
};

#endif     /* __IPOQUE_DECODER_HI5_INCLUDE_FILE__ */
