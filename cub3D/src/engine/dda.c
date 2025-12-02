/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 09:20:00 by tiyang            #+#    #+#             */
/*   Updated: 2025/12/02 12:30:20 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Sets the step direction and initial side distances for DDA.
 * 
 * @param game The game structure containing player position.
 * @param ray The ray structure to set step and side distances.
 */
void	set_step_and_side_dist(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->pos_y)
			* ray->delta_dist_y;
	}
}

/**
 * @brief Performs the DDA algorithm to find wall hits.
 * 
 * @param game The game structure containing the map.
 * @param ray The ray structure to perform DDA on.
 */
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

/**
 * @brief Calculates the perpendicular wall distance for the ray.
 * 
 * @param ray The ray structure containing side distances and direction.
 * @return double The perpendicular distance to the wall.
 */
double	calculate_perp_wall_dist(t_ray *ray)
{
	double	perp_wall_dist;

	if (ray->side == 0)
		perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	return (perp_wall_dist);
}

/**
 * @brief Selects the appropriate texture based on the ray's side and direction.
 * 
 * @param game The game structure containing textures.
 * @param ray The ray structure containing side and direction information.
 * @return t_img* Pointer to the selected texture.
 */
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

/**
 * @brief Calculates the x-coordinate on the texture for wall rendering.
 * 
 * @param game The game structure containing textures.
 * @param ray The ray structure with hit information.
 * @param perp_wall_dist The perpendicular distance to the wall.
 * @param data The drawing data structure to populate.
 */
void	calculate_texture_x(t_game *game, t_ray *ray,
	double perp_wall_dist, t_draw_data *data)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = game->pos_y + perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->pos_x + perp_wall_dist * ray->ray_dir_x;
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
