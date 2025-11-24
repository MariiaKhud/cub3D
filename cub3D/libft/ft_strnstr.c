/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 10:54:28 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 10:52:13 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_strnstr: Finds a substring within a string, 
//				searching at most len characters.
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;
	const char	*sbig;

	if (!*little)
		return ((char *)big);
	i = 0;
	while (i < len && big[i])
	{
		if (big[i] == *little)
		{
			sbig = &big[i];
			j = 0;
			while (i + j < len && sbig[j] && sbig[j] == little[j])
			{
				j++;
				if (!little[j])
					return ((char *)sbig);
			}
		}
		i++;
	}
	return (NULL);
}

/* #include <stdio.h>
int main(void)
{
    const char *haystack = "This is a simple string.";
    const char *needle1 = "simple";
    const char *needle2 = "string";
    const char *needle3 = "notfound";
    const char *needle4 = ""; // Edge case: empty needle

    char *result;

    result = ft_strnstr(haystack, needle1, 20);
    printf("Searching for \"%s\" in \"%s\" (len = 20): %s\n",
           needle1, haystack, result ? result : "Not found");

    result = ft_strnstr(haystack, needle2, 10);
    printf("Searching for \"%s\" in \"%s\" (len = 10): %s\n",
           needle2, haystack, result ? result : "Not found");

    result = ft_strnstr(haystack, needle3, 25);
    printf("Searching for \"%s\" in \"%s\" (len = 25): %s\n",
           needle3, haystack, result ? result : "Not found");

    result = ft_strnstr(haystack, needle4, 5);
    printf("Searching for empty needle in \"%s\" (len = 5): %s\n",
           haystack, result ? result : "Not found");

    return 0;
} //TESTED */