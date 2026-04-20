#include "ft_malcolm.h"

static int hex_char_to_val(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (-1);
}

int parse_mac(const char *str, uint8_t mac[6])
{
	int		i;
	int		val;
	int 	byte;
	int		len;

	i = 0;
	while (i < 6)
	{
		len = 0;
		byte = 0;
		while (*str && *str != ':')
		{
			val = hex_char_to_val(*str);
			if (val == -1 || len >= 2)
				return (0);
			byte = byte * 16 + val;
			str++;
			len++;
		}
		if (len == 0)
			return (0);
		mac[i] = (uint8_t)byte;
		i++;
		if (i < 6 && *str == ':')
			str++;
		else if (i < 6)
			return (0);
	}
	return (*str == '\0');
}