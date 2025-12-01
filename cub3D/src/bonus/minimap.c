/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/01 10:39:59 by tiyang        #+#    #+#                 */
/*   Updated: 2025/12/01 13:26:04 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* 
 * @brief Draws the minimap centered around the player's position.
 * 
 * @param game The game structure containing the map and player info.
 */
static void	draw_map_tiles(t_game *game)
{
	int	x;
	int	y;
	int	screen_x;
	int	screen_y;

	y = -MM_VIEW_RANGE;
	while (y <= MM_VIEW_RANGE)
	{
		x = -MM_VIEW_RANGE;
		while (x <= MM_VIEW_RANGE)
		{
			screen_x = MM_OFFSET + (x + MM_VIEW_RANGE) * MM_TILE_SIZE;
			screen_y = MM_OFFSET + (y + MM_VIEW_RANGE) * MM_TILE_SIZE;
			draw_mm_square(game, screen_x, screen_y,
				get_tile_color(game, (int)game->pos_x + x,
					(int)game->pos_y + y));
			x++;
		}
		y++;
	}
}

/* 
 * @brief Draws the player's position as a dot on the minimap.
 * 
 * @param game The game structure containing the minimap image.
 * @param center_x The x-coordinate of the minimap center.
 * @param center_y The y-coordinate of the minimap center.
 */
static void	draw_player_dot(t_game *game, int center_x, int center_y)
{
	int	i;
	int	j;

	i = 0;
	while (i < MM_PLAYER_SIZE)
	{
		j = 0;
		while (j < MM_PLAYER_SIZE)
		{
			mm_pixel_put(game, center_x + MM_PLAYER_OFFSET + j,
				center_y + MM_PLAYER_OFFSET + i, MM_COLOR_PLAYER);
			j++;
		}
		i++;
	}
}

/* 
 * @brief Draws the player's direction vector on the minimap.
 * 
 * @param game The game structure containing the minimap image.
 * @param center_x The x-coordinate of the minimap center.
 * @param center_y The y-coordinate of the minimap center.
 */
static void	draw_direction_vector(t_game *game, int center_x, int center_y)
{
	int	coords[4];
	int	offset;

	offset = MM_PLAYER_OFFSET + MM_PLAYER_SIZE / 2;
	coords[0] = center_x + offset;
	coords[1] = center_y + offset;
	coords[2] = center_x + offset + (int)(game->dir_x * MM_DIR_LENGTH);
	coords[3] = center_y + offset + (int)(game->dir_y * MM_DIR_LENGTH);
	init_and_draw_line(game, coords, MM_COLOR_PLAYER);
}

/* 
 * @brief Renders the minimap on the game screen.
 * 
 * @param game The game structure containing the map and player info.
 */
void	render_minimap(t_game *game)
{
	int	center_x;
	int	center_y;

	draw_map_tiles(game);
	center_x = MM_OFFSET + MM_VIEW_RANGE * MM_TILE_SIZE;
	center_y = MM_OFFSET + MM_VIEW_RANGE * MM_TILE_SIZE;
	draw_player_dot(game, center_x, center_y);
	draw_direction_vector(game, center_x, center_y);
}
