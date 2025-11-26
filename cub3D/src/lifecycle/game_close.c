// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   game_close.c                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/07/02 10:56:34 by tiyang            #+#    #+#             */
// /*   Updated: 2025/11/25 12:14:16 by makhudon         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../includes/cub3d.h"

// wrapper for mlx_hook
int	handle_close(t_game *game)
{
	close_game(game, EXIT_SUCCESS);
	return (0);
}

void	close_game(t_game *game, int exit_status)
{
	ft_printf("\n--- Closing Game ---\n");

	// destroy main image buffer
	if (game->img.img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->img.img_ptr);
		game->img.img_ptr = NULL;
	}
	// destroy wall textures
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
	// destroy window
	if (game->win_ptr)
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		game->win_ptr = NULL;
	}
	// destroy MLX display
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		game->mlx_ptr = NULL;
	}
	// free map memory
	if (game->map)
		free_map(game->map);
	exit(exit_status);
}
