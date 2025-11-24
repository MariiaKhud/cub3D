/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:13:55 by tiyang            #+#    #+#             */
/*   Updated: 2025/11/24 10:47:59 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


// initialise the player starting position in the game struct
void	set_starting_position(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

// recursive flood fill using a copy of the map, starting from the 
// starting position of the player. 
// checks if every collectible can be reached,
// and fills every visited tile with 'Y'.
// treats the exit as the wall for now as the player needs to collect
// all collectibles before using the exit.
void	floodfill_collectibles(char **map_copy, int x, int y)
{
	if (map_copy[y][x] == '1' || map_copy[y][x] == 'Y' ||
		map_copy[y][x] == 'E')
		return ;
	if (map_copy[y][x] == 'C' || map_copy[y][x] == '0')
		map_copy[y][x] = 'Y';
	floodfill_collectibles(map_copy, x + 1, y);
	floodfill_collectibles(map_copy, x - 1, y);
	floodfill_collectibles(map_copy, x, y + 1);
	floodfill_collectibles(map_copy, x, y - 1);
}

// second flood fill that checks if the exit is reachable at all
void	floodfill_exit(char **map_copy, int x, int y)
{
	if (map_copy[y][x] == '1' || map_copy[y][x] == 'Y')
		return ;
	if (map_copy[y][x] == 'C' || map_copy[y][x] == '0' ||
		map_copy[y][x] == 'E')
		map_copy[y][x] = 'Y';
	floodfill_exit(map_copy, x + 1, y);
	floodfill_exit(map_copy, x - 1, y);
	floodfill_exit(map_copy, x, y + 1);
	floodfill_exit(map_copy, x, y - 1);
}

// checks if after each flood fill a specific element has not been reached.
// returns 1 if that element is unreached.
int	is_element_unreachable(char **map_copy, char element, t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (map_copy[y][x] == element)
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}
