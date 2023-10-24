/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:35:18 by pbergero          #+#    #+#             */
/*   Updated: 2023/10/24 14:44:38 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/// @brief create the ray use for redering base on the fov ,
/// width of the game and wich column needed to be rendered

void	set_step(t_vector	*v)
{
	if (v->dx > 0)
	{
		v->side_dist_x = (v->end_x + 1 - v->start_x) * v->delta_dist_x;
		v->step_x = 1;
	}
	else
	{
		v->side_dist_x = (v->start_x - v->end_x) * v->delta_dist_x;
		v->step_x = -1;
	}
	if (v->dy > 0)
	{
		v->side_dist_y = (v->end_y + 1 - v->start_y) * v->delta_dist_y;
		v->step_y = 1;
	}
	else
	{
		v->side_dist_y = (v->start_y - v->end_y) * v->delta_dist_y;
		v->step_y = -1;
	}
}

t_vector	create_ray(t_game *game, int i)
{
	t_vector	v;
	double		camx;

	v.start_x = game->player.x;
	v.start_y = game->player.y;
	v.end_x = (int)game->player.x;
	v.end_y = (int)game->player.y;
	camx = 2 * i / (double)WIDTH - 1;
	v.dx = game->player.dx + game->plane_x * camx;
	v.dy = game->player.dy + game->plane_y * camx;
	v.delta_dist_x = fabs(1 / v.dx);
	v.delta_dist_y = fabs(1 / v.dy);
	set_step(&v);
	return (v);
}

void	dda(t_game *game, t_vector *v)
{
	while (true)
	{
		if (v->side_dist_x < v->side_dist_y)
		{
			v->side_dist_x += v->delta_dist_x;
			v->end_x += v->step_x;
			v->side = WEST;
			if (v->step_x == 1)
				v->side = EAST;
		}
		else
		{
			v->side_dist_y += v->delta_dist_y;
			v->end_y += v->step_y;
			v->side = NORTH;
			if (v->step_y == 1)
				v->side = SOUTH;
		}
		if (game->map[(int)v->end_x][(int)v->end_y] == '1')
			break ;
	}
	if (v->side == NORTH || v->side == SOUTH)
		v->length = (v->side_dist_y - v->delta_dist_y);
	else
		v->length = (v->side_dist_x - v->delta_dist_x);
}

/// @param r,g,b,a the component of rgba colors
/// @brief apply bitshift to get the right color
int	rgba(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

void	calc_wall_height(t_wall	*w, t_vector *vector, mlx_texture_t *tex)
{
	w->line_height = (int)HEIGHT / vector->length * WALL_HEIGHT;
	w->start = -w->line_height / 2 + HEIGHT / 2;
	if (w->start < 0)
		w->start = 0;
	w->end = w->line_height / 2 + HEIGHT / 2;
	if (w->end >= HEIGHT)
		w->end = HEIGHT - 1;
	w->step = 1.0 * tex->height / w->line_height;
	if (vector->side == EAST || vector->side == WEST)
		w->wallx = vector->start_y + vector->length * vector->dy;
	else
		w->wallx = vector->start_x + vector->length * vector->dx;
	w->wallx -= floor((w->wallx));
	w->tex_x = (int)(w->wallx * (double)tex->width);
	if (vector->side == EAST || vector->side == NORTH)
		w->tex_x = tex->width - w->tex_x - 1;
	w->tex_pos = (w->start - HEIGHT / 2 + w->line_height / 2) * w->step;
	w->i = w->start;
}
