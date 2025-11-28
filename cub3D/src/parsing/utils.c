/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:29:46 by tiyang            #+#    #+#             */
/*   Updated: 2025/11/28 09:14:27 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Frees all dynamically allocated memory in the game structure.
 * @param game The game structure to free.
 */
void	free_game(t_game *game)
{
	int	i;
	
	if (game->no_texture) free(game->no_texture);
	if (game->so_texture) free(game->so_texture);
	if (game->we_texture) free(game->we_texture);
	if (game->ea_texture) free(game->ea_texture);
	if (game->map != NULL)
	{
		i = 0;
		while (game->map[i] != NULL)
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
	}
}

/**
 * @brief Frees a dynamically allocated array of strings.
 * @param split The array of strings to free.
 */
void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split == NULL)
		return ;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/**
 * @brief Frees a dynamically allocated 2D array (matrix) of strings.
 * @param matrix The 2D array to free.
 */
void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}

/**
 * @brief Creates a deep copy of the game map.
 * @param game The game structure containing the map.
 * @return char** A newly allocated copy of the map,
 *         or NULL on failure.
 */
char	**copy_map(t_game *game)
{
	char	**map_copy;
	int		y;

	y = 0;
	map_copy = malloc(sizeof(char *) * (game->map_height + 1));
	if (map_copy == NULL)
		return (NULL);
	while (y < game->map_height)
	{
		map_copy[y] = ft_strdup(game->map[y]);
		if (map_copy[y] == NULL)
		{
			while (y > 0)
				free(map_copy[--y]);
			free(map_copy);
			return (NULL);
		}
		y++;
	}
	map_copy[y] = NULL;
	return (map_copy);
}

/**
 * @brief Calculates the length of a string excluding the trailing newline.
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
