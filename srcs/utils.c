/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:41:05 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/19 21:50:29 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"



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
	size_t lenght;
	

	i = 0;
	lenght = 0;
	if (str == NULL)
	{
		perror("DEBUG: Pointer is NULL for ft_wrdlen\n");
		return (-1);
	}		
	while (str[i].c != 0)
	{
		if (str[i].c == ' ' && str[i].esc == 0)
			return (lenght);
		if (str[i].c == '$' && str[i].esc == 0)
			lenght = lenght + ft_strlen(find_env(&str[i], data));
		if (str[i].var == 0)
			lenght++;
		i++;
	}
	return (i);
}

void destroy_node(t_node *node)
{
	
	node->prev->next = node->next;
	
	
}


void print_node(t_list *list, t_node *node)
{
	int	i;

	(void) list;
	if(node->str == NULL)
		printf("{}");
	i = 0;
	while (node->str && node->str[i].c)
	{
		 while (node->str[i].c)
    	{
		if (node->str[i].esc && node->str[i].c == ' ')
			printf("%s_%s", RED, RESET);
        else if (node->str[i].esc)
        {
            printf("%s%c%s", RED, node->str[i].c, RESET);
        }
		else if (node->str[i].com)
		{
            printf("%s%c%s", BLUE, node->str[i].c, RESET);
        }
		else if (node->str[i].var)
		{
            printf("%s%c%s", GREEN, node->str[i].c, RESET);
        }
        else
            printf("%c", node->str[i].c);
        i++;
    	}
	}
}
