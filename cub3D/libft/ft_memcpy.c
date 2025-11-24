/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 11:27:57 by tiyang        #+#    #+#                 */
/*   Updated: 2025/05/05 15:31:22 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_memcpy: Copies memory from one location to another (non-overlapping).
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if ((!dest && !src) && n != 0)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	while (n > 0)
	{
		*d = *s;
		n--;
		d++;
		s++;
	}
	return (dest);
}

// #include <stdio.h>
// int main(void)
// {
// 	char src[10] = "123456";
// 	char dest[10] = "abcdef";
// 	ft_memcpy(dest + 2, src, 3);  // Copy "123" into dest+2
// 	printf("Result: %s\n", dest);  // Output: ab123f
// 	return 0;
// } // tested