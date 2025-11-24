/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isprint.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/22 14:52:50 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 15:11:19 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_isprint: Checks if a character is printable 
// 				(includes space, excludes control chars).
#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}

/* #include <stdio.h>

int main(void)
{
	printf("ft_isprint('A') = %d\n", ft_isprint('A')); // should be 1
	printf("ft_isprint(31) = %d\n", ft_isprint(31));   // should be 0
	return 0;
} // TESTED */