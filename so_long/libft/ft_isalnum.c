/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalnum.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/22 13:40:04 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 15:08:01 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_isalnum: Checks if a character is alphanumeric (letter or digit).
#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

// #include <stdio.h>
// int main()
// {
// 	printf("%d\n", ft_isalnum('1'));
// } // TESTED 