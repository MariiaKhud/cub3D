/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:17:46 by makhudon          #+#    #+#             */
/*   Updated: 2025/12/04 14:20:32 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Checks if all necessary textures and colors have been set.
 * 
 * @param game Pointer to the game structure.
 * @param has_floor Flag indicating if floor color is set.
 * @param has_ceiling Flag indicating if ceiling color is set.
 * @return int 1 if all identifiers are set, 0 otherwise.
 */
static int	all_identifiers_set(t_game *game,
							int has_floor, int has_ceiling)
{
	if (!game->no_texture || !game->so_texture
		|| !game->we_texture || !game->ea_texture)
		return (0);
	if (!has_floor || !has_ceiling)
		return (0);
	return (1);
}

/**
 * @brief Trim trailing '\n' and spaces from a string (in-place).
 * 
 * @param s The string to trim.
 */
void	trim_trailing_whitespace(char *s)
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
 * @brief Sets texture or color based on the line identifier.
 * 
 * @param game Pointer to the game structure.
 * @param line The line to process.
 * @param has_floor Pointer to floor flag.
 * @param has_ceiling Pointer to ceiling flag.
 * @return 1 on success, 0 on error.
 */
static int	set_texture_or_color(t_game *game, char *line,
								int *has_floor, int *has_ceiling)
{
	char	*trimmed;
	int		res;

	trimmed = skip_spaces(line);
	if (*trimmed == '\0' || *trimmed == '\n' || *trimmed == '#')
		return (1);
	res = process_texture_id(game, trimmed);
	if (res == 1)
		return (1);
	if (res == 0)
		return (0);
	if ((trimmed[0] == 'F' || trimmed[0] == 'C')
		&& (trimmed[1] == ' ' || trimmed[1] == '\t'))
		return (set_color(game, trimmed, has_floor, has_ceiling));
	if (*trimmed == '1' || *trimmed == '0' || *trimmed == ' ')
		return (1);
	ft_printf("Error\nInvalid identifier: %s\n", line);
	return (0);
}

/**
 * @brief Parses texture and color information from the map file.
 * 
 * @param fd File descriptor of the map file.
 * @param game Pointer to the game structure.
 * @param has_floor Pointer to floor flag.
 * @param has_ceiling Pointer to ceiling flag.
 * @return int 0 on success, 1 on error.
 */
static int	parse_file_lines(int fd, t_game *game,
							int *has_floor, int *has_ceiling)
{
	char	*line;
	char	*trimmed;
	int		in_map;

	in_map = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		trimmed = skip_spaces(line);
		if (*trimmed == '\0' || *trimmed == '\n' || *trimmed == '#')
		{
			free(line);
			continue ;
		}
		if (*trimmed == '1' || *trimmed == '0' || *trimmed == ' ')
		{
			in_map = 1;
			free(line);
			continue ;
		}
		if (in_map)
		{
			free(line);
			continue ;
		}
		if (!set_texture_or_color(game, line, has_floor, has_ceiling))
		{
			free(line);
			while ((line = get_next_line(fd)) != NULL)
				free(line);
			return (1);
		}
		free(line);
	}
	return (0);
}

/**
 * @brief Parses all textures and colors from the map file.
 * 
 * @param filename Path to the map file.
 * @param game Game structure to populate.
 * @return 0 on success, 1 on error.
 */
int	parse_textures_and_colors(char *filename, t_game *game)
{
	int	fd;
	int	has_floor;
	int	has_ceiling;

	has_floor = 0;
	has_ceiling = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("Error: cannot open file %s\n", filename), 1);
	if (parse_file_lines(fd, game, &has_floor, &has_ceiling))
	{
		close(fd);
		return (1);
	}
	close(fd);
	if (!all_identifiers_set(game, has_floor, has_ceiling))
	{
		ft_printf("Error\nMissing identifiers (texture or color)\n");
		return (1);
	}
	if (validate_textures(game))
		return (1);
	return (0);
}
