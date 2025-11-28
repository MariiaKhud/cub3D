/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:03:37 by tiyang            #+#    #+#             */
/*   Updated: 2025/11/28 10:33:10 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* 
 * @brief Main game loop function called by MLX.
 * 
 * @param param Pointer to the game structure.
 * @return int Always returns 0.
 */
int	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	raycast(game);
	return (0);
}

// Call this at the very end of main(), after you finish parsing and using the map
// static void	cleanup_gnl(void)
// {
// 	char	*line;

// 	// Call get_next_line until it returns NULL to free the static storage
// 	while ((line = get_next_line(-1)))
// 		free(line);
// }


/* 
 * @brief Checks if the given filename has a .cub extension.
 * 
 * @param filename The name of the file to check.
 * @return int 1 if the file has a .cub extension, 0 otherwise.
 */
int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	if (argc != 2)
		return (ft_printf("Error\nUsage: ./cub3D <map.cub>\n"), 1);
	if (!is_cub_file(argv[1]))
		return (ft_printf("Error\nWrong map file type\n"), 1);
	if (parse_textures_and_colors(argv[1], &game))
		// return (ft_printf("Error\nFailed to parse\n"), 1);
	{
		free_game(&game);
		// return (ft_printf("Error\nFailed to parse\n"), 1);
		ft_putstr_fd("Error\nFailed to parse\n", 2);
		return (EXIT_FAILURE);
	}
	if (!parse_map_file(argv[1], &game))
		// return (ft_printf("Error\nFailed to load map\n"), 1);
	{
		free_game(&game);
        ft_putstr_fd("Error\nFailed to load map\n", 2);
        return (EXIT_FAILURE);
	}
	if (!validate_map(&game))
		// return (ft_printf("Error\nInvalid map\n"), 1);
	{
		free_game(&game);                // free everything safely
		ft_putstr_fd("Error\nInvalid map\n", 2);
		return (EXIT_FAILURE);
	}
	init_player_orientation(&game);
	load_game(&game);
	ft_printf("--- Starting Game ---\n");
	register_mlx_hooks(&game);
	mlx_loop_hook(game.mlx_ptr, game_loop, &game);
	mlx_loop(game.mlx_ptr);
	// cleanup_gnl();
	return (0);
}
