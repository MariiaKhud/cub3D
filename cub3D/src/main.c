/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/12 15:03:37 by tiyang        #+#    #+#                 */
/*   Updated: 2025/11/25 15:19:53 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Temporary Hardcoded Map (24x24)
// 1 = Wall, 0 = Empty
int worldMap[24][24] = {
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,5,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

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

	// CUB3D
	(void)argc;
	(void)argv;
	// 1. Initialize MLX
    game.mlx_ptr = mlx_init();
    game.win_ptr = mlx_new_window(game.mlx_ptr, WIDTH, HEIGHT, "Cub3D - Day 2");

	// Create the Image Buffer (The canvas we draw on)
    game.img.img_ptr = mlx_new_image(game.mlx_ptr, WIDTH, HEIGHT);
    game.img.addr = mlx_get_data_addr(game.img.img_ptr, &game.img.bpp,
        &game.img.line_length, &game.img.endian);

    // 2. Initialize Player Variables (Start Position)
    game.posX = 22.0;
    game.posY = 12.0;  // Start somewhere in the middle-right
    game.dirX = -1.0;  // Facing West
    game.dirY = 0.0;
    game.planeX = 0.0;
    game.planeY = 0.66; // The 2D Raycaster version of "Field of View"

    // 3. Link the map
    game.test_map = worldMap;

    // 4. Start the loop
    // Instead of rendering once, we hook it to the loop for future movement
    mlx_loop_hook(game.mlx_ptr, game_loop, &game);
    mlx_loop(game.mlx_ptr);

	// OLD MAIN FUNCTION 
	// ft_bzero(&game, sizeof(t_game));
	// if (argc != 2)
	// 	return (ft_printf("Error\nUsage: ./so_long <map.ber>\n"), EXIT_FAILURE);
	// if (!is_ber_file(argv[1]))
	// 	return (ft_printf("Error\nWrong map file type\n"), EXIT_FAILURE);
	// if (!load_map(argv[1], &game))
	// 	return (ft_printf("Error\nFailed to load map\n"), EXIT_FAILURE);
	// if (!validate_map(&game))
	// 	return (ft_printf("Error\nInvalid map\n"), EXIT_FAILURE);
	// load_game(&game);
	// ft_printf("\n--- Starting Game ---\n");
	// ft_printf("Collect all avocados before boarding the spaceship!\n");
	// mlx_loop(game.mlx_ptr);
	return (EXIT_SUCCESS);
}
