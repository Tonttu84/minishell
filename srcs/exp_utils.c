/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:55:23 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/20 12:46:19 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//Todennakoisesti tahan kohtaan $?

int	match_env_argument_char(char *source, char *env_var)
{
	int	i;

	i = 0;
	if (env_var == NULL || env_var[0] == '\0')
		return (0);
	if ((ft_isalnum(source[1]) == 0 && source[1] != '_'))
		return (0);
	i = 1;
	while (ft_isalnum(source[i]) || source[i] == '_')
	{
		if (source[i] == env_var[i - 1])
			i++;
		else
			break ;
	}
	if ((env_var[i - 1] == 0 || env_var[i - 1] == '=') && !ft_isalnum(source[i])
		&& source[i] != '_')
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
			return (((const char *)data->env[i]));
		i++;
	}
	return (NULL);
}

const char	*find_env_value(char *source, t_data *data)
{
	int			i;
	const char	*ptr;

	i = 0;
	ptr = find_env_char(source, data);
	if (ptr)
	{
		while (ptr[i] && ptr[i] != '=')
			i++;
	}
	if (ptr && ptr[i] == '=')
	{
		i++;
	}
	return (ptr + i);
}

void	expand_envvar(char *unexp, char *exp, int *i, int *k)
{
	const char	*ptr_envvar;
	int			j;

	ptr_envvar = find_env_char(unexp + *i, get_data());
	j = 0;
	while (ptr_envvar && ptr_envvar[j] && ptr_envvar[j] != '=')
		j++;
	if (ptr_envvar[j] == '=')
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
	while (ft_isalnum(unexp[*i]) || unexp[*i] == '_')
		(*i)++;
}
