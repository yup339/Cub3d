/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_power.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:44:11 by pbergero          #+#    #+#             */
/*   Updated: 2023/02/27 19:22:05 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	square_power(int n)
{
	if (n == 0)
		return (1);
	else
		return (2 * square_power(n - 1));
}
