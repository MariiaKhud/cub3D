/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:01:16 by makhudon          #+#    #+#             */
/*   Updated: 2025/12/04 12:08:13 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Removes a comment from a map line by truncating
 *        at the '#' character.
 * 
 * @param line The line to process; everything after '#'
 *             will be removed.
 */
static void	trim_map_comment(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '#')
		{
			line[i] = '\0';
			return ;
		}
		i++;
	}
}

/** 
 * @brief Stores a map line into the game structure.
 * 
 * @param game The game structure to populate.
 * @param line The line to store.
 * @return int 1 on success.
 */
static int	store_map_line(t_game *game, char *line)
{
	int	len;

	trim_map_comment(line);
	len = (int)ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[--len] = '\0';
	if (len > game->max_width)
		game->max_width = len;
	game->map[game->index++] = line;
	return (1);
}

/** 
 * @brief Checks if a line contains valid map content.
 * 
 * A valid map content line contains at least one '0' or '1'
 * and only valid map characters ('0', '1', 'N', 'S', 'E', 'W', ' ', 'D', 'O').
 * 
 * @param line The line to check.
 * @return int 1 if the line contains map content, 0 otherwise.
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
	while (line[i] && line[i] != '\n' && line[i] != '#')
	{
		if (!ft_strchr("01NSEW2 DO", line[i]))
			return (0);
		if (line[i] == '0' || line[i] == '1')
			has_digit = 1;
		i++;
	}
	return (has_digit);
}

/** 
 * @brief Processes a single line from the map file.
 * 
 * Determines if the line is part of the map and stores it
 * in the game structure if so. Handles errors for invalid
 * lines after the map has started.
 * 
 * @param game Pointer to the game structure.
 * @param line The line to process.
 * @return int 1 on success, 0 to skip line, -1 on error.
 */
static int	process_map_line(t_game *game, char *line)
{
	char	*trimmed;

	trimmed = skip_spaces(line);
	if (game->map_start == 0 && (*trimmed == '\0' || *trimmed == '\n'))
		return (free(line), 0);
	if (check_invalid_identifier_order(game, trimmed, line))
		return (-1);
	if (game->map_start == 1 && !is_map_content_line(line))
	{
		if (*trimmed == '\0' || *trimmed == '\n')
			return (free(line), 0);
		ft_printf("Error\nExtra content after map\n");
		free(line);
		return (-1);
	}
	if (game->map_start == 0 && is_map_content_line(line))
		game->map_start = 1;
	if (game->map_start == 1)
		return (store_map_line(game, line));
	free(line);
	return (1);
}

/**
 * @brief Reads the map file line by line and processes each line.
 * 
 * Calls `process_map_line` for each line. Stops and frees remaining lines
 * on error. Marks the end of the map with NULL and closes the file descriptor.
 * 
 * @param fd File descriptor of the opened map file.
 * @param game Pointer to the game structure to populate the map.
 * @return 1 on success, 0 if an error occurred while processing the map.
 */
int	read_map_file(int fd, t_game *game)
{
	char	*line;
	int		res;

	line = get_next_line(fd);
	while (line != NULL)
	{
		res = process_map_line(game, line);
		if (res == -1)
		{
			game->map[game->index] = NULL;
			line = get_next_line(fd);
			while (line != NULL)
			{
				free(line);
				line = get_next_line(fd);
			}
			close(fd);
			return (0);
		}
		line = get_next_line(fd);
	}
	game->map[game->index] = NULL;
	close(fd);
	return (1);
}
