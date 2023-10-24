/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:03:12 by pbergero          #+#    #+#             */
/*   Updated: 2023/10/24 13:59:48 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	is_pos_valid(char **map, int y, int x)
{
	int	height;

	height = 0;
	while (map[height])
		height++;
	if (x < 0 || y < 0)
		return (false);
	if (y > height)
		return (false);
	if (x > (int)ft_strlen(map[y]))
		return (false);
	if (map[y][x] == '0' || map[y][x] == '1' || map[y][x] == '2')
		return (true);
	return (false);
}

bool	flood(char **map, int y, int x)
{
	static bool	is_valid = true;

	if (is_valid == false)
		return (false);
	if (!is_pos_valid(map, y, x))
	{
		is_valid = false;
		return (false);
	}
	if (map[y][x] == '1' || map[y][x] == '2')
		return (is_valid);
	map[y][x] = '2';
	flood(map, y + 1, x);
	flood(map, y, x + 1);
	flood(map, y - 1, x);
	flood(map, y, x - 1);
	return (is_valid);
}

void	flood_fill(t_game *game)
{
	if (!flood(game->map, (int)game->player.x, (int)game->player.y))
	{
		write_error("map not enclosed");
		free_game(game, true, false);
	}
}
