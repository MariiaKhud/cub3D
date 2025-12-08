/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_init.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/26 10:15:14 by makhudon      #+#    #+#                 */
/*   Updated: 2025/12/08 09:56:43 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Handles the window close event.
 * 
 * @param game The game structure.
 * @return int Always returns 0.
 */
int	handle_close(t_game *game)
{
	close_game(game, EXIT_SUCCESS);
	return (0);
}

/**
 * @brief Loads a single texture from an XPM file into
 *        the given t_img structure.
 * 
 * @param game The game structure containing the MLX pointer.
 * @param tex The t_img structure to load the texture into.
 * @param path The file path to the XPM texture.
 * @return int 1 on success, 0 on failure.
 */
static int	load_one_texture(t_game *game, t_img *tex, char *path)
{
	tex->img_ptr = mlx_xpm_file_to_image(
			game->mlx_ptr, path, &tex->width, &tex->height);
	if (tex->img_ptr == NULL)
		return (0);
	tex->addr = mlx_get_data_addr(
			tex->img_ptr, &tex->bpp, &tex->line_length, &tex->endian);
	return (1);
}

/**
 * @brief Loads all wall textures and the sky texture.
 * 
 * @param game The game structure containing texture paths.
 * @return int 1 on success, 0 on failure.
 */
static int	load_textures(t_game *game)
{
	if (!load_one_texture(game, &game->tex_no, game->no_texture))
		return (0);
	if (!load_one_texture(game, &game->tex_so, game->so_texture))
		return (0);
	if (!load_one_texture(game, &game->tex_we, game->we_texture))
		return (0);
	if (!load_one_texture(game, &game->tex_ea, game->ea_texture))
		return (0);
	if (!load_one_texture(game, &game->tex_sky, "./textures/sky.xpm"))
		return (0);
	if (!load_one_texture(game, &game->tex_door, "./textures/door.xpm"))
		return (0);
	if (!load_one_texture(game, &game->tex_sprite, "./textures/ball.xpm"))
		return (0);
	return (1);
}

/** 
 * @brief Registers MLX event hooks for keypress, window close,
 *        and mouse movement events.
 * 
 * @param game The game structure containing MLX and window pointers.
 */
void	register_mlx_hooks(t_game *game)
{
	mlx_hook(game->win_ptr, MLX_KEY_PRESS, (1L << 0),
		handle_keypress, game);
	mlx_hook(game->win_ptr, MLX_DESTROY_NOTIFY, 0L,
		handle_close, game);
	mlx_hook(game->win_ptr, MLX_MOTION_NOTIFY, (1L << 6),
		handle_mouse, game);
	mlx_mouse_move(game->mlx_ptr, game->win_ptr, WIDTH / 2, HEIGHT / 2);
}

/** 
 * @brief Initializes the game: MLX, window, textures,
 *        raycasting, and event hooks.
 * 
 * @param game The game structure to initialize.
 */
void	load_game(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (game->mlx_ptr == NULL)
		close_game(game, EXIT_FAILURE);
	if (!load_textures(game))
	{
		ft_printf("Error\nFailed to load textures\n");
		close_game(game, EXIT_FAILURE);
	}
	load_player_sprites(game);
	game->win_ptr = mlx_new_window(game->mlx_ptr,
			WIDTH, HEIGHT, "cub3D");
	if (game->win_ptr == NULL)
		close_game(game, EXIT_FAILURE);
	game->img.img_ptr = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img_ptr, &game->img.bpp,
			&game->img.line_length, &game->img.endian);
	game->mouse_locked = 1;
	mlx_mouse_hide(game->mlx_ptr, game->win_ptr);
}
