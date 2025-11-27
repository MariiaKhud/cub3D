/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/27 09:13:32 by tiyang        #+#    #+#                 */
/*   Updated: 2025/11/27 10:20:57 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* 
 * @brief Puts a pixel of a specific color at (x, y) in the game's image.
 * 
 * @param game The game structure containing the image.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The color of the pixel in 0xAARRGGBB format.
 */
static void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
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
static unsigned int	get_texture_pixel(t_img *tex, int x, int y)
{
	char	*dst;

	if (!tex->addr)
		return (0xFFFFFF);
	dst = tex->addr + (y * tex->line_length + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

/**
 * @brief Renders the background by filling the top half with ceiling color
 *        and the bottom half with floor color.
 * 
 * @param game The game structure containing the image and colors.
 */
void	render_background(t_game *game)
{
	unsigned int	*dst;
	int				i;
	int				total_pixels;

	dst = (unsigned int *)game->img.addr;
	total_pixels = WIDTH * HEIGHT;
	i = 0;
	while (i < total_pixels / 2)
	{
		dst[i] = game->ceiling_color;
		i++;
	}
	while (i < total_pixels)
	{
		dst[i] = game->floor_color;
		i++;
	}
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
