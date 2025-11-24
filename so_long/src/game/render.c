/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/30 14:00:28 by tiyang        #+#    #+#                 */
/*   Updated: 2025/11/24 10:20:12 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

// gets pixel color from an image's pixel data.
// declares a char pointer to store the memory address of the pixel.
// has a bound check for safety: if the requested coordinate is outside of 
// the image's bounds, returns an error color (0x00000000).
// calculates the address of the pixel, cast it into (unsigned int *) 
// in order to read the full 32-bit color value.
// dereferences the casted pointer to read the value stored at
// the memory address, which represents the color, and returns it.
unsigned int	get_pixel_color(t_img *img, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);
	pixel = img->addr + (y * img->line_length + x * (img->bpp / 8));
	return (*(unsigned int *)pixel);
}

// helper function that takes in pixel coordinates 
// and calculates the address of the pixel.
// if the pixel coordinates is out of bounds, returns NULL,
// otherwise returns an address in the form of (unsigned int *)
unsigned int	*get_pixel_address(t_game *game, int pixel_x, int pixel_y)
{
	char	*target_pixel_addr;

	if (pixel_x >= 0 && pixel_y >= 0
		&& pixel_x < (game->map_width * TILE_SIZE)
		&& pixel_y < (game->map_height * TILE_SIZE))
	{
		target_pixel_addr = game->img.addr
			+ (pixel_y * game->img.line_length
				+ pixel_x * (game->img.bpp / 8));
		return ((unsigned int *)target_pixel_addr);
	}
	else
		return (NULL);
}

// custom function to draw a sprite with transparency 
// onto the main drawing image (game->img.img_ptr).
// takes in as parameters the tile coordinates of the tile
// where we want to draw the sprites.
// checks against a "magic color" that represents transparency in the xmp files,
// if a pixel is not that color, draw it on to the canvas.
// this allows the image underneath to show through the "transparent" pixels.
void	draw_sprite(t_game *game, t_img *sprite, int tile_x, int tile_y)
{
	int				col;
	int				row;
	int				target_pixel_x;
	int				target_pixel_y;
	unsigned int	*target_pixel_addr;

	row = 0;
	while (row < sprite->height)
	{
		col = 0;
		while (col < sprite->width)
		{
			if (get_pixel_color(sprite, col, row) != TRANSPARENT_COLOR)
			{
				target_pixel_x = tile_x * TILE_SIZE + col;
				target_pixel_y = tile_y * TILE_SIZE + row;
				target_pixel_addr = get_pixel_address(game, target_pixel_x,
						target_pixel_y);
				if (target_pixel_addr)
					*target_pixel_addr = get_pixel_color(sprite, col, row);
			}
			col++;
		}
		row++;
	}
}

void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == '1')
				draw_sprite(game, &game->wall_sprite, x, y);
			else
				draw_sprite(game, &game->floor_sprite, x, y);
			if (game->map[y][x] == 'C')
				draw_sprite(game, &game->collectible_sprite, x, y);
			else if (game->map[y][x] == 'E')
				draw_sprite(game, &game->exit_sprite, x, y);
			x++;
		}
		y++;
	}
	draw_sprite(game, &game->current_player_sprite, game->player_x,
		game->player_y);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->img.img_ptr, 0, 0);
}
