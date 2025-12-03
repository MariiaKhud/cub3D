/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 08:49:32 by makhudon          #+#    #+#             */
/*   Updated: 2025/12/03 11:59:12 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    check_sprite_pickup(t_game *game)
{
    int     i;
    double  dx;
    double  dy;
    double  dist;

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
 * @brief Checks if the player can move to the specified position
 *        without colliding with walls.
 * @param game The game structure.
 * @param new_y The new y-coordinate to check.
 * @param new_x The new x-coordinate to check.
 * @return int 1 if movement is possible, 0 if a collision would occur.
 */
static int	can_move(t_game *game, double new_y, double new_x)
{
	if (!is_valid_pos(game, new_x, new_y))
		return (0);
	if (!is_valid_pos(game, new_x - COLLISION_DIST, new_y - COLLISION_DIST))
		return (0);
	if (!is_valid_pos(game, new_x + COLLISION_DIST, new_y - COLLISION_DIST))
		return (0);
	if (!is_valid_pos(game, new_x - COLLISION_DIST, new_y + COLLISION_DIST))
		return (0);
	if (!is_valid_pos(game, new_x + COLLISION_DIST, new_y + COLLISION_DIST))
		return (0);
	return (1);
}

/**
 * @brief Moves the player to the right relative to their current direction.
 * @param game The game structure containing player position and direction.
 */
void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->pos_x - game->dir_y * MOVE_SPEED;
	new_y = game->pos_y + game->dir_x * MOVE_SPEED;
	if (can_move(game, game->pos_y, new_x))
		game->pos_x = new_x;
	if (can_move(game, new_y, game->pos_x))
		game->pos_y = new_y;
}

/**
 * @brief Moves the player to the left relative to their current direction.
 * @param game The game structure containing player position and direction.
 */
void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->pos_x + game->dir_y * MOVE_SPEED;
	new_y = game->pos_y - game->dir_x * MOVE_SPEED;
	if (can_move(game, game->pos_y, new_x))
		game->pos_x = new_x;
	if (can_move(game, new_y, game->pos_x))
		game->pos_y = new_y;
}

/**
 * @brief Moves the player backward opposite to the direction they are facing.
 * @param game The game structure containing player position and direction.
 */
void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->pos_x - game->dir_x * MOVE_SPEED;
	new_y = game->pos_y - game->dir_y * MOVE_SPEED;
	if (can_move(game, game->pos_y, new_x))
		game->pos_x = new_x;
	if (can_move(game, new_y, game->pos_x))
		game->pos_y = new_y;
}

/**
 * @brief Moves the player forward in the direction they are facing.
 * @param game The game structure containing player position and direction.
 */
void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->pos_x + game->dir_x * MOVE_SPEED;
	new_y = game->pos_y + game->dir_y * MOVE_SPEED;
	if (can_move(game, game->pos_y, new_x))
		game->pos_x = new_x;
	if (can_move(game, new_y, game->pos_x))
		game->pos_y = new_y;
}
