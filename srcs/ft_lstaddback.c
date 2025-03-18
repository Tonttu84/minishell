/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:41:58 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/18 12:18:19 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//BASH counts heredocs quite early so we do it here
//Im counting the args but I dont seen to use it for anything will delete later when I have a stable commit
static void	set_type(t_node *new)
{
	static int	args = 0;

	if (new->str == NULL)
		new->type = DELIMIT;
	else if (new->str &&new->str[0].c == '|' && new->str[0].com)
	{
		new->type = PIPE;
		args = 0;
	}
	else if (((new->str &&new->str[0].c == '>') || (new->str
				&&new->str[0].c == '<' && new->str[0].com)))
		new->type = REDIRECT;
	else if (new->prev->str &&new->prev->str[0].c == '>'
		&& new->prev->str[1].c == '>' && new->prev->str[0].com)
		new->type = APPEND;
	else if (new->prev->str &&new->prev->str[0].c == '>'
		&& new->prev->str[0].com)
		new->type = OUT_FILE;
	else if (new->prev->str &&new->prev->str[0].c == '<'
		&& new->prev->str[1].c == '<' && new->prev->str[0].com)
	{
		new->type = HERE_DOCS;
		get_data()->herecount++;
		if (get_data()->herecount >= 17)
		{
			perror("Maximum amount of heredocs is 16");
			exit(2);
		}
	}
	else if (new->prev->str &&new->prev->str[0].c == '<'
		&& new->prev->str[0].com)
		new->type = IN_FILE;
	else if (new->str &&new->str[0].com)
		new->type = CTRL;
	else
	{
		if (args == 0)
			new->type = CMD;
		else
		{
			new->type = ARG;
		}
		args++;
	}
}

static void	add_back_utils(t_list *stack, t_node *new, t_node *cur)
{
	cur->next = new;
	stack->last = new;
}

static void	initialize_empty_stack(t_list *stack, t_node *new)
{
	stack->first = new;
	stack->last = new;
	new->next = new;
	new->prev = new;
	set_type(new);
}

void	ft_lstadd_back(t_list *stack, t_node *new)
{
	t_node	*cur;

	if (new == NULL)
		return (perror("DEBUG: Tried to add an empty stack"));
	if (stack->first == NULL)
		return (initialize_empty_stack(stack, new));
	cur = stack->first;
	if (stack->first == stack->last)
	{
		add_back_utils(stack, new, cur);
		cur->prev = new;
		new->prev = cur;
		new->next = cur;
		set_type(new);
		return ;
	}
	while (cur != stack->last)
		cur = cur->next;
	add_back_utils(stack, new, cur);
	new->prev = cur;
	new->next = stack->first;
	stack->first->prev = stack->last;
	set_type(new);
}
