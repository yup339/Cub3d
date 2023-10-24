/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:35:53 by pbergero          #+#    #+#             */
/*   Updated: 2023/10/24 12:10:05 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

double	angle_to_rad(double angle)
{
	return (angle * M_PI / 180);
}

void	perror_exit(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

int	get_nb_of_player(char **str)
{
	int	i;
	int	j;
	int	n;

	n = 0;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == 'N' || str[i][j] == 'W'
				|| str[i][j] == 'S' || str[i][j] == 'E')
				n++;
			j++;
		}
		i++;
	}
	return (n);
}

void	close_game(void *game)
{
	free_game((t_game *)game, true, true);
}

int	count_char(char *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}
