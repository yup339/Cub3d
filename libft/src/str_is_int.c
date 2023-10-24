/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_is_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 20:59:02 by pbergero          #+#    #+#             */
/*   Updated: 2023/10/23 17:48:56 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	is_str_int2(const char *str, int len)
{
	if (len > 11)
		return (0);
	if (len == 11)
	{
		if (str[0] != '-')
			return (0);
		if (str[0] == '-' && ft_strcmp(str, "-2147483648") > 0)
			return (0);
	}
	if (len == 10)
	{
		if (ft_strcmp(str, "2147483647") > 0)
			return (0);
	}
	return (1);
}

int	is_str_int(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[0] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while ((str[i]))
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (is_str_int2(str, ft_strlen(str)));
}
