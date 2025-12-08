/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/01 10:39:59 by tiyang        #+#    #+#                 */
/*   Updated: 2025/12/08 08:58:30 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Calculates the minimap position for a sprite.
 * 
 * @param g The game structure.
 * @param i The index of the sprite.
 * @param mm_x Pointer to store the calculated minimap x-coordinate.
 * @param mm_y Pointer to store the calculated minimap y-coordinate.
 */
static void	calculate_sprite_position(t_game *g, int i, int *mm_x, int *mm_y)
{
	int	dx;
	int	dy;

	dx = (int)g->sprites[i].x - (int)g->pos_x;
	dy = (int)g->sprites[i].y - (int)g->pos_y;
	*mm_x = MM_OFFSET + (MM_VIEW_RANGE * MM_TILE_SIZE) + (dx * MM_TILE_SIZE);
	*mm_y = MM_OFFSET + (MM_VIEW_RANGE * MM_TILE_SIZE) + (dy * MM_TILE_SIZE);
}

/**
 * @brief Draws the sprites on the minimap within the view range.
 * 
 * @param g The game structure containing sprite and player info.
 */
void	draw_minimap_sprites(t_game *g)
{
	int	i;
	int	dx;
	int	dy;
	int	mm_x;
	int	mm_y;

	i = 0;
	while (i < g->sprite_count)
	{
		if (!g->sprites[i].alive)
		{
			i++;
			continue ;
		}
		dx = (int)g->sprites[i].x - (int)g->pos_x;
		dy = (int)g->sprites[i].y - (int)g->pos_y;
		if (abs(dx) <= MM_VIEW_RANGE && abs(dy) <= MM_VIEW_RANGE)
		{
			calculate_sprite_position(g, i, &mm_x, &mm_y);
			draw_mm_square(g, mm_x, mm_y, 0x00FF00);
		}
		i++;
	}
}

/** 
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

/**
 * @brief Draws the player (dot and direction vector) on the minimap.
 *
 * @param game The game structure containing the minimap image.
 * @param center_x The x-coordinate of the minimap center.
 * @param center_y The y-coordinate of the minimap center.
 */
static void	draw_player(t_game *game, int center_x, int center_y)
{
	int	i;
	int	j;
	int	coords[4];
	int	offset;

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
	offset = MM_PLAYER_OFFSET + MM_PLAYER_SIZE / 2;
	coords[0] = center_x + offset;
	coords[1] = center_y + offset;
	coords[2] = center_x + offset + (int)(game->dir_x * MM_DIR_LENGTH);
	coords[3] = center_y + offset + (int)(game->dir_y * MM_DIR_LENGTH);
	init_and_draw_line(game, coords, MM_COLOR_PLAYER);
}

/** 
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
	draw_minimap_sprites(game);
	draw_player(game, center_x, center_y);
}
