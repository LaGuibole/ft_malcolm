#include "ft_malcolm.h"

static int ip_is_in_subnet(struct ifaddrs *ifa, const char *dest_ip)
{
    struct sockaddr_in  *addr;
    struct sockaddr_in  *mask;
    uint32_t            iface_net;
    uint32_t            dest_net;
    uint32_t            dest;

    if (!ifa->ifa_addr || !ifa->ifa_netmask)
        return (0);
    if (ifa->ifa_addr->sa_family != AF_INET)
        return (0);
    addr = (struct sockaddr_in *)ifa->ifa_addr;
    mask = (struct sockaddr_in *)ifa->ifa_netmask;
    inet_pton(AF_INET, dest_ip, &dest);
    iface_net = addr->sin_addr.s_addr & mask->sin_addr.s_addr;
    dest_net = dest & mask->sin_addr.s_addr;
    return (iface_net == dest_net);
}

int find_interface(t_malcolm *malcolm_ctx)
{
    struct  ifaddrs *ifas;
    struct  ifaddrs *ifa;

    if (getifaddrs(&ifas) == -1)
        return (ft_printf("ft_malcom: getifaddrs failed: %s\n", strerror(errno)), 0);
    
    ifa = ifas;

    while (ifa)
    {
        if (!(ifa->ifa_flags & IFF_LOOPBACK)
                && (ifa->ifa_flags & IFF_UP)
                && ip_is_in_subnet(ifa, malcolm_ctx->dest_ip))
        {
            ft_strlcpy(malcolm_ctx->iface, ifa->ifa_name, IF_NAMESIZE);
            ft_printf("Found available interface : %s\n", malcolm_ctx->iface);
            freeifaddrs(ifas);
            return (1);
        }
        ifa = ifa->ifa_next;
    }
    freeifaddrs(ifas);
    return (ft_printf(NO_IFA_FOUND), 0);
}

