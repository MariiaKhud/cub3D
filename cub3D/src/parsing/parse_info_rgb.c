/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info_rgb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 13:04:34 by makhudon          #+#    #+#             */
/*   Updated: 2025/12/02 09:57:03 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/** 
 * @brief Checks if a line starts with the given identifier.
 * @param line The line to check.
 * @param id The identifier to look for (e.g., "NO", "SO").
 * @return int 1 if the line starts with the identifier, 0 otherwise.
 */
int	process_texture_id(t_game *game, char *trimmed)
{
	if (is_id(trimmed, "NO"))
		return (handle_texture(game, trimmed, &game->no_texture));
	if (is_id(trimmed, "SO"))
		return (handle_texture(game, trimmed, &game->so_texture));
	if (is_id(trimmed, "WE"))
		return (handle_texture(game, trimmed, &game->we_texture));
	if (is_id(trimmed, "EA"))
		return (handle_texture(game, trimmed, &game->ea_texture));
	return (-1);
}

/** 
 * @brief Skips leading spaces and tabs in a string.
 * @param s The string to process.
 * @return char* Pointer to the first non-space character.
 */
char	*skip_spaces(char *s)
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
 * @brief Parses an RGB color from a string in the format "R,G,B".
 * @param line The string containing the RGB values.
 * @return int The combined RGB color as an integer,
 *         or -1 on error.
 */
int	parse_rgb(char *line)
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
