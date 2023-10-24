/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_double_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:40:08 by pbergero          #+#    #+#             */
/*   Updated: 2023/03/21 20:30:24 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <stdio.h>

void	free_double_array(void	**ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr[i] != NULL)
	{
		free (ptr[i]);
		i++;
	}
	free (ptr);
}
