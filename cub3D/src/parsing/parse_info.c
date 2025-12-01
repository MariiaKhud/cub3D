/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:17:46 by makhudon          #+#    #+#             */
/*   Updated: 2025/12/01 13:51:41 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Checks if all necessary textures and colors have been set.
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
 * @brief Parses a line to set textures, colors, or validate map content.
 * Skips empty lines or comments. Sets textures for "NO", "SO", "WE", "EA",
 * sets floor/ceiling colors for 'F'/'C', and ignores map layout lines. 
 * Prints an error for invalid identifiers or duplicate textures.
 */
static int	set_texture_or_color(t_game *game, char *line,
								int *has_floor, int *has_ceiling)
{
	char	*trimmed;

	trimmed = skip_spaces(line);
	if (*trimmed == '\0' || *trimmed == '\n' || *trimmed == '#')
		return (1);
	if (is_id(trimmed, "NO"))
	{
		if (game->no_texture)
		{
			ft_printf("Error\nDuplicate texture identifier\n");
			return (0);
		}
		set_texture(game, trimmed);
		return (1);
	}
	if (is_id(trimmed, "SO"))
	{
		if (game->so_texture)
		{
			ft_printf("Error\nDuplicate texture identifier\n");
			return (0);
		}
		set_texture(game, trimmed);
		return (1);
	}
	if (is_id(trimmed, "WE"))
	{
		if (game->we_texture)
		{
			ft_printf("Error\nDuplicate texture identifier\n");
			return (0);
		}
		set_texture(game, trimmed);
		return (1);
	}
	if (is_id(trimmed, "EA"))
	{
		if (game->ea_texture)
		{
			ft_printf("Error\nDuplicate texture identifier\n");
			return (0);
		}
		set_texture(game, trimmed);
		return (1);
	}
	if ((trimmed[0] == 'F' || trimmed[0] == 'C')
		&& (trimmed[1] == ' ' || trimmed[1] == '\t'))
		return (set_color(game, trimmed, has_floor, has_ceiling));
	if (*trimmed == '1' || *trimmed == '0' || *trimmed == ' ')
		return (1);
	ft_printf("Error\nInvalid identifier: %s\n", line);
	return (0);
}

/**
 * @brief Reads the file line by line and sets textures or colors.
 * 
 * @param fd File descriptor of the opened map file.
 * @param game Game structure to populate.
 * @param has_floor Pointer to a flag for floor color.
 * @param has_ceiling Pointer to a flag for ceiling color.
 * @return 0 on success, 1 on error.
 */
static int	parse_file_lines(int fd, t_game *game, int *has_floor,
													int *has_ceiling)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (*line)
		{
			if (!set_texture_or_color(game, line, has_floor, has_ceiling))
			{
				free(line);
				line = get_next_line(fd);
				while (line != NULL)
				{
					free(line);
					line = get_next_line(fd);
				}
				return (1);
			}
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
