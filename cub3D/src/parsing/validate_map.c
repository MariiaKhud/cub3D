/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:14:05 by tiyang            #+#    #+#             */
/*   Updated: 2025/11/24 13:30:13 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Counts the occurrences of a specific element in the game map.
 * @param game Pointer to the game structure.
 * @param element The character element to count (e.g., 'P', 'E', 'C').
 * @return int The count of the specified element in the map.
 */
static int	check_element_count(t_game *game, char element)
{
	int	element_count;
	int	i;
	int	j;

	if (game == NULL)
		return (0);
	i = 0;
	element_count = 0;
	while (game->map[i] != NULL)
	{
		j = 0;
		while (game->map[i][j] != '\0')
		{
			if (game->map[i][j] == element)
				element_count++;
			j++;
		}
		i++;
	}
	return (element_count);
}

/**
 * @brief Checks if the map is surrounded by walls, returns 1 if true.
 * Checks if the first and last rows are filled with '1's
 * and if the first and last character in each row are '1'.
 * 	
 * @param game Pointer to the game structure containing the map.
 * @return int Returns 1 if the map is properly walled, otherwise returns 0.
 */
static int	is_surrounded_by_wall(t_game *game)
{
	int	i;
	int	last_row_index;
	int	last_col_index;

	if (game == NULL)
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

/**
 * @brief Checks if the map contains only valid characters.
 * Valid characters are '0', '1', 'C', 'E', 'P', and '\n'.
 * @param map The 2D character array representing the map.
 * @return int Returns 1 if all characters are valid, otherwise returns 0.
 */
static int	is_all_chars_valid(char **map)
{
	int	i;
	int	j;

	if (map == NULL)
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

/**
 * @brief Checks if the map is rectangular.
 * @param map The 2D character array representing the map.
 * @param line_count The number of lines in the map.
 * @return int Returns 1 if the map is rectangular, otherwise returns 0.
 */
static int	is_rectangular(char **map, int line_count)
{
	int	init_length;
	int	i;
	int	line_length;

	if (map == NULL || map[0] == NULL || line_count <= 0)
		return (0);
	if (line_count == 1)
		return (1);
	init_length = ft_strlen_without_newline(map[0]);
	i = 1;
	while (i < line_count)
	{
		line_length = ft_strlen_without_newline(map[i]);
		if (line_length != init_length)
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Validates the game map for correctness.
 * This function checks if the map is rectangular,
 * contains only valid characters, is surrounded by walls,
 * has the correct number of essential elements (player, exit, collectibles),
 * and ensures that all collectibles and the exit are reachable from the
 * player's starting position.
 * @param game Pointer to the game structure containing the map.
 * @return int Returns 1 if the map is valid, otherwise returns 0.
 */
int	validate_map(t_game *game)
{
	int	player;
	int	exit;
	int	collectibles;

	if (!game || !is_rectangular(game->map, game->map_height)
		|| !is_all_chars_valid(game->map) || !is_surrounded_by_wall(game))
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
