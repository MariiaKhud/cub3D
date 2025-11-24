/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 11:28:44 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 16:29:41 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_strncmp: Compares two strings up to n characters.
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/* #include <stdio.h>

int main(void)
{
    const char *s1 = "apple";
    const char *s2 = "apricot";
    int result;

    result = ft_strncmp(s1, s2, 2);
    printf("Comparing first 2 chars: \"%s\" vs \"%s\" → %d\n", s1, s2, result);

    result = ft_strncmp(s1, s2, 5);
    printf("Comparing first 5 chars: \"%s\" vs \"%s\" → %d\n", s1, s2, result);

    result = ft_strncmp(s1, s1, 5);
    printf("Comparing same strings: \"%s\" vs \"%s\" → %d\n", s1, s1, result);

    return 0;
} // tested 
 */