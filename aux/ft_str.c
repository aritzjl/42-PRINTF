#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	int	count;

	count = 0;
	if (!str)
	{
		count += ft_putstr("(null)");
		return (count);
	}
	while (*str)
	{
		count += ft_putchar(*str);
		str++;
	}
	return (count);
}
