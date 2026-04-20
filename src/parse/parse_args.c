#include "ft_malcolm.h"

int  parse_args(t_malcolm *malcolm_ctx, char **argv)
{
    if (!parse_ip(argv[1]))
        return (ft_printf(INVALID_IP_MSG, argv[1]), 0);
    if (!parse_mac(argv[2], malcolm_ctx->src_mac))
        return (ft_printf(INVALID_MAC_MSG, argv[2]), 0);
    if (!parse_ip(argv[3]))
        return (ft_printf(INVALID_IP_MSG, argv[3]), 0);
    if (!parse_mac(argv[4], malcolm_ctx->dest_mac))
        return (ft_printf(INVALID_MAC_MSG, argv[4]), 0);
    malcolm_ctx->src_ip = argv[1];
    malcolm_ctx->dest_ip = argv[3];
    return (1);
}