#include "cub.h"

void	shoot_bullet(t_game *game, t_gun *gun)
{
	(void)game;
	printf("bam!!\n");
	usleep(gun->fire_rate * 1000);
}

void	*gun_fire(void *ptr)
{
	t_game	*game;

	game = (t_game *)ptr;
	while (1)
	{
		pthread_mutex_lock(&game->player.gun->m);
		if (!game->player.gun->is_firing)
		{
			pthread_mutex_unlock(&game->player.gun->m);
			return (NULL);
		}
		pthread_mutex_unlock(&game->player.gun->m);
		shoot_bullet(game, game->player.gun);
	}
}

int	pistol_fire(void *ptr)
{
	t_game	*game;

	game = (t_game *)ptr;
	game->player.gun->is_firing = true;
	if (pthread_create(&game->player.gun->t, NULL, gun_fire, game))
		perror("thread:");
	return (0);
}

