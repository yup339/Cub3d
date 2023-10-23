/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:21:54 by pbergero          #+#    #+#             */
/*   Updated: 2023/10/23 16:23:55 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*copy_nospace(char *str, char *original)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (original[i])
	{
		if (original[i] != ' ')
		{
			str[j] = original[i];
			j++;
		}
		i++;
	}
	free(original);
	return (str);
}

char	*remove_white_space(char *str, bool flag)
{
	int		i;
	int		l;
	char	*s;

	if (flag)
		return (str);
	if (!str)
		return (NULL);
	i = 0;
	l = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			l++;
		i++;
	}
	l = i - l;
	s = ft_calloc(l + 1, 1);
	if (!s)
	{
		free (str);
		return (NULL);
	}
	return (copy_nospace(s, str));
}
