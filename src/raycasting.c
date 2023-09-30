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
	camx = 2 * i / (double)(WIDTH - 1);
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
			if (v->step_x == 1)
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

void	draw_wall(t_game *game, t_vector *vector, int x)
{
	int	line_height;
	int	start;
	int	end;

	line_height	= (int)HEIGHT / vector->length;
	start = -line_height / 2 + HEIGHT / 2;
	if (start < 0)
		start = 0;
	end = line_height / 2 + HEIGHT / 2;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	while (end > start)
	{
		mlx_put_pixel(game->texture.render, x, start, WALL);
		start++;
	}
	
}

void	render_ray(t_game *game, t_vector *vector, int x)
{

	dda(game, vector);
	draw_wall(game, vector, x);
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
