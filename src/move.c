#include "cub.h"

void	rotate_player_vector(t_game *game, double angle)
{
	double	old_dx;
	double	old_planex;

	old_dx = game->player.dx;
	old_planex = game->plane_x;
	game->player.dx = game->player.dx * cos(angle) - game->player.dy * sin(angle);
	game->player.dy = old_dx * sin(angle) + game->player.dy * cos(angle);
	game->plane_x = game->plane_x * cos(angle) - game->plane_y * sin(angle);
	game->plane_y = old_planex * sin(angle) + game->plane_y * cos(angle);
}

void	change_rotation(t_game *game)
{
	if (game->player.rotation & LEFT)
	{
		rotate_player_vector(game, angle_to_rad(-ROTATION_SPEED));
		game->player.cam = fmod(game->player.cam - ROTATION_SPEED + 360, 360);
	}
	if (game->player.rotation & RIGHT)
	{
		rotate_player_vector(game, angle_to_rad(ROTATION_SPEED));
		game->player.cam = fmod(game->player.cam + ROTATION_SPEED + 360, 360);
	}
	if (game->player.rotation)
		printf("cam = %d°\n",(int)game->player.cam);
}

bool	collision_ray(t_game *game, int	angle)
{
	t_vector	vector;
	int			i;
	int			j;

	vector.angle = angle;
	vector.start_x = game->player.x;
	vector.start_y = game->player.y;
	vector.end_x = vector.start_x + SPEED * cos(vector.angle * M_PI / 180);
	vector.end_y = vector.start_y + SPEED * sin(vector.angle * M_PI / 180);
	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			//printf("map :%d,%d = %c\n",j,i,game->map[i][j]);
			//printf("collision :%f,%f\n",vector.end_x,vector.end_y);
			if (game->map[i][j] == '1' && vector_hits_wall(vector.end_x, vector.end_y , j, i))
			{
				return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
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
	if (game->map[(int)(game->player.x)][(int)(game->player.y - (v.dy * SPEED))] != '1')
	{
		game->player.y -= (v.dy * SPEED);
	}
	if (game->map[(int)(game->player.x - (v.dx * SPEED))][(int)(game->player.y)] != '1')
	{
		game->player.x -= (v.dx * SPEED);
	}
}

void	move_player(t_game *game)
{
	if (game->player.direction & FORWARD && !(game->player.direction & BACKWARD))
		translate_player(game, 180);
	if (game->player.direction & BACKWARD && !(game->player.direction & FORWARD))
		translate_player(game, 0);
	if (game->player.direction & RIGHT && !(game->player.direction & LEFT))
		translate_player(game, 90);
	if (game->player.direction & LEFT && !(game->player.direction & RIGHT))
		translate_player(game, 270);
	if (game->player.direction)
		printf("x:%f, y:%f\n",game->player.x, game->player.y);
}
