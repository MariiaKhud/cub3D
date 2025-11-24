/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 10:56:34 by tiyang            #+#    #+#             */
/*   Updated: 2025/11/24 10:50:56 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// wrapper function for close_game() in order to register it with mlx_hook()
// which expects the callback function to have a specific signature
int	handle_close(t_game *game)
{
	close_game(game, EXIT_SUCCESS);
	return (0);
}

void	close_game(t_game *game, int exit_status)
{
	ft_printf("\n--- Closing Game ---\n");
	if (game->img.img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->img.img_ptr);
		game->img.img_ptr = NULL;
	}
	destroy_player_sprites(game);
	destroy_environment(game);
	destroy_objects(game);
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
		free_matrix(game->map);
	exit(exit_status);
}

// destroys player sprites
void	destroy_player_sprites(t_game *game)
{
	if (game->player_down_sprite.img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->player_down_sprite.img_ptr);
		game->player_down_sprite.img_ptr = NULL;
	}
	if (game->player_up_sprite.img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->player_up_sprite.img_ptr);
		game->player_up_sprite.img_ptr = NULL;
	}
	if (game->player_left_sprite.img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->player_left_sprite.img_ptr);
		game->player_left_sprite.img_ptr = NULL;
	}
	if (game->player_right_sprite.img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->player_right_sprite.img_ptr);
		game->player_right_sprite.img_ptr = NULL;
	}
}

// destroys collectibles and exit
void	destroy_objects(t_game *game)
{
	if (game->collectible_sprite.img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->collectible_sprite.img_ptr);
		game->collectible_sprite.img_ptr = NULL;
	}
	if (game->exit_sprite.img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->exit_sprite.img_ptr);
		game->exit_sprite.img_ptr = NULL;
	}
}

// destroys walls and floor
void	destroy_environment(t_game *game)
{
	if (game->floor_sprite.img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->floor_sprite.img_ptr);
		game->floor_sprite.img_ptr = NULL;
	}
	if (game->wall_sprite.img_ptr)
	{
		mlx_destroy_image(game->mlx_ptr, game->wall_sprite.img_ptr);
		game->wall_sprite.img_ptr = NULL;
	}
}
