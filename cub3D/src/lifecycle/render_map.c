/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:27:14 by makhudon          #+#    #+#             */
/*   Updated: 2025/11/24 13:29:30 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void render_map(t_game *game)
{
    int x;
	int y;
    int pixel_x;
	int pixel_y;

    y = 0;
    while (y < game->map_height)
    {
        x = 0;
        while (x < game->map_width)
        {
            pixel_x = x * TILE_SIZE;
            pixel_y = y * TILE_SIZE;
            if (game->map[y][x] == '1') // wall
                mlx_put_image_to_window(game->mlx_ptr,
                                        game->win_ptr,
                                        game->wall_sprite.img_ptr,
                                        pixel_x, pixel_y);
            else if (game->map[y][x] == '0') // floor
                mlx_put_image_to_window(game->mlx_ptr,
                                        game->win_ptr,
                                        game->floor_sprite.img_ptr,
                                        pixel_x, pixel_y);
            else if (game->map[y][x] == 'C') // collectible
                mlx_put_image_to_window(game->mlx_ptr,
                                        game->win_ptr,
                                        game->collectible_sprite.img_ptr,
                                        pixel_x, pixel_y);
            else if (game->map[y][x] == 'E') // exit
                mlx_put_image_to_window(game->mlx_ptr,
                                        game->win_ptr,
                                        game->exit_sprite.img_ptr,
                                        pixel_x, pixel_y);
            else if (game->map[y][x] == 'P') // player
                mlx_put_image_to_window(game->mlx_ptr,
                                        game->win_ptr,
                                        game->current_player_sprite.img_ptr,
                                        pixel_x, pixel_y);
            x++;
        }
        y++;
    }
}
