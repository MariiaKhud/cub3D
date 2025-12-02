/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 13:43:02 by makhudon          #+#    #+#             */
/*   Updated: 2025/12/02 13:40:28 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Handles setting a texture path,
 *        checking for duplicates.
 * 
 * @param game Pointer to the game structure.
 * @param trimmed The line trimmed of leading spaces.
 * @param target Pointer to the texture path to set.
 * @return 1 on success, 0 on error.
 */
int	handle_texture(t_game *game, char *trimmed, char **target)
{
	if (*target != NULL)
	{
		ft_printf("Error\nDuplicate texture identifier\n");
		return (0);
	}
	set_texture(game, trimmed);
	return (1);
}

/**
 * @brief Frees a dynamically allocated array of strings.
 * 
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
 * 
 * @param map The 2D array to free.
 */
void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map && map[i] != NULL)
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}

/**
 * @brief Frees the texture path strings in the game structure.
 * 
 * @param game The game structure.
 */
static void	free_textures(t_game *game)
{
	if (game->no_texture)
		free(game->no_texture);
	if (game->so_texture)
		free(game->so_texture);
	if (game->we_texture)
		free(game->we_texture);
	if (game->ea_texture)
		free(game->ea_texture);
}

/** 
 * @brief Frees all dynamically allocated resources in the game structure.
 * 
 * @param game The game structure to free.
 */
void	free_game(t_game *game)
{
	free_textures(game);
	free_map(game->map);
}
