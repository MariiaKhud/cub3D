/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 11:27:44 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 14:53:28 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_memchr: Searches memory for a byte value.
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;

	p = (const unsigned char *)s;
	while (n--)
	{
		if (*p == (unsigned char)c)
			return ((void *)p);
		p++;
	}
	return (NULL);
}

// #include <stdio.h>
// int main(void)
// {
// 	char data[] = "abcdef";
// 	char *result = ft_memchr(data, 'd', 6);
// 	if (result)
// 		printf("Found: %c\n", *result);
// 	else
// 		printf("Not found\n");
// 	return 0;
// } // TESTED 