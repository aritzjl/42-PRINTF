/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aritz <aritz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:46:57 by arjaber-          #+#    #+#             */
/*   Updated: 2024/10/16 19:37:19 by aritz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_put_hex_lower(unsigned int n)
{
	char	*hex_digits;
	int		digit;
	int		count;

	count = 0;
	if (n >= 16)
		count += ft_put_hex_lower(n / 16);
	hex_digits = "0123456789abcdef";
	digit = hex_digits[n % 16];
	count += write(1, &digit, 1);
	return (count);
}

int	ft_put_hex_upper(unsigned int n)
{
	char	*hex_digits;
	int		digit;
	int		count;

	count = 0;
	if (n >= 16)
		count += ft_put_hex_upper(n / 16);
	hex_digits = "0123456789ABCDEF";
	digit = hex_digits[n % 16];
	count += write(1, &digit, 1);
	return (count);
}

int	ft_put_hex_lower_64(unsigned long long n)
{
	char	*hex_digits;
	int		digit;
	int		count;

	count = 0;
	if (n >= 16)
		count += ft_put_hex_lower_64(n / 16);
	hex_digits = "0123456789abcdef";
	digit = hex_digits[n % 16];
	count += write(1, &digit, 1);
	return (count);
}
