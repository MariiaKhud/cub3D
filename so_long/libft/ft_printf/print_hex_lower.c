/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_hex_lower.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/01 13:32:02 by tiyang        #+#    #+#                 */
/*   Updated: 2025/05/22 13:30:49 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Hexadecimal (%x or %X) in printf always treats numbers as unsigned.
// if we pass a negative int to printf("%x", -42), 
// it interprets the bits of the negative number 
// as if it were an unsigned number
int	print_hex_lower(unsigned int n)
{
	const char	*hex_lower;
	char		digit;
	int			count;

	count = 0;
	hex_lower = "0123456789abcdef";
	if (n >= 16)
		count += print_hex_lower(n / 16);
	digit = hex_lower[n % 16];
	count += write(1, &digit, 1);
	return (count);
}

/* 
#include <unistd.h>

int main(void)
{
    print_hex_lower(0);
    write(1, "\n", 1);
    print_hex_lower(10);
    write(1, "\n", 1);
    print_hex_lower(255);
    write(1, "\n", 1);
    print_hex_lower(4095);
    write(1, "\n", 1);
    print_hex_lower(4294967295u); // UINT_MAX
    write(1, "\n", 1);
    return 0;
} // TESTED  
 */