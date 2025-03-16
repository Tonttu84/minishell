/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:55:05 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/15 12:48:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <unistd.h>

void	ft_exit(t_data *data, char *cmd, char *message, int exit_code)
{
	// free everything
	(void)data;
	error_printf(cmd, message);
	exit(exit_code);
}

void error_printf(char *cmd, char *message)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("minishell: %s: %s\n", cmd, message);
}

void	deallocate(void);
