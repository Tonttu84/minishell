/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:18:56 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/26 11:39:51 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
char *expand_heredocs(char *result);


char *expand_heredocs(char *result)
{
	return result;
}
//Missing expansion support
char 	*create_heredoc(char *terminator, int expansion)
{
	char	*tmp;
	char	*result;
	char	*cpy;
	
	tmp = NULL;
	result = NULL;
	cpy = NULL;
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
	if (expansion)
		return (expand_heredocs(result));
	return (result);
}