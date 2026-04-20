# ifndef FT_MALCOLM_H
#define FT_MALCOLM_H

#include "libft.h"

typedef struct s_malcolm {
    char    *src_ip;
    uint8_t src_mac[6];
    char    *dest_ip;
    uint8_t dest_mac[6];
    int     sockfd;
    char    iface[IF_NAME_SIZE];
} t_malcolm;

#endif