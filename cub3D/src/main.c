/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/12 15:03:37 by tiyang        #+#    #+#                 */
/*   Updated: 2025/12/02 13:04:59 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Main game loop function called by MLX.
 * 
 * @param param Pointer to the game structure.
 * @return int Always returns 0.
 */
static int	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	update_animation(game);
	raycast(game);
	return (0);
}

/**
 * @brief Start the game: initialize player,
 *        load resources, and enter MLX loop.
 * 
 * @param game Pointer to the game structure.
 */
static void	start_game(t_game *game)
{
	init_player_orientation(game);
	load_game(game);
	ft_printf("--- Starting Game ---\n");
	ft_printf("Use WASD to move, Arrow Keys ('<-' & '->') to look around.\n");
	ft_printf("Move mouse to look around when mouse is locked.\n");
	ft_printf("Press M to toggle mouse lock.\n");
	ft_printf("Press ESC to quit the game.\n");
	register_mlx_hooks(game);
	mlx_loop_hook(game->mlx_ptr, game_loop, game);
	mlx_loop(game->mlx_ptr);
}

/**
 * @brief Initialize the game: parse textures, colors, and map.
 * 
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param game Pointer to the game structure.
 * @return int 1 if success, 0 if failure.
 */
static int	initialize_game(int argc, char **argv, t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	if (argc != 2)
		return (ft_printf("Error\nUsage: ./cub3D <map.cub>\n"), 0);
	if (!is_cub_file(argv[1]))
		return (ft_printf("Error\nWrong map file type\n"), 0);
	if (parse_textures_and_colors(argv[1], game))
		return (0);
	if (!parse_map_file(argv[1], game))
		return (0);
	if (!validate_map(game))
	{
		ft_putstr_fd("Error\nInvalid map\n", 2);
		return (0);
	}
	return (1);
}

/**
 * @brief Entry point of the program.
 * 
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return int Exit status.
 */
int	main(int argc, char **argv)
{
	t_game	game;

	if (!initialize_game(argc, argv, &game))
	{
		free_game(&game);
		return (EXIT_FAILURE);
	}
	start_game(&game);
	free_game(&game);
	return (0);
}
