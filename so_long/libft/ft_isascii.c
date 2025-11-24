/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isascii.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/22 14:53:09 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 15:09:46 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_isascii: Checks if a character is a valid ASCII character (0–127).
#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}

/* #include <stdio.h>

int main(void)
{
	printf("ft_isascii(65) = %d\n", ft_isascii(65));   // should be 1
	printf("ft_isascii(200) = %d\n", ft_isascii(200)); // should be 0
	return 0;
} // tested */