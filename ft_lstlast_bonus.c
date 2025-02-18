/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:05:09 by jrimpila          #+#    #+#             */
/*   Updated: 2024/11/03 13:21:09 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*cur;
	t_list	*last;

	cur = lst;
	last = NULL;
	while (cur != NULL)
	{
		last = cur;
		cur = cur->next;
	}
	return (last);
}
