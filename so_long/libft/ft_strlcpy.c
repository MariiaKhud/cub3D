/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/22 15:02:00 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 16:27:00 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_strlcpy: Safely copies a string into a buffer 
//				(like strncpy, but null-terminates).
#include "libft.h"

// size is an unsigned type (size_t), so it can never be negative.
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	i;

	srclen = 0;
	while (src[srclen])
		srclen++;
	if (size == 0)
		return (srclen);
	i = 0;
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}

// #include <stdio.h>
// void test(int size)
// {
//     char string[] = "a string with a length of 28"; // strlen(string) = 28;
//     char buffer[size];
//     int r;
//     r = ft_strlcpy(buffer,string,size);
// 	if (size == 0)
// 	{
// 		printf("Buffer size entered is 0, copying not possible, ");
// 		printf("src length is %d\n", r);
// 		return ;
// 	}
//     printf("Copied %d characters from '%s' into '%s', src length is %d\n",
// 			size - 1,
//             string,
//             buffer,
//             r
//           );
// }
// int main()
// {
//     test(29);
//     test(14);
//     test(1);
//     test(0);
//     return(0);
// } // tested 