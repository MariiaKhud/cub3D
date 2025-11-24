/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_striteri.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 13:33:48 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 10:54:27 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_striteri: Applies a function to each character of a string (with index), 
//				modifying it in-place.
#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

/* // TESTING FUNCTION
#include <stdio.h>

void example_function(unsigned int i, char *c)
{
    // we turn characters at even indices to uppercase.
    if (i % 2 == 0)
        *c = (*c >= 'a' && *c <= 'z') ? *c - 32 : *c; // Convert to uppercase
}

int main(void)
{
    char str[] = "abcdef";
    
    printf("Before ft_striteri: %s\n", str);
    ft_striteri(str, example_function);
    printf("After ft_striteri: %s\n", str);

    return 0;
} //TESTED */