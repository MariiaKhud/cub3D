/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_unsigned_int.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/01 13:25:59 by tiyang        #+#    #+#                 */
/*   Updated: 2025/05/05 09:11:43 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// count the number of digits in an integer (unsigned)
static int	count_unsigned_digit(unsigned int n)
{
	int	count;

	count = 1;
	while (n > 9)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static void	ft_put_unsigned_nbr(unsigned int n)
{
	char	digit;

	if (n > 9)
		ft_put_unsigned_nbr(n / 10);
	digit = '0' + n % 10;
	write(1, &digit, 1);
}

int	print_unsigned_int(unsigned int n)
{
	ft_put_unsigned_nbr(n);
	return (count_unsigned_digit(n));
}

/* int main(void)
{
    print_unsigned_int(0);
    write(1, "\n", 1);
    print_unsigned_int(42);
    write(1, "\n", 1);
    print_unsigned_int(2147483647u);
    write(1, "\n", 1);
    print_unsigned_int(4294967295u); // UINT_MAX
    write(1, "\n", 1);
    return 0;
} // TESTED */