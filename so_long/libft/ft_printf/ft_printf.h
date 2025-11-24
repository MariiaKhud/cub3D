/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/01 12:54:38 by tiyang        #+#    #+#                 */
/*   Updated: 2025/05/22 10:36:30 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h> // for variadic functions
# include <unistd.h> // for write
# include <limits.h> // for INT_MIN
# include <stdint.h> // for uintptr_t

int	print_char(int c);
int	print_str(char *str);
int	print_ptr(void *ptr);
int	print_int(int n);
int	print_unsigned_int(unsigned int n);
int	print_hex_lower(unsigned int n);
int	print_hex_upper(unsigned int n);
int	handle_format(char format, va_list args);
int	ft_printf(const char *format, ...);

#endif