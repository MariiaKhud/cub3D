/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_close.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/02 10:56:34 by tiyang        #+#    #+#                 */
/*   Updated: 2025/11/27 09:05:31 by tiyang        ########   odam.nl         */
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
 * @brief Destroys all loaded textures in the game.
 * 
 * @param game The game structure containing textures.
 */
static void	destroy_textures(t_game *game)
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
		game->mlx_ptr = NULL;
	}
	if (game->map)
		free_map(game->map);
	exit(exit_status);
}
