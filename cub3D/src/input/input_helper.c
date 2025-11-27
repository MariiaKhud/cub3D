/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 08:49:32 by makhudon          #+#    #+#             */
/*   Updated: 2025/11/27 09:46:13 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Checks if the player can move to the specified position.
 * @param game The game structure containing the map.
 * @param new_y The new Y position to check.
 * @param new_x The new X position to check.
 * @return int 1 if the player can move to the position, 0 otherwise.
 */
static int	can_move(t_game *game, double new_y, double new_x)
{
	int	x;
	int	y;
	int	row_len;

	y = (int)new_y;
	x = (int)new_x;
	if (y < 0 || y >= game->map_height)
		return (0);
	row_len = (int)ft_strlen(game->map[y]);
	if (x < 0 || x >= row_len)
		return (0);
	if (game->map[y][x] == '1' || game->map[y][x] == ' ')
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

	new_x = game->posX - game->dirY * MOVE_SPEED;
	new_y = game->posY + game->dirX * MOVE_SPEED;
	if (can_move(game, game->posY, new_x))
		game->posX = new_x;
	if (can_move(game, new_y, game->posX))
		game->posY = new_y;
}

/**
 * @brief Moves the player to the left relative to their current direction.
 * @param game The game structure containing player position and direction.
 */
void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->posX + game->dirY * MOVE_SPEED;
	new_y = game->posY - game->dirX * MOVE_SPEED;
	if (can_move(game, game->posY, new_x))
		game->posX = new_x;
	if (can_move(game, new_y, game->posX))
		game->posY = new_y;
}

/**
 * @brief Moves the player backward opposite to the direction they are facing.
 * @param game The game structure containing player position and direction.
 */
void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->posX - game->dirX * MOVE_SPEED;
	new_y = game->posY - game->dirY * MOVE_SPEED;
	if (can_move(game, game->posY, new_x))
		game->posX = new_x;
	if (can_move(game, new_y, game->posX))
		game->posY = new_y;
}

/**
 * @brief Moves the player forward in the direction they are facing.
 * @param game The game structure containing player position and direction.
 */
void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->posX + game->dirX * MOVE_SPEED;
	new_y = game->posY + game->dirY * MOVE_SPEED;
	if (can_move(game, game->posY, new_x))
		game->posX = new_x;
	if (can_move(game, new_y, game->posX))
		game->posY = new_y;
}
