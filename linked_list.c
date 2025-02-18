/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:10:48 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/15 16:16:58 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node *create_node(char *setstr, t_token set_type, t_data *data)
{
	t_node *new;

	new = ft_calloc(1, sizeof(t_node), data);
	
	if (new == NULL)
		return (NULL);
	new->type = set_type;
	new->str = setstr;
	
	return new;
}

static void	add_back_utils(t_stack *stack, t_node *new, t_node *cur)
{
	cur -> next = new;
	stack -> last = new;
}

static void	initialize_empty_stack(t_stack *stack, t_node *new)
{
	stack->first = new;
	stack->last = new;
	new->next = new;
	new->prev = new;
}

void	ft_lstadd_back(t_stack *stack, t_node *new)
{
	t_node	*cur;

	if (new == NULL)
	{
		perror("DEBUG: Tried to add an empty stack");
		return ;
	}
	if (stack->first == NULL)
		return (initialize_empty_stack(stack, new));
	cur = stack->first;
	if (stack->first == stack->last)
	{
		add_back_utils(stack, new, cur);
		cur->prev = new;
		new->prev = cur;
		new->next = cur;
		return ;
	}
	while (cur != stack->last)
		cur = cur->next;
	add_back_utils(stack, new, cur);
	new->prev = cur;
	new->next = stack->first;
	stack->first->prev = stack->last;
}