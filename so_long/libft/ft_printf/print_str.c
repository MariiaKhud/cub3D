/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_str.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/01 13:33:10 by tiyang        #+#    #+#                 */
/*   Updated: 2025/05/22 11:30:59 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_str(char *str)
{
	int	i;

	if (!str)
		return (write(1, "(null)", 6));
	i = 0;
	while (str[i])
		i++;
	return (write(1, str, i));
}

/* 
#include <unistd.h>

int main(void)
{
    print_str("Hello, Codam!");
    write(1, "\n", 1);
    print_str("");
    write(1, "\n", 1);
    print_str(NULL); // 
    write(1, "\n", 1);
    return 0;
}
// TESTED 
 */