/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:44:06 by tiyang            #+#    #+#             */
/*   Updated: 2025/11/24 13:00:47 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Loads the map from a .ber file into the game structure.
 * @param filename The name of the .ber file containing the map.
 * @param game Pointer to the game structure where the map will be stored.
 * @return int Returns 1 on success, otherwise returns 0 on failure.
 */
int	parse_map_file(char *filename, t_game *game)
{
	int		fd;
	char	*line;
	int		map_start;
	int		i;

	i = 0;
	map_start = 0; // flag to know when map begins
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	game->map = malloc(sizeof(char *) * 1024); // temp, will realloc later
	if (!game->map)
		return (0);
	while ((line = get_next_line(fd)))
	{
		if (*line == '\n' || *line == '\0')
		{
			free(line);
			continue;
		}
		if (map_start == 0 && line[0] == '1')
			map_start = 1;
		if (map_start == 1)
		{
			if (line[ft_strlen(line) - 1] == '\n')
				line[ft_strlen(line) - 1] = '\0';
			game->map[i++] = line;
		}
		else
		{
			free(line);
		}
	}
	game->map[i] = NULL;
	close(fd);
	game->map_height = i;
	if (i > 0)
		game->map_width = ft_strlen_without_newline(game->map[0]);
	else
		game->map_width = 0;
	return (i > 0);
}

/**
 * @brief Checks if the given filename has a .ber or .cub extension.
 * @param filename The name of the file to check.
 * @return int Returns 1 if the file has a .ber or .cub extension, otherwise returns 0.
 */
int	is_cub_file(char *filename)
{
	int len;

	len = (int)ft_strlen(filename);
	if (len < 5)
		return (0);
	if (!ft_strncmp(filename + len - 4, ".ber", 4) || 
	    !ft_strncmp(filename + len - 4, ".cub", 4))
		return (1);
	return (0);
}

