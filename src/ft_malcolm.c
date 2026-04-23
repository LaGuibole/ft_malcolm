#include "ft_malcolm.h"

volatile sig_atomic_t g_signal = 0;

static void handle_sigint(int sig)
{
    (void)sig;
    g_signal = 1;
}

int main(int argc, char **argv)
{
    t_malcolm           malcolm_ctx;
    struct sigaction    sa;

    if (argc != 5)
        return (ft_printf(BOLD_RED "Usage: ./ft_malcolm <src_ip> <src_mac> <dest_ip> <dest_mac>\n" RESET),  1);
    print_title();
    ft_memset(&malcolm_ctx, 0, sizeof(t_malcolm));
    print_parse();
    if (!parse_args(&malcolm_ctx, argv))
        return (1);
    ft_printf(BOLD_MAGENTA "PARSE OK !\n" RESET);
    print_sum(&malcolm_ctx);
    find_interface(&malcolm_ctx);
    init_socket(&malcolm_ctx);


    ft_memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handle_sigint;
    sigaction(SIGINT, &sa, NULL);
    
    listen_for_request(&malcolm_ctx);
    close(malcolm_ctx.sockfd);
    return (0);
}