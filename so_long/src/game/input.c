/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/30 16:43:58 by tiyang        #+#    #+#                 */
/*   Updated: 2025/11/24 10:20:09 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

// Handle Player Movement (W, A, S, D keys)
// Update new_player_x and new_player_y based on key pressed
// and update player sprite based on the direction of movement
void	handle_move(int keycode, t_game *game, int *player_x, int *player_y)
{
	if (keycode == KEY_W)
	{
		(*player_y)--;
		game->current_player_sprite = game->player_up_sprite;
	}
	else if (keycode == KEY_S)
	{
		(*player_y)++;
		game->current_player_sprite = game->player_down_sprite;
	}
	else if (keycode == KEY_A)
	{
		(*player_x)--;
		game->current_player_sprite = game->player_left_sprite;
	}
	else if (keycode == KEY_D)
	{
		(*player_x)++;
		game->current_player_sprite = game->player_right_sprite;
	}
}

int	touch_collectible(t_game *game, int new_player_x, int new_player_y)
{
	game->collectibles_collected++;
	game->map[new_player_y][new_player_x] = '0';
	ft_printf("Avocado collected! Total: %d/%d\n",
		game->collectibles_collected, game->total_collectibles);
	game->player_x = new_player_x;
	game->player_y = new_player_y;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
	render_map(game);
	return (0);
}

// how to handle image layering if the player walks onto the exit but has 
// not collected all the collectibles?
int	touch_exit(t_game *game, int new_player_x, int new_player_y)
{
	if (game->collectibles_collected == game->total_collectibles)
	{
		game->player_x = new_player_x;
		game->player_y = new_player_y;
		game->moves++;
		ft_printf("You reached the spaceship! All avocados gathered!\n");
		ft_printf("You win! Total moves: %d\n", game->moves);
		render_map(game);
		close_game(game, EXIT_SUCCESS);
		return (0);
	}
	else
	{
		game->player_x = new_player_x;
		game->player_y = new_player_y;
		game->moves++;
		ft_printf("Collect all avocados first! (%d/%d collected) Moves: %d\n",
			game->collectibles_collected, game->total_collectibles,
			game->moves);
		render_map(game);
		return (0);
	}
}

int	handle_interaction(char target, t_game *game, int target_x, int target_y)
{
	if (target == '1')
	{
		ft_printf("Cannot move into a wall!\n");
		render_map(game);
		return (0);
	}
	else if (target == 'E')
		return (touch_exit(game, target_x, target_y));
	else
		return (touch_collectible(game, target_x, target_y));
}

// this function is the callback for keyboard presses.
// it takes in the code for the key that was pressed
// and alters the state of the game status accordingly.
int	handle_keypress(int keycode, t_game *game)
{
	int		new_player_x;
	int		new_player_y;
	char	target;

	if (keycode == KEY_ESC)
		close_game(game, EXIT_SUCCESS);
	new_player_x = game->player_x;
	new_player_y = game->player_y;
	if (keycode == KEY_A || keycode == KEY_D || keycode == KEY_S
		|| keycode == KEY_W)
		handle_move(keycode, game, &new_player_x, &new_player_y);
	else
		return (0);
	target = game->map[new_player_y][new_player_x];
	if (target == '1' || target == 'E' || target == 'C')
		return (handle_interaction(target, game, new_player_x, new_player_y));
	game->player_x = new_player_x;
	game->player_y = new_player_y;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
	render_map(game);
	return (0);
}
