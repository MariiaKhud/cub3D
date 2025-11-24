/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 14:32:07 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 16:19:55 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_strdup: Duplicates a string using dynamic memory allocation.
#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	l;
	char	*d;

	l = 0;
	while (s[l])
		l++;
	d = (char *)malloc((l + 1) * sizeof(char));
	if (!d)
		return (NULL);
	l = 0;
	while (s[l])
	{
		d[l] = s[l];
		l++;
	}
	d[l] = '\0';
	return (d);
}

/* 
#include <stdio.h>

int main(void)
{
	char *s = "Libft is fun!";
	char *copy = ft_strdup(s);

	printf("Original : %s\n", s);
	printf("Copy     : %s\n", copy);

	free(copy);
	return 0;
} // tested */