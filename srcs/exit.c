/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:55:05 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/19 21:51:01 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exit(t_data *data, char *message, int exit_code)
{
	// free everything
	(void)data;
	fprintf(stderr, "%s\n", message);
	exit(exit_code);
}
