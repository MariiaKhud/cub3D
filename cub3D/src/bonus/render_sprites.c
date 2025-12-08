/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_sprites.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/03 09:22:17 by makhudon      #+#    #+#                 */
/*   Updated: 2025/12/08 09:25:43 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Draws a vertical stripe of the sprite on the screen.
 * 
 * @param g The game structure containing sprite and player info.
 * @param tex The texture image for the sprite.
 * @param sr The calculated sprite rendering dimensions.
 * @param stripe The current screen x-coordinate to draw.
 */
static void	draw_sprite_stripe(t_game *g, t_img *tex,
				t_sprite_render *sr, int stripe)
{
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;

	tex_x = (int)(256 * (stripe - (-sr->width / 2 + sr->screen_x))
			* tex->width / sr->width) / 256;
	y = sr->start_y;
	while (y < sr->end_y)
	{
		tex_y = ((y - HEIGHT / 2 + sr->height / 2) * tex->height) / sr->height;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		color = get_texture_pixel(tex, tex_x, tex_y);
		if ((color & 0x00FFFFFF) != TRANSPARENT_COLOR)
			my_mlx_pixel_put(g, stripe, y, color);
		y++;
	}
}

/** 
 * @brief Draws a single sprite on the screen.
 * 
 * @param g The game structure containing sprite and player info.
 * @param tex The texture image for the sprite.
 * @param trans_x The transformed x position of the sprite.
 * @param trans	y The transformed y position of the sprite.
 */
static void	draw_single_sprite(t_game *g, t_img *tex,
				double trans_x, double trans_y)
{
	t_sprite_render	sr;
	int				stripe;

	calc_sprite_dims(&sr, trans_x, trans_y);
	stripe = sr.start_x;
	while (stripe < sr.end_x)
	{
		if (trans_y > 0 && stripe > 0 && stripe < WIDTH
			&& trans_y < g->z_buffer[stripe])
			draw_sprite_stripe(g, tex, &sr, stripe);
		stripe++;
	}
}

/**
 * @brief Calculates the transformed position of a sprite.
 * 
 * @param g The game structure containing player info.
 * @param sx Pointer to store the sprite's x position relative to the player.
 * @param sy Pointer to store the sprite's y position relative to the player.
 */
static void	calc_transform(t_game *g, double *trans, double sx, double sy)
{
	double	inv_det;

	inv_det = 1.0 / (g->plane_x * g->dir_y - g->dir_x * g->plane_y);
	trans[0] = inv_det * (g->dir_y * sx - g->dir_x * sy);
	trans[1] = inv_det * (-g->plane_y * sx + g->plane_x * sy);
}

/**
 * @brief Renders a single sprite at the given index 
 * after calculating its position and transformation.
 * 
 * @param g The game structure containing sprite and player info.
 * @param order The array of sorted sprite indices.
 * @param i The index of the sprite to render.
 */
static void	render_sprite_at_index(t_game *g, int *order, int i)
{
	double	sprite_pos[2];
	double	trans[2];

	if (!g->sprites[order[i]].alive)
		return ;
	calc_sprite_pos(g, order[i], &sprite_pos[0], &sprite_pos[1]);
	calc_transform(g, trans, sprite_pos[0], sprite_pos[1]);
	if (trans[1] > 0.1)
		draw_single_sprite(g, &g->tex_sprite, trans[0], trans[1]);
}

/**
 * @brief Renders all sprites in the game, sorted by distance from the player.
 * 
 * @param g The game structure containing sprite and player info.
 */
void	render_sprites(t_game *g)
{
	int		order[MAX_SPRITES];
	double	dist[MAX_SPRITES];
	int		i;

	if (g->sprite_count <= 0)
		return ;
	init_sprite_arrays(g, order, dist);
	sort_sprites(g, order, dist);
	i = 0;
	while (i < g->sprite_count)
	{
		render_sprite_at_index(g, order, i);
		i++;
	}
}
