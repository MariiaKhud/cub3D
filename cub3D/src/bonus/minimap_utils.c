/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/01 10:39:59 by tiyang        #+#    #+#                 */
/*   Updated: 2025/12/08 13:26:21 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Determines the color of a minimap tile based on map content.
 * 
 * @param game The game structure containing the map.
 * @param map_x The x-coordinate in the map.
 * @param map_y The y-coordinate in the map.
 * @return int The color to use for the tile.
 */
int	get_tile_color(t_game *game, int map_x, int map_y)
{
	char	tile;

	if (map_y < 0 || map_y >= game->map_height)
		return (MM_COLOR_BLACK);
	if (map_x < 0 || map_x >= (int)ft_strlen(game->map[map_y]))
		return (MM_COLOR_BLACK);
	tile = game->map[map_y][map_x];
	if (tile == '1')
		return (MM_COLOR_WALL);
	if (tile == 'D')
		return (MM_COLOR_DOOR_CLOSED);
	if (tile == 'O')
		return (MM_COLOR_DOOR_OPEN);
	if (tile == ' ' || tile == '\0')
		return (MM_COLOR_BLACK);
	return (MM_COLOR_FLOOR);
}

/** 
 * @brief Draws a square tile on the minimap at (x, y) with the given color.
 * 
 * @param game The game structure containing the minimap image.
 * @param x The top-left x-coordinate of the tile.
 * @param y The top-left y-coordinate of the tile.
 * @param color The color to fill the tile.
 */
void	draw_mm_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MM_TILE_SIZE)
	{
		j = 0;
		while (j < MM_TILE_SIZE)
		{
			my_mlx_pixel_put(game, x + j, y + i, color);
			j++;
		}
		i++;
	}
}
