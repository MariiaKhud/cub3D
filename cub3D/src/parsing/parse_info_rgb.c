/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info_rgb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 13:04:34 by makhudon          #+#    #+#             */
/*   Updated: 2025/11/28 13:33:13 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/** 
 * @brief Skips leading spaces and tabs in a string.
 * @param s The string to process.
 * @return char* Pointer to the first non-space character.
 */
static char	*skip_spaces(char *s)
{
	while (*s == ' ' || *s == '\t')
		s++;
	return (s);
}

/**
 * @brief Converts RGB string components to a single integer color.
 * @param r_str The red component as a string.
 * @param g_str The green component as a string.
 * @param b_str The blue component as a string.
 * @return int The combined RGB color as an integer.
 */
static int	convert_rgb(char *r_str, char *g_str, char *b_str)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(skip_spaces(r_str));
	g = ft_atoi(skip_spaces(g_str));
	b = ft_atoi(skip_spaces(b_str));
	return ((r << 16) | (g << 8) | b);
}

/**
 * @brief Validates if a string represents a valid RGB number (0-255).
 * @param s The string to validate.
 * @return int 1 if valid, 0 otherwise.
 */
static int	is_valid_rgb_number(const char *s)
{
	int	number;

	while (*s == ' ' || *s == '\t')
		s++;
	if (*s == '\0')
		return (0);
	number = ft_atoi(s);
	if (number < 0 || number > 255)
		return (0);
	while (*s && *s != ',' && *s != ' ' && *s != '\t')
	{
		if (!(*s >= '0' && *s <= '9'))
			return (0);
		s++;
	}
	return (1);
}

/**
 * @brief Parses an RGB color from a string in the format "R,G,B".
 * @param line The string containing the RGB values.
 * @return int The combined RGB color as an integer,
 *         or -1 on error.
 */
static int	parse_rgb(char *line)
{
	char	**split;
	int		i;
	int		result;

	split = ft_split(line, ',');
	if (split == NULL)
		return (-1);
	i = 0;
	while (split[i] != NULL)
		i++;
	if (i != 3)
		return (free_split(split), -1);
	i = 0;
	while (i < 3)
	{
		if (!is_valid_rgb_number(split[i]))
		{
			free_split(split);
			return (-1);
		}
		i++;
	}
	result = convert_rgb(split[0], split[1], split[2]);
	free_split(split);
	return (result);
}

/**
 * @brief Parses a color line into an integer, trimming whitespace.
 * @param line Pointer to the line containing the color (e.g., "34,139,34").
 * @return The integer color, or -1 on error.
 */
int	parse_color_line(char *line)
{
	trim_trailing_whitespace(line);
	return (parse_rgb(line));
}
