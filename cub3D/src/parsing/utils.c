/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:29:46 by tiyang            #+#    #+#             */
/*   Updated: 2025/11/24 10:48:14 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// adjusted ft_strlen function that does not count the newline character at the
// end of the string as part of the length, in order to correctly validate if 
// the map is rectangular.
int	ft_strlen_without_newline(char *line)
{
	int	len;

	if (!line)
		return (0);
	len = (int)ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		return (len - 1);
	return (len);
}

// checks if each row in the map has the same length, returns 1 if true
int	is_rectangular(char **map, int line_count)
{
	int	init_length;
	int	i;
	int	line_length;

	if (!map || !map[0] || line_count <= 0)
		return (0);
	if (line_count == 1)
		return (1);
	init_length = ft_strlen_without_newline(map[0]);
	i = 1;
	while (i < line_count)
	{
		line_length = ft_strlen_without_newline(map[i]);
		if (line_length != init_length)
			return (0);
		i++;
	}
	return (1);
}

// create a copy of the map using malloc. 
// The caller needs to free memory.
char	**copy_map(t_game *game)
{
	char	**map_copy;
	int		i;

	map_copy = malloc(sizeof(char *) * (game->map_height + 1));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < game->map_height)
	{
		map_copy[i] = ft_strdup(game->map[i]);
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

// safely frees a nul-terminated 2D character array
void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix && matrix[i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
	matrix = NULL;
}
