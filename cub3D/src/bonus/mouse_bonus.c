/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/01 11:20:49 by tiyang        #+#    #+#                 */
/*   Updated: 2025/12/01 13:31:11 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Handles mouse motion events to rotate the player.
 * * Logic:
 * 1. Calculate delta_x (current mouse X - screen center).
 * 2. If delta_x is 0, do nothing (avoids infinite loops from reset).
 * 3. Calculate rotation speed/angle based on delta_x.
 * 4. Apply rotation matrix to dir and plane vectors.
 * 5. Reset mouse cursor to center of screen.
 * * @param x The current x-coordinate of the mouse.
 * @param y The current y-coordinate of the mouse (unused).
 * @param game The game structure.
 * @return int Always returns 0.
 */
int	handle_mouse(int x, int y, t_game *game)
{
	int		delta_x;
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;

	(void)y;
	if (!game->mouse_locked)
		return (0);
	delta_x = x - (WIDTH / 2);
	if (delta_x == 0)
		return (0);
	rot_speed = delta_x * MOUSE_SENSITIVITY;
	old_dir_x = game->dir_x;
	game->dir_x = game->dir_x * cos(rot_speed)
		- game->dir_y * sin(rot_speed);
	game->dir_y = old_dir_x * sin(rot_speed)
		+ game->dir_y * cos(rot_speed);
	old_plane_x = game->plane_x;
	game->plane_x = game->plane_x * cos(rot_speed)
		- game->plane_y * sin(rot_speed);
	game->plane_y = old_plane_x * sin(rot_speed)
		+ game->plane_y * cos(rot_speed);
	mlx_mouse_move(game->mlx_ptr, game->win_ptr, WIDTH / 2, HEIGHT / 2);
	return (0);
}
