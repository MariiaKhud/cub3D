/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 14:43:02 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 10:55:42 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_putnbr_fd: Writes an integer to a file descriptor.
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	digit;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	digit = '0' + n % 10;
	write(fd, &digit, 1);
}

/* int	main(void)
{
	// Test 1: positive number
	ft_putnbr_fd(12345, 1);
	write(1, "\n", 1);

	// Test 2: negative number
	ft_putnbr_fd(-6789, 1);
	write(1, "\n", 1);

	// Test 3: zero
	ft_putnbr_fd(0, 1);
	write(1, "\n", 1);

	// Test 4: INT_MIN (-2147483648)
	ft_putnbr_fd(-2147483648, 1);
	write(1, "\n", 1);

	// Test 5: INT_MAX (2147483647)
	ft_putnbr_fd(2147483647, 1);
	write(1, "\n", 1);

	return (0);
} // 	TESTED 
 */