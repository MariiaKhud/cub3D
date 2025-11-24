/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/22 14:51:53 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 10:48:50 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_strlen: Returns the length of a null-terminated string.
#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

// #include <stdio.h>
// int main()
// {
// 	const char *s = "";
// 	printf("%zu", ft_strlen(s)); // Use %zu to print size_t.
// } // tested