/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/25 13:38:16 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 16:10:12 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_split: Splits a string into an array of strings based on a delimiter.
#include "libft.h"

static size_t	count_strings(char const *s, char c)
{
	size_t	i;
	size_t	string_count;
	int		new_string;

	i = 0;
	string_count = 0;
	new_string = 1;
	while (s[i])
	{
		if (s[i] == c)
			new_string = 1;
		else
		{
			if (new_string == 1)
			{
				string_count++;
				new_string = 0;
			}
		}
		i++;
	}
	return (string_count);
}

static void	free_memory(char **dest, size_t j)
{
	size_t	k;

	k = 0;
	while (k < j)
	{
		free(dest[k]);
		k++;
	}
	free(dest);
}

static char	*copy_sub_string(char const *s, char c, size_t *i)
{
	size_t	sub_len;
	size_t	start;
	char	*sub_str;

	sub_len = 0;
	start = *i;
	while (s[start + sub_len] && s[start + sub_len] != c)
		sub_len++;
	sub_str = (char *)malloc(sizeof(char) * (sub_len + 1));
	if (!sub_str)
		return (NULL);
	ft_strlcpy(sub_str, s + start, sub_len + 1);
	*i += sub_len;
	return (sub_str);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	dest = (char **)malloc(sizeof(char *) * (count_strings(s, c) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			dest[j] = copy_sub_string(s, c, &i);
			if (!dest[j])
				return (free_memory(dest, j), NULL);
			j++;
		}
	}
	dest[j] = NULL;
	return (dest);
}

/* // TESTING FUNCTION
#include <stdio.h>
static void print_split_result(char **result)
{
    int i = 0;
    if (!result)
    {
        printf("Result is NULL\n");
        return;
    }
    while (result[i])
    {
        printf("result[%d]: \"%s\"\n", i, result[i]);
        i++;
    }
}

static void free_split_result(char **result)
{
    int i = 0;
    if (!result)
        return;
    while (result[i])
    {
        free(result[i]);
        i++;
    }
    free(result);
}

int main(void)
{
    char **split;
    
    printf("Test 1:\n");
    split = ft_split("Hello world 42 school", ' ');
    print_split_result(split);
    free_split_result(split);

    printf("\nTest 2:\n");
    split = ft_split("  this  is   a test ", ' ');
    print_split_result(split);
    free_split_result(split);

    printf("\nTest 3:\n");
    split = ft_split("splitXthisXstringXonXcharX", 'X');
    print_split_result(split);
    free_split_result(split);

    printf("\nTest 4 (empty string):\n");
    split = ft_split("", ' ');
    print_split_result(split);
    free_split_result(split);

    printf("\nTest 5 (delimiter not found):\n");
    split = ft_split("NoDelimiterHere", ' ');
    print_split_result(split);
    free_split_result(split);

    printf("\nTest 6 (NULL input):\n");
    split = ft_split(NULL, ' ');
    print_split_result(split);

    return (0);
} // TESTED */