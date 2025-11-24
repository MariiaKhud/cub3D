/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:44:06 by tiyang            #+#    #+#             */
/*   Updated: 2025/11/24 10:48:07 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// checks if the file entered has valid extension type ".ber".
// the minimum file name length for a valid file is 5.
// returns 1 if the file type is valid.
int	is_ber_file(char *filename)
{
	int	len;

	len = (int)ft_strlen(filename);
	if (len < 5)
		return (0);
	if (!ft_strncmp(filename + len - 4, ".ber", 4))
		return (1);
	else
		return (0);
}

// counts how many lines there are in the map, in order to be able to 
// convert the map into a nul-terminated 2D array.
// returns -1 in case of error, returns the number of lines on success.
int	count_lines(char *filename)
{
	int		fd;
	int		line_count;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	line_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		line_count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (line_count);
}

// convert the map file into a malloc'd 2D character array 
// and load it into game.
// returns 1 on successful load and 0 on error.
// proceeds to map_validation.c to validate further map details.
int	load_map(char *filename, t_game *game)
{
	int		fd;
	int		line_count;
	int		i;

	line_count = count_lines(filename);
	if (line_count <= 0)
		return (0);
	game->map = malloc(sizeof(char *) * (line_count + 1));
	if (!game->map)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (free_matrix(game->map), 0);
	i = 0;
	while (i < line_count)
		game->map[i++] = get_next_line(fd);
	game->map[i] = NULL;
	close(fd);
	game->map_height = line_count;
	game->map_width = ft_strlen_without_newline(game->map[0]);
	return (1);
}
