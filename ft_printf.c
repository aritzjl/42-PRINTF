/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arjaber- <arjaber-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:11:06 by arjaber-          #+#    #+#             */
/*   Updated: 2024/10/11 18:05:05 by arjaber-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

void	ft_print_arg(char c, int *counter)
{
	write(1, &"[argumento]", 11);
	*counter = *counter + 1;
}

int	is_arg(const char *format, int *counter)
{
	int	 i;
	char *s;
	int	og_counter;

	og_counter = *counter;
	i = 0;
	s = "cspdiuxX";
	while (format[*counter] && format[*counter] == ' ')
		(*counter)++;
	while (s[i])
	{
		if (s[i] == format[*counter])
		{
			if (format[*counter - 1] && format[*counter - 1] == ' ')
				write(1, " ", 1);
			*counter = *counter - 1;
			return (1);	
		}
		i++;
	}
	*counter = og_counter;
	return (0);
}

int ft_printf(char const *format, ...)
{
	va_list	args;
	int	counter;

	va_start(args, format);
	counter = 0;
	if (!format)
		return (1);
	while (format[counter])
	{
		if (format[counter] != '%')
			write(1, &format[counter], 1);
		else
		{
			counter++;
			if (is_arg(format, &counter))
				ft_print_arg(format[counter], &counter);
			else if (format[counter] == '%')
				write(1, "%", 1);
			else
			{
				write(1, "%", 1);
				write(1, &format[counter], 1);
			}
		}
		counter++;
	}
	va_end(args);
	return (1);
}

int	main(void)
{
	ft_printf("Hola %J");
	printf("\n");
	printf("Hola %J");
	printf("\n");

	// Multiple ' '
	ft_printf("Hola    J");
	printf("\n");
	printf("Hola    J");
	printf("\n");

	// Multiple %%%, and multiple ' ' between % and argument type declarator
	ft_printf("Hola cómo estás, %s? Tienes un 20%%%     ie posibilidades de ser majo :)");
	printf("\n");
	printf("Hola cómo estás, %s? Tienes un 20%%%     ie posibilidades de ser majo :)", "[argumento]", 6);
	return (0);
}
