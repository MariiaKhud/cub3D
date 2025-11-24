/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isdigit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/22 14:53:00 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 15:08:22 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_isdigit: Checks if a character is a digit (0-9).
#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

// #include <stdio.h>
// int main()
// {
// 	printf("%d\n", ft_isdigit('8'));
// } // TESTED 