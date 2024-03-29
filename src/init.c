/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:35:31 by pbergero          #+#    #+#             */
/*   Updated: 2023/10/24 14:26:14 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/* create the background image by making it half sky/half floor colors */
static void	create_background(t_game *g)
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
				mlx_put_pixel(g->texture.background, x, y, g->load_info.s_c);
				x++;
			}
		}
		else
		{
			while (x < WIDTH)
			{
				mlx_put_pixel(g->texture.background, x, y, g->load_info.f_c);
				x++;
			}
		}
	}
}

/* load texture exit cleanly if there is a problem loading the texture*/
void	load_texture(t_game *game)
{
	game->texture.east = mlx_load_png(game->load_info.ea_path);
	game->texture.west = mlx_load_png(game->load_info.we_path);
	game->texture.north = mlx_load_png(game->load_info.no_path);
	game->texture.south = mlx_load_png(game->load_info.so_path);
	if (!game->texture.east || !game->texture.west
		|| !game->texture.north || !game->texture.south)
	{
		write_error("invalid texture");
		free_game(game, true, true);
	}
}

/*we start the player in the middle of its coord
then we rotate the player depending of its starting angle*/
void	set_player(t_game *game, int y, int x)
{
	game->player.y = x + 0.5;
	game->player.x = y + 0.5;
	if (game->map[y][x] == 'S')
		rotate_player_vector(game, angle_to_rad(90));
	if (game->map[y][x] == 'W')
		rotate_player_vector(game, angle_to_rad(180));
	if (game->map[y][x] == 'N')
		rotate_player_vector(game, angle_to_rad(270));
}

/*find the player position*/
void	find_player(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'W'
				|| game->map[y][x] == 'E' || game->map[y][x] == 'S')
			{
				set_player(game, y, x);
				game->map[y][x] = '0';
				break ;
			}
			x++;
		}
		y++;
	}
}

/*init the variable for raycasting and init the images use in the window*/
void	init_game(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "CUBE 3D", true);
	if (!game->mlx)
	{
		write_error(NULL);
		exit (0);
	}
	game->player.dx = -1;
	game->player.dy = 0;
	game->plane_x = 0;
	game->plane_y = 1;
	game->player.cam = 0;
	game->player.rotation = 0;
	game->player.direction = 0;
	find_player(game);
	game->texture.background = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->texture.render = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	create_background(game);
	mlx_image_to_window(game->mlx, game->texture.background, 0, 0);
	mlx_image_to_window(game->mlx, game->texture.render, 0, 0);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
}
