#include "cub.h"
#include "fcntl.h"

/// @brief create the ray use for redering base on the fov ,
/// width of the game and wich column needed to be rendered
t_vector	create_ray(t_game *game, int i)
{
	t_vector	v;

	v.start_x = game->player.x;
	v.start_y = game->player.y;
	v.angle = (fmod((double)((game->player.cam - (FOV / 2)) + (i * FOV / WIDTH)) + 360, 360));
	return (v);
}

void	calculate_wall_height(t_vector *ray, t_game *game,
	u_int32_t *wall_height, u_int32_t *wall_starting_position)
{
	*wall_height = WALL_HEIGHT / (ray->length
			* cos(angle_to_rad(ray->angle) - angle_to_rad(game->player.cam)));
	*wall_starting_position = (HEIGHT / 2) - (*wall_height / 2);
}

void	render_ray(t_game *game, t_vector *vector, int x)
{
	u_int32_t	wall_height;
	u_int32_t	wall_starting_position;

	vector_collision(game, vector, vector->start_x, vector->start_y);
	calculate_wall_height(vector, game, &wall_height, &wall_starting_position);

	while (wall_height)
	{
		if (wall_height + wall_starting_position < HEIGHT)
			mlx_put_pixel(game->texture.render, x,
				wall_height + wall_starting_position, WALL);
		wall_height--;
	}
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
