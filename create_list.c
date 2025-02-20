/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:50:42 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/20 15:03:30 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node *create_node(t_char *line, size_t start, size_t size, t_data *data)
{
	t_node *node;
	t_char *str;
	int i;
	
	
	str = NULL;
	node = ft_xcalloc(sizeof(t_node), 1, data);
	if (line && size > 0)
	{
		i = 0;
		str = ft_xcalloc(sizeof(t_char), size + 1, data);
		while (line[start].c != 0 && (line[start].c!= ' ' || line[start].esc))
		{
		str[i].c = line[start].c;
		str[i].esc = line[start].esc;
		str[i].var = line[start].var;
		str[i].com = line[start].com;
		start++;
		i++;
		}
	}
	node->str = str;
	return (node);
}


void create_list(t_data *data, t_char *line)
{
	size_t i;
	size_t strsize;
	

	i = 0;
	while(line[i].c != 0 )
	{
		while(line[i].c != 0 && line[i].c == ' ' && line[i].esc == 0)
			i++;
		strsize = ft_wrdlen(line + i, data);
		ft_lstadd_back(&data->tokens, create_node(line, i, strsize, data));
		//creates a delimiter token
		ft_lstadd_back(&data->tokens, create_node(NULL, 0, 0, data));
		while(line[i].c != 0)
		{
			if (line[i].c == ' ' && line[i].esc == 0)
				break;
			i++;
		}
	}
}