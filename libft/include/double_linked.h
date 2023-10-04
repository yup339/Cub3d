/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_linked.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbergero <pascaloubergeron@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 00:23:55 by pbergero          #+#    #+#             */
/*   Updated: 2023/02/28 19:44:31 by pbergero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOUBLE_LINKED_H
# define DOUBLE_LINKED_H

# include <stdlib.h>
# include <stdio.h>

typedef struct s_list{
	struct s_list	*next;
	struct s_list	*previous;
	int				content;
}	t_list;

t_list	*create_add_back_2wl(t_list **list, int content);
t_list	*create_add_front_2wl(t_list **list, int content);
void	free_list(t_list *list);
int		get_list_size(t_list *list);
t_list	*get_x_elem(t_list *list, int x);
void	print_list_content(t_list *list);
void	swap_elem_position(t_list **list);
void	print_reverse_list_content(t_list *list);

#endif