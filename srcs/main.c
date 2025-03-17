/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:36:25 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/14 13:53:24 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	flag = 0;

size_t					ft_strlcpy(char *dst, const char *src, size_t size);

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
	int pfd[2];

	(void)argv;
	if (argc != 1)
	{
		return (-1);
	}
	init(get_data()->env, envp);
	set_signals();
	prompt_input(NULL, pfd, get_data());
}
