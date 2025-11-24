/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_int.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/01 13:28:49 by tiyang        #+#    #+#                 */
/*   Updated: 2025/05/01 17:34:29 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// count the number of digits in an integer, including the negative sign
static int	count_digit(int n)
{
	int	count;

	if (n == INT_MIN)
		return (11);
	count = 1;
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n > 9)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static void	ft_putnbr(int n)
{
	char	digit;

	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
		ft_putnbr(n / 10);
	digit = '0' + n % 10;
	write(1, &digit, 1);
}

int	print_int(int n)
{
	ft_putnbr(n);
	return (count_digit(n));
}

/* 
#include <unistd.h>

int main(void)
{
    print_int(0);
    write(1, "\n", 1);
    print_int(42);
    write(1, "\n", 1);
    print_int(-42);
    write(1, "\n", 1);
    print_int(123456789);
    write(1, "\n", 1);
    print_int(-2147483648); // INT_MIN
    write(1, "\n", 1);
    print_int(2147483647);  // INT_MAX
    write(1, "\n", 1);
    return 0;
} // TESTED */