/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 16:33:19 by tiyang        #+#    #+#                 */
/*   Updated: 2025/06/30 10:39:59 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include "get_next_line/get_next_line.h"
# include "ft_printf/ft_printf.h"

// Character checks and conversions
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
// Memory functions
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
// String length and manipulation
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *s);
// Advanced string handling
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
// Number conversion
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);
// File descriptor output
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

#endif
/* 
####### Character checks and conversions #######

ft_isalpha: Checks if a character is an alphabetic letter (A-Z, a-z).

ft_isdigit: Checks if a character is a digit (0-9).

ft_isalnum: Checks if a character is alphanumeric (letter or digit).

ft_isascii: Checks if a character is a valid ASCII character (0–127).

ft_isprint: Checks if a character is printable 
			(includes space, excludes control chars).

ft_tolower: Converts an uppercase letter to lowercase.

ft_toupper: Converts a lowercase letter to uppercase.

####### Memory functions #######

ft_bzero: Sets a memory block to zero.

ft_memset: Fills a block of memory with a specific byte value.

ft_memcpy: Copies memory from one location to another (non-overlapping).

ft_memmove: Copies memory safely, even if regions overlap.

ft_memchr: Searches memory for a byte value.

ft_memcmp: Compares two memory areas byte by byte.

ft_calloc: Allocates and zeroes memory for an array.

####### String length and manipulation #######

ft_strlen: Returns the length of a null-terminated string.

ft_strlcpy: Safely copies a string into a buffer 
			(like strncpy, but null-terminates).

ft_strlcat: Appends one string to another, respecting buffer size.

ft_strncmp: Compares two strings up to n characters.

ft_strchr: Finds the first occurrence of a character in a string.

ft_strrchr: Finds the last occurrence of a character in a string.

ft_strnstr: Finds a substring within a string, 
			searching at most len characters.

ft_strdup: Duplicates a string using dynamic memory allocation.

####### Advanced string handling #######

ft_substr: Extracts a substring from a string starting at a given index.

ft_strjoin: Concatenates two strings into a new one.

ft_strtrim: Removes specified characters from the beginning and end of a string.

ft_split: Splits a string into an array of strings based on a delimiter.

ft_strmapi: Applies a function to each character of a string (with index), 
			returning a new string.

ft_striteri: Applies a function to each character of a string (with index), 
			modifying it in-place.

####### Number conversion #######

ft_atoi: Converts a string to an integer.

ft_itoa: Converts an integer to a string.

####### File descriptor output #######

ft_putchar_fd: Writes a character to a file descriptor.

ft_putstr_fd: Writes a string to a file descriptor.

ft_putendl_fd: Writes a string followed by a newline to a file descriptor.

ft_putnbr_fd: Writes an integer to a file descriptor.

 */