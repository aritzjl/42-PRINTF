/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aritz <aritz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:11:06 by arjaber-          #+#    #+#             */
/*   Updated: 2024/10/15 13:05:10 by aritz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putnbr(int n)
{
	int count = 0;
	if (n == -2147483648)
	{
		count += ft_putchar('-');
		count += ft_putchar('2');
		count += ft_putnbr(147483648);
		return count;
	}
	if (n < 0)
	{
		count += ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
		count += ft_putnbr(n / 10);
	count += ft_putchar(n % 10 + '0');
	return count;
}

int	ft_put_hex_lower(unsigned int n)
{
    char	*hex_digits = "0123456789abcdef";
	int		digit;
	int		count = 0;

    if (n >= 16)
        count += ft_put_hex_lower(n / 16);
    digit = hex_digits[n % 16];  
    count += write(1, &digit, 1);
	return count;
}

int	ft_put_hex_upper(unsigned int n)
{
    char	*hex_digits = "0123456789ABCDEF";
	int		digit;
	int		count = 0;

    if (n >= 16)
        count += ft_put_hex_upper(n / 16);
    digit = hex_digits[n % 16];  
    count += write(1, &digit, 1);
	return count;
}

int	ft_putstr(char *str)
{
	int count = 0;

	if (!str)
	{
		count += ft_putstr("(null)");
		return count;
	}
	while (*str)
	{
		count += ft_putchar(*str);
		str++;
	}
	return count;
}

int ft_putunsigned(unsigned int n)
{
	int count = 0;

    if (n >= 10)
        count += ft_putunsigned(n / 10);
    count += ft_putchar(n % 10 + '0');
	return count;
}

int	ft_put_hex_lower_64(unsigned long long n)
{
    char	*hex_digits = "0123456789abcdef";
	int		digit;
	int		count = 0;

    if (n >= 16)
        count += ft_put_hex_lower_64(n / 16);
    digit = hex_digits[n % 16];  
    count += write(1, &digit, 1);
	return count;
}

int	ft_put_ptr(void *ptr)
{
    unsigned long long address;
	int count = 0;

    address = (unsigned long long)ptr;
	if (address == 0)
	{
		count += ft_putstr("(nil)");
		return count;
	}
    count += ft_putstr("0x");
    count += ft_put_hex_lower_64(address);
	return count;
}


int	ft_print_arg(char c, va_list args)
{
	int count = 0;

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
	else
		count += write(1, "[argumento]", 11);
	return count;
}

int	ft_printf(char const *str, ...)
{
	va_list	args;
	int		total_len = 0;
	int		counter = -1;

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
/*
int	main(void)
{
int my_len, orig_len;

// Test with a simple string
my_len = ft_printf("Simple test\n");
orig_len = printf("Simple test\n");
printf("ft_printf: %d characters, printf: %d characters\n\n", my_len, orig_len);

// Test with integers (including limits)
my_len = ft_printf("Positive integer: %d, Negative integer: %d\n", 123, -456);
orig_len = printf("Positive integer: %d, Negative integer: %d\n", 123, -456);
printf("ft_printf: %d characters, printf: %d characters\n\n", my_len, orig_len);

my_len = ft_printf("Maximum integer: %d, Minimum integer: %d\n", INT_MAX, INT_MIN);
orig_len = printf("Maximum integer: %d, Minimum integer: %d\n", INT_MAX, INT_MIN);
printf("ft_printf: %d characters, printf: %d characters\n\n", my_len, orig_len);

// Test with characters
my_len = ft_printf("Character: %c\n", 'A');
orig_len = printf("Character: %c\n", 'A');
printf("ft_printf: %d characters, printf: %d characters\n\n", my_len, orig_len);

// Test with strings
my_len = ft_printf("String: %s\n", "Hello, world!");
orig_len = printf("String: %s\n", "Hello, world!");
printf("ft_printf: %d characters, printf: %d characters\n\n", my_len, orig_len);

my_len = ft_printf("NULL string: %s\n", NULL);
orig_len = printf("NULL string: %s\n", NULL);
printf("ft_printf: %d characters, printf: %d characters\n\n", my_len, orig_len);

// Test with pointers
int x = 42;
my_len = ft_printf("Pointer: %p\n", &x);
orig_len = printf("Pointer: %p\n", &x);
printf("ft_printf: %d characters, printf: %d characters\n\n", my_len, orig_len);

// Test with hexadecimal numbers (lowercase)
my_len = ft_printf("Hexadecimal (lowercase): %x\n", 255);
orig_len = printf("Hexadecimal (lowercase): %x\n", 255);
printf("ft_printf: %d characters, printf: %d characters\n\n", my_len, orig_len);

// Test with hexadecimal numbers (uppercase)
my_len = ft_printf("Hexadecimal (uppercase): %X\n", 255);
orig_len = printf("Hexadecimal (uppercase): %X\n", 255);
printf("ft_printf: %d characters, printf: %d characters\n\n", my_len, orig_len);

// Test with unsigned integers
my_len = ft_printf("Unsigned: %u\n", 4294967295u);
orig_len = printf("Unsigned: %u\n", 4294967295u);
printf("ft_printf: %d characters, printf: %d characters\n\n", my_len, orig_len);

// Test with percentage
my_len = ft_printf("Percentage: %%\n");
orig_len = printf("Percentage: %%\n");
printf("ft_printf: %d characters, printf: %d characters\n\n", my_len, orig_len);

// Edge cases and combinations
my_len = ft_printf("Combination: %d, %x, %s, %p\n", 1024, 255, "Test", &x);
orig_len = printf("Combination: %d, %x, %s, %p\n", 1024, 255, "Test", &x);
printf("ft_printf: %d characters, printf: %d characters\n\n", my_len, orig_len);

return 0;
}
*/

/*
int main(void)
{
    int n = 42;
    unsigned int un = -42;
    char c = '\0';
    char *s = NULL;
    char *ptr = "Test";
    int rlen1 = 0, rlen2 = 0;
    // Test 1: Mix
    rlen1 = ft_printf("\033[0;33mTest Mix: %c %s %d %i %u %x %X %p %%\n\033[0m", c, s, n, n, un, n, n, s);
    rlen2 = printf("\033[0;32mTest Mix: %c %s %d %i %u %x %X %p %%\n\033[0m", c, s, n, n, un, n, n, s);
    printf("\033[0;33mft_printf devolvió: %d\n\033[0m", rlen1);
    printf("\033[0;32mprintf devolvió: %d\n\033[0m", rlen2);
    printf("\n\n");
    // Test 2: Char
    rlen1 = ft_printf("\033[0;33mTest char: %c\n\033[0m", 'A');
    rlen2 = printf("\033[0;32mTest char: %c\n\033[0m", 'A');
    printf("\033[0;33mft_printf devolvió: %d\n\033[0m", rlen1);
    printf("\033[0;32mprintf devolvió: %d\n\033[0m", rlen2);
    printf("\n\n");
    // Test 3: String
    rlen1 = ft_printf("\033[0;33mTest string: %s\n\033[0m", "mundo");
    rlen2 = printf("\033[0;32mTest string: %s\n\033[0m", "mundo");
    printf("\033[0;33mft_printf devolvió: %d\n\033[0m", rlen1);
    printf("\033[0;32mprintf devolvió: %d\n\033[0m", rlen2);
    printf("\n\n");
    // Test 4: Hex minusculas
    rlen1 = ft_printf("\033[0;33mTest hex: %x\n\033[0m", 25555555);
    rlen2 = printf("\033[0;32mTest hex: %x\n\033[0m", 25555555);
    printf("\033[0;33mft_printf devolvió: %d\n\033[0m", rlen1);
    printf("\033[0;32mprintf devolvió: %d\n\033[0m", rlen2);
    printf("\n\n");
    // Test 5: Puntero
    rlen1 = ft_printf("\033[0;33mTest ptr: %p\n\033[0m", ptr);
    rlen2 = printf("\033[0;32mTest ptr: %p\n\033[0m", ptr);
    printf("\033[0;33mft_printf devolvió: %d\n\033[0m", rlen1);
    printf("\033[0;32mprintf devolvió: %d\n\033[0m", rlen2);
    printf("\n\n");
    // Test 6: Hex mayusculas
    rlen1 = ft_printf("\033[0;33mTest HEX: %X\n\033[0m", 255);
    rlen2 = printf("\033[0;32mTest HEX: %X\n\033[0m", 255);
    printf("\033[0;33mft_printf devolvió: %d\n\033[0m", rlen1);
    printf("\033[0;32mprintf devolvió: %d\n\033[0m", rlen2);
    printf("\n\n");
    // Test 7: Decimal
    rlen1 = ft_printf("\033[0;33mTest dec: %d\n\033[0m", 777);
    rlen2 = printf("\033[0;32mTest dec: %d\n\033[0m", 777);
    printf("\033[0;33mft_printf devolvió: %d\n\033[0m", rlen1);
    printf("\033[0;32mprintf devolvió: %d\n\033[0m", rlen2);
    printf("\n\n");
    // Test 8: Int
    rlen1 = ft_printf("\033[0;33mTest int: %i\n\033[0m", 777);
    rlen2 = printf("\033[0;32mTest int: %i\n\033[0m", 777);
    printf("\033[0;33mft_printf devolvió: %d\n\033[0m", rlen1);
    printf("\033[0;32mprintf devolvió: %d\n\033[0m", rlen2);
    printf("\n\n");
    // Test 9: Unsigned int
    rlen1 = ft_printf("\033[0;33mTest uns: %u\n\033[0m", -0);
    rlen2 = printf("\033[0;32mTest uns: %u\n\033[0m", -0);
    printf("\033[0;33mft_printf devolvió: %d\n\033[0m", rlen1);
    printf("\033[0;32mprintf devolvió: %d\n\033[0m", rlen2);
    printf("\n\n");
    // Test 10: Porcentaje
    rlen1 = ft_printf("\033[0;33mTest porcentaje: %%\n\033[0m");
    rlen2 = printf("\033[0;32mTest porcentaje: %%\n\033[0m");
    printf("\033[0;33mft_printf devolvió: %d\n\033[0m", rlen1);
    printf("\033[0;32mprintf devolvió: %d\n\033[0m", rlen2);
    printf("\n\n");
    // Test 11: Locura
    rlen1 = ft_printf("\033[0;33mTest locura: %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%\n\033[0m", 'A', "42", 42, 42 ,42 , 42, 42, 'B', "-42", -42, -42 ,-42 ,-42, 42, 'C', "0", 0, 0 ,0 ,0, 42, 0);
    rlen2 = printf ("\033[0;32mtest locura: %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%\n\033[0m", 'A', "42", 42, 42 ,42 , 42, 42, 'B', "-42", -42, -42 ,-42 ,-42, 42, 'C', "0", 0, 0 ,0 ,0, 42, 0);
    printf("\033[0;33mft_printf devolvió: %d\n\033[0m", rlen1);
    printf("\033[0;32mprintf devolvió: %d\n\033[0m", rlen2);
    printf("\n\n");
    return 0;
}
*/