/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:17:46 by makhudon          #+#    #+#             */
/*   Updated: 2025/11/28 10:09:19 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
 * @brief Sets floor or ceiling color in the game structure
 *        based on the provided line.
 * @param game The game structure to populate.
 * @param line The line containing color information.
 */
static int	set_color(t_game *game, char *line)
{
	int	color;

	if (!ft_strncmp(line, "F ", 2))
	{
		trim_trailing_whitespace(line + 2);
		color = parse_rgb(line + 2);
		if (color == -1)
		{
			ft_printf("Error\nInvalid floor color\n");
			free_game(game);
			return (0);
		}
		game->floor_color = color;
		return (1);
	}
	else if (!ft_strncmp(line, "C ", 2))
	{
		trim_trailing_whitespace(line + 2);
		color = parse_rgb(line + 2);
		if (color == -1)
		{
			ft_printf("Error\nInvalid ceiling color\n");
			free_game(game);
			return (0);
		}
		game->ceiling_color = color;
		return (1);
	}
	return (1);
}

/**
 * @brief Sets texture paths in the game structure
 *        based on the provided line.
 * @param game The game structure to populate.
 * @param line The line containing texture information.
 */
static void	set_texture(t_game *game, char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
	{
		if (game->no_texture)
			free(game->no_texture);
		game->no_texture = ft_strdup(line + 3);
		if (game->no_texture)
			trim_trailing_whitespace(game->no_texture);
	}
	else if (!ft_strncmp(line, "SO ", 3))
	{
		if (game->no_texture)
			free(game->no_texture);
		game->so_texture = ft_strdup(line + 3);
		if (game->so_texture)
			trim_trailing_whitespace(game->so_texture);
	}
	else if (!ft_strncmp(line, "WE ", 3))
	{
		if (game->no_texture)
			free(game->no_texture);
		game->we_texture = ft_strdup(line + 3);
		if (game->we_texture)
			trim_trailing_whitespace(game->we_texture);
	}
	else if (!ft_strncmp(line, "EA ", 3))
	{
		if (game->no_texture)
			free(game->no_texture);
		game->ea_texture = ft_strdup(line + 3);
		if (game->ea_texture)
			trim_trailing_whitespace(game->ea_texture);
	}
}

/**
 * @brief Sets texture paths or colors in the game structure
 * based on the provided line.
 * @param game The game structure to populate.
 * @param line The line containing texture or color information.
 */
static int	set_texture_or_color(t_game *game, char *line)
{
	// set_texture(game, line);
	// set_color(game, line);
		// Texture identifiers
	if (!ft_strncmp(line, "NO ", 3)
		|| !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3)
		|| !ft_strncmp(line, "EA ", 3))
	{
		set_texture(game, line);
		return (1);
	}

	// Color identifiers
	if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
	{
		if (!set_color(game, line))
			return (0);
		return (1);
	}

	// Not a texture or color → let map parser handle it
	return (1);
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
			// set_texture_or_color(game, line);
		{
			if (!set_texture_or_color(game, line))
			{
				free(line);
				close(fd);
				free_game(game);
				return (1);
			}
		}
		free(line);
	}
	close(fd);
	return (0);
}
