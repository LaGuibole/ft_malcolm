#include "ft_malcolm.h"

static void build_reply(t_malcolm *malcolm_ctx, t_frame *reply, t_frame *request)
{
    // header eth
    ft_memcpy(reply->eth.dest_mac, request->arp.sender_hardware_addr, 6);
    ft_memcpy(reply->eth.src_mac, malcolm_ctx->src_mac, 6);
    reply->eth.ether_type = htons(ETH_P_ARP);

    // ARP packet
    reply->arp.hardware_type = htons(1);
    reply->arp.protocol = htons(ETH_P_IP);
    reply->arp.hardware_len = 6;
    reply->arp.protocol_len = 4;
    reply->arp.op_code = htons(2); // reply

    ft_memcpy(reply->arp.sender_hardware_addr, malcolm_ctx->src_mac, 6);
    inet_pton(AF_INET, malcolm_ctx->src_ip, &reply->arp.sender_protocol_addr);

    ft_memcpy(reply->arp.target_hardware_addr, request->arp.sender_hardware_addr, 6);
    reply->arp.target_protocol_addr = request->arp.sender_protocol_addr;
}

int send_reply(t_malcolm *malcolm_ctx, t_frame *request)
{
    t_frame             reply;
    struct sockaddr_ll  sll;
    int                 ifindex;

    ft_memset(&reply, 0, sizeof(t_frame));
    ft_memset(&sll, 0, sizeof(sll));

    build_reply(malcolm_ctx, &reply, request);
    
    ifindex = if_nametoindex(malcolm_ctx->iface);
    if (ifindex < 0)
        return (ft_printf(NAME_TO_IDX_MSG, strerror(errno)), 0);

    sll.sll_family = AF_PACKET;
    sll.sll_protocol = htons(ETH_P_ARP);
    sll.sll_ifindex = ifindex;
    sll.sll_halen = 6;

    ft_memcpy(sll.sll_addr, request->arp.sender_hardware_addr, 6);
    ft_printf("Now sending ARP Reply to : %s ...\n", malcolm_ctx->dest_ip);

    if (sendto(malcolm_ctx->sockfd, &reply, sizeof(t_frame), 0, (struct sockaddr *)&sll, sizeof(sll)) == -1)
        return (ft_printf(SENDTO_ERR_MSG), strerror(errno), 0);
    ft_printf("Sent ! Check ARP Table on the target, i hope i didn't mess this up\n"); //debug
    ft_printf("Exiting programm ...");
    return (1);
}