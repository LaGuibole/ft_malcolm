#include "ft_malcolm.h"

int init_socket(t_malcolm *malcolm_ctx)
{
	struct packet_mreq  mreq;
	int                 ifindex;

	malcolm_ctx->sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
	if (malcolm_ctx->sockfd == -1)
		return (ft_printf("ft_malcolm: socket: %s\n", strerror(errno)), 0);

	ifindex = if_nametoindex(malcolm_ctx->iface);
	if (ifindex == 0)
		return (ft_printf(NAME_TO_IDX_MSG, strerror(errno)), 0);
	ft_memset(&mreq, 0, sizeof(mreq));
	mreq.mr_ifindex = ifindex;
	mreq.mr_type = PACKET_MR_PROMISC;
	if (setsockopt(malcolm_ctx->sockfd, SOL_SOCKET, PACKET_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) == -1)
		return (ft_printf("ft_malcolm: setsockopt: %s\n", strerror(errno)), 0);
	return (1);
}