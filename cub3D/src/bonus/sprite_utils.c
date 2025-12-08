/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/08 00:00:00 by tiyang        #+#    #+#                 */
/*   Updated: 2025/12/08 09:35:48 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Calculates the sprite's on-screen dimensions and position.
 * 
 * @param sr Pointer to the sprite rendering structure to populate.
 * @param trans_x The transformed x position of the sprite.
 * @param trans_y The transformed y position of the sprite.
 */
void	calc_sprite_dims(t_sprite_render *sr,
				double trans_x, double trans_y)
{
	sr->screen_x = (int)((WIDTH / 2) * (1 + trans_x / trans_y));
	sr->height = abs((int)(HEIGHT / trans_y));
	sr->start_y = -sr->height / 2 + HEIGHT / 2;
	if (sr->start_y < 0)
		sr->start_y = 0;
	sr->end_y = sr->height / 2 + HEIGHT / 2;
	if (sr->end_y >= HEIGHT)
		sr->end_y = HEIGHT - 1;
	sr->width = sr->height;
	sr->start_x = -sr->width / 2 + sr->screen_x;
	if (sr->start_x < 0)
		sr->start_x = 0;
	sr->end_x = sr->width / 2 + sr->screen_x;
	if (sr->end_x >= WIDTH)
		sr->end_x = WIDTH - 1;
}

/**
 * @brief Calculates the sprite's position relative to the player.
 * 
 * @param g The game structure containing player info.
 * @param idx The index of the sprite in the sprite array.
 * @param sx Pointer to store the sprite's x position relative to the player.
 * @param sy Pointer to store the sprite's y position relative to the player.
 */
void	calc_sprite_pos(t_game *g, int idx, double *sx, double *sy)
{
	*sx = g->sprites[idx].x - g->pos_x;
	*sy = g->sprites[idx].y - g->pos_y;
}
