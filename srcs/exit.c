/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:55:05 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/20 07:04:54 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <unistd.h>

/*
 *frees all heap memory, prints message to stderr and exits with correct code
 */
void	ft_exit(t_data *data, char *cmd, char *message, int exit_code)
{
	deallocate(data);
	error_printf(cmd, message);
	exit(exit_code);
}

void error_printf(char *cmd, char *message)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("minishell: %s: %s\n", cmd, message);
}

void	deallocate(t_data *data)
{
	(void)data;
}
