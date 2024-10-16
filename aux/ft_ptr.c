#include "ft_printf.h"

int	ft_put_ptr(void *ptr)
{
	unsigned long long	address;
	int					count;

	count = 0;
	address = (unsigned long long)ptr;
	if (address == 0)
	{
		count += ft_putstr("(nil)");
		return (count);
	}
	count += ft_putstr("0x");
	count += ft_put_hex_lower_64(address);
	return (count);
}
