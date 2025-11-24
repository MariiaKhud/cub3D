/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:13:55 by tiyang            #+#    #+#             */
/*   Updated: 2025/11/24 13:43:18 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Flood fill algorithm to mark reachable exits.
 * @param map_copy A copy of the game map.
 * @param x The current x-coordinate.
 * @param y The current y-coordinate.
 * This function marks all reachable 'E' (exits), 'C' (collectibles),
 * and '0' (empty spaces) from the starting position (x, y)
 * by changing them to 'Y'.
 * It stops when it hits walls ('1') or already visited positions ('Y').
 */
static void	floodfill_exit(char **map_copy, int x, int y)
{
	if (map_copy[y][x] == '1' || map_copy[y][x] == 'Y')
		return ;
	if (map_copy[y][x] == 'C' || map_copy[y][x] == '0' ||
		map_copy[y][x] == 'E')
		map_copy[y][x] = 'Y';
	floodfill_exit(map_copy, x + 1, y);
	floodfill_exit(map_copy, x - 1, y);
	floodfill_exit(map_copy, x, y + 1);
	floodfill_exit(map_copy, x, y - 1);
}

/**
 * @brief Checks if a specific element is unreachable in the map copy.
 * 	
 * @param map_copy A copy of the game map.
 * @param element The character element to check for (e.g., 'C', 'E').
 * @param game Pointer to the game structure.
 * @return int Returns 1 if the element is unreachable, otherwise returns 0.
 */
static int	is_element_unreachable(char **map_copy, char element, t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (map_copy[y][x] == element)
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

/**
 * @brief Flood fill algorithm to mark reachable collectibles.
 * @param map_copy A copy of the game map.
 * @param x The current x-coordinate.
 * @param y The current y-coordinate.
 * This function marks all reachable 'C' (collectibles) and '0' (empty spaces)
 * from the starting position (x, y) by changing them to 'Y'.
 * It stops when it hits walls ('1') or already visited positions ('Y')
 * or the exit ('E').
 */
static void	floodfill_collectibles(char **map_copy, int x, int y)
{
	if (map_copy[y][x] == '1' || map_copy[y][x] == 'Y' ||
		map_copy[y][x] == 'E')
		return ;
	if (map_copy[y][x] == 'C' || map_copy[y][x] == '0')
		map_copy[y][x] = 'Y';
	floodfill_collectibles(map_copy, x + 1, y);
	floodfill_collectibles(map_copy, x - 1, y);
	floodfill_collectibles(map_copy, x, y + 1);
	floodfill_collectibles(map_copy, x, y - 1);
}

/**
 * @brief Sets the starting position of the player in the game structure.
 * @param game Pointer to the game structure.
 * 
 * This function searches the game map for the player's starting position
 * (denoted by 'P') and sets the player_x and player_y fields in the
 * 	game structure accordingly.
 * If the player position is not found, the function does nothing.
 * Assumes that the map is valid and contains exactly one player position.
 */
static void	set_player_start_pos(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

/**
 * @brief Validates if all collectibles and the exit are reachable
 *        from the player's position.
 * @param game Pointer to the game structure.
 * @return int Returns 1 if all collectibles and the exit are reachable,
 *         otherwise returns 0.
 * 
 * This function uses flood fill algorithms to check if the player can reach
 * all collectibles ('C') and the exit ('E') in the game map.
 * It creates copies of the map for each flood fill to avoid modifying the
 * original map.
 * If any collectibles or the exit are found to be unreachable, it returns 0.
 * Otherwise, it returns 1 indicating that all required elements are reachable.
 */
int	validate_path(t_game *game)
{
	char	**map_copy;

	if (game == NULL)
		return (0);
	set_player_start_pos(game);
	map_copy = copy_map(game);
	if (map_copy == NULL)
		return (0);
	floodfill_collectibles(map_copy, game->player_x, game->player_y);
	if (is_element_unreachable(map_copy, 'C', game))
		return (free_matrix(map_copy), 0);
	free_matrix(map_copy);
	map_copy = copy_map(game);
	if (map_copy == NULL)
		return (0);
	floodfill_exit(map_copy, game->player_x, game->player_y);
	if (is_element_unreachable(map_copy, 'E', game))
		return (free_matrix(map_copy), 0);
	free_matrix(map_copy);
	return (1);
}