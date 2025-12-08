/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap_line.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/01 10:39:59 by tiyang        #+#    #+#                 */
/*   Updated: 2025/12/08 13:26:46 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Initializes the deltas and steps for Bresenham's line algorithm.
 * 
 * @param line The line structure to initialize.
 */
static void	init_line_deltas(t_line *line)
{
	line->dx = abs(line->x1 - line->x0);
	line->dy = abs(line->y1 - line->y0);
	if (line->x0 < line->x1)
		line->sx = 1;
	else
		line->sx = -1;
	if (line->y0 < line->y1)
		line->sy = 1;
	else
		line->sy = -1;
	line->err = line->dx - line->dy;
}

/**
 * @brief Draws a single step of the line using Bresenham's algorithm.
 * 
 * @param game The game structure containing the minimap image.
 * @param line The line structure with current position and deltas.
 * @param color The color to draw the pixel.
 */
static void	draw_line_step(t_game *game, t_line *line, int color)
{
	int	e2;

	my_mlx_pixel_put(game, line->x0, line->y0, color);
	e2 = 2 * line->err;
	if (e2 > -(line->dy))
	{
		line->err -= line->dy;
		line->x0 += line->sx;
	}
	if (e2 < line->dx)
	{
		line->err += line->dx;
		line->y0 += line->sy;
	}
}

/**
 * @brief Draws a line on the minimap using Bresenham's algorithm.
 * 
 * @param game The game structure containing the minimap image.
 * @param line The line structure with start and end coordinates.
 * @param color The color to draw the line.
 */
void	draw_mm_line(t_game *game, t_line *line, int color)
{
	while (1)
	{
		draw_line_step(game, line, color);
		if (line->x0 == line->x1 && line->y0 == line->y1)
			break ;
	}
}

/**
 * @brief Initializes a line structure and draws the line on the minimap.
 * 
 * @param game The game structure containing the minimap image.
 * @param coords An array of 4 integers: [x0, y0, x1, y1].
 * @param color The color to draw the line.
 */
void	init_and_draw_line(t_game *game, int coords[4], int color)
{
	t_line	line;

	line.x0 = coords[0];
	line.y0 = coords[1];
	line.x1 = coords[2];
	line.y1 = coords[3];
	init_line_deltas(&line);
	draw_mm_line(game, &line, color);
}
