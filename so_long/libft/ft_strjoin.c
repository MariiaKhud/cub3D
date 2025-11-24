/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/25 11:48:04 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 16:20:40 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_strjoin: Concatenates two strings into a new one.
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	l1;
	size_t	l2;
	char	*d;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	d = malloc(sizeof(char) * (l1 + l2 + 1));
	if (!d)
		return (NULL);
	i = 0;
	j = 0;
	while (j < l1)
		d[i++] = s1[j++];
	j = 0;
	while (j < l2)
		d[i++] = s2[j++];
	d[i] = '\0';
	return (d);
}

/* #include <stdio.h> 
int main(void)
{
    const char *str1 = "Hello, ";
    const char *str2 = "world!";
    char *joined;

    joined = ft_strjoin(str1, str2);
    if (joined)
    {
        printf("Result: \"%s\"\n", joined);
        free(joined); 
    }
    else
    {
        printf("Memory allocation failed.\n");
    }

    return 0;
} // tested 
 */ 