/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:35:53 by pbergero          #+#    #+#             */
/*   Updated: 2023/10/23 15:11:10 by pbergero         ###   ########.fr       */
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

int	get_nb_of_player(char *str)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == 'N' || str[i] == 'W' || str[i] == 'S' || str[i] == 'E')
			n++;
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
