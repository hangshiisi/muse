/* written by Ralf Hoffmann, ipoque GmbH
 * ralf.hoffmann@ipoque.com
 */

#ifndef __IPOQUE_API_INCLUDE_FILE__
#error CANNOT INCLUDE THIS .H FILE, INCLUDE IPQ_API.H
#endif

#ifndef IPQ_APPLICATIONS_H
#define IPQ_APPLICATIONS_H

#ifdef __cplusplus
extern "C" {
#endif

#define IPOQUE_APPLICATION_NOT_YET_DETECTED  	     0
#define IPOQUE_APPLICATION_NOT_DETECTED     	     1
#define IPOQUE_APPLICATION_FACEBOOK             	 2
#define IPOQUE_APPLICATION_MAGICJACK             	 3
#define IPOQUE_APPLICATION_ITUNES             	     4
#define IPOQUE_APPLICATION_MYSPACE               	 5
#define IPOQUE_APPLICATION_FACETIME             	 6
#define IPOQUE_APPLICATION_TRUPHONE             	 7
#define IPOQUE_APPLICATION_TWITTER                 	 8
#define IPOQUE_APPLICATION_WINDOWSMEDIA            	 9
#define IPOQUE_APPLICATION_XBOX                  	 10
#define IPOQUE_APPLICATION_REALMEDIA               	 11
#define IPOQUE_APPLICATION_GMAIL                 	 12
#define IPOQUE_APPLICATION_GOOBER                  	 13
#define IPOQUE_APPLICATION_BLACKBERRY             	 14
#define IPOQUE_APPLICATION_ICLOUD	             	 15
#define IPOQUE_APPLICATION_UBUNTUONE             	 16
#define IPOQUE_APPLICATION_DROPBOX	             	 17
#define IPOQUE_APPLICATION_GOOGLEDOCS             	 18
#define IPOQUE_APPLICATION_YUILOP             	     19
#define IPOQUE_APPLICATION_IMESSAGE             	 20
#define IPOQUE_APPLICATION_GOTOMYPC             	 21
#define IPOQUE_APPLICATION_GOTOMEETING             	 22
#define IPOQUE_APPLICATION_WINDOWS_AZURE             23
#define IPOQUE_APPLICATION_AMAZON_CLOUD              24
#define IPOQUE_APPLICATION_DAILYMOTION               25
#define IPOQUE_APPLICATION_DEEZER					 26
#define IPOQUE_APPLICATION_GROOVESHARK	             27
#define IPOQUE_APPLICATION_SUDAPHONE		         28
#define IPOQUE_APPLICATION_OFFICE365	             29
#define IPOQUE_APPLICATION_CNTV						 30
#define IPOQUE_APPLICATION_SINATV 		             31
#define IPOQUE_APPLICATION_YOUTUBE	             	 32
#define IPOQUE_APPLICATION_VOIP_SWITCH			   	 33
#define IPOQUE_APPLICATION_ZYNGA	             	 34
#define IPOQUE_APPLICATION_CRIMECITY	             35
#define IPOQUE_APPLICATION_MODERNWAR	             36
#define IPOQUE_APPLICATION_VIPPIE					 37
#define IPOQUE_APPLICATION_BOX						 38
#define IPOQUE_APPLICATION_SKYDRIVE					 39
#define IPOQUE_APPLICATION_ADOBE_CREATIVE_CLOUD		 40
#define IPOQUE_APPLICATION_LINKEDIN					 41
#define IPOQUE_APPLICATION_ORKUT					 42
#define IPOQUE_APPLICATION_HI5						 43
#define IPOQUE_APPLICATION_SORIBADA					 44
#define IPOQUE_APPLICATION_ZOHO_WORK_ONLINE			 45
#define IPOQUE_APPLICATION_HOTMAIL					 46
#define IPOQUE_APPLICATION_INSTAGRAM                 47
#define IPOQUE_APPLICATION_SUGARSYNC                 48
#define IPOQUE_APPLICATION_WICKR                     49
#define IPOQUE_APPLICATION_TIGERTEXT                 50
#define IPOQUE_APPLICATION_VIBE                      51
#define IPOQUE_APPLICATION_ENLEGION                  52
#define IPOQUE_APPLICATION_VOXER                     53
#define IPOQUE_APPLICATION_LOVEFILM					 54
#define IPOQUE_APPLICATION_FRIENDSTER                55
#define IPOQUE_APPLICATION_BURNER					 56
#define IPOQUE_APPLICATION_FLICKR                    57
#define IPOQUE_APPLICATION_LIVE_COM                  58
#define IPOQUE_APPLICATION_ICQ_WEBCHAT               59
#define IPOQUE_APPLICATION_REDTUBE                   60
#define IPOQUE_APPLICATION_EVERNOTE                  61
#define IPOQUE_APPLICATION_SPREED                 	 62
#define IPOQUE_APPLICATION_TEXTPLUS                  63
#define IPOQUE_APPLICATION_XVIDEOS                   64
#define IPOQUE_APPLICATION_SNAPCHAT                  65
#define IPOQUE_APPLICATION_YOUKU                     66
#define IPOQUE_APPLICATION_MYMUSIC_TW                67
#define IPOQUE_APPLICATION_RENREN                    68
#define IPOQUE_APPLICATION_YELP                      69
#define IPOQUE_APPLICATION_AMAZON_SHOP               70
#define IPOQUE_APPLICATION_YOUPORN                   71
#define IPOQUE_APPLICATION_EBAY                      72
#define IPOQUE_APPLICATION_PORNHUB                   73
#define IPOQUE_APPLICATION_SPIDEROAK                 74
#define IPOQUE_APPLICATION_ADRIVE                    75
#define IPOQUE_APPLICATION_TUMBLR                    76
#define IPOQUE_APPLICATION_XING                      77
#define IPOQUE_APPLICATION_GOOGLE_PLAY_MUSIC         78
#define IPOQUE_APPLICATION_VIMEO                     79
#define IPOQUE_APPLICATION_SALESFORCE                80
#define IPOQUE_APPLICATION_ITUNES_RADIO              81
#define IPOQUE_APPLICATION_SINA_WEIBO                82
#define IPOQUE_APPLICATION_FORFONE                   83
#define IPOQUE_APPLICATION_LIVEJASMIN                84
#define IPOQUE_APPLICATION_JINGDONG                  85
#define IPOQUE_APPLICATION_LASTFM                    86
#define IPOQUE_APPLICATION_IMS                       87
#define IPOQUE_APPLICATION_BAIDU                     88
#define IPOQUE_APPLICATION_TAOBAO                    89
#define IPOQUE_APPLICATION_WATCHEVER                 90
#define IPOQUE_APPLICATION_TTPOD                     91
#define IPOQUE_APPLICATION_360MOBILE                 92
#define IPOQUE_APPLICATION_PINTEREST                 93
#define IPOQUE_APPLICATION_VINE                      94
#define IPOQUE_APPLICATION_NET2PHONE                 95
#define IPOQUE_APPLICATION_FOURSQUARE                96
#define IPOQUE_APPLICATION_ILIVE_TO                  97
#define IPOQUE_APPLICATION_MEGA                      98
#define IPOQUE_APPLICATION_DOOOK                     99
#define IPOQUE_APPLICATION_VBULLETIN                 100
#define IPOQUE_APPLICATION_CLOUDME                   101
#define IPOQUE_APPLICATION_YIKYAK                    102
#define IPOQUE_APPLICATION_REDMINE                   103
#define IPOQUE_APPLICATION_IHEART_RADIO              104
#define IPOQUE_APPLICATION_AVIRA_ANTIVIRUS           105
#define IPOQUE_APPLICATION_NORTON_ANTIVIRUS          106
#define IPOQUE_APPLICATION_KASPERSKY_ANTIVIRUS       107
#define IPOQUE_APPLICATION_AVG_ANTIVIRUS             108
#define IPOQUE_APPLICATION_SOUNDCLOUD                109
#define IPOQUE_APPLICATION_RDIO                      110
#define IPOQUE_APPLICATION_AMAZON_PRIME_MUSIC        111
#define IPOQUE_APPLICATION_RUNKEEPER                 112
#define IPOQUE_APPLICATION_MYBOOK                    113
#define IPOQUE_APPLICATION_NIKEPLUS                  114
#define IPOQUE_APPLICATION_MAGV                      115
#define IPOQUE_APPLICATION_MAGV_KIDS                 116
#define IPOQUE_APPLICATION_DOTA_LEGEND               117
#define IPOQUE_APPLICATION_LETV                      118
#define IPOQUE_APPLICATION_MY_FITNESS_PAL            119
#define IPOQUE_APPLICATION_SOHU                      120
#define IPOQUE_APPLICATION_1KXUN                     121
#define IPOQUE_APPLICATION_TVBS                      122
#define IPOQUE_APPLICATION_XNXX                      123
#define IPOQUE_APPLICATION_CTITV                     124
#define IPOQUE_APPLICATION_ENDOMONDO                 125
#define IPOQUE_APPLICATION_TIMELY_TV                 126
#define IPOQUE_APPLICATION_WORKOUT_TRAINER           127
#define IPOQUE_APPLICATION_MAP_MY_RUN                128
#define IPOQUE_APPLICATION_KING_OF_PIRATES           129
#define IPOQUE_APPLICATION_TUDOU                     130
#define IPOQUE_APPLICATION_DUOKAN                    131
#define IPOQUE_APPLICATION_MEI_LU                    132
#define IPOQUE_APPLICATION_SKOUT                     133
#define IPOQUE_APPLICATION_PLAYTALES                 134
#define IPOQUE_APPLICATION_GAME_OF_WAR               135
#define IPOQUE_APPLICATION_FETNET                    136
#define IPOQUE_APPLICATION_FBS                       137
#define IPOQUE_APPLICATION_NATIONAL_BASEBALL         138
#define IPOQUE_APPLICATION_PINKFONG                  139
#define IPOQUE_APPLICATION_KOLLECT_BOOK              140
#define IPOQUE_APPLICATION_SPTG_TV                   141
#define IPOQUE_APPLICATION_CIAOMOBILE_HDTV           142
#define IPOQUE_APPLICATION_SKYKING                   143
#define IPOQUE_APPLICATION_MOVES                     144
#define IPOQUE_APPLICATION_PATH                      145
#define IPOQUE_APPLICATION_IWOW_SYSTEX               146
#define IPOQUE_APPLICATION_9KU                       147
#define IPOQUE_APPLICATION_NEXTTV                    148
#define IPOQUE_APPLICATION_SYNCPLICITY               149
#define IPOQUE_APPLICATION_REALMA                    150
#define IPOQUE_APPLICATION_YUANTA_WEB                151
#define IPOQUE_APPLICATION_HINET                     152
#define IPOQUE_APPLICATION_MYCARD                    153
#define IPOQUE_APPLICATION_KONO                      154
#define IPOQUE_APPLICATION_SPEAKABOOS                155
#define IPOQUE_APPLICATION_DUO_DUO                   156
#define IPOQUE_APPLICATION_WEALTH_GOD                157
#define IPOQUE_APPLICATION_ILEADER                   158
#define IPOQUE_APPLICATION_THREE_BAMBOO              159
#define IPOQUE_APPLICATION_TAAZE                     160
#define IPOQUE_APPLICATION_AUDIKO                    161
#define IPOQUE_APPLICATION_PUBU_BOOKBUFFET           162
#define IPOQUE_APPLICATION_MITAKE                    163
#define IPOQUE_APPLICATION_HYREAD                    164
#define IPOQUE_APPLICATION_DISNEY_STORYTIME          165
#define IPOQUE_APPLICATION_QUALYS                    166
#define IPOQUE_APPLICATION_CONSTANT_CONTACT          167
#define IPOQUE_APPLICATION_RALLY                     168
#define IPOQUE_APPLICATION_INTRALINKS                169
#define IPOQUE_APPLICATION_APPLE_MUSIC               170
#define IPOQUE_APPLICATION_NAVER                     171
#define IPOQUE_APPLICATION_BOOKING_COM               172
#define IPOQUE_APPLICATION_CNN                       173
#define IPOQUE_APPLICATION_PAYEASY                   174
#define IPOQUE_APPLICATION_LINE_RANGERS              175
#define IPOQUE_APPLICATION_IOS_APP_STORE             176
#define IPOQUE_APPLICATION_MYVIDEO_TW                177
#define IPOQUE_APPLICATION_KING_GAMING               178
#define IPOQUE_APPLICATION_CANDY_CRUSH               179
#define IPOQUE_APPLICATION_CANDY_CRUSH_SODA          180
#define IPOQUE_APPLICATION_BUBBLE_WITCH              181
#define IPOQUE_APPLICATION_FARM_HERO                 182
#define IPOQUE_APPLICATION_WINDOWS_STORE             183

#define IPOQUE_NUMBER_OF_APPLICATIONS                184

#define IPOQUE_APPLICATION_SHORT_STRING \
	"not_yet_detected",					\
		"not_detected",					\
		"facebook",						\
		"magicjack",					\
		"itunes",						\
		"myspace",						\
		"facetime",						\
		"truphone",						\
		"twitter",						\
		"windowsmedia",					\
		"xbox",							\
		"realmedia",					\
		"gmail",						\
		"goober",						\
		"blackberry",					\
		"icloud",						\
		"ubuntuone",					\
		"dropbox",						\
		"googledocs",					\
		"yuilop",						\
		"imessage",						\
		"gotomypc",						\
		"gotomeeting",					\
		"windows_azure",				\
		"amazon_cloud",					\
		"dailymotion",					\
		"deezer",						\
		"grooveshark",					\
		"sudaphone",					\
		"office365",					\
		"cntv",							\
		"sinatv",						\
		"youtube",						\
		"voipswitchvoiptunnel",			\
		"zynga",						\
		"crimecity",					\
		"modernwar",					\
		"vippie",						\
		"box",							\
		"skydrive",						\
        "adobe_creative_cloud",         \
        "linkedin",						\
        "orkut",						\
        "hi5",							\
		"soribada",						\
		"zoho_work_online",				\
		"hotmail_webmail",              \
		"instagram",                    \
		"sugarsync",                    \
		"wickr",                        \
		"tigertext",                    \
		"vibe",                         \
		"enlegion",                     \
		"voxer",						\
		"lovefilm",                     \
		"friendster",					\
		"burner",                       \
        "flickr",                       \
        "live_com",                     \
        "icq_webchat",                  \
        "redtube",                      \
        "evernote",						\
        "spreed",                       \
        "textplus",                     \
        "xvideos",						\
        "snapchat",                     \
        "youku",                        \
        "mymusic_tw",                   \
        "renren",						\
        "yelp",							\
        "amazon_shop",                  \
        "youporn",                      \
        "ebay",                         \
        "pornhub",                      \
        "spideroak",                    \
        "adrive",                       \
        "tumblr",                       \
        "xing",                         \
        "google_play_music",            \
        "vimeo",                        \
        "salesforce",					\
        "itunes_radio",					\
        "sina_weibo",					\
        "forfone",                      \
        "livejasmin",                   \
        "jingdong",                     \
        "lastfm",                       \
        "ims",                          \
        "baidu",                        \
        "taobao",                       \
        "watchever",                    \
        "ttpod",                        \
        "360mobile",                    \
        "pinterest",                    \
        "vine",                         \
        "net2phone",                    \
        "foursquare",                   \
        "ilive_to",                     \
        "mega",                         \
        "doook",                        \
        "vbulletin",                    \
        "cloudme",                      \
        "yikyak",                       \
        "redmine",                      \
        "iheartradio",                  \
        "avira-antivir",                \
        "norton-antivir",               \
        "kaspersky-antivir",            \
        "avg-antivir",                  \
        "soundcloud",                   \
        "rdio",                         \
        "amazon-prime-music",           \
        "runkeeper",                    \
        "mybook",                       \
        "nikeplus",                     \
        "magv",                         \
        "magv-kids",                    \
        "dota-legend",                  \
        "letv",                         \
        "my-fitness-pal",               \
        "sohu",                         \
        "1kxun",                        \
        "tvbs",                         \
        "xnxx",                         \
        "ctitv",                        \
        "endomondo",                    \
        "timely-tv",                    \
        "workout-trainer",              \
        "mapmyrun",                     \
        "king-of-pirates",              \
        "tudou",                        \
        "duokan",                       \
        "mei-lu",                       \
        "skout",                        \
        "playtales",                    \
        "gameofwar",                    \
        "fetnet",                       \
        "fbs",                          \
        "national-baseball",            \
        "pinkfong",                     \
        "kollect-book",                 \
        "sptg-tv",                      \
        "ciaomobile-hdtv",              \
        "skyking",                      \
        "moves",                        \
        "path",                         \
        "iwow-systex",                  \
        "9ku",                          \
        "nexttv",                       \
        "syncplicity",                  \
        "realma",                       \
        "yuanta-web",                   \
        "hinet",                        \
        "mycard",                       \
        "kono",                         \
        "speakaboos",                   \
        "duo-duo",                      \
        "wealth-god",                   \
        "ileader",                      \
        "three-bamboo",                 \
        "taaze",                        \
        "audiko",                       \
        "pubu-bookbuffet",              \
        "mitake",                       \
        "hyread",                       \
        "disney-storytime",             \
        "qualys",                       \
        "constant-contact",             \
        "rally",                        \
        "intralinks",                   \
        "apple-music",                  \
        "naver",                        \
        "booking-com",                  \
        "cnn",                          \
        "payeasy",                      \
        "line-rangers",                 \
        "ios-app-store",                \
        "myvideo-tw",                   \
        "king-gaming",                  \
        "candy-crush",                  \
        "candy-crush-soda",             \
        "bubble-witch",                 \
        "farm-hero",                    \
        "windows-store"

#define IPOQUE_APPLICATION_LONG_STRING  \
        "Not yet detected",             \
        "Not detected",                 \
        "Facebook",                     \
        "magicJack",                    \
        "iTunes",                       \
        "MySpace",                      \
        "FaceTime",                     \
        "Truphone",                     \
        "Twitter",                      \
        "WindowsMedia",                 \
        "XBOX gaming console",          \
        "RealMedia",                    \
        "GMail webmail",                \
        "Goober",                       \
        "Blackberry",                   \
        "iCloud",                       \
        "Ubuntu One",                   \
        "Dropbox",                      \
        "Google Docs",                  \
        "Yuilop",                       \
        "iMessage",                     \
        "GoToMyPC",                     \
        "GoToMeeting",                  \
        "Windows Azure",                \
        "Amazon Cloud",                 \
        "Dailymotion",                  \
        "Deezer",                       \
        "Grooveshark",                  \
        "SUDA Phone",                   \
        "Office 365",                   \
        "CNTV",                         \
        "SINATV",                       \
        "YouTube",                      \
        "VoipSwitch",                   \
        "Zynga",                        \
        "Crime City",                   \
        "Modern War",                   \
        "Vippie",                       \
        "Box",                          \
        "Skydrive",                     \
        "Adobe Creative Cloud",         \
        "LinkedIn",                     \
        "Orkut",                        \
        "hi5",                          \
        "Soribada",                     \
        "Zoho Work Online",             \
        "Hotmail",                      \
        "Instagram",                    \
        "SugarSync",                    \
        "Wickr",                        \
        "TigerText",                    \
        "Vibe",                         \
        "enLegion",                     \
        "Voxer",                        \
        "LOVEFiLM",                     \
        "Friendster",                   \
        "Burner",                       \
        "Flickr",                       \
        "live.com",                     \
        "ICQ Webchat",                  \
        "RedTube",                      \
        "Evernote",                     \
        "Spreed",                       \
        "textPlus",                     \
        "Xvideos",                      \
        "Snapchat",                     \
        "Youku",                        \
        "MyMusic",                      \
        "Renren",                       \
        "Yelp",                         \
        "Amazon shopping",              \
        "YouPorn",                      \
        "eBay",                         \
        "PornHub",                      \
        "Spideroak",                    \
        "Adrive",                       \
        "tumblr",                       \
        "XING",                         \
        "Google Play Music",            \
        "Vimeo",                        \
        "Salesforce",                   \
        "iTunes Radio",                 \
        "Sina Weibo",                   \
        "Forfone",                      \
        "LiveJasmin",                   \
        "Jingdong",                     \
        "Last.fm",                      \
        "IP Multimedia Subsystem",      \
        "Baidu",                        \
        "Taobao",                       \
        "Watchever",                    \
        "TTPod",                        \
        "360 Mobile Security",          \
        "Pinterest",                    \
        "Vine",                         \
        "Net2Phone",                    \
        "Foursquare",                   \
        "iLive.to",                     \
        "MEGA",                         \
        "Doook",                        \
        "vBulletin",                    \
        "CloudMe",                      \
        "Yik Yak",                      \
        "Redmine",                      \
        "iHeartRadio",                  \
        "Avira Antivirus",              \
        "Norton Antivirus",             \
        "Kaspersky Antivirus",          \
        "AVG Antivirus",                \
        "SoundCloud",                   \
        "Rdio",                         \
        "Amazon Prime Music",           \
        "RunKeeper",                    \
        "myBook",                       \
        "Nike Plus",                    \
        "MagV",                         \
        "MagV Kids",                    \
        "Dota Legend",                  \
        "LeTV",                         \
        "MyFitnessPal",                 \
        "Sohu",                         \
        "1kxun",                        \
        "TVBS",                         \
        "XNXX",                         \
        "CtiTV",                        \
        "Endomondo",                    \
        "Timely TV",                    \
        "Workout Trainer",              \
        "MapMyRun",                     \
        "King of Pirates",              \
        "Tudou",                        \
        "Duokan",                       \
        "Mei Lu",                       \
        "Skout",                        \
        "PlayTales",                    \
        "Game of War",                  \
        "FETnet",                       \
        "Fubon E-Broker",               \
        "National Baseball",            \
        "PinkFong",                     \
        "Kollect Book",                 \
        "SPTG TV",                      \
        "Ciaomobile HDTV",              \
        "Skyking",                      \
        "Moves",                        \
        "Path",                         \
        "iWow systex",                  \
        "9ku",                          \
        "Next TV",                      \
        "Syncplicity",                  \
        "RealMa",                       \
        "Yuanta Web",                   \
        "HiNet",                        \
        "MyCard",                       \
        "Kono",                         \
        "Speakaboos",                   \
        "Duo Duo",                      \
        "Wealth God",                   \
        "iLeader",                      \
        "Three Bamboo",                 \
        "Taaze",                        \
        "Audiko",                       \
        "pubu bookbuffet",              \
        "Mitake",                       \
        "HyRead",                       \
        "Disney Storytime",             \
        "Qualys",                       \
        "Constant Contact",             \
        "Rally",                        \
        "IntraLinks",                   \
        "Apple Music",                  \
        "Naver",                        \
        "Booking_com",                  \
        "CNN",                          \
        "PayEasy",                      \
        "LINE Rangers",                 \
        "iOS App Store",                \
        "MyVideo TW",                   \
        "King gaming",                  \
        "Candy Crush",                  \
        "Candy Crush Soda",             \
        "Bubble Witch",                 \
        "Farm Hero",                    \
        "Windows Store"

#ifdef __cplusplus
}
#endif

#endif /* IPQ_APPLICATIONS_H */
