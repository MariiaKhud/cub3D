/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putchar_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 14:21:15 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 15:59:06 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_putchar_fd: Writes a character to a file descriptor.
#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/* 
int main(void)
{
	ft_putchar_fd('A', 1); // should print: A
	ft_putchar_fd('\n', 1);
	return 0;
} // tested  */