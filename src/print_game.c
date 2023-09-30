
#include "cub.h"

void	draw_cursor(t_game *game)
{
	int	i;

	ft_memset(game->texture.corsor->pixels, 0, 10 * 10 * sizeof(int32_t));
	i = 0;
	while (i < 5)
	{
		mlx_put_pixel(game->texture.corsor, i, 3, MAP_FOV_COLOR);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		mlx_put_pixel(game->texture.corsor,3,i, MAP_FOV_COLOR);
		i++;
	}
}
