/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:57:17 by tiyang            #+#    #+#             */
/*   Updated: 2025/12/08 12:03:11 by makhudon         ###   ########.fr       */
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

# define WIDTH 1280
# define HEIGHT 960
# define KEY_ESC 65307
# define KEY_LEFT  65361
# define KEY_RIGHT 65363
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_M 109 // 'M' key for mouse toggle
# define KEY_E 101 // 'E' key for interact
# define MLX_KEY_PRESS 2
# define MLX_DESTROY_NOTIFY 17
# define MLX_MOTION_NOTIFY 6
# define MOVE_SPEED 0.08
# define ROT_SPEED 0.05
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define MOUSE_SENSITIVITY 0.0005 // mouse sensitivity factor
# define COLLISION_DIST 0.2
# define MM_TILE_SIZE 10
# define MM_OFFSET 20 // minimap offset from window edge
# define MM_VIEW_RANGE 10
# define MM_PLAYER_OFFSET 3 // player offset on the minimap
# define MM_PLAYER_SIZE 4
# define PLAYER_FRAMES 5 // pixels between animation frames
# define MM_DIR_LENGTH 15
# define MM_COLOR_BLACK 0x000000
# define MM_COLOR_WALL 0x808080
# define MM_COLOR_FLOOR 0xD3D3D3
# define MM_COLOR_PLAYER 0xFF0000
# define MM_COLOR_DOOR_CLOSED 0x800000
# define MM_COLOR_DOOR_OPEN 0xFFA500
# define TRANSPARENT_COLOR 0xFF00FF
# define MAX_SPRITES 128

/**
 * @brief Structure representing a sprite in the game.
 * 
 * Contains the position, texture ID, and state of the sprite.
 */
typedef struct s_sprite
{
	double	x;
	double	y;
	int		tex_id; // texture ID for the sprite
	int		alive; // 1 = alive/visible, 0 = inactive
}	t_sprite;

/**
 * @brief Structure for rendering sprite parameters.
 * 
 * Contains screen position and dimensions for rendering a sprite.
 */
typedef struct s_sprite_render
{
	int		screen_x;
	int		height;
	int		width;
	int		start_y;
	int		end_y;
	int		start_x;
	int		end_x;
}	t_sprite_render;

/**
 * @brief Structure to track parsing state.
 * 
 * Used to ensure correct order of identifiers and map data.
 */
typedef struct s_parse_state
{
	int	has_floor;
	int	has_ceiling;
	int	in_map;
}	t_parse_state;

/**
 * @brief Structure representing an image/texture.
 * 
 * Contains pointers and metadata for image manipulation.
 */
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

/**
 * @brief Structure for drawing vertical lines on the screen.
 * 
 * Contains parameters needed for rendering a vertical slice of a wall.
 */
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

/**
 * @brief Structure representing a ray in the raycasting engine.
 * 
 * Contains parameters for ray direction, position, and collision detection.
 */
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

/**
 * @brief Structure for Bresenham's line drawing algorithm.
 * 
 * Contains parameters needed to draw a line between two points.
 */
typedef struct s_line
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}	t_line;

/**
 * @brief Structure representing the overall game state.
 * 
 * Contains map data, player position and direction, textures,
 * and rendering information.
 */
typedef struct s_game
{
	char		**map;
	int			map_width;
	int			map_height;
	int			map_start;
	int			max_width;
	int			index;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	void		*mlx_ptr;
	void		*win_ptr;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	int			floor_color;
	int			ceiling_color;
	t_img		img;
	t_img		tex_no;
	t_img		tex_so;
	t_img		tex_we;
	t_img		tex_ea;
	t_img		tex_sky; // bonus sky texture
	t_img		player_anim[PLAYER_FRAMES]; // bonus player animation frames
	int			anim_frame;
	int			anim_index;
	t_sprite	sprites[MAX_SPRITES]; // array of sprites in the game
	int			sprite_count; // number of sprites
	double		z_buffer[WIDTH]; // z-buffer for sprite rendering
	t_img		tex_sprite; // sprite texture
	t_img		tex_door;
	int			mouse_locked; // 1 = locked (gameplay), 0 = unlocked (menu)
}	t_game;

// ============ ENGINE FUNCTIONS =========== //
// raycast.c
void			raycast(t_game *game);

// render_background.c
void			render_background(t_game *game);

// render_utils.c
void			render_background(t_game *game);
void			draw_vertical_line(t_game *game, t_draw_data *data);
unsigned int	get_texture_pixel(t_img *tex, int x, int y);
int				clamp_tex(int value, int limit);
void			my_mlx_pixel_put(t_game *game, int x, int y, int color);

// dda.c
void			set_step_and_side_dist(t_game *game, t_ray *ray);
void			perform_dda(t_game *game, t_ray *ray);
double			calculate_perp_wall_dist(t_ray *ray);
void			calculate_texture_x(t_game *game, t_ray *ray,
					double perp_wall_dist, t_draw_data *data);

// ============ PARSING FUNCTIONS =========== //

// parse_info.c
int				parse_textures_and_colors(char *filename, t_game *game);

// parse_info_rgb.c
int				parse_rgb(char *line);

// parse_info_utils.c
void			set_texture(t_game *game, char *trimmed);
int				set_color(t_game *game, char *trimmed,
					int *has_floor, int *has_ceiling);

// parse_info_helper.c
int				all_identifiers_set(t_game *game,
					int has_floor, int has_ceiling);
void			trim_trailing_whitespace(char *s);
char			*skip_spaces(char *s);
int				process_texture_id(t_game *game, char *trimmed);
int				is_id(const char *s, const char *id2);

// parse_map.c
int				is_cub_file(char *filename);
int				parse_map_file(char *filename, t_game *game);

// parse_map_utils.c
int				read_map_file(int fd, t_game *game);
int				is_map_content_line(char *line);

// utils.c
int				ft_strlen_without_newline(char *line);
char			**copy_map(t_game *game);
int				validate_textures(t_game *game);
int				check_invalid_identifier_order(t_game *game, char *trimmed,
					char *line);

// free_utils.c
void			free_game(t_game *game);
void			free_map(char **map);
void			free_split(char **split);
int				handle_texture(t_game *game, char *trimmed, char **target);

// validate_map.c
int				validate_map(t_game *game);

// validate_map_utils.c
int				has_open_on_border(t_game *game);

// ============ INPUT FUNCTIONS =========== //
// input.c
int				handle_keypress(int key, t_game *game);
void			check_sprite_pickup(t_game *game);

// input_helper.c
void			move_left(t_game *game);
void			move_right(t_game *game);
void			move_forward(t_game *game);
void			move_backward(t_game *game);

// ============ LIFECYCLE FUNCTIONS ========== //
// game_init.c
void			load_game(t_game *game);
void			register_mlx_hooks(t_game *game);

// game_close.c
int				handle_close(t_game *game);
void			close_game(t_game *game, int exit_status);

// game_close_helper.c
void			destroy_texture_path_strings(t_game *game);
void			destroy_player_sprites(t_game *game);
void			destroy_player_textures(t_game *game);

// player_init.c
void			set_direction_north(t_game *game);
void			set_direction_south(t_game *game);
void			set_direction_east(t_game *game);
void			set_direction_west(t_game *game);
void			set_player_direction(t_game *game, char direction);

// player_position.c
void			init_player_orientation(t_game *game);

// ============ BONUS ======================== //
// Minimap (Bonus)
void			render_minimap(t_game *game);
void			mm_pixel_put(t_game *game, int x, int y, int color);
int				get_tile_color(t_game *game, int map_x, int map_y);
void			draw_mm_square(t_game *game, int x, int y, int color);
void			draw_mm_line(t_game *game, t_line *line, int color);
void			init_and_draw_line(t_game *game, int coords[4], int color);

// Mouse Input (Bonus)
int				handle_mouse(int x, int y, t_game *game);

// Collision Detection (Bonus)
int				is_valid_pos(t_game *game, double x, double y);

// Animation (Bonus)
void			load_player_sprites(t_game *game);
void			update_animation(t_game *game);
void			draw_player_sprite(t_game *game);

// Interaction
void			interact(t_game *game);
int				is_door_enclosed(t_game *game, int x, int y);
int				validate_doors(t_game *game);

// render_sprites.c
void			render_sprites(t_game *g);

// parse_sprites.c
void			find_sprites_in_map(t_game *game);
void			init_sprite_arrays(t_game *g, int *order, double *dist);
void			sort_sprites(t_game *g, int *order, double *dist);

// sprite_utils.c
void			calc_sprite_dims(t_sprite_render *sr,
					double trans_x, double trans_y);
void			calc_sprite_pos(t_game *g, int idx, double *sx, double *sy);

#endif