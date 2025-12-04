/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   interact.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/03 09:30:51 by tiyang        #+#    #+#                 */
/*   Updated: 2025/12/04 12:52:03 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Interactions with the world (Doors).
 * Logic:
 * 1. Calculate the map coordinates 1 step in front of the player.
 * 2. Check if that cell is a Door ('D') or an Open Door ('O').
 * 3. Toggle the state.
 */
void	interact(t_game *game)
{
	int	target_x;
	int	target_y;

	target_x = (int)(game->pos_x + game->dir_x);
	target_y = (int)(game->pos_y + game->dir_y);
	if (target_x < 0 || target_x >= game->map_width || 
		target_y < 0 || target_y >= game->map_height)
		return ;
	if (game->map[target_y][target_x] == 'D')
		game->map[target_y][target_x] = 'O';
	else if (game->map[target_y][target_x] == 'O')
	{
		if ((int)game->pos_x != target_x || (int)game->pos_y != target_y)
			game->map[target_y][target_x] = 'D';
	}
}

/**
 * @brief Checks if a door at (x, y) is correctly surrounded by walls.
 * A valid door must be sandwiched between '1's 
 * either horizontally OR vertically.
 * * @param game The game structure.
 * @param x The x-coordinate of the door.
 * @param y The y-coordinate of the door.
 * @return int 1 if valid, 0 if invalid.
 */
int	is_door_enclosed(t_game *game, int x, int y)
{
	int	horizontal;
	int	vertical;

	horizontal = 0;
	vertical = 0;
	if (x > 0 && x < game->map_width - 1)
	{
		if (game->map[y][x - 1] == '1' && game->map[y][x + 1] == '1')
			horizontal = 1;
	}
	if (y > 0 && y < game->map_height - 1)
	{
		if (game->map[y - 1][x] == '1' && game->map[y + 1][x] == '1')
			vertical = 1;
	}
	return (horizontal || vertical);
}

/**
 * @brief Iterates through the map to validate all door placements.
 * * @param game The game structure.
 * @return int 1 if all doors are valid, 0 otherwise.
 */
int	validate_doors(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'D')
			{
				if (!is_door_enclosed(game, x, y))
				{
					ft_printf("Door at (%d, %d) is not inside a wall.\n", x, y);
					return (0);
				}
			}
			x++;
		}
		y++;
	}
	return (1);
}
