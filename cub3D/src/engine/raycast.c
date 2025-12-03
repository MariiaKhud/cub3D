/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:46:59 by tiyang            #+#    #+#             */
/*   Updated: 2025/12/03 12:02:19 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/** 
 * @brief Initializes the ray for a specific screen column.
 * 
 * @param game The game structure containing player info.
 * @param x The x-coordinate of the screen column.
 * @param ray The ray structure to initialize.
 */
static void	init_ray(t_game *game, int x, t_ray *ray)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = game->dir_x + game->plane_x * ray->camera_x;
	ray->ray_dir_y = game->dir_y + game->plane_y * ray->camera_x;
	ray->map_x = (int)game->pos_x;
	ray->map_y = (int)game->pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

/** 
 * @brief Calculates the drawing parameters for a wall slice.
 * 
 * @param perp_wall_dist The perpendicular distance to the wall.
 * @param data The drawing data structure to populate.
 */
static void	calculate_draw_params(double perp_wall_dist, t_draw_data *data)
{
	int	line_height;

	line_height = (int)(HEIGHT / perp_wall_dist);
	data->line_height = line_height;
	data->draw_start = -line_height / 2 + HEIGHT / 2;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = line_height / 2 + HEIGHT / 2;
	if (data->draw_end >= HEIGHT)
		data->draw_end = HEIGHT - 1;
}

/** 
 * @brief Calculates the x-coordinate on the texture for wall rendering.
 * 
 * @param game The game structure containing textures.
 * @param ray The ray structure with hit information.
 * @param perp_wall_dist The perpendicular distance to the wall.
 * @param data The drawing data structure to populate.
 */
static void	cast_single_ray(t_game *game, int x)
{
	t_ray		ray;
	double		perp_wall_dist;
	t_draw_data	data;

	init_ray(game, x, &ray);
	set_step_and_side_dist(game, &ray);
	perform_dda(game, &ray);
	perp_wall_dist = calculate_perp_wall_dist(&ray);
	game->z_buffer[x] = perp_wall_dist;
	calculate_draw_params(perp_wall_dist, &data);
	calculate_texture_x(game, &ray, perp_wall_dist, &data);
	data.x = x;
	draw_vertical_line(game, &data);
	// game->z_buffer[x] = perp_wall_dist;
}

/** 
 * @brief Performs raycasting for the entire screen and renders the scene.
 * 
 * @param game The game structure containing all necessary info.
 */
void	raycast(t_game *game)
{
	int	x;

	render_background(game);
	x = 0;
	while (x < WIDTH)
	{
		cast_single_ray(game, x);
		x++;
	}
	render_sprites(game);
	render_minimap(game);
	draw_player_sprite(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->img.img_ptr, 0, 0);
}
