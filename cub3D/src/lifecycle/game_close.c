/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:56:34 by tiyang            #+#    #+#             */
/*   Updated: 2025/12/02 12:37:10 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Destroys all loaded player animation textures in the game.
 * 
 * @param game The game structure.
 */
static void	destroy_player_textures(t_game *game)
{
	if (game->player_anim[0].img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->player_anim[0].img_ptr);
		game->player_anim[0].img_ptr = NULL;
	}
	if (game->player_anim[1].img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->player_anim[1].img_ptr);
		game->player_anim[1].img_ptr = NULL;
	}
}

/**
 * @brief Destroys all loaded wall and sky textures in the game.
 * 
 * @param game The game structure.
 */
static void	destroy_wall_and_sky_textures(t_game *game)
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
	if (game->tex_sky.img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->tex_sky.img_ptr);
		game->tex_sky.img_ptr = NULL;
	}
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
}

/**
 * @brief Frees the texture path strings in the game structure.
 * 
 * @param game The game structure.
 */
static void	destroy_texture_path_strings(t_game *game)
{
	if (game->no_texture)
	{
		free(game->no_texture);
		game->no_texture = NULL;
	}
	if (game->so_texture)
	{
		free(game->so_texture);
		game->so_texture = NULL;
	}
	if (game->we_texture)
	{
		free(game->we_texture);
		game->we_texture = NULL;
	}
	if (game->ea_texture)
	{
		free(game->ea_texture);
		game->ea_texture = NULL;
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
	ft_printf("\n--- Closing Game ---\n");
	if (game->img.img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->img.img_ptr);
		game->img.img_ptr = NULL;
	}
	destroy_textures(game);
	if (game->win_ptr)
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		game->win_ptr = NULL;
	}
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		game->mlx_ptr = NULL;
	}
	destroy_texture_path_strings(game);
	if (game->map)
		free_map(game->map);
	exit(exit_status);
}
