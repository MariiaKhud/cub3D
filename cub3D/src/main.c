/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/12 15:03:37 by tiyang        #+#    #+#                 */
/*   Updated: 2025/11/27 10:53:24 by tiyang        ########   odam.nl         */
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
		return (ft_printf("Error\nFailed to parse\n"), 1);
	if (!parse_map_file(argv[1], &game))
		return (ft_printf("Error\nFailed to load map\n"), 1);
	if (!validate_map(&game))
		return (ft_printf("Error\nInvalid map\n"), 1);
	init_player_orientation(&game);
	load_game(&game);
	ft_printf("\n--- Starting Game ---\n");
	register_mlx_hooks(&game);
	mlx_loop_hook(game.mlx_ptr, game_loop, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
