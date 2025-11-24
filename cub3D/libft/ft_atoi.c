/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 11:27:17 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 14:21:17 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_atoi: Converts a string to an integer.
#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	n;

	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n' || *nptr == '\r'
		|| *nptr == '\v' || *nptr == '\f')
		nptr++;
	sign = 1;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	n = 0;
	while (*nptr && *nptr >= '0' && *nptr <= '9')
	{
		n = n * 10 + (*nptr - '0');
		nptr++;
	}
	return (sign * n);
}

/* #include <stdio.h>

int main(void)
{
    printf("Input: \"42\"            -> Result: %d\n", ft_atoi("42"));
    printf("Input: \"   -123\"       -> Result: %d\n", ft_atoi("   -123"));
    printf("Input: \"+7\"            -> Result: %d\n", ft_atoi("+7"));
    printf("Input: \"0042\"          -> Result: %d\n", ft_atoi("0042"));
    printf("Input: \"abc\"           -> Result: %d\n", ft_atoi("abc"));
    printf("Input: \"123abc\"        -> Result: %d\n", ft_atoi("123abc"));
    printf("Input: \"   +0\"         -> Result: %d\n", ft_atoi("   +0"));
    printf("Input: \"-2147483648\"   -> Result: %d\n", ft_atoi("-2147483648"));
    printf("Input: \"2147483647\"    -> Result: %d\n", ft_atoi("2147483647"));
    return 0;
}
// tested */