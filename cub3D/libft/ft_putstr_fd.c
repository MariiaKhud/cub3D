/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 14:25:32 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 16:01:20 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_putstr_fd: Writes a string to a file descriptor.
#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

// int main(void)
// {
// 	ft_putstr_fd("Hello, libft!\n", 1); // should print: Hello, libft!
// 	return 0;
// } // tested 