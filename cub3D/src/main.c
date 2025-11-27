/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:03:37 by tiyang            #+#    #+#             */
/*   Updated: 2025/11/27 08:45:10 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// // Temporary Hardcoded Map (24x24)
// // 1 = Wall, 0 = Empty
// int worldMap[24][24] = {
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,3,0,3,0,3,0,0,0,1},
//   {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,3,0,0,0,3,0,0,0,1},
//   {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,3,0,3,0,3,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,0,0,0,0,5,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };


void init_player_orientation(t_game *game)
{
    int y = 0;
    while (y < game->map_height)
    {
        int x = 0;
        // Iterate only up to the line length to avoid segfaults
        while (game->map[y][x]) 
        {
            if (ft_strchr("NSEW", game->map[y][x]))
            {
                game->posX = x + 0.5;
                game->posY = y + 0.5;
                // Set vectors based on direction (Example for North)
                // You will need to implement logic for S, E, W
                if (game->map[y][x] == 'N') {
                    game->dirX = 0; game->dirY = -1;
                    game->planeX = 0.66; game->planeY = 0;
                }
                // ... Add 'S', 'E', 'W' cases ...

                // Set current cell to empty so we don't collide with ourselves
                game->map[y][x] = '0';
                return;
            }
            x++;
        }
        y++;
    }
}
// This wrapper is needed because mlx_loop_hook expects (void *)
int game_loop(void *param)
{
    t_game *game = (t_game *)param;
    raycast(game);
    return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	if (argc != 2)
		return (ft_printf("Error\nUsage: ./cub3D <map.cub>\n"), EXIT_FAILURE);
	if (!is_cub_file(argv[1]))
		return (ft_printf("Error\nWrong map file type\n"), EXIT_FAILURE);
	if (parse_textures_and_colors(argv[1], &game))
    	return (ft_printf("Error\nFailed to parse textures/colors\n"), EXIT_FAILURE);

	// ====== Debug: Print parsed textures/colors ======
	ft_printf("NO texture: %s\n", game.no_texture);
	ft_printf("SO texture: %s\n", game.so_texture);
	ft_printf("WE texture: %s\n", game.we_texture);
	ft_printf("EA texture: %s\n", game.ea_texture);
	ft_printf("Floor color: 0x%X\n", game.floor_color);
	ft_printf("Ceiling color: 0x%X\n", game.ceiling_color);
	// =================================================
	
	if (!parse_map_file(argv[1], &game))
		return (ft_printf("Error\nFailed to load map\n"), EXIT_FAILURE);
	if (!validate_map(&game))
		return (ft_printf("Error\nInvalid map\n"), EXIT_FAILURE);
	
	
	
	// ======== INIT PLAYER ========
	init_player_orientation(&game);
	// ======== MLX INIT ============
	// 1. Initialize MLX
	ft_printf("\n--- Starting Game ---\n");
	load_game(&game);
    // game.mlx_ptr = mlx_init();
	// if (!game.mlx_ptr)
    //     return (EXIT_FAILURE);
    // game.win_ptr = mlx_new_window(game.mlx_ptr, WIDTH, HEIGHT, "Cub3D");

	// // Create the Image Buffer (The canvas we draw on)
    // game.img.img_ptr = mlx_new_image(game.mlx_ptr, WIDTH, HEIGHT);
    // game.img.addr = mlx_get_data_addr(game.img.img_ptr, &game.img.bpp,
    //     &game.img.line_length, &game.img.endian);

    // // 2. Initialize Player Variables (Start Position)
    // // game.posX = 22.0;
    // // game.posY = 12.0;  // Start somewhere in the middle-right
    // // game.dirX = -1.0;  // Facing West
    // // game.dirY = 0.0;
    // // game.planeX = 0.0;
    // // game.planeY = 0.66; // The 2D Raycaster version of "Field of View"

    // // 3. Link the map
    // //game.test_map = worldMap;

    // // 4. Start the loop
    // // Instead of rendering once, we hook it to the loop for future movement
	register_mlx_hooks(&game);
    mlx_loop_hook(game.mlx_ptr, game_loop, &game);
    mlx_loop(game.mlx_ptr);
	return (EXIT_SUCCESS);
}
