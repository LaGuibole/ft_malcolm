#include "ft_malcolm.h"

int main(int argc, char **argv)
{
    t_malcolm   malcolm_ctx;

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
    listen_for_request(&malcolm_ctx);
    return (0);
}