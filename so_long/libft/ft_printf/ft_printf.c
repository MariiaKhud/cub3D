/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/01 11:37:53 by tiyang        #+#    #+#                 */
/*   Updated: 2025/05/22 17:46:35 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		written_count;
	int		print_count;

	if (!format)
		return (-1);
	i = 0;
	written_count = 0;
	print_count = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
			written_count = handle_format(format[++i], args);
		else
			written_count = write(1, &format[i], 1);
		if (written_count < 0)
			return (va_end(args), -1);
		print_count += written_count;
		i++;
	}
	return (va_end(args), print_count);
}

/* #include <stdio.h>  // for the real printf
#include <fcntl.h>
// need to makefile first!

int main(void)
{
    int ret1, ret2;

	// Test 0: no format specifier
	printf("Real printf: \n");
    ret1 = printf("hello world\n");
	printf("ft_printf: \n");
    ret2 = ft_printf("hello world\n");
    printf("printf returned: %d\n", ret1);
    printf("ft_printf returned: %d\n\n", ret2);

    // Test 1: character
	printf("Real printf: \n");
    ret1 = printf("%c\n", 'a');
	printf("ft_printf: \n");
    ret2 = ft_printf("%c\n", 'a');
    printf("printf returned: %d\n", ret1);
    printf("ft_printf returned: %d\n\n", ret2);

	// Test 2: string
	printf("Real printf: \n");
    ret1 = printf("Hello %s\n", "Codam student");
    printf("ft_printf: \n");
	ret2 = ft_printf("Hello %s\n", "Codam student");
    printf("printf returned: %d\n", ret1);
    printf("ft_printf returned: %d\n\n", ret2);

	// Test 2.1: NULL pointer
	printf("Real printf: \n");
    ret1 = printf("Hello %s\n", NULL);
    printf("ft_printf: \n");
	ret2 = ft_printf("Hello %s\n", NULL);
    printf("printf returned: %d\n", ret1);
    printf("ft_printf returned: %d\n\n", ret2);

	// Test 2.2: empty string
	printf("Real printf: \n");
	ret1 = printf("%s\n", "");
	printf("ft_printf: \n");
	ret2 = ft_printf("%s\n", "");
	printf("printf returned: %d\n", ret1);
	printf("ft_printf returned: %d\n\n", ret2);

	// Test 3: pointer
    void *ptr = &ret1;
	printf("Real printf: \n");
    ret1 = printf("%p\n", ptr);
	printf("ft_printf: \n");
    ret2 = ft_printf("%p\n", ptr);
    printf("printf returned: %d\n", ret1);
    printf("ft_printf returned: %d\n\n", ret2);

	// Test 3.1: NULL pointer
    ptr = NULL;
	printf("Real printf: \n");
    ret1 = printf("%p\n", ptr);
	printf("ft_printf: \n");
    ret2 = ft_printf("%p\n", ptr);
    printf("printf returned: %d\n", ret1);
    printf("ft_printf returned: %d\n\n", ret2);

    // Test 4: integers (INT_MAX & INT_MIN)
	printf("Real printf: \n");
    ret1 = printf("%d, %i\n", INT_MAX, INT_MIN);
	printf("ft_printf: \n");
    ret2 = ft_printf("%d, %i\n", INT_MAX, INT_MIN);
    printf("printf returned: %d\n", ret1);
    printf("ft_printf returned: %d\n\n", ret2);

    // Test 5: unsigned integers (UINT_MAX)
	printf("Real printf: \n");
    ret1 = printf("%u\n", UINT_MAX);
	printf("ft_printf: \n");
    ret2 = ft_printf("%u\n", UINT_MAX);
    printf("printf returned: %d\n", ret1);
    printf("ft_printf returned: %d\n\n", ret2);

    // Test 6: hex lowercase
	printf("Real printf: \n");
    ret1 = printf("%x\n", 48888);
	printf("ft_printf: \n");
    ret2 = ft_printf("%x\n", 48888);
    printf("printf returned: %d\n", ret1);
    printf("ft_printf returned: %d\n\n", ret2);

    // Test 7: hex uppercase
	printf("Real printf: \n");
    ret1 = printf("%X\n", 48888);
	printf("ft_printf: \n");
    ret2 = ft_printf("%X\n", 48888);
    printf("printf returned: %d\n", ret1);
    printf("ft_printf returned: %d\n\n", ret2);

    // Test 8: percent sign
	printf("Real printf: \n");
    ret1 = printf("%%%%\n");
	printf("ft_printf: \n");
    ret2 = ft_printf("%%%%\n");
    printf("printf returned: %d\n", ret1);
    printf("ft_printf returned: %d\n\n", ret2);

	// ERROR HANDLING: invalid nor no format specifier: undefined behavior
	printf("Real printf: \n");
    ret1 = printf("hello %k!!!\n", "world");
	printf("ft_printf: \n");
    ret2 = ft_printf("hello %k!!!\n", "world");
    printf("printf returned: %d\n", ret1);
    printf("ft_printf returned: %d\n\n", ret2);

	// ERROR HANDLING: write() fails, returns -1
	// Save original stdout and close stdout to simulate a write failure
	int saved_stdout = dup(1);   
	close(1); 
    ret1 = printf("hello %s\n", "world");
    ret2 = ft_printf("hello %s\n", "world");
	// Restore stdout
	dup2(saved_stdout, 1);
    close(saved_stdout);
	// print result
    printf("printf returned: %d\n", ret1);
    printf("ft_printf returned: %d\n\n", ret2);

	// ERROR HANDLING: too many arguments: ignore extra arguments
	printf("Real printf: \n");
	ret1 = printf("Hi %s\n", "Codam", 123, 'x');
	printf("ft_printf: \n");
	ret2 = ft_printf("Hi %s\n", "Codam", 123, 'x');
	printf("printf returned: %d\n", ret1);
    printf("ft_printf returned: %d\n\n", ret2);

	// ERROR HANDLING: too few arguments: undefined behavior
	printf("Real printf: \n");
	ret1 = printf("Hi %s, you were %d years old in year %d\n", "Karin");
	printf("ft_printf: \n");
	ret2 = ft_printf("Hi %s, you were %d years old in year %d\n", "Karin");
	printf("printf returned: %d\n", ret1);
    printf("ft_printf returned: %d\n\n", ret2);
	
	// ERROR HANDLING: argument does not match format: undefined behavior
	printf("Real printf: \n");
	ret1 = printf("Hi %d\n", "Karin");
	printf("ft_printf: \n");
	ret2 = ft_printf("Hi %d\n", "Karin");
	printf("printf returned: %d\n", ret1);
    printf("ft_printf returned: %d\n\n", ret2);

	// ERROR HANDLING: NULL passed as format
	printf("Real printf: \n");
	ret1 = printf(NULL);
	printf("ft_printf: \n");
	ret2 = ft_printf(NULL);
	printf("printf returned: %d\n", ret1);
    printf("ft_printf returned: %d\n\n", ret2);
	
    return 0;
} */