/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 11:19:47 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 10:54:48 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_itoa: Converts an integer to a string.
#include "libft.h"

static int	count_digit(int n)
{
	int	count;

	if (n == -2147483648)
		return (11);
	count = 1;
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n > 9)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*dest;
	int		len;

	len = count_digit(n);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	if (n == -2147483648)
	{
		ft_strlcpy(dest, "-2147483648", len + 1);
		return (dest);
	}
	if (n < 0)
	{
		dest[0] = '-';
		n *= -1;
	}
	dest[len] = '\0';
	while (n > 9)
	{
		dest[--len] = n % 10 + '0';
		n /= 10;
	}
	dest[len - 1] = n % 10 + '0';
	return (dest);
}

/* #include <stdio.h>
int main(void)
{
    char *result;

    printf("Test 1 (Zero):\n");
    result = ft_itoa(0);
    if (result)
    {
        printf("Result: \"%s\"\n", result);
        free(result);
    }

    printf("\nTest 2 (Positive number):\n");
    result = ft_itoa(12345);
    if (result)
    {
        printf("Result: \"%s\"\n", result);
        free(result);
    }

    printf("\nTest 3 (Negative number):\n");
    result = ft_itoa(-6789);
    if (result)
    {
        printf("Result: \"%s\"\n", result);
        free(result);
    }

    printf("\nTest 4 (INT_MIN):\n");
    result = ft_itoa(-2147483648);
    if (result)
    {
        printf("Result: \"%s\"\n", result);
        free(result);
    }

    printf("\nTest 5 (INT_MAX):\n");
    result = ft_itoa(2147483647);
    if (result)
    {
        printf("Result: \"%s\"\n", result);
        free(result);
    }

    return (0);
} // TESTED */