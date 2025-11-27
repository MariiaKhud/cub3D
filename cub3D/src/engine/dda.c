/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dda.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/27 09:20:00 by tiyang        #+#    #+#                 */
/*   Updated: 2025/11/27 09:31:11 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_step_and_side_dist(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->posX - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->posX)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->posY - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->posY)
			* ray->delta_dist_y;
	}
}

void	perform_dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

double	calculate_perp_wall_dist(t_ray *ray)
{
	double	perp_wall_dist;

	if (ray->side == 0)
		perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	return (perp_wall_dist);
}

static t_img	*select_texture(t_game *game, t_ray *ray)
{
	t_img	*texture;

	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			texture = &game->tex_we;
		else
			texture = &game->tex_ea;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			texture = &game->tex_no;
		else
			texture = &game->tex_so;
	}
	return (texture);
}

void	calculate_texture_x(t_game *game, t_ray *ray,
	double perp_wall_dist, t_draw_data *data)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = game->posY + perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->posX + perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	data->tex = select_texture(game, ray);
	tex_x = (int)(wall_x * (double)data->tex->width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = data->tex->width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = data->tex->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= data->tex->width)
		tex_x = data->tex->width - 1;
	data->tex_x = tex_x;
}
