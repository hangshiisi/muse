#ifndef __IPQ_METADATA_PUBLIC_H__
#define __IPQ_METADATA_PUBLIC_H__

#ifndef __IPOQUE_API_INCLUDE_FILE__
#error CANNOT INCLUDE THIS .H FILE, INCLUDE IPQ_API.H
#endif


enum dissector_metadata_type {
    DISSECTOR_IP = 0,               /* Dissector for IP metadata */
    DISSECTOR_TCP,                  /* Dissector for TCP metadata */
    DISSECTOR_H264,                 /* Dissector for H264 metadata */
    DISSECTOR_AMR,                  /* Dissector for AMR metadata */
    DISSECTOR_RTP,                  /* Dissector for RTP metadata */
    DISSECTOR_ID3,                  /* Dissector for ID3 metadata */
    DISSECTOR_MP3,                  /* Dissector for MP3 metadata */
    DISSECTOR_HTTP,                 /* Dissector for HTTP metadata */
    DISSECTOR_MP4,                  /* Dissector for MP4 metadata */
#ifdef IPOQUE_ENABLE_MOS_CUST
    DISSECTOR_MOS_CUST,             /* Dissector for MOS metadata */
#endif

    METADATA_DISSECTOR_COUNT
};

enum metadata_status {
    METADATA_DISSECTOR_SUCCESS = 0,
    METADATA_DISSECTOR_MEMORY_ALLOCATION_FAILED,
    METADATA_DISSECTOR_INVALID_ARGUMENTS,
    METADATA_DISSECTOR_NO_DATA,
    METADATA_DISSECTOR_NOT_ENABLED,
    METADATA_DISSECTOR_MISSING_DEPENDENCY,
    METADATA_DISSECTOR_FAILURE
};

#define CODEC_LIST(M) M(UNKNOWN, UNKNOWN) \
                      M(H263,    VIDEO)   \
                      M(H264,    VIDEO)   \
                      M(AMR,     AUDIO)   \
                      M(PCMU,    AUDIO)   \
                      M(GSM,     AUDIO)   \
                      M(G723,    AUDIO)   \
                      M(DVI4,    AUDIO)   \
                      M(LPC,     AUDIO)   \
                      M(PCMA,    AUDIO)   \
                      M(G722,    AUDIO)   \
                      M(L16,     AUDIO)   \
                      M(QCELP,   AUDIO)   \
                      M(CN,      AUDIO)   \
                      M(MPA,     AUDIO)   \
                      M(G728,    AUDIO)   \
                      M(G729,    AUDIO)   \
                      M(CELB,    VIDEO)   \
                      M(H261,    VIDEO)   \
                      M(MPV,     VIDEO)   \
                      M(JPEG,    VIDEO)   \
                      M(NV,      VIDEO)   \
                      M(AMR_WB,  AUDIO)   \
                      M(AAC,     AUDIO)   \
                      M(MP3,     AUDIO)   \
                      M(MP4,     AUDIO)

#define STREAM_TYPE_LIST(M) M(UNKNOWN)              \
                            M(AUDIO)                \
                            M(VIDEO)                \
                            M(AUDIO_VIDEO)

#define LIST_TO_STREAM_TYPE_ENUM(NAME) STREAM_TYPE_ ## NAME,
#define LIST_TO_CODEC_ENUM(NAME, ...) CODEC_ ## NAME,
#define LIST_TO_STR(NAME, ...) #NAME,

enum stream_media_type {
    STREAM_TYPE_LIST(LIST_TO_STREAM_TYPE_ENUM)

    NUMBER_OF_STREAM_TYPES
};

enum codec_type {
    CODEC_LIST(LIST_TO_CODEC_ENUM)

    NUMBER_OF_CODECS
};

struct metadata_string {
    u8 const * ptr;
    u16 len;
};

union dissector_result {
    struct {
        struct {
            u16 min;                /* Minimum packet size per flow */
            u16 max;                /* Maximum packet size per flow */
            u16 avg;                /* Average packet size per flow */
        } packet_size[2];

        u32 invalid_checksums[2];   /* Total count of invalid IP checksum per flow and direction */

        struct {
            u64 min;                /* Minimum throughput in Bytes/s per flow */
            u64 max;                /* Maximum throughput in Bytes/s per flow */
            u64 avg;                /* Average throughput in Bytes/s per flow */
        } throughput[2];

        u64 throughput_interval[2]; /* Throughput in Bytes/s
                                       The interval is the time between one get_metadata_ip()
                                       function call and the next one.
                                     */
        u32 interval_duration[2];   /* Interval duration of throughput_interval in s*/

        u64 packets[2];             /* Number of packets per direction */
        u64 bytes[2];               /* Bytes per direction */
    } ip;

    struct {

        u32 ooo_packets;            /* Total count of out-of-order packets per flow */
        u32 retransmissions;        /* Total count of retransmitted packets per flow */
        u32 invalid_checksums[2];   /* Total count of packets with an invalid TCP checksum per flow and direction */

        struct {
            u16 min;                /* Minimum TCP window size per flow and direction */
            u16 max;                /* Maximum TCP window size per flow and direction */
            u16 avg;                /* Average TCP window size per flow and direction */
            u16 cur;                /* Current TCP window size of the packet */
        } window_size[2];

        struct {
            u8 value:4;             /* Current window scale value per flow and direction */
        } window_scale[2];

        struct {
            u16 min;                /* Minimum RTT per flow and direction */
            u16 max;                /* Maximum RTT per flow and direction */
            u16 avg;                /* Average RTT per flow and direction */
            u16 cur;                /* Current RTT of the packet */
        } round_trip_time;

        u64 network_limit;          /* Theoretical throughput of this flow without considering the TCP window, given in Bytes/s */
        u64 throughput_max[2];      /* Maximum possible TCP throughput, given in Bytes/s */

        u16 max_segment_size;       /* Maximum segment size */
    } tcp;


    struct {
        struct {
            u8 numerator;
            u8 divisor;
        } aspect_ratio[2];                      /* aspect ratio, i.e 4:3 */

        u32 bitrate[2];                         /* bitrate in bits per second */
        u32 frame_count[2];                     /* total number of frames */
        u32 iframe_count[2];                    /* number of i-frames */
        u16 picture_width[2];                   /* picture width in pixels */
        u16 picture_height[2];                  /* picture height in pixels */
        u8 frame_rate[2];                       /* frame rate in frames per second */
        u8 avg_frame_rate[2];                   /* average frame rate in frames per second */
    } h264;

    struct {
        const char *codec_str[2];               /* detected codec as string */
        const char *stream_type_str[2];         /* detected stream type as string */
        enum codec_type codec[2];               /* detected codec as enum value */
        enum stream_media_type stream_type[2];  /* detected stream type as enum value */
    } rtp;

    struct {
        u32 bitrate[2];                         /* bitrate in bits per second */
        u8 dtx_silence_active[2];               /* whether dtx silence is currently active or not */
    } amr;

    struct {
        struct {
            struct metadata_string talb;       /* Album/Movie/Show title */
            struct metadata_string tpe1;       /* Lead performer(s)/Soloist(s) */
            struct metadata_string tpe2;       /* Band/orchestra/accompaniment */
            struct metadata_string tpe3;       /* Conductor/performer refinement */
            struct metadata_string tpe4;       /* Interpreted, remixed, or otherwise modified by */
            struct metadata_string trck;       /* Track number/Position in set */
            struct metadata_string tit1;       /* Content group description */
            struct metadata_string tit2;       /* Title/songname/content description */
            struct metadata_string tit3;       /* Subtitle/Description refinement */
            struct metadata_string tcon;       /* Content type */
        } frames;
        u8 version;                         /* ID3v2 version */
    } id3;

    struct {
        const char * codec_str[2];             /* detected codec as string */
        enum codec_type codec[2];              /* detected codec as enum value */
        struct {
            u32 bitrate;                       /* bitrate in bits per second */
            u16 sampling_rate;                 /* Sampling rate frequency index */
            u8 channel_mode:2;                 /* Channel mode */
            u8 version:2;                      /* MPEG Audio version ID */
            u8 copyright:1;                    /* Copyright*/
            u8 original:1;                     /* Original media */
        } audio[2];

    } mp3;

    struct {
        struct {
            enum pace_http_content_type type;   /* the container format which could be identified */
            char const * type_str;              /* detected type as string */
            u8 done;                            /* tracks the status of the http dissector - 0: still ongoing; 1: done */
        } content;
    } http;

    struct {

        struct {
            const char *codec_str;              /* detected codec as string */
            enum codec_type codec;              /* detected codec as enum value */
            u32 bitrate;                        /* bitrate of the video stream */
            u16 width;                          /* width of the video in pixels */
            u16 height;                         /* width of the video in pixels */
            u16 color_depth;                    /* color depth of the video in bit */
            struct {
                u8 numerator;
                u8 divisor;
            } aspect;                           /* aspect ratio, i.e 4:3 */
            u8 fps;                             /* calculated frames per second */
        } video[2];

        struct {
            const char *codec_str;              /* detected codec as string */
            enum codec_type codec;              /* detected codec as enum value */
            u32 sampling_rate;                  /* sampling rate of the audio stream */
            u32 bitrate;                        /* bitrate of the audio stream in bits per second */
            u16 channels;                       /* number of audio channels */
        } audio[2];

        u64 duration[2];                        /* the current duration of the stream in seconds */
        const char *stream_type_str[2];         /* detected stream type as string */
        enum stream_media_type type[2];         /* detected stream type as enum value */
    } mp4;

#ifdef IPOQUE_ENABLE_MOS_CUST
    struct {
        u8 type[2];                                /* the MOS type: 0: nothing, 1: rtp, 2: buffered */
        union {
            struct {
                u8 jitter;                         /* Jitter based MOS value */
                u8 codec;                          /* Codec based MOS value */
                u8 packetloss;                     /* Packetloss based MOS value */
                u8 overall;                        /* Overall MOS value based on all influences */
            } rtp;

            struct {
                u8 buffer;                         /* Buffer MOS value */
                u8 codec;                          /* Codec based MOS value */
                u8 overall;                        /* Overall MOS value based on all influences */
            } buffered;
        } values[2];
    } mos_cust;
#endif
};

struct dissector_config {
    struct {
        u8 enabled;
    } ip;

    struct {
        u8 enabled;
    } tcp;

    struct {
        u8 enabled;
    } h264;

    struct {
        u8 enabled;
    } amr;

    struct {
        u8 enabled;
    } rtp;

    struct {
        u8 enabled;
    } id3;

    struct {
        u8 enabled;
    } mp3;

    struct {
        u8 enabled;
    } http;

    struct {
        u8 enabled;
    } mp4;

#ifdef IPOQUE_ENABLE_MOS_CUST
    struct {
        u8 enabled;
    } mos_cust;
#endif
};


#endif
