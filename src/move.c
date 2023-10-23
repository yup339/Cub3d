/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:35:43 by pbergero          #+#    #+#             */
/*   Updated: 2023/10/23 16:58:20 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	rotate_player_vector(t_game *game, double angle)
{
	double	old_dx;
	double	old_planex;

	old_dx = game->player.dx;
	old_planex = game->plane_x;
	game->player.dx
		= game->player.dx * cos(angle) - game->player.dy * sin(angle);
	game->player.dy = old_dx * sin(angle) + game->player.dy * cos(angle);
	game->plane_x = game->plane_x * cos(angle) - game->plane_y * sin(angle);
	game->plane_y = old_planex * sin(angle) + game->plane_y * cos(angle);
}

void	change_rotation(t_game *game)
{
	if (game->player.rotation & LEFT)
	{
		rotate_player_vector(game, angle_to_rad(ROTATION_SPEED));
		game->player.cam = fmod(game->player.cam + ROTATION_SPEED + 360, 360);
	}
	if (game->player.rotation & RIGHT)
	{
		rotate_player_vector(game, angle_to_rad(-ROTATION_SPEED));
		game->player.cam = fmod(game->player.cam - ROTATION_SPEED + 360, 360);
	}
}

t_mini_vec	rotate_vector(double dx, double dy, double angles)
{
	t_mini_vec	v;
	double		angle;

	angle = angle_to_rad(angles);
	v.dx = dx * cos(angle) - dy * sin(angle);
	v.dy = dx * sin(angle) + dy * cos(angle);
	return (v);
}

void	translate_player(t_game *game, int angle)
{
	t_mini_vec	v;

	v = rotate_vector(game->player.dx, game->player.dy, angle);
	if (game->map[(int)(game->player.x)]
		[(int)(game->player.y - (v.dy * SPEED))] != '1')
	{
		game->player.y -= (v.dy * SPEED);
	}
	if (game->map[(int)(game->player.x - (v.dx * SPEED))]
		[(int)(game->player.y)] != '1')
	{
		game->player.x -= (v.dx * SPEED);
	}
}

void	move_player(t_game *game)
{
	if (game->player.direction & FORWARD
		&& !(game->player.direction & BACKWARD))
		translate_player(game, 180);
	if (game->player.direction & BACKWARD
		&& !(game->player.direction & FORWARD))
		translate_player(game, 0);
	if (game->player.direction & RIGHT && !(game->player.direction & LEFT))
		translate_player(game, 90);
	if (game->player.direction & LEFT && !(game->player.direction & RIGHT))
		translate_player(game, 270);
}
