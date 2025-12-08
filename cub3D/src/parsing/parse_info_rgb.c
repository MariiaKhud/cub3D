/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info_rgb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 13:04:34 by makhudon          #+#    #+#             */
/*   Updated: 2025/12/08 09:11:33 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Converts RGB string components to a single integer color.
 * 
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
 * @brief Checks if a string represents a valid RGB component (0–255).
 * Skips leading and trailing whitespace, ensures the number is within 0–255,
 * and allows an optional comment after the number.
 * 
 * @param s String to validate.
 * @return 1 if valid, 0 otherwise.
 */
static int	is_valid_rgb_number(const char *s)
{
	long	number;

	while (*s == ' ' || *s == '\t')
		s++;
	if (!(*s >= '0' && *s <= '9'))
		return (0);
	number = 0;
	while (*s >= '0' && *s <= '9')
	{
		number = number * 10 + (*s - '0');
		if (number > 255)
			return (0);
		s++;
	}
	while (*s == ' ' || *s == '\t')
		s++;
	if (*s == '\0' || *s == '#')
		return (1);
	return (0);
}

/**
 * @brief Validates that the RGB components are correct.
 * 
 * @param split Array of strings representing RGB components.
 * @return int 1 if valid, 0 otherwise.
 */
static int	validate_rgb_components(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
		i++;
	if (i != 3)
		return (0);
	i = 0;
	while (i < 3)
	{
		if (!is_valid_rgb_number(split[i]))
			return (0);
		i++;
	}
	return (1);
}

/** 
 * @brief Counts the number of commas in a string.
 * 
 * @param line The input string.
 * @return int The number of commas found.
 */
static int	count_commas(char *line)
{
	int		count;
	char	*ptr;

	count = 0;
	ptr = line;
	while (*ptr && *ptr != '\n')
	{
		if (*ptr == ',')
			count++;
		ptr++;
	}
	return (count);
}

/**
 * @brief Parses an RGB color from a string in the format "R,G,B".
 * Validates the format and range of each component.
 * 
 * @param line The input string containing the RGB values.
 * @return int The combined RGB color as an integer, or -1 on error.
 */
int	parse_rgb(char *line)
{
	char	**split;
	int		result;

	if (count_commas(line) != 2)
		return (-1);
	split = ft_split(line, ',');
	if (split == NULL)
		return (-1);
	if (!validate_rgb_components(split))
	{
		free_split(split);
		return (-1);
	}
	result = convert_rgb(split[0], split[1], split[2]);
	free_split(split);
	return (result);
}
