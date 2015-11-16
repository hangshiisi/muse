/********************************************************************************/
/**
 ** \file       pace2_applications.h
 ** \brief      PACE 2 application definitions
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef PACE2_APPLICATIONS_H
#define PACE2_APPLICATIONS_H

/* Includes *********************************************************************/
#include "pace2_basic_def.h"

/* Public Types *****************************************************************/

/**
 * @brief Enum defining all available applications.
**/

typedef enum pace2_applications {
    PACE2_APPLICATION_UNKNOWN = 0,
    PACE2_APPLICATION_FACEBOOK,
    PACE2_APPLICATION_MAGICJACK,
    PACE2_APPLICATION_ITUNES,
    PACE2_APPLICATION_MYSPACE,
    PACE2_APPLICATION_FACETIME,
    PACE2_APPLICATION_TRUPHONE,
    PACE2_APPLICATION_TWITTER,
    PACE2_APPLICATION_XBOX,
    PACE2_APPLICATION_REALMEDIA,
    PACE2_APPLICATION_GOOGLE_MAIL,
    PACE2_APPLICATION_GOOBER,
    PACE2_APPLICATION_ICLOUD,
    PACE2_APPLICATION_UBUNTUONE,
    PACE2_APPLICATION_DROPBOX,
    PACE2_APPLICATION_YUILOP,
    PACE2_APPLICATION_IMESSAGE,
    PACE2_APPLICATION_GOTOMYPC,
    PACE2_APPLICATION_GOTOMEETING,
    PACE2_APPLICATION_WINDOWS_AZURE,
    PACE2_APPLICATION_AMAZON_CLOUD,
    PACE2_APPLICATION_DAILYMOTION,
    PACE2_APPLICATION_DEEZER,
    PACE2_APPLICATION_GROOVESHARK,
    PACE2_APPLICATION_SUDAPHONE,
    PACE2_APPLICATION_OFFICE365,
    PACE2_APPLICATION_CNTV,
    PACE2_APPLICATION_SINATV,
    PACE2_APPLICATION_YOUTUBE,
    PACE2_APPLICATION_VOIP_SWITCH,
    PACE2_APPLICATION_ZYNGA,
    PACE2_APPLICATION_CRIMECITY,
    PACE2_APPLICATION_MODERNWAR,
    PACE2_APPLICATION_VIPPIE,
    PACE2_APPLICATION_BOX,
    PACE2_APPLICATION_SKYDRIVE,
    PACE2_APPLICATION_ADOBE_CREATIVE_CLOUD,
    PACE2_APPLICATION_LINKEDIN,
    PACE2_APPLICATION_ORKUT,
    PACE2_APPLICATION_HI5,
    PACE2_APPLICATION_SORIBADA,
    PACE2_APPLICATION_ZOHO_WORK_ONLINE,
    PACE2_APPLICATION_HOTMAIL,
    PACE2_APPLICATION_INSTAGRAM,
    PACE2_APPLICATION_SUGARSYNC,
    PACE2_APPLICATION_WICKR,
    PACE2_APPLICATION_TIGERTEXT,
    PACE2_APPLICATION_VIBE,
    PACE2_APPLICATION_ENLEGION,
    PACE2_APPLICATION_VOXER,
    PACE2_APPLICATION_LOVEFILM,
    PACE2_APPLICATION_FRIENDSTER,
    PACE2_APPLICATION_BURNER,
    PACE2_APPLICATION_FLICKR,
    PACE2_APPLICATION_LIVE_COM,
    PACE2_APPLICATION_ICQ_WEBCHAT,
    PACE2_APPLICATION_REDTUBE,
    PACE2_APPLICATION_EVERNOTE,
    PACE2_APPLICATION_SPREED,
    PACE2_APPLICATION_TEXTPLUS,
    PACE2_APPLICATION_XVIDEOS,
    PACE2_APPLICATION_SNAPCHAT,
    PACE2_APPLICATION_YOUKU,
    PACE2_APPLICATION_MYMUSIC_TW,
    PACE2_APPLICATION_RENREN,
    PACE2_APPLICATION_YELP,
    PACE2_APPLICATION_AMAZON_SHOP,
    PACE2_APPLICATION_YOUPORN,
    PACE2_APPLICATION_EBAY,
    PACE2_APPLICATION_PORNHUB,
    PACE2_APPLICATION_SPIDEROAK,
    PACE2_APPLICATION_ADRIVE,
    PACE2_APPLICATION_TUMBLR,
    PACE2_APPLICATION_XING,
    PACE2_APPLICATION_GOOGLE_PLAY_MUSIC,
    PACE2_APPLICATION_VIMEO,
    PACE2_APPLICATION_SALESFORCE,
    PACE2_APPLICATION_ITUNES_RADIO,
    PACE2_APPLICATION_SINA_WEIBO,
    PACE2_APPLICATION_FORFONE,
    PACE2_APPLICATION_LIVEJASMIN,
    PACE2_APPLICATION_JINGDONG,
    PACE2_APPLICATION_LASTFM,
    PACE2_APPLICATION_IMS,
    PACE2_APPLICATION_BAIDU,
    PACE2_APPLICATION_TAOBAO,
    PACE2_APPLICATION_WATCHEVER,
    PACE2_APPLICATION_TTPOD,
    PACE2_APPLICATION_360MOBILE,
    PACE2_APPLICATION_PINTEREST,
    PACE2_APPLICATION_VINE,
    PACE2_APPLICATION_NET2PHONE,
    PACE2_APPLICATION_FOURSQUARE,
    PACE2_APPLICATION_ILIVE_TO,
    PACE2_APPLICATION_MEGA,
    PACE2_APPLICATION_DOOOK,
    PACE2_APPLICATION_VBULLETIN,
    PACE2_APPLICATION_CLOUDME,
    PACE2_APPLICATION_YIKYAK,
    PACE2_APPLICATION_REDMINE,
    PACE2_APPLICATION_IHEART_RADIO,
    PACE2_APPLICATION_AVIRA_ANTIVIRUS,
    PACE2_APPLICATION_NORTON_ANTIVIRUS,
    PACE2_APPLICATION_KASPERSKY_ANTIVIRUS,
    PACE2_APPLICATION_AVG_ANTIVIRUS,
    PACE2_APPLICATION_SOUNDCLOUD,
    PACE2_APPLICATION_RDIO,
    PACE2_APPLICATION_AMAZON_PRIME_MUSIC,
    PACE2_APPLICATION_RUNKEEPER,
    PACE2_APPLICATION_MYBOOK,
    PACE2_APPLICATION_NIKEPLUS,
    PACE2_APPLICATION_MAGV,
    PACE2_APPLICATION_MAGV_KIDS,
    PACE2_APPLICATION_DOTA_LEGEND,
    PACE2_APPLICATION_LETV,
    PACE2_APPLICATION_MY_FITNESS_PAL,
    PACE2_APPLICATION_SOHU,
    PACE2_APPLICATION_1KXUN,
    PACE2_APPLICATION_TVBS,
    PACE2_APPLICATION_XNXX,
    PACE2_APPLICATION_CTITV,
    PACE2_APPLICATION_ENDOMONDO,
    PACE2_APPLICATION_TIMELY_TV,
    PACE2_APPLICATION_WORKOUT_TRAINER,
    PACE2_APPLICATION_MAP_MY_RUN,
    PACE2_APPLICATION_KING_OF_PIRATES,
    PACE2_APPLICATION_TUDOU,
    PACE2_APPLICATION_BITTORRENT,
    PACE2_APPLICATION_EDONKEY,
    PACE2_APPLICATION_FASTTRACK,
    PACE2_APPLICATION_GNUTELLA,
    PACE2_APPLICATION_DIRECTCONNECT,
    PACE2_APPLICATION_APPLEJUICE,
    PACE2_APPLICATION_SOULSEEK,
    PACE2_APPLICATION_ARES,
    PACE2_APPLICATION_FREENET,
    PACE2_APPLICATION_MUTE,
    PACE2_APPLICATION_SKYPE,
    PACE2_APPLICATION_MSN,
    PACE2_APPLICATION_YAHOO,
    PACE2_APPLICATION_VONAGE,
    PACE2_APPLICATION_OSCAR,
    PACE2_APPLICATION_GADUGADU,
    PACE2_APPLICATION_MPLUS,
    PACE2_APPLICATION_IRC,
    PACE2_APPLICATION_SLINGBOX,
    PACE2_APPLICATION_VCAST,
    PACE2_APPLICATION_DDL_4SHARED_COM,
    PACE2_APPLICATION_DDL_ADRIVE_COM,
    PACE2_APPLICATION_DDL_BADONGO_COM,
    PACE2_APPLICATION_DDL_BADONGO_NET,
    PACE2_APPLICATION_DDL_BESTSHARING_COM,
    PACE2_APPLICATION_DDL_BIGFILEZ_COM,
    PACE2_APPLICATION_DDL_CHINAMOFILE_COM,
    PACE2_APPLICATION_DDL_DATA_HU,
    PACE2_APPLICATION_DDL_DEPOSITFILES_COM,
    PACE2_APPLICATION_DDL_EASY_SHARE_COM,
    PACE2_APPLICATION_DDL_FAST_LOAD_NET,
    PACE2_APPLICATION_DDL_FAST_SHARE_COM,
    PACE2_APPLICATION_DDL_FILE_UPLOAD_NET,
    PACE2_APPLICATION_DDL_FILE_UPLOAD_TO,
    PACE2_APPLICATION_DDL_FILEARCHIV_RU,
    PACE2_APPLICATION_DDL_FILEBASE_TO,
    PACE2_APPLICATION_DDL_FILECLOUD_COM,
    PACE2_APPLICATION_DDL_FILEFACTORY_COM,
    PACE2_APPLICATION_DDL_FILEFRONT_COM,
    PACE2_APPLICATION_DDL_FILEHO_COM,
    PACE2_APPLICATION_DDL_FILEHOST_TV,
    PACE2_APPLICATION_DDL_FILEPOST_RU,
    PACE2_APPLICATION_DDL_FILER_NET,
    PACE2_APPLICATION_DDL_FILES_UPLOAD_COM,
    PACE2_APPLICATION_DDL_FILES_TO,
    PACE2_APPLICATION_DDL_FILESAFE_TO,
    PACE2_APPLICATION_DDL_FILESEND_NET,
    PACE2_APPLICATION_DDL_FILEUPYOURS_COM,
    PACE2_APPLICATION_DDL_FTP2SHARE_COM,
    PACE2_APPLICATION_DDL_GIGASIZE_COM,
    PACE2_APPLICATION_DDL_GIGESHARE_COM,
    PACE2_APPLICATION_DDL_HOSTGGG_COM,
    PACE2_APPLICATION_DDL_HOTFILE_COM,
    PACE2_APPLICATION_DDL_IFOLDER_RU,
    PACE2_APPLICATION_DDL_KEEPMYFILE_COM,
    PACE2_APPLICATION_DDL_LETECKAPOSTA_CZ,
    PACE2_APPLICATION_DDL_LIVE_SHARE_COM,
    PACE2_APPLICATION_DDL_LIVEDEPOT_NET,
    PACE2_APPLICATION_DDL_LOAD_TO,
    PACE2_APPLICATION_DDL_MASSMIRROR_COM,
    PACE2_APPLICATION_DDL_MEDIAFIRE_COM,
    PACE2_APPLICATION_DDL_MEGAROTIC_COM,
    PACE2_APPLICATION_DDL_MEGASHARE_COM,
    PACE2_APPLICATION_DDL_MEGASHARES_COM,
    PACE2_APPLICATION_DDL_MEGAUPLOAD_COM,
    PACE2_APPLICATION_DDL_MOFILE_COM,
    PACE2_APPLICATION_DDL_MOFILE_NET,
    PACE2_APPLICATION_DDL_MYTEMPDIR_COM,
    PACE2_APPLICATION_DDL_NETLOAD_IN,
    PACE2_APPLICATION_DDL_ODSIEBIE_NAJLEPSZE_NET,
    PACE2_APPLICATION_DDL_QUICKSHARING_COM,
    PACE2_APPLICATION_DDL_RAPIDSHARE_COM,
    PACE2_APPLICATION_DDL_RAPIDSHARE_DE,
    PACE2_APPLICATION_DDL_RAPIDUPLOAD_COM,
    PACE2_APPLICATION_DDL_SAVEFILE_COM,
    PACE2_APPLICATION_DDL_SENDMEFILE_COM,
    PACE2_APPLICATION_DDL_SENDSPACE_COM,
    PACE2_APPLICATION_DDL_SHAREBASE_TO,
    PACE2_APPLICATION_DDL_SHAREBEE_COM,
    PACE2_APPLICATION_DDL_SHAREBIG_COM,
    PACE2_APPLICATION_DDL_SHAREBIGFILE_COM,
    PACE2_APPLICATION_DDL_SHAREBIGFLIE_COM,
    PACE2_APPLICATION_DDL_SIMPLEUPLOAD_NET,
    PACE2_APPLICATION_DDL_SPEEDSHARE_ORG,
    PACE2_APPLICATION_DDL_TURBOUPLOAD_COM,
    PACE2_APPLICATION_DDL_ULTRASHARE_DE,
    PACE2_APPLICATION_DDL_UP_FILE_COM,
    PACE2_APPLICATION_DDL_UPLOADED_TO,
    PACE2_APPLICATION_DDL_UPLOADING_COM,
    PACE2_APPLICATION_DDL_UPLOADINGIT_COM,
    PACE2_APPLICATION_DDL_UPLOADPOWER_COM,
    PACE2_APPLICATION_DDL_UPLOADYOURFILES_DE,
    PACE2_APPLICATION_DDL_VIP_FILE_COM,
    PACE2_APPLICATION_DDL_WIIUPLOAD_NET,
    PACE2_APPLICATION_DDL_YOURFILEHOST_COM,
    PACE2_APPLICATION_DDL_YOURFILES_BIZ,
    PACE2_APPLICATION_DDL_YOUTUBE_COM,
    PACE2_APPLICATION_DDL_ZSHARE_NET,
    PACE2_APPLICATION_DDL_4SHARED_VN,
    PACE2_APPLICATION_DDL_MEGA_1280_COM,
    PACE2_APPLICATION_DDL_MEGASHARE_VN,
    PACE2_APPLICATION_DDL_FILESERVE_COM,
    PACE2_APPLICATION_DDL_FILESONIC_COM,
    PACE2_APPLICATION_DDL_1_UPLOAD_TO,
    PACE2_APPLICATION_DDL_1FICHIER_COM,
    PACE2_APPLICATION_DDL_4FASTFILE_COM,
    PACE2_APPLICATION_DDL_10UPLOAD_COM,
    PACE2_APPLICATION_DDL_1CLICKSHARE_NET,
    PACE2_APPLICATION_DDL_FILEDUDE_COM,
    PACE2_APPLICATION_DDL_ASIXFILES_COM,
    PACE2_APPLICATION_DDL_BANASHARE_COM,
    PACE2_APPLICATION_DDL_BIGGERUPLOAD_COM,
    PACE2_APPLICATION_DDL_BITSHARE_COM,
    PACE2_APPLICATION_DDL_CASH_FILE_NET,
    PACE2_APPLICATION_DDL_CRAMIT_IN,
    PACE2_APPLICATION_DDL_CZSHARE_COM,
    PACE2_APPLICATION_DDL_DATA_LOADING_COM,
    PACE2_APPLICATION_DDL_DATAPORT_CZ,
    PACE2_APPLICATION_DDL_DATEI_TO,
    PACE2_APPLICATION_DDL_DOWNUPLOAD_COM,
    PACE2_APPLICATION_DDL_EASYBYTEZ_COM,
    PACE2_APPLICATION_DDL_EDISK_CZ,
    PACE2_APPLICATION_DDL_ENTERUPLOAD_COM,
    PACE2_APPLICATION_DDL_EUROSHARE_EU,
    PACE2_APPLICATION_DDL_EXTABIT_COM,
    PACE2_APPLICATION_DDL_FASTFILESHARE_COM_AR,
    PACE2_APPLICATION_DDL_FIK1_COM,
    PACE2_APPLICATION_DDL_FILE2UPLOAD_NET,
    PACE2_APPLICATION_DDL_FILEAPE_COM,
    PACE2_APPLICATION_DDL_FILEFLYER_COM,
    PACE2_APPLICATION_DDL_FILEFROG_COM,
    PACE2_APPLICATION_DDL_FILEHOOK_COM,
    PACE2_APPLICATION_DDL_FILEOVER_NET,
    PACE2_APPLICATION_DDL_FILEPOST_COM,
    PACE2_APPLICATION_DDL_FILES_MAIL_RU,
    PACE2_APPLICATION_DDL_FILESHARE_IN_UA,
    PACE2_APPLICATION_DDL_FILESMONSTER_COM,
    PACE2_APPLICATION_DDL_FILEVO_COM,
    PACE2_APPLICATION_DDL_FILEZUP_COM,
    PACE2_APPLICATION_DDL_FREAKSHARE_NET,
    PACE2_APPLICATION_DDL_FSHARE_VN,
    PACE2_APPLICATION_DDL_GAIAFILE_COM,
    PACE2_APPLICATION_DDL_GIGAPETA_COM,
    PACE2_APPLICATION_DDL_GOTOUPLOAD_COM,
    PACE2_APPLICATION_DDL_HELLSHARE_COM,
    PACE2_APPLICATION_DDL_HITFILE_NET,
    PACE2_APPLICATION_DDL_HULKSHARE_COM,
    PACE2_APPLICATION_DDL_HYPERFILESHARE_COM,
    PACE2_APPLICATION_DDL_I_FILEZ_COM,
    PACE2_APPLICATION_DDL_IFILE_IT,
    PACE2_APPLICATION_DDL_KEWLSHARE_COM,
    PACE2_APPLICATION_DDL_LETITBIT_NET,
    PACE2_APPLICATION_DDL_LOADFILES_IN,
    PACE2_APPLICATION_DDL_MEGAFREE_KZ,
    PACE2_APPLICATION_DDL_MEGARAPID_EU,
    PACE2_APPLICATION_DDL_MEGASHARE_VNN_VN,
    PACE2_APPLICATION_DDL_MIDUPLOAD_COM,
    PACE2_APPLICATION_DDL_MULTISHARE_CZ,
    PACE2_APPLICATION_DDL_NETUPLOADED_COM,
    PACE2_APPLICATION_DDL_ORON_COM,
    PACE2_APPLICATION_DDL_PRZEKLEJ_PL,
    PACE2_APPLICATION_DDL_PUTSHARE_COM,
    PACE2_APPLICATION_DDL_QSHARE_COM,
    PACE2_APPLICATION_DDL_QUICKSHARE_CZ,
    PACE2_APPLICATION_DDL_RAPIDSHARK_PL,
    PACE2_APPLICATION_DDL_SCRIBD_COM,
    PACE2_APPLICATION_DDL_SHARE_ONLINE_BZ,
    PACE2_APPLICATION_DDL_SHARE_RAPID_CZ,
    PACE2_APPLICATION_DDL_SHRAGLE_COM,
    PACE2_APPLICATION_DDL_STORAGE_TO,
    PACE2_APPLICATION_DDL_TERAFILES_NET,
    PACE2_APPLICATION_DDL_TUNABOX_NET,
    PACE2_APPLICATION_DDL_TURBOBIT_NET,
    PACE2_APPLICATION_DDL_UGOTFILE_COM,
    PACE2_APPLICATION_DDL_ULOZ_TO,
    PACE2_APPLICATION_DDL_UNIBYTES_COM,
    PACE2_APPLICATION_DDL_UNLIMIT_CO_IL,
    PACE2_APPLICATION_DDL_UP_4SHARE_VN,
    PACE2_APPLICATION_DDL_UPLOAD_COM_UA,
    PACE2_APPLICATION_DDL_UPLOADBOX_COM,
    PACE2_APPLICATION_DDL_UPLOADER_PL,
    PACE2_APPLICATION_DDL_UPLOADFLOOR_COM,
    PACE2_APPLICATION_DDL_UPLOADSTATION_COM,
    PACE2_APPLICATION_DDL_UPNITO_SK,
    PACE2_APPLICATION_DDL_USERSHARE_NET,
    PACE2_APPLICATION_DDL_VIDEOBB_COM,
    PACE2_APPLICATION_DDL_WUPLOAD_COM,
    PACE2_APPLICATION_DDL_X7_TO,
    PACE2_APPLICATION_DDL_YUNFILE_TO,
    PACE2_APPLICATION_DDL_ZOMGUPLOAD_TO,
    PACE2_APPLICATION_DDL_ZIDDU_COM,
    PACE2_APPLICATION_DDL_1_UPLOAD_COM,
    PACE2_APPLICATION_DDL_1_CLICKSHARE_COM,
    PACE2_APPLICATION_DDL_123UPLOAD_PL,
    PACE2_APPLICATION_DDL_139PAN_COM,
    PACE2_APPLICATION_DDL_163PAN_COM,
    PACE2_APPLICATION_DDL_2SHARED_COM,
    PACE2_APPLICATION_DDL_4SHARE_WS,
    PACE2_APPLICATION_DDL_4US_TO,
    PACE2_APPLICATION_DDL_ALLDRIVES_GE,
    PACE2_APPLICATION_DDL_ALLSHARES_GE,
    PACE2_APPLICATION_DDL_ANNONHOST_NET,
    PACE2_APPLICATION_DDL_BOOSTERKING_COM,
    PACE2_APPLICATION_DDL_COBRASHARE_SK,
    PACE2_APPLICATION_DDL_COOLSHARE_CZ,
    PACE2_APPLICATION_DDL_CROCKO_COM,
    PACE2_APPLICATION_DDL_CUM_COM,
    PACE2_APPLICATION_DDL_EYVX_COM,
    PACE2_APPLICATION_DDL_FILEARN_COM,
    PACE2_APPLICATION_DDL_FILEJUNGLE_COM,
    PACE2_APPLICATION_DDL_FILEMAZE_WS,
    PACE2_APPLICATION_DDL_FILESFLASH_COM,
    PACE2_APPLICATION_DDL_FREESPACE_BY,
    PACE2_APPLICATION_DDL_FSX_HU,
    PACE2_APPLICATION_DDL_JAKFILE_COM,
    PACE2_APPLICATION_DDL_JUMBOFILES_COM,
    PACE2_APPLICATION_DDL_KICKLOAD_COM,
    PACE2_APPLICATION_DDL_MISSUPLOAD_COM,
    PACE2_APPLICATION_DDL_MOVREEL_COM,
    PACE2_APPLICATION_DDL_PLATINSHARE_COM,
    PACE2_APPLICATION_DDL_SANUPLOAD_COM,
    PACE2_APPLICATION_DDL_SHAREFLARE_NET,
    PACE2_APPLICATION_DDL_U_115_COM,
    PACE2_APPLICATION_DDL_UPLOADC_COM,
    PACE2_APPLICATION_DDL_UPLOADKING_COM,
    PACE2_APPLICATION_DDL_UPTOBOX_COM,
    PACE2_APPLICATION_DDL_FILESTUBE_COM,
    PACE2_APPLICATION_DDL_GAMEFRONT_COM,
    PACE2_APPLICATION_DDL_MEGAPORN_COM,
    PACE2_APPLICATION_DDL_FILESONIC_IN,
    PACE2_APPLICATION_DDL_TURBOBIT_RU,
    PACE2_APPLICATION_USENET,
    PACE2_APPLICATION_FTP,
    PACE2_APPLICATION_FILETOPIA,
    PACE2_APPLICATION_MANOLITO,
    PACE2_APPLICATION_IMESH,
    PACE2_APPLICATION_PANDO,
    PACE2_APPLICATION_SOPCAST,
    PACE2_APPLICATION_TVUPLAYER,
    PACE2_APPLICATION_PPSTREAM,
    PACE2_APPLICATION_PPLIVE,
    PACE2_APPLICATION_ZATTOO,
    PACE2_APPLICATION_QQ,
    PACE2_APPLICATION_QQLIVE,
    PACE2_APPLICATION_FEIDIAN,
    PACE2_APPLICATION_POPO,
    PACE2_APPLICATION_THUNDER,
    PACE2_APPLICATION_UUSEE,
    PACE2_APPLICATION_VNC,
    PACE2_APPLICATION_STEAM,
    PACE2_APPLICATION_HALFLIFE2,
    PACE2_APPLICATION_SOFTETHER,
    PACE2_APPLICATION_TELNET,
    PACE2_APPLICATION_OFF,
    PACE2_APPLICATION_TOR,
    PACE2_APPLICATION_WORLDOFWARCRAFT,
    PACE2_APPLICATION_HAMACHI_VPN,
    PACE2_APPLICATION_SKINNY,
    PACE2_APPLICATION_CITRIX,
    PACE2_APPLICATION_PALTALK,
    PACE2_APPLICATION_QUAKE,
    PACE2_APPLICATION_SECONDLIFE,
    PACE2_APPLICATION_BATTLEFIELD,
    PACE2_APPLICATION_PCANYWHERE,
    PACE2_APPLICATION_ICECAST,
    PACE2_APPLICATION_SHOUTCAST,
    PACE2_APPLICATION_QQGAME,
    PACE2_APPLICATION_VEOHTV,
    PACE2_APPLICATION_OPENFT,
    PACE2_APPLICATION_PANDORA,
    PACE2_APPLICATION_IPP,
    PACE2_APPLICATION_WARCRAFT3,
    PACE2_APPLICATION_OOVOO,
    PACE2_APPLICATION_GOOGLE_TALK,
    PACE2_APPLICATION_ISKOOT,
    PACE2_APPLICATION_FRING,
    PACE2_APPLICATION_IPTV,
    PACE2_APPLICATION_YOURFREEDOM,
    PACE2_APPLICATION_VOIPSWITCH_VOIPTUNNEL,
    PACE2_APPLICATION_MEEBO,
    PACE2_APPLICATION_FUNSHION,
    PACE2_APPLICATION_AIMINI,
    PACE2_APPLICATION_CLUBPENGUIN,
    PACE2_APPLICATION_FLORENSIA,
    PACE2_APPLICATION_TEAMSPEAK,
    PACE2_APPLICATION_MAPLESTORY,
    PACE2_APPLICATION_OSH,
    PACE2_APPLICATION_PS3,
    PACE2_APPLICATION_DOFUS,
    PACE2_APPLICATION_FIESTA,
    PACE2_APPLICATION_SPLASHFIGHTER,
    PACE2_APPLICATION_ACTIVESYNC,
    PACE2_APPLICATION_JABBER_APPLICATION_NIMBUZZ,
    PACE2_APPLICATION_CROSSFIRE,
    PACE2_APPLICATION_WAP_WSP,
    PACE2_APPLICATION_GUILDWARS,
    PACE2_APPLICATION_ARMAGETRON,
    PACE2_APPLICATION_RFACTOR,
    PACE2_APPLICATION_TEAMVIEWER,
    PACE2_APPLICATION_GAMEKIT,
    PACE2_APPLICATION_ULTRABAC,
    PACE2_APPLICATION_SPOTIFY,
    PACE2_APPLICATION_IMPLUS,
    PACE2_APPLICATION_ANTSP2P,
    PACE2_APPLICATION_ULTRASURF,
    PACE2_APPLICATION_VIBER,
    PACE2_APPLICATION_TANGO,
    PACE2_APPLICATION_IPLAYER,
    PACE2_APPLICATION_OPERAMINI,
    PACE2_APPLICATION_BOLT,
    PACE2_APPLICATION_SCYDO,
    PACE2_APPLICATION_WHATSAPP,
    PACE2_APPLICATION_WEBEX,
    PACE2_APPLICATION_NETFLIX,
    PACE2_APPLICATION_MOJO,
    PACE2_APPLICATION_IMO,
    PACE2_APPLICATION_CITRIX_GOTO,
    PACE2_APPLICATION_FICALL,
    PACE2_APPLICATION_COMODOUNITE,
    PACE2_APPLICATION_VENTRILO,
    PACE2_APPLICATION_MYPEOPLE,
    PACE2_APPLICATION_EBUDDY,
    PACE2_APPLICATION_ADOBE_CONNECT,
    PACE2_APPLICATION_JAP,
    PACE2_APPLICATION_WUALA,
    PACE2_APPLICATION_WEBDAV,
    PACE2_APPLICATION_LYNC,
    PACE2_APPLICATION_AUDIOGALAXY,
    PACE2_APPLICATION_MIG33,
    PACE2_APPLICATION_HTTP_TUNNEL,
    PACE2_APPLICATION_RHAPSODY,
    PACE2_APPLICATION_WEBQQ,
    PACE2_APPLICATION_PDPROXY,
    PACE2_APPLICATION_CYBERGHOST,
    PACE2_APPLICATION_GOOGLE_CLOUD,
    PACE2_APPLICATION_GOOGLE_DRIVE,
    PACE2_APPLICATION_GOOGLE_DOCS,
    PACE2_APPLICATION_GOOGLE_PLUS,
    PACE2_APPLICATION_ORACLE_DB,
    PACE2_APPLICATION_ITV,
    PACE2_APPLICATION_DEMAND5,
    PACE2_APPLICATION_RSVP,
    PACE2_APPLICATION_CHANNEL_4OD,
    PACE2_APPLICATION_LOTUS_NOTES,
    PACE2_APPLICATION_POISON_IVY,
    PACE2_APPLICATION_HIDRIVE,
    PACE2_APPLICATION_WECHAT,
    PACE2_APPLICATION_MYVIDEO,
    PACE2_APPLICATION_KIK_MESSENGER,
    PACE2_APPLICATION_LINE,
    PACE2_APPLICATION_IPERF,
    PACE2_APPLICATION_OS_UPDATE,
    PACE2_APPLICATION_HIKE_MESSENGER,
    PACE2_APPLICATION_DIDI,
    PACE2_APPLICATION_IDRIVE,
    PACE2_APPLICATION_SPREECAST,
    PACE2_APPLICATION_SIMFY,
    PACE2_APPLICATION_DOTA2,
    PACE2_APPLICATION_QVOD,
    PACE2_APPLICATION_HULU,
    PACE2_APPLICATION_MSEXCHANGE,
    PACE2_APPLICATION_MSNAV,
    PACE2_APPLICATION_FUZE,
    PACE2_APPLICATION_KAKAOTALK,
    PACE2_APPLICATION_DESTINY,
    PACE2_APPLICATION_VYPR_VPN,
    PACE2_APPLICATION_THREEMA,
    PACE2_APPLICATION_NTLM,
    PACE2_APPLICATION_TWITCH,
    PACE2_APPLICATION_WOWZA,
    PACE2_APPLICATION_RUNTASTIC,
    PACE2_APPLICATION_TELEGRAM,
    PACE2_APPLICATION_STREETVOICE,
    PACE2_APPLICATION_DUOKAN,
    PACE2_APPLICATION_MEI_LU,
    PACE2_APPLICATION_SKOUT,
    PACE2_APPLICATION_PLAYTALES,
    PACE2_APPLICATION_GAME_OF_WAR,
    PACE2_APPLICATION_FETNET,
    PACE2_APPLICATION_FBS,
    PACE2_APPLICATION_NATIONAL_BASEBALL,
    PACE2_APPLICATION_PINKFONG,
    PACE2_APPLICATION_KOLLECT_BOOK,
    PACE2_APPLICATION_SPTG_TV,
	PACE2_APPLICATION_CIAOMOBILE_HDTV,
	PACE2_APPLICATION_SKYKING,
    PACE2_APPLICATION_MOVES,
    PACE2_APPLICATION_PATH,
    PACE2_APPLICATION_AOWE,
    PACE2_APPLICATION_IWOW_SYSTEX,
    PACE2_APPLICATION_9KU,
    PACE2_APPLICATION_NEXTTV,
    PACE2_APPLICATION_SYNCPLICITY,
    PACE2_APPLICATION_REALMA,
    PACE2_APPLICATION_YUANTA_WEB,
    PACE2_APPLICATION_HINET,
    PACE2_APPLICATION_MYCARD,
	PACE2_APPLICATION_KONO,
	PACE2_APPLICATION_SPEAKABOOS,
    PACE2_APPLICATION_DUO_DUO,
    PACE2_APPLICATION_WEALTH_GOD,
    PACE2_APPLICATION_ILEADER,
    PACE2_APPLICATION_THREE_BAMBOO,
    PACE2_APPLICATION_TAAZE,
    PACE2_APPLICATION_AUDIKO,
    PACE2_APPLICATION_PUBU_BOOKBUFFET,
    PACE2_APPLICATION_MITAKE,
    PACE2_APPLICATION_HYREAD,
    PACE2_APPLICATION_DISNEY_STORYTIME,
    PACE2_APPLICATION_QUALYS,
    PACE2_APPLICATION_CONSTANT_CONTACT,
    PACE2_APPLICATION_RALLY,
    PACE2_APPLICATION_MAGINE_TV,
    PACE2_APPLICATION_INTRALINKS,
    PACE2_APPLICATION_LIVEPERSON,
    PACE2_APPLICATION_SPEEDTEST,
    PACE2_APPLICATION_BLUEJEANS,
    PACE2_APPLICATION_APPLE_MUSIC,
    PACE2_APPLICATION_NAVER,
    PACE2_APPLICATION_BOOKING_COM,
    PACE2_APPLICATION_CNN,
    PACE2_APPLICATION_PERISCOPE,
    PACE2_APPLICATION_PAYEASY,
    PACE2_APPLICATION_LINE_RANGERS,
    PACE2_APPLICATION_IOS_APP_STORE,
    PACE2_APPLICATION_MYVIDEO_TW,
    PACE2_APPLICATION_KING_GAMING,
    PACE2_APPLICATION_CANDY_CRUSH,
    PACE2_APPLICATION_CANDY_CRUSH_SODA,
    PACE2_APPLICATION_BUBBLE_WITCH,
    PACE2_APPLICATION_FARM_HERO,
    PACE2_APPLICATION_PLAYSTATION,
    PACE2_APPLICATION_GOOGLE_PLAY,
    PACE2_APPLICATION_SUPERCELL,
    PACE2_APPLICATION_CLASH_OF_CLANS,
    PACE2_APPLICATION_BOOM_BEACH,
    PACE2_APPLICATION_HAY_DAY,
    PACE2_APPLICATION_WINDOWS_STORE,
    PACE2_APPLICATION_SKYPE_FOR_BUSINESS,

    PACE2_APPLICATIONS_COUNT

} PACE2_applications;

/**
 * @brief Struct representing all available applications as a bitmask.
**/
typedef struct {
    u32 ukn:1;                      //!< unknown
    u32 facebook:1;                 //!< Facebook
    u32 magicjack:1;                //!< magicJack
    u32 itunes:1;                   //!< iTunes
    u32 myspace:1;                  //!< MySpace
    u32 facetime:1;                 //!< FaceTime
    u32 truphone:1;                 //!< Truphone
    u32 twitter:1;                  //!< Twitter
    u32 xbox:1;                     //!< XBOX gaming console
    u32 realmedia:1;                //!< RealMedia
    u32 google_mail:1;              //!< Google Mail
    u32 goober:1;                   //!< Goober
    u32 icloud:1;                   //!< iCloud
    u32 ubuntuone:1;                //!< Ubuntu One
    u32 dropbox:1;                  //!< Dropbox
    u32 yuilop:1;                   //!< Yuilop
    u32 imessage:1;                 //!< iMessage
    u32 gotomypc:1;                 //!< GoToMyPC
    u32 gotomeeting:1;              //!< GoToMeeting
    u32 windows_azure:1;            //!< Windows Azure
    u32 amazon_cloud:1;             //!< Amazon Cloud
    u32 dailymotion:1;              //!< Dailymotion
    u32 deezer:1;                   //!< Deezer
    u32 grooveshark:1;              //!< Grooveshark
    u32 sudaphone:1;                //!< SUDA Phone
    u32 office365:1;                //!< Office 365
    u32 cntv:1;                     //!< CNTV
    u32 sinatv:1;                   //!< SINATV
    u32 youtube:1;                  //!< YouTube
    u32 voipswitch:1;               //!< VoipSwitch
    u32 zynga:1;                    //!< Zynga
    u32 crimecity:1;                //!< Crime City
    u32 modernwar:1;                //!< Modern War
    u32 vippie:1;                   //!< Vippie
    u32 box:1;                      //!< Box
    u32 skydrive:1;                 //!< Skydrive
    u32 adobe_creative_cloud:1;     //!< Adobe Creative Cloud
    u32 linkedin:1;                 //!< LinkedIn
    u32 orkut:1;                    //!< Orkut
    u32 hi5:1;                      //!< hi5
    u32 soribada:1;                 //!< Soribada
    u32 zoho_work_online:1;         //!< Zoho Work Online
    u32 hotmail_webmail:1;          //!< Hotmail
    u32 instagram:1;                //!< Instagram
    u32 sugarsync:1;                //!< SugarSync
    u32 wickr:1;                    //!< Wickr
    u32 tigertext:1;                //!< TigerText
    u32 vibe:1;                     //!< Vibe
    u32 enlegion:1;                 //!< enLegion
    u32 voxer:1;                    //!< Voxer
    u32 lovefilm:1;                 //!< LOVEFiLM
    u32 friendster:1;               //!< Friendster
    u32 burner:1;                   //!< Burner
    u32 flickr:1;                   //!< Flickr
    u32 live_com:1;                 //!< live.com
    u32 icq_webchat:1;              //!< ICQ Webchat
    u32 redtube:1;                  //!< RedTube
    u32 evernote:1;                 //!< Evernote
    u32 spreed:1;                   //!< Spreed
    u32 textplus:1;                 //!< textPlus
    u32 xvideos:1;                  //!< Xvideos
    u32 snapchat:1;                 //!< Snapchat
    u32 youku:1;                    //!< Youku
    u32 mymusic_tw:1;               //!< MyMusic
    u32 renren:1;                   //!< Renren
    u32 yelp:1;                     //!< Yelp
    u32 amazon_shop:1;              //!< Amazon shopping
    u32 youporn:1;                  //!< YouPorn
    u32 ebay:1;                     //!< eBay
    u32 pornhub:1;                  //!< PornHub
    u32 spideroak:1;                //!< Spideroak
    u32 adrive:1;                   //!< Adrive
    u32 tumblr:1;                   //!< tumblr
    u32 xing:1;                     //!< XING
    u32 google_play_music:1;        //!< Google Play Music
    u32 vimeo:1;                    //!< Vimeo
    u32 salesforce:1;               //!< Salesforce
    u32 itunes_radio:1;             //!< iTunes Radio
    u32 sina_weibo:1;               //!< Sina Weibo
    u32 forfone:1;                  //!< Forfone
    u32 livejasmin:1;               //!< LiveJasmin
    u32 jingdong:1;                 //!< Jingdong
    u32 lastfm:1;                   //!< Last.fm
    u32 ims:1;                      //!< IP Multimedia Subsystem
    u32 baidu:1;                    //!< Baidu
    u32 taobao:1;                   //!< Taobao
    u32 watchever:1;                //!< Watchever
    u32 ttpod:1;                    //!< TTPod
    u32 _360mobile:1;               //!< 360 Mobile Security
    u32 pinterest:1;                //!< Pinterest
    u32 vine:1;                     //!< Vine
    u32 net2phone:1;                //!< Net2Phone
    u32 foursquare:1;               //!< Foursquare
    u32 ilive_to:1;                 //!< iLive.to
    u32 mega:1;                     //!< MEGA
    u32 doook:1;                    //!< Doook
    u32 vbulletin:1;                //!< vBulletin
    u32 cloudme:1;                  //!< CloudMe
    u32 yikyak:1;                   //!< Yik Yak
    u32 redmine:1;                  //!< Redmine
    u32 iheartradio:1;              //!< iHeartRadio
    u32 avira_antivir:1;            //!< Avira Antivirus
    u32 norton_antivir:1;           //!< Norton Antivirus
    u32 kaspersky_antivir:1;        //!< Kaspersky Antivirus
    u32 avg_antivir:1;              //!< AVG Antivirus
    u32 soundcloud:1;               //!< SoundCloud
    u32 rdio:1;                     //!< Rdio
    u32 amazon_prime_music:1;       //!< Amazon Prime Music
    u32 runkeeper:1;                //!< RunKeeper
    u32 mybook:1;                   //!< myBook
    u32 nikeplus:1;                 //!< Nike Plus
    u32 magv:1;                     //!< MagV
    u32 magv_kids:1;                //!< MagV Kids
    u32 dota_legend:1;              //!< Dota Legend
    u32 letv:1;                     //!< LeTV
    u32 my_fitness_pal:1;           //!< MyFitnessPal
    u32 sohu:1;                     //!< Sohu
    u32 _1kxun:1;                   //!< 1kxun
    u32 tvbs:1;                     //!< TVBS
    u32 xnxx:1;                     //!< XNXX
    u32 ctitv:1;                    //!< CtiTV
    u32 endomondo:1;                //!< Endomondo
    u32 timely_tv:1;                //!< Timely TV
    u32 workout_trainer:1;          //!< Workout Trainer
    u32 mapmyrun:1;                 //!< MapMyRun
    u32 king_of_pirates:1;          //!< King of Pirates
    u32 tudou:1;                    //!< Tudou
    u32 bit:1;                      //!< BitTorrent
    u32 edk:1;                      //!< eDonkey
    u32 kazaa:1;                    //!< KaZaa/Fasttrack
    u32 gnu:1;                      //!< Gnutella
    u32 directconnect:1;            //!< DirectConnect
    u32 apple:1;                    //!< AppleJuice
    u32 soul:1;                     //!< Soulseek
    u32 ares:1;                     //!< Ares
    u32 freenet:1;                  //!< Freenet
    u32 mute:1;                     //!< Mute
    u32 skype:1;                    //!< Skype
    u32 msn:1;                      //!< MSN
    u32 yahoo:1;                    //!< Yahoo
    u32 vonage:1;                   //!< vonage
    u32 oscar:1;                    //!< Oscar
    u32 gadugadu:1;                 //!< Gadu-Gadu
    u32 mplus:1;                    //!< MPlus
    u32 irc:1;                      //!< IRC
    u32 sling:1;                    //!< Slingbox
    u32 vcast:1;                    //!< Vcast
    u32 _4shared_com:1;             //!< 4shared.com
    u32 adrive_com:1;               //!< adrive.com
    u32 badongo_com:1;              //!< badongo.com
    u32 badongo_net:1;              //!< badongo.net
    u32 bestsharing_com:1;          //!< bestsharing.com
    u32 bigfilez_com:1;             //!< bigfilez.com
    u32 chinamofile_com:1;          //!< chinamofile.com
    u32 data_hu:1;                  //!< data.hu
    u32 depositfiles_com:1;         //!< depositfiles.com
    u32 easy_share_com:1;           //!< easy-share.com
    u32 fast_load_net:1;            //!< fast-load.net
    u32 fast_share_com:1;           //!< fast-share.com
    u32 file_upload_net:1;          //!< file-upload.net
    u32 file_upload_to:1;           //!< file-upload.to
    u32 filearchiv_ru:1;            //!< filearchiv.ru
    u32 filebase_to:1;              //!< filebase.to
    u32 filecloud_com:1;            //!< filecloud.com
    u32 filefactory_com:1;          //!< filefactory.com
    u32 filefront_com:1;            //!< filefront.com
    u32 fileho_com:1;               //!< fileho.com
    u32 filehost_tv:1;              //!< filehost.tv
    u32 filepost_ru:1;              //!< filepost.ru
    u32 filer_net:1;                //!< filer.net
    u32 files_upload_com:1;         //!< files-upload.com
    u32 files_to:1;                 //!< files.to
    u32 filesafe_to:1;              //!< filesafe.to
    u32 filesend_net:1;             //!< filesend.net
    u32 fileupyours_com:1;          //!< fileupyours.com
    u32 ftp2share_com:1;            //!< ftp2share.com
    u32 gigasize_com:1;             //!< gigasize.com
    u32 gigeshare_com:1;            //!< gigeshare.com
    u32 hostggg_com:1;              //!< hostggg.com
    u32 hotfile_com:1;              //!< hotfile.com
    u32 ifolder_ru:1;               //!< ifolder.ru
    u32 keepmyfile_com:1;           //!< keepmyfile.com
    u32 leteckaposta_cz:1;          //!< leteckaposta.cz
    u32 live_share_com:1;           //!< live-share.com
    u32 livedepot_net:1;            //!< livedepot.net
    u32 load_to:1;                  //!< load.to
    u32 massmirror_com:1;           //!< massmirror.com
    u32 mediafire_com:1;            //!< mediafire.com
    u32 megarotic_com:1;            //!< megarotic.com
    u32 megashare_com:1;            //!< megashare.com
    u32 megashares_com:1;           //!< megashares.com
    u32 megaupload_com:1;           //!< megaupload.com
    u32 mofile_com:1;               //!< mofile.com
    u32 mofile_net:1;               //!< mofile.net
    u32 mytempdir_com:1;            //!< mytempdir.com
    u32 netload_in:1;               //!< netload.in
    u32 odsiebie_najlepsze_net:1;   //!< odsiebie.najlepsze.net
    u32 quicksharing_com:1;         //!< quicksharing.com
    u32 rapidshare_com:1;           //!< rapidshare.com
    u32 rapidshare_de:1;            //!< rapidshare.de
    u32 rapidupload_com:1;          //!< rapidupload.com
    u32 savefile_com:1;             //!< savefile.com
    u32 sendmefile_com:1;           //!< sendmefile.com
    u32 sendspace_com:1;            //!< sendspace.com
    u32 sharebase_to:1;             //!< sharebase.to
    u32 sharebee_com:1;             //!< sharebee.com
    u32 sharebig_com:1;             //!< sharebig.com
    u32 sharebigfile_com:1;         //!< sharebigfile.com
    u32 sharebigflie_com:1;         //!< sharebigflie.com
    u32 simpleupload_net:1;         //!< simpleupload.net
    u32 speedshare_org:1;           //!< speedshare.org
    u32 turboupload_com:1;          //!< turboupload.com
    u32 ultrashare_de:1;            //!< ultrashare.de
    u32 up_file_com:1;              //!< up-file.com
    u32 uploaded_to:1;              //!< uploaded.to
    u32 uploading_com:1;            //!< uploading.com
    u32 uploadingit_com:1;          //!< uploadingit.com
    u32 uploadpower_com:1;          //!< uploadpower.com
    u32 uploadyourfiles_de:1;       //!< uploadyourfiles.de
    u32 vip_file_com:1;             //!< vip-file.com
    u32 wiiupload_net:1;            //!< wiiupload.net
    u32 yourfilehost_com:1;         //!< yourfilehost.com
    u32 yourfiles_biz:1;            //!< yourfiles.biz
    u32 youtube_com:1;              //!< youtube.com
    u32 zshare_net:1;               //!< zshare.net
    u32 _4shared_vn:1;              //!< 4shared.vn
    u32 mega_1280_com:1;            //!< mega.1280.com
    u32 megashare_vn:1;             //!< megashare.vn
    u32 fileserve_com:1;            //!< fileserve.com
    u32 filesonic_com:1;            //!< filesonic.com
    u32 _1_upload_to:1;             //!< 1-upload.to
    u32 _1fichier_com:1;            //!< 1fichier.com
    u32 _4fastfile_com:1;           //!< 4fastfile.com
    u32 _10upload_com:1;            //!< 10upload.com
    u32 _1clickshare_net:1;         //!< 1clickshare.net
    u32 filedude_com:1;             //!< filedude.com
    u32 asixfiles_com:1;            //!< asixfiles.com
    u32 banashare_com:1;            //!< banashare.com
    u32 biggerupload_com:1;         //!< biggerupload.com
    u32 bitshare_com:1;             //!< bitshare.com
    u32 cash_file_net:1;            //!< cash-file.net
    u32 cramit_in:1;                //!< cramit.in
    u32 czshare_com:1;              //!< czshare.com
    u32 data_loading_com:1;         //!< data-loading.com
    u32 dataport_cz:1;              //!< dataport.cz
    u32 datei_to:1;                 //!< datei.to
    u32 downupload_com:1;           //!< downupload.com
    u32 easybytez_com:1;            //!< easybytez.com
    u32 edisk_cz:1;                 //!< edisk.cz
    u32 enterupload_com:1;          //!< enterupload.com
    u32 euroshare_eu:1;             //!< euroshare.eu
    u32 extabit_com:1;              //!< extabit.com
    u32 fastfileshare_com_ar:1;     //!< fastfileshare.com.ar
    u32 fik1_com:1;                 //!< fik1.com
    u32 file2upload_net:1;          //!< file2upload.net
    u32 fileape_com:1;              //!< fileape.com
    u32 fileflyer_com:1;            //!< fileflyer.com
    u32 filefrog_com:1;             //!< filefrog.com
    u32 filehook_com:1;             //!< filehook.com
    u32 fileover_net:1;             //!< fileover.net
    u32 filepost_com:1;             //!< filepost.com
    u32 files_mail_ru:1;            //!< files.mail.ru
    u32 fileshare_in_ua:1;          //!< fileshare.in.ua
    u32 filesmonster_com:1;         //!< filesmonster.com
    u32 filevo_com:1;               //!< filevo.com
    u32 filezup_com:1;              //!< filezup.com
    u32 freakshare_net:1;           //!< freakshare.net
    u32 fshare_vn:1;                //!< fshare.vn
    u32 gaiafile_com:1;             //!< gaiafile.com
    u32 gigapeta_com:1;             //!< gigapeta.com
    u32 gotoupload_com:1;           //!< gotoupload.com
    u32 hellshare_com:1;            //!< hellshare.com
    u32 hitfile_net:1;              //!< hitfile.net
    u32 hulkshare_com:1;            //!< hulkshare.com
    u32 hyperfileshare_com:1;       //!< hyperfileshare.com
    u32 i_filez_com:1;              //!< i-filez.com
    u32 ifile_it:1;                 //!< ifile.it
    u32 kewlshare_com:1;            //!< kewlshare.com
    u32 letitbit_net:1;             //!< letitbit.net
    u32 loadfiles_in:1;             //!< loadfiles.in
    u32 megafree_kz:1;              //!< megafree.kz
    u32 megarapid_eu:1;             //!< megarapid.eu
    u32 megashare_vnn_vn:1;         //!< megashare.vnn.vn
    u32 midupload_com:1;            //!< midupload.com
    u32 multishare_cz:1;            //!< multishare.cz
    u32 netuploaded_com:1;          //!< netuploaded.com
    u32 oron_com:1;                 //!< oron.com
    u32 przeklej_pl:1;              //!< przeklej.pl
    u32 putshare_com:1;             //!< putshare.com
    u32 qshare_com:1;               //!< qshare.com
    u32 quickshare_cz:1;            //!< quickshare.cz
    u32 rapidshark_pl:1;            //!< rapidshark.pl
    u32 scribd_com:1;               //!< scribd.com
    u32 share_online_bz:1;          //!< share-online.bz
    u32 share_rapid_cz:1;           //!< share-rapid.cz
    u32 shragle_com:1;              //!< shragle.com
    u32 storage_to:1;               //!< storage.to
    u32 terafiles_net:1;            //!< terafiles.net
    u32 tunabox_net:1;              //!< tunabox.net
    u32 turbobit_net:1;             //!< turbobit.net
    u32 ugotfile_com:1;             //!< ugotfile.com
    u32 uloz_to:1;                  //!< uloz.to
    u32 unibytes_com:1;             //!< unibytes.com
    u32 unlimit_co_il:1;            //!< unlimit.co.il
    u32 up_4share_vn:1;             //!< up.4share.vn
    u32 upload_com_ua:1;            //!< upload.com.ua
    u32 uploadbox_com:1;            //!< uploadbox.com
    u32 uploader_pl:1;              //!< uploader.pl
    u32 uploadfloor_com:1;          //!< uploadfloor.com
    u32 uploadstation_com:1;        //!< uploadstation.com
    u32 upnito_sk:1;                //!< upnito.sk
    u32 usershare_net:1;            //!< usershare.net
    u32 videobb_com:1;              //!< videobb.com
    u32 wupload_com:1;              //!< wupload.com
    u32 x7_to:1;                    //!< x7.to
    u32 yunfile_to:1;               //!< yunfile.to
    u32 zomgupload_to:1;            //!< zomgupload.to
    u32 ziddu_com:1;                //!< ziddu.com
    u32 _1_upload_com:1;            //!< 1-upload.com
    u32 _1_clickshare_com:1;        //!< 1-clickshare.com
    u32 _123upload_pl:1;            //!< 123upload.pl
    u32 _139pan_com:1;              //!< 139pan.com
    u32 _163pan_com:1;              //!< 163pan.com
    u32 _2shared_com:1;             //!< 2shared.com
    u32 _4share_ws:1;               //!< 4share.ws
    u32 _4us_to:1;                  //!< 4us.to
    u32 alldrives_ge:1;             //!< alldrives.ge
    u32 allshares_ge:1;             //!< allshares.ge
    u32 annonhost_net:1;            //!< annonhost.net
    u32 boosterking_com:1;          //!< boosterking.com
    u32 cobrashare_sk:1;            //!< cobrashare.sk
    u32 coolshare_cz:1;             //!< coolshare.cz
    u32 crocko_com:1;               //!< crocko.com
    u32 cum_com:1;                  //!< cum.com
    u32 eyvx_com:1;                 //!< eyvx.com
    u32 filearn_com:1;              //!< filearn.com
    u32 filejungle_com:1;           //!< filejungle.com
    u32 filemaze_ws:1;              //!< filemaze.ws
    u32 filesflash_com:1;           //!< filesflash.com
    u32 freespace_by:1;             //!< freespace.by
    u32 fsx_hu:1;                   //!< fsx.hu
    u32 jakfile_com:1;              //!< jakfile.com
    u32 jumbofiles_com:1;           //!< jumbofiles.com
    u32 kickload_com:1;             //!< kickload.com
    u32 missupload_com:1;           //!< missupload.com
    u32 movreel_com:1;              //!< movreel.com
    u32 platinshare_com:1;          //!< platinshare.com
    u32 sanupload_com:1;            //!< sanupload.com
    u32 shareflare_net:1;           //!< shareflare.net
    u32 u_115_com:1;                //!< u.115.com
    u32 uploadc_com:1;              //!< uploadc.com
    u32 uploadking_com:1;           //!< uploadking.com
    u32 uptobox_com:1;              //!< uptobox.com
    u32 filestube_com:1;            //!< filestube.com
    u32 gamefront_com:1;            //!< gamefront.com
    u32 megaporn_com:1;             //!< megaporn.com
    u32 filesonic_in:1;             //!< filesonic.in
    u32 turbobit_ru:1;              //!< turbobit.ru
    u32 usenet:1;                   //!< Usenet
    u32 ftp:1;                      //!< FTP
    u32 filetopia:1;                //!< Filetopia
    u32 manolito:1;                 //!< Manolito
    u32 imesh:1;                    //!< iMesh
    u32 pando:1;                    //!< Pando
    u32 sopcast:1;                  //!< SOPCAST
    u32 tvuplayer:1;                //!< TVUPLAYER
    u32 ppstream:1;                 //!< PPSTREAM
    u32 pplive:1;                   //!< PPLIVE
    u32 zattoo:1;                   //!< ZATTOO
    u32 qq:1;                       //!< QQ
    u32 qqlive:1;                   //!< QQLive
    u32 feidian:1;                  //!< Feidian
    u32 popo:1;                     //!< POPO
    u32 thunder:1;                  //!< Thunder/Webthunder
    u32 uusee:1;                    //!< UUSEE
    u32 vnc:1;                      //!< VNC
    u32 steam:1;                    //!< Steam
    u32 hl2:1;                      //!< Halflife2
    u32 softether:1;                //!< SoftEthernet
    u32 telnet:1;                   //!< Telnet
    u32 off:1;                      //!< OFF
    u32 tor:1;                      //!< TOR
    u32 worldofwarcraft:1;          //!< World of Warcraft
    u32 hamachi:1;                  //!< HamachiVPN
    u32 skinny:1;                   //!< Skinny
    u32 citrix:1;                   //!< Citrix
    u32 paltalk:1;                  //!< Paltalk
    u32 quake:1;                    //!< Quake
    u32 secondlife:1;               //!< Second Life
    u32 battlefield:1;              //!< Battlefield
    u32 pcanywhere:1;               //!< PCAnywhere
    u32 icecast:1;                  //!< Icecast
    u32 shoutcast:1;                //!< Shoutcast
    u32 qqgame:1;                   //!< QQGame
    u32 veohtv:1;                   //!< VeohTV
    u32 openft:1;                   //!< OpenFT
    u32 pandora:1;                  //!< Pandora
    u32 ipp:1;                      //!< IPP
    u32 warcraft3:1;                //!< WARCRAFT3
    u32 oovoo:1;                    //!< ooVoo
    u32 google_talk:1;              //!< Google Talk
    u32 iskoot:1;                   //!< Iskoot
    u32 fring:1;                    //!< Fring
    u32 iptv:1;                     //!< IPTV
    u32 yourfreedom:1;              //!< YourFreedom Tunnel
    u32 voipswitchvoiptunnel:1;     //!< VoipSwitch VoIP Tunnel
    u32 meebo:1;                    //!< MEEBO
    u32 funshion:1;                 //!< Funshion
    u32 aimini:1;                   //!< Aimini
    u32 clubpenguin:1;              //!< ClubPenguin
    u32 florensia:1;                //!< Florensia
    u32 teamspeak:1;                //!< TeamSpeak
    u32 maplestory:1;               //!< MapleStory
    u32 osh:1;                      //!< Octoshape
    u32 ps3:1;                      //!< PS3
    u32 dofus:1;                    //!< Dofus
    u32 fiesta:1;                   //!< Fiesta
    u32 splashfighter:1;            //!< SplashFighter
    u32 activesync:1;               //!< Activesync
    u32 nimbuzz:1;                  //!< NIMBUZZ
    u32 crossfire:1;                //!< CrossFire
    u32 wapwsp:1;                   //!< WAP-WSP
    u32 guildwars:1;                //!< Guildwars
    u32 armagetron:1;               //!< Armagetron
    u32 rfactor:1;                  //!< rFactor
    u32 teamviewer:1;               //!< TeamViewer
    u32 gamekit:1;                  //!< GameKit
    u32 ultrabac:1;                 //!< UltraBac
    u32 spotify:1;                  //!< Spotify
    u32 implus:1;                   //!< IMplus
    u32 antsp2p:1;                  //!< ANtsP2P
    u32 ultrasurf:1;                //!< UltraSurf
    u32 viber:1;                    //!< Viber
    u32 tango:1;                    //!< Tango
    u32 iplayer:1;                  //!< iPlayer
    u32 operamini:1;                //!< OperaMini
    u32 bolt:1;                     //!< BOLT
    u32 scydo:1;                    //!< Scydo
    u32 whatsapp:1;                 //!< WhatsApp
    u32 webex:1;                    //!< Webex
    u32 netflix:1;                  //!< NetFlix
    u32 mojo:1;                     //!< Mojo
    u32 imo:1;                      //!< IMO
    u32 citrixgoto:1;               //!< CitrixGoTo
    u32 ficall:1;                   //!< FiCall
    u32 comodounite:1;              //!< ComodoUnite
    u32 ventrilo:1;                 //!< Ventrilo
    u32 mypeople:1;                 //!< MyPeople
    u32 ebuddy:1;                   //!< eBuddy
    u32 adobeconnect:1;             //!< AdobeConnect
    u32 jap:1;                      //!< JAP
    u32 wuala:1;                    //!< Wuala
    u32 webdav:1;                   //!< WebDAV
    u32 lync:1;                     //!< Lync
    u32 audiogalaxy:1;              //!< Audiogalaxy
    u32 mig33:1;                    //!< Mig33
    u32 httptunnel:1;               //!< HTTPTunnel
    u32 rhapsody:1;                 //!< Rhapsody
    u32 webqq:1;                    //!< WebQQ
    u32 pdproxy:1;                  //!< PDProxy
    u32 cyberghost:1;               //!< CyberGhost
    u32 google_cloud:1;             //!< google_cloud
    u32 google_drive:1;             //!< google_drive
    u32 google_docs:1;              //!< google_docs
    u32 google_plus:1;              //!< google_plus
    u32 oracledb:1;                 //!< Oracle Database
    u32 itv:1;                      //!< ITV
    u32 demand5:1;                  //!< Demand 5
    u32 rsvp:1;                     //!< RSVP
    u32 channel4od:1;               //!< Channel 4oD
    u32 lotusnotes:1;               //!< Lotus Notes
    u32 poisonivy:1;                //!< Poison Ivy
    u32 hidrive:1;                  //!< HiDrive
    u32 wechat:1;                   //!< WeChat
    u32 myvideo:1;                  //!< MyVideo
    u32 kik:1;                      //!< Kik Messenger
    u32 line:1;                     //!< Line
    u32 iperf:1;                    //!< Iperf
    u32 osupdate:1;                 //!< OS update
    u32 hike:1;                     //!< Hike Messenger
    u32 didi:1;                     //!< DiDi
    u32 idrive:1;                   //!< IDrive
    u32 spreecast:1;                //!< Spreecast
    u32 simfy:1;                    //!< Simfy
    u32 dota2:1;                    //!< Dota 2
    u32 qvod:1;                     //!< QVOD
    u32 hulu:1;                     //!< Hulu
    u32 msexchange:1;               //!< Microsoft Exchange
    u32 msnav:1;                    //!< Microsoft Dynamics NAV
    u32 fuze:1;                     //!< Fuze Meeting
    u32 kakaotalk:1;                //!< kakaotalk
    u32 destiny:1;                  //!< Destiny
    u32 vyprvpn:1;                  //!< VyprVPN
    u32 threema:1;                  //!< Threema
    u32 ntlm:1;                     //!< NTLM
    u32 twitch:1;                   //!< Twitch
    u32 wowza:1;                    //!< Wowza
    u32 runtastic:1;                //!< Runtastic
    u32 telegram:1;                 //!< Telegram
    u32 streetvoice:1;              //!< StreetVoice
    u32 duokan:1;                   //!< Duokan
    u32 mei_lu:1;                   //!< Mei Lu
    u32 skout:1;                    //!< Skout
    u32 playtales:1;                //!< PlayTales
    u32 gameofwar:1;                //!< Game of War
    u32 fetnet:1;                   //!< FETnet
    u32 fbs:1;                      //!< Fubon E-Broker
    u32 national_baseball:1;        //!< National Baseball
    u32 pinkfong:1;                 //!< PinkFong
    u32 kollect_book:1;             //!< Kollect Book
    u32 sptg_tv:1;                  //!< SPTG TV
    u32 ciaomobile_hdtv:1;          //!< Ciaomobile HDTV
    u32 skyking:1;                  //!< Skyking
    u32 moves:1;                    //!< MOVES
    u32 path:1;                     //!< Path
    u32 aowe:1;                     //!< Age of Warring Empire
    u32 iwow_systex:1;              //!< iWow systex
    u32 _9ku:1;                     //!< 9ku
    u32 nexttv:1;                   //!< Nexttv
    u32 syncplicity1;               //!< Syncplicity
    u32 realma:1;                   //!< RealMa
    u32 yuanta_web:1;               //!< Yuanata Web
    u32 hinet:1;                    //!< HiNet
    u32 mycard:1;                   //!< MyCard
    u32 kono:1;                     //!< kono
    u32 speakaboos:1;               //!< Speakaboos
    u32 duo_duo:1;                  //!< Duo Duo
    u32 wealth_god:1;               //!< Wealth God
    u32 ileader:1;                  //!< iLeader
    u32 three_bamboo:1;             //!< Three Bamboo
    u32 taaze:1;                    //!< Taaze
    u32 audiko:1;                   //!< Audiko
    u32 pubu_bookbuffet:1;          //!< pubu bookbuffet
    u32 mitake:1;                   //!< Mitake
    u32 hyread:1;                   //!< hyread
    u32 disney_storytime:1;         //!< Disney Storytime
    u32 qualys:1;                   //!< Qualys
    u32 constant_contact:1;         //!< Constant Contact
    u32 rally:1;                    //!< Rally
    u32 maginetv:1;                 //!< Magine TV
    u32 intralinks:1;               //!< IntraLinks
    u32 liveperson:1;               //!< LivePerson
    u32 speedtest:1;                //!< Speedtest
    u32 bluejeans:1;                //!< BlueJeans
    u32 apple_music:1;              //!< Apple Music
    u32 naver:1;                    //!< Naver
    u32 booking_com:1;              //!< Booking.com
    u32 cnn:1;                      //!< CNN
    u32 periscope:1;                //!< Periscope
    u32 payeasy:1;                  //!< PayEasy
    u32 line_rangers:1;             //!< Line Ranger
    u32 ios_app_store:1;            //!< iOS App Store
    u32 myvideo_tw:1;               //!< MyVideo TW
    u32 king_gaming:1;              //!< King.com gaming
    u32 candy_crush:1;              //!< Candy Crush Saga
    u32 candy_crush_soda:1;         //!< Candy Crush Soda Saga
    u32 bubble_with:1;              //!< Bubble Witch
    u32 farm_hero:1;                //!< Farm Hero
    u32 playstation:1;              //!< PlayStation
    u32 google_play:1;              //!< google_play
    u32 supercell:1;                //!< Supercell
    u32 clash_of_clans:1;           //!< Clash of Clans
    u32 boom_beach:1;               //!< Boom Beach
    u32 hay_day:1;                  //!< Hay Day
    u32 windows_store:1;            //!< WindowsPhone Store
    u32 skype_for_business:1;       //!< Skype for Business

    /* following field is added just for padding reasons and does not carry a value */
    u32 padding:(32 - (PACE2_APPLICATIONS_COUNT % 32));
} PACE2_applications_struct;

#define PACE2_APPLICATIONS_SHORT_STRS \
    "ukn",\
    "facebook",\
    "magicjack",\
    "itunes",\
    "myspace",\
    "facetime",\
    "truphone",\
    "twitter",\
    "xbox",\
    "realmedia",\
    "google_mail",\
    "goober",\
    "icloud",\
    "ubuntuone",\
    "dropbox",\
    "yuilop",\
    "imessage",\
    "gotomypc",\
    "gotomeeting",\
    "windows_azure",\
    "amazon_cloud",\
    "dailymotion",\
    "deezer",\
    "grooveshark",\
    "sudaphone",\
    "office365",\
    "cntv",\
    "sinatv",\
    "youtube",\
    "voipswitch",\
    "zynga",\
    "crimecity",\
    "modernwar",\
    "vippie",\
    "box",\
    "skydrive",\
    "adobe_creative_cloud",\
    "linkedin",\
    "orkut",\
    "hi5",\
    "soribada",\
    "zoho_work_online",\
    "hotmail_webmail",\
    "instagram",\
    "sugarsync",\
    "wickr",\
    "tigertext",\
    "vibe",\
    "enlegion",\
    "voxer",\
    "lovefilm",\
    "friendster",\
    "burner",\
    "flickr",\
    "live_com",\
    "icq_webchat",\
    "redtube",\
    "evernote",\
    "spreed",\
    "textplus",\
    "xvideos",\
    "snapchat",\
    "youku",\
    "mymusic_tw",\
    "renren",\
    "yelp",\
    "amazon_shop",\
    "youporn",\
    "ebay",\
    "pornhub",\
    "spideroak",\
    "adrive",\
    "tumblr",\
    "xing",\
    "google_play_music",\
    "vimeo",\
    "salesforce",\
    "itunes_radio",\
    "sina_weibo",\
    "forfone",\
    "livejasmin",\
    "jingdong",\
    "lastfm",\
    "ims",\
    "baidu",\
    "taobao",\
    "watchever",\
    "ttpod",\
    "360mobile",\
    "pinterest",\
    "vine",\
    "net2phone",\
    "foursquare",\
    "ilive_to",\
    "mega",\
    "doook",\
    "vbulletin",\
    "cloudme",\
    "yikyak",\
    "redmine",\
    "iheartradio",\
    "avira-antivir",\
    "norton-antivir",\
    "kaspersky-antivir",\
    "avg-antivir",\
    "soundcloud",\
    "rdio",\
    "amazon-prime-music",\
    "runkeeper",\
    "mybook",\
    "nikeplus",\
    "magv",\
    "magv-kids",\
    "dota-legend",\
    "letv",\
    "my-fitness-pal",\
    "sohu",\
    "1kxun",\
    "tvbs",\
    "xnxx",\
    "ctitv",\
    "endomondo",\
    "timely-tv",\
    "workout-trainer",\
    "mapmyrun",\
    "king-of-pirates",\
    "tudou",\
    "bit",\
    "edk",\
    "kazaa",\
    "gnu",\
    "directconnect",\
    "apple",\
    "soul",\
    "ares",\
    "freenet",\
    "mute",\
    "skype",\
    "msn",\
    "yahoo",\
    "vonage",\
    "oscar",\
    "gadugadu",\
    "mplus",\
    "irc",\
    "sling",\
    "vcast",\
    "4shared.com",\
    "adrive.com",\
    "badongo.com",\
    "badongo.net",\
    "bestsharing.com",\
    "bigfilez.com",\
    "chinamofile.com",\
    "data.hu",\
    "depositfiles.com",\
    "easy-share.com",\
    "fast-load.net",\
    "fast-share.com",\
    "file-upload.net",\
    "file-upload.to",\
    "filearchiv.ru",\
    "filebase.to",\
    "filecloud.com",\
    "filefactory.com",\
    "filefront.com",\
    "fileho.com",\
    "filehost.tv",\
    "filepost.ru",\
    "filer.net",\
    "files-upload.com",\
    "files.to",\
    "filesafe.to",\
    "filesend.net",\
    "fileupyours.com",\
    "ftp2share.com",\
    "gigasize.com",\
    "gigeshare.com",\
    "hostggg.com",\
    "hotfile.com",\
    "ifolder.ru",\
    "keepmyfile.com",\
    "leteckaposta.cz",\
    "live-share.com",\
    "livedepot.net",\
    "load.to",\
    "massmirror.com",\
    "mediafire.com",\
    "megarotic.com",\
    "megashare.com",\
    "megashares.com",\
    "megaupload.com",\
    "mofile.com",\
    "mofile.net",\
    "mytempdir.com",\
    "netload.in",\
    "odsiebie.najlepsze.net",\
    "quicksharing.com",\
    "rapidshare.com",\
    "rapidshare.de",\
    "rapidupload.com",\
    "savefile.com",\
    "sendmefile.com",\
    "sendspace.com",\
    "sharebase.to",\
    "sharebee.com",\
    "sharebig.com",\
    "sharebigfile.com",\
    "sharebigflie.com",\
    "simpleupload.net",\
    "speedshare.org",\
    "turboupload.com",\
    "ultrashare.de",\
    "up-file.com",\
    "uploaded.to",\
    "uploading.com",\
    "uploadingit.com",\
    "uploadpower.com",\
    "uploadyourfiles.de",\
    "vip-file.com",\
    "wiiupload.net",\
    "yourfilehost.com",\
    "yourfiles.biz",\
    "youtube.com",\
    "zshare.net",\
    "4shared.vn",\
    "mega.1280.com",\
    "megashare.vn",\
    "fileserve.com",\
    "filesonic.com",\
    "1-upload.to",\
    "1fichier.com",\
    "4fastfile.com",\
    "10upload.com",\
    "1clickshare.net",\
    "filedude.com",\
    "asixfiles.com",\
    "banashare.com",\
    "biggerupload.com",\
    "bitshare.com",\
    "cash-file.net",\
    "cramit.in",\
    "czshare.com",\
    "data-loading.com",\
    "dataport.cz",\
    "datei.to",\
    "downupload.com",\
    "easybytez.com",\
    "edisk.cz",\
    "enterupload.com",\
    "euroshare.eu",\
    "extabit.com",\
    "fastfileshare.com.ar",\
    "fik1.com",\
    "file2upload.net",\
    "fileape.com",\
    "fileflyer.com",\
    "filefrog.com",\
    "filehook.com",\
    "fileover.net",\
    "filepost.com",\
    "files.mail.ru",\
    "fileshare.in.ua",\
    "filesmonster.com",\
    "filevo.com",\
    "filezup.com",\
    "freakshare.net",\
    "fshare.vn",\
    "gaiafile.com",\
    "gigapeta.com",\
    "gotoupload.com",\
    "hellshare.com",\
    "hitfile.net",\
    "hulkshare.com",\
    "hyperfileshare.com",\
    "i-filez.com",\
    "ifile.it",\
    "kewlshare.com",\
    "letitbit.net",\
    "loadfiles.in",\
    "megafree.kz",\
    "megarapid.eu",\
    "megashare.vnn.vn",\
    "midupload.com",\
    "multishare.cz",\
    "netuploaded.com",\
    "oron.com",\
    "przeklej.pl",\
    "putshare.com",\
    "qshare.com",\
    "quickshare.cz",\
    "rapidshark.pl",\
    "scribd.com",\
    "share-online.bz",\
    "share-rapid.cz",\
    "shragle.com",\
    "storage.to",\
    "terafiles.net",\
    "tunabox.net",\
    "turbobit.net",\
    "ugotfile.com",\
    "uloz.to",\
    "unibytes.com",\
    "unlimit.co.il",\
    "up.4share.vn",\
    "upload.com.ua",\
    "uploadbox.com",\
    "uploader.pl",\
    "uploadfloor.com",\
    "uploadstation.com",\
    "upnito.sk",\
    "usershare.net",\
    "videobb.com",\
    "wupload.com",\
    "x7.to",\
    "yunfile.to",\
    "zomgupload.to",\
    "ziddu.com",\
    "1-upload.com",\
    "1-clickshare.com",\
    "123upload.pl",\
    "139pan.com",\
    "163pan.com",\
    "2shared.com",\
    "4share.ws",\
    "4us.to",\
    "alldrives.ge",\
    "allshares.ge",\
    "annonhost.net",\
    "boosterking.com",\
    "cobrashare.sk",\
    "coolshare.cz",\
    "crocko.com",\
    "cum.com",\
    "eyvx.com",\
    "filearn.com",\
    "filejungle.com",\
    "filemaze.ws",\
    "filesflash.com",\
    "freespace.by",\
    "fsx.hu",\
    "jakfile.com",\
    "jumbofiles.com",\
    "kickload.com",\
    "missupload.com",\
    "movreel.com",\
    "platinshare.com",\
    "sanupload.com",\
    "shareflare.net",\
    "u.115.com",\
    "uploadc.com",\
    "uploadking.com",\
    "uptobox.com",\
    "filestube.com",\
    "gamefront.com",\
    "megaporn.com",\
    "filesonic.in",\
    "turbobit.ru",\
    "usenet",\
    "ftp",\
    "filetopia",\
    "manolito",\
    "imesh",\
    "pando",\
    "sopcast",\
    "tvuplayer",\
    "ppstream",\
    "pplive",\
    "zattoo",\
    "qq",\
    "qqlive",\
    "feidian",\
    "popo",\
    "thunder",\
    "uusee",\
    "vnc",\
    "steam",\
    "hl2",\
    "softether",\
    "telnet",\
    "off",\
    "tor",\
    "worldofwarcraft",\
    "hamachi",\
    "skinny",\
    "citrix",\
    "paltalk",\
    "quake",\
    "secondlife",\
    "battlefield",\
    "pcanywhere",\
    "icecast",\
    "shoutcast",\
    "qqgame",\
    "veohtv",\
    "openft",\
    "pandora",\
    "ipp",\
    "warcraft3",\
    "oovoo",\
    "google_talk",\
    "iskoot",\
    "fring",\
    "iptv",\
    "yourfreedom",\
    "voipswitchvoiptunnel",\
    "meebo",\
    "funshion",\
    "aimini",\
    "clubpenguin",\
    "florensia",\
    "teamspeak",\
    "maplestory",\
    "osh",\
    "ps3",\
    "dofus",\
    "fiesta",\
    "splashfighter",\
    "activesync",\
    "nimbuzz",\
    "crossfire",\
    "wapwsp",\
    "guildwars",\
    "armagetron",\
    "rfactor",\
    "teamviewer",\
    "gamekit",\
    "ultrabac",\
    "spotify",\
    "implus",\
    "antsp2p",\
    "ultrasurf",\
    "viber",\
    "tango",\
    "iplayer",\
    "operamini",\
    "bolt",\
    "scydo",\
    "whatsapp",\
    "webex",\
    "netflix",\
    "mojo",\
    "imo",\
    "citrixgoto",\
    "ficall",\
    "comodounite",\
    "ventrilo",\
    "mypeople",\
    "ebuddy",\
    "adobeconnect",\
    "jap",\
    "wuala",\
    "webdav",\
    "lync",\
    "audiogalaxy",\
    "mig33",\
    "httptunnel",\
    "rhapsody",\
    "webqq",\
    "pdproxy",\
    "cyberghost",\
    "google_cloud",\
    "google_drive",\
    "google_docs",\
    "google_plus",\
    "oracledb",\
    "itv",\
    "demand5",\
    "rsvp",\
    "channel4od",\
    "lotusnotes",\
    "poisonivy",\
    "hidrive",\
    "wechat",\
    "myvideo",\
    "kik",\
    "line",\
    "iperf",\
    "osupdate",\
    "hike",\
    "didi",\
    "idrive",\
    "spreecast",\
    "simfy",\
    "dota2",\
    "qvod",\
    "hulu",\
    "msexchange",\
    "msnav",\
    "fuze",\
    "kakaotalk",\
    "destiny",\
    "vyprvpn",\
    "threema",\
    "ntlm",\
    "twitch",\
    "wowza",\
    "runtastic",\
    "telegram",\
    "streetvoice",\
    "duokan",\
    "mei-lu",\
    "skout",\
    "playtales",\
    "gameofwar",\
    "fetnet",\
    "fbs",\
    "national-baseball",\
    "pinkfong",\
    "kollect-book",\
    "sptg-tv",\
    "ciaomobile-hdtv",\
    "skyking",\
    "moves",\
    "path",\
    "aowe",\
    "iwow-systex",\
    "9ku",\
    "nexttv",\
    "syncplicity",\
    "realma",\
    "yuanta-web",\
    "hinet",\
    "mycard",\
    "kono",\
    "speakaboos",\
    "duo-duo",\
    "wealth-god",\
    "ileader",\
    "three-bamboo",\
    "taaze",\
    "audiko",\
    "pubu-bookbuffet",\
    "mitake",\
    "hyread",\
    "disney-storytime",\
    "qualys",\
    "constant-contact",\
    "rally",\
    "maginetv",\
    "intralinks",\
    "liveperson",\
    "speedtest",\
    "bluejeans",\
    "apple-music",\
    "naver",\
    "booking-com",\
    "cnn",\
    "periscope",\
    "payeasy",\
    "line-rangers",\
    "ios-app-store",\
    "myvideo-tw",\
    "King Gaming",\
    "candy-crush",\
    "candy-crush-soda",\
    "bubble-witch",\
    "farm-hero",\
    "playstation",\
    "google_play",\
    "supercell",\
    "clash-of-clans",\
    "boom-beach",\
    "hay-day",\
    "windows-store",\
    "skype-for-business"

#define PACE2_APPLICATIONS_LONG_STRS \
    "unknown",\
    "Facebook",\
    "magicJack",\
    "iTunes",\
    "MySpace",\
    "FaceTime",\
    "Truphone",\
    "Twitter",\
    "XBOX gaming console",\
    "RealMedia",\
    "Google Mail",\
    "Goober",\
    "iCloud",\
    "Ubuntu One",\
    "Dropbox",\
    "Yuilop",\
    "iMessage",\
    "GoToMyPC",\
    "GoToMeeting",\
    "Windows Azure",\
    "Amazon Cloud",\
    "Dailymotion",\
    "Deezer",\
    "Grooveshark",\
    "SUDA Phone",\
    "Office 365",\
    "CNTV",\
    "SINATV",\
    "YouTube",\
    "VoipSwitch",\
    "Zynga",\
    "Crime City",\
    "Modern War",\
    "Vippie",\
    "Box",\
    "Skydrive",\
    "Adobe Creative Cloud",\
    "LinkedIn",\
    "Orkut",\
    "hi5",\
    "Soribada",\
    "Zoho Work Online",\
    "Hotmail",\
    "Instagram",\
    "SugarSync",\
    "Wickr",\
    "TigerText",\
    "Vibe",\
    "enLegion",\
    "Voxer",\
    "LOVEFiLM",\
    "Friendster",\
    "Burner",\
    "Flickr",\
    "live.com",\
    "ICQ Webchat",\
    "RedTube",\
    "Evernote",\
    "Spreed",\
    "textPlus",\
    "Xvideos",\
    "Snapchat",\
    "Youku",\
    "MyMusic",\
    "Renren",\
    "Yelp",\
    "Amazon shopping",\
    "YouPorn",\
    "eBay",\
    "PornHub",\
    "Spideroak",\
    "Adrive",\
    "tumblr",\
    "XING",\
    "Google Play Music",\
    "Vimeo",\
    "Salesforce",\
    "iTunes Radio",\
    "Sina Weibo",\
    "Forfone",\
    "LiveJasmin",\
    "Jingdong",\
    "Last.fm",\
    "IP Multimedia Subsystem",\
    "Baidu",\
    "Taobao",\
    "Watchever",\
    "TTPod",\
    "360 Mobile Security",\
    "Pinterest",\
    "Vine",\
    "Net2Phone",\
    "Foursquare",\
    "iLive.to",\
    "MEGA",\
    "Doook",\
    "vBulletin",\
    "CloudMe",\
    "Yik Yak",\
    "Redmine",\
    "iHeartRadio",\
    "Avira Antivirus",\
    "Norton Antivirus",\
    "Kaspersky Antivirus",\
    "AVG Antivirus",\
    "SoundCloud",\
    "Rdio",\
    "Amazon Prime Music",\
    "RunKeeper",\
    "myBook",\
    "Nike Plus",\
    "MagV",\
    "MagV Kids",\
    "Dota Legend",\
    "LeTV",\
    "MyFitnessPal",\
    "Sohu",\
    "1kxun",\
    "TVBS",\
    "XNXX",\
    "CtiTV",\
    "Endomondo",\
    "Timely TV",\
    "Workout Trainer",\
    "MapMyRun",\
    "King of Pirates",\
    "Tudou",\
    "BitTorrent",\
    "eDonkey",\
    "KaZaa/Fasttrack",\
    "Gnutella",\
    "DirectConnect",\
    "AppleJuice",\
    "Soulseek",\
    "Ares",\
    "Freenet",\
    "Mute",\
    "Skype",\
    "MSN",\
    "Yahoo",\
    "vonage",\
    "Oscar",\
    "Gadu-Gadu",\
    "MPlus",\
    "IRC",\
    "Slingbox",\
    "Vcast",\
    "4shared.com",\
    "adrive.com",\
    "badongo.com",\
    "badongo.net",\
    "bestsharing.com",\
    "bigfilez.com",\
    "chinamofile.com",\
    "data.hu",\
    "depositfiles.com",\
    "easy-share.com",\
    "fast-load.net",\
    "fast-share.com",\
    "file-upload.net",\
    "file-upload.to",\
    "filearchiv.ru",\
    "filebase.to",\
    "filecloud.com",\
    "filefactory.com",\
    "filefront.com",\
    "fileho.com",\
    "filehost.tv",\
    "filepost.ru",\
    "filer.net",\
    "files-upload.com",\
    "files.to",\
    "filesafe.to",\
    "filesend.net",\
    "fileupyours.com",\
    "ftp2share.com",\
    "gigasize.com",\
    "gigeshare.com",\
    "hostggg.com",\
    "hotfile.com",\
    "ifolder.ru",\
    "keepmyfile.com",\
    "leteckaposta.cz",\
    "live-share.com",\
    "livedepot.net",\
    "load.to",\
    "massmirror.com",\
    "mediafire.com",\
    "megarotic.com",\
    "megashare.com",\
    "megashares.com",\
    "megaupload.com",\
    "mofile.com",\
    "mofile.net",\
    "mytempdir.com",\
    "netload.in",\
    "odsiebie.najlepsze.net",\
    "quicksharing.com",\
    "rapidshare.com",\
    "rapidshare.de",\
    "rapidupload.com",\
    "savefile.com",\
    "sendmefile.com",\
    "sendspace.com",\
    "sharebase.to",\
    "sharebee.com",\
    "sharebig.com",\
    "sharebigfile.com",\
    "sharebigflie.com",\
    "simpleupload.net",\
    "speedshare.org",\
    "turboupload.com",\
    "ultrashare.de",\
    "up-file.com",\
    "uploaded.to",\
    "uploading.com",\
    "uploadingit.com",\
    "uploadpower.com",\
    "uploadyourfiles.de",\
    "vip-file.com",\
    "wiiupload.net",\
    "yourfilehost.com",\
    "yourfiles.biz",\
    "youtube.com",\
    "zshare.net",\
    "4shared.vn",\
    "mega.1280.com",\
    "megashare.vn",\
    "fileserve.com",\
    "filesonic.com",\
    "1-upload.to",\
    "1fichier.com",\
    "4fastfile.com",\
    "10upload.com",\
    "1clickshare.net",\
    "filedude.com",\
    "asixfiles.com",\
    "banashare.com",\
    "biggerupload.com",\
    "bitshare.com",\
    "cash-file.net",\
    "cramit.in",\
    "czshare.com",\
    "data-loading.com",\
    "dataport.cz",\
    "datei.to",\
    "downupload.com",\
    "easybytez.com",\
    "edisk.cz",\
    "enterupload.com",\
    "euroshare.eu",\
    "extabit.com",\
    "fastfileshare.com.ar",\
    "fik1.com",\
    "file2upload.net",\
    "fileape.com",\
    "fileflyer.com",\
    "filefrog.com",\
    "filehook.com",\
    "fileover.net",\
    "filepost.com",\
    "files.mail.ru",\
    "fileshare.in.ua",\
    "filesmonster.com",\
    "filevo.com",\
    "filezup.com",\
    "freakshare.net",\
    "fshare.vn",\
    "gaiafile.com",\
    "gigapeta.com",\
    "gotoupload.com",\
    "hellshare.com",\
    "hitfile.net",\
    "hulkshare.com",\
    "hyperfileshare.com",\
    "i-filez.com",\
    "ifile.it",\
    "kewlshare.com",\
    "letitbit.net",\
    "loadfiles.in",\
    "megafree.kz",\
    "megarapid.eu",\
    "megashare.vnn.vn",\
    "midupload.com",\
    "multishare.cz",\
    "netuploaded.com",\
    "oron.com",\
    "przeklej.pl",\
    "putshare.com",\
    "qshare.com",\
    "quickshare.cz",\
    "rapidshark.pl",\
    "scribd.com",\
    "share-online.bz",\
    "share-rapid.cz",\
    "shragle.com",\
    "storage.to",\
    "terafiles.net",\
    "tunabox.net",\
    "turbobit.net",\
    "ugotfile.com",\
    "uloz.to",\
    "unibytes.com",\
    "unlimit.co.il",\
    "up.4share.vn",\
    "upload.com.ua",\
    "uploadbox.com",\
    "uploader.pl",\
    "uploadfloor.com",\
    "uploadstation.com",\
    "upnito.sk",\
    "usershare.net",\
    "videobb.com",\
    "wupload.com",\
    "x7.to",\
    "yunfile.to",\
    "zomgupload.to",\
    "ziddu.com",\
    "1-upload.com",\
    "1-clickshare.com",\
    "123upload.pl",\
    "139pan.com",\
    "163pan.com",\
    "2shared.com",\
    "4share.ws",\
    "4us.to",\
    "alldrives.ge",\
    "allshares.ge",\
    "annonhost.net",\
    "boosterking.com",\
    "cobrashare.sk",\
    "coolshare.cz",\
    "crocko.com",\
    "cum.com",\
    "eyvx.com",\
    "filearn.com",\
    "filejungle.com",\
    "filemaze.ws",\
    "filesflash.com",\
    "freespace.by",\
    "fsx.hu",\
    "jakfile.com",\
    "jumbofiles.com",\
    "kickload.com",\
    "missupload.com",\
    "movreel.com",\
    "platinshare.com",\
    "sanupload.com",\
    "shareflare.net",\
    "u.115.com",\
    "uploadc.com",\
    "uploadking.com",\
    "uptobox.com",\
    "filestube.com",\
    "gamefront.com",\
    "megaporn.com",\
    "filesonic.in",\
    "turbobit.ru",\
    "Usenet",\
    "FTP",\
    "Filetopia",\
    "Manolito",\
    "iMesh",\
    "Pando",\
    "SOPCAST",\
    "TVUPLAYER",\
    "PPSTREAM",\
    "PPLIVE",\
    "ZATTOO",\
    "QQ",\
    "QQLive",\
    "Feidian",\
    "POPO",\
    "Thunder/Webthunder",\
    "UUSEE",\
    "VNC",\
    "Steam",\
    "Halflife2",\
    "SoftEthernet",\
    "Telnet",\
    "OFF",\
    "TOR",\
    "World of Warcraft",\
    "HamachiVPN",\
    "Skinny",\
    "Citrix",\
    "Paltalk",\
    "Quake",\
    "Second Life",\
    "Battlefield",\
    "PCAnywhere",\
    "Icecast",\
    "Shoutcast",\
    "QQGame",\
    "VeohTV",\
    "OpenFT",\
    "Pandora",\
    "IPP",\
    "WARCRAFT3",\
    "ooVoo",\
    "Google Talk",\
    "Iskoot",\
    "Fring",\
    "IPTV",\
    "YourFreedom Tunnel",\
    "VoipSwitch VoIP Tunnel",\
    "MEEBO",\
    "Funshion",\
    "Aimini",\
    "ClubPenguin",\
    "Florensia",\
    "TeamSpeak",\
    "MapleStory",\
    "Octoshape",\
    "PS3",\
    "Dofus",\
    "Fiesta",\
    "SplashFighter",\
    "Activesync",\
    "NIMBUZZ",\
    "CrossFire",\
    "WAP-WSP",\
    "Guildwars",\
    "Armagetron",\
    "rFactor",\
    "TeamViewer",\
    "GameKit",\
    "UltraBac",\
    "Spotify",\
    "IMplus",\
    "ANtsP2P",\
    "UltraSurf",\
    "Viber",\
    "Tango",\
    "iPlayer",\
    "OperaMini",\
    "BOLT",\
    "Scydo",\
    "WhatsApp",\
    "Webex",\
    "NetFlix",\
    "Mojo",\
    "IMO",\
    "CitrixGoTo",\
    "FiCall",\
    "ComodoUnite",\
    "Ventrilo",\
    "MyPeople",\
    "eBuddy",\
    "AdobeConnect",\
    "JAP",\
    "Wuala",\
    "WebDAV",\
    "Lync",\
    "Audiogalaxy",\
    "Mig33",\
    "HTTPTunnel",\
    "Rhapsody",\
    "WebQQ",\
    "PDProxy",\
    "CyberGhost",\
    "google_cloud",\
    "google_drive",\
    "google_docs",\
    "google_plus",\
    "Oracle Database",\
    "ITV",\
    "Demand 5",\
    "RSVP",\
    "Channel 4oD",\
    "Lotus Notes",\
    "Poison Ivy",\
    "HiDrive",\
    "WeChat",\
    "MyVideo",\
    "Kik Messenger",\
    "Line",\
    "Iperf",\
    "OS update",\
    "Hike Messenger",\
    "DiDi",\
    "IDrive",\
    "Spreecast",\
    "Simfy",\
    "Dota 2",\
    "QVOD",\
    "Hulu",\
    "Microsoft Exchange",\
    "Microsoft Dynamics NAV",\
    "Fuze Meeting",\
    "kakaotalk",\
    "Destiny",\
    "VyprVPN",\
    "Threema",\
    "NTLM",\
    "Twitch",\
    "Wowza",\
    "Runtastic",\
    "Telegram",\
    "StreetVoice",\
    "Duokan",\
    "Mei Lu",\
    "Skout",\
    "PlayTales",\
    "Game of War",\
    "FETnet",\
    "Fubon E-Broker",\
    "National Baseball",\
    "PinkFong",\
    "Kollect Book",\
    "SPTG TV",\
    "Ciaomobile HDTV",\
    "Skyking",\
    "Moves",\
    "Path",\
    "Age of Warring Empire",\
    "iWow systex",\
    "9ku",\
    "Next TV",\
    "Syncplicity",\
    "RealMa",\
    "Yuanta Web",\
    "HiNet",\
    "MyCard",\
    "Kono",\
    "Speakaboos",\
    "Duo Duo",\
    "Wealth God",\
    "iLeader",\
    "Three Bamboo",\
    "Taaze",\
    "Audiko",\
    "pubu bookbuffet",\
    "Mitake",\
    "Hyread",\
    "Disney Storytime",\
    "Qualys",\
    "Constant Contact",\
    "Rally",\
    "Magine TV",\
    "IntraLinks",\
    "LivePerson",\
    "Speedtest",\
    "BlueJeans",\
    "Apple Music",\
    "Naver",\
    "Booking_com",\
    "CNN",\
    "Periscope",\
    "PayEasy",\
    "Line Rangers",\
    "iOS App Store",\
    "MyVideo TW",\
    "King Gaming",\
    "Candy Crush",\
    "Candy Crush Soda",\
    "Bubble Witch",\
    "Farm Hero",\
    "PlayStation Network",\
    "Google Play",\
    "Supercell",\
    "Clash of Clans",\
    "Boom Beach",\
    "Hay Day",\
    "Windows Store",\
    "Skype for Business"

#endif /* PACE2_APPLICATIONS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
