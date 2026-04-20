#include "ft_malcolm.h"

int init_socket(t_malcolm *malcolm_ctx)
{
    malcolm_ctx->sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
    if (malcolm_ctx->sockfd == -1)
        return (ft_printf("ft_malcolm: socket: %s\n", strerror(errno)), 0);
    if (setsockopt(malcolm_ctx->sockfd, SOL_SOCKET, SO_BINDTODEVICE,
        malcolm_ctx->iface, IF_NAMESIZE) == -1)
        return (ft_printf("ft_malcolm: setsockopt: %s\n", strerror(errno)), 0);
    else
    {
        ft_printf("sockfd = %d\n", malcolm_ctx->sockfd);
    }
    return (1);
}