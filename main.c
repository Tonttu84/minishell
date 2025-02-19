/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:36:25 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/19 15:32:04 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size);


//Creates a copy of env variables
void init(char env_cpy[MAX_VARS + 1][MAX_LENGHT + 1], char **orig, t_data *data)
{
	int i;

	(void) data;
	i = 0;
	while (i < MAX_VARS && orig[i])
	{
		ft_strlcpy(env_cpy[i], orig[i], MAX_LENGHT);
		i++;
	}
}


int main(int argc, char **argv, char *envp[])
{
	static t_data	data[1];
	
	(void) argv;
	if (argc != 1)
	{
		return (-1);
	}
	init(data->env, envp, data);
	test(data);
}

