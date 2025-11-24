/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 15:30:31 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 14:30:37 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_bzero: Sets a memory block to zero.
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n--)
		*p++ = 0;
}

/* #include <stdio.h>
int main(void)
{
	char buffer[10] = "abcdef"; 
	// rest of the elements (from index 6 to 9) will be set to '\0' 
	// automatically by the compiler.
	ft_bzero(buffer + 2, 3); // set index 2 - 4 to '\0'
	// Prints each character, replacing null bytes with a dot
	for (int i = 0; i < 10; i++) 
		printf("%c ", buffer[i] ? buffer[i] : '.');
	printf("\n");
	return 0;
} // TESTED */