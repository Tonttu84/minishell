/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 10:18:39 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/15 16:22:47 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// Copies a substring from start to emd
char *ft_strndup(const char *s, size_t start, size_t end)
{
    char *copy;
    size_t length;

    if (s == NULL || start > end || end >= ft_strlen(s))
        return (NULL);

    length = end - start + 1;
    copy = (char *)malloc((length + 1) * sizeof(char));
    if (copy == NULL)
        return (NULL);

    ft_strlcpy(copy, s + start, length);
    copy[length] = '\0';

    return copy;
}

void add_behind(t_node *target, t_node *new, t_data *data)
{
	if(!target || !new || !data)
		perror("DEBUG, iffy input to add_behind");
	target->next->prev = new;
	new -> next = target->next;
	target->next = new;
	new->prev = target;
	if (data->tokens.last == target) 
		data->tokens.last = new;

}

char *get_own_env(t_data *data, char *str)
{
	char *target;
	int tar_i;

	tar_i = find_env(str, data);
	
	if (tar_i == -1)
		return (NULL);
	target = data->env[tar_i];
	return (target + (ft_strlen(str) + 1));
}