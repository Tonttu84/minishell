/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:18:56 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/03 14:09:04 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	match_env_argument_char(char *source, char *env_var)
{
	int	i;

	i = 0;
	if (env_var == NULL || env_var[0] == '\0')
		return (0);
	if (source[0] != '$' || (ft_isalnum(source[1]) == 0
			&& source[1] != '_'))
		perror("DEBUG iffy input to match_env_argument\n");
	i = 1;
	while (ft_isalnum(source[i]) || source[i] == '_')
	{
		if (source[i] == env_var[i - 1])
			i++;
	}
	if (source[i] == 0 || source[i] == '=')
		return (1);
	return (0);
}

const char	*find_env_char(char *source, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->env_count)
	{
		if (match_env_argument_char(source, data->env[i]))
			return (((const char *)data->env + i));
		i++;
	}
	return (NULL);
}

// I have a pointer to the start of the env variable
void	expand_envvar(char *unexp, char *exp, int *i, int *k)
{
	const char *ptr_envvar;
	int j;

	ptr_envvar = find_env_char(unexp + *i, get_data());
	j = 0;
	while (ptr_envvar && ptr_envvar[j] && ptr_envvar[j] != '=')
		j++;
	while (ptr_envvar && ptr_envvar[j])
	{
		exp[*k] = ptr_envvar[j];
		(*k)++;
		j++;
	}
	if (unexp[*i] == '$')
		(*i)++;
	else
		perror("DEBUG, something seems wrong");
	while(ft_isalnum(unexp[*i]) ||unexp[*i] == '_')
		(*i)++;
	
}



char	*expand_heredocs(char *unexpanded)
{
	int	i;
	int	k;
	char *expanded;

	i = 0;
	k = 0;
	expanded = ft_xcalloc(65000, 1);
	while (unexpanded[i])
	{
		if (unexpanded[i] == '$')
		{
			expand_envvar(unexpanded, expanded, &i, &k);
		}
		expanded[k]=unexpanded[i];
		i++;
		k++;
	}
	free(unexpanded);
	return (expanded);
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
