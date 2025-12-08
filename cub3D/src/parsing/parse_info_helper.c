/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 08:56:53 by makhudon          #+#    #+#             */
/*   Updated: 2025/12/08 09:15:08 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Checks if all necessary textures and colors have been set.
 * 
 * @param game Pointer to the game structure.
 * @param has_floor Flag indicating if floor color is set.
 * @param has_ceiling Flag indicating if ceiling color is set.
 * @return int 1 if all identifiers are set, 0 otherwise.
 */
int	all_identifiers_set(t_game *game,
							int has_floor, int has_ceiling)
{
	if (!game->no_texture || !game->so_texture
		|| !game->we_texture || !game->ea_texture)
		return (0);
	if (!has_floor || !has_ceiling)
		return (0);
	return (1);
}

/**
 * @brief Trim trailing '\n' and spaces from a string (in-place).
 * 
 * @param s The string to trim.
 */
void	trim_trailing_whitespace(char *s)
{
	int	len;

	if (s == NULL)
		return ;
	len = (int)ft_strlen(s);
	while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == ' '
			|| s[len - 1] == '\t'))
	{
		s[len - 1] = '\0';
		len--;
	}
}

/** 
 * @brief Checks if a line starts with the given identifier.
 * 
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
 * 
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
