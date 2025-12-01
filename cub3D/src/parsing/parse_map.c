/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:14:23 by makhudon          #+#    #+#             */
/*   Updated: 2025/12/01 13:02:40 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/** 
 * @brief Normalizes a line to the specified maximum width
 *        by padding with spaces.
 * @param line The original line.
 * @param max_width The desired maximum width.
 * @return char* The normalized line (may be the same
 *         as input if no padding needed).
 */
static char	*normalize_line_width(char *line, int max_width)
{
	int		len;
	int		i;
	char	*normalized_line;

	len = (int)ft_strlen(line);
	if (len >= max_width)
		return (line);
	normalized_line = (char *)malloc(sizeof(char) * (max_width + 1));
	if (normalized_line == NULL)
		return (line);
	i = 0;
	while (i < len)
	{
		normalized_line[i] = line[i];
		i++;
	}
	while (i < max_width)
	{
		normalized_line[i] = ' ';
		i++;
	}
	normalized_line[i] = '\0';
	free(line);
	return (normalized_line);
}

/** 
 * @brief Finishes populating the game map after reading all lines.
 * @param game The game structure containing the map.
 */
static void	finish_map(t_game *game)
{
	int	y;

	game->map[game->index] = NULL;
	game->map_height = game->index;
	game->map_width = game->max_width;
	y = 0;
	while (y < game->map_height)
	{
		game->map[y] = normalize_line_width(game->map[y], game->map_width);
		y++;
	}
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
	game->map = malloc(sizeof(char *) * 1024);
	if (game->map == NULL)
		return (close(fd), -1);
	return (fd);
}

/** 
 * @brief Parses the map file and populates the game map.
 * @param filename The name of the map file.
 * @param game The game structure to populate.
 * @return int 1 on success, 0 on failure.
 */
int	parse_map_file(char *filename, t_game *game)
{
	int	fd;

	game->map_start = 0;
	game->max_width = 0;
	game->index = 0;
	fd = open_map_file(filename, game);
	if (fd < 0)
		return (0);
	if (!read_map_file(fd, game))
		return (0);
	finish_map(game);
	return (game->map_height > 0);
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
