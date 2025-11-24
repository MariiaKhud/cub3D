/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/25 13:39:36 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 16:36:57 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_strtrim: Removes specified characters 
//				from the beginning and end of a string.
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*dest;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	if (!s1[start])
		return (ft_strdup(""));
	end = ft_strlen(s1) - 1;
	while (end > start && ft_strchr(set, s1[end]))
		end--;
	len = end - start + 1;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s1 + start, len + 1);
	return (dest);
}

/*  #include <stdio.h>
int main() {
    // Test 1: Trim spaces from the beginning and end
    char *test1 = ft_strtrim("  hello world  ", " ");
    printf("Test 1: '%s'\n", test1);  // Expected: "hello world"
    free(test1);

    // Test 2: Trim specific characters 
		(e.g., "h" "l" and "d") from the beginning and end
    char *test2 = ft_strtrim("hello world", "hdl");
    printf("Test 2: '%s'\n", test2);  // Expected: "ello worl"
    free(test2);

    // Test 3: Trim characters from both ends 
	when there's nothing to trim in the middle
    char *test3 = ft_strtrim("abcdef", "abc");
    printf("Test 3: '%s'\n", test3);  // Expected: "def"
    free(test3);

    // Test 4: Empty string as input
    char *test4 = ft_strtrim("", "abc");
    printf("Test 4: '%s'\n", test4);  // Expected: "" (empty string)
    free(test4);

    // Test 5: Trim when the entire string is part of the set
    char *test5 = ft_strtrim("aaa", "a");
    printf("Test 5: '%s'\n", test5);  // Expected: "" (empty string)
    free(test5);

    // Test 6: String with no trimming needed
    char *test6 = ft_strtrim("hello world", "z");
    printf("Test 6: '%s'\n", test6);  // Expected: "hello world"
    free(test6);

	// Test 7: Short string 
    char *test7 = ft_strtrim("     a    ", " ");
    printf("Test 7: '%s'\n", test7);  // Expected: "a"
    free(test7);

    return 0;
} //tested */