/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:35:53 by pbergero          #+#    #+#             */
/*   Updated: 2023/10/12 17:46:35 by pbergero         ###   ########.fr       */
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
	exit(1);
}
