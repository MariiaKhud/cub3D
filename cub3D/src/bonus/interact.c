/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   interact.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/03 09:30:51 by tiyang        #+#    #+#                 */
/*   Updated: 2025/12/03 09:31:15 by tiyang        ########   odam.nl         */
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
