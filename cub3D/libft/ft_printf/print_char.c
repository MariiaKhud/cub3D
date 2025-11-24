/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_char.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/01 13:29:34 by tiyang        #+#    #+#                 */
/*   Updated: 2025/05/22 17:40:41 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(int c)
{
	return (write(1, &c, 1));
}

/* #include <unistd.h>

int main(void)
{
    print_char('A');
    write(1, "\n", 1);
    print_char('z');
    write(1, "\n", 1);
    print_char('\n');
    write(1, "\n", 1);
    print_char(0);   // NULL character
    write(1, "\n", 1);
    print_char(127); // DEL character
    write(1, "\n", 1);
    return 0;
} // TESTED */