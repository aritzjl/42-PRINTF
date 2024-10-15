/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aritz <aritz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:11:06 by arjaber-          #+#    #+#             */
/*   Updated: 2024/10/15 11:56:18 by aritz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		ft_putchar('-');
		ft_putchar('2');
		ft_putnbr(147483648);
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar(n % 10 + '0');
}

void	ft_putstr(char *str)
{
	if (!str)
		return ;
	while (*str)
	{
		ft_putchar(*str);
		str++;
	}	
}

void	ft_print_arg(char c, va_list args)
{
	if (c == '%')
		ft_putchar('%');
	else if (c == 'i')
		ft_putnbr(va_arg(args, int));
	else if (c == 's')
		ft_putstr(va_arg(args, char *));
	else
		write(1, "[argumento]", 11);
}

int	ft_printf(char const *str, ...)
{
	va_list	args;
	int		counter;

	va_start(args, str);
	counter = -1;
	while (str[++counter])
	{
		if (str[counter] == '%')
			ft_print_arg(str[++counter], args);
		else
			ft_putchar(str[counter]);
	}
	va_end(args);
	return (1);
}

int	main(void)
{
	// Tests para tipo int
	ft_printf("ft_printf (int):\n");
	ft_printf("Hola %i\n", 42);
	ft_printf("El número es %i\n", -2147483648);
	ft_printf("Un número positivo %i\n", 123456);
	ft_printf("Otro número negativo %i\n", -123);
	
	printf("\n");
	
	printf("printf (int):\n");
	printf("Hola %i\n", 42);
	printf("El número es %i\n", -2147483648);
	printf("Un número positivo %i\n", 123456);
	printf("Otro número negativo %i\n", -123);
	
	printf("\n");
	
	// Tests para tipo string
	ft_printf("ft_printf (string):\n");
	ft_printf("Hola %s\n", "mundo");
	ft_printf("Una cadena %s\n", "de prueba");
	ft_printf("Cadena vacía %s\n", "");
	ft_printf("Cadena NULL %s\n", NULL);
	
	printf("\n");

	printf("printf (string):\n");
	printf("Hola %s\n", "mundo");
	printf("Una cadena %s\n", "de prueba");
	printf("Cadena vacía %s\n", "");
	printf("Cadena NULL %s\n", NULL);
	
	return (0);
}