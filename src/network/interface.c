#include "ft_malcolm.h"

int find_interface(t_malcolm *malcolm_ctx)
{
    struct  ifaddrs *ifas;
    struct  ifaddrs *ifa;

    if (getifaddrs(&ifas) == -1)
        return (ft_printf("ft_malcom: getifaddrs failed: %s\n", strerror(errno)), 0);
    
    ifa = ifas;

    while (ifa)
    {
        if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_PACKET
            && !(ifa->ifa_flags & IFF_LOOPBACK)
            && (ifa->ifa_flags & IFF_UP))
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