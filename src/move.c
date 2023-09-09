#include "cub.h"

void	change_rotation(t_game *game)
{
	if (game->player.rotation & LEFT)
		game->player.cam = ((int)game->player.cam - ROTATION_SPEED + 360) % 360;
	if (game->player.rotation & RIGHT)
		game->player.cam = ((int)game->player.cam + ROTATION_SPEED + 360) % 360;
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
	vector.end_x = vector.start_x + SPEED * 3 * cos(vector.angle);
	vector.end_y = vector.start_y - (SPEED * 3 * sin(vector.angle));
	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			printf("map :%d,%d = %c\n",j,i,game->map[i][j]);
			printf("collision :%f,%f\n",vector.end_x,vector.end_y);
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

void	translate_player(t_game *game, int angle)
{
	game->player.x = game->player.x + (SPEED * cos(angle * M_PI / 180));
	game->player.y = game->player.y + (SPEED * sin(angle * M_PI / 180));
}

void	move_player(t_game *game)
{
	if (game->player.direction & FORWARD && !(game->player.direction & BACKWARD)
		&& !collision_ray(game, game->player.cam))
		translate_player(game, game->player.cam);
	if (game->player.direction & BACKWARD && !(game->player.direction & FORWARD)
		&& !collision_ray(game, game->player.cam + 180 % 360))
		translate_player(game, game->player.cam + 180 % 360);
	if (game->player.direction & RIGHT && !(game->player.direction & LEFT)
		&& !collision_ray(game, game->player.cam + 90 % 360))
		translate_player(game, game->player.cam + 90 % 360);
	if (game->player.direction & LEFT && !(game->player.direction & RIGHT)
		&& !collision_ray(game, game->player.cam + 270 % 360))
		translate_player(game, game->player.cam + 270 % 360);
	if (game->player.direction)
		printf("x:%f, y:%f\n",game->player.x, game->player.y);
}
