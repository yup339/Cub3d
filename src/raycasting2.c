/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:35:50 by pbergero          #+#    #+#             */
/*   Updated: 2023/10/14 23:04:05 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_wall(t_game *game, t_vector *vector, int x, mlx_texture_t *tex)
{
	t_wall	w;

	calc_wall_height(&w, vector, tex);
	while (w.i < w.end)
	{
		w.tex_y = w.tex_pos;
		w.tex_pos += w.step;
		w.color = &tex->pixels[(((tex->height * w.tex_y) + w.tex_x) * 4)];
		w.pixel = rgba(w.color[0], w.color[1], w.color[2], w.color[3]);
		mlx_put_pixel(game->texture.render, x, w.i, w.pixel);
		w.i++;
	}
}

mlx_texture_t	*texture_picker(t_vector *vector, t_game *game)
{
	if (vector->side == NORTH)
		return (game->texture.north);
	else if (vector->side == SOUTH)
		return (game->texture.south);
	else if (vector->side == WEST)
		return (game->texture.west);
	else
		return (game->texture.east);
}

void	render_ray(t_game *game, t_vector *vector, int x)
{
	mlx_texture_t	*tex;

	dda(game, vector);
	tex = texture_picker(vector, game);
	draw_wall(game, vector, x, tex);
}

/// @brief create the render using raycast sending one ray per pixel
void	raycast(t_game *game)
{
	int			x;
	t_vector	ray;

	x = 0;
	while (x < WIDTH)
	{
		ray = create_ray(game, x);
		render_ray(game, &ray, x);
		x++;
	}
}
