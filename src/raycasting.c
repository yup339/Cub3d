#include "cub.h"
#include "fcntl.h"

/// @brief create the ray use for redering base on the fov ,
/// width of the game and wich column needed to be rendered
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
	v.delta_dist_x = fabs(1/v.dx);
	v.delta_dist_y = fabs(1/v.dy);
	//v.angle = (fmod((double)((game->player.cam - (FOV / 2)) + (i * FOV / WIDTH)) + 360, 360));
	if (v.dx > 0)
	{
		v.side_dist_x = (v.end_x + 1 - v.start_x) * v.delta_dist_x;
		v.step_x = 1;
	}
	else
	{
		v.side_dist_x = (v.start_x - v.end_x) * v.delta_dist_x;
		v.step_x = -1;
	}
	if (v.dy > 0)
	{
		v.side_dist_y = (v.end_y + 1 - v.start_y) * v.delta_dist_y;
		v.step_y = 1;
	}
	else
	{
		v.side_dist_y = (v.start_y - v.end_y) * v.delta_dist_y;
		v.step_y = -1;
	}
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

int	rgba(int r, int g, int b, int a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

void	draw_wall(t_game *game, t_vector *vector, int x, mlx_texture_t *tex)
{
	int				line_height;
	int				start;
	int				end;
	uint8_t			*color;
	int				pixel;
	double			step;
	double			wallx;
	int				tex_x;
	int				tex_y;
	double 			tex_pos;
	int				i;

	line_height = (int)HEIGHT / vector->length * (0.6);
	start = -line_height / 2 + HEIGHT / 2;
	if (start < 0)
		start = 0;
	end = line_height / 2 + HEIGHT / 2;
	if (end >= HEIGHT)
		end = HEIGHT - 1;

	//texture calc x
	step = 1.0 * tex->height / line_height;
	if (vector->side == EAST || vector->side == WEST)
		wallx = vector->start_y + vector->length * vector->dy;
	else
		wallx = vector->start_x + vector->length * vector->dx;
	wallx -= floor((wallx));
	tex_x = (int)(wallx * (double)tex->width);
	if (vector->side == EAST || vector->side == NORTH)
		tex_x = tex->width - tex_x - 1;
	//texture y
	step = 1.0 * tex->height / line_height;
	tex_pos = (start - HEIGHT / 2 + line_height / 2) * step;

	i = start;

	while (i < end)
	{
		tex_y = tex_pos;
		tex_pos += step;
		color = &tex->pixels[(((tex->height * tex_y) + tex_x) * 4)];
		pixel = rgba(color[0], color[1], color[2], color[3]);
		mlx_put_pixel(game->texture.render, x, i, pixel);
		i++;
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
