/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aritz <aritz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:11:06 by arjaber-          #+#    #+#             */
/*   Updated: 2024/10/16 09:09:45 by aritz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_arg(char c, va_list args)
{
	int	count;

	count = 0;
	if (c == '%')
		count += ft_putchar('%');
	else if (c == 'i' || c == 'd')
		count += ft_putnbr(va_arg(args, int));
	else if (c == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (c == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (c == 'u')
		count += ft_putunsigned(va_arg(args, unsigned int));
	else if (c == 'x')
		count += ft_put_hex_lower(va_arg(args, unsigned int));
	else if (c == 'X')
		count += ft_put_hex_upper(va_arg(args, unsigned int));
	else if (c == 'p')
		count += ft_put_ptr(va_arg(args, void *));
	return (count);
}

int	ft_printf(char const *str, ...)
{
	va_list	args;
	int		total_len;
	int		counter;

	total_len = 0;
	counter = -1;
	va_start(args, str);
	while (str[++counter])
	{
		if (str[counter] == '%')
			total_len += ft_print_arg(str[++counter], args);
		else
			total_len += ft_putchar(str[counter]);
	}
	va_end(args);
	return (total_len);
}
