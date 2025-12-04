/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 09:12:23 by makhudon          #+#    #+#             */
/*   Updated: 2025/12/03 11:57:04 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    find_sprites_in_map(t_game *game)
{
    int y;
    int x;

    game->sprite_count = 0;
    y = 0;
    while (y < game->map_height)
    {
        x = 0;
        while (x < game->map_width)
        {
            if (game->map[y][x] == '2')
            {
                if (game->sprite_count < MAX_SPRITES)
                {
                    game->sprites[game->sprite_count].x = x + 0.5;
                    game->sprites[game->sprite_count].y = y + 0.5;
                    game->sprites[game->sprite_count].tex_id = 0;
                    game->sprites[game->sprite_count].alive = 1;
                    game->sprite_count++;
                }
                game->map[y][x] = '0';
            }
            x++;
        }
        y++;
    }
}
