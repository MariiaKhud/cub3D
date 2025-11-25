/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:17:46 by makhudon          #+#    #+#             */
/*   Updated: 2025/11/25 11:22:15 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub3d.h"

/**
 * @brief Parses an RGB color from a string in the format "R,G,B".
 * @param line The string containing the RGB values.
 * @return int The combined RGB color as an integer.
 */
static int	parse_rgb(char *line)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(line);
	while (*line && *line != ',')
		line++;
	if (*line)
		line++;
	g = ft_atoi(line);
	while (*line && *line != ',')
		line++;
	if (*line)
		line++;
	b = ft_atoi(line);
	return ((r << 16) | (g << 8) | b);
}

/**
 * @brief Trim trailing '\n' and spaces from a string (in-place).
 * @param s The string to trim.
 */
static void	trim_trailing_whitespace(char *s)
{
	int	len;

	if (s == NULL)
		return ;
	len = (int)ft_strlen(s);
	while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == ' '
			|| s[len - 1] == '\t'))
	{
		s[len - 1] = '\0';
		len--;
	}
}

/**
 * @brief Sets texture paths or floor/ceiling colors in the game struct.
 * @param game The game structure to populate.
 * @param line The line containing the texture path or color info.
 */
static void	set_texture_or_color(t_game *game, char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
	{
		game->no_texture = ft_strdup(line + 3);
		if (game->no_texture)
			trim_trailing_whitespace(game->no_texture);
	}
	else if (!ft_strncmp(line, "SO ", 3))
	{
		game->so_texture = ft_strdup(line + 3);
		if (game->so_texture)
			trim_trailing_whitespace(game->so_texture);
	}
	else if (!ft_strncmp(line, "WE ", 3))
	{
		game->we_texture = ft_strdup(line + 3);
		if (game->we_texture)
			trim_trailing_whitespace(game->we_texture);
	}
	else if (!ft_strncmp(line, "EA ", 3))
	{
		game->ea_texture = ft_strdup(line + 3);
		if (game->ea_texture)
			trim_trailing_whitespace(game->ea_texture);
	}
	else if (!ft_strncmp(line, "F ", 2))
		game->floor_color = parse_rgb(line + 2);
	else if (!ft_strncmp(line, "C ", 2))
		game->ceiling_color = parse_rgb(line + 2);
}

/**
 * @brief Parses texture paths and floor/ceiling colors from the map file.
 * @param filename The name of the map file.
 * @param game The game structure to populate.
 * @return int 0 on success, 1 on failure.
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
		if (*line)
			set_texture_or_color(game, line);
		free(line);
	}
	close(fd);
	return (0);
}
