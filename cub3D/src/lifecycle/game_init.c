/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_init.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/30 15:38:24 by tiyang        #+#    #+#                 */
/*   Updated: 2025/11/24 11:11:37 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Helper function for loading and getting data address
void	load_xpm_sprite(t_game *game, t_img *sprite_struct, const char *path)
{
	int	tmp_width;
	int	tmp_height;

	sprite_struct->img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, (char *)path,
			&tmp_width, &tmp_height);
	if (!sprite_struct->img_ptr)
	{
		ft_printf("Error\nFailed to load sprite from %s\n", path);
		close_game(game, EXIT_FAILURE);
	}
	sprite_struct->addr = mlx_get_data_addr(sprite_struct->img_ptr,
			&sprite_struct->bpp,
			&sprite_struct->line_length,
			&sprite_struct->endian);
	sprite_struct->width = tmp_width;
	sprite_struct->height = tmp_height;
}

void	load_sprites(t_game *game)
{
	load_xpm_sprite(game, &game->player_down_sprite,
		"textures/player_down.xpm");
	load_xpm_sprite(game, &game->player_up_sprite,
		"textures/player_up.xpm");
	load_xpm_sprite(game, &game->player_left_sprite,
		"textures/player_left.xpm");
	load_xpm_sprite(game, &game->player_right_sprite,
		"textures/player_right.xpm");
	game->current_player_sprite = game->player_down_sprite;
	load_xpm_sprite(game, &game->floor_sprite,
		"textures/floor.xpm");
	load_xpm_sprite(game, &game->wall_sprite,
		"textures/wall.xpm");
	load_xpm_sprite(game, &game->collectible_sprite,
		"textures/collectible.xpm");
	load_xpm_sprite(game, &game->exit_sprite,
		"textures/exit.xpm");
}

void	create_image_buffer(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
	{
		ft_printf("Error\nFailed to initialise MLX\n");
		close_game(game, EXIT_FAILURE);
	}
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->map_width * TILE_SIZE,
			game->map_height * TILE_SIZE, "so_long");
	if (!game->win_ptr)
	{
		ft_printf("Error\nFailed to create display window\n");
		close_game(game, EXIT_FAILURE);
	}
	game->img.img_ptr = mlx_new_image(game->mlx_ptr,
			game->map_width * TILE_SIZE, game->map_height * TILE_SIZE);
	if (!game->img.img_ptr)
	{
		ft_printf("Error\nFailed to create image buffer\n");
		close_game(game, EXIT_FAILURE);
	}
	game->img.addr = mlx_get_data_addr(game->img.img_ptr,
			&game->img.bpp, &game->img.line_length, &game->img.endian);
}

// registers event hooks. See further notes below.
void	register_mlx_hooks(t_game *game)
{
	// NEED TO CREATE NEW FUNCTIONS TO HANDLE USER INPUT EVENTS
	// mlx_hook(game->win_ptr, MLX_KEY_PRESS, (1L << 0),
	// 	handle_keypress, game);
	mlx_hook(game->win_ptr, MLX_DESTROY_NOTIFY, MLX_NO_EVENT_MASK,
		handle_close, game);
}

// starts the game. See further notes below regarding the workflow.
// in case of any errors in the process of loading game, 
// the helper function where the error is encountered 
// will free up game resources, 
// terminate the entire program and print the corresponding error message.
void	load_game(t_game *game)
{
	create_image_buffer(game);
	load_sprites(game);
	// render_map(game);  // NEED NEW FUNCTION TO RENDER MAP
	register_mlx_hooks(game);
}

/* NOTES ON LOAD_GAME WORKFLOW
1. mlx_init() - Initialize MiniLibX
	This function initializes the connection 
	to the graphical display system.
	It returns a void pointer (mlx_ptr) 
	which is like a handle to this connection.
	If it fails (e.g., no display server), 
	it returns NULL. Always check for NULL.
2. mlx_new_window() - Create a Window
	Creates a new window on the screen.
		- mlx_ptr: The pointer returned by mlx_init().
		- size_x: The width of the window in pixels.
		- size_y: The height of the window in pixels.
		- title: A string that will appear in the window's title bar.
	It returns a void pointer (win_ptr) to the newly created window.
	Returns NULL on failure.
3. mlx_new_image() - Create an Image in Memory (The Drawing Canvas)
	Allocates memory for an image that you can draw pixels to.
	This image is *not* visible yet; it's just a buffer in RAM.
		- mlx_ptr: The pointer from mlx_init().
		- width: The width of the image in pixels.
		- height: The height of the image in pixels.
	Returns a void pointer (img_ptr) to the image.
	Returns NULL on failure.
4. mlx_get_data_addr() - Get Pointer to Image Pixel Data
	Provides direct access to the raw pixel data of an MLX image.
	Need this function to draw pixels directly.
		- img_ptr: The pointer returned by mlx_new_image().
		- bits_per_pixel: A pointer to an int where MLX will store 
		the number of bits per pixel (e.g., 32 for RGBA).
		- line_length: A pointer to an int where MLX will store 
		the number of bytes for one full row of pixels.
		This is crucial for moving to the next row (y-coordinate).
		- endian: A pointer to an int where MLX will store 
		the endianness (byte order, 0 or 1).
	Returns a `char *` pointer to the first byte of the pixel data.
5. load_sprites() - loading xpm images into the game
6. render_map() - draw the current state of the game 
7. register_mlx_hooks() - centralised function to register all event hooks.
	1) Key Press Event (User presses a key)
	Event code 2: KeyPress (defined in X11/X.h)
	Event mask (1L << 0): KeyPressMask (tells X server to send key press events)
	handle_keypress: function to handle what happens when a key is pressed
	2) Window Close Event (User clicks the 'X' button on the window)
	Event code 17: DestroyNotify (defined in X11/X.h)
	Event mask 0L: NoEventMask
	handle_close: function to handle cleanup and exit when the window is closed
*/