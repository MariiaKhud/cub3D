/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_close_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 09:31:11 by makhudon          #+#    #+#             */
/*   Updated: 2025/12/08 09:35:36 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Frees the texture path strings in the game structure.
 * 
 * @param game The game structure.
 */
void	destroy_texture_path_strings(t_game *game)
{
	if (game->no_texture != NULL)
	{
		free(game->no_texture);
		game->no_texture = NULL;
	}
	if (game->so_texture != NULL)
	{
		free(game->so_texture);
		game->so_texture = NULL;
	}
	if (game->we_texture != NULL)
	{
		free(game->we_texture);
		game->we_texture = NULL;
	}
	if (game->ea_texture != NULL)
	{
		free(game->ea_texture);
		game->ea_texture = NULL;
	}
}

/**
 * @brief Destroys all loaded player animation textures in the game.
 * 
 * @param game The game structure.
 */
void	destroy_player_sprites(t_game *game)
{
	int	i;

	i = 0;
	while (i < PLAYER_FRAMES)
	{
		if (game->player_anim[i].img_ptr != NULL)
		{
			mlx_destroy_image(game->mlx_ptr, game->player_anim[i].img_ptr);
			game->player_anim[i].img_ptr = NULL;
		}
		i++;
	}
}

/**
 * @brief Destroys all loaded player animation textures in the game.
 * 
 * @param game The game structure.
 */
void	destroy_player_textures(t_game *game)
{
	if (game->player_anim[0].img_ptr != NULL)
	{
		mlx_destroy_image(game->mlx_ptr, game->player_anim[0].img_ptr);
		game->player_anim[0].img_ptr = NULL;
	}
	if (game->player_anim[1].img_ptr != NULL)
	{
		mlx_destroy_image(game->mlx_ptr, game->player_anim[1].img_ptr);
		game->player_anim[1].img_ptr = NULL;
	}
}
