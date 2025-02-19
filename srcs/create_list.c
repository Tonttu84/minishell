/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:50:42 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/19 21:50:10 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t set_line(t_char *line, t_node *node, t_data *data)
{
	size_t li;
	char *arg;
	size_t ni;
	size_t temp;

	arg = NULL;
	li = 0;
	ni = 0;
	while(line[li].c != 0 && line[li].c != ' ' && line[li].esc == 0)
	{
		if (line[li].c == '&' && line[li].esc == 0)
			{
				arg = getenv(find_env(line + 1, data));
				temp = 0;
				while (arg && arg[temp])
				{
					node->str[ni].c = arg[temp];
					node->str[ni].var = 1;
					ni++;
					temp++;
				}
			}
		if (line[li].var == 0)
			{
				ft_memcpy(node + ni, line + li, sizeof(t_char));
				ni++;	
			}
		li++;
	}
	return (ni);
}

t_node *create_node(t_char *line, size_t start, size_t size, t_data *data)
{
	t_node *node;
	t_char *str;
	
	str = NULL;
	node = ft_xcalloc(sizeof(t_node), 1, data);
	if (line && size > 0)
	{
	str = ft_xcalloc(sizeof(t_char), size + 1, data);
	node->str = str;
   		if (size != set_line(line + start, node, data))
			perror("DEBUG: sizes for create node dont match");
	}
	node ->str = str;
	return (node);
}


void create_list(t_data *data, t_char *line)
{
	size_t i;
	size_t strsize;
	//int type;

	i = 0;
	while(line[i].c )
	{
		while(line[i].c == ' ' && line[i].esc == 0)
			i++;
		strsize = ft_wrdlen(line + i, data);
		ft_lstadd_back(&data->tokens, create_node(line, i, strsize, data));
		//creates a delimiter token
		ft_lstadd_back(&data->tokens, create_node(NULL, 0, 0, data));
		i += strsize + 1;
	}
}
