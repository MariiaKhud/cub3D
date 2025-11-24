/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 11:28:34 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/30 16:55:29 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_strchr: Finds the first occurrence of a character in a string.
// return type is char *,
// need to cast the result.
// Passing a NULL pointer to strchr()
// is undefined behavior. 
// therefor we don't check the edge case
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	while (*s)
	{
		if (*s == uc)
			return ((char *)s);
		s++;
	}
	if (uc == '\0')
		return ((char *)s);
	return (NULL);
}

/* 
#include <stdio.h>

int main(void)
{
	const char *str = "Hello, world!";
	char c = 'o';
	char *result = ft_strchr(str, c);

	if (result)
		printf("Character '%c' found at position: %ld\n", c, result - str);
	else
		printf("Character '%c' not found.\n", c);

	// Test with a character that does not exist
	c = 'z';
	result = ft_strchr(str, c);
	if (result)
		printf("Character '%c' found at position: %ld\n", c, result - str);
	else
		printf("Character '%c' not found.\n", c);

	// Test with null terminator
	c = '\0';
	result = ft_strchr(str, c);
	if (result)
		printf("Null terminator found at position: %ld\n", result - str);
	else
		printf("Null terminator not found.\n");

	// Test with large integer
	// wrap to 0
	c = 1024;
	result = ft_strchr(str, c);
	if (result)
		printf("Null terminator found at position: %ld\n", result - str);
	else
		printf("Null terminator not found.\n");

	return 0;
} // tested  */