/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:35:36 by pbergero          #+#    #+#             */
/*   Updated: 2023/10/23 14:00:53 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/// @brief main loop of the game 
/// @param ptr game pointer toward the main struct
void	game_loop(void *ptr)
{
	t_game	*game;

	game = (t_game *)ptr;
	ft_memset(game->texture.render->pixels, 0,
		(HEIGHT) * (WIDTH) * sizeof(int32_t));
	raycast(game);
	change_rotation(game);
	move_player(game);
}

void	key_loop2(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		free_game(game, true, true);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		game->player.direction |= FORWARD;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		game->player.direction |= LEFT;
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		game->player.direction |= BACKWARD;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		game->player.direction |= RIGHT;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		game->player.direction &= ~FORWARD;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		game->player.direction &= ~LEFT;
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		game->player.direction &= ~BACKWARD;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		game->player.direction &= ~RIGHT;
}

void	key_loop(mlx_key_data_t keydata, void *ptr)
{
	t_game		*game;

	game = (t_game *)ptr;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		game->player.rotation |= LEFT;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		game->player.rotation |= RIGHT;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		game->player.rotation &= ~LEFT;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		game->player.rotation &= ~RIGHT;
	if (keydata.key == MLX_KEY_TAB && keydata.action == MLX_PRESS
		&& game->cursor == false)
	{
		mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
		game->cursor = true;
	}
	else if (keydata.key == MLX_KEY_TAB && keydata.action == MLX_PRESS
		&& game->cursor == true)
	{
		mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
		game->cursor = false;
	}
	key_loop2(keydata, game);
}

void	cursor_hook_function(double x, double y, void *ptr)
{
	t_game			*game;
	static double	previous_x = 0;

	game = (t_game *)ptr;
	if (game->cursor == true)
		return ;
	(void)y;
	rotate_player_vector(game, -angle_to_rad((x - previous_x) * SENSITIVITY));
	previous_x = x;
}

void	run_game(t_game *game)
{
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_cursor_hook(game->mlx, &cursor_hook_function, game);
	mlx_key_hook(game->mlx, &key_loop, game);
	mlx_close_hook(game->mlx, close_game, game);
	mlx_loop(game->mlx);
}
