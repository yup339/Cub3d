#include "cub.h"

bool	vector_hits_wall(double x, double y, double map_x, double map_y)
{
	if (x >= map_x - 0.05 && x <= map_x + 1.05
		&& y >= map_y - 0.05 && y <= map_y + 1.05)
		return (true);
	return (false);
}

/*looks for collision threw the map and update the vector with new info*/
bool	vector_collision(t_game *game, t_vector *vector, double x, double y)
{
	int	i;
	int	j;

	while (x >= 0 && x < game->width && y >= 0 && y < game->height)
	{
		i = 0;
		while (game->map[i])
		{
			j = 0;
			while (game->map[i][j])
			{
				if (game->map[i][j] == '1' && vector_hits_wall(x, y, j, i))
					return (true);
				j++;
			}
			i++;
		}
		x += RAY_SPEED * cos(vector->angle * M_PI / 180);
		y += RAY_SPEED * sin(vector->angle * M_PI / 180);
		vector->end_x = x;
		vector->end_y = y;
		vector->length += RAY_SPEED;
	}
	return (false);
}
