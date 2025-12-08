/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_sprites.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/03 09:12:23 by makhudon      #+#    #+#                 */
/*   Updated: 2025/12/08 09:24:29 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Adds a sprite at the given map coordinates.
 * 
 * @param game The game structure.
 * @param x The x-coordinate on the map.
 * @param y The y-coordinate on the map.
 */
static void	add_sprite(t_game *game, int x, int y)
{
	if (game->sprite_count >= MAX_SPRITES)
		return ;
	game->sprites[game->sprite_count].x = x + 0.5;
	game->sprites[game->sprite_count].y = y + 0.5;
	game->sprites[game->sprite_count].tex_id = 0;
	game->sprites[game->sprite_count].alive = 1;
	game->sprite_count++;
}

/**
 * @brief Scans the game map for sprites ('2') 
 * and adds them to the sprite array.
 * 
 * @param game The game structure containing the map and sprite info.
 */
void	find_sprites_in_map(t_game *game)
{
	int	y;
	int	x;

	game->sprite_count = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == '2')
			{
				add_sprite(game, x, y);
				game->map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}

/**
 * @brief Sorts sprites based on their distance from the player.
 * Uses a simple bubble sort for demonstration purposes.
 * 
 * @param g The game structure containing sprite and player info.
 * @param order An array of sprite indices to be sorted.
 * @param dist An array of squared distances from the player.
 */
void	sort_sprites(t_game *g, int *order, double *dist)
{
	int		i;
	int		j;
	int		tmp_i;
	double	tmp_d;

	i = 0;
	while (i < g->sprite_count - 1)
	{
		j = 0;
		while (j < g->sprite_count - 1 - i)
		{
			if (dist[j] < dist[j + 1])
			{
				tmp_d = dist[j];
				dist[j] = dist[j + 1];
				dist[j + 1] = tmp_d;
				tmp_i = order[j];
				order[j] = order[j + 1];
				order[j + 1] = tmp_i;
			}
			j++;
		}
		i++;
	}
}

/**
 * @brief Initializes sprite order and distance arrays.
 * 
 * @param g The game structure containing sprite and player info.
 * @param order An array to hold the sprite indices.
 * @param dist An array to hold the squared distances from the player.
 */
void	init_sprite_arrays(t_game *g, int *order, double *dist)
{
	int		i;
	double	dx;
	double	dy;

	i = 0;
	while (i < g->sprite_count)
	{
		order[i] = i;
		dx = g->sprites[i].x - g->pos_x;
		dy = g->sprites[i].y - g->pos_y;
		dist[i] = dx * dx + dy * dy;
		i++;
	}
}
