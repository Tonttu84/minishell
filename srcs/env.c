/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:32:26 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/21 19:33:19 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*get_env can have special characters

! is not a valid variable

export SPECIAL_VAR=1@#$%^&*()_!3+{}|:"<>?-=ta[]\;d,./`~
export SPECIAL_VAR=1@#$%^&*()_cd ..+{}|:"<>?-=ta[]\;d,./`~
bash: syntax error near unexpected token `_cd'


jrimpila@c1r1p11:~/Hiveprojects/philo5.3$ export SPECIAL_VAR=1!@#$%^&*()_3+{}|:"<>?-=ta[]\;d,./`~
bash: !@#: event not found
*/

// returns 1 for match, 0 for no match.
int	match_env_argument(t_char *source, char *env_var)
{
	int	i;

	i = 0;
	if (env_var == NULL || env_var[0] == '\0')
		return (0);
	if (source[0].c != '$' || (ft_isalnum(source[1].c) == 0
			&& source[1].c != '_'))
		perror("DEBUG iffy input to match_env_argument\n");
	i = 1;
	while (env_var[i - 1] && source[i].c && source[i].c == env_var[i - 1]
		&& source[i].var)
	{
		i++;
	}
	if (source[i].var == 0 && env_var[i - 1] == '=')
		return (1);
	return (0);
}

const char	*ft_get_env(const char *target)
{
	int	i;

	i = 0;
	if (target == NULL)
		return (NULL);
	while (*target && *target != '=')
		target++;
	if (*target == '=')
		target++;
	return (target);
}

// export finds all, ENV only finds if there is =

const char	*find_env(t_char *source, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->env_count)
	{
		if (match_env_argument(source, data->env[i]))
			return (ft_get_env(data->env[i]));
		i++;
	}
	return (NULL);
}

void	env(t_data *data)
{
	const char	*str;
	int			i;

	i = 0;
	str = NULL;
	while (i < MAX_LENGTH)
	{
		str = ft_get_env(data->env[i]);
		if (str && str[0])
			printf("%s\n", str);
		i++;
	}
}
