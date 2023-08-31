#include "cub.h"

void	draw_x_vector(t_game *game, t_vector vector, int x, int y)
{
	if (x <= vector.end_x)
	{
		while (x <= vector.end_x)
		{
			y = vector.end_y + (x - vector.end_x)
				* (vector.start_y - vector.end_y)
				/ (vector.start_x - vector.end_x);
			if (x > 0 && x < MINIMAP_WIDTH && y > 0 && y < MINIMAP_HEIGHT)
				mlx_put_pixel(game->texture.minimap, x, y, MAP_FOV_COLOR);
			x++;
		}
	}
	else
	{
		while (x >= vector.end_x)
		{
			y = vector.end_y + (x - vector.end_x)
				* (vector.start_y - vector.end_y)
				/ (vector.start_x - vector.end_x);
			if (x > 0 && x < MINIMAP_WIDTH && y > 0 && y < MINIMAP_HEIGHT)
				mlx_put_pixel(game->texture.minimap, x, y, MAP_FOV_COLOR);
			x--;
		}
	}
}

void	draw_y_vector(t_game *game, t_vector vector, int x, int y)
{
	if (y >= vector.end_y)
	{
		while (y >= vector.end_y)
		{
			x = vector.end_x + (y - vector.end_y)
				* (vector.start_x - vector.end_x)
				/ (vector.start_y - vector.end_y);
			if (x > 0 && x < MINIMAP_WIDTH && y > 0 && y < MINIMAP_HEIGHT)
				mlx_put_pixel(game->texture.minimap, x, y, MAP_FOV_COLOR);
			y--;
		}
	}
	else
	{
		while (y <= vector.end_y)
		{
			x = vector.end_x + (y - vector.end_y)
				* (vector.start_x - vector.end_x)
				/ (vector.start_y - vector.end_y);
			if (x > 0 && x < MINIMAP_WIDTH && y > 0 && y < MINIMAP_HEIGHT)
				mlx_put_pixel(game->texture.minimap, x, y, MAP_FOV_COLOR);
			y++;
		}
	}
}
