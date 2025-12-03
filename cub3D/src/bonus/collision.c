/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collision.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/01 12:56:53 by tiyang        #+#    #+#                 */
/*   Updated: 2025/12/03 09:39:52 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Checks if a specific point (x, y) is inside a wall or invalid space.
 * @param game The game structure.
 * @param x The x-coordinate to check.
 * @param y The y-coordinate to check.
 * @return int 1 if the point is safe (walkable), 0 if it is a wall/door.
 */
int	is_valid_pos(t_game *game, double x, double y)
{
	int		map_x;
	int		map_y;
	char	cell;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y >= game->map_height)
		return (0);
	if (map_x < 0 || map_x >= (int)ft_strlen(game->map[map_y]))
		return (0);
	if (game->map[map_y][map_x] == '1' || game->map[map_y][map_x] == ' ')
		return (0);
	cell = game->map[map_y][map_x];
	if (cell == '1')
		return (0);
	if (cell == 'D')
		return (0);
	if (cell == ' ' || cell == '\0')
		return (0);
	return (1);
}
