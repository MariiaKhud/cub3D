/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:40:37 by makhudon          #+#    #+#             */
/*   Updated: 2025/12/03 12:33:50 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Local helper to put a pixel on the main game image.
 * Duplicated here because the engine version is static.
 */
static void	anim_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = game->img.addr + (y * game->img.line_length
			+ x * (game->img.bpp / 8));
	*(unsigned int *)dst = color;
}

/**
 * @brief Draws the current player sprite at the center-bottom of the window.
 * * LOGIC:
 * 1. Calculate the starting screen coordinates (center bottom).
 * 2. Iterate through every pixel of the sprite texture.
 * 3. Retrieve the color of the sprite pixel using get_texture_pixel.
 * 4. IF the color is NOT Magenta, draw it to the game image.
 */
void	draw_player_sprite(t_game *game)
{
	t_img	*sprite;
	int		x;
	int		y;
	int		screen_x;
	int		screen_y;

	sprite = &game->player_anim[game->anim_index];
	if (sprite->img_ptr == NULL)
		return ;
	screen_x = (WIDTH - sprite->width) / 2;
	screen_y = HEIGHT - sprite->height - 10;
	y = 0;
	while (y < sprite->height)
	{
		x = 0;
		while (x < sprite->width)
		{
			if ((get_texture_pixel(sprite, x, y) & 0x00FFFFFF)
				!= TRANSPARENT_COLOR)
				anim_pixel_put(game, screen_x + x, screen_y + y,
					get_texture_pixel(sprite, x, y));
			x++;
		}
		y++;
	}
}

/**
 * @brief Updates the animation frame for the player sprite.
 * 
 * @param game The game structure containing animation state.
 */
void	update_animation(t_game *game)
{
	game->anim_frame++;
	if (game->anim_frame >= 30)
	{
		game->anim_frame = 0;
		game->anim_index = (game->anim_index + 1) % PLAYER_FRAMES;
	}
}

/**
 * @brief Loads a single player sprite from an XPM file into
 *        the given t_img structure.
 * 
 * @param game The game structure containing the MLX pointer.
 * @param dst The t_img structure to load the sprite into.
 * @param path The file path to the XPM sprite.
 */
static void	load_one_player_sprite(t_game *game, t_img *dst, char *path)
{
	dst->img_ptr = mlx_xpm_file_to_image(
			game->mlx_ptr, path, &dst->width, &dst->height);
	if (dst->img_ptr == NULL)
	{
		ft_printf("Error\nFailed to load player sprite: %s\n", path);
		close_game(game, EXIT_FAILURE);
	}
	dst->addr = mlx_get_data_addr(
			dst->img_ptr, &dst->bpp, &dst->line_length, &dst->endian);
}

/**
 * @brief Loads all player animation sprites into the game structure.
 * 
 * @param game The game structure to load sprites into.
 */
void	load_player_sprites(t_game *game)
{
	// load_one_player_sprite(game, &game->player_anim[0],
	// 	"./textures/11.xpm");
	// load_one_player_sprite(game, &game->player_anim[1],
	// 	"./textures/22.xpm");
	// load_one_player_sprite(game, &game->player_anim[2],
	// 	"./textures/33.xpm");
	load_one_player_sprite(game, &game->player_anim[0],
		"./textures/player_0.xpm");
	load_one_player_sprite(game, &game->player_anim[1],
		"./textures/player_1.xpm");
	load_one_player_sprite(game, &game->player_anim[2],
		"./textures/player_2.xpm");
	load_one_player_sprite(game, &game->player_anim[3],
		"./textures/player_3.xpm");
	load_one_player_sprite(game, &game->player_anim[4],
		"./textures/player_4.xpm");
	game->anim_frame = 0;
	game->anim_index = 0;
}
