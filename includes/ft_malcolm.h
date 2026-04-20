# ifndef FT_MALCOLM_H
#define FT_MALCOLM_H

#include "libft.h"

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
    char    iface[IF_NAME_SIZE];
} t_malcolm;

int parse_ip(const char *str);


#endif