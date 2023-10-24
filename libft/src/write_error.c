/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:19:46 by pbergero          #+#    #+#             */
/*   Updated: 2023/10/23 18:33:31 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	write_error(char *cust_mess)
{
	write(2, "Error\n", 6);
	if (cust_mess)
	{
		write(2, cust_mess, ft_strlen(cust_mess));
	}
	write(2, "\n", 1);
	return (0);
}
