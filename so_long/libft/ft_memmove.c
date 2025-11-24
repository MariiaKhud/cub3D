/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 11:28:18 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 14:50:21 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_memmove: Copies memory safely, even if regions overlap.
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;

	s = (const unsigned char *)src;
	d = (unsigned char *)dest;
	if (d == s || !n)
		return (dest);
	if (d < s)
	{
		while (n--)
			*d++ = *s++;
	}
	else
	{
		d += n;
		s += n;
		while (n--)
			*(--d) = *(--s);
	}
	return (dest);
}

// #include <stdio.h>
// int main(void)
// {
// 	char str[] = "123456789";
// 	ft_memmove(str + 2, str, 5);  // Overlapping copy
// 	printf("Result: %s\n", str);  // Expected: "121234589"
// 	return 0;
// } // TESTED 