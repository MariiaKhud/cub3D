/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 12:38:02 by makhudon          #+#    #+#             */
/*   Updated: 2025/12/08 09:39:12 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Checks if the player is close enough to any sprite
 *        to pick it up, and marks it as not alive if so.
 * @param game The game structure containing player and sprite info.
 */
void	check_sprite_pickup(t_game *game)
{
	int		i;
	double	dx;
	double	dy;
	double	dist;

	i = 0;
	while (i < game->sprite_count)
	{
		if (game->sprites[i].alive)
		{
			dx = game->pos_x - game->sprites[i].x;
			dy = game->pos_y - game->sprites[i].y;
			dist = sqrt(dx * dx + dy * dy);
			if (dist < 0.4)
				game->sprites[i].alive = 0;
		}
		i++;
	}
}

/**
 * @brief Rotates the player's direction and camera plane to the left.
 * @param game The game structure containing player direction and plane.
 */
static void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->dir_x;
	old_plane_x = game->plane_x;
	game->dir_x = game->dir_x * cos(-ROT_SPEED) - game->dir_y * sin(-ROT_SPEED);
	game->dir_y = old_dir_x * sin(-ROT_SPEED) + game->dir_y * cos(-ROT_SPEED);
	game->plane_x = game->plane_x * cos(-ROT_SPEED)
		- game->plane_y * sin(-ROT_SPEED);
	game->plane_y = old_plane_x * sin(-ROT_SPEED)
		+ game->plane_y * cos(-ROT_SPEED);
}

/**
 * @brief Rotates the player's direction and camera plane to the right.
 * @param game The game structure containing player direction and plane.
 */
static void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->dir_x;
	old_plane_x = game->plane_x;
	game->dir_x = game->dir_x * cos(ROT_SPEED) - game->dir_y * sin(ROT_SPEED);
	game->dir_y = old_dir_x * sin(ROT_SPEED) + game->dir_y * cos(ROT_SPEED);
	game->plane_x = game->plane_x * cos(ROT_SPEED)
		- game->plane_y * sin(ROT_SPEED);
	game->plane_y = old_plane_x * sin(ROT_SPEED)
		+ game->plane_y * cos(ROT_SPEED);
}

/** 
 * @brief Toggles the mouse state between locked and unlocked.
 * @param game The game structure containing mouse state and MLX pointers.
 */
static void	toggle_mouse_state(t_game *game)
{
	if (game->mouse_locked)
	{
		game->mouse_locked = 0;
		mlx_mouse_show(game->mlx_ptr, game->win_ptr);
	}
	else
	{
		game->mouse_locked = 1;
		mlx_mouse_hide(game->mlx_ptr, game->win_ptr);
		mlx_mouse_move(game->mlx_ptr, game->win_ptr, WIDTH / 2, HEIGHT / 2);
	}
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
	else if (key == KEY_M)
		toggle_mouse_state(game);
	else if (key == KEY_E)
		interact(game);
	return (0);
}
