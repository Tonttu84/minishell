/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:41:58 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/24 14:09:06 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void set_type(t_list *stack, t_node *new)
{
	
	//redirections should have higher direction

	if (stack->first == new)
		new->type = CMD;
	if (new->str == NULL)
		new ->type = DELIMIT;
	
	else if (new->str[0].c == '|' && new->str[0].com)
		new->type = PIPE;
	else if ((new->str[0].c == '>' || new->str[0].c == '<') && new->str[0].com)
		new->type = REDIRECT;
		
	else if ((new->prev->prev->str[0].c == '|') && new->prev->prev->str[0].com)
		new->type = CMD;
	else if (new->prev->prev->str[0].c == '>' && new->prev->prev->str[1].c == '>' && new->prev->prev->str[0].com)
		new->type = APPEND;
	else if (new->prev->prev->str[0].c == '>' && new->prev->prev->str[0].com)
		new->type = OUT_FILE;
	else if (new->prev->prev->str[0].c == '<' && new->prev->prev->str[1].c == '<' && new->prev->prev->str[0].com)
		new->type = HERE_DOCS;
	else if (new->prev->prev->str[0].c == '<' && new->prev->prev->str[0].com)
		new->type = IN_FILE;
	else if (new->str[0].com)
		new->type = CTRL;
	else 
		new->type = ARG;
}

static void	add_back_utils(t_list *stack, t_node *new, t_node *cur)
{
	cur -> next = new;
	stack -> last = new;
}

static void	initialize_empty_stack(t_list *stack, t_node *new)
{
	
	stack->first = new;
	stack->last = new;
	new->next = new;
	new->prev = new;
	new->type = CMD;
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
		set_type(stack, new);
		return ;
	}
	while (cur != stack->last)
		cur = cur->next;
	add_back_utils(stack, new, cur);
	new->prev = cur;
	new->next = stack->first;
	stack->first->prev = stack->last;

	//This spot could check for ivalid stuff like > > but for now Im just adding the normal types
	set_type(stack, new);
	
	
}
