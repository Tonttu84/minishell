/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:06:42 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/11 17:56:01 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

const char	*token_to_string(t_token token)
{
	
	if (token == ARG)
		return ("ARG");
	else if (token == CMD)
		return ("CMD");
	else if (token == OUT_FILE)
		return ("OUT_FILE");
	else if (token == IN_FILE)
		return ("IN_FILE");
	else if (token == CTRL)
		return ("CTRL");
	else if (token == PIPE)
		return ("PIPE");
	else if (token == REDIRECT)
		return ("REDIRECT");
	else if (token == APPEND)
		return ("APPEND");
	else if (token == HERE_DOCS)
		return ("HERE_DOCS");
	else
		return ("UNKNOWN");
}

const char	*token_to_color(t_token token)
{
	if (token == IN_FILE)
		return (BRIGHT_BLUE);
	else if (token == DELIMIT)
		return (YELLOW);
	else if (token == ARG)
		return (CYAN);
	else if (token == HERE_DOCS)
		return (BRIGHT_CYAN);
	else if (token == CMD)
		return (MAGENTA);
	else if (token == OUT_FILE)
		return (WHITE);
	else if (token == APPEND)
		return (BRIGHT_WHITE);
	else if (token == CTRL)
		return (BLUE);
	else if (token == REDIRECT)
		return (BLUE);
	else if (token == PIPE)
		return (BRIGHT_YELLOW);
	else
		return (RESET);
}

void	print_node(t_list *list, t_node *node)
{
	(void)node;
	(void)list;/*
	int			i;
	const char	*color;

	if (node)
		color = token_to_color(node->type);
	else
		perror("NODE IS NULL");
	(void)list;
	printf("{%s%s%s", color, token_to_string(node->type), RESET);
	if (node->type != DELIMIT)
		printf(" ");
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
	printf("}");*/
}

void	debug_print(t_char *array, t_data *data)
{
	(void)array;
	(void)data;/*
	int	i;

	i = 0;
	while (array[i].c)
	{
		if (array[i].esc && array[i].c == ' ')
			printf("%s_%s", RED, RESET);
		else if (array[i].esc)
			printf("%s%c%s", RED, array[i].c, RESET);
		else if (array[i].com)
			printf("%s%c%s", BLUE, array[i].c, RESET);
		else if (array[i].c == '$' && array[i].var)
		{
			printf("%s%s%s", YELLOW, find_env(array + i, data), RESET);
			printf("%s%c%s", GREEN, array[i].c, RESET);
		}
		else if (array[i].var)
			printf("%s%c%s", GREEN, array[i].c, RESET);
		else if (array[i].c == ' ' && array[i].ghost)
			printf("[G]");
		else
			printf("%c", array[i].c);
		i++;
	}
	printf("\n");*/
}

void	print_sentence(t_sent *sentence)
{
	(void)sentence;/*
	int	i;
	i = 0;
	//const char *color = token_to_color(sentence->redirs[i].type);
	//const char *token_str = token_to_string(sentence->redirs[i].type);

	printf("Arguments are :\n");
	
	while (sentence->array[i] && i < 6)
	{
		printf("%s \n", sentence->array[i]);
		i++;
	}
	i = 0;
	printf("Redirections are :\n");
	while (i < 20 && sentence->redirs[i].path)
	{
		//printf("%s%s: %s%s\n", color, token_str, sentence->redirs[i].path, RESET);
		printf("%s , type is %d\n", sentence->redirs[i].path, sentence->redirs[i].type);
		i++;
	}
	printf("\n");
	printf("Inpipe is %d, ", sentence->inpipe);
	printf("outpipe is %d, ", sentence->outpipe);*/
}
