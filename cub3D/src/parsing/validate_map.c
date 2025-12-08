/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 12:08:49 by makhudon          #+#    #+#             */
/*   Updated: 2025/12/08 12:01:50 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Flood fill algorithm to check if the map is closed.
 * 
 * @param game The game structure containing the map.
 * @param map A copy of the game map to modify during flood fill.
 * @param y Current Y position.
 * @param x Current X position.
 * @return int 1 if the area is closed, 0 if it reaches the edge
 * 			  of the map (not closed).
 */
static int	floodfill_closed(t_game *game, char **map, int y, int x)
{
	if (y < 0 || y >= game->map_height || x < 0 || x >= game->map_width)
		return (0);
	if (map[y][x] == ' ' || map[y][x] == '\0')
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (1);
	map[y][x] = 'V';
	if (!floodfill_closed(game, map, y - 1, x))
		return (0);
	if (!floodfill_closed(game, map, y + 1, x))
		return (0);
	if (!floodfill_closed(game, map, y, x - 1))
		return (0);
	if (!floodfill_closed(game, map, y, x + 1))
		return (0);
	return (1);
}

/**
 * @brief Finds the player's position in the map.
 * 
 * @param game The game structure containing the map.
 * @param pos_y Pointer to store the player's Y position.
 * @param pos_x Pointer to store the player's X position.
 * @return int 1 if exactly one player found, 0 otherwise.
 */
static int	find_player_pos(t_game *game, int *pos_y, int *pos_x)
{
	int	y;
	int	x;
	int	count;

	y = 0;
	count = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width && game->map[y][x] != '\0')
		{
			if (ft_strchr("NSEW", game->map[y][x]))
			{
				*pos_y = y;
				*pos_x = x;
				count++;
			}
			x++;
		}
		y++;
	}
	if (count != 1)
		return (0);
	return (1);
}

/**
 * @brief Counts occurrences of a specific element in the game map.
 * 
 * @param game The game structure containing the map.
 * @param element The character element to count.
 * @return int The count of the specified element in the map.
 */
static int	check_element_count(t_game *game, char element)
{
	int	element_count;
	int	y;
	int	x;

	element_count = 0;
	y = 0;
	if (game == NULL)
		return (0);
	while (game->map[y] != NULL)
	{
		x = 0;
		while (game->map[y][x] != '\0')
		{
			if (game->map[y][x] == element)
				element_count++;
			x++;
		}
		y++;
	}
	return (element_count);
}

/**
 * @brief Checks if all characters in the map are valid.
 * 
 * Valid characters are '0', '1', 'N', 'S', 'E', 'W', ' ', and tabs.
 * 
 * @param map The game map to check.
 * @return int 1 if all characters are valid, 0 otherwise.
 */
static int	is_all_chars_valid(char **map)
{
	int	y;
	int	x;

	y = 0;
	if (map == NULL)
		return (0);
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (!ft_strchr("01NSEW2 DO", map[y][x]))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

/**
 * @brief Validates the game map.
 * 
 * Checks for valid characters, exactly one player,
 * and that the map is closed using flood fill.
 * 
 * @param game The game structure containing the map.
 * @return int 1 if the map is valid, 0 otherwise.
 */
int	validate_map(t_game *game)
{
	int		player_y;
	int		player_x;
	char	**map_copy;
	int		is_closed;

	if (game == NULL || game->map == NULL)
		return (0);
	if (!is_all_chars_valid(game->map))
		return (0);
	if (has_open_on_border(game))
		return (0);
	if ((check_element_count(game, 'N') + check_element_count(game, 'S')
			+ check_element_count(game, 'E')
			+ check_element_count(game, 'W')) != 1)
		return (0);
	if (!find_player_pos(game, &player_y, &player_x))
		return (0);
	if (!validate_doors(game))
		return (0);
	map_copy = copy_map(game);
	if (map_copy == NULL)
		return (0);
	is_closed = floodfill_closed(game, map_copy, player_y, player_x);
	free_map(map_copy);
	if (is_closed == 0)
		return (0);
	return (1);
}
