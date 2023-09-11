
#include "cub.h"

static void	create_background(t_game *game, int sky_color, int ground_color)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = 0;
		if (y < HEIGHT / 2)
		{
			while (x < WIDTH)
			{
				mlx_put_pixel(game->texture.background, x, y, sky_color);
				x++;
			}
		}
		else
		{
			while (x < WIDTH)
			{
				mlx_put_pixel(game->texture.background, x, y, ground_color);
				x++;
			}
		}
	}
}

void	init_gun(t_game *game)
{
	static t_gun gun;

	gun.fire = pistol_fire;
	gun.draw = pistol_draw;
	gun.fire_rate = 10;
	pthread_mutex_init(&gun.m, NULL);
	game->player.gun = &gun;
	gun.tex = mlx_load_png("./texture/gun.png");
	gun.texture = mlx_texture_to_image(game->mlx, gun.tex);
}

void	init_game(t_game *game)
{
	static int	sky_color = (0 << 24 | 255 << 16 | 255 << 8 | 255);
	static int	ground_color = (0 << 24 | 145 << 16 | 33 << 8 | 255);

	game->mlx = mlx_init(WIDTH, HEIGHT, "CUBE 3D", true);
	if (!game->mlx)
	{
		write_error(NULL);
		exit (0);
	}
	game->texture.background = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->texture.render = mlx_new_image(game->mlx, WIDTH, HEIGHT); 
	game->texture.minimap
		= mlx_new_image(game->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	create_background(game, sky_color, ground_color);
	mlx_image_to_window(game->mlx, game->texture.background, 0, 0);
	mlx_image_to_window(game->mlx, game->texture.render, 0, 0);
	mlx_image_to_window(game->mlx, game->texture.minimap, 0, 0);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	init_gun(game);
}

