/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_hex_upper.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/01 14:14:26 by tiyang        #+#    #+#                 */
/*   Updated: 2025/05/22 13:31:06 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Hexadecimal (%x or %X) in printf always treats numbers as unsigned.
int	print_hex_upper(unsigned int n)
{
	const char	*hex_upper;
	char		digit;
	int			count;

	count = 0;
	hex_upper = "0123456789ABCDEF";
	if (n >= 16)
		count += print_hex_upper(n / 16);
	digit = hex_upper[n % 16];
	count += write(1, &digit, 1);
	return (count);
}

/* 
#include <unistd.h>

int main(void)
{
    print_hex_upper(0);
    write(1, "\n", 1);
    print_hex_upper(10);
    write(1, "\n", 1);
    print_hex_upper(255);
    write(1, "\n", 1);
    print_hex_upper(4095);
    write(1, "\n", 1);
    print_hex_upper(4294967295u); // UINT_MAX
    write(1, "\n", 1);
    return 0;
} // TESTED */