
#include "cub.h"

void	free_game(t_game *game)
{
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

void	run_game(t_game *game)
{
	mlx_loop_hook(game->mlx, game_loop, game);
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
	run_game(&game);
}
