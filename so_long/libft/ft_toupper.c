/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_toupper.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/22 14:52:28 by tiyang        #+#    #+#                 */
/*   Updated: 2025/04/29 10:47:18 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// ft_toupper: Converts a lowercase letter to uppercase.
#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	else
		return (c);
}

// #include <stdio.h>
// int main()
// {
// 	printf("%c", toupper(109));
// } //TESTED 