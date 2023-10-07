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

void	render_ray(t_game *game, t_vector *vector, int x)
{
	mlx_texture_t	*tex;

	dda(game, vector);
	if (vector->side == NORTH)
		tex = game->texture.north;
	else if (vector->side == SOUTH)
		tex = game->texture.south;
	else if (vector->side == WEST)
		tex = game->texture.west;
	else
		tex = game->texture.east;
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
