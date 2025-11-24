/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tolower.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/22 14:43:10 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 15:13:09 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_tolower: Converts an uppercase letter to lowercase.
#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	else
		return (c);
}

/* #include <stdio.h>

int main(void)
{
	printf("ft_tolower('A') = %c\n", ft_tolower('A')); // should be 'a'
	printf("ft_tolower('!') = %c\n", ft_tolower('!')); // should stay '!'
	return 0;
} // tested  */