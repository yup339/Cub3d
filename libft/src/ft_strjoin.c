/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:38:10 by pbergero          #+#    #+#             */
/*   Updated: 2023/10/15 00:36:54 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*fail_return(char *s1, char *s2, int flag1, int flag2)
{
	if (flag1 == 1 && s1)
		free(s1);
	if (flag2 == 1 && s2)
		free(s2);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2, int flag1, int flag2)
{
	char	*str;
	int		i;
	int		j;

	str = malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	j = 0;
	if (!str)
		return (fail_return(s1, s2, flag1, flag2));
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = 0;
	if (flag1 == 1 && s1)
		free(s1);
	if (flag2 == 1 && s2)
		free(s2);
	return (str);
}
