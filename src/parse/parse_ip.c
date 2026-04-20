#include "ft_malcolm.h"

int parse_ip(const char *str)
{
    struct in_addr  addr;

    if (inet_pton(AF_INET, str, &addr) != 1)
        return (0);
    return (1);
}