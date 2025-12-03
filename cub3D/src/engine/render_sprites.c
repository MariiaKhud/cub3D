/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 09:22:17 by makhudon          #+#    #+#             */
/*   Updated: 2025/12/03 12:02:43 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	sort_sprites(t_game *g, int *order, double *dist)
{
	int		i;
	int		j;
	int		tmp_i;
	double	tmp_d;

	i = 0;
	while (i < g->sprite_count - 1)
	{
		j = 0;
		while (j < g->sprite_count - 1 - i)
		{
			if (dist[j] < dist[j + 1])
			{
				tmp_d = dist[j];
				dist[j] = dist[j + 1];
				dist[j + 1] = tmp_d;
				tmp_i = order[j];
				order[j] = order[j + 1];
				order[j + 1] = tmp_i;
			}
			j++;
		}
		i++;
	}
}

static void	init_sprite_arrays(t_game *g, int *order, double *dist)
{
	int	i;
	double	dx;
	double	dy;

	i = 0;
	while (i < g->sprite_count)
	{
		order[i] = i;
		dx = g->sprites[i].x - g->pos_x;
		dy = g->sprites[i].y - g->pos_y;
		dist[i] = dx * dx + dy * dy;
		i++;
	}
}

static void	draw_single_sprite(t_game *g, t_img *tex,
				double trans_x, double trans_y)
{
	int	sprite_screen_x;
	int	sprite_height;
	int	sprite_width;
	int	draw_start_y;
	int	draw_end_y;
	int	draw_start_x;
	int	draw_end_x;
	int	stripe;
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;

	sprite_screen_x = (int)((WIDTH / 2) * (1 + trans_x / trans_y));
	sprite_height = abs((int)(HEIGHT / trans_y));
	draw_start_y = -sprite_height / 2 + HEIGHT / 2;
	if (draw_start_y < 0)
		draw_start_y = 0;
	draw_end_y = sprite_height / 2 + HEIGHT / 2;
	if (draw_end_y >= HEIGHT)
		draw_end_y = HEIGHT - 1;
	sprite_width = sprite_height;
	draw_start_x = -sprite_width / 2 + sprite_screen_x;
	if (draw_start_x < 0)
		draw_start_x = 0;
	draw_end_x = sprite_width / 2 + sprite_screen_x;
	if (draw_end_x >= WIDTH)
		draw_end_x = WIDTH - 1;
	stripe = draw_start_x;
	while (stripe < draw_end_x)
	{
		tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x))
				* tex->width / sprite_width) / 256;
		if (trans_y > 0 && stripe > 0 && stripe < WIDTH
			&& trans_y < g->z_buffer[stripe])
		{
			y = draw_start_y;
			while (y < draw_end_y)
			{
				tex_y = ((y - HEIGHT / 2 + sprite_height / 2)
						* tex->height) / sprite_height;
				if (tex_y < 0)
					tex_y = 0;
				if (tex_y >= tex->height)
					tex_y = tex->height - 1;
				color = get_texture_pixel(tex, tex_x, tex_y);
				if ((color & 0xFF000000) == 0)
					my_mlx_pixel_put(g, stripe, y, color);
				y++;
			}
		}
		stripe++;
	}
}

void    render_sprites(t_game *g)
{
    int     order[MAX_SPRITES];
    double  dist[MAX_SPRITES];
    int     i;
    double  sprite_x;
    double  sprite_y;
    double  inv_det;
    double  trans_x;
    double  trans_y;
    t_img   *tex;

    if (g->sprite_count <= 0)
        return ;
    init_sprite_arrays(g, order, dist);
    sort_sprites(g, order, dist);
    tex = &g->tex_sprite;
    i = 0;
    while (i < g->sprite_count)
    {
        if (g->sprites[order[i]].alive)
        {
            sprite_x = g->sprites[order[i]].x - g->pos_x;
            sprite_y = g->sprites[order[i]].y - g->pos_y;
            inv_det = 1.0 / (g->plane_x * g->dir_y - g->dir_x * g->plane_y);
            trans_x = inv_det * (g->dir_y * sprite_x - g->dir_x * sprite_y);
            trans_y = inv_det * (-g->plane_y * sprite_x + g->plane_x * sprite_y);
            if (trans_y > 0.1)
                draw_single_sprite(g, tex, trans_x, trans_y);
        }
        i++;
    }
}
