/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:36:25 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/27 12:19:05 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size);

// Creates a copy of env variables
void	init(char env_cpy[MAX_VARS + 1][MAX_LENGTH + 1], char **orig)
{
	int	i;

	i = 0;
	while (i < MAX_VARS && orig[i])
	{
		ft_strlcpy(env_cpy[i], orig[i], MAX_LENGTH);
		i++;
	}
	get_data()->env_count = i;
}

int	main(int argc, char **argv, char *envp[])
{

	(void)argv;
	if (argc != 1)
	{
		return (-1);
	}
	init(get_data()->env, envp);
	test();
}
