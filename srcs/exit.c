/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:55:05 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/01 20:59:15 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exit(t_data *data, char *message, int exit_code)
{
	// free everything
	(void)data;
	perror(message);
	exit(exit_code);
}

void	deallocate(void);
