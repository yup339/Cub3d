
#include "cub.h"

void	free_game(t_game *game)
{
	//free_double_array((void **)game->map);
	mlx_terminate(game->mlx);
	exit(EXIT_SUCCESS);
}

void	init_map(t_game *game)
{
	static char	*maps[] = 
	{
		"111111111111111",
		"100000000000111",
		"101011000000001",
		"1001 1011111111",
		"110011010010001",
		"110011010110001",
		"110011010010001",
		"110011000000001",
		"111111111111111",
		NULL
	};

	game->map = maps;
	game->height = 9;
	game->width = 15;
	game->minimap_elsize_x = 20;
	game->minimap_elsize_y = 20;
	game->player.x = 1.5;
	game->player.y = 1.5;
}

void	cursor_hook_function(double x, double y, void *ptr)
{
	t_game			*game;
	static double	previous_x = 0;

	game = (t_game *)ptr;
	if (game->cursor == true)
		return ;
	(void)y;
	game->player.cam = fmod((game->player.cam
				+ ((x - previous_x) * SENSITIVITY) + 360), 360);
	rotate_player_vector(game, -angle_to_rad((x - previous_x) * SENSITIVITY));
	previous_x = x;
}


void	run_game(t_game *game)
{
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_cursor_hook(game->mlx, &cursor_hook_function, game);
	mlx_key_hook(game->mlx, &key_loop, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_game	game;

	(void)argc;
	(void)argv;
	init_map(&game);
	init_game(&game);
	load_texture(&game);
	run_game(&game);
}
