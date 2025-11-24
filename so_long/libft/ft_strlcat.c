/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/22 16:59:29 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 16:23:46 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_strlcat: Appends one string to another, respecting buffer size.
//
// Note, however, that if strlcat() traverses size characters without find‐
//      ing a NUL, the length of the string is considered to be size 
//       and the destination string will not be NUL-terminated 
//		(since there was no space for the NUL).  
//		This keeps strlcat() from running off the end of a string.  
// In practice this should not happen (as it means that either size is incor‐
//      rect or that dst is not a proper “C” string).  The check exists to pre‐
//      vent potential security problems in incorrect code.
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	i;

	srclen = 0;
	while (src[srclen])
		srclen++;
	dstlen = 0;
	while (dst[dstlen] && dstlen < size)
		dstlen++;
	if (size == dstlen)
		return (srclen + size);
	i = 0;
	while (i < size - dstlen - 1 && src[i])
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (srclen + dstlen);
}

// #include <stdio.h>
// static void test(int size)
// {
//     char src[] = "a string with a length of 28"; // strlen(src) = 28;
//     char buffer[size]; 
// 	char dst[] = "ah!"; // strlen(buffer) = 3;
// 	// ft_strcpy - copy dst to the buffer
// 	int i = 0;
// 	while (dst[i])
// 	{
// 		buffer[i] = dst[i];
// 		i++;
// 	}
// 	buffer[i] = '\0';
//     int r;
//     r = ft_strlcat(buffer,src,size);
//     printf("appended '%s' to '%s', result is '%s', combi length %d\n",
//             src,
// 			dst,
//             buffer,
//             r
//           );
// }
// int main()
// {
//     test(32); // buffer size exactly enough to copy src to dst
//     test(14);
//     test(4); // buffer size leaves no space for appendment
//     return(0);
// } // tested 