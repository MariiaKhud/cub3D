/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:14:23 by makhudon          #+#    #+#             */
/*   Updated: 2025/11/26 09:22:24 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/** 
 * @brief Normalizes a line to the specified maximum width by padding with spaces.
 * @param line The original line.
 * @param max_width The desired maximum width.
 * @return char* The normalized line (may be the same as input if no padding needed).
 */
static char	*normalize_line_width(char *line, int max_width)
{
	int		len;
	int		i;
	char	*new;

	len = (int)ft_strlen(line);
	if (len >= max_width)
		return (line);
	new = (char *)malloc(sizeof(char) * (max_width + 1));
	if (!new)
		return (line);
	i = 0;
	while (i < len)
	{
		new[i] = line[i];
		i++;
	}
	while (i < max_width)
	{
		new[i] = ' ';
		i++;
	}
	new[i] = '\0';
	free(line);
	return (new);
}

/** 
 * @brief Checks if a line contains valid map content.
 * A valid map content line contains at least one '0' or '1'
 * and only the characters '0', '1', 'N', 'S', 'E', 'W', ' ', and tabs.
 * @param line The line to check.
 * @return int 1 if the line is a valid map content line, 0 otherwise
 */
static int	is_map_content_line(char *line)
{
	int	i;
	int	has_digit;

	i = 0;
	has_digit = 0;
	if (line == NULL)
		return (0);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (!ft_strchr("01NSEW ", line[i]))
			return (0);
		if (line[i] == '0' || line[i] == '1')
			has_digit = 1;
		i++;
	}
	return (has_digit);
}

/**
 * @brief Processes a single line from the map file.
 * Updates the game map, map start flag, and max width as needed.
 * @param game The game structure to update.
 * @param line The line to process.
 * @param map_start Pointer to the map start flag.
 * @param max_width Pointer to the maximum width of the map.
 * @param i Pointer to the current index in the game map.
 * @return int 1 on success, 0 if line is ignored, -1 on error.
 */
static int	process_map_line(t_game *game, char *line, int *map_start,
							  int *max_width, int *i)
{
	int	len;

	if (*map_start == 0 && (*line == '\n' || *line == '\0'))
		return (free(line), 0);
	if (*map_start == 1 && (*line == '\n' || *line == '\0'))
	{
		free(line);
		line = ft_strdup(" ");
		if (!line)
			return (-1);
	}
	if (*map_start == 0 && is_map_content_line(line))
		*map_start = 1;
	if (*map_start == 1)
	{
		len = (int)ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[--len] = '\0';
		if (len > *max_width)
			*max_width = len;
		game->map[(*i)++] = line;
	}
	else
		free(line);
	return (1);
}

/** 
 * @brief Opens the map file and initializes the game map.
 * @param filename The name of the map file.
 * @param game The game structure to initialize.
 * @return int The file descriptor on success, -1 on error.
 */
static int	open_map_file(char *filename, t_game *game)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	game->map = malloc(sizeof(char *) * 1024); // temporary, can realloc later
	if (game->map == NULL)
		return (close(fd), -1);
	return (fd);
}

/** 
 * @brief Parses the map from the given file and populates the game structure.
 * @param filename The name of the map file.
 * @param game The game structure to populate.
 * @return int 1 on success, 0 on failure.
 */
int	parse_map_file(char *filename, t_game *game)
{
	int		fd;
	char	*line;
	int		map_start;
	int		i;
	int		max_width;
	int		res;

	i = 0;
	max_width = 0;
	map_start = 0;
	fd = open_map_file(filename, game);
	if (fd < 0)
		return (0);
	while ((line = get_next_line(fd)))
	{
		res = process_map_line(game, line, &map_start, &max_width, &i);
		if (res == -1)
			return (close(fd), 0);
	}
	close(fd);
	game->map[i] = NULL;
	game->map_height = i;
	// if (i > 0)
	// 	game->map_width = max_width;
	if (i > 0)
	{
		game->map_width = max_width;
		int y = 0;
		while (y < game->map_height)
		{
			game->map[y] = normalize_line_width(game->map[y], game->map_width);
			y++;
		}
	}
	else
		game->map_width = 0;
	return (i > 0);
}

/**
 * @brief Checks if the given filename has a .cub extension.
 * @param filename The name of the file to check.
 * @return int 1 if the file has a .cub or .ber extension,
 * 0 otherwise.
 */
int	is_cub_file(char *filename)
{
	int	len;

	len = (int)ft_strlen(filename);
	if (len < 5)
		return (0);
	if (!ft_strncmp(filename + len - 4, ".cub", 4))
		return (1);
	return (0);
}
