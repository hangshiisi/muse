/* written by klaus degner, ipoque GmbH
 * klaus.degner@ipoque.com
 */

#ifndef __IPOQUE_API_INCLUDE_FILE__
#error CANNOT INCLUDE THIS .H FILE, INCLUDE IPQ_API.H
#endif

#ifndef __IPQ_PROTOCOLS_DEFAULT_H__
#define __IPQ_PROTOCOLS_DEFAULT_H__

#ifdef __cplusplus
extern "C" {
#endif

	/*************************
	 * The interface variant *
	 *************************/

#include "ipq_config.h"
	
	/********************
	 * Generic settings *
	 ********************/

#define IPOQUE_USE_INTERNAL_FASTPATH

// #define IPOQUE_USE_CITRIX_CONNECTION_TRACKING

// #define IPOQUE_GENERIC_FINAL_STATE_MACHINE

#define IPOQUE_USE_NEW_HASH_TABLE

#define IPOQUE_INTER_DETECTION_MESSAGING

#define IPOQUE_DECAPSULATE_PLAIN_TUNNELS

// #define IPOQUE_ENABLE_DEBUG_MESSAGES

// #define IPOQUE_DEBUG_ENABLE_DETECTION_CALL_TRACKING

// #define IPQ_MEMCHECK_HASH_USER_BUFFER

// #define IPOQUE_INTERNAL_REDZONE_CHECKING

// #define IPQ_TOH_LOCKABLE

// #define IPQ_TOH_LOCKABLE_BRANCH_CONDITION unlikely

#define IPOQUE_DETECTION_SUPPORT_NONLINEAR_PROCESSING

#define IPOQUE_DETECTION_SUPPORT_ASYMETRIC_DETECTION

#define IPOQUE_DETECTION_SUPPORT_IPV6

#define IPOQUE_DETECTION_SUPPORT_UNDETECTED_PROTOCOL_DETECTION

#define IPOQUE_ENABLE_FLOW_OOO_COUNTER

#define IPOQUE_ENABLE_TCP_RETRANSMISSION_COUNTER

#define IPOQUE_DETECTION_MEASURE_TCP_FLOW_LATENCY

// #define IPOQUE_INTEGRATE_DECAPSULATION_CODE

#define IPOQUE_DETECTION_MEASURE_ASYMETRIC_CONNECTION_SETUP

#define IPOQUE_DETECTION_DECODE_SIP_CONNECTIONS

#define IPOQUE_ENABLE_SSL_DECODE

#define IPOQUE_ENABLE_AGGRESSIVE_DETECTION

#define IPOQUE_ENABLE_MIDSTREAM_DETECTION

#define IPOQUE_ENABLE_SEAMLESS_UPGRADE

// #define IPOQUE_ENABLE_CORRELATING_FLOW_ID
// #define IPOQUE_ENABLE_CORRELATING_SIP_FLOW_ID

/*
 * Flow ID correlation support can only be activated in PACE MK2 and higher
 * and if IPOQUE_ENABLE_CORRELATING_FLOW_ID and IPOQUE_ENABLE_CORRELATING_SIP_FLOW_ID are NOT defined
 */
#if defined (IPOQUE_SUPPORT_FLOW_ID_CORRELATION)
#   if defined (IPOQUE_PACE_API_MK1) || defined(IPOQUE_ENABLE_CORRELATING_FLOW_ID) || defined(IPOQUE_ENABLE_CORRELATING_SIP_FLOW_ID)
#       undef IPOQUE_SUPPORT_FLOW_ID_CORRELATION
#       error Flow ID correlation support can only be activated in PACE MK2 (or higher) and if IPOQUE_ENABLE_CORRELATING_FLOW_ID and IPOQUE_ENABLE_CORRELATING_SIP_FLOW_ID are NOT defined
#   endif
#endif

#define IPOQUE_ENABLE_DEFRAG_ENGINE

#define IPOQUE_DETECTION_SUPPORT_CLIENT_SERVER_INDICATION

// #define IPOQUE_USE_INTERNAL_MEMSET_CPY

/* this define was developed especially for MrB. As soon as the PRX
 * supports sub-protocols, the define and all the code inside the define can be deleted.
 */
// #define SPECIAL_MR_B_HACK

#define IPOQUE_PROTOCOL_HISTORY_SIZE 3

#define SKYPE_VOICE_DETECTION

#define IPOQUE_SIP_DETECT_VONAGE

	/*****************************
	 * API MK1 specific features *
	 *****************************/

#ifdef IPOQUE_PACE_API_MK1

#  define IPOQUE_USER_DEFINED_PROTOCOLS


#endif // MK1

	/*****************************
	 * API MK2 specific features *
	 *****************************/

#if defined(IPOQUE_PACE_API_MK2) || defined(IPOQUE_PACE_API_MK3)

#  define IPOQUE_CUSTOM_DEFINED_PROTOCOLS_2_0

#   ifndef PACE_KERNEL_LIB
#       if defined(__linux__) || defined(__FreeBSD__)
#           define IPOQUE_PACE_DYNAMIC_UPGRADE
#       endif
#   endif

#endif // MK2 || MK3

	/*************
	 * Protocols *
	 *************/

#define IPOQUE_PROTOCOL_UNKNOWN           	     0
#define IPOQUE_PROTOCOL_BITTORRENT             	 1
#define IPOQUE_PROTOCOL_EDONKEY                	 2
#define IPOQUE_PROTOCOL_FASTTRACK              	 3
#define IPOQUE_PROTOCOL_GNUTELLA               	 4
#define IPOQUE_PROTOCOL_WINMX                  	 5
#define IPOQUE_PROTOCOL_DIRECTCONNECT          	 6
#define IPOQUE_PROTOCOL_APPLEJUICE             	 7
#define IPOQUE_PROTOCOL_SOULSEEK               	 8
#define IPOQUE_PROTOCOL_ARES                   	 9
#define IPOQUE_PROTOCOL_FREENET                 10
#define IPOQUE_PROTOCOL_MUTE                    11
#define IPOQUE_PROTOCOL_XDCC                    12
#define IPOQUE_PROTOCOL_SKYPE                   13
#define IPOQUE_PROTOCOL_SIP                     14
#define IPOQUE_PROTOCOL_MSN                     15
#define IPOQUE_PROTOCOL_YAHOO                   16
#define IPOQUE_PROTOCOL_OSCAR                   17
#define IPOQUE_PROTOCOL_IRC                     18
#define IPOQUE_PROTOCOL_UNENCRYPED_JABBER       19
#define IPOQUE_PROTOCOL_ORB                     20
#define IPOQUE_PROTOCOL_SLINGBOX                21
#define IPOQUE_PROTOCOL_VCAST                   22
#define IPOQUE_PROTOCOL_HTTP                    23
#define IPOQUE_PROTOCOL_DIRECT_DOWNLOAD_LINK    24
#define IPOQUE_PROTOCOL_MAIL_POP                25
#define IPOQUE_PROTOCOL_MAIL_SMTP               26
#define IPOQUE_PROTOCOL_MAIL_IMAP               27
#define IPOQUE_PROTOCOL_USENET                  28
#define IPOQUE_PROTOCOL_FTP                     29
#define IPOQUE_PROTOCOL_DNS                     30
#define IPOQUE_PROTOCOL_RTSP                    31
#define IPOQUE_PROTOCOL_FILETOPIA               32
#define IPOQUE_PROTOCOL_MANOLITO                33
#define IPOQUE_PROTOCOL_IMESH                   34
#define IPOQUE_PROTOCOL_SSL                     35
#define IPOQUE_PROTOCOL_FLASH                   36
#define IPOQUE_PROTOCOL_MMS                     37
#define IPOQUE_PROTOCOL_MPEG                    38
#define IPOQUE_PROTOCOL_QUICKTIME               39
#define IPOQUE_PROTOCOL_PANDO                   40
#define IPOQUE_PROTOCOL_OPENVPN                 41
#define IPOQUE_PROTOCOL_IPSEC                   42
#define IPOQUE_PROTOCOL_GRE                     43
#define IPOQUE_PROTOCOL_NOT_DETECTED            44
#define IPOQUE_PROTOCOL_H323                    45
#define IPOQUE_PROTOCOL_WINDOWSMEDIA            46
#define IPOQUE_PROTOCOL_REALMEDIA               47
#define IPOQUE_PROTOCOL_TVANTS                  48
#define IPOQUE_PROTOCOL_SOPCAST                 49
#define IPOQUE_PROTOCOL_TVUPLAYER               50
#define IPOQUE_PROTOCOL_PPSTREAM                51
#define IPOQUE_PROTOCOL_PPLIVE                  52
#define IPOQUE_PROTOCOL_IAX                     53
#define IPOQUE_PROTOCOL_VTUN                    54
#define IPOQUE_PROTOCOL_MGCP                    55
#define IPOQUE_PROTOCOL_GADUGADU                56
#define IPOQUE_PROTOCOL_ZATTOO                  57
#define IPOQUE_PROTOCOL_WINNY                   58
#define IPOQUE_PROTOCOL_QQ                      59
#define IPOQUE_PROTOCOL_QQLIVE                  60
#define IPOQUE_PROTOCOL_FEIDIAN                 61
#define IPOQUE_PROTOCOL_SSH                     62
#define IPOQUE_PROTOCOL_POPO                    63
#define IPOQUE_PROTOCOL_THUNDER                 64
#define IPOQUE_PROTOCOL_UUSEE                   65
#define IPOQUE_PROTOCOL_VNC                     66
#define IPOQUE_PROTOCOL_ICMP                    67
#define IPOQUE_PROTOCOL_DHCP                    68
#define IPOQUE_PROTOCOL_IGMP                    69
#define IPOQUE_PROTOCOL_EGP                     70
#define IPOQUE_PROTOCOL_STEAM                   71
#define IPOQUE_PROTOCOL_HALFLIFE2               72
#define IPOQUE_PROTOCOL_XBOX                    73
#define IPOQUE_PROTOCOL_SOFTETHER               74
#define IPOQUE_PROTOCOL_SCTP                    75
#define IPOQUE_PROTOCOL_SMB                     76
#define IPOQUE_PROTOCOL_TELNET                  77
#define IPOQUE_PROTOCOL_NTP                     78
#define IPOQUE_PROTOCOL_NFS                     79
#define IPOQUE_PROTOCOL_OFF                     80
#define IPOQUE_PROTOCOL_RTP                     81
#define IPOQUE_PROTOCOL_TOR                     82
#define IPOQUE_PROTOCOL_SSDP                    83
#define IPOQUE_PROTOCOL_WORLDOFWARCRAFT         84
#define IPOQUE_PROTOCOL_AVI                     85
#define IPOQUE_PROTOCOL_VPN_X                   86
#define IPOQUE_PROTOCOL_HAMACHI_VPN             87
#define IPOQUE_PROTOCOL_SKINNY                  88
#define IPOQUE_PROTOCOL_CITRIX                  89
#define IPOQUE_PROTOCOL_OGG                     90
#define IPOQUE_PROTOCOL_PALTALK                 91
#define IPOQUE_PROTOCOL_MOVE                    92
#define IPOQUE_PROTOCOL_POSTGRES                93
#define IPOQUE_PROTOCOL_OSPF                    94
#define IPOQUE_PROTOCOL_BGP                     95
#define IPOQUE_PROTOCOL_QUAKE                   96
#define IPOQUE_PROTOCOL_SECONDLIFE              97
#define IPOQUE_PROTOCOL_MYSQL                   98
#define IPOQUE_PROTOCOL_BATTLEFIELD             99
#define IPOQUE_PROTOCOL_PCANYWHERE              100
#define IPOQUE_PROTOCOL_RDP                     101
#define IPOQUE_PROTOCOL_SNMP                    102
#define IPOQUE_PROTOCOL_KONTIKI                 103
#define IPOQUE_PROTOCOL_ICECAST                 104
#define IPOQUE_PROTOCOL_SHOUTCAST               105
#define	IPOQUE_PROTOCOL_HTTP_APPLICATION_QQGAME	106
#define IPOQUE_PROTOCOL_HTTP_APPLICATION_VEOHTV 107
#define IPOQUE_PROTOCOL_KERBEROS                108
#define IPOQUE_PROTOCOL_OPENFT                  109
#define IPOQUE_PROTOCOL_IP_IN_IP                110
#define IPOQUE_PROTOCOL_GTP	                    111
#define IPOQUE_PROTOCOL_RADIUS	                112
#define IPOQUE_PROTOCOL_PANDORA	                113
#define IPOQUE_PROTOCOL_STUN	                114
#define IPOQUE_PROTOCOL_SYSLOG	                115
#define IPOQUE_PROTOCOL_TDS 	                116
#define IPOQUE_PROTOCOL_NETBIOS					117
#define IPOQUE_PROTOCOL_MDNS					118
#define IPOQUE_PROTOCOL_IPP						119
#define IPOQUE_PROTOCOL_LDAP					120
#define IPOQUE_PROTOCOL_WARCRAFT3				121
#define IPOQUE_PROTOCOL_XDMCP					122
#define IPOQUE_PROTOCOL_OOVOO                   123
#define IPOQUE_PROTOCOL_HTTP_APPLICATION_GOOGLE_TALK               124
#define IPOQUE_PROTOCOL_ISKOOT					125
#define IPOQUE_PROTOCOL_FRING					126
#define IPOQUE_PROTOCOL_MAPI					127
#define IPOQUE_PROTOCOL_GENVOICE				128
#define IPOQUE_PROTOCOL_L2TP					129
#define IPOQUE_PROTOCOL_ISAKMP					130
#define IPOQUE_PROTOCOL_RTCP                    131
#define IPOQUE_PROTOCOL_IPTV					132
#define IPOQUE_PROTOCOL_TFTP					133
#define IPOQUE_PROTOCOL_MSSQL					134
#define IPOQUE_PROTOCOL_PPP						135
#define IPOQUE_PROTOCOL_PPTP					136
#define IPOQUE_PROTOCOL_STEALTHNET				137
#define IPOQUE_PROTOCOL_SAP						138
#define IPOQUE_PROTOCOL_ICMPV6					139
#define IPOQUE_PROTOCOL_YOURFREEDOM				140
#define IPOQUE_PROTOCOL_VOIPSWITCH_VOIPTUNNEL	141
#define IPOQUE_PROTOCOL_DHCPV6					142
#define IPOQUE_PROTOCOL_MEEBO					143
#define IPOQUE_PROTOCOL_FUNSHION				144
#define IPOQUE_PROTOCOL_AFP						145
#define IPOQUE_PROTOCOL_AIMINI					146
#define IPOQUE_PROTOCOL_TRUPHONE              	147
#define IPOQUE_PROTOCOL_CLUBPENGUIN				148
#define IPOQUE_PROTOCOL_FLORENSIA				149
#define IPOQUE_PROTOCOL_TEAMSPEAK				150
#define IPOQUE_PROTOCOL_MAPLESTORY				151
#define IPOQUE_PROTOCOL_OSH						152
#define	IPOQUE_PROTOCOL_PS3						153
#define	IPOQUE_PROTOCOL_DOFUS					154
#define IPOQUE_PROTOCOL_WII						155
#define	IPOQUE_PROTOCOL_IPSEC_UDP				156
#define	IPOQUE_PROTOCOL_WORLD_OF_KUNG_FU		157
#define	IPOQUE_PROTOCOL_FIESTA					158
#define IPOQUE_PROTOCOL_SPLASHFIGHTER			159
#define	IPOQUE_PROTOCOL_HTTP_APPLICATION_ACTIVESYNC	160
#define	IPOQUE_PROTOCOL_JABBER_APPLICATION_NIMBUZZ	161
#define IPOQUE_PROTOCOL_CROSSFIRE				162
#define IPOQUE_PROTOCOL_TUNNELVOICE               163
#define IPOQUE_PROTOCOL_WAP_WSP					164
#define IPOQUE_PROTOCOL_WAP_WTP_WSP				165
#define IPOQUE_PROTOCOL_WAP_WTLS				166
#define IPOQUE_PROTOCOL_MULTIMEDIA_MESSAGING	167
#define IPOQUE_PROTOCOL_GUILDWARS				168
#define IPOQUE_PROTOCOL_ARMAGETRON				169
#define IPOQUE_PROTOCOL_BLACKBERRY				170
#define IPOQUE_PROTOCOL_RFACTOR					171
#define IPOQUE_PROTOCOL_RDT						172
#define IPOQUE_PROTOCOL_TEAMVIEWER				173
#define IPOQUE_PROTOCOL_GAMEKIT					174
#define IPOQUE_PROTOCOL_NETMOTION				175
#define IPOQUE_PROTOCOL_ULTRABAC				176
#define IPOQUE_PROTOCOL_TEREDO					177
#define IPOQUE_PROTOCOL_SPOTIFY					178
#define IPOQUE_PROTOCOL_IMPLUS					179
#define IPOQUE_PROTOCOL_ANTSP2P					180
#define IPOQUE_PROTOCOL_ULTRASURF				181
#define IPOQUE_PROTOCOL_VIBER					182
#define IPOQUE_PROTOCOL_TANGO                   183
#define IPOQUE_PROTOCOL_IPLAYER                 184
#define IPOQUE_PROTOCOL_JBK3K                   185
#define IPOQUE_PROTOCOL_OPERAMINI               186
#define IPOQUE_PROTOCOL_BOLT                    187
#define IPOQUE_PROTOCOL_SCYDO                   188
#define IPOQUE_PROTOCOL_WHATSAPP                189
#define IPOQUE_PROTOCOL_WEBEX                   190
#define IPOQUE_PROTOCOL_NETFLIX                 191
#define IPOQUE_PROTOCOL_MOJO                    192
#define IPOQUE_PROTOCOL_IMO                     193
#define IPOQUE_PROTOCOL_CITRIX_GOTO             194
#define IPOQUE_PROTOCOL_FICALL                  195
#define IPOQUE_PROTOCOL_COMODOUNITE		        196
#define IPOQUE_PROTOCOL_GOOBER                  197
#define IPOQUE_PROTOCOL_VENTRILO				198
#define IPOQUE_PROTOCOL_MYPEOPLE				199
#define IPOQUE_PROTOCOL_WEBSOCKET               200
#define IPOQUE_PROTOCOL_EBUDDY                  201
#define IPOQUE_PROTOCOL_SSTP                    202
#define IPOQUE_PROTOCOL_ADOBE_CONNECT			203
#define IPOQUE_PROTOCOL_JAP						204
#define IPOQUE_PROTOCOL_LDP						205
#define IPOQUE_PROTOCOL_WUALA					206
#define IPOQUE_PROTOCOL_MSRP					207
#define IPOQUE_PROTOCOL_WEBDAV					208
#define IPOQUE_PROTOCOL_LYNC					209
#define IPOQUE_PROTOCOL_SOCKS					210
#define IPOQUE_PROTOCOL_AUDIOGALAXY				211
#define IPOQUE_PROTOCOL_MIG33					212
#define IPOQUE_PROTOCOL_HTTP_TUNNEL				213
#define IPOQUE_PROTOCOL_RHAPSODY				214
#define IPOQUE_PROTOCOL_SUDAPHONE				215
#define IPOQUE_PROTOCOL_WEBQQ					216
#define IPOQUE_PROTOCOL_PDPROXY					217
#define IPOQUE_PROTOCOL_LICENSE_EXCEEDED		218
#define IPOQUE_PROTOCOL_SILVERLIGHT				219
#define IPOQUE_PROTOCOL_SPDY					220
#define IPOQUE_PROTOCOL_CYBERGHOST				221
#define IPOQUE_PROTOCOL_GOOGLE					222
#define IPOQUE_PROTOCOL_FIX					    223
#define IPOQUE_PROTOCOL_ORACLE_DB				224
#define IPOQUE_PROTOCOL_ITV						225
#define IPOQUE_PROTOCOL_DEMAND5                 226
#define IPOQUE_PROTOCOL_RSVP                    227
#define IPOQUE_PROTOCOL_CHANNEL_4OD             228
#define IPOQUE_PROTOCOL_LOTUS_NOTES				229
#define IPOQUE_PROTOCOL_POISON_IVY				230
#define IPOQUE_PROTOCOL_NETFLOW					231
#define IPOQUE_PROTOCOL_HIDRIVE                 232
#define IPOQUE_PROTOCOL_WECHAT                  233
#define IPOQUE_PROTOCOL_MYVIDEO					234
#define IPOQUE_PROTOCOL_SOAP                    235
#define IPOQUE_PROTOCOL_KIK_MESSENGER           236
#define IPOQUE_PROTOCOL_MPLUS                   237
#define IPOQUE_PROTOCOL_LINE                    238
#define IPOQUE_PROTOCOL_IPERF                   239
#define IPOQUE_PROTOCOL_OS_UPDATE               240
#define IPOQUE_PROTOCOL_DIAMETER                241
#define IPOQUE_PROTOCOL_HIKE_MESSENGER          242
#define IPOQUE_PROTOCOL_MQTT                    243
#define IPOQUE_PROTOCOL_DIDI                    244
#define IPOQUE_PROTOCOL_DCE_RPC					245
#define IPOQUE_PROTOCOL_IDRIVE                  246
#define IPOQUE_PROTOCOL_SPREECAST               247
#define IPOQUE_PROTOCOL_SIMFY                   248
#define IPOQUE_PROTOCOL_DOTA2                   249
#define IPOQUE_PROTOCOL_QVOD                    250
#define IPOQUE_PROTOCOL_HULU                    251
#define IPOQUE_PROTOCOL_MSEXCHANGE              252
#define IPOQUE_PROTOCOL_MSNAV                   253
#define IPOQUE_PROTOCOL_FUZE                    254
#define IPOQUE_PROTOCOL_TIBIA                   255
#define IPOQUE_PROTOCOL_KAKAO                   256
#define IPOQUE_PROTOCOL_DESTINY                 257
#define IPOQUE_PROTOCOL_VYPR_VPN                258
#define IPOQUE_PROTOCOL_TACACS                  259
#define IPOQUE_PROTOCOL_THREEMA                 260
#define IPOQUE_PROTOCOL_NTLM                    261
#define IPOQUE_PROTOCOL_TWITCH                  262
#define IPOQUE_PROTOCOL_WOWZA                   263
#define IPOQUE_PROTOCOL_RUNTASTIC               264
#define IPOQUE_PROTOCOL_TELEGRAM                265
#define IPOQUE_PROTOCOL_STREETVOICE             266
#define IPOQUE_PROTOCOL_WHOIS                   267
#define IPOQUE_PROTOCOL_FLUTE                   268
#define IPOQUE_PROTOCOL_MEGACO                  269
#define IPOQUE_PROTOCOL_AOWE                    270
#define IPOQUE_PROTOCOL_MAGINE_TV               271
#define IPOQUE_PROTOCOL_QUIC                    272
#define IPOQUE_PROTOCOL_LIVEPERSON              273
#define IPOQUE_PROTOCOL_DOOOK                   274
#define IPOQUE_PROTOCOL_SPEEDTEST               275
#define IPOQUE_PROTOCOL_BLUEJEANS               276
#define IPOQUE_PROTOCOL_IEC61850                277
#define IPOQUE_PROTOCOL_SCADA                   278
#define IPOQUE_PROTOCOL_CASSANDRA_QUERY_LANGUAGE            279
#define IPOQUE_PROTOCOL_CASSANDRA_INTERNODE_COMMUNICATION   280
#define IPOQUE_PROTOCOL_PERISCOPE               281
#define IPOQUE_PROTOCOL_THRIFT                  282
#define IPOQUE_PROTOCOL_PLAYSTATION             283
#define IPOQUE_PROTOCOL_SUPERCELL               284
#define IPOQUE_PROTOCOL_SKYPE_FOR_BUSINESS      285
#define IPOQUE_PROTOCOL_T3                      286

#define IPOQUE_LAST_IMPLEMENTED_PROTOCOL        286

#ifdef IPOQUE_USER_DEFINED_PROTOCOLS
#define IPOQUE_USER_DEFINED_MAX_PROTOCOLS       32
#define IPOQUE_MAX_SUPPORTED_PROTOCOLS          (IPOQUE_LAST_IMPLEMENTED_PROTOCOL + IPOQUE_USER_DEFINED_MAX_PROTOCOLS)

#else							/* IPOQUE_USER_DEFINED_PROTOCOLS */

#define IPOQUE_MAX_SUPPORTED_PROTOCOLS IPOQUE_LAST_IMPLEMENTED_PROTOCOL

#ifdef IPOQUE_PACE_API_MK1

#define IPOQUE_USER_DEFINED_MAX_PROTOCOLS       0

#endif

#endif							/* IPOQUE_USER_DEFINED_PROTOCOLS */


#define IPOQUE_PROTOCOL_LONG_STRING "unknown","BitTorrent","eDonkey","KaZaa/Fasttrack","Gnutella",\
"WinMX","DirectConnect","AppleJuice","Soulseek","Ares","Freenet","Mute","XDCC","Skype",\
"SIP","MSN","Yahoo","Oscar","IRC","Jabber","ORB","Slingbox","Vcast","HTTP","DirectDownloadLink",\
"POP","SMTP","IMAP","Usenet","FTP","DNS","RTSP","Filetopia","Manolito","iMesh","SSL","FLASH","MMS","MPEG","QUICKTIME","Pando",\
"OpenVPN","IPSEC","GRE","undetected","H323","WINDOWSMEDIA","REALMEDIA","TVANTS","SOPCAST","TVUPLAYER","PPSTREAM","PPLIVE",\
"IAX","VTUN","MGCP","Gadu-Gadu","ZATTOO","WINNY","QQ","QQLive","Feidian","SSH","POPO","Thunder/Webthunder","UUSEE","VNC","ICMP",\
"DHCP","IGMP","EGP","Steam","Halflife2","XBOX","SoftEthernet","SCTP","SMB/CIFS","Telnet","NTP","NFS","OFF","RTP",\
"TOR","SSDP","World of Warcraft","AVI","VPN-X","HamachiVPN","Skinny","Citrix","OGG","Paltalk","Move","PostgreSQL",\
"OSPF","BGP","Quake","Second Life","MySQL","Battlefield","PCAnywhere","RDP","SNMP","Kontiki","Icecast","Shoutcast",\
"HTTP Application QQGame","HTTP Application VeohTV","Kerberos","OpenFT","IP in IP","GTP","RADIUS","Pandora","STUN","Syslog","TDS","NETBIOS","MulticastDNS",\
"IPP","LDAP","WARCRAFT3","XDMCP","ooVoo","HTTP application Google Talk", "Iskoot","Fring","Mapi","Generic Voice","L2TP","ISAKMP",\
"RTCP","IPTV","TFTP","msSQL","PPP","PPTP","StealthNet","SAP","ICMPv6","YourFreedom Tunnel","VoipSwitch VoIP Tunnel",\
"DHCPv6","MEEBO","Funshion","AFP","Aimini","Truphone","ClubPenguin","Florensia","TeamSpeak","MapleStory","Octoshape","PS3",\
"Dofus","WII","IPSEC_UDP","World of Kung Fu","Fiesta","SplashFighter","HTTP Application Activesync",\
"JABBER Application NIMBUZZ","CrossFire","Tunnelvoice","WAP-WSP","WAP-WTP-WSP","WAP-WTLS","MultimediaMessaging",\
"Guildwars","Armagetron","Blackberry","rFactor", "RealDataTransport", "TeamViewer", "GameKit", "NetMotion", "UltraBac", \
"Teredo", "Spotify", "IMplus", "ANtsP2P", "UltraSurf", "Viber", "Tango", "iPlayer", "JBK3000", "OperaMini", "BOLT", \
"Scydo", "WhatsApp", "Webex", "NetFlix", "Mojo", "IMO", "CitrixGoTo", "FiCall", "ComodoUnite", "Goober", "Ventrilo", \
"MyPeople", "WebSocket", "eBuddy", "SSTP", "AdobeConnect", "JAP", "LDP", "Wuala", "MSRP", "WebDAV", "Lync", "Socks", \
"Audiogalaxy", "Mig33", "HTTPTunnel", "Rhapsody", "Sudaphone", "WebQQ", "PDProxy", "License exceeded", "Silverlight", \
"SPDY", "CyberGhost", "Google", "FIX", "Oracle Database", "ITV", "Demand 5", "RSVP", "Channel 4oD", "Lotus Notes", \
"Poison Ivy", "NetFlow", "HiDrive", "WeChat", "MyVideo", "SOAP", "Kik Messenger", "MPlus", "Line", "Iperf", "OS update", \
"Diameter", "Hike Messenger", "MQTT", "DiDi", "DCE_RPC", "IDrive", "Spreecast", "Simfy", "Dota 2", "QVOD", "Hulu", \
"Microsoft Exchange", "Microsoft Dynamics NAV", "Fuze Meeting", "Tibia", "Kakao", "Destiny", "VyprVPN", "TACACS",\
"Threema", "NTLM", "Twitch", "Wowza", "Runtastic", "Telegram", "StreetVoice", "WHOIS", "FLUTE", "Megaco", \
"Age of Warring Empire", "Magine TV", "Quic", "LivePerson", "Doook", "Speedtest", "BlueJeans", "IEC61850", "SCADA", \
"Cassandra Query Language", "Cassandra Internode Communication", "Periscope", "Thrift", "PlayStation Network", \
"Supercell", "Skype for Business", "T3", \
"USER1","USER2","USER3","USER4","USER5","USER6","USER7","USER8","USER9","USER10","USER11",\
"USER12","USER13","USER14","USER15","USER16","USER17","USER18","USER19","USER20","USER21",\
"USER22","USER23","USER24","USER25","USER26","USER27","USER28","USER29","USER30","USER31",\
"USER32","USER33","USER34","USER35","USER36","USER37","USER38","USER39",\
"USER40","USER41","USER42","USER43","USER44","USER45","USER46","USER47","USER48","USER49",\
"USER50","USER51","USER52","USER53","USER54","USER55","USER56","USER57","USER58","USER59",\
"USER60","USER61","USER62","USER63","USER64","USER65","USER66","USER67","USER68","USER69",\
"USER70","USER71","USER72","USER73","USER74","USER75","USER76","USER77","USER78","USER79",\
"USER80","USER81","USER82","USER83","USER84","USER85","USER86","USER87","USER88","USER89",\
"USER90","USER91","USER92","USER93","USER94","USER95","USER96","USER97","USER98","USER99",\
"USER100"

#define IPOQUE_PROTOCOL_SHORT_STRING "ukn","bit","edk","kazaa","gnu","winmx","directconnect","apple","soul",\
"ares","freenet","mute","xdcc","skype","sip","msn","yahoo","oscar","irc","jabber","orb","sling","vcast","http",\
"ddl","pop","smtp","imap","usenet","ftp","dns","rtsp","filetopia","manolito","imesh","ssl","flash","mms","mpeg",\
"quicktime","pando","openvpn","ipsec","gre","notdetect","h323","windowsmedia","realmedia","tvants","sopcast",\
"tvuplayer","ppstream","pplive","iax","vtun","mgcp","gadugadu","zattoo","winny","qq","qqlive","feidian","ssh",\
"popo","thunder","uusee","vnc","icmp","dhcp","igmp","egp","steam","hl2","xbox","softether","sctp","smb","telnet",\
"ntp","nfs","off","rtp","tor","ssdp","worldofwarcraft","avi","vpnx","hamachi","skinny","citrix","ogg","paltalk",\
"move","postgres","ospf","bgp","quake","secondlife","mysql","battlefield","pcanywhere","rdp","snmp","kontiki",\
"icecast","shoutcast","httpqqgame","httpveohtv","kerberos","openft","ipip","gtp","radius","pandora","stun","syslog","tds",\
"netbios","mdns","ipp","ldap","warcraft3","xdmcp","oovoo","httpgoogletalk","iskoot","fring","mapi","genvoice","l2tp","isakmp",\
"rtcp","iptv","tftp","mssql","ppp","pptp","stealthnet","sap","icmpv6","yourfreedom","voipswitchvoiptunnel","dhcpv6",\
"meebo","funshion","afp","aimini","truphone","clubpenguin","florensia","teamspeak","maplestory","osh","ps3",\
"dofus","wii","ipsecudp","wokf","fiesta","splashfighter","httpactivesync","jabbernimbuzz", "crossfire","tunnelvoice",\
"wapwsp","wapwtpwsp","wapwtls","multimediamessaging","guildwars","armagetron","blackberry","rfactor", "rdt", \
"teamviewer", "gamekit", "netmotion", "ultrabac", "teredo", "spotify", "implus", "antsp2p", "ultrasurf", "viber", \
"tango", "iplayer", "jbk3k", "operamini", "bolt", "scydo", "whatsapp", "webex", "netflix", "mojo", "imo", \
"citrixgoto", "ficall", "comodounite", "goober", "ventrilo", "mypeople", "websocket", "ebuddy", \
"sstp", "adobeconnect", "jap", "ldp", "wuala", "msrp", "webdav", "lync", "socks", "audiogalaxy", "mig33", \
"httptunnel", "rhapsody", "sudaphone", "webqq", "pdproxy", "license", "silverlight", "spdy", "cyberghost", "google", \
"fix", "oracledb", "itv", "demand5", "rsvp", "channel4od", "lotusnotes", "poisonivy", "netflow", "hidrive", "wechat", \
"myvideo", "soap", "kik", "mplus", "line", "iperf", "osupdate", "diameter", "hike", "mqtt", "didi", "dce_rpc", "idrive", \
"spreecast", "simfy", "dota2", "qvod", "hulu", "msexchange", "msnav", "fuze", "tibia", "kakao", "destiny", "vyprvpn", \
"tacacs", "threema", "ntlm", "twitch", "wowza", "runtastic", "telegram", "streetvoice", "whois", "flute", "megaco", \
"aowe", "maginetv", "quic", "liveperson", "doook", "speedtest", "bluejeans", "iec61850", "scada", \
"cql", "cic", "periscope", "thrift", "playstation", "supercell", "skype-for-business", "t3", \
"USER1","USER2","USER3","USER4","USER5","USER6","USER7","USER8","USER9","USER10","USER11",\
"USER12","USER13","USER14","USER15","USER16","USER17","USER18","USER19","USER20","USER21",\
"USER22","USER23","USER24","USER25","USER26","USER27","USER28","USER29","USER30","USER31",\
"USER32","USER33","USER34","USER35","USER36","USER37","USER38","USER39",\
"USER40","USER41","USER42","USER43","USER44","USER45","USER46","USER47","USER48","USER49",\
"USER50","USER51","USER52","USER53","USER54","USER55","USER56","USER57","USER58","USER59",\
"USER60","USER61","USER62","USER63","USER64","USER65","USER66","USER67","USER68","USER69",\
"USER70","USER71","USER72","USER73","USER74","USER75","USER76","USER77","USER78","USER79",\
"USER80","USER81","USER82","USER83","USER84","USER85","USER86","USER87","USER88","USER89",\
"USER90","USER91","USER92","USER93","USER94","USER95","USER96","USER97","USER98","USER99",\
"USER100"

// IPOQUE_PROTOCOL_DESCRIPTION_STRING must contain information about:
// 1. is it a protocol or an application or both and if it is an application what is the corresponding protocol
// 2. information about the protocol family
// 3. information about existing subprotocols and which protocols the subprotocols use.
// 4. block limitation: if not all traffic produced by the protocol/application is blocked when someone blocks the protocol/application
// 5. information if the protocol/application is standardized/proprietary/obfuscated.

#define IPOQUE_PROTOCOL_DESCRIPTION_STRING \
	"All traffic that is not classified yet we call unknown.",\
	"BitTorrent is the protocol of the corresponding P2P network.",\
	"The eDonkey network (also known as the eDonkey2000 network or eD2k) is a decentralized, mostly server-based, peer-to-peer file sharing network protocol best suited to share big files among users, and to provide long term availability of said files.",\
	"Kazaa is the protocol of the corresponding P2P network.",\
	"Gnutella is the protocol of the corresponding P2P network.",\
	"WinMX is the protocol of the corresponding P2P network and a favorite in Japan.",\
	"Direct Connect is the protocol of the corresponding P2P network.",\
	"Applejuice is the protocol of the corresponding P2P network.",\
	"Soulseek is the protocol of the corresponding P2P file-sharing network and application.",\
	"Ares is the protocol of the corresponding P2P network.",\
	"Freenet is the protocol of the P2P network with the same name.",\
	"MUTE is the protocol of an open source P2P file sharing network developed with anonymity in mind.",\
	"XDCC is a protocol used by popular Instant Messaging applications.",\
	"Skype is the protocol of the corresponding popular instant messaging, voice and file transfer application.",\
	"Traffic of voice calls initiated over the protocol standardized SIP.",\
	"MSN is the protocol used by the Microsoft MSN Instant Messaging application family.",\
	"Yahoo Messenger is a popular instant messaging application with support for chat, voice calls and file transfer.",\
	"OSCAR is the protocol used by AOL Messenger applications.",\
	"IRC is a protocol used by a number of popular Instant Messaging applications.",\
	"Extensible Messaging and Presence Protocol (XMPP) (formerly named Jabber) is an open, XML-based protocol originally aimed at near-real-time, extensible instant messaging (IM) and presence information (e.g., buddy lists), but now expanded into the broader realm of message-oriented middle ware.",\
	"Orb is a free streaming application.",\
	"Slingbox is the protocol of the Slingbox TV streaming device that enables users to remotely view their home's cable, satellite, or personal video recorder (PVR) programming from an Internet-enabled computer with a broadband Internet connection.",\
	"V CAST is a protocol/transport mechanism developed by Verizon Wireless to deliver audio, video and entertainment content.",\
	"HTTP is used to access web servers but is also transport protocol for a number of streaming applications.",\
	"Direct Download Link refers to a HTTP hyperlink-based approach to easily and directly share large files like music and video.",\
	"POP is the protocol to fetch e-mails from servers.",\
	"SMTP is used to transmit e-mails.",\
	"IMAP is used to remotely access e-mails on an IMAP server.",\
	"The Network News Transfer Protocol (NNTP) is an Internet application protocol used for transporting Usenet news articles (netnews) between news servers and for reading and posting articles by end user client applications.",\
	"FTP, File Transfer Protocol, is a simple protocol to upload to and download files from FTP servers.",\
	"DNS, Domain Name System, is a protocol to resolve domain names to IP addresses.",\
	"RTSP is a used to transport audio and video streams.",\
	"FileTopia is the protocol of the corresponding free, Windows-based client and networking tool allowing users to organize files, text and voice recordings, chat, and instant messages.",\
	"Manolito is the protocol of the corresponding P2P network.",\
	"iMesh is the protocol of the iMesh P2P network.",\
	"SSL/TLS is a network protocol used to provide secure communication over IP networks.",\
	"Flash streaming over HTTP and is also the name of the protocol used by the streaming server of the company macromedia.",\
	"MMS is a proprietary network streaming protocol from Microsoft.",\
	"MPEG Streaming over HTTP.",\
	"QuickTime Streaming over HTTP.",\
	"Pando is the protocol of the Pando P2P network.",\
	"OpenVPN is a free and open source virtual private network (VPN) program for creating point-to-point or server-to-multiclient encrypted tunnels between host computers. It is capable of establishing direct links between computers across network address translators (NATs) and firewalls.",\
	"IPSec is a protocol suite for securing Internet Protocol (IP) communications by authenticating and encrypting each IP packet of a communication session.",\
	"GRE is a protocol used to tunnel usually non-IP protocols over IP. Examples are PPTP, IPv6, IPX or AppleTalk.",\
	"Traffic that cannot be classified by ipoque detection we call undetected.",\
	"Traffic of H.323 initiated calls.",\
	"Windows Media Streaming.",\
	"Protocol of RealNetworks RealMedia streaming application and browser plugin.",\
	"TVAnts is the protocol of a P2P TV streaming network with the same name.",\
	"SopCast is the protocol of the P2P Internet TV streaming network.",\
	"TVU is the protocol of the TVUPlayer application.",\
	"PPStream is the protocol of the corresponding Chinese peer-to-peer streaming video network software. Since the target user is in Chinese mainland, there is no official English version, and vast majority of channels are from Eastern Asia, mostly Mainland China, Korea, Japan, Hong Kong, Taiwan and Singapore. Channel varieties vary from Chinese movies to Japanese anime, sports channels, as well as American popular TV and films.",\
	"PPLive is a peer-to-peer streaming video network created in Huazhong University of Science and Technology, People's Republic of China. It is part of a new generation of P2P applications, that combine P2P and Internet TV, called P2PTV.",\
	"IAX is used by the open source PBX Asterisk.",\
	"VTun is a networking application which can set up Virtual Tunnels over TCP/IP networks.",\
	"MGCP is used for communication between voice gateways.",\
	"Gadu-Gadu is the protocol of the corresponding popular Polish instant messaging application.",\
	"Zattoo is a proprietary peer-to-peer Internet Protocol Television system (\"P2PTV\") with current focus on European channels, licensed content, and Digital Rights Management.",\
	"WinNY is the protocol of the P2P network with the same name.",\
	"Instant Messaging application popular in China and the Asian region.",\
	"QQLive is P2PTV software and a service provided by Tencent Corporation of China. It is one of mostly installed and used P2PTV software and service in China.",\
	"Feidian (Boiling Point) is a P2PTV application from the People's Republic of China.",\
	"SSH is a protocol used to provide secure, encrypted communication (file transfer etc.) over IP networks.",\
	"PoPo is the protocol of an instant messaging application popular in China.",\
	"Thunder is a P2P filesharing application mainly used in china",\
	"UUSee is the protocol of a P2P network with the same name.",\
	"Similar to RDP VNC provides a way to access the graphical user interface/desktop of remote systems.",\
	"ICMP is used to exchange status information and error messages over IP networks.",\
	"DHCP is a protocol used to dynamically configure systems in IP networks.",\
	"IGMP is used to manage multicast groups.",\
	"EGP is an important routing protocol of the Internet.",\
	"Steam is a protocol used by popular multiplayer online games like Half-Life.",\
	"Half-Life 2 is the protocol of the popular multiplayer online game.",\
	"XBox Traffic.",\
	"SoftEthernet",\
	"SCTP is a reliable, connection-oriented protocol at layer 4 of the OSI model.",\
	"CIFS/SMB is a protocol used to provide file access to Microsoft Windows systems usually.",\
	"Telnet (teletype network) is a network protocol used on the Internet or local area networks to provide a bidirectional interactive communications facility. Typically, telnet provides access to a command-line interface on a remote host via a virtual terminal connection which consists of an 8-bit byte oriented data connection over the Transmission Control Protocol (TCP). User data is interspersed in-band with TELNET control information.",\
	"NTP is used to sync time of computer systems.",\
	"The NFS protocol is used to share files over a network.",\
	"The Owner-Free File System (OFF System, or OFF for short) is a peer-to-peer distributed file system through which all shared files are represented by randomized multi-used data blocks. The system is referred to as a brightnet to contrast its method of operation with that of private file sharing systems known as darknets. OFF was created with the expressed intention \"to cut off some gangrene-infested bits of the copyright industry.\"",\
	"RTP is a standard protocol used to transport audio and video streams over IP networks.",\
	"Tor is a protocol used to provide secure communication and anonymity over IP networks.",\
	"SSDP is used to discover UPnP devices.",\
	"Protocol of the corresponding multiplayer online game.",\
	"AVI Video Streams over HTTP.",\
	"vpnx is the protocol used by the vpnx tunnel application.",\
	"Hamachi is a zero-configuration virtual private network (VPN) shareware application capable of establishing direct links between computers that are behind NAT firewalls without requiring reconfiguration (in most cases); in other words, it establishes a connection over the Internet that very closely emulates the connection that would exist if the computers were connected over a local area network.",\
	"The Skinny Call Control Protocol (SCCP, or short Skinny) is a proprietary network terminal control protocol originally developed by Selsius Corporation.",\
	"Citrix is the protocol of the terminal server application with the same name.",\
	"Ogg Vorbis is an open-source streaming technology.",\
	"Paltalk is an internet chat service that allows users to communicate via instant messaging, voice and video chat.",\
	"Move is a streaming protocol over HTTP.",\
	"PostgreSQL database traffic.",\
	"OSPF is an important routing protocol of the Internet.",\
	"BGP is an important routing protocol of the Internet.",\
	"Quake refers to the protocol which is used for communication between systems during multiplayer games.",\
	"Protocol for the corresponding virtual world application.",\
	"Traffic of the MySQL Database protocol.",\
	"Battlefield.",\
	"Protocol of the pcAnywhere remote desktop application.",\
	"Proprietary Microsoft protocol used to remotely connect to Windows systems and take control over the desktop.",\
	"SNMP is used for monitoring and managing network components such as switches, routers etc.",\
	"Kontiki is the protocol of the content delivery platform with the same name.",\
	"Icecast is a streaming media project released as free software maintained by the Xiph.org Foundation. It also refers specifically to the server program which is part of the project.",\
	"SHOUTcast is the protocol of the corresponding media streaming server software developed by Nullsoft.",\
	"QQGame is a game that uses HTTP and HTTP_FLASH as protocol.",\
	"Veoh TV is the HTTP application the Veoh Internet television service.",\
	"Kerberos is a computer network authentication protocol, which allows nodes communicating over a non-secure network to prove their identity to one another in a secure manner. It is also a suite of free software published by Massachusetts Institute of Technology (MIT) that implements this protocol. Its designers aimed primarily at a client-server model, and it provides mutual authentication — both the user and the server verify each other's identity. Kerberos protocol messages are protected against eavesdropping and replay attacks.",\
	"OpenFT is a file sharing protocol developed by the giFT project.",\
	"IP in IP is an IP tunneling protocol that encapsulates one IP packet in another IP packet.",\
	"GPRS Tunnelling Protocol (GTP) is a group of IP-based communications protocols used to carry General Packet Radio Service (GPRS) within GSM and UMTS networks.",\
	"Remote Authentication Dial In User Service (RADIUS) is a networking protocol that provides centralized Authentication, Authorization, and Accounting (AAA) management for computers to connect and use a network service.",\
	"Pandora is the streaming protocol of the internet radio application with the same name.",\
	"STUN is an Internet standards-track suite of methods, including a network protocol, used in NAT traversal for applications of real-time voice, video, messaging, and other interactive IP communications.",\
	"Syslog is a standard for forwarding log messages in an Internet Protocol (IP) computer network.",\
	"Tabular Data Stream (TDS) is an application layer protocol, used to transfer data between a database server and a client. Initially designed and developed by Sybase Inc. for their Sybase SQL Server relational database engine in 1984, and later by Microsoft in Microsoft SQL Server.",\
	"NetBIOS is an acronym for Network Basic Input/Output System. It provides services related to the session layer of the OSI model allowing applications on separate computers to communicate over a local area network.",\
	"MDNS is part of the zero configurartion networking (zeroconf) and is used for automatic resolution and distribution of computer hostnames (multicast DNS)",\
	"Internet Printing Protocol (IPP) provides a standard network protocol for remote printing as well as for managing print jobs, media size, resolution, and so forth.",\
	"The Lightweight Directory Access Protocol, or LDAP, is an application protocol for querying and modifying directory services running over TCP/IP.",\
	"Warcraft3 is the protocol of the corresponding multiplayer online game.",\
	"X Display Manager Control Protocol (XDMCP) for the X window system.",\
	"OOVOO is a voice over ip protocol.",\
	"HTTP Application Google Talk is the HTTP traffic caused by application google talk.",\
	"ISKOOT is a voice over IP protocol.",\
	"Fring is the corresponding protocol to the application with the same name, which support Voice over IP and instant messaging over Skype, ICQ, MSN, AIM, Yahoo and SIP.",\
	"MAPI/RPC is a proprietary protocol that Microsoft Outlook uses to communicate with Microsoft Exchange.",\
	"A voice over IP protocol, where the type is unknown.",\
	"L2TP is used to tunnel PPP frames over IP networks.",\
	"ISAKMP is a protocol for establishing Security Associations (SA) and cryptographic keys in an Internet environment. The protocol is defined by RFC 2408.",\
	"The RTP Control Protocol (RTCP) is a sister protocol of the Real-time Transport Protocol (RTP). Its basic functionality and packet structure is defined in the RTP specification RFC 3550.",\
	"Internet Protocol television (IPTV) is a streaming protocol.",\
	"Trivial File Transfer Protocol (TFTP) is a file transfer protocol, with the functionality of a very basic form of File Transfer Protocol (FTP).",\
	"MSSQL is the protocol for the corresponding database application.",\
	"Point-to-Point Protocol, or PPP, is a data link protocol commonly used to establish a direct connection between two networking nodes. It can provide connection authentication, transmission encryption privacy, and compression.",\
	"The Point-to-Point Tunneling Protocol (PPTP) is a method for implementing virtual private networks (VPN). PPTP uses a control channel over TCP and a GRE tunnel operating to encapsulate PPP packets.",\
	"StealthNet is the protocol to the corresponding P2P application.",\
	"SAP is the protocol used between SAP Server and SAP Clients.",\
	"ICMPv6 is ICMP (is used to exchange status information and error messages over IP networks.) for IPv6",\
	"YourFreedom is a tunnel protocol.",\
	"VoipSwitch or VoipTunnel are a tunnel protocol with voip inside.",\
	"DHCPv6 is the DHCP for IPv6",\
	"Meebo is the protocol for the corresponding instant messanger.",\
	"Funshion is a streaming protocol.",\
	"The Apple Filing Protocol (AFP) is a network protocol that offers file services for Mac OS X and original Mac OS.",\
	"Aimini is a P2P protocol.",\
	"TruPhone is the protocol of the corresponding VoIP application.",\
	"ClubPenguin is the protocol of the corresponding Massive Multiplayer Online Game, which is provided by ClubPenguin.com.",\
	"Florencia is the protocol of the corresponding massive multiplayer online game.",\
	"TeamSpeak is the protocol of the corresponding VoIP application.",\
	"MapleStory is the protocol of the corresponding massive multiplayer online role play game.",\
	"Octoshape is the protocol of the corresponding streaming application.",\
	"PS3 is the protocol of the corresponding traffic of the PS3 video game console.",\
	"Dofus is the protocol of the corresponding massive multiplayer online role play game.",\
	"wii is the protocol of the corresponding traffic of the wii video game console",\
	"IPsecUDP is IPsec over UDP.",\
	"World of Kung Fu is the protocol of the corresponding massive multiplayer online role play game.",\
	"Fiesta is the protocol of the corresponding massive multiplayer online role play game.",\
	"SplashFighter is the protocol of the corresponding multiplayer online game.",\
	"Activesync is a software to synchronize PCs and mobile phones.",\
	"Nimbuzz is a Jabber Application used to chat and to phone.",\
	"Crossfire is an open source, cooperative multiplayer graphical RPG and adventure game.",\
	"Tunnelvoice is a heuristic for detecting voip calls in tunnels",\
	"WAP-WSP Wireless Application Protocol using the Wireless Session Protocol is used to deliver Internet contents to devices with slower Internet connections like mobile phones.",\
	"WAP-WTP-WSP Wireless Application Protocol using the Wireless Transport Protocol and Wireless Session Protocol is used to deliver Internet contents to devices with slower Internet connections like mobile phones.",\
	"WAP-WTLS Wireless Application Protocol using the Wireless Transport Layer Security is used to securely deliver Internet contents to devices with slower Internet connections like mobile phones.",\
	"Multimedia Messaging Service (MMS) is a protocol for sending messages that include multimedia content from mobile phones.",\
	"Guild Wars is an episodic series of multiplayer online role-playing games developed by ArenaNet and published by NCsoft.",\
	"Armagetron Advanced is a multiplayer game in 3D.",\
	"Blackberry",\
	"rFactor is a computer racing simulator.",\
	"RDT is an audio/video transport protocol from RealNetworks", \
	"TeamViewer is a remote administration tool", \
	"GameKit is a framework from Apple for multiplayer/social games", \
	"NetMotion is a mobile VPN solution", \
	"UltraBac is a backup software", \
	"Teredo is a IPv6 in IPv4/UDP tunnel", \
	"Spotify is a music listening service", \
	"IM+ is a multi-protocol multi-platform messenger client.", \
	"ANts P2P is a p2p program written in java.", \
	"UltraSurf is a proxy solution for anonymous browsing.", \
	"Viber is VoIP application for iphone/android/blackberry.", \
    "Tango is VoIP application for iphone/android.", \
    "iPlayer is an internet television and radio service developed by BBC.", \
    "JBK3000 sends measurement data over LAN from a automatic tester which is used to measure various types of flammable liquid petroleum products.",\
    "OperaMini is the protocol used by the mobile web browser of the same name from Opera.",\
    "Bolt is the protocol used by the mobile web browser Bolt for smartphones",\
    "Scydo is VoIP application for iphone/android.", \
    "WhatsApp is a cross-platform mobile messaging app for iPhone, BlackBerry, Android and Nokia", \
    "Webex is Ciscos Web Conferencing and Collaboration Solution", \
    "NetFlix is an online media steaming service", \
	"Mojo is a P2P software for sharing the iTunes library", \
	"IMO is a web-based service that allows users to hold text, voice, and video chats on multiple instant messaging protocols.", \
	"CitrixGoTo is the protocol which is used by the Cirix GoTo... applications", \
	"FiCall is a service for internet audio and video calls. FiCall also provides sending text messages and watching ipTV", \
	"Comodo Unite is a VPN client for windows computers.",\
	"Goober is a VoIP / Instant messenger", \
	"Ventrilo is a proprietary VoIP software which includes text chat.",\
	"MyPeople is a korean voip and im app",\
	"WebSockets are an XMLHttpRequest replacement for HTTP", \
	"eBuddy is a web and mobile multi messenger", \
	"SSTP is the Secure Socket Tunneling Protocol, a VPN over SSL.", \
	"Adobe Connect is an enterprise web conferencing solution for online meetings.",\
	"JAP - JonDonym anonymous proxy servers - is an anonymization service.",\
	"LDP is a way for labeling servers to propagate labeling information, used e.g. for routing.",\
	"Wuala is a online storage service",\
	"MSRP is a protcol used for transmitting IM, files and sharing images within a communication session. Message sessions are treated like media streams and can be set up by SIP (e.g.).",\
	"WebDAV (Web-based Distributed Authoring and Versioning) is extension to the HTTP protocol to collaboratively edit and manage files on web servers",\
	"Lync is a communication software for IM, VoIP and online meetings.",\
	"Socks is proxy protocol for tunneling any kind of traffic via Socks proxy server.",\
	"Audiogalaxy is a streaming service that allows users stream private music from their PCs",\
	"Mig33 is a mobile social network popular in Asia. Supports IM, blogs and minigames.",\
	"HTTPTunnel is a tunneling software that can tunnel network connections over HTTP GET and POST requests.",\
	"Rhapsody (Napster in europe) is a music streaming service. ",\
	"Sudaphone is a popular korean VoIP and IM application.",\
	"WebQQ is a web desktop application.",\
	"PDProxy is a tunneling software.",\
	"License exceeded is used to mark traffic if the license limitations are reached.",\
	"Silverlight is Microsofts equivalent to Adobes Flash.",\
	"SPDY is an internet protocol based on HTTP with the goal of lower latency on web pages.",\
    "CyberGhost is a tunneling software.",\
	"Google provides various service in the web including search, cloud etc. ",\
	"The FIX (Financial Information eXchange) protocol is used for financial and trade related transactions",\
	"Oracle Database is a database management system produced and marketed by Oracle Corporation.",\
	"ITV is television network providing online streaming of various tv channels.",\
	"Demand 5 is a television network providing streams of various shows",\
	"RSVP is a protocol to reserve resources across a network.",\
	"Channel 4oD is a British public-service television broadcaster.",\
	"Lotus Notes is a popular groupware solution.",\
	"Poison Ivy is a remote administration tool that mostly is used as trojan attached to other executables.", \
    "NetFlow is a network reporting protocol developed by Cisco.", \
	"Strato HiDrive is a cloud storage service with free and subscription based plans.",\
	"WeChat is a voice and text messaging application for different smartphone operating systems.",\
    "MyVideo is a video streaming portal similar to YouTube.", \
    "SOAP is a protocol for exchanging structured information and is based on XML.", \
    "Kik Messenger is a free IM application.",\
    "MPlus is a messaging application for mobile phones.", \
    "Line is a free VOIP and messaging application.", \
    "Iperf is a tool to measure network performance by generating traffic", \
    "OS Update classifies traffic from operating system updates.", \
    "Diameter is an authentication, accounting and authorization protocol for network services. It was designed to replace RADIUS.", \
    "Hike Messenger is a free IM application.", \
    "MQTT is a lightweight messaging protocol for small sensors and mobile devices.", \
    "DiDi is a voice over ip and instant messaging software.", \
    "DCE/RPC is the remote procedure call system developed for the Distributed Computing Environment (DCE).", \
    "IDrive is a cloud based storage and backup service.", \
    "Spreecast is a streaming service for private and commercial videos.", \
    "Simfy is an online music listening service", \
    "Dota 2 is a free to play online multiplayer game.", \
    "QVoD is an all-in-one media player.", \
    "Hulu is a video-on-demand streaming portal.", \
    "Microsoft Exchange is a groupware server to manage mails, contacts and calendars.", \
    "Microsoft Dynamics NAV is an enterprise resource planning software product.", \
    "Fuze is a free online meeting service.", \
    "Tibia is a online role playing game developed by CipSoft.", \
    "Kakao is the company behind the application KakaoTalk and the underlying platform.", \
    "Destiny is a Massively Multiplayer Online First-Person Shooter (MMOFPS) developed by Bungie.", \
    "VyprVPN is a personal VPN solution.", \
    "TACACS provides access control for routers, network access servers and other networked computing devices via one or more centralized servers.",\
    "Threema is an encrypted instant messaging application for Android, Windows Phone and iOS.", \
    "NTLM (NT LAN Manager) is a Microsoft security protocol used for authentication mechanisms.", \
    "Twitch is a live streaming platform which is focused on video gaming and e-sport videos.", \
    "Wowza Streaming Engine is a streaming media server software which allows to stream different formats. They offer also a client application for android and iOS named GoCoder.", \
    "Runtastic is a fitness tracking application for mobile devices, which can be used to track and share activities.", \
    "Telegram is an encrypted instant messaging application.", \
    "StreetVoice is a social network for sharing self made music.", \
    "WHOIS is a protocol for querying registered users of an Internet resource.", \
    "FLUTE is a protocol used to deliver files over the Internet or unidirectional systems from one or more senders to one or more receivers.", \
    "The Media Gateway Control Protocol (Megaco) is a protocol for controlling media gateways.", \
    "Age of Warring Empire is a RPG game in China.", \
    "Magine TV is a tv streaming plattform.",\
    "QUIC is a multiplexed stream transport over UDP", \
    "LivePerson is a Live Chat Software for companies.", \
    "Doook is a Java based chat application.", \
    "Speedtest is an internet connection quality measurement tool.", \
    "BlueJeans is a mobile messaging and voice app for iPhone and Android.", \
    "IEC61850 is a standard for the design of the automation of electrical stations.", \
    "SCADA is a control and data transfer protocol used in industrial applications.", \
    "Cassandra Query Language (CQL) is the client protocol used to access Cassandra NoSQL databases.", \
    "Cassandra Internode Communication (CIC) is the protocol used for Cassandra server to server traffic.", \
    "Periscope is an application for streaming live videos.", \
    "Thrift is a protocol for skalable, interoperational services",\
    "PlayStation Network is the protocol of the corresponding traffic of the PlayStation video game console like PS3, PS4 or PS Vita.",\
    "Supercell is an online gaming company.",\
    "Skype for Business is a communication software for IM, VoIP and online meetings.",\
    "T3 is a proprietary protocol for RMI communication with  Oracle WebLogic Server.",\
    "USER1",\
	"USER2",\
	"USER3",\
	"USER4",\
	"USER5",\
	"USER6",\
	"USER7",\
	"USER8",\
	"USER9",\
	"USER10",\
	"USER11",\
	"USER12",\
	"USER13",\
	"USER14",\
	"USER15",\
	"USER16",\
	"USER17",\
	"USER18",\
	"USER19",\
	"USER20",\
	"USER11",\
	"USER22",\
	"USER23",\
	"USER24",\
	"USER25",\
	"USER26",\
	"USER27",\
	"USER28",\
	"USER29",\
	"USER30",\
	"USER31",\
	"USER32",\
	"USER33",\
	"USER34",\
	"USER35",\
	"USER36",\
	"USER37",\
	"USER38",\
	"USER39",\
	"USER40",\
	"USER41",\
	"USER42",\
	"USER43",\
	"USER44",\
	"USER45",\
	"USER46",\
	"USER47",\
	"USER48",\
	"USER49",\
	"USER50",\
	"USER51",\
	"USER52",\
	"USER53",\
	"USER54",\
	"USER55",\
	"USER56",\
	"USER57",\
	"USER58",\
	"USER59",\
	"USER60",\
	"USER61",\
	"USER62",\
	"USER63",\
	"USER64",\
	"USER65",\
	"USER66",\
	"USER67",\
	"USER68",\
	"USER69",\
	"USER70",\
	"USER71",\
	"USER72",\
	"USER73",\
	"USER74",\
	"USER75",\
	"USER76",\
	"USER77",\
	"USER78",\
	"USER79",\
	"USER80",\
	"USER81",\
	"USER82",\
	"USER83",\
	"USER84",\
	"USER85",\
	"USER86",\
	"USER87",\
	"USER88",\
	"USER89",\
	"USER90",\
	"USER91",\
	"USER92",\
	"USER93",\
	"USER94",\
	"USER95",\
	"USER96",\
	"USER97",\
	"USER98",\
	"USER99",\
	"USER100"


    /* debug features */
#if defined(IPOQUE_INTERNAL_REDZONE_CHECKING) && !defined(IPQ_MEMCHECK_HASH_USER_BUFFER)
#  define IPQ_MEMCHECK_HASH_USER_BUFFER
#endif


#ifdef __cplusplus
}
#endif
#endif
