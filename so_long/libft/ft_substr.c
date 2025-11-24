/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/25 11:02:18 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 16:35:57 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_substr: Extracts a substring from a string starting at a given index.
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	slen;
	size_t	i;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > slen - start)
		len = slen - start;
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

/* #include <stdio.h>
int main(void)
{
    char *result;

    // Test 1: Normal case
    result = ft_substr("Hello, world!", 7, 5);
    printf("Test 1: %s\n", result);
    free(result);

    // Test 2: len exceeds end of string
    result = ft_substr("42 Network", 3, 100);
    printf("Test 2: %s\n", result);
    free(result);

    // Test 3: start beyond string length
    result = ft_substr("Short", 10, 3);
    printf("Test 3: '%s'\n", result);
    free(result);

    // Test 4: start = 0, len = 0
    result = ft_substr("Nothing here", 0, 0);
    printf("Test 4: '%s'\n", result);
    free(result);

    // Test 5: full string
    result = ft_substr("Complete", 0, 8);
    printf("Test 5: %s\n", result);
    free(result);

    // Test 6: empty input string
    result = ft_substr("", 0, 5);
    printf("Test 6: '%s'\n", result);
    free(result);

    // Test 7: Null input string
    result = ft_substr(NULL, 0, 5);
    printf("Test 7: %s\n", result);  // May crash if NULL isn't handled
    free(result);

    return 0;
} // tested  */ 