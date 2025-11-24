/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_ptr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/01 14:47:20 by tiyang        #+#    #+#                 */
/*   Updated: 2025/05/22 13:31:41 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_hex_pointer(uintptr_t address)
{
	const char	*hex_lower;
	char		digit;
	int			count;

	count = 0;
	hex_lower = "0123456789abcdef";
	if (address >= 16)
		count += print_hex_pointer(address / 16);
	digit = hex_lower[address % 16];
	count += write(1, &digit, 1);
	return (count);
}

int	print_ptr(void *ptr)
{
	uintptr_t	address;
	int			count;

	count = 0;
	address = (uintptr_t)ptr;
	if (!address)
	{
		count += write(1, "(nil)", 5);
		return (count);
	}
	count += write(1, "0x", 2);
	count += print_hex_pointer(address);
	return (count);
}

/* 
#include <stdio.h>

int main(void)
{
	int x = 42;
    int *ptr1 = &x;
	printf("Real printf: \n");
    int ret1 = printf("%p", ptr1);
	printf("\n");
	printf("print_ptr: \n");
    int ret2 = print_ptr(ptr1);
    printf("\nprintf returned: %d\n", ret1);
    printf("print_ptr returned: %d\n\n", ret2);

	int *ptr2 = NULL;
	printf("Real printf: \n");
    ret1 = printf("%p", ptr2);
	printf("\n");
	printf("print_ptr: \n");
    ret2 = print_ptr(ptr2);
    printf("\nprintf returned: %d\n", ret1);
    printf("print_ptr returned: %d\n\n", ret2);
}
 // tested */