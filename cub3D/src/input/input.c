/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makhudon <makhudon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 12:38:02 by makhudon          #+#    #+#             */
/*   Updated: 2025/11/26 09:28:00 by makhudon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#define MOVE_SPEED 0.08
#define ROT_SPEED 0.05

/* ----------- COLLISION DETECTION ----------- */
static int	can_move(t_game *g, double newY, double newX)
{
	int	x;
	int	y;
	int	row_len;

	y = (int)newY;
	x = (int)newX;
	if (y < 0 || y >= g->map_height)
		return (0);
	row_len = (int)ft_strlen(g->map[y]);
	if (x < 0 || x >= row_len)
		return (0);
	if (g->map[y][x] == '1' || g->map[y][x] == ' ')
		return (0);
	return (1);
}

/* ----------- MOVE FORWARD / BACKWARD (W / S) ----------- */
static void move_forward(t_game *g)
{
    double newX = g->posX + g->dirX * MOVE_SPEED;
    double newY = g->posY + g->dirY * MOVE_SPEED;

    if (can_move(g, g->posY, newX))
        g->posX = newX;
    if (can_move(g, newY, g->posX))
        g->posY = newY;
}

static void move_backward(t_game *g)
{
    double newX = g->posX - g->dirX * MOVE_SPEED;
    double newY = g->posY - g->dirY * MOVE_SPEED;

    if (can_move(g, g->posY, newX))
        g->posX = newX;
    if (can_move(g, newY, g->posX))
        g->posY = newY;
}

/* ----------- STRAFE LEFT / RIGHT (A / D) ----------- */
static void move_left(t_game *g)
{
    double newX = g->posX - g->dirY * MOVE_SPEED;
    double newY = g->posY + g->dirX * MOVE_SPEED;

    if (can_move(g, g->posY, newX))
        g->posX = newX;
    if (can_move(g, newY, g->posX))
        g->posY = newY;
}

static void move_right(t_game *g)
{
    double newX = g->posX + g->dirY * MOVE_SPEED;
    double newY = g->posY - g->dirX * MOVE_SPEED;

    if (can_move(g, g->posY, newX))
        g->posX = newX;
    if (can_move(g, newY, g->posX))
        g->posY = newY;
}

/* ----------- ROTATION (LEFT / RIGHT ARROWS) ----------- */
static void rotate_left(t_game *g)
{
    double oldDirX = g->dirX;
    double oldPlaneX = g->planeX;

    g->dirX = g->dirX * cos(ROT_SPEED) - g->dirY * sin(ROT_SPEED);
    g->dirY = oldDirX * sin(ROT_SPEED) + g->dirY * cos(ROT_SPEED);

    g->planeX = g->planeX * cos(ROT_SPEED) - g->planeY * sin(ROT_SPEED);
    g->planeY = oldPlaneX * sin(ROT_SPEED) + g->planeY * cos(ROT_SPEED);
}

static void rotate_right(t_game *g)
{
    double oldDirX = g->dirX;
    double oldPlaneX = g->planeX;

    g->dirX = g->dirX * cos(-ROT_SPEED) - g->dirY * sin(-ROT_SPEED);
    g->dirY = oldDirX * sin(-ROT_SPEED) + g->dirY * cos(-ROT_SPEED);

    g->planeX = g->planeX * cos(-ROT_SPEED) - g->planeY * sin(-ROT_SPEED);
    g->planeY = oldPlaneX * sin(-ROT_SPEED) + g->planeY * cos(-ROT_SPEED);
}

/* ----------- KEY PRESS HANDLER ----------- */

int	handle_keypress(int key, t_game *g)
{
	if (key == KEY_ESC)
		close_game(g, EXIT_SUCCESS);
	else if (key == KEY_W)
		move_forward(g);
	else if (key == KEY_S)
		move_backward(g);
	else if (key == KEY_A)
		move_left(g);
	else if (key == KEY_D)
		move_right(g);
	else if (key == KEY_LEFT)
		rotate_left(g);
	else if (key == KEY_RIGHT)
		rotate_right(g);

	render_map(g); // 🔹 Important: redraw the screen
	return (0);
}

