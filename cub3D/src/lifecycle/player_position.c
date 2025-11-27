/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_position.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/27 09:42:21 by tiyang        #+#    #+#                 */
/*   Updated: 2025/11/27 09:51:58 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Checks if the current map cell contains the player start position.
 *        If found, sets the player's position and direction.
 * 
 * @param game The game structure containing the map and player info.
 * @param x The x-coordinate in the map.
 * @param y The y-coordinate in the map.
 * @return int 1 if player position is found and set, 0 otherwise.
 */
static int	check_player_position(t_game *game, int x, int y)
{
	if (ft_strchr("NSEW", game->map[y][x]))
	{
		game->posX = x + 0.5;
		game->posY = y + 0.5;
		set_player_direction(game, game->map[y][x]);
		game->map[y][x] = '0';
		return (1);
	}
	return (0);
}

/**
 * @brief Initializes the player's orientation and position based on the map.
 * 
 * @param game The game structure containing the map and player info.
 */
void	init_player_orientation(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (game->map[y][x])
		{
			if (check_player_position(game, x, y))
				return ;
			x++;
		}
		y++;
	}
}
