/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 12:38:02 by makhudon          #+#    #+#             */
/*   Updated: 2025/11/27 09:28:03 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Rotates the player's direction and camera plane to the left.
 * @param game The game structure containing player direction and plane.
 */
static void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->dirX;
	old_plane_x = game->planeX;
	game->dirX = game->dirX * cos(-ROT_SPEED) - game->dirY * sin(-ROT_SPEED);
	game->dirY = old_dir_x * sin(-ROT_SPEED) + game->dirY * cos(-ROT_SPEED);
	game->planeX = game->planeX * cos(-ROT_SPEED)
		- game->planeY * sin(-ROT_SPEED);
	game->planeY = old_plane_x * sin(-ROT_SPEED)
		+ game->planeY * cos(-ROT_SPEED);
}

/**
 * @brief Rotates the player's direction and camera plane to the right.
 * @param game The game structure containing player direction and plane.
 */
static void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->dirX;
	old_plane_x = game->planeX;
	game->dirX = game->dirX * cos(ROT_SPEED) - game->dirY * sin(ROT_SPEED);
	game->dirY = old_dir_x * sin(ROT_SPEED) + game->dirY * cos(ROT_SPEED);
	game->planeX = game->planeX * cos(ROT_SPEED)
		- game->planeY * sin(ROT_SPEED);
	game->planeY = old_plane_x * sin(ROT_SPEED) + game->planeY * cos(ROT_SPEED);
}

/**
 * @brief Handles key press events and triggers corresponding actions.
 * @param key The key code of the pressed key.
 * @param game The game structure containing player state.
 * @return int Always returns 0.
 */
int	handle_keypress(int key, t_game *game)
{
	if (key == KEY_ESC)
		close_game(game, EXIT_SUCCESS);
	else if (key == KEY_W)
		move_forward(game);
	else if (key == KEY_S)
		move_backward(game);
	else if (key == KEY_A)
		move_left(game);
	else if (key == KEY_D)
		move_right(game);
	else if (key == KEY_LEFT)
		rotate_left(game);
	else if (key == KEY_RIGHT)
		rotate_right(game);
	return (0);
}
