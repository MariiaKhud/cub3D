/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_close.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/02 10:56:34 by tiyang        #+#    #+#                 */
/*   Updated: 2025/12/08 12:31:28 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Destroys the extra textures (sky and sprite) in the game.
 * 
 * @param game The game structure.
 */
static void	destroy_extra_textures(t_game *game)
{
	if (game->tex_sky.img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->tex_sky.img_ptr);
		game->tex_sky.img_ptr = NULL;
	}
	if (game->tex_sprite.img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->tex_sprite.img_ptr);
		game->tex_sprite.img_ptr = NULL;
	}
}

/**
 * @brief Destroys the basic wall textures in the game.
 * 
 * @param game The game structure.
 */
static void	destroy_basic_textures(t_game *game)
{
	if (game->tex_no.img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->tex_no.img_ptr);
		game->tex_no.img_ptr = NULL;
	}
	if (game->tex_so.img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->tex_so.img_ptr);
		game->tex_so.img_ptr = NULL;
	}
	if (game->tex_we.img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->tex_we.img_ptr);
		game->tex_we.img_ptr = NULL;
	}
	if (game->tex_ea.img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->tex_ea.img_ptr);
		game->tex_ea.img_ptr = NULL;
	}
}

/**
 * @brief Destroys all wall and sky textures in the game.
 * 
 * @param game The game structure.
 */
void	destroy_wall_and_sky_textures(t_game *game)
{
	destroy_basic_textures(game);
	destroy_extra_textures(game);
}

/**
 * @brief Destroys all loaded textures in the game.
 * 
 * @param game The game structure.
 */
static void	destroy_textures(t_game *game)
{
	destroy_wall_and_sky_textures(game);
	destroy_player_textures(game);
	if (game->tex_door.img_ptr != NULL)
	{
		mlx_destroy_image(game->mlx_ptr, game->tex_door.img_ptr);
		game->tex_door.img_ptr = NULL;
	}
}

/**
 * @brief Closes the game, frees resources, and exits.
 * 
 * @param game The game structure.
 * @param exit_status The exit status code.
 */
void	close_game(t_game *game, int exit_status)
{
	if (exit_status == EXIT_SUCCESS)
		ft_printf("--- Closing Game ---\n");
	if (game->img.img_ptr != NULL)
	{
		mlx_destroy_image(game->mlx_ptr, game->img.img_ptr);
		game->img.img_ptr = NULL;
	}
	destroy_textures(game);
	destroy_player_sprites(game);
	if (game->win_ptr != NULL)
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		game->win_ptr = NULL;
	}
	if (game->mlx_ptr != NULL)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		game->mlx_ptr = NULL;
	}
	destroy_texture_path_strings(game);
	if (game->map != NULL)
		free_map(game->map);
	exit(exit_status);
}
