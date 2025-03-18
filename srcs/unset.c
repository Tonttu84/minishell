/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:25:07 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/18 12:46:40 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	unset_one(char *env_val)
{
	t_data	*data;
	int		i;
	int		lenght;

	i = 0;
	data = get_data();
	if (env_val == NULL)
		return (1);
	lenght = ft_strlen(env_val);
	while (i < ENV_SIZE)
	{
		if (!ft_strncmp(env_val, data->env[i], lenght + 1)
			&& (data->env[i][lenght] == 0 || data->env[i][lenght] == '='))
		{
			ft_memset(data->env[i], 0, MAX_LENGTH + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

//BASH seems to return 0 even if the value does not exist
int	bi_unset(int argc, char *argv[], t_sent *sent)
{
	int	i;

	if (argc == 1 || sent->inpipe || sent->outpipe)
		return (0);
	i = 1;
	while (i < argc)
	{
		if (argv[i])
		{
			unset_one(argv[i]);
		}
		i++;
	}
	return (0);
}
