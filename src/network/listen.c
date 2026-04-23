#include "ft_malcolm.h"

static int is_valid_request(t_malcolm *malcolm_ctx, t_arp_packet *arp)
{
	uint32_t    src_ip;
	uint32_t    dest_ip;

	inet_pton(AF_INET, malcolm_ctx->src_ip, &src_ip);
	inet_pton(AF_INET, malcolm_ctx->dest_ip, &dest_ip);

	// char sender[INET_ADDRSTRLEN];                                                           	// debug       
	// char target[INET_ADDRSTRLEN];                                                           	// debug
	// inet_ntop(AF_INET, &arp->sender_protocol_addr, sender, INET_ADDRSTRLEN);                	// debug
	// inet_ntop(AF_INET, &arp->target_protocol_addr, target, INET_ADDRSTRLEN);                    // debug
	// printf("op: %d | sender: %s | target: %s\n", ntohs(arp->op_code), sender, target);			// debug
	// printf("expecting target: %s | sender: %s\n", malcolm_ctx->src_ip, malcolm_ctx->dest_ip); 	// debug
	
	if (ntohs(arp->op_code) != 1)
		return (0);
	if (arp->target_protocol_addr != src_ip)
		return (0);
	if (arp->sender_protocol_addr != dest_ip)
		return (0);


	return (1);
}

int listen_for_request(t_malcolm *malcolm_ctx)
{
	t_frame frame;
	ssize_t len;

	// ft_printf("Waiting for ARP request...\n");
	while (1)
	{
		ft_memset(&frame, 0, sizeof(t_frame));
		len = recvfrom(malcolm_ctx->sockfd, &frame, sizeof(t_frame), 0, NULL, NULL);
		if (len == -1)
			return (ft_printf(RECV_ERR_MSG, strerror(errno)), 0);
		
		// printf("sizeof t_eth_header: %zu\n", sizeof(t_eth_header));								// debug
		// printf("sizeof t_arp_packet: %zu\n", sizeof(t_arp_packet));								// debug
		// printf("sizeof t_frame: %zu\n", sizeof(t_frame));										// debug
		// printf("Received %ld bytes, ethertype: 0x%04x\n", len, ntohs(frame.eth.ether_type));	// debug
		
		if (ntohs(frame.eth.ether_type) != ETH_P_ARP)
			continue ;
		if (is_valid_request(malcolm_ctx, &frame.arp))
		{
			ft_printf("An ARP request has been broadcasted.\n");
			printf("mac address of request : %02x:%02x:%02x:%02x:%02x:%02x:\n",
				frame.arp.sender_hardware_addr[0], frame.arp.sender_hardware_addr[1], frame.arp.sender_hardware_addr[2], 
				frame.arp.sender_hardware_addr[3], frame.arp.sender_hardware_addr[4], frame.arp.sender_hardware_addr[5]);
			ft_printf("IP address of request : %s\n", malcolm_ctx->dest_ip);
			return (send_reply(malcolm_ctx, &frame));
		}
	}
}