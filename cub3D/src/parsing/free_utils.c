/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 13:43:02 by makhudon          #+#    #+#             */
/*   Updated: 2025/12/02 09:26:29 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_texture(t_game *game, char *trimmed, char **target)
{
	if (*target)
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
	while (map && map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}

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

void	free_game(t_game *game)
{
	free_textures(game);
	free_map(game->map);
}
