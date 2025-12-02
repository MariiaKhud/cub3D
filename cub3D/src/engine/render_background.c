/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:17:37 by makhudon          #+#    #+#             */
/*   Updated: 2025/12/02 10:29:01 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/** 
 * @brief Renders the floor with a solid color.
 * 
 * @param game The game structure containing the floor color.
 */
static void	render_floor(t_game *game)
{
	int				y;
	int				x;
	int				idx;
	unsigned int	*dst;

	dst = (unsigned int *)game->img.addr;
	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			idx = y * WIDTH + x;
			dst[idx] = game->floor_color;
			x++;
		}
		y++;
	}
}

/** 
 * @brief Renders the background sky using a solid color.
 * 
 * @param game The game structure containing the ceiling color.
 * @param dst The destination pixel array of the game's image.
 */
static void	render_background_sky_color(t_game *game, unsigned int *dst)
{
	int	i;

	i = 0;
	while (i < (WIDTH * HEIGHT) / 2)
	{
		dst[i] = game->ceiling_color;
		i++;
	}
}

/**
 * @brief Renders the sky texture onto the upper half of the screen.
 * 
 * @param game The game structure containing the sky texture.
 * @param dst The destination pixel array of the game's image.
 * @param x The x-coordinate on the screen.
 * @param y The y-coordinate on the screen.
 */
static void	render_sky(t_game *game,
				unsigned int *dst, int x, int y)
{
	int				sky_x;
	int				sky_y;
	int				index;
	unsigned int	color;

	sky_x = (int)((double)x / (double)WIDTH
			* (double)game->tex_sky.width);
	sky_y = (int)((double)y / ((double)HEIGHT / 2.0)
			* (double)game->tex_sky.height);
	sky_x = clamp_tex(sky_x, game->tex_sky.width);
	sky_y = clamp_tex(sky_y, game->tex_sky.height);
	color = get_texture_pixel(&game->tex_sky, sky_x, sky_y);
	index = y * WIDTH + x;
	dst[index] = color;
}

/**
 * @brief Renders the background sky using either a texture
 *        or a solid color.
 * 
 * @param game The game structure containing the sky texture or color.
 * @param dst The destination pixel array of the game's image.
 */
static void	render_background_sky_tex(t_game *game, unsigned int *dst)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			render_sky(game, dst, x, y);
			x++;
		}
		y++;
	}
}

/** 
 * @brief Renders the background (sky and floor) of the scene.
 * 
 * @param game The game structure containing colors and textures.
 */
void	render_background(t_game *game)
{
	unsigned int	*dst;

	dst = (unsigned int *)game->img.addr;
	if (game->tex_sky.img_ptr != NULL)
		render_background_sky_tex(game, dst);
	else
		render_background_sky_color(game, dst);
	render_floor(game);
}
