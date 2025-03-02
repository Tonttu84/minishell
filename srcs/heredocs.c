/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:18:56 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/02 15:52:39 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand_heredocs(char *result);

char	*expand_heredocs(char *result)
{
	return (result);
}

int	t_compare(t_char *str, char *str2)
{
	int	i;

	if (!str)
		perror("Heredocs delimiter should not be NULL\n");
	if (!str2)
		return (1);
	i = 0;
	while (str[i].c && str2[i])
	{
		if (str[i].c != str2[i])
			return (1);
		i++;
	}
	if (str[i].c != str2[i])
		return (1);
	return (0);
}

// Missing expansion support <<"tad"aa delimiter is tadaa expansion doesnt happen
// Currently heredocs that is instantly terminated returns a NULL terminator but we need to test it what format is required
char	*create_heredoc(char *terminator, int expand)
{
	char	*tmp;
	char	*result;
	char	*cpy;

	tmp = NULL;
	result = NULL;
	cpy = NULL;
	while (ft_strncmp(terminator, tmp, ft_strlen(terminator + 1)))
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
				result = ft_strjoin(result, tmp);
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
	free(tmp);
	if (expand)
		return (expand_heredocs(result));
	return (result);
}
