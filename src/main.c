
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

void	cursor_hook_function(double x, double y, void *ptr)
{
	t_game			*game;
	static double	previous_x = 0;

	game = (t_game *)ptr;
	(void)y;
	game->player.cam = fmod((game->player.cam
				+ ((x - previous_x) * SENSITIVITY) + 360), 360);
	previous_x = x;
}

void	mouse_loop(mouse_key_t button, action_t action, modifier_key_t mods, void *ptr)
{
	t_game	*game;

	game = (t_game *)ptr;
	(void)mods;
	printf("trying to shoot\n");
	if (game->player.gun && button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		printf("trying to shoot\n");
		game->player.gun->fire(game);
	}
	else if (game->player.gun && button == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
	{
		pthread_mutex_lock(&game->player.gun->m);
		game->player.gun->is_firing = false;
		pthread_mutex_unlock(&game->player.gun->m);
		pthread_join(game->player.gun->t, NULL);
	}
}

void	run_game(t_game *game)
{
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_mouse_hook(game->mlx, mouse_loop, game);
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
	run_game(&game);
}
