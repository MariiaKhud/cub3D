/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 13:33:40 by makhudon          #+#    #+#             */
/*   Updated: 2025/12/01 10:53:35 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Sets the ceiling color from a line,
 *        validating RGB and handling duplicates.
 * Skips spaces, removes comments, trims, parses RGB,
 * and updates the game structure.
 * 
 * @param game Pointer to the game structure.
 * @param val Line after the 'C' identifier.
 * @param has_ceiling Pointer to ceiling flag.
 * @return 1 on success, 0 on error.
 */
static int	set_ceiling_color(t_game *game, char *val, int *has_ceiling)
{
	char	*comment;
	int		color;

	if (*has_ceiling)
	{
		ft_printf("Error\nDuplicate ceiling color (C)\n");
		return (0);
	}
	val = skip_spaces(val);
	comment = ft_strchr(val, '#');
	if (comment)
		*comment = '\0';
	trim_trailing_whitespace(val);
	color = parse_rgb(val);
	if (color == -1)
	{
		ft_printf("Error\nInvalid ceiling color\n");
		return (0);
	}
	game->ceiling_color = color;
	*has_ceiling = 1;
	return (1);
}

/**
 * @brief Sets the floor color from a line,
 *        validating RGB and handling duplicates.
 * Skips spaces, removes comments, trims, parses RGB,
 * and updates the game structure.
 * 
 * @param game Pointer to the game structure.
 * @param val Line after the 'F' identifier.
 * @param has_floor Pointer to floor flag.
 * @return 1 on success, 0 on error.
 */
static int	set_floor_color(t_game *game, char *val, int *has_floor)
{
	char	*comment;
	int		color;

	if (*has_floor)
	{
		ft_printf("Error\nDuplicate floor color (F)\n");
		return (0);
	}
	val = skip_spaces(val);
	comment = ft_strchr(val, '#');
	if (comment)
		*comment = '\0';
	trim_trailing_whitespace(val);
	color = parse_rgb(val);
	if (color == -1)
	{
		ft_printf("Error\nInvalid floor color\n");
		return (0);
	}
	game->floor_color = color;
	*has_floor = 1;
	return (1);
}

/**
 * @brief Determines if a line defines a floor or ceiling color and sets it.
 * 
 * @param game Pointer to the game structure.
 * @param trimmed Line to parse.
 * @param has_floor Pointer to the floor flag.
 * @param has_ceiling Pointer to the ceiling flag.
 * @return 1 on success or ignored line, 0 on error.
 */
int	set_color(t_game *game, char *trimmed, int *has_floor, int *has_ceiling)
{
	if (trimmed[0] == 'F' && (trimmed[1] == ' ' || trimmed[1] == '\t'))
		return (set_floor_color(game, trimmed + 1, has_floor));
	if (trimmed[0] == 'C' && (trimmed[1] == ' ' || trimmed[1] == '\t'))
		return (set_ceiling_color(game, trimmed + 1, has_ceiling));
	return (1);
}

/**
 * @brief Checks if a string starts with a given 2-character
 * identifier followed by space or tab.
 * 
 * @param s String to check.
 * @param id2 2-character identifier to match.
 * @return 1 if `s` matches `id2` followed by a space or tab, 0 otherwise.
 */
int	is_id(const char *s, const char *id2)
{
	if (s[0] != id2[0] || s[1] != id2[1])
		return (0);
	if (s[2] != ' ' && s[2] != '\t')
		return (0);
	return (1);
}

/**
 * @brief Sets the file path for a texture based on its identifier.
 * Determines which texture (NO, SO, WE, EA) the line defines, extracts the 
 * file path, trims trailing whitespace, and stores it in the game structure.
 * 
 * @param game Pointer to the game structure to update.
 * @param trimmed Line containing the texture identifier and path.
 */
void	set_texture(t_game *game, char *trimmed)
{
	char	*path_start;
	char	**target;
	int		len;

	target = NULL;
	len = 0;
	if (is_id(trimmed, "NO"))
		target = &game->no_texture;
	else if (is_id(trimmed, "SO"))
		target = &game->so_texture;
	else if (is_id(trimmed, "WE"))
		target = &game->we_texture;
	else if (is_id(trimmed, "EA"))
		target = &game->ea_texture;
	if (target == NULL)
		return ;
	path_start = skip_spaces(trimmed + 2);
	while (path_start[len] && path_start[len] != '\n'
		&& path_start[len] != '#')
		len++;
	free(*target);
	*target = ft_substr(path_start, 0, len);
	if (*target)
		trim_trailing_whitespace(*target);
}
