/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:03:37 by tiyang            #+#    #+#             */
/*   Updated: 2025/11/24 10:48:25 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	if (argc != 2)
		return (ft_printf("Error\nUsage: ./so_long <map.ber>\n"), EXIT_FAILURE);
	if (!is_ber_file(argv[1]))
		return (ft_printf("Error\nWrong map file type\n"), EXIT_FAILURE);
	if (!load_map(argv[1], &game))
		return (ft_printf("Error\nFailed to load map\n"), EXIT_FAILURE);
	if (!validate_map(&game))
		return (ft_printf("Error\nInvalid map\n"), EXIT_FAILURE);
	load_game(&game);
	ft_printf("\n--- Starting Game ---\n");
	ft_printf("Collect all avocados before boarding the spaceship!\n");
	mlx_loop(game.mlx_ptr);
	return (EXIT_SUCCESS);
}
