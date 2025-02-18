/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:11:43 by jrimpila          #+#    #+#             */
/*   Updated: 2024/11/03 14:27:22 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*copy_node(t_list *orig, void *(*f)(void *))
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->content = f(orig->content);
	new_node->next = NULL;
	return (new_node);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*cur;
	t_list	*prev;
	t_list	*first;

	prev = NULL;
	first = NULL;
	cur = lst;
	while (cur)
	{
		newlst = copy_node(cur, f);
		if (!newlst)
		{
			ft_lstclear(&first, del);
			return (NULL);
		}
		if (!first)
			first = newlst;
		if (prev)
			prev->next = newlst;
		prev = newlst;
		cur = cur->next;
	}
	return (first);
}
