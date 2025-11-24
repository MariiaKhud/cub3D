/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:14:05 by tiyang            #+#    #+#             */
/*   Updated: 2025/11/24 10:48:11 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// checks if each character in the map is part of the set of valid characters
// returns 1 if true
int	has_valid_char(char **map)
{
	int	i;
	int	j;

	if (!map)
		return (0);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_strchr("01CEP\n", map[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

// checks if the map is surrounded by walls, returns 1 if true
// checks if the first and last rows are filled with '1's 
// and if the first and last character in each row are '1'
int	check_walls(t_game *game)
{
	int	i;
	int	last_row_index;
	int	last_col_index;

	if (!game)
		return (0);
	if (game->map_height < 3 || game->map_width < 3)
		return (0);
	i = 0;
	last_row_index = game->map_height - 1;
	while (game->map[0][i] && game->map[last_row_index][i])
	{
		if (game->map[0][i] != '1' || game->map[last_row_index][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	last_col_index = game->map_width - 1;
	while (i < game->map_height)
	{
		if (game->map[i][0] != '1' || game->map[i][last_col_index] != '1')
			return (0);
		i++;
	}
	return (1);
}

// checks how many times a specific element has shown up in the map
// and returns the count.
int	check_element_count(t_game *game, char element)
{
	int	element_count;
	int	i;
	int	j;

	if (!game)
		return (0);
	i = 0;
	element_count = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == element)
				element_count++;
			j++;
		}
		i++;
	}
	return (element_count);
}

// uses two flood fills to check if player can reach all collectibles and
// the exit and in that specific order. Returns 1 if true.
// uses two malloc'd copied maps for each flood fill, frees them after use.
int	validate_path(t_game *game)
{
	char	**map_copy;

	if (!game)
		return (0);
	set_starting_position(game);
	map_copy = copy_map(game);
	if (!map_copy)
		return (0);
	floodfill_collectibles(map_copy, game->player_x, game->player_y);
	if (is_element_unreachable(map_copy, 'C', game))
		return (free_matrix(map_copy), 0);
	free_matrix(map_copy);
	map_copy = copy_map(game);
	if (!map_copy)
		return (0);
	floodfill_exit(map_copy, game->player_x, game->player_y);
	if (is_element_unreachable(map_copy, 'E', game))
		return (free_matrix(map_copy), 0);
	free_matrix(map_copy);
	return (1);
}

// validate if the map meets all requirements.
// returns 1 if true.
int	validate_map(t_game *game)
{
	int	player;
	int	exit;
	int	collectibles;

	if (!game || !is_rectangular(game->map, game->map_height)
		|| !has_valid_char(game->map) || !check_walls(game))
		return (free_matrix(game->map), 0);
	player = check_element_count(game, 'P');
	exit = check_element_count(game, 'E');
	collectibles = check_element_count(game, 'C');
	if (player != 1 || exit != 1 || collectibles < 1)
		return (free_matrix(game->map), 0);
	if (!validate_path(game))
		return (free_matrix(game->map), 0);
	game->total_collectibles = collectibles;
	game->collectibles_collected = 0;
	game->moves = 0;
	return (1);
}
