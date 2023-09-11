#include "cub.h"

/// @brief main loop of the game 
/// @param ptr game pointer toward the main struct
void	game_loop(void *ptr)
{
	t_game	*game;

	game = (t_game *)ptr;
	ft_memset(game->texture.minimap->pixels, 0,
		(MINIMAP_HEIGHT) * (MINIMAP_WIDTH) * sizeof(int32_t));
	ft_memset(game->texture.render->pixels, 0,
		(HEIGHT) * (WIDTH) * sizeof(int32_t));
	raycast(game);
	draw_minimap(game);
	if (game->player.gun)
		game->player.gun->draw(game);
	change_rotation(game);
	move_player(game);
}

void	key_loop2(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		game->player.direction |= FORWARD;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		game->player.direction |= LEFT;
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		game->player.direction |= BACKWARD;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		game->player.direction |= RIGHT;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		game->player.direction &= ~FORWARD;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		game->player.direction &= ~LEFT;
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		game->player.direction &= ~BACKWARD;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		game->player.direction &= ~RIGHT;
}

void	key_loop(mlx_key_data_t keydata, void *ptr)
{
	t_game	*game;

	game = (t_game *)ptr;
	if (keydata.key == MLX_KEY_ESCAPE)
		free_game(game);
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		game->player.rotation |= LEFT;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		game->player.rotation |= RIGHT;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		game->player.rotation &= ~LEFT;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		game->player.rotation &= ~RIGHT;
	key_loop2(keydata, game);
}
