/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arjaber- <arjaber-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:11:06 by arjaber-          #+#    #+#             */
/*   Updated: 2024/10/11 16:44:54 by arjaber-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

void	ft_print_arg(char c)
{
	write(1, &"k", 1);
}

int	is_arg(char c)
{
	
}

int ft_printf(char const *format, ...)
{
	int	counter;

	counter = 0;
	if (!format)
		return (1);
	while (format[counter])
	{
		if (format[counter] == '%' && is_arg(format[counter + 1]))
			ft_print_arg(format[counter++]);
		else
			write(1, &format[counter], 1);
		counter++;
	}
	return (1);
}

int	main(void)
{
	ft_printf("Hola cómo estás, %s? Tienes un 20%% de posibilidades de ser majo :)");
	return (0);
}
