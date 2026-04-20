# ifndef FT_MALCOLM_H
#define FT_MALCOLM_H

#include "libft.h"
#include "errors.h"
#include <net/if.h>
#include <arpa/inet.h> // inet_pton, inet ntop, inet_addr etc...
#include <netinet/in.h> // struct in_addr, AF_INET etc ...
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
} t_malcolm;

int	parse_ip(const char *str);
int	parse_mac(const char *str, uint8_t mac[6]);
int	parse_args(t_malcolm *malcolm, char **argv);

#endif