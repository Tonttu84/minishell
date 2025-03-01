/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:54:24 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/27 10:53:28 by jrimpila         ###   ########.fr       */
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
	length = ft_tcharlen(line) * 2;
	result = ft_xcalloc((ft_tcharlen(line) * 2) + 1, sizeof(char));
	while (i < length && line[k].c)
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
	result[i] = '\0';
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
