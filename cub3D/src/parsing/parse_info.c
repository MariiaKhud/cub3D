/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_info.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/24 11:17:46 by makhudon      #+#    #+#                 */
/*   Updated: 2025/12/08 10:26:31 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	ft_printf("Error\nInvalid identifier: %s", line);
	return (0);
}

/** 
 * @brief Handles identifiers or errors in a line.
 * 
 * @param game Pointer to the game structure.
 * @param line The line to process.
 * @param st Pointer to the parse state structure.
 * @return int 0 to continue, -1 on error.
 */
static int	handle_identifier_or_error(t_game *game, char *line,
					t_parse_state *st)
{
	char	*trimmed;

	trimmed = skip_spaces(line);
	if (*trimmed == '\0' || *trimmed == '\n' || *trimmed == '#')
		return (0);
	if (*trimmed == '1' || *trimmed == '0' || *trimmed == ' ')
	{
		st->in_map = 1;
		return (0);
	}
	if (st->in_map && (*trimmed == 'N' || *trimmed == 'S'
			|| *trimmed == 'W' || *trimmed == 'E'
			|| *trimmed == 'F' || *trimmed == 'C'))
	{
		ft_printf("Error\nInvalid identifier order\n");
		return (-1);
	}
	if (!st->in_map)
	{
		if (!set_texture_or_color(game, line,
				&st->has_floor, &st->has_ceiling))
			return (-1);
	}
	return (0);
}

/** 
 * @brief Reads the next line from the file descriptor.
 * 
 * @param fd File descriptor to read from.
 * @param line Pointer to store the read line.
 * @return int 1 if a line was read, 0 on EOF.
 */
static int	read_next_line(int fd, char **line)
{
	*line = get_next_line(fd);
	if (*line == NULL)
		return (0);
	return (1);
}

/** 
 * @brief Parses the file lines for textures and colors.
 * 
 * @param fd File descriptor of the opened map file.
 * @param game Pointer to the game structure.
 * @param has_floor Pointer to floor flag.
 * @param has_ceiling Pointer to ceiling flag.
 * @return int 0 on success, 1 on error.
 */
static int	parse_file_lines(int fd, t_game *game,
				int *has_floor, int *has_ceiling)
{
	char			*line;
	t_parse_state	st;
	int				result;

	st.has_floor = *has_floor;
	st.has_ceiling = *has_ceiling;
	st.in_map = 0;
	while (read_next_line(fd, &line))
	{
		result = handle_identifier_or_error(game, line, &st);
		if (result == -1)
		{
			free(line);
			while (read_next_line(fd, &line))
				free(line);
			return (1);
		}
		free(line);
	}
	*has_floor = st.has_floor;
	*has_ceiling = st.has_ceiling;
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
