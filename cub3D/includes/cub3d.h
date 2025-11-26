/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:57:17 by tiyang            #+#    #+#             */
/*   Updated: 2025/11/25 12:44:16 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef cub3d_H
# define cub3d_H

# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <mlx.h>
# include <math.h>
# include "libft.h"

# define TILE_SIZE 64
# define TRANSPARENT_COLOR 0x00FF00FF
# define KEY_ESC 65307
# define KEY_LEFT  65361
# define KEY_RIGHT 65363
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
// Event codes for mlx_hook
# define MLX_KEY_PRESS 2
# define MLX_DESTROY_NOTIFY 17
// Event masks for mlx_hook
// # define MLX_KEY_PRESS_MASK (1L << 0)
# define MLX_NO_EVENT_MASK 0L
// Exit status codes
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

typedef struct s_game
{
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	double posX, posY;      // Player position
	double dirX, dirY;      // Direction vector
	double planeX, planeY;

	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	t_img	player_down_sprite; // For player facing down
	t_img	player_up_sprite; // For player facing up
	t_img	player_left_sprite; // For player facing left
	t_img	player_right_sprite; // For player facing right
	t_img	current_player_sprite; // the currently active player sprite
	t_img	floor_sprite;
	t_img	wall_sprite;
	t_img	collectible_sprite;
	t_img	exit_sprite;
	int		collectibles_collected;
	int		total_collectibles;
	int		moves;

	char	*no_texture; // North texture path
	char	*so_texture; // South texture path
	char	*we_texture; // West texture path
	char	*ea_texture; // East texture path
	int		floor_color; // Floor color in RGB
	int		ceiling_color; // Ceiling color in RGB

}	t_game;

// parse_info.c
int				parse_textures_and_colors(char *filename, t_game *game);

// parse_map.c
int				is_cub_file(char *filename);
int				parse_map_file(char *filename, t_game *game);

// utils.c
int				ft_strlen_without_newline(char *line);
char			**copy_map(t_game *game);
void			free_map(char **matrix);

// validate_map.c
int				validate_map(t_game *game);

// validate_path.c
int				validate_path(t_game *game);

//input.c
int				handle_keypress(int key, t_game *g);

/* GAME */
/* RENDER */
unsigned int	get_pixel_color(t_img *img, int x, int y);
unsigned int	*get_pixel_address(t_game *game, int pixel_x, int pixel_y);
void			draw_sprite(t_game *game, t_img *sprite, int tile_x,
					int tile_y);
void			render_map(t_game *game);
/* GAME INIT */
void			load_xpm_sprite(t_game *game, t_img *sprite_struct,
					const char *path);
void			load_sprites(t_game *game);
void			create_image_buffer(t_game *game);
void			register_mlx_hooks(t_game *game);
void			load_game(t_game *game);
/* INPUT */
int				touch_collectible(t_game *game, int new_player_x,
					int new_player_y);
int				touch_exit(t_game *game, int new_player_x, int new_player_y);
void			handle_move(int keycode, t_game *game, int *player_x,
					int *player_y);

int				handle_interaction(char target, t_game *game,
					int target_x, int target_y);
/* GAME CLOSE */
int				handle_close(t_game *game);
void			close_game(t_game *game, int exit_status);
void			destroy_objects(t_game *game);
void			destroy_player_sprites(t_game *game);
void			destroy_environment(t_game *game);

#endif
