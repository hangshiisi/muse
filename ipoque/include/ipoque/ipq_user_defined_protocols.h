#ifndef __IPOQUE_API_INCLUDE_FILE__
#error CANNOT INCLUDE THIS .H FILE, INCLUDE IPQ_API.H
#endif

#ifndef __IPQ_USER_DEFINED_PROTOCOLS_H__
#define __IPQ_USER_DEFINED_PROTOCOLS_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef IPOQUE_USER_DEFINED_PROTOCOLS

	typedef struct ipoque_detection_user_defined_extend {
		u64 flags;
		 u32(*callback_extend) (struct ipoque_detection_module_struct *, void *);

#ifndef IPOQUE_DETECTION_USER_DEFINED_EXTEND_MATCH
#define IPOQUE_DETECTION_USER_DEFINED_EXTEND_MATCH	0x10
#endif							/* IPOQUE_DETECTION_USER_DEFINED_EXTEND_MATCH */

#ifndef IPOQUE_DETECTION_USER_DEFINED_EXTEND_NOT_MATCH
#define IPOQUE_DETECTION_USER_DEFINED_EXTEND_NOT_MATCH	0x20
#endif							/* IPOQUE_DETECTION_USER_DEFINED_EXTEND_NOT_MATCH */

#ifndef IPOQUE_DETECTION_USER_DEFINED_EXTEND_MAY_MATCH
#define IPOQUE_DETECTION_USER_DEFINED_EXTEND_MAY_MATCH	0x30
#endif							/* IPOQUE_DETECTION_USER_DEFINED_EXTEND_MAY_MATCH */

		void (*callback_accessor) (void *, u8 what);
#ifndef	IPOQUE_DETECTION_USER_DEFINED_EXTEND_LOCK
#define IPOQUE_DETECTION_USER_DEFINED_EXTEND_LOCK 0x2
#endif							/* IPOQUE_DETECTION_USER_DEFINED_EXTEND_LOCK */

#ifndef IPOQUE_DETECTION_USER_DEFINED_EXTEND_UNLOCK
#define IPOQUE_DETECTION_USER_DEFINED_EXTEND_UNLOCK 0x3
#endif							/* IPOQUE_DETECTION_USER_DEFINED_EXTEND_UNLOCK */
		void *datap;
	} ipoque_detection_user_defined_extend_t;


#define IPOQUE_USER_DETECTION_MAX_NAME_LEN				64
#define IPOQUE_USER_DETECTION_MAX_USED_SUBNETS                          100
#define IPOQUE_USER_DETECTION_MAX_USED_PORTS                            100
#define IPOQUE_USER_DETECTION_MAX_USED_TRANSPORT_LAYER_PROTOCOLS        10
#ifndef IPOQUE_USER_DETECTION_MAX_NUMBER_OF_HOSTS
#define IPOQUE_USER_DETECTION_MAX_NUMBER_OF_HOSTS                       100
#endif
#define IPOQUE_USER_DETECTION_MAX_NUMBER_OF_SSL_RULES                   10

	/* all values in the structure are in network byte order !!! */

	typedef struct ipoque_detection_user_defined_subnet {
		/* subnet in network byte order */
		u32 ip;
		/* subnet mask in network byte order */
		u32 mask;
	} ipoque_detection_user_defined_subnet_t;

	typedef struct ipoque_detection_user_defined_port_range {
		/* range start port in network byte order */
		u16 from_port;
		/* range end port in network byte order */
		u16 to_port;
	} ipoque_detection_user_defined_port_range_t;

	typedef struct ipoque_detection_user_defined_host_struct {
#define IPOQUE_DETECTION_USER_DEFINED_MAX_HOST_LEN      128
		/* host is limited to 128 bytes. it is a last match host rule */
		u32 hostlen;
		/* string containing the hostname */
		u8 host[IPOQUE_DETECTION_USER_DEFINED_MAX_HOST_LEN];
	} ipoque_detection_user_defined_host_struct_t;

	typedef enum { IPOQUE_USER_SSL_RULE_SUBJECT_ORGANIZATION_NAME,
		IPOQUE_USER_SSL_RULE_SUBJECT_COMMON_NAME
	} ipoque_user_ssl_rule_t;

	typedef struct ipoque_detection_user_defined_ssl_struct {
#define IPOQUE_DETECTION_USER_DEFINED_MAX_SSL_RULE_LEN      128
		/* SSL rule len is limited to 128 bytes, it's a suffix match rule */
		ipoque_user_ssl_rule_t rule_type;
		u32 rule_len;
		u8 rule[IPOQUE_DETECTION_USER_DEFINED_MAX_SSL_RULE_LEN];
	} ipoque_detection_user_defined_ssl_struct_t;

	typedef struct ipoque_detection_user_defined_direction_struct {
		/* 0 if direction is not used in filter, 1 otherwise */
		u8 direction_used;
		/* packet direction (0 or 1) */
		u8 direction;
	} ipoque_detection_user_defined_direction_struct_t;


	typedef struct ipoque_detection_user_defined_transport_layer_protocol_struct {
		/* range start for transport layer protocol number */
		u8 from_transport_layer_protocol;
		/* range end for transport layer protocol number */
		u8 to_transport_layer_protocol;
	} ipoque_detection_user_defined_transport_layer_protocol_struct_t;


	typedef struct ipoque_detection_user_defined_parameters_struct {
		/* null-terminated string that contains the name of the user-defined protocol */
		u8 name[IPOQUE_USER_DETECTION_MAX_NAME_LEN];
		/* number of used subnet structs */
		u32 number_of_subnets;
		/* array of subnet structs (see ipoque_detection_user_defined_subnet) */
		struct ipoque_detection_user_defined_subnet
		 subnets[IPOQUE_USER_DETECTION_MAX_USED_SUBNETS];
		/* port part */

		/* number of used source port ranges */
		u32 number_of_src_ports_ranges;
		/* array of source port range structs (see ipoque_detection_user_defined_port_range) */
		struct ipoque_detection_user_defined_port_range
		 src_port_ranges[IPOQUE_USER_DETECTION_MAX_USED_PORTS];
		/* number of used destination port ranges */
		u32 number_of_dst_ports_ranges;
		/* array of destination port range structs (see ipoque_detection_user_defined_port_range) */
		struct ipoque_detection_user_defined_port_range
		 dst_port_ranges[IPOQUE_USER_DETECTION_MAX_USED_PORTS];

		/* direction struct (see ipoque_detection_user_defined_direction_struct) */
		struct ipoque_detection_user_defined_direction_struct direction;

		/* number of used transport layer protocol structs */
		u32 number_of_transport_layer_protocols;
		/* array of transport layer protocol structs (see ipoque_detection_user_defined_transport_layer_protocol_struct) */
		struct ipoque_detection_user_defined_transport_layer_protocol_struct
		 transport_layer_protocols[IPOQUE_USER_DETECTION_MAX_USED_TRANSPORT_LAYER_PROTOCOLS];

		/* number of used protocols */
		u32 protocols_used;
		/* bitmask that contains the selected protocols */
		IPOQUE_PROTOCOL_BITMASK selected_protocols;

		/* should be set to allow a cdp reset of this rule by a new http request */
		u32 allow_reset_by_http;

		/* pointer to the extended struct (see ipoque_detection_user_defined_extend) */
		struct ipoque_detection_user_defined_extend *extend;

		/* number of used host structs */
		u32 number_of_hosts;
		/* array of host structs (see ipoque_detection_user_defined_host_struct) */
		struct ipoque_detection_user_defined_host_struct
		 hosts[IPOQUE_USER_DETECTION_MAX_NUMBER_OF_HOSTS];

		/* number of ssl rules */
		u32 number_of_ssl_rules;
		/* array of ssl rules (see ipoque_detection_user_defined_ssl_struct) */
		struct ipoque_detection_user_defined_ssl_struct
		 ssl_rules[IPOQUE_USER_DETECTION_MAX_NUMBER_OF_SSL_RULES];
	} ipoque_detection_user_defined_parameters_struct_t;


	/**
	 * registers a new user-defined protocol in the detection module. If the maximum number of
	 * user-defined protocols for the module is exceeded, the call will result in an error, otherwise it will succeed.
	 * @param ipoque_struct the detection module, not NULL
	 * @param ipoque_detection_protocol_id_number an arbitrary number to identify the user-defined protocol, must be less than IPOQUE_USER_DEFINED_MAX_PROTOCOLS
	 * @param parameter pointer to a struct that contains the parameters for the user-defined protocol (see ipoque_detection_user_defined_parameters_struct)
	 * @return returns 0 on success and a non-zero value in case of an error.
	 *
	 * works with IPOQUE_PACE_DYNAMIC_UPGRADE
	 * */
	u32 ipoque_detection_add_user_defined_protocol(struct
												   ipoque_detection_module_struct
												   *ipoque_struct, u32 ipoque_detection_protocol_id_number, struct
												   ipoque_detection_user_defined_parameters_struct
												   *parameter);

	/**
	 * returns a pointer to a struct defining the desired user-defined protocol,
	 * see ipoque_detection_add_user_defined_protocol() for a description of the struct.
	 * NULL is returned in case of an error.
	 * @param ipoque_struct the detection module, not NULL
	 * @return returns the desired ipoque_detection_user_defined_parameters_struct or NULL in case no user-defined
	 * protocol exists for the given number
	 *
	 * works with IPOQUE_PACE_DYNAMIC_UPGRADE
	 */
	const struct ipoque_detection_user_defined_parameters_struct
	*ipoque_detection_get_user_defined_protocol(struct
												ipoque_detection_module_struct
												*ipoque_struct, u32 protocol_number);

	/**
	 * resets all user-defined protocols for the given detection module. After
	 * calling the function, no more user-defined protocols are present.
	 * @param ipoque_struct the detection module, not NULL
	 * works with IPOQUE_PACE_DYNAMIC_UPGRADE
	 */
	void ipoque_detection_reset_all_user_defined_protocol(struct
														  ipoque_detection_module_struct
														  *ipoque_struct);

	struct ipoque_detection_user_defined_extend *ipoque_detectection_set_udp_extend(struct
																					ipoque_detection_user_defined_parameters_struct
																					*, struct
																					ipoque_detection_user_defined_extend
																					*);
	struct ipoque_detection_user_defined_extend *ipoque_detectection_get_udp_extend(struct
																					ipoque_detection_user_defined_parameters_struct
																					*);


#endif							/* IPOQUE_USER_DEFINED_PROTOCOLS */

#if defined( IPOQUE_USER_DEFINED_PROTOCOLS ) || defined( IPOQUE_CUSTOM_DEFINED_PROTOCOLS_2_0 ) || defined( IPOQUE_USE_PRX_PROTOCOLS_ONLY )
	/**
	 * returns the protocol number for the protocol that has been detected for the current packet
	 * @param ipoque_struct the detection module, not NULL
	 * @return protocol number, if no protocol has been detected (yet) the return value is IPOQUE_PROTOCOL_UNKNOWN
	 *
	 * works with IPOQUE_PACE_DYNAMIC_UPGRADE
	 */
	u32 ipoque_detection_get_protocol(struct
									  ipoque_detection_module_struct
									  *ipoque_struct);

	/**
	 * returns the protocol number for the protocol that has been detected for the current packet. In case a
	 * user-defined protocol has been detected, the number returned is the one for the protocol that has originally been detected for the packet
	 * without taking any user-defined filters into consideration.
	 * @param ipoque_struct the detection module, not NULL
	 * @return original protocol number, if no protocol has been detected (yet) the return value is IPOQUE_PROTOCOL_UNKNOWN
	 *
	 * works with IPOQUE_PACE_DYNAMIC_UPGRADE
	 */
	u32 ipoque_detection_get_original_protocol(struct
											   ipoque_detection_module_struct
											   *ipoque_struct);
#endif

#ifdef __cplusplus
}
#endif
#endif
