/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:01:42 by makhudon          #+#    #+#             */
/*   Updated: 2025/12/08 12:03:42 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/** 
 * @brief Checks if there are any open spaces or player
 *        start positions on the border of the map.
 * 
 * @param game The game structure containing the map.
 * @return int 1 if there is an open space or player
 *             start on the border, 0 otherwise.
 */
int	has_open_on_border(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (y == 0 || y == game->map_height - 1
				|| x == 0 || x == game->map_width - 1)
			{
				if (ft_strchr("0NSEW2", game->map[y][x]))
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
