/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 11:28:51 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/30 16:54:57 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_strrchr: Finds the last occurrence of a character in a string.
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	unsigned char	uc;

	uc = (unsigned char)c;
	i = 0;
	while (s[i])
		i++;
	if (uc == '\0')
		return ((char *)(s + i));
	while (i > 0)
	{
		if (*(s + i - 1) == uc)
			return ((char *)(s + i - 1));
		i--;
	}
	return (NULL);
}

/* 
#include <stdio.h>

int main(void)
{
    const char *str = "hello world!";
    char c = 'o';
    char *result;

    result = ft_strrchr(str, c);
    if (result)
        printf("Last occurrence of '%c' in \"%s\" is at position: %ld\n", 
		c, str, result - str);
    else
        printf("Character '%c' not found in \"%s\"\n", c, str);

    // Test with a character not in the string
    c = 'z';
    result = ft_strrchr(str, c);
    if (result)
        printf("Last occurrence of '%c' in \"%s\" is at position: %ld\n", 
		c, str, result - str);
    else
        printf("Character '%c' not found in \"%s\"\n", c, str);

    // Test with null terminator
    c = '\0';
    result = ft_strrchr(str, c);
    if (result)
        printf("Last occurrence of '\\0' in \"%s\" is at position: %ld\n", 
		str, result - str);
    else
        printf("Null terminator not found in \"%s\"\n", str);
	
	// tested with large integer
	// wrap to 0 because of (unsigned char)c
	c = 1024;
	result = ft_strrchr(str, c);
    if (result)
        printf("Last occurrence of '\\0' in \"%s\" is at position: %ld\n", 
		str, result - str);
    else
        printf("Null terminator not found in \"%s\"\n", str);

    return 0;
} // tested */