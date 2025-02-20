/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:41:05 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/20 13:08:12 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void iterate_list(t_list *list, node_func func)
{
    t_node *current = list->first;
    while (current != list->last) {
        func(list, current);
        current = current->next;
    }
    // Apply the function to the last node
    if (current == list->last) {
        func(list, current);
    }
}


size_t ft_wrdlen(t_char *str, t_data *data)
{
	size_t i;
	
	(void) data;
	i = 0;
	if (str == NULL)
	{
		perror("DEBUG: Pointer is NULL for ft_wrdlen\n");
		return (-1);
	}		
	while (str[i].c != 0 && (str[i].c != ' ' || str[i].esc == 1))
	{
		i++;
	}
	return (i);
}

void destroy_node(t_node *node)
{
	
	node->prev->next = node->next;
	
	
}



