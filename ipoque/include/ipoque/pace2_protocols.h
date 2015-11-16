/********************************************************************************/
/**
 ** \file       pace2_protocols.h
 ** \brief      PACE 2 protocol definitions
 ** \copyright  ipoque GmbH
 **/
/********************************************************************************/

#ifndef PACE2_PROTOCOLS_H
#define PACE2_PROTOCOLS_H

/* Includes *********************************************************************/
#include "pace2_basic_def.h"

/* Public Types *****************************************************************/

/**
 * @brief Enum defining all available protocols.
**/
typedef enum pace2_protocols {
    PACE2_PROTOCOL_UNKNOWN = 0,
    PACE2_PROTOCOL_BITTORRENT,
    PACE2_PROTOCOL_EDONKEY,
    PACE2_PROTOCOL_GNUTELLA,
    PACE2_PROTOCOL_WINMX,
    PACE2_PROTOCOL_DIRECTCONNECT,
    PACE2_PROTOCOL_APPLEJUICE,
    PACE2_PROTOCOL_SOULSEEK,
    PACE2_PROTOCOL_ARES,
    PACE2_PROTOCOL_FREENET,
    PACE2_PROTOCOL_MUTE,
    PACE2_PROTOCOL_XDCC,
    PACE2_PROTOCOL_SKYPE,
    PACE2_PROTOCOL_SIP,
    PACE2_PROTOCOL_MSN,
    PACE2_PROTOCOL_YAHOO,
    PACE2_PROTOCOL_OSCAR,
    PACE2_PROTOCOL_IRC,
    PACE2_PROTOCOL_XMPP,
    PACE2_PROTOCOL_HTTP,
    PACE2_PROTOCOL_POP,
    PACE2_PROTOCOL_SMTP,
    PACE2_PROTOCOL_IMAP,
    PACE2_PROTOCOL_USENET,
    PACE2_PROTOCOL_FTP,
    PACE2_PROTOCOL_DNS,
    PACE2_PROTOCOL_RTSP,
    PACE2_PROTOCOL_FILETOPIA,
    PACE2_PROTOCOL_MANOLITO,
    PACE2_PROTOCOL_IMESH,
    PACE2_PROTOCOL_SSL,
    PACE2_PROTOCOL_FLASH,
    PACE2_PROTOCOL_MMS,
    PACE2_PROTOCOL_MPEG,
    PACE2_PROTOCOL_QUICKTIME,
    PACE2_PROTOCOL_PANDO,
    PACE2_PROTOCOL_OPENVPN,
    PACE2_PROTOCOL_IPSEC,
    PACE2_PROTOCOL_GRE,
    PACE2_PROTOCOL_NOT_DETECTED,
    PACE2_PROTOCOL_H323,
    PACE2_PROTOCOL_WINDOWSMEDIA,
    PACE2_PROTOCOL_REALMEDIA,
    PACE2_PROTOCOL_TVANTS,
    PACE2_PROTOCOL_SOPCAST,
    PACE2_PROTOCOL_TVUPLAYER,
    PACE2_PROTOCOL_PPSTREAM,
    PACE2_PROTOCOL_PPLIVE,
    PACE2_PROTOCOL_IAX,
    PACE2_PROTOCOL_VTUN,
    PACE2_PROTOCOL_MGCP,
    PACE2_PROTOCOL_GADUGADU,
    PACE2_PROTOCOL_ZATTOO,
    PACE2_PROTOCOL_WINNY,
    PACE2_PROTOCOL_QQ,
    PACE2_PROTOCOL_QQLIVE,
    PACE2_PROTOCOL_FEIDIAN,
    PACE2_PROTOCOL_SSH,
    PACE2_PROTOCOL_POPO,
    PACE2_PROTOCOL_THUNDER,
    PACE2_PROTOCOL_UUSEE,
    PACE2_PROTOCOL_VNC,
    PACE2_PROTOCOL_ICMP,
    PACE2_PROTOCOL_DHCP,
    PACE2_PROTOCOL_IGMP,
    PACE2_PROTOCOL_EGP,
    PACE2_PROTOCOL_STEAM,
    PACE2_PROTOCOL_HALFLIFE2,
    PACE2_PROTOCOL_XBOX,
    PACE2_PROTOCOL_SOFTETHER,
    PACE2_PROTOCOL_SCTP,
    PACE2_PROTOCOL_SMB,
    PACE2_PROTOCOL_TELNET,
    PACE2_PROTOCOL_NTP,
    PACE2_PROTOCOL_NFS,
    PACE2_PROTOCOL_RTP,
    PACE2_PROTOCOL_TOR,
    PACE2_PROTOCOL_SSDP,
    PACE2_PROTOCOL_WORLDOFWARCRAFT,
    PACE2_PROTOCOL_AVI,
    PACE2_PROTOCOL_VPN_X,
    PACE2_PROTOCOL_HAMACHI_VPN,
    PACE2_PROTOCOL_SKINNY,
    PACE2_PROTOCOL_CITRIX,
    PACE2_PROTOCOL_OGG,
    PACE2_PROTOCOL_PALTALK,
    PACE2_PROTOCOL_MOVE,
    PACE2_PROTOCOL_POSTGRES,
    PACE2_PROTOCOL_OSPF,
    PACE2_PROTOCOL_BGP,
    PACE2_PROTOCOL_QUAKE,
    PACE2_PROTOCOL_SECONDLIFE,
    PACE2_PROTOCOL_MYSQL,
    PACE2_PROTOCOL_BATTLEFIELD,
    PACE2_PROTOCOL_PCANYWHERE,
    PACE2_PROTOCOL_RDP,
    PACE2_PROTOCOL_SNMP,
    PACE2_PROTOCOL_KONTIKI,
    PACE2_PROTOCOL_VEOHTV,
    PACE2_PROTOCOL_KERBEROS,
    PACE2_PROTOCOL_IP_IN_IP,
    PACE2_PROTOCOL_GTP,
    PACE2_PROTOCOL_RADIUS,
    PACE2_PROTOCOL_STUN,
    PACE2_PROTOCOL_SYSLOG,
    PACE2_PROTOCOL_TDS,
    PACE2_PROTOCOL_NETBIOS,
    PACE2_PROTOCOL_MDNS,
    PACE2_PROTOCOL_IPP,
    PACE2_PROTOCOL_LDAP,
    PACE2_PROTOCOL_WARCRAFT3,
    PACE2_PROTOCOL_XDMCP,
    PACE2_PROTOCOL_OOVOO,
    PACE2_PROTOCOL_FRING,
    PACE2_PROTOCOL_MAPI,
    PACE2_PROTOCOL_L2TP,
    PACE2_PROTOCOL_ISAKMP,
    PACE2_PROTOCOL_RTCP,
    PACE2_PROTOCOL_TFTP,
    PACE2_PROTOCOL_MSSQL,
    PACE2_PROTOCOL_PPP,
    PACE2_PROTOCOL_PPTP,
    PACE2_PROTOCOL_STEALTHNET,
    PACE2_PROTOCOL_SAP,
    PACE2_PROTOCOL_ICMPV6,
    PACE2_PROTOCOL_YOURFREEDOM,
    PACE2_PROTOCOL_VOIPSWITCH_VOIPTUNNEL,
    PACE2_PROTOCOL_DHCPV6,
    PACE2_PROTOCOL_MEEBO,
    PACE2_PROTOCOL_FUNSHION,
    PACE2_PROTOCOL_AFP,
    PACE2_PROTOCOL_AIMINI,
    PACE2_PROTOCOL_CLUBPENGUIN,
    PACE2_PROTOCOL_FLORENSIA,
    PACE2_PROTOCOL_TEAMSPEAK,
    PACE2_PROTOCOL_MAPLESTORY,
    PACE2_PROTOCOL_OSH,
    PACE2_PROTOCOL_PS3,
    PACE2_PROTOCOL_DOFUS,
    PACE2_PROTOCOL_WII,
    PACE2_PROTOCOL_WORLD_OF_KUNG_FU,
    PACE2_PROTOCOL_FIESTA,
    PACE2_PROTOCOL_SPLASHFIGHTER,
    PACE2_PROTOCOL_CROSSFIRE,
    PACE2_PROTOCOL_WAP_WSP,
    PACE2_PROTOCOL_WAP_WTP_WSP,
    PACE2_PROTOCOL_WAP_WTLS,
    PACE2_PROTOCOL_MULTIMEDIA_MESSAGING,
    PACE2_PROTOCOL_GUILDWARS,
    PACE2_PROTOCOL_ARMAGETRON,
    PACE2_PROTOCOL_RIM_PROPRIETARY,
    PACE2_PROTOCOL_RFACTOR,
    PACE2_PROTOCOL_RDT,
    PACE2_PROTOCOL_TEAMVIEWER,
    PACE2_PROTOCOL_GAMEKIT,
    PACE2_PROTOCOL_NETMOTION,
    PACE2_PROTOCOL_TEREDO,
    PACE2_PROTOCOL_SPOTIFY,
    PACE2_PROTOCOL_IMPLUS,
    PACE2_PROTOCOL_ULTRASURF,
    PACE2_PROTOCOL_VIBER,
    PACE2_PROTOCOL_TANGO,
    PACE2_PROTOCOL_IPLAYER,
    PACE2_PROTOCOL_JBK3K,
    PACE2_PROTOCOL_OPERAMINI,
    PACE2_PROTOCOL_BOLT,
    PACE2_PROTOCOL_SCYDO,
    PACE2_PROTOCOL_WHATSAPP,
    PACE2_PROTOCOL_WEBEX,
    PACE2_PROTOCOL_MOJO,
    PACE2_PROTOCOL_IMO,
    PACE2_PROTOCOL_CITRIX_GOTO,
    PACE2_PROTOCOL_COMODOUNITE,
    PACE2_PROTOCOL_GOOBER,
    PACE2_PROTOCOL_VENTRILO,
    PACE2_PROTOCOL_MYPEOPLE,
    PACE2_PROTOCOL_WEBSOCKET,
    PACE2_PROTOCOL_EBUDDY,
    PACE2_PROTOCOL_SSTP,
    PACE2_PROTOCOL_ADOBE_CONNECT,
    PACE2_PROTOCOL_JAP,
    PACE2_PROTOCOL_LDP,
    PACE2_PROTOCOL_WUALA,
    PACE2_PROTOCOL_MSRP,
    PACE2_PROTOCOL_LYNC,
    PACE2_PROTOCOL_SOCKS,
    PACE2_PROTOCOL_AUDIOGALAXY,
    PACE2_PROTOCOL_MIG33,
    PACE2_PROTOCOL_RHAPSODY,
    PACE2_PROTOCOL_SUDAPHONE,
    PACE2_PROTOCOL_WEBQQ,
    PACE2_PROTOCOL_PDPROXY,
    PACE2_PROTOCOL_SILVERLIGHT,
    PACE2_PROTOCOL_CYBERGHOST,
    PACE2_PROTOCOL_FIX,
    PACE2_PROTOCOL_ORACLE_DB,
    PACE2_PROTOCOL_RSVP,
    PACE2_PROTOCOL_LOTUS_NOTES,
    PACE2_PROTOCOL_POISON_IVY,
    PACE2_PROTOCOL_NETFLOW,
    PACE2_PROTOCOL_WECHAT,
    PACE2_PROTOCOL_SOAP,
    PACE2_PROTOCOL_KIK_MESSENGER,
    PACE2_PROTOCOL_MPLUS,
    PACE2_PROTOCOL_LINE,
    PACE2_PROTOCOL_IPERF,
    PACE2_PROTOCOL_DIAMETER,
    PACE2_PROTOCOL_HIKE_MESSENGER,
    PACE2_PROTOCOL_MQTT,
    PACE2_PROTOCOL_DCE_RPC,
    PACE2_PROTOCOL_IDRIVE,
    PACE2_PROTOCOL_DOTA2,
    PACE2_PROTOCOL_QVOD,
    PACE2_PROTOCOL_MSEXCHANGE,
    PACE2_PROTOCOL_MSNAV,
    PACE2_PROTOCOL_TIBIA,
    PACE2_PROTOCOL_KAKAO,
    PACE2_PROTOCOL_DESTINY,
    PACE2_PROTOCOL_VYPR_VPN,
    PACE2_PROTOCOL_TACACS,
    PACE2_PROTOCOL_THREEMA,
    PACE2_PROTOCOL_NTLM,
    PACE2_PROTOCOL_TELEGRAM,
    PACE2_PROTOCOL_WHOIS,
    PACE2_PROTOCOL_LAYER3_IPV4,
    PACE2_PROTOCOL_LAYER3_IPV6,
    PACE2_PROTOCOL_LAYER4_TCP,
    PACE2_PROTOCOL_LAYER4_UDP,
    PACE2_PROTOCOL_RTMP,
    PACE2_PROTOCOL_NNTP,
    PACE2_PROTOCOL_FLUTE,
    PACE2_PROTOCOL_MEGACO,
    PACE2_PROTOCOL_TWITCH,
    PACE2_PROTOCOL_QUIC,
    PACE2_PROTOCOL_FUZE,
    PACE2_PROTOCOL_AOWE,
    PACE2_PROTOCOL_DOOOK,
    PACE2_PROTOCOL_SPEEDTEST,
    PACE2_PROTOCOL_IEC61850,
    PACE2_PROTOCOL_SCADA,
    PACE2_PROTOCOL_SHOUTCAST,
    PACE2_PROTOCOL_CASSANDRA_QUERY_LANGUAGE,
    PACE2_PROTOCOL_CASSANDRA_INTERNODE_COMMUNICATION,
    PACE2_PROTOCOL_THRIFT,
    PACE2_PROTOCOL_PLAYSTATION,
    PACE2_PROTOCOL_SUPERCELL,
    PACE2_PROTOCOL_SKYPE_FOR_BUSINESS,
    PACE2_PROTOCOL_T3,

    PACE2_PROTOCOL_COUNT

} PACE2_protocols;

/**
 * @brief Struct representing all available protocols as a bitmask.
**/
typedef struct {
#if __BYTE_ORDER == __LITTLE_ENDIAN
    u32 ukn:1;                    //!< unknown
    u32 bit:1;                    //!< BitTorrent
    u32 edk:1;                    //!< eDonkey
    u32 gnu:1;                    //!< Gnutella
    u32 winmx:1;                  //!< WinMX
    u32 directconnect:1;          //!< DirectConnect
    u32 apple:1;                  //!< AppleJuice
    u32 soul:1;                   //!< Soulseek
    u32 ares:1;                   //!< Ares
    u32 freenet:1;                //!< Freenet
    u32 mute:1;                   //!< Mute
    u32 xdcc:1;                   //!< XDCC
    u32 skype:1;                  //!< Skype
    u32 sip:1;                    //!< SIP
    u32 msn:1;                    //!< MSN
    u32 yahoo:1;                  //!< Yahoo
    u32 oscar:1;                  //!< Oscar
    u32 irc:1;                    //!< IRC
    u32 xmpp:1;                   //!< XMPP
    u32 http:1;                   //!< HTTP
    u32 pop:1;                    //!< POP
    u32 smtp:1;                   //!< SMTP
    u32 imap:1;                   //!< IMAP
    u32 usenet:1;                 //!< Usenet
    u32 ftp:1;                    //!< FTP
    u32 dns:1;                    //!< DNS
    u32 rtsp:1;                   //!< RTSP
    u32 filetopia:1;              //!< Filetopia
    u32 manolito:1;               //!< Manolito
    u32 imesh:1;                  //!< iMesh
    u32 ssl:1;                    //!< SSL
    u32 flash:1;                  //!< FLASH
    u32 mms:1;                    //!< MMS
    u32 mpeg:1;                   //!< MPEG
    u32 quicktime:1;              //!< QUICKTIME
    u32 pando:1;                  //!< Pando
    u32 openvpn:1;                //!< OpenVPN
    u32 ipsec:1;                  //!< IPSEC
    u32 gre:1;                    //!< GRE
    u32 notdetect:1;              //!< undetected
    u32 h323:1;                   //!< H323
    u32 windowsmedia:1;           //!< WINDOWSMEDIA
    u32 realmedia:1;              //!< REALMEDIA
    u32 tvants:1;                 //!< TVANTS
    u32 sopcast:1;                //!< SOPCAST
    u32 tvuplayer:1;              //!< TVUPLAYER
    u32 ppstream:1;               //!< PPSTREAM
    u32 pplive:1;                 //!< PPLIVE
    u32 iax:1;                    //!< IAX
    u32 vtun:1;                   //!< VTUN
    u32 mgcp:1;                   //!< MGCP
    u32 gadugadu:1;               //!< Gadu-Gadu
    u32 zattoo:1;                 //!< ZATTOO
    u32 winny:1;                  //!< WINNY
    u32 qq:1;                     //!< QQ
    u32 qqlive:1;                 //!< QQLive
    u32 feidian:1;                //!< Feidian
    u32 ssh:1;                    //!< SSH
    u32 popo:1;                   //!< POPO
    u32 thunder:1;                //!< Thunder/Webthunder
    u32 uusee:1;                  //!< UUSEE
    u32 vnc:1;                    //!< VNC
    u32 icmp:1;                   //!< ICMP
    u32 dhcp:1;                   //!< DHCP
#elif __BYTE_ORDER == __BIG_ENDIAN
    u32 dhcp:1;                   //!< DHCP
    u32 icmp:1;                   //!< ICMP
    u32 vnc:1;                    //!< VNC
    u32 uusee:1;                  //!< UUSEE
    u32 thunder:1;                //!< Thunder/Webthunder
    u32 popo:1;                   //!< POPO
    u32 ssh:1;                    //!< SSH
    u32 feidian:1;                //!< Feidian
    u32 qqlive:1;                 //!< QQLive
    u32 qq:1;                     //!< QQ
    u32 winny:1;                  //!< WINNY
    u32 zattoo:1;                 //!< ZATTOO
    u32 gadugadu:1;               //!< Gadu-Gadu
    u32 mgcp:1;                   //!< MGCP
    u32 vtun:1;                   //!< VTUN
    u32 iax:1;                    //!< IAX
    u32 pplive:1;                 //!< PPLIVE
    u32 ppstream:1;               //!< PPSTREAM
    u32 tvuplayer:1;              //!< TVUPLAYER
    u32 sopcast:1;                //!< SOPCAST
    u32 tvants:1;                 //!< TVANTS
    u32 realmedia:1;              //!< REALMEDIA
    u32 windowsmedia:1;           //!< WINDOWSMEDIA
    u32 h323:1;                   //!< H323
    u32 notdetect:1;              //!< undetected
    u32 gre:1;                    //!< GRE
    u32 ipsec:1;                  //!< IPSEC
    u32 openvpn:1;                //!< OpenVPN
    u32 pando:1;                  //!< Pando
    u32 quicktime:1;              //!< QUICKTIME
    u32 mpeg:1;                   //!< MPEG
    u32 mms:1;                    //!< MMS
    u32 flash:1;                  //!< FLASH
    u32 ssl:1;                    //!< SSL
    u32 imesh:1;                  //!< iMesh
    u32 manolito:1;               //!< Manolito
    u32 filetopia:1;              //!< Filetopia
    u32 rtsp:1;                   //!< RTSP
    u32 dns:1;                    //!< DNS
    u32 ftp:1;                    //!< FTP
    u32 usenet:1;                 //!< Usenet
    u32 imap:1;                   //!< IMAP
    u32 smtp:1;                   //!< SMTP
    u32 pop:1;                    //!< POP
    u32 http:1;                   //!< HTTP
    u32 xmpp:1;                   //!< XMPP
    u32 irc:1;                    //!< IRC
    u32 oscar:1;                  //!< Oscar
    u32 yahoo:1;                  //!< Yahoo
    u32 msn:1;                    //!< MSN
    u32 sip:1;                    //!< SIP
    u32 skype:1;                  //!< Skype
    u32 xdcc:1;                   //!< XDCC
    u32 mute:1;                   //!< Mute
    u32 freenet:1;                //!< Freenet
    u32 ares:1;                   //!< Ares
    u32 soul:1;                   //!< Soulseek
    u32 apple:1;                  //!< AppleJuice
    u32 directconnect:1;          //!< DirectConnect
    u32 winmx:1;                  //!< WinMX
    u32 gnu:1;                    //!< Gnutella
    u32 edk:1;                    //!< eDonkey
    u32 bit:1;                    //!< BitTorrent
    u32 ukn:1;                    //!< unknown
#endif

#if __BYTE_ORDER == __LITTLE_ENDIAN
    u32 igmp:1;                   //!< IGMP
    u32 egp:1;                    //!< EGP
    u32 steam:1;                  //!< Steam
    u32 hl2:1;                    //!< Halflife2
    u32 xbox:1;                   //!< XBOX
    u32 softether:1;              //!< SoftEthernet
    u32 sctp:1;                   //!< SCTP
    u32 smb:1;                    //!< SMB/CIFS
    u32 telnet:1;                 //!< Telnet
    u32 ntp:1;                    //!< NTP
    u32 nfs:1;                    //!< NFS
    u32 rtp:1;                    //!< RTP
    u32 tor:1;                    //!< TOR
    u32 ssdp:1;                   //!< SSDP
    u32 worldofwarcraft:1;        //!< World of Warcraft
    u32 avi:1;                    //!< AVI
    u32 vpnx:1;                   //!< VPN-X
    u32 hamachi:1;                //!< HamachiVPN
    u32 skinny:1;                 //!< Skinny
    u32 citrix:1;                 //!< Citrix
    u32 ogg:1;                    //!< OGG
    u32 paltalk:1;                //!< Paltalk
    u32 move:1;                   //!< Move
    u32 postgres:1;               //!< PostgreSQL
    u32 ospf:1;                   //!< OSPF
    u32 bgp:1;                    //!< BGP
    u32 quake:1;                  //!< Quake
    u32 secondlife:1;             //!< Second Life
    u32 mysql:1;                  //!< MySQL
    u32 battlefield:1;            //!< Battlefield
    u32 pcanywhere:1;             //!< PCAnywhere
    u32 rdp:1;                    //!< RDP
    u32 snmp:1;                   //!< SNMP
    u32 kontiki:1;                //!< Kontiki
    u32 veohtv:1;                 //!< VeohTV
    u32 kerberos:1;               //!< Kerberos
    u32 ipip:1;                   //!< IP in IP
    u32 gtp:1;                    //!< GTP
    u32 radius:1;                 //!< RADIUS
    u32 stun:1;                   //!< STUN
    u32 syslog:1;                 //!< Syslog
    u32 tds:1;                    //!< TDS
    u32 netbios:1;                //!< NETBIOS
    u32 mdns:1;                   //!< MulticastDNS
    u32 ipp:1;                    //!< IPP
    u32 ldap:1;                   //!< LDAP
    u32 warcraft3:1;              //!< WARCRAFT3
    u32 xdmcp:1;                  //!< XDMCP
    u32 oovoo:1;                  //!< ooVoo
    u32 fring:1;                  //!< Fring
    u32 mapi:1;                   //!< Mapi
    u32 l2tp:1;                   //!< L2TP
    u32 isakmp:1;                 //!< ISAKMP
    u32 rtcp:1;                   //!< RTCP
    u32 tftp:1;                   //!< TFTP
    u32 mssql:1;                  //!< msSQL
    u32 ppp:1;                    //!< PPP
    u32 pptp:1;                   //!< PPTP
    u32 stealthnet:1;             //!< StealthNet
    u32 sap:1;                    //!< SAP
    u32 icmpv6:1;                 //!< ICMPv6
    u32 yourfreedom:1;            //!< YourFreedom Tunnel
    u32 voipswitchvoiptunnel:1;   //!< VoipSwitch VoIP Tunnel
    u32 dhcpv6:1;                 //!< DHCPv6
#elif __BYTE_ORDER == __BIG_ENDIAN
    u32 dhcpv6:1;                 //!< DHCPv6
    u32 voipswitchvoiptunnel:1;   //!< VoipSwitch VoIP Tunnel
    u32 yourfreedom:1;            //!< YourFreedom Tunnel
    u32 icmpv6:1;                 //!< ICMPv6
    u32 sap:1;                    //!< SAP
    u32 stealthnet:1;             //!< StealthNet
    u32 pptp:1;                   //!< PPTP
    u32 ppp:1;                    //!< PPP
    u32 mssql:1;                  //!< msSQL
    u32 tftp:1;                   //!< TFTP
    u32 rtcp:1;                   //!< RTCP
    u32 isakmp:1;                 //!< ISAKMP
    u32 l2tp:1;                   //!< L2TP
    u32 mapi:1;                   //!< Mapi
    u32 fring:1;                  //!< Fring
    u32 oovoo:1;                  //!< ooVoo
    u32 xdmcp:1;                  //!< XDMCP
    u32 warcraft3:1;              //!< WARCRAFT3
    u32 ldap:1;                   //!< LDAP
    u32 ipp:1;                    //!< IPP
    u32 mdns:1;                   //!< MulticastDNS
    u32 netbios:1;                //!< NETBIOS
    u32 tds:1;                    //!< TDS
    u32 syslog:1;                 //!< Syslog
    u32 stun:1;                   //!< STUN
    u32 radius:1;                 //!< RADIUS
    u32 gtp:1;                    //!< GTP
    u32 ipip:1;                   //!< IP in IP
    u32 kerberos:1;               //!< Kerberos
    u32 veohtv:1;                 //!< VeohTV
    u32 kontiki:1;                //!< Kontiki
    u32 snmp:1;                   //!< SNMP
    u32 rdp:1;                    //!< RDP
    u32 pcanywhere:1;             //!< PCAnywhere
    u32 battlefield:1;            //!< Battlefield
    u32 mysql:1;                  //!< MySQL
    u32 secondlife:1;             //!< Second Life
    u32 quake:1;                  //!< Quake
    u32 bgp:1;                    //!< BGP
    u32 ospf:1;                   //!< OSPF
    u32 postgres:1;               //!< PostgreSQL
    u32 move:1;                   //!< Move
    u32 paltalk:1;                //!< Paltalk
    u32 ogg:1;                    //!< OGG
    u32 citrix:1;                 //!< Citrix
    u32 skinny:1;                 //!< Skinny
    u32 hamachi:1;                //!< HamachiVPN
    u32 vpnx:1;                   //!< VPN-X
    u32 avi:1;                    //!< AVI
    u32 worldofwarcraft:1;        //!< World of Warcraft
    u32 ssdp:1;                   //!< SSDP
    u32 tor:1;                    //!< TOR
    u32 rtp:1;                    //!< RTP
    u32 nfs:1;                    //!< NFS
    u32 ntp:1;                    //!< NTP
    u32 telnet:1;                 //!< Telnet
    u32 smb:1;                    //!< SMB/CIFS
    u32 sctp:1;                   //!< SCTP
    u32 softether:1;              //!< SoftEthernet
    u32 xbox:1;                   //!< XBOX
    u32 hl2:1;                    //!< Halflife2
    u32 steam:1;                  //!< Steam
    u32 egp:1;                    //!< EGP
    u32 igmp:1;                   //!< IGMP

#endif

#if __BYTE_ORDER == __LITTLE_ENDIAN
    u32 meebo:1;                  //!< MEEBO
    u32 funshion:1;               //!< Funshion
    u32 afp:1;                    //!< AFP
    u32 aimini:1;                 //!< Aimini
    u32 clubpenguin:1;            //!< ClubPenguin
    u32 florensia:1;              //!< Florensia
    u32 teamspeak:1;              //!< TeamSpeak
    u32 maplestory:1;             //!< MapleStory
    u32 osh:1;                    //!< Octoshape
    u32 ps3:1;                    //!< PS3
    u32 dofus:1;                  //!< Dofus
    u32 wii:1;                    //!< WII
    u32 wokf:1;                   //!< World of Kung Fu
    u32 fiesta:1;                 //!< Fiesta
    u32 splashfighter:1;          //!< SplashFighter
    u32 crossfire:1;              //!< CrossFire
    u32 wapwsp:1;                 //!< WAP-WSP
    u32 wapwtpwsp:1;              //!< WAP-WTP-WSP
    u32 wapwtls:1;                //!< WAP-WTLS
    u32 multimediamessaging:1;    //!< MultimediaMessaging
    u32 guildwars:1;              //!< Guildwars
    u32 armagetron:1;             //!< Armagetron
    u32 rim_prop:1;               //!< RIM proprietary
    u32 rfactor:1;                //!< rFactor
    u32 rdt:1;                    //!< RealDataTransport
    u32 teamviewer:1;             //!< TeamViewer
    u32 gamekit:1;                //!< GameKit
    u32 netmotion:1;              //!< NetMotion
    u32 teredo:1;                 //!< Teredo
    u32 spotify:1;                //!< Spotify
    u32 implus:1;                 //!< IMplus
    u32 ultrasurf:1;              //!< UltraSurf
    u32 viber:1;                  //!< Viber
    u32 tango:1;                  //!< Tango
    u32 iplayer:1;                //!< iPlayer
    u32 jbk3k:1;                  //!< JBK3000
    u32 operamini:1;              //!< OperaMini
    u32 bolt:1;                   //!< BOLT
    u32 scydo:1;                  //!< Scydo
    u32 whatsapp:1;               //!< WhatsApp
    u32 webex:1;                  //!< Webex
    u32 mojo:1;                   //!< Mojo
    u32 imo:1;                    //!< IMO
    u32 citrixgoto:1;             //!< CitrixGoTo
    u32 comodounite:1;            //!< ComodoUnite
    u32 goober:1;                 //!< Goober
    u32 ventrilo:1;               //!< Ventrilo
    u32 mypeople:1;               //!< MyPeople
    u32 websocket:1;              //!< WebSocket
    u32 ebuddy:1;                 //!< eBuddy
    u32 sstp:1;                   //!< SSTP
    u32 adobeconnect:1;           //!< AdobeConnect
    u32 jap:1;                    //!< JAP
    u32 ldp:1;                    //!< LDP
    u32 wuala:1;                  //!< Wuala
    u32 msrp:1;                   //!< MSRP
    u32 lync:1;                   //!< Lync
    u32 socks:1;                  //!< Socks
    u32 audiogalaxy:1;            //!< Audiogalaxy
    u32 mig33:1;                  //!< Mig33
    u32 rhapsody:1;               //!< Rhapsody
    u32 sudaphone:1;              //!< Sudaphone
    u32 webqq:1;                  //!< WebQQ
    u32 pdproxy:1;                //!< PDProxy
#elif __BYTE_ORDER == __BIG_ENDIAN
    u32 pdproxy:1;                //!< PDProxy
    u32 webqq:1;                  //!< WebQQ
    u32 sudaphone:1;              //!< Sudaphone
    u32 rhapsody:1;               //!< Rhapsody
    u32 mig33:1;                  //!< Mig33
    u32 audiogalaxy:1;            //!< Audiogalaxy
    u32 socks:1;                  //!< Socks
    u32 lync:1;                   //!< Lync
    u32 msrp:1;                   //!< MSRP
    u32 wuala:1;                  //!< Wuala
    u32 ldp:1;                    //!< LDP
    u32 jap:1;                    //!< JAP
    u32 adobeconnect:1;           //!< AdobeConnect
    u32 sstp:1;                   //!< SSTP
    u32 ebuddy:1;                 //!< eBuddy
    u32 websocket:1;              //!< WebSocket
    u32 mypeople:1;               //!< MyPeople
    u32 ventrilo:1;               //!< Ventrilo
    u32 goober:1;                 //!< Goober
    u32 comodounite:1;            //!< ComodoUnite
    u32 citrixgoto:1;             //!< CitrixGoTo
    u32 imo:1;                    //!< IMO
    u32 mojo:1;                   //!< Mojo
    u32 webex:1;                  //!< Webex
    u32 whatsapp:1;               //!< WhatsApp
    u32 scydo:1;                  //!< Scydo
    u32 bolt:1;                   //!< BOLT
    u32 operamini:1;              //!< OperaMini
    u32 jbk3k:1;                  //!< JBK3000
    u32 iplayer:1;                //!< iPlayer
    u32 tango:1;                  //!< Tango
    u32 viber:1;                  //!< Viber
    u32 ultrasurf:1;              //!< UltraSurf
    u32 implus:1;                 //!< IMplus
    u32 spotify:1;                //!< Spotify
    u32 teredo:1;                 //!< Teredo
    u32 netmotion:1;              //!< NetMotion
    u32 gamekit:1;                //!< GameKit
    u32 teamviewer:1;             //!< TeamViewer
    u32 rdt:1;                    //!< RealDataTransport
    u32 rfactor:1;                //!< rFactor
    u32 rim_prop:1;               //!< RIM proprietary
    u32 armagetron:1;             //!< Armagetron
    u32 guildwars:1;              //!< Guildwars
    u32 multimediamessaging:1;    //!< MultimediaMessaging
    u32 wapwtls:1;                //!< WAP-WTLS
    u32 wapwtpwsp:1;              //!< WAP-WTP-WSP
    u32 wapwsp:1;                 //!< WAP-WSP
    u32 crossfire:1;              //!< CrossFire
    u32 splashfighter:1;          //!< SplashFighter
    u32 fiesta:1;                 //!< Fiesta
    u32 wokf:1;                   //!< World of Kung Fu
    u32 wii:1;                    //!< WII
    u32 dofus:1;                  //!< Dofus
    u32 ps3:1;                    //!< PS3
    u32 osh:1;                    //!< Octoshape
    u32 maplestory:1;             //!< MapleStory
    u32 teamspeak:1;              //!< TeamSpeak
    u32 florensia:1;              //!< Florensia
    u32 clubpenguin:1;            //!< ClubPenguin
    u32 aimini:1;                 //!< Aimini
    u32 afp:1;                    //!< AFP
    u32 funshion:1;               //!< Funshion
    u32 meebo:1;                  //!< MEEBO
#endif

#if __BYTE_ORDER == __LITTLE_ENDIAN
    u32 silverlight:1;            //!< Silverlight
    u32 cyberghost:1;             //!< CyberGhost
    u32 fix:1;                    //!< FIX
    u32 oracledb:1;               //!< Oracle Database
    u32 rsvp:1;                   //!< RSVP
    u32 lotusnotes:1;             //!< Lotus Notes
    u32 poisonivy:1;              //!< Poison Ivy
    u32 netflow:1;                //!< NetFlow
    u32 wechat:1;                 //!< WeChat
    u32 soap:1;                   //!< SOAP
    u32 kik:1;                    //!< Kik Messenger
    u32 mplus:1;                  //!< MPlus
    u32 line:1;                   //!< Line
    u32 iperf:1;                  //!< Iperf
    u32 diameter:1;               //!< Diameter
    u32 hike:1;                   //!< Hike Messenger
    u32 mqtt:1;                   //!< MQTT
    u32 dce_rpc:1;                //!< DCE_RPC
    u32 idrive:1;                 //!< IDrive
    u32 dota2:1;                  //!< Dota 2
    u32 qvod:1;                   //!< QVOD
    u32 msexchange:1;             //!< Microsoft Exchange
    u32 msnav:1;                  //!< Microsoft Dynamics NAV
    u32 tibia:1;                  //!< Tibia
    u32 kakao:1;                  //!< Kakao
    u32 destiny:1;                //!< Destiny
    u32 vyprvpn:1;                //!< VyprVPN
    u32 tacacs:1;                 //!< TACACS
    u32 threema:1;                //!< Threema
    u32 ntlm:1;                   //!< NTLM
    u32 telegram:1;               //!< Telegram
    u32 whois:1;                  //!< WHOIS
    u32 ipv4:1;                   //!< IPv4
    u32 ipv6:1;                   //!< IPv6
    u32 tcp:1;                    //!< TCP
    u32 udp:1;                    //!< UDP
    u32 rtmp:1;                   //!< RTMP
    u32 nntp:1;                   //!< NNTP
    u32 flute:1;                  //!< Flute
    u32 megaco:1;                 //!< Megaco
    u32 twitch:1;                 //!< Twitch
    u32 quic:1;                   //!< Quic
    u32 fuze:1;                   //!< Fuze
    u32 aowe:1;                   //!< Age of Warring Empire
    u32 doook:1;                  //!< Doook
    u32 speedtest:1;              //!< Speedtest
    u32 iec61850:1;               //!< IEC61850
    u32 scada:1;                  //!< SCADA
    u32 shoutcast:1;              //!< Shoutcast
    u32 cassandra_query_language:1;                       //!< Cassandra Query Language
    u32 cassandra_internode_communication:1;              //!< Cassandra Query Language
    u32 thrift:1;                 //!< Thrift
    u32 playstation:1;            //!< PlayStation
    u32 supercell:1;              //!< Supercell
    u32 skype_for_business:1;     //!< Skype for Business
    u32 t3:1;                     //!< T3

    /* following field is added just for padding reasons and does not carry a value */
    u32 padding:(256 - PACE2_PROTOCOL_COUNT);
#elif __BYTE_ORDER == __BIG_ENDIAN
    /* following field is added just for padding reasons and does not carry a value */
    u32 padding:(256 - PACE2_PROTOCOL_COUNT);

    u32 t3:1;                     //!< T3
    u32 skype_for_business:1;     //!< Skype for Business
    u32 supercell:1;              //!< Supercell
    u32 playstation:1;            //!< PlayStation
    u32 thrift:1;                 //!< Thrift
    u32 cassandra_internode_communication:1;              //!< Cassandra Query Language
    u32 cassandra_query_language:1;                       //!< Cassandra Query Language
    u32 shoutcast:1;              //!< Shoutcast
    u32 scada:1;                  //!< SCADA
    u32 iec61850:1;               //!< IEC61850
    u32 speedtest:1;              //!< Speedtest
    u32 doook:1;                  //!< Doook
    u32 aowe:1;                   //!< Age of Warring Empire
    u32 fuze:1;                   //!< Fuze
    u32 quic:1;                   //!< Quic
    u32 twitch:1;                 //!< Twitch
    u32 megaco:1;                 //!< Megaco
    u32 flute:1;                  //!< Flute
    u32 nntp:1;                   //!< NNTP
    u32 rtmp:1;                   //!< RTMP
    u32 udp:1;                    //!< UDP
    u32 tcp:1;                    //!< TCP
    u32 ipv6:1;                   //!< IPv6
    u32 ipv4:1;                   //!< IPv4
    u32 whois:1;                  //!< WHOIS
    u32 telegram:1;               //!< Telegram
    u32 ntlm:1;                   //!< NTLM
    u32 threema:1;                //!< Threema
    u32 tacacs:1;                 //!< TACACS
    u32 vyprvpn:1;                //!< VyprVPN
    u32 destiny:1;                //!< Destiny
    u32 kakao:1;                  //!< Kakao
    u32 tibia:1;                  //!< Tibia
    u32 msnav:1;                  //!< Microsoft Dynamics NAV
    u32 msexchange:1;             //!< Microsoft Exchange
    u32 qvod:1;                   //!< QVOD
    u32 dota2:1;                  //!< Dota 2
    u32 idrive:1;                 //!< IDrive
    u32 dce_rpc:1;                //!< DCE_RPC
    u32 mqtt:1;                   //!< MQTT
    u32 hike:1;                   //!< Hike Messenger
    u32 diameter:1;               //!< Diameter
    u32 iperf:1;                  //!< Iperf
    u32 line:1;                   //!< Line
    u32 mplus:1;                  //!< MPlus
    u32 kik:1;                    //!< Kik Messenger
    u32 soap:1;                   //!< SOAP
    u32 wechat:1;                 //!< WeChat
    u32 netflow:1;                //!< NetFlow
    u32 poisonivy:1;              //!< Poison Ivy
    u32 lotusnotes:1;             //!< Lotus Notes
    u32 rsvp:1;                   //!< RSVP
    u32 oracledb:1;               //!< Oracle Database
    u32 fix:1;                    //!< FIX
    u32 cyberghost:1;             //!< CyberGhost
    u32 silverlight:1;            //!< Silverlight
#endif
} PACE2_protocols_struct;

#define PACE2_PROTOCOLS_SHORT_STRS \
    "ukn",\
    "bit",\
    "edk",\
    "gnu",\
    "winmx",\
    "directconnect",\
    "apple",\
    "soul",\
    "ares",\
    "freenet",\
    "mute",\
    "xdcc",\
    "skype",\
    "sip",\
    "msn",\
    "yahoo",\
    "oscar",\
    "irc",\
    "xmpp",\
    "http",\
    "pop",\
    "smtp",\
    "imap",\
    "usenet",\
    "ftp",\
    "dns",\
    "rtsp",\
    "filetopia",\
    "manolito",\
    "imesh",\
    "ssl",\
    "flash",\
    "mms",\
    "mpeg",\
    "quicktime",\
    "pando",\
    "openvpn",\
    "ipsec",\
    "gre",\
    "notdetect",\
    "h323",\
    "windowsmedia",\
    "realmedia",\
    "tvants",\
    "sopcast",\
    "tvuplayer",\
    "ppstream",\
    "pplive",\
    "iax",\
    "vtun",\
    "mgcp",\
    "gadugadu",\
    "zattoo",\
    "winny",\
    "qq",\
    "qqlive",\
    "feidian",\
    "ssh",\
    "popo",\
    "thunder",\
    "uusee",\
    "vnc",\
    "icmp",\
    "dhcp",\
    "igmp",\
    "egp",\
    "steam",\
    "hl2",\
    "xbox",\
    "softether",\
    "sctp",\
    "smb",\
    "telnet",\
    "ntp",\
    "nfs",\
    "rtp",\
    "tor",\
    "ssdp",\
    "worldofwarcraft",\
    "avi",\
    "vpnx",\
    "hamachi",\
    "skinny",\
    "citrix",\
    "ogg",\
    "paltalk",\
    "move",\
    "postgres",\
    "ospf",\
    "bgp",\
    "quake",\
    "secondlife",\
    "mysql",\
    "battlefield",\
    "pcanywhere",\
    "rdp",\
    "snmp",\
    "kontiki",\
    "veohtv",\
    "kerberos",\
    "ipip",\
    "gtp",\
    "radius",\
    "stun",\
    "syslog",\
    "tds",\
    "netbios",\
    "mdns",\
    "ipp",\
    "ldap",\
    "warcraft3",\
    "xdmcp",\
    "oovoo",\
    "fring",\
    "mapi",\
    "l2tp",\
    "isakmp",\
    "rtcp",\
    "tftp",\
    "mssql",\
    "ppp",\
    "pptp",\
    "stealthnet",\
    "sap",\
    "icmpv6",\
    "yourfreedom",\
    "voipswitchvoiptunnel",\
    "dhcpv6",\
    "meebo",\
    "funshion",\
    "afp",\
    "aimini",\
    "clubpenguin",\
    "florensia",\
    "teamspeak",\
    "maplestory",\
    "osh",\
    "ps3",\
    "dofus",\
    "wii",\
    "wokf",\
    "fiesta",\
    "splashfighter",\
    "crossfire",\
    "wapwsp",\
    "wapwtpwsp",\
    "wapwtls",\
    "multimediamessaging",\
    "guildwars",\
    "armagetron",\
    "rim_prop",\
    "rfactor",\
    "rdt",\
    "teamviewer",\
    "gamekit",\
    "netmotion",\
    "teredo",\
    "spotify",\
    "implus",\
    "ultrasurf",\
    "viber",\
    "tango",\
    "iplayer",\
    "jbk3k",\
    "operamini",\
    "bolt",\
    "scydo",\
    "whatsapp",\
    "webex",\
    "mojo",\
    "imo",\
    "citrixgoto",\
    "comodounite",\
    "goober",\
    "ventrilo",\
    "mypeople",\
    "websocket",\
    "ebuddy",\
    "sstp",\
    "adobeconnect",\
    "jap",\
    "ldp",\
    "wuala",\
    "msrp",\
    "lync",\
    "socks",\
    "audiogalaxy",\
    "mig33",\
    "rhapsody",\
    "sudaphone",\
    "webqq",\
    "pdproxy",\
    "silverlight",\
    "cyberghost",\
    "fix",\
    "oracledb",\
    "rsvp",\
    "lotusnotes",\
    "poisonivy",\
    "netflow",\
    "wechat",\
    "soap",\
    "kik",\
    "mplus",\
    "line",\
    "iperf",\
    "diameter",\
    "hike",\
    "mqtt",\
    "dce_rpc",\
    "idrive",\
    "dota2",\
    "qvod",\
    "msexchange",\
    "msnav",\
    "tibia",\
    "kakao",\
    "destiny",\
    "vyprvpn",\
    "tacacs",\
    "threema",\
    "ntlm",\
    "telegram",\
    "whois",\
    "ipv4",\
    "ipv6",\
    "tcp",\
    "udp",\
    "rtmp",\
    "nntp",\
    "flute",\
    "megaco",\
    "twitch",\
    "quic",\
    "fuze",\
    "aowe",\
    "doook",\
    "speedtest",\
    "iec61850",\
    "scada",\
    "shoutcast",\
    "cql",\
    "cic",\
    "thrift",\
    "playstation",\
    "supercell",\
    "skype-for-business",\
    "t3"

#define PACE2_PROTOCOLS_LONG_STRS \
    "unknown",\
    "BitTorrent",\
    "eDonkey",\
    "Gnutella",\
    "WinMX",\
    "DirectConnect",\
    "AppleJuice",\
    "Soulseek",\
    "Ares",\
    "Freenet",\
    "Mute",\
    "XDCC",\
    "Skype",\
    "SIP",\
    "MSN",\
    "Yahoo",\
    "Oscar",\
    "IRC",\
    "XMPP",\
    "HTTP",\
    "POP",\
    "SMTP",\
    "IMAP",\
    "Usenet",\
    "FTP",\
    "DNS",\
    "RTSP",\
    "Filetopia",\
    "Manolito",\
    "iMesh",\
    "SSL",\
    "FLASH",\
    "MMS",\
    "MPEG",\
    "QUICKTIME",\
    "Pando",\
    "OpenVPN",\
    "IPSEC",\
    "GRE",\
    "undetected",\
    "H323",\
    "WINDOWSMEDIA",\
    "REALMEDIA",\
    "TVANTS",\
    "SOPCAST",\
    "TVUPLAYER",\
    "PPSTREAM",\
    "PPLIVE",\
    "IAX",\
    "VTUN",\
    "MGCP",\
    "Gadu-Gadu",\
    "ZATTOO",\
    "WINNY",\
    "QQ",\
    "QQLive",\
    "Feidian",\
    "SSH",\
    "POPO",\
    "Thunder/Webthunder",\
    "UUSEE",\
    "VNC",\
    "ICMP",\
    "DHCP",\
    "IGMP",\
    "EGP",\
    "Steam",\
    "Halflife2",\
    "XBOX",\
    "SoftEthernet",\
    "SCTP",\
    "SMB/CIFS",\
    "Telnet",\
    "NTP",\
    "NFS",\
    "RTP",\
    "TOR",\
    "SSDP",\
    "World of Warcraft",\
    "AVI",\
    "VPN-X",\
    "HamachiVPN",\
    "Skinny",\
    "Citrix",\
    "OGG",\
    "Paltalk",\
    "Move",\
    "PostgreSQL",\
    "OSPF",\
    "BGP",\
    "Quake",\
    "Second Life",\
    "MySQL",\
    "Battlefield",\
    "PCAnywhere",\
    "RDP",\
    "SNMP",\
    "Kontiki",\
    "VeohTV",\
    "Kerberos",\
    "IP in IP",\
    "GTP",\
    "RADIUS",\
    "STUN",\
    "Syslog",\
    "TDS",\
    "NETBIOS",\
    "MulticastDNS",\
    "IPP",\
    "LDAP",\
    "WARCRAFT3",\
    "XDMCP",\
    "ooVoo",\
    "Fring",\
    "Mapi",\
    "L2TP",\
    "ISAKMP",\
    "RTCP",\
    "TFTP",\
    "msSQL",\
    "PPP",\
    "PPTP",\
    "StealthNet",\
    "SAP",\
    "ICMPv6",\
    "YourFreedom Tunnel",\
    "VoipSwitch VoIP Tunnel",\
    "DHCPv6",\
    "MEEBO",\
    "Funshion",\
    "AFP",\
    "Aimini",\
    "ClubPenguin",\
    "Florensia",\
    "TeamSpeak",\
    "MapleStory",\
    "Octoshape",\
    "PS3",\
    "Dofus",\
    "WII",\
    "World of Kung Fu",\
    "Fiesta",\
    "SplashFighter",\
    "CrossFire",\
    "WAP-WSP",\
    "WAP-WTP-WSP",\
    "WAP-WTLS",\
    "MultimediaMessaging",\
    "Guildwars",\
    "Armagetron",\
    "RIM proprietary",\
    "rFactor",\
    "RealDataTransport",\
    "TeamViewer",\
    "GameKit",\
    "NetMotion",\
    "Teredo",\
    "Spotify",\
    "IMplus",\
    "UltraSurf",\
    "Viber",\
    "Tango",\
    "iPlayer",\
    "JBK3000",\
    "OperaMini",\
    "BOLT",\
    "Scydo",\
    "WhatsApp",\
    "Webex",\
    "Mojo",\
    "IMO",\
    "CitrixGoTo",\
    "ComodoUnite",\
    "Goober",\
    "Ventrilo",\
    "MyPeople",\
    "WebSocket",\
    "eBuddy",\
    "SSTP",\
    "AdobeConnect",\
    "JAP",\
    "LDP",\
    "Wuala",\
    "MSRP",\
    "Lync",\
    "Socks",\
    "Audiogalaxy",\
    "Mig33",\
    "Rhapsody",\
    "Sudaphone",\
    "WebQQ",\
    "PDProxy",\
    "Silverlight",\
    "CyberGhost",\
    "FIX",\
    "Oracle Database",\
    "RSVP",\
    "Lotus Notes",\
    "Poison Ivy",\
    "NetFlow",\
    "WeChat",\
    "SOAP",\
    "Kik Messenger",\
    "MPlus",\
    "Line",\
    "Iperf",\
    "Diameter",\
    "Hike Messenger",\
    "MQTT",\
    "DCE_RPC",\
    "IDrive",\
    "Dota 2",\
    "QVOD",\
    "Microsoft Exchange",\
    "Microsoft Dynamics NAV",\
    "Tibia",\
    "Kakao",\
    "Destiny",\
    "VyprVPN",\
    "TACACS",\
    "Threema",\
    "NTLM",\
    "Telegram",\
    "WHOIS",\
    "IPv4",\
    "IPv6",\
    "TCP",\
    "UDP",\
    "RTMP",\
    "NNTP",\
    "FLUTE",\
    "Megaco",\
    "Twitch",\
    "Quic",\
    "Fuze Meeting",\
    "Age of Warring Empire",\
    "Doook",\
    "Speedtest",\
    "IEC61850",\
    "SCADA",\
    "Shoutcast",\
    "Cassandra Query Language",\
    "Cassandra Internode Communication",\
    "Thrift",\
    "PlayStation Network",\
    "Supercell",\
    "Skype for Business",\
    "T3"

#define PACE2_PROTOCOLS_DESCRIPTIONS \
    "All traffic that is not classified yet we call unknown.",\
    "BitTorrent is the protocol of the corresponding P2P network.",\
    "The eDonkey network (also known as the eDonkey2000 network or eD2k) is a decentralized, mostly server-based, peer-to-peer file sharing network protocol best suited to share big files among users, and to provide long term availability of said files.",\
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
    "SIP is traffic of voice calls initiated over the protocol standardized SIP.",\
    "MSN is the protocol used by the Microsoft MSN Instant Messaging application family.",\
    "Yahoo Messenger is a popular instant messaging application with support for chat, voice calls and file transfer.",\
    "OSCAR is the protocol used by AOL Messenger applications.",\
    "IRC is a protocol used by a number of popular Instant Messaging applications.",\
    "Extensible Messaging and Presence Protocol (XMPP) (formerly named Jabber) is an open, XML-based protocol originally aimed at near-real-time, extensible instant messaging (IM) and presence information (e.g., buddy lists), but now expanded into the broader realm of message-oriented middle ware.",\
    "HTTP is used to access web servers but is also transport protocol for a number of streaming applications.",\
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
    "H323 is traffic of H.323 initiated calls.",\
    "WINDOWSMEDIA is the protocol of Windows Media Streaming.",\
    "REALMEDIA is the protocol of RealNetworks RealMedia streaming application and browser plugin.",\
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
    "QQ is an Instant Messaging application popular in China and the Asian region.",\
    "QQLive is P2PTV software and a service provided by Tencent Corporation of China. It is one of mostly installed and used P2PTV software and service in China.",\
    "Feidian (Boiling Point) is a P2PTV application from the People's Republic of China.",\
    "SSH is a protocol used to provide secure, encrypted communication (file transfer etc.) over IP networks.",\
    "PoPo is the protocol of an instant messaging application popular in China.",\
    "Thunder is a P2P filesharing application mainly used in China.",\
    "UUSee is the protocol of a P2P network with the same name.",\
    "Similar to RDP VNC provides a way to access the graphical user interface/desktop of remote systems.",\
    "ICMP is used to exchange status information and error messages over IP networks.",\
    "DHCP is a protocol used to dynamically configure systems in IP networks.",\
    "IGMP is used to manage multicast groups.",\
    "EGP is an important routing protocol of the Internet.",\
    "Steam is a protocol used by popular multiplayer online games like Half-Life.",\
    "Half-Life 2 is the protocol of the popular multiplayer online game.",\
    "XBOX is the protocol of the corresponding traffic of the XBox video game console.",\
    "SoftEthernet is the protocol of an multi-protocol VPN software.",\
    "SCTP is a reliable, connection-oriented protocol at layer 4 of the OSI model.",\
    "CIFS/SMB is a protocol used to provide file access to Microsoft Windows systems usually.",\
    "Telnet (teletype network) is a network protocol used on the Internet or local area networks to provide a bidirectional interactive communications facility. Typically, telnet provides access to a command-line interface on a remote host via a virtual terminal connection which consists of an 8-bit byte oriented data connection over the Transmission Control Protocol (TCP). User data is interspersed in-band with TELNET control information.",\
    "NTP is used to sync time of computer systems.",\
    "The NFS protocol is used to share files over a network.",\
    "RTP is a standard protocol used to transport audio and video streams over IP networks.",\
    "Tor is a protocol used to provide secure communication and anonymity over IP networks.",\
    "SSDP is used to discover UPnP devices.",\
    "World of Warcraft is the protocol of the corresponding multiplayer online game.",\
    "AVI is the protocol of AVI Video Streams over HTTP.",\
    "VPN-X is the protocol used by the vpnx tunnel application.",\
    "Hamachi is a zero-configuration virtual private network (VPN) shareware application capable of establishing direct links between computers that are behind NAT firewalls without requiring reconfiguration (in most cases); in other words, it establishes a connection over the Internet that very closely emulates the connection that would exist if the computers were connected over a local area network.",\
    "The Skinny Call Control Protocol (SCCP, or short Skinny) is a proprietary network terminal control protocol originally developed by Selsius Corporation.",\
    "Citrix is the protocol of the terminal server application with the same name.",\
    "Ogg Vorbis is an open-source streaming technology.",\
    "Paltalk is an internet chat service that allows users to communicate via instant messaging, voice and video chat.",\
    "Move is a streaming protocol over HTTP.",\
    "PostgreSQL is the protocol for corresponding database traffic.",\
    "OSPF is an important routing protocol of the Internet.",\
    "BGP is an important routing protocol of the Internet.",\
    "Quake refers to the protocol which is used for communication between systems during multiplayer games.",\
    "Second Life is the protocol for the corresponding virtual world application.",\
    "MySQL is the protocol for the traffic of the MySQL Database.",\
    "Battlefield is the protocol for the corresponding online game.",\
    "PCAnywhere is the protocol of the pcAnywhere remote desktop application.",\
    "Proprietary Microsoft protocol is used to remotely connect to Windows systems and take control over the desktop.",\
    "SNMP is used for monitoring and managing network components such as switches, routers etc.",\
    "Kontiki is the protocol of the content delivery platform with the same name.",\
    "Veoh TV is the HTTP application the Veoh Internet television service.",\
    "Kerberos is a computer network authentication protocol, which allows nodes communicating over a non-secure network to prove their identity to one another in a secure manner. It is also a suite of free software published by Massachusetts Institute of Technology (MIT) that implements this protocol. Its designers aimed primarily at a client-server model, and it provides mutual authentication — both the user and the server verify each other's identity. Kerberos protocol messages are protected against eavesdropping and replay attacks.",\
    "IP in IP is an IP tunneling protocol that encapsulates one IP packet in another IP packet.",\
    "GPRS Tunnelling Protocol (GTP) is a group of IP-based communications protocols used to carry General Packet Radio Service (GPRS) within GSM and UMTS networks.",\
    "Remote Authentication Dial In User Service (RADIUS) is a networking protocol that provides centralized Authentication, Authorization, and Accounting (AAA) management for computers to connect and use a network service.",\
    "STUN is an Internet standards-track suite of methods, including a network protocol, used in NAT traversal for applications of real-time voice, video, messaging, and other interactive IP communications.",\
    "Syslog is a standard for forwarding log messages in an Internet Protocol (IP) computer network.",\
    "Tabular Data Stream (TDS) is an application layer protocol, used to transfer data between a database server and a client. Initially designed and developed by Sybase Inc. for their Sybase SQL Server relational database engine in 1984, and later by Microsoft in Microsoft SQL Server.",\
    "NetBIOS is an acronym for Network Basic Input/Output System. It provides services related to the session layer of the OSI model allowing applications on separate computers to communicate over a local area network.",\
    "MDNS is part of the zero configurartion networking (zeroconf) and is used for automatic resolution and distribution of computer hostnames (multicast DNS).",\
    "Internet Printing Protocol (IPP) provides a standard network protocol for remote printing as well as for managing print jobs, media size, resolution, and so forth.",\
    "The Lightweight Directory Access Protocol, or LDAP, is an application protocol for querying and modifying directory services running over TCP/IP.",\
    "Warcraft3 is the protocol of the corresponding multiplayer online game.",\
    "TX Display Manager Control Protocol for the X window system mandates that the X server starts autonomously and connects to the display manager.",\
    "OOVOO is a voice over ip protocol.",\
    "Fring is the corresponding protocol to the application with the same name, which support Voice over IP and instant messaging over Skype, ICQ, MSN, AIM, Yahoo and SIP.",\
    "MAPI/RPC is a proprietary protocol that Microsoft Outlook uses to communicate with Microsoft Exchange.",\
    "L2TP is used to tunnel PPP frames over IP networks.",\
    "ISAKMP is a protocol for establishing Security Associations (SA) and cryptographic keys in an Internet environment. The protocol is defined by RFC 2408.",\
    "The RTP Control Protocol (RTCP) is a sister protocol of the Real-time Transport Protocol (RTP). Its basic functionality and packet structure is defined in the RTP specification RFC 3550.",\
    "Trivial File Transfer Protocol (TFTP) is a file transfer protocol, with the functionality of a very basic form of File Transfer Protocol (FTP).",\
    "MSSQL is the protocol for the corresponding database application. This protocol is obsolete and will be detected as TDS.",\
    "Point-to-Point Protocol, or PPP, is a data link protocol commonly used to establish a direct connection between two networking nodes. It can provide connection authentication, transmission encryption privacy, and compression.",\
    "The Point-to-Point Tunneling Protocol (PPTP) is a method for implementing virtual private networks (VPN). PPTP uses a control channel over TCP and a GRE tunnel operating to encapsulate PPP packets.",\
    "StealthNet is the protocol to the corresponding P2P application.",\
    "SAP is the protocol used between SAP Server and SAP Clients.",\
    "ICMPv6 is ICMP (is used to exchange status information and error messages over IP networks) for IPv6.",\
    "YourFreedom is a tunnel protocol.",\
    "VoipSwitch or VoipTunnel is a tunnel protocol with voip inside.",\
    "DHCPv6 is the DHCP for IPv6.",\
    "Meebo is the protocol for the corresponding instant messanger.",\
    "Funshion is a streaming protocol.",\
    "The Apple Filing Protocol (AFP) is a network protocol that offers file services for Mac OS X and original Mac OS.",\
    "Aimini is a P2P protocol.",\
    "ClubPenguin is the protocol of the corresponding Massive Multiplayer Online Game, which is provided by ClubPenguin.com.",\
    "Florencia is the protocol of the corresponding massive multiplayer online game.",\
    "TeamSpeak is the protocol of the corresponding VoIP application.",\
    "MapleStory is the protocol of the corresponding massive multiplayer online role play game.",\
    "Octoshape is the protocol of the corresponding streaming application.",\
    "PS3 is the protocol of the corresponding traffic of the PS3 video game console.",\
    "Dofus is the protocol of the corresponding massive multiplayer online role play game.",\
    "Wii is the protocol of the corresponding traffic of the wii video game console.",\
    "World of Kung Fu is the protocol of the corresponding massive multiplayer online role play game.",\
    "Fiesta is the protocol of the corresponding massive multiplayer online role play game.",\
    "SplashFighter is the protocol of the corresponding multiplayer online game.",\
    "Crossfire is an open source, cooperative multiplayer graphical RPG and adventure game.",\
    "WAP-WSP Wireless Application Protocol using the Wireless Session Protocol is used to deliver Internet contents to devices with slower Internet connections like mobile phones.",\
    "WAP-WTP-WSP Wireless Application Protocol using the Wireless Transport Protocol and Wireless Session Protocol is used to deliver Internet contents to devices with slower Internet connections like mobile phones.",\
    "WAP-WTLS Wireless Application Protocol using the Wireless Transport Layer Security is used to securely deliver Internet contents to devices with slower Internet connections like mobile phones.",\
    "Multimedia Messaging Service (MMS) is a protocol for sending messages that include multimedia content from mobile phones.",\
    "Guild Wars is an episodic series of multiplayer online role-playing games developed by ArenaNet and published by NCsoft.",\
    "Armagetron Advanced is a multiplayer game in 3D.",\
    "RIM proprietary protocol is a protocol used by blackberry.",\
    "rFactor is a computer racing simulator.",\
    "RDT is an audio/video transport protocol from RealNetworks.",\
    "TeamViewer is a remote administration tool.",\
    "GameKit is a framework from Apple for multiplayer/social games.",\
    "NetMotion is a mobile VPN solution.",\
    "Teredo is a IPv6 in IPv4/UDP tunnel.",\
    "Spotify is a music listening service.",\
    "IM+ is a multi-protocol multi-platform messenger client.",\
    "UltraSurf is a proxy solution for anonymous browsing.",\
    "Viber is VoIP application for iphone/android/blackberry.",\
    "Tango is VoIP application for iphone/android.",\
    "iPlayer is an internet television and radio service developed by BBC.",\
    "JBK3000 sends measurement data over LAN from a automatic tester which is used to measure various types of flammable liquid petroleum products.",\
    "OperaMini is the protocol used by the mobile web browser of the same name from Opera.",\
    "Bolt is the protocol used by the mobile web browser Bolt for smartphones.",\
    "Scydo is VoIP application for iphone/android.",\
    "WhatsApp is a cross-platform mobile messaging app for iPhone, BlackBerry, Android and Nokia.",\
    "Webex is Ciscos Web Conferencing and Collaboration Solution.",\
    "Mojo is a P2P software for sharing the iTunes library.",\
    "IMO is a web-based service that allows users to hold text, voice, and video chats on multiple instant messaging protocols.",\
    "CitrixGoTo is the protocol which is used by the Cirix GoTo... applications.",\
    "Comodo Unite is a VPN client for windows computers.",\
    "Goober is a VoIP / Instant messenger.",\
    "Ventrilo is a proprietary VoIP software which includes text chat.",\
    "MyPeople is a korean voip and im app.",\
    "WebSockets are an XMLHttpRequest replacement for HTTP.",\
    "eBuddy is a web and mobile multi messenger.",\
    "SSTP is the Secure Socket Tunneling Protocol, a VPN over SSL.",\
    "Adobe Connect is an enterprise web conferencing solution for online meetings.",\
    "JAP - JonDonym anonymous proxy servers - is an anonymization service.",\
    "LDP is a way for labeling servers to propagate labeling information, used e.g. for routing.",\
    "Wuala is a online storage service.",\
    "MSRP is a protcol used for transmitting IM, files and sharing images within a communication session. Message sessions are treated like media streams and can be set up by SIP (e.g.).",\
    "Lync is a communication software for IM, VoIP and online meetings.",\
    "Socks is proxy protocol for tunneling any kind of traffic via Socks proxy server.",\
    "Audiogalaxy is a streaming service that allows users stream private music from their PCs.",\
    "Mig33 is a mobile social network popular in Asia. Supports IM, blogs and minigames.",\
    "Rhapsody (Napster in europe) is a music streaming service.",\
    "Sudaphone is a popular korean VoIP and IM application.",\
    "WebQQ is a web desktop application.",\
    "PDProxy is a tunneling software.",\
    "Silverlight is Microsofts equivalent to Adobes Flash.",\
    "CyberGhost is a tunneling software.",\
    "The FIX (Financial Information eXchange) protocol is used for financial and trade related transactions.",\
    "Oracle Database is a database management system produced and marketed by Oracle Corporation.",\
    "RSVP is a protocol to reserve resources across a network.",\
    "Lotus Notes is a popular groupware solution.",\
    "Poison Ivy is a remote administration tool that mostly is used as trojan attached to other executables.",\
    "NetFlow is a network reporting protocol developed by Cisco.",\
    "WeChat is a voice and text messaging application for different smartphone operating systems.",\
    "SOAP is a protocol for exchanging structured information and is based on XML.",\
    "Kik Messenger is a free IM application.",\
    "MPlus is a messaging application for mobile phones.",\
    "Line is a free VOIP and messaging application.",\
    "Iperf is a tool to measure network performance by generating traffic.",\
    "Diameter is an authentication, accounting and authorization protocol for network services. It was designed to replace RADIUS.",\
    "Hike Messenger is a free IM application.",\
    "MQTT is a lightweight messaging protocol for small sensors and mobile devices.",\
    "DCE/RPC is the remote procedure call system developed for the Distributed Computing Environment (DCE).",\
    "IDrive is a cloud based storage and backup service.",\
    "Dota 2 is a free to play online multiplayer game.",\
    "QVoD is an all-in-one media player.",\
    "Microsoft Exchange is a groupware server to manage mails, contacts and calendars.",\
    "Microsoft Dynamics NAV is an enterprise resource planning software product.",\
    "Tibia is a online role playing game developed by CipSoft.",\
    "Kakao is the company behind the application KakaoTalk and the underlying platform.",\
    "Destiny is a Massively Multiplayer Online First-Person Shooter (MMOFPS) developed by Bungie.",\
    "VyprVPN is a personal VPN solution.",\
    "TACACS provides access control for routers, network access servers and other networked computing devices via one or more centralized servers.",\
    "Threema is an encrypted instant messaging application for Android, Windows Phone and iOS.",\
    "NTLM (NT LAN Manager) is a Microsoft security protocol used for authentication mechanisms.",\
    "Telegram is an encrypted instant messaging application.",\
    "WHOIS is a protocol for querying registered users of an Internet resource.",\
    "IPv4 is a Layer 3 protocol.",\
    "IPv6 is a Layer 3 protocol.",\
    "TCP is a Layer 4 protocol.",\
    "UDP is a Layer 4 protocol.",\
    "Real Time Messaging Protocol is a proprietary protocol for streaming audio, video for Flash player.",\
    "The Network News Transfer Protocol (NNTP) is the protocol used to transfer messages with Usenet.",\
    "FLUTE is a protocol used to deliver files over the Internet or unidirectional systems from one or more senders to one or more receivers.",\
    "The Media Gateway Control Protocol (Megaco) is a protocol for controlling media gateways.",\
    "Twitch is a live streaming platform which is focused on video gaming and e-sport videos.",\
    "QUIC is a multiplexed stream transport protocol over UDP.",\
    "Fuze is a free online meeting service.",\
    "Age of Warring Empire is a RPG game in China.",\
    "Doook is a Java based chat application.",\
    "Speedtest is a Internet connection quality measurement tool from Ookla.",\
    "IEC61850 is a standard for the design of the automation of electrical stations.",\
    "SCADA is a control and data transfer protocol used in industrial applications.",\
    "Shoutcast is the protocol of the corresponding media streaming server software developed by Nullsoft.",\
    "Cassandra Query Language (CQL) is the client protocol used to access Cassandra NoSQL databases.", \
    "Cassandra Internode Communication (CIC) is the protocol used for Cassandra server to server traffic.", \
    "Thrift is a protocol for skalable, interoperational services.", \
    "PlayStation Network is the protocol of the corresponding traffic of the PlayStation video game console like PS3, PS4 or PS Vita.",\
    "Supercell is an online gaming company.",\
    "Skype for Business is a communication software for IM, VoIP and online meetings.",\
    "T3 is a proprietary protocol for RMI communication with  Oracle WebLogic Server."


#endif /* PACE2_PROTOCOLS_H */

/*********************************************************************************
 ** EOF
 ********************************************************************************/
