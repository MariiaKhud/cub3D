/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:17:46 by makhudon          #+#    #+#             */
/*   Updated: 2025/11/26 13:09:29 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub3d.h"

/**
 * @brief Parses an RGB color from a string in the format "R,G,B".
 * @param line The string containing the RGB values.
 * @return int The combined RGB color as an integer.
 */
// static int	parse_rgb(char *line)
// {
// 	int	r;
// 	int	g;
// 	int	b;

// 	r = ft_atoi(line);
// 	while (*line && *line != ',')
// 		line++;
// 	if (*line)
// 		line++;
// 	g = ft_atoi(line);
// 	while (*line && *line != ',')
// 		line++;
// 	if (*line)
// 		line++;
// 	b = ft_atoi(line);
// 	return ((r << 16) | (g << 8) | b);
// }

static char *skip_spaces(char *s)
{
    while (*s == ' ' || *s == '\t')
        s++;
    return s;
}

static int is_valid_rgb_number(const char *s)
{
    int n;

    // Skip leading spaces/tabs
    while (*s == ' ' || *s == '\t')
        s++;

    if (!*s)
        return 0;

    n = ft_atoi(s);
    if (n < 0 || n > 255)
        return 0;

    // Only allow digits until comma, space, tab, or end
    while (*s && *s != ',' && *s != ' ' && *s != '\t')
    {
        if (!(*s >= '0' && *s <= '9'))
            return 0;
        s++;
    }
    return 1;
}

static int	parse_rgb(char *line)
{
	char **split;
	int r;
	int g;
	int b;
	int i;
	int result;

	split = ft_split(line, ',');
	if (!split)
		return (-1);

	// Count elements
	i = 0;
	while (split[i])
		i++;
	if (i != 3)
	{
		free_split(split);
		return (-1);
	}

	// Validate each number
	i = 0;
	while (i < 3)
	{
		if (!is_valid_rgb_number(split[i]))
		{
			free_split(split);
			return (-1);
		}
		i++;
	}

	r = ft_atoi(skip_spaces(split[0]));
	g = ft_atoi(skip_spaces(split[1]));
	b = ft_atoi(skip_spaces(split[2]));

	free_split(split);
	result = (r << 16) | (g << 8) | b;
	return (result);
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
	int	color;
	
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
	{
		trim_trailing_whitespace(line + 2);
		color = parse_rgb(line + 2);
		if (color == -1)
		{
			ft_printf("Error\nInvalid floor color\n");
			exit(EXIT_FAILURE); // terminate on error
		}
		game->floor_color = color;
	}
	else if (!ft_strncmp(line, "C ", 2))
	{
		trim_trailing_whitespace(line + 2);
		color = parse_rgb(line + 2);
		if (color == -1)
		{
			ft_printf("Error\nInvalid ceiling color\n");
			exit(EXIT_FAILURE);
		}
		game->ceiling_color = color;
	}
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
