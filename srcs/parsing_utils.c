/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:54:24 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/25 18:06:48 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Untested 24.2

static int	ft_isescapable(char c);

size_t	ft_tcharlen(t_char *line)
{
	size_t	length;

	length = 0;
	while (line[length].c != '\0')
	{
		length++;
	}
	return (length);
}

char	*cnvrt_to_char(t_char *line)
{
	size_t	i;
	size_t	k;
	size_t	length;
	char	*result;

	i = 0;
	k = 0;
	length = ft_tcharlen(line);
	result = ft_xcalloc((ft_tcharlen(line) * 2) + 1, sizeof(char));
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
	return (result);
}

static int	ft_isescapable(char c)
{
	if (c == '*' || c == '?' || c == '[' || c == ']' || c == '{' || c == '}'
		|| c == '~' || c == '$' || c == '(' || c == ')' || c == '\\'
		|| c == '\'' || c == '\"' || c == '>' || c == '<' || c == '|'
		|| c == '&' || c == ';' || c == '!' || c == '#' || c == ' ')
		return (1);
	return (0);
}




void create_heredoc(char *terminator)
{
	char *tmp;
	char *result;
	char *cpy;
	
	tmp = NULL;
	while (tmp == NULL || ft_strncmp(terminator, tmp, ft_strlen(terminator) +1))
	{
		
		if (tmp)
		{
			cpy = tmp;
			tmp = ft_strjoin(tmp, "\n");
			free(cpy);
			cpy = NULL;
			if (result)
			{
				cpy = result;
				result = ft_strjoin(result, tmp);;
				free(cpy);
				free(tmp);
				tmp = NULL;
				cpy = NULL;
			}
			else 
				result = tmp;
		}
		tmp = readline(">");
	}
	free (tmp);
	return (result);
}



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

	sentence = ft_xcalloc(sizeof(t_node), 1);
	
	if (node->type == PIPE)
	{
		sentence->inpipe = 1;
		node = destroy_node(&get_data()->tokens, node);
		if (node->type == DELIMIT)
			node = destroy_node(&get_data()->tokens, node);
	}
	i = 0;
	while (node != get_data()->tokens.last && node->type != PIPE)
	{
		if (node->next->next->type == IN_FILE)
				{
					free(sentence->heredocs);
					sentence->heredocs = NULL;
					free(sentence->infile);
					sentence->infile = NULL;
					sentence->infile = cnvrt_to_char(node->str);

				}
		else if (node->next->next->type == OUT_FILE)
		{
				free(sentence->outfile);
				sentence->outfile = NULL;
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
				sentence->infile = cnvrt_to_char(node->str);
		else if (node->next->next->type == OUT_FILE)
				sentence->outfile = cnvrt_to_char(node->str);
		else if (node->type != DELIMIT)
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

t_sent	**create_page(t_list *stack)
{
	t_sent	*page;
	t_node	*cur;
	int		i;

	destroy_old_page();
	page = get_data()->page;
	if (stack == NULL || stack->first == NULL)
		return (NULL);
	cur = stack->first;
	i = 0;
	while (cur)
	{
		

		// TODO create redirection files
		// HEREDOCS should capture input here
		//If open fails, abort at this point
		page[i] = conv_linked_to_sentence(cur);
		i++;
	}
	return (page);
}
