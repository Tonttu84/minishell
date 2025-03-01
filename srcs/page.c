/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:20:15 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/01 16:13:51 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *test_infile(t_char *raw_path)
{
	(void) raw_path;
	return NULL;
}

t_sent	*conv_linked_to_sentence(void)
{
	int		i;
	t_sent	*sentence;
	t_node	*node;
	t_data	*data;
	int k;

	k = 0;
	data = get_data();
	node = data->tokens.first;
	sentence = ft_xcalloc(sizeof(t_sent), 1);
	if (node && node->type == PIPE)
	{
		sentence ->inpipe = 1;
		node = destroy_node(&get_data()->tokens, node);
	}
	i = 0;
	while (node)
	{
		node = get_data()->tokens.first;
		if (node->type == PIPE)
		{
			sentence->outpipe = 1;
			return (sentence);
		}
		if (node->type == REDIRECT)
			;
		else if (node->type == IN_FILE || node->type == OUT_FILE || node->type == APPEND || node->type == HERE_DOCS)
		{
			add_redirection(node, sentence, k);
			k++;	
		}
		else
		{
			sentence->array[i] = cnvrt_to_char(node->str);
			i++;
		}
		node = destroy_node(&get_data()->tokens, node);
	}
	return (sentence);
}

void	destroy_old_page(void)
{
	int		i;
	int		k;
	t_data	*data;

	data = get_data();
	i = 0;
	while (i < MAX_SENTENCES)
	{
		k = 0;
		while (k < MAX_SENT_SIZE && data->page[i])
		{
			free(data->page[i]->array[k]);
			data->page[i]->array[k] = NULL;
			k++;
		}
		free(data->page[i]);
		data->page[i] = NULL;
		i++;
	}
}

t_sent	**create_page(t_list *stack)
{
	t_sent	**page;
	t_node	*cur;
	int		i;

	destroy_old_page();
	page = get_data()->page;
	if (stack == NULL || stack->first == NULL)
		return (NULL);
	cur = stack->first;
	if (!cur)
		perror("CUR IS NULL");
	i = 0;
	while (cur)
	{
		page[i] = conv_linked_to_sentence();
		cur = stack->first;
		printf("\n");
		print_sentence(page[i]);
		printf("\n");
		i++;
	}
	return (page);
}
