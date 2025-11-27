/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_init.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/27 09:42:21 by tiyang        #+#    #+#                 */
/*   Updated: 2025/11/27 09:52:41 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Sets the player's direction and camera plane for facing North.
 * 
 * @param game The game structure containing player info.
 */
void	set_direction_north(t_game *game)
{
	game->dir_x = 0;
	game->dir_y = -1;
	game->plane_x = 0.66;
	game->plane_y = 0;
}

/**
 * @brief Sets the player's direction and camera plane for facing South.
 * 
 * @param game The game structure containing player info.
 */
void	set_direction_south(t_game *game)
{
	game->dir_x = 0;
	game->dir_y = 1;
	game->plane_x = -0.66;
	game->plane_y = 0;
}

/**
 * @brief Sets the player's direction and camera plane for facing East.
 * 
 * @param game The game structure containing player info.
 */
void	set_direction_east(t_game *game)
{
	game->dir_x = 1;
	game->dir_y = 0;
	game->plane_x = 0;
	game->plane_y = 0.66;
}

/**
 * @brief Sets the player's direction and camera plane for facing West.
 * 
 * @param game The game structure containing player info.
 */
void	set_direction_west(t_game *game)
{
	game->dir_x = -1;
	game->dir_y = 0;
	game->plane_x = 0;
	game->plane_y = -0.66;
}

/**
 * @brief Sets the player's direction based on the given character.
 * 
 * @param game The game structure containing player info.
 * @param direction The character representing the direction ('N','S','E','W').
 */
void	set_player_direction(t_game *game, char direction)
{
	if (direction == 'N')
		set_direction_north(game);
	else if (direction == 'S')
		set_direction_south(game);
	else if (direction == 'E')
		set_direction_east(game);
	else if (direction == 'W')
		set_direction_west(game);
}
