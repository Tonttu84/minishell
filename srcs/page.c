/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:20:15 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/26 15:03:00 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_sent	*conv_linked_to_sentence(t_node *node)
{
	int		i;
	t_sent	*sentence;

//Need to handle expansion or non-expansion, doesnt expand if quoted



/*	//if (HEREDOCS)
		{
		free(sentence->heredocs)
		sentence->heredocs = NULL;
		free(sentence->infile);
		sentence->infile = NULL;
		sentence->heredocs = create_heredoc()
		}
*/
	if (!node)
		return NULL;
	
	sentence = ft_xcalloc(sizeof(t_node), 1);
	{
		
	}
	
	if (node->type == PIPE)
	{
		sentence->inpipe = 1;
		node = destroy_node(&get_data()->tokens, node);
	}
	i = 0;
	while (node && node != get_data()->tokens.last && node->type != PIPE)
	{
		/*
		if (!node) {
        fprintf(stderr, "DEBUG: Node is NULL\n");
        break;
    }
    if (node == get_data()->tokens.last) {
        fprintf(stderr, "DEBUG: Node is the last token\n");
        break;
    }
    fprintf(stderr, "DEBUG: Node type: %d\n", node->type);
	*/
		printf("I is %d\n", i);
			//DEBUG the guard should not be needed
		if (node->type == IN_FILE)
		{
			if (sentence)
				free(sentence->heredocs);
			sentence->heredocs = NULL;
			free(sentence->infile);
			sentence->infile = NULL;
			sentence->infile = cnvrt_to_char(node->str);
		}
		else if (node->type == OUT_FILE)
		{
			free(sentence->outfile);
			sentence->outfile = NULL;
			sentence->outfile = cnvrt_to_char(node->str);

		}
		else if (node->type != DELIMIT && node->str)
		{
			sentence->array[i] = cnvrt_to_char(node->str);
			i++;
		}
		node = destroy_node(&get_data()->tokens, node);
	}
	
	if (node->type == PIPE)
		{
			sentence->outpipe = 1;
			perror("PIPE FOUND");
			printf("Node type is %p \n", get_data()->tokens.first);
		}
	else
	{
		if (node->next->type == IN_FILE)
				sentence->infile = cnvrt_to_char(node->str);
		else if (node->next->type == OUT_FILE)
				sentence->outfile = cnvrt_to_char(node->str);
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
	while (cur && i == 0)
	{
		//iterate_list(&get_data()->tokens, print_node);

		// TODO create redirection files
		// HEREDOCS should capture input here
		//If open fails, abort at this point
		if (cur)
			page[i] = conv_linked_to_sentence(cur);
		cur = stack->first;
		i++;
	}
	print_sentence(page[0]);
	return (page);
}