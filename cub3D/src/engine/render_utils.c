/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:19:24 by makhudon          #+#    #+#             */
/*   Updated: 2025/12/03 09:11:25 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Clamps a texture coordinate to be within valid bounds.
 * 
 * @param value The texture coordinate value.
 * @param limit The maximum limit (width or height) of the texture.
 * @return int The clamped texture coordinate.
 */
int	clamp_tex(int value, int limit)
{
	if (value < 0)
		return (0);
	if (value >= limit)
		return (limit - 1);
	return (value);
}

/** 
 * @brief Puts a pixel of a specific color at (x, y) in the game's image.
 * 
 * @param game The game structure containing the image.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The color of the pixel in 0xAARRGGBB format.
 */
void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = game->img.addr + (y * game->img.line_length
			+ x * (game->img.bpp / 8));
	*(unsigned int *)dst = color;
}

/**
 * @brief Retrieves the color of a pixel from a texture at (x, y).
 * 
 * @param tex The texture image.
 * @param x The x-coordinate of the pixel in the texture.
 * @param y The y-coordinate of the pixel in the texture.
 * @return unsigned int The color of the pixel in 0xAARRGGBB format.
 */
unsigned int	get_texture_pixel(t_img *tex, int x, int y)
{
	char	*dst;

	if (tex->addr == NULL)
		return (0xFFFFFF);
	dst = tex->addr + (y * tex->line_length + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

/** 
 * @brief Draws a vertical textured line on the screen.
 * 
 * @param game The game structure containing the image.
 * @param data The drawing data including texture info and line parameters.
 */
static void	calculate_tex_y(t_draw_data *data, int *tex_y, int *color)
{
	int	d;

	d = data->y * 256 - HEIGHT * 128 + data->line_height * 128;
	*tex_y = ((d * data->tex->height) / data->line_height) / 256;
	if (*tex_y < 0)
		*tex_y = 0;
	if (*tex_y >= data->tex->height)
		*tex_y = data->tex->height - 1;
	*color = get_texture_pixel(data->tex, data->tex_x, *tex_y);
}

/**
 * @brief Draws a vertical line on the screen with texture mapping.
 * 
 * @param game The game structure containing the image.
 * @param data The drawing data including texture info and line parameters.
 */
void	draw_vertical_line(t_game *game, t_draw_data *data)
{
	int	tex_y;
	int	color;

	data->y = data->draw_start;
	while (data->y < data->draw_end)
	{
		calculate_tex_y(data, &tex_y, &color);
		if ((color & 0xFF000000) == 0)
			my_mlx_pixel_put(game, data->x, data->y, color);
		data->y++;
	}
}
