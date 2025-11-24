/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/24 14:48:54 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 15:54:20 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_calloc: Allocates and zeroes memory for an array.
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*d;
	unsigned char	*p;
	size_t			total;

	if (!nmemb || !size)
	{
		d = malloc(0);
		return ((void *)d);
	}
	total = nmemb * size;
	if (total / nmemb != size)
		return (NULL);
	d = malloc(total);
	if (!d)
		return (NULL);
	p = d;
	while (total--)
		*p++ = 0;
	return ((void *)d);
}

/* #include <stdio.h>

int main(void)
{
    // Test 1: Normal case
    int *arr = (int *)ft_calloc(5, sizeof(int));
    if (arr)
    {
        printf("Test 1: Normal allocation\n");
        for (int i = 0; i < 5; i++)
            printf("arr[%d] = %d\n", i, arr[i]); // Should all be 0
        free(arr);
    }

    // Test 2: Zero nmemb
    void *z1 = ft_calloc(0, 4);
    printf("\nTest 2: calloc(0, 4) = %p\n", z1);
    free(z1);

    // Test 3: Zero size
    void *z2 = ft_calloc(4, 0);
    printf("Test 3: calloc(4, 0) = %p\n", z2);
    free(z2);

    // Test 4: Overflow detection
    size_t big = (size_t)-1;
    void *z3 = ft_calloc(big, big); // This should fail and return NULL
    printf("Test 4: Overflow test = %p\n", z3);

    return 0;
}// tested  */