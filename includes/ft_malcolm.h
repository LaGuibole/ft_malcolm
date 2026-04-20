# ifndef FT_MALCOLM_H
#define FT_MALCOLM_H

#include "libft.h"
#include "errors.h"
#include <net/if.h>
#include <arpa/inet.h> // inet_pton, inet ntop, inet_addr etc...
#include <netinet/in.h> // struct in_addr, AF_INET etc ...
#include <ifaddrs.h> // getifaddrs, free ifaddrs, struct ifaddrs
#include <sys/socket.h> // AF SOCKET, SOCK_RAW, socket, bind etc ..
#include <asm-generic/socket.h>
#include <linux/if_packet.h> // struct sockaddr_11, EHT_P_ARP
#include <net/ethernet.h>
#include <errno.h>

/*
	Structure for ft_malcom : 
		- src_ip / dest_ip = Arg string "10.12.255.255", will be converted uint32_t for comparison later
		- src_mac / dest_mac = MAC adresses stocked in 6 bytes array
		- sockfd =  FD for raw socket 
		- iface = network interface stocked as a string
*/
typedef struct s_malcolm {
	char    *src_ip; 
	uint8_t src_mac[6];
	char    *dest_ip;
	uint8_t dest_mac[6];
	int     sockfd;
	char    iface[IF_NAMESIZE];
} __attribute__((packed)) t_malcolm;

typedef struct s_eth_header {
	uint8_t		dest_mac[6];
	uint8_t 	src_mac[6];
	uint16_t	ether_type;
}	__attribute__((packed)) t_eth_header;

typedef struct s_arp_packet {
	uint16_t	hardware_type;
	uint16_t	protocol;
	uint8_t		hardware_len;
	uint8_t		protocol_len;
	uint16_t	op_code;
	uint8_t		sender_hardware_addr[6];
	uint32_t	sender_protocol_addr;
	uint8_t		target_hardware_addr[6];
	uint32_t	target_protocol_addr;
}	__attribute__((packed)) t_arp_packet;

typedef struct s_frame {
	t_eth_header	eth;
	t_arp_packet	arp;
}	__attribute__((packed)) t_frame;

int	parse_ip(const char *str);
int	parse_mac(const char *str, uint8_t mac[6]);
int	parse_args(t_malcolm *malcolm, char **argv);
int find_interface(t_malcolm *malcolm_ctx);
int init_socket(t_malcolm *malcolm_ctx);
int listen_for_request(t_malcolm *malcolm_ctx);

#endif