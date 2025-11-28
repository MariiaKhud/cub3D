/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 13:33:40 by makhudon          #+#    #+#             */
/*   Updated: 2025/11/28 13:35:33 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Sets the floor color in the game structure.
 * 
 * @param game Game structure to populate.
 * @param line Line containing the floor color.
 * @param has_floor Pointer to the floor flag to detect duplicates.
 * @return 1 on success, 0 on error.
 */
static int	set_floor_color(t_game *game, char *line, int *has_floor)
{
	int	color;

	if (*has_floor)
	{
		ft_printf("Error\nDuplicate floor color (F)\n");
		return (0);
	}
	color = parse_color_line(line);
	if (color == -1)
	{
		ft_printf("Error\nInvalid floor color\n");
		return (0);
	}
	game->floor_color = color;
	*has_floor = 1;
	return (1);
}

/**
 * @brief Sets the ceiling color in the game structure.
 * 
 * @param game Game structure to populate.
 * @param line Line containing the ceiling color.
 * @param has_ceiling Pointer to the ceiling flag to detect duplicates.
 * @return 1 on success, 0 on error.
 */
static int	set_ceiling_color(t_game *game, char *line, int *has_ceiling)
{
	int	color;

	if (*has_ceiling)
	{
		ft_printf("Error\nDuplicate ceiling color (C)\n");
		return (0);
	}
	color = parse_color_line(line);
	if (color == -1)
	{
		ft_printf("Error\nInvalid ceiling color\n");
		return (0);
	}
	game->ceiling_color = color;
	*has_ceiling = 1;
	return (1);
}

/**
 * @brief Determines if a line defines a floor or ceiling color and sets it.
 * 
 * @param game Pointer to the game structure to populate.
 * @param line The line containing the color definition.
 * @param has_floor Pointer to a flag indicating whether
 *                  the floor color has already been set.
 * @param has_ceiling Pointer to a flag indicating whether
 *                    the ceiling color has already been set.
 * @return 1 if the line was successfully processed or ignored,
 *         0 if there was an error setting the floor or ceiling color.
 */
int	set_color(t_game *game, char *line, int *has_floor, int *has_ceiling)
{
	if (!ft_strncmp(line, "F ", 2))
		return (set_floor_color(game, line + 2, has_floor));
	else if (!ft_strncmp(line, "C ", 2))
		return (set_ceiling_color(game, line + 2, has_ceiling));
	return (1);
}

/**
 * @brief Frees the old texture string and duplicates a new one.
 * 
 * @param dest Pointer to the texture string to update.
 * @param line Line from the map containing the texture path.
 */
static void	update_texture(char **dest, char *line)
{
	free(*dest);
	*dest = ft_strdup(line);
	if (*dest)
		trim_trailing_whitespace(*dest);
}

/**
 * @brief Sets the correct texture in the game structure based on the line.
 * 
 * @param game Game structure to populate.
 * @param line Line containing the texture identifier and path.
 */
void	set_texture(t_game *game, char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		update_texture(&game->no_texture, line + 3);
	else if (!ft_strncmp(line, "SO ", 3))
		update_texture(&game->so_texture, line + 3);
	else if (!ft_strncmp(line, "WE ", 3))
		update_texture(&game->we_texture, line + 3);
	else if (!ft_strncmp(line, "EA ", 3))
		update_texture(&game->ea_texture, line + 3);
}
