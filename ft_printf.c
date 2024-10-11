/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arjaber- <arjaber-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:11:06 by arjaber-          #+#    #+#             */
/*   Updated: 2024/10/11 17:07:07 by arjaber-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

void	ft_print_arg(char c, int *counter)
{
	write(1, &"[argumento]", 11);
	*counter = *counter + 1;
}

int	is_arg(char c)
{
	int	counter;
	char	*s;

	s = "cspdiuxX";
	counter = 0;
	while (s[counter])
	{
		if (s[counter] == c)
			return (1);
		counter++;
	}
	return (0);
}

int ft_printf(char const *format, ...)
{
	int	counter;

	counter = 0;
	if (!format)
		return (1);
	while (format[counter])
	{
		if (format[counter] != '%')
			write(1, &format[counter], 1);
		else if (format[counter] == '%' &&  is_arg(format[counter + 1]))
			ft_print_arg(format[counter + 1], &counter);
		else if (format[counter] == '%' &&  format[counter + 1] == '%')
			write(1, "%", 1);
		counter++;
	}
	return (1);
}

int	main(void)
{
	ft_printf("Hola cómo estás, %s? Tienes un 20%% de posibilidades de ser majo :)");
	return (0);
}
