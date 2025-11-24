/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:17:46 by makhudon          #+#    #+#             */
/*   Updated: 2025/11/24 13:02:25 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Parses an RGB color from a string in the format "R,G,B".
 * @param line The string containing the RGB values.
 * @return int The packed RGB color as an integer.
 */
static int	parse_rgb(char *line)
{
	int	r;
	int	g;
	int	b;

	r = atoi(line);
	while (*line && *line != ',')
		line++;
	if (*line)
		line++;
	g = atoi(line);
	while (*line && *line != ',')
		line++;
	if (*line)
		line++;
	b = atoi(line);
	return ((r << 16) | (g << 8) | b);
}

/**
 * @brief Sets texture paths or floor/ceiling colors in the game struct.
 * @param game Pointer to the game structure.
 * @param line The line from the map file containing the info.
 */
static void	set_texture_or_color(t_game *game, char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		game->no_texture = ft_strdup(line + 3);
	else if (!ft_strncmp(line, "SO ", 3))
		game->so_texture = ft_strdup(line + 3);
	else if (!ft_strncmp(line, "WE ", 3))
		game->we_texture = ft_strdup(line + 3);
	else if (!ft_strncmp(line, "EA ", 3))
		game->ea_texture = ft_strdup(line + 3);
	else if (!ft_strncmp(line, "F ", 2))
		game->floor_color = parse_rgb(line + 2);
	else if (!ft_strncmp(line, "C ", 2))
		game->ceiling_color = parse_rgb(line + 2);
}

/**
 * @brief Parses texture paths and floor/ceiling colors from the map file.
 * @param filename The name of the .ber file containing the map.
 * @param game Pointer to the game structure where the info will be stored.
 * @return int Returns 0 on success, otherwise returns 1 on failure.
 */
int	parse_textures_and_colors(char *filename, t_game *game)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("Error: cannot open file %s\n", filename), 1);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		// ===== Debug print =====
        ft_printf("DEBUG line: '%s'\n", line);
        // =======================
		if (*line)
			set_texture_or_color(game, line);
		free(line);
	}
	close(fd);
	return (0);
}
