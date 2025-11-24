/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 14:31:58 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 16:02:07 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_putendl_fd: Writes a string followed by a newline to a file descriptor.
#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
	write(fd, "\n", 1);
}

// int main(void)
// {
// 	ft_putendl_fd("This is a line.", 1); // should print: This is a line.\n
// 	return 0;
// } // tested 