/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:54:24 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/22 17:56:41 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_isescapable(char c);


size_t ft_tcharlen(t_char *line)
{
    size_t length = 0;
    while (line[length].c != '\0')
    {
        length++;
    }
    return length;
}

char *cnvrt_to_char(t_char *line)
{
	size_t i;
	size_t k;
	
	i = 0;
	k = 0;
    size_t length = ft_tcharlen(line);
    char *result = ft_xcalloc((ft_tcharlen(line) * 2) + 1, sizeof(char));
    while (i < length)
    {
		if (line[k].esc && ft_isescapable(line[k].c))
		{	
				result[i] = '\\';
				i++; 
		}
        result[i] = line[k].c;
		i++;
		k++;
    }
    result[length] = '\0';
    return result;
}


static int ft_isescapable(char c)
{
    if (c == '*' || c == '?' || c == '[' || c == ']' || c == '{' || c == '}' || 
        c == '~' || c == '$' || c == '(' || c == ')' || c == '\\' || c == '\'' ||
        c == '\"' || c == '>' || c == '<' || c == '|' || c == '&' || c == ';' || 
        c == '!' || c == '#' || c == ' ')
        return (1);
    return (0);
}

t_sent *conv_linked_to_sentence(t_node *node)
{
	int i;
	t_sent *sentence;
	
	sentence = ft_xcalloc(sizeof(t_node), 1);
	if(node->type == PIPE)
	{
		sentence->inpipe = 1;
		node = destroy_node(&get_data()->tokens, node);
		if (node->type == DELIMIT)
		node = destroy_node(&get_data()->tokens, node);
	}
	i = 0;
	while(node != get_data()->tokens.last && node->type != PIPE)
	{
		if (node->next->next->type == IN_FILE)
		{
			if (sentence->infile != NULL)
				perror("Too many infiles");
			else 
				sentence->infile = cnvrt_to_char(node->str);
		}
		else if (node->next->next->type == OUT_FILE)
		{
			if (sentence->outfile != NULL)
				perror("Too many infiles");
			else 
				sentence->outfile = cnvrt_to_char(node->str);
		}
		else if (node->type != DELIMIT)
		{ 
			sentence->array[i] = cnvrt_to_char(node->str);
			i++;
		}
		node = destroy_node(&get_data()->tokens, node);
	} 
	if (node->type == DELIMIT)
		node = destroy_node(&get_data()->tokens, node);
	if (node->type == PIPE)
		sentence->outpipe = 1;
	else 
	{
		if (node->next->next->type == IN_FILE)
		{
			if (sentence->infile != NULL)
				perror("Too many infiles");
			else 
				sentence->infile = cnvrt_to_char(node->str);
		}
		else if (node->next->next->type == OUT_FILE)
		{
			if (sentence->outfile != NULL)
				perror("Too many infiles");
			else 
				sentence->outfile = cnvrt_to_char(node->str);
		}
		else if (node->type != DELIMIT)
		{ 
			sentence->array[i] = cnvrt_to_char(node->str);
			i++;
		}
		node = destroy_node(&get_data()->tokens, node);
	}
	return (sentence);
}

void destroy_old_page(void)
{
	int i;
	int k;
	t_data *data;
		
	data = get_data();
	i = 0;
	while (i < MAX_SENTENCES)
	{
		k = 0;
		while (k < MAX_SENT_SIZE)
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


t_sent **create_page(t_list *stack)
{
	t_sent **page;
	t_node *cur;
	int i;

	
	destroy_old_page();
	page = get_data()->page;
	if (stack == NULL || stack->first == NULL)
		return (NULL);
	cur = stack->first;
	i = 0;
	while (cur)
	{
		page[i] = conv_linked_to_sentence(cur);
		i++;
	}
	return (page);

} 