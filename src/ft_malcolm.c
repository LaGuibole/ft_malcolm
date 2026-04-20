#include "ft_malcolm.h"

int main(int argc, char **argv)
{
    t_malcolm   malcolm;

    if (argc != 5)
        return (ft_printf("Usage: ./ft_malcolm <src_ip> <src_mac> <dest_ip> <dest_mac>\n"), 1);
    ft_memset(&malcolm, 0, sizeof(t_malcolm));
    ft_printf("Usage ok, proceeding to parsing :\n");
    if (!parse_args(&malcolm, argv))
        return (1);
    ft_printf("PARSE OK !\n");
    return (0);
}