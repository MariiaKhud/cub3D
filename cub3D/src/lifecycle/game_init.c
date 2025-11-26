/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:38:24 by tiyang            #+#    #+#             */
/*   Updated: 2025/11/26 08:39:06 by makhudon         ###   ########.fr       */
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

// static int	handle_keypress(int keycode, t_game *game)
// {
// 	if (keycode == KEY_ESC)
// 		close_game(game, EXIT_SUCCESS);
// 	return (0);
// }


// registers event hooks. See further notes below.
void	register_mlx_hooks(t_game *game)
{
	mlx_hook(game->win_ptr, MLX_KEY_PRESS, (1L << 0),
		handle_keypress, game);
	mlx_hook(game->win_ptr, MLX_DESTROY_NOTIFY, 0L,
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
	render_map(game);  // NEED NEW FUNCTION TO RENDER MAP
	register_mlx_hooks(game);
}
