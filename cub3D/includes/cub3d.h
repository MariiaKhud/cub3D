/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:57:17 by tiyang            #+#    #+#             */
/*   Updated: 2025/11/27 10:48:05 by makhudon         ###   ########.fr       */
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
# define TILE_SIZE 64
# define TRANSPARENT_COLOR 0x00FF00FF
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

typedef struct s_game
{
	// OLD MAP VARIABLES
	char	**map;
	int		map_width;
	int		map_height;
	int map_start;
	int max_width;
	int index;

	// NEW PLAYER POSITION & ORIENTATION VARIABLES
	double posX, posY;      // Player position
	double dirX, dirY;      // Direction vector
	double planeX, planeY;
	
	// MLX POINTERS
	void	*mlx_ptr;
	void	*win_ptr;
	// BELOW VARIABLES FROM SO_LONG TO BE CHANGED / DELETED

	// NEW: TEXTURE VARIABLES
	char	*no_texture; // North texture path
	char	*so_texture; // South texture path
	char	*we_texture; // West texture path
	char	*ea_texture; // East texture path
	int		floor_color; // Floor color in RGB
	int		ceiling_color; // Ceiling color in RGB

	t_img	img;     // Main image buffer
	t_img   tex_no;  // North wall texture
	t_img   tex_so;  // South wall texture
	t_img   tex_we;  // West wall texture
	t_img   tex_ea;  // East wall texture

}	t_game;

// CUB3D FUNCTIONS
void    raycast(t_game *game);

// PARSING FUNCTIONS
// parse_info.c
int				parse_textures_and_colors(char *filename, t_game *game);

// parse_info_utils.c
int				parse_rgb(char *line);

// parse_map.c
int				is_cub_file(char *filename);
int				parse_map_file(char *filename, t_game *game);

// parse_map_utils.c
int				read_map_file(int fd, t_game *game);

// utils.c
int				ft_strlen_without_newline(char *line);
char			**copy_map(t_game *game);
void			free_map(char **matrix);
void			free_split(char **split);
// validate_map.c
int				validate_map(t_game *game);
// validate_path.c
void			free_map(char **matrix);

// INPUT FUNCTIONS
// input.c
int				handle_keypress(int key, t_game *game);

// input_helper.c
void			move_left(t_game *game);
void			move_right(t_game *game);
void			move_forward(t_game *game);
void			move_backward(t_game *game);

// LIFECYCLE FUNCTIONS
// game_init.c
void			load_game(t_game *game);
void			register_mlx_hooks(t_game *game);

// game_close.c
int				handle_close(t_game *game);
void			close_game(t_game *game, int exit_status);

#endif