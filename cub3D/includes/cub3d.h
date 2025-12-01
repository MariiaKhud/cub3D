/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:57:17 by tiyang            #+#    #+#             */
/*   Updated: 2025/12/01 13:13:36 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <mlx.h>
# include <math.h>
# include "libft.h"

# define WIDTH 640
# define HEIGHT 480
# define KEY_ESC 65307
# define KEY_LEFT  65361
# define KEY_RIGHT 65363
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define MLX_KEY_PRESS 2
# define MLX_DESTROY_NOTIFY 17
# define MOVE_SPEED 0.08
# define ROT_SPEED 0.05
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

typedef struct s_img
{
	void	*img_ptr; // drawing canvas
	char	*addr; // pointer to the start of pixel data
	int		bpp; // bits_per_pixel (32 for RGBA)
	int		line_length; // number of bytes for one row of pixels
	int		endian; // how bytes are ordered (0 or 1)
	int		width; // sprite dimensions
	int		height; // sprite dimensions
}	t_img;

typedef struct s_draw_data
{
	int		x;
	int		y;
	int		draw_start;
	int		draw_end;
	int		line_height;
	int		tex_x;
	t_img	*tex;
}	t_draw_data;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}	t_ray;

typedef struct s_game
{
	char	**map;
	int		map_width;
	int		map_height;
	int		map_start;
	int		max_width;
	int		index;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	void	*mlx_ptr;
	void	*win_ptr;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor_color;
	int		ceiling_color;
	t_img	img;
	t_img	tex_no;
	t_img	tex_so;
	t_img	tex_we;
	t_img	tex_ea;
}	t_game;

// ============ ENGINE FUNCTIONS =========== //
// raycast.c
void	raycast(t_game *game);

// utils.c
void	render_background(t_game *game);
void	draw_vertical_line(t_game *game, t_draw_data *data);

// dda.c
void	set_step_and_side_dist(t_game *game, t_ray *ray);
void	perform_dda(t_game *game, t_ray *ray);
double	calculate_perp_wall_dist(t_ray *ray);
void	calculate_texture_x(t_game *game, t_ray *ray,
			double perp_wall_dist, t_draw_data *data);

// ============ PARSING FUNCTIONS =========== //
// parse_info.c
int		parse_textures_and_colors(char *filename, t_game *game);
void	trim_trailing_whitespace(char *s);

// parse_info_rgb.c
int		parse_rgb(char *line);
char	*skip_spaces(char *s);

// parse_info_utils.c
int		is_id(const char *s, const char *id2);
void	set_texture(t_game *game, char *trimmed);
int		set_color(t_game *game, char *trimmed,
			int *has_floor, int *has_ceiling);

// parse_map.c
int		is_cub_file(char *filename);
int		parse_map_file(char *filename, t_game *game);

// parse_map_utils.c
int		read_map_file(int fd, t_game *game);

// utils.c
int		ft_strlen_without_newline(char *line);
char	**copy_map(t_game *game);
int		validate_textures(t_game *game);
int		check_invalid_identifier_order(t_game *game, char *trimmed,
			char *line);

// free_utils.c
void	free_game(t_game *game);
void	free_map(char **map);
void	free_split(char **split);

// validate_map.c
int		validate_map(t_game *game);

// ============ INPUT FUNCTIONS =========== //
// input.c
int		handle_keypress(int key, t_game *game);

// input_helper.c
void	move_left(t_game *game);
void	move_right(t_game *game);
void	move_forward(t_game *game);
void	move_backward(t_game *game);

// ============ LIFECYCLE FUNCTIONS ========== //
// game_init.c
void	load_game(t_game *game);
void	register_mlx_hooks(t_game *game);

// game_close.c
int		handle_close(t_game *game);
void	close_game(t_game *game, int exit_status);

// player_init.c
void	set_direction_north(t_game *game);
void	set_direction_south(t_game *game);
void	set_direction_east(t_game *game);
void	set_direction_west(t_game *game);
void	set_player_direction(t_game *game, char direction);

// player_position.c
void	init_player_orientation(t_game *game);

#endif