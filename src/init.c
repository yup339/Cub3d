
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
	gun.fire_rate = 10;
	pthread_mutex_init(&gun.m, NULL);
	game->player.gun = &gun;
	gun.tex = mlx_load_png("./texture/gun.png");
	gun.texture = mlx_texture_to_image(game->mlx, gun.tex);
}

void	load_texture(t_game *game)
{
	game->texture.east = mlx_load_png(EAST_TEX);
	game->texture.west = mlx_load_png(WEST_TEX);
	game->texture.north = mlx_load_png(NORTH_TEX);
	game->texture.south = mlx_load_png(SOUTH_TEX);
	if (!game->texture.east || !game->texture.west || !game->texture.north || !game->texture.south)
	{
		free_game(game);
		exit (0);
	}
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
	game->player.dx = -1;
	game->player.dy = 0;
	game->plane_x = 0;
	game->plane_y = 0.80;
	game->player.cam = 0;
	rotate_player_vector(game, angle_to_rad(180));
	game->player.rotation = 0;
	game->player.direction = 0;
	game->texture.background = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->texture.render = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->texture.minimap
		= mlx_new_image(game->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	create_background(game, sky_color, ground_color);
	mlx_image_to_window(game->mlx, game->texture.background, 0, 0);
	mlx_image_to_window(game->mlx, game->texture.render, 0, 0);
	mlx_image_to_window(game->mlx, game->texture.minimap, 0, 0);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
}

