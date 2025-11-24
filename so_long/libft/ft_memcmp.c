/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 11:27:51 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 15:04:15 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_memcmp: Compares two memory areas byte by byte.
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;

	p1 = (const unsigned char *)s1;
	p2 = (const unsigned char *)s2;
	if (!n)
		return (0);
	while (n--)
	{
		if (*p1 != *p2)
			return ((int)(*p1 - *p2));
		p1++;
		p2++;
	}
	return (0);
}

// #include <stdio.h>
// int main(void)
// {
// 	char a[] = "abcde";
// 	char b[] = "abzde";
// 	int result = ft_memcmp(a, b, 3);  // Compares "abc" and "abz"
// 	printf("Result: %d\n", result);  // < 0 because 'c' < 'z'
// 	return 0;
// } //TESTED 