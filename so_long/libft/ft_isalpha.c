/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalpha.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/22 12:46:16 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 15:08:15 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_isalpha: Checks if a character is an alphabetic letter (A-Z, a-z).
#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

// #include <stdio.h>
// int main()
// {
// 	printf("%d\n", ft_isalpha(-1));
// } // TESTED 