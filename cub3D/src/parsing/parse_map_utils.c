/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 10:01:16 by makhudon          #+#    #+#             */
/*   Updated: 2025/11/27 10:35:20 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/** 
 * @brief Stores a map line into the game structure.
 * @param game The game structure to populate.
 * @param line The line to store.
 * @return int 1 on success.
 */
static int	store_map_line(t_game *game, char *line)
{
	int	len;

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
 * @brief Processes a line from the map file.
 * Determines if the line is part of the map and stores it if so.
 * @param game The game structure to populate.
 * @param line The line to process.
 * @return int 1 on success, 0 if line is empty before map starts,
 * -1 on memory allocation failure.
 */
static int	process_map_line(t_game *game, char *line)
{
	if (game->map_start == 0 && (*line == '\n' || *line == '\0'))
		return (free(line), 0);
	if (game->map_start == 1 && (*line == '\n' || *line == '\0'))
	{
		free(line);
		line = ft_strdup(" ");
		if (line == NULL)
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
 * @brief Reads the map content from the file descriptor
 * and populates the game map.
 * @param fd The file descriptor of the map file.
 * @param game The game structure to populate.
 * @return int 1 on success, 0 on failure.
 */
int	read_map_file(int fd, t_game *game)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (process_map_line(game, line) == -1)
		{
			close(fd);
			return (0);
		}
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
