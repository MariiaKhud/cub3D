/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 11:28:25 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 14:36:23 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_memset: Fills a block of memory with a specific byte value.
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		*p = (unsigned char)c;
		i++;
		p++;
	}
	return (s);
}

// #include <stdio.h>
// #include <string.h>  // For standard memset
// int main(void)
// {
// 	char buffer1[20] = "Hello, world!";
// 	char buffer2[20] = "Hello, world!";
// 	printf("Before memset:\n");
// 	printf("buffer1: %s\n", buffer1);
// 	printf("buffer2: %s\n", buffer2);
// 	// Use ft_memset
// 	ft_memset(buffer1 + 7, '*', 5);  // Replace "world" with "*****"
// 	// Use standard memset
// 	memset(buffer2 + 7, '*', 5);
// 	printf("\nAfter memset:\n");
// 	printf("buffer1 (ft_memset): %s\n", buffer1);
// 	printf("buffer2 (memset):    %s\n", buffer2);
// 	return 0;
// } // TESTED 