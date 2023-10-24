/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:21:54 by pbergero          #+#    #+#             */
/*   Updated: 2023/10/24 14:20:49 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


/*makes a copy without spaces "ascii = 32"*/
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
	return (str);
}

/*remove all spaces "ascii = 32"*/
char	*remove_white_space(char *str)
{
	int		i;
	int		l;
	char	*s;

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
		return (NULL);
	}
	return (copy_nospace(s, str));
}
