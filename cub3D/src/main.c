/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:03:37 by tiyang            #+#    #+#             */
/*   Updated: 2025/11/25 11:14:41 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief The main entry point of the cub3D game.
 * This function initializes the game, loads the map,
 * validates it, and starts the game loop.
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line argument strings.
 * @return int Exit status of the program.
 * */
int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	if (argc != 2)
		return (ft_printf("Error\nUsage: ./cub3D <map.ber>\n"), EXIT_FAILURE);
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
	load_game(&game);
	ft_printf("\n--- Starting Game ---\n");
	ft_printf("Collect all avocados before boarding the spaceship!\n");
	mlx_loop(game.mlx_ptr);
	return (EXIT_SUCCESS);
}
