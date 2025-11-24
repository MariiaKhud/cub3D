/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_format.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/01 13:14:32 by tiyang        #+#    #+#                 */
/*   Updated: 2025/05/22 17:36:02 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	valid_format(char format)
{
	const char	*valid_format_specifier;
	int			i;

	valid_format_specifier = "cspdiuxX%";
	i = 0;
	while (valid_format_specifier[i])
	{
		if (format == valid_format_specifier[i])
			return (1);
		i++;
	}
	return (0);
}

// putting together the print_* functions which return the number of characters
// printed to the terminal
int	handle_format(char format, va_list args)
{
	int	count;

	if (!valid_format(format))
		return (print_char('%') + print_char(format));
	count = 0;
	if (format == 'c')
		count += print_char(va_arg(args, int));
	else if (format == 's')
		count += print_str(va_arg(args, char *));
	else if (format == 'p')
		count += print_ptr(va_arg(args, void *));
	else if (format == 'd' || format == 'i')
		count += print_int(va_arg(args, int));
	else if (format == 'u')
		count += print_unsigned_int(va_arg(args, unsigned int));
	else if (format == 'x')
		count += print_hex_lower(va_arg(args, unsigned int));
	else if (format == 'X')
		count += print_hex_upper(va_arg(args, unsigned int));
	else
		count += print_char('%');
	return (count);
}
