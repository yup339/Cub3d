#include "cub.h"

void	print_vector(t_vector	*vector)
{
	printf("vector:%d°  [%f][%f]\n",(int)vector->angle,vector->start_x, vector->end_x);
	printf("            [%f][%f]\n",vector->start_y, vector->end_y);
}

static void	draw_minimap_fov(t_game	*game)
{
	t_vector	vector;
	int	i;

	i = 0;
	vector.angle = ((int)game->player.cam - (FOV / 2) + 360) % 360;
	while (i++ < NBR_MINIRAY)
	{
		vector.start_x = game->player.x;
		vector.start_y = game->player.y;
		vector_collision(game, &vector, vector.start_x, vector.start_y);
		vector.start_x *= game->minimap_elsize_x;
		vector.start_y *= game->minimap_elsize_y;
		vector.end_x *= game->minimap_elsize_x;
		vector.end_y *= game->minimap_elsize_y;
		draw_y_vector(game, vector, 0, vector.start_y);
		draw_x_vector(game, vector, vector.start_x, 0);
		vector.angle += FOV / NBR_MINIRAY % 360;
	}
}

static void	fill_element(t_game	*game, int x, int y, int fill)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->minimap_elsize_y)
	{
		j = 0 ;
		while (j < game->minimap_elsize_x)
		{
			mlx_put_pixel(game->texture.minimap,
				(x * game->minimap_elsize_x) + j,
				(y * game->minimap_elsize_x) + i, fill);
			j++;
		}
		i++;
	}
}

static void	draw_element(t_game	*game, int x, int y)
{
	if (game->map[y][x] == '0')
	{
		fill_element(game, x, y, FLOOR);
	}
	else
	{
		fill_element(game, x, y, CLEAR);
	}
}

static void	draw_player(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			mlx_put_pixel(game->texture.minimap,
				game->player.x * game->minimap_elsize_x + j - 1,
				game->player.y * game->minimap_elsize_y - i + 1,
				PLAYER);
			j++;
		}
		i++;
	}
	draw_minimap_fov(game);
}

void	draw_minimap(t_game	*game)
{
	int	x;
	int	y;

	ft_memset(game->texture.minimap->pixels, 0,
		(MINIMAP_HEIGHT) * (MINIMAP_WIDTH) * sizeof(int32_t));
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			draw_element(game, x, y);
			x++;
		}
		y++;
	}
	draw_player(game);
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] == '1')
				fill_element(game, x, y, WALL);
			x++;
		}
		y++;
	}
}
