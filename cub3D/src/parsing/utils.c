/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:29:46 by tiyang            #+#    #+#             */
/*   Updated: 2025/12/08 09:18:17 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Checks if a line contains a map identifier after the map has started.
 * 
 * Prints an error if an identifier appears after the map has started.
 * 
 * @param game Pointer to the game structure.
 * @param trimmed Line trimmed of leading spaces.
 * @param line Original line to free in case of error.
 * @return 1 if invalid order detected, 0 otherwise.
 */
int	check_invalid_identifier_order(t_game *game, char *trimmed,
															char *line)
{
	if (game->map_start == 1 && (!ft_strncmp(trimmed, "NO ", 3)
			|| !ft_strncmp(trimmed, "SO ", 3) || !ft_strncmp(trimmed, "WE ", 3)
			|| !ft_strncmp(trimmed, "EA ", 3) || !ft_strncmp(trimmed, "F ", 2)
			|| !ft_strncmp(trimmed, "C ", 2)))
	{
		free(line);
		ft_printf("Error\nInvalid identifier order\n");
		return (1);
	}
	return (0);
}

/**
 * @brief Checks if a texture path is valid.
 * A valid path must be non-empty and must not
 * contain quotes, spaces, or tabs.
 * 
 * @param path Texture path to validate.
 * @return 1 if valid, 0 otherwise.
 */

static int	is_valid_texture_path(char *path)
{
	int	i;

	if (!path || *path == '\0')
		return (0);
	i = 0;
	while (path[i])
	{
		if (path[i] == '"')
			return (0);
		if (path[i] == ' ' || path[i] == '\t')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Validates all texture paths in the game structure.
 * 
 * Checks if each of the four textures has a valid path. Prints an error
 * if any path is invalid.
 * 
 * @param game Pointer to the game structure.
 * @return 1 if any texture path is invalid, 0 if all are valid.
 */
int	validate_textures(t_game *game)
{
	if (!is_valid_texture_path(game->no_texture)
		|| !is_valid_texture_path(game->so_texture)
		|| !is_valid_texture_path(game->we_texture)
		|| !is_valid_texture_path(game->ea_texture))
	{
		ft_printf("Error\nInvalid texture path\n");
		return (1);
	}
	return (0);
}

/**
 * @brief Creates a copy of the game map.
 * 
 * Allocates memory for a new 2D array and copies the contents
 * of the game's map into it.
 * 
 * @param game Pointer to the game structure.
 * @return char** Pointer to the copied map, or NULL on failure.
 */
char	**copy_map(t_game *game)
{
	char	**map_copy;
	int		y;
	int		width;

	width = game->map_width;
	map_copy = malloc(sizeof(char *) * (game->map_height + 1));
	if (map_copy == NULL)
		return (NULL);
	y = 0;
	while (y < game->map_height)
	{
		map_copy[y] = malloc(width + 1);
		if (map_copy[y] == NULL)
		{
			while (--y >= 0)
				free(map_copy[y]);
			return (free(map_copy), NULL);
		}
		ft_memset(map_copy[y], ' ', width);
		ft_memcpy(map_copy[y], game->map[y], ft_strlen(game->map[y]));
		map_copy[y][width] = '\0';
		y++;
	}
	map_copy[y] = NULL;
	return (map_copy);
}

/**
 * @brief Calculates the length of a string excluding the trailing newline.
 * 
 * @param line The input string.
 * @return int The length of the string without the newline.
 */
int	ft_strlen_without_newline(char *line)
{
	int	len;

	if (line == NULL)
		return (0);
	len = (int)ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		return (len - 1);
	return (len);
}
