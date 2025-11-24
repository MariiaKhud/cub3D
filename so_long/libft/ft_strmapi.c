/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 13:10:48 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 10:54:10 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_strmapi: Applies a function to each character of a string (with index), 
//				returning a new string.
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	i;
	char	*dest;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dest[i] = f((unsigned int)i, s[i]);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/* // Testing function
#include <stdio.h>

static char example_function(unsigned int i, char c)
{
    if (i % 2 == 0)
        return c - 32;  // Convert to uppercase if index is even
    return c;  // Otherwise, leave the character unchanged
}

int main(void)
{
    char *result;

    result = ft_strmapi("abcdef", &example_function);
    if (result)
    {
        printf("Result: \"%s\"\n", result);
        free(result); 
    }

    result = ft_strmapi(NULL, &example_function);
    if (!result)
        printf("NULL string returned NULL as expected.\n");

    return 0;
} // TESTED
 */