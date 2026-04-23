#include "ft_malcolm.h"

void print_title(void)
{
    ft_printf(BOLD_YELLOW "===============================================================\n" RESET);
    ft_printf(BOLD_YELLOW "|| ft_malcolm for 42                                         ||\n" RESET);
    ft_printf(BOLD_YELLOW "||                                             An ARP Spoofer||\n" RESET);
    ft_printf(BOLD_YELLOW "||                         MITM : o/                         ||\n" RESET);
    ft_printf(BOLD_YELLOW "===============================================================\n" RESET);
}

void print_parse(void)
{
    ft_printf(BOLD_MAGENTA "\nNow parsing IPs and MAC adresses" RESET);
    ft_printf(BOLD_MAGENTA " .");
    // sleep(1);
    ft_printf(BOLD_MAGENTA " .");
    // sleep(1);
    ft_printf(BOLD_MAGENTA " .\n" RESET);
    // sleep(1);
}

void print_sum(t_malcolm *malcolm_ctx)
{
ft_printf("\n");
ft_printf("=========================================\n");
ft_printf("        ft_malcolm - ARP Spoofing        \n");
ft_printf("=========================================\n");
ft_printf("  Source IP    : %s\n", malcolm_ctx->src_ip);
printf("  Source MAC   : %02x:%02x:%02x:%02x:%02x:%02x\n",
    malcolm_ctx->src_mac[0], malcolm_ctx->src_mac[1], malcolm_ctx->src_mac[2],
    malcolm_ctx->src_mac[3], malcolm_ctx->src_mac[4], malcolm_ctx->src_mac[5]);
ft_printf("-----------------------------------------\n");
ft_printf("  Target IP    : %s\n", malcolm_ctx->dest_ip);
printf("  Target MAC   : %02x:%02x:%02x:%02x:%02x:%02x\n",
    malcolm_ctx->dest_mac[0], malcolm_ctx->dest_mac[1], malcolm_ctx->dest_mac[2],
    malcolm_ctx->dest_mac[3], malcolm_ctx->dest_mac[4], malcolm_ctx->dest_mac[5]);
ft_printf("-----------------------------------------\n");
ft_printf("  Interface    : %s\n", malcolm_ctx->iface);
ft_printf("=========================================\n");
ft_printf("\n");
ft_printf("[*] Waiting for ARP request from %s...\n", malcolm_ctx->dest_ip);
}