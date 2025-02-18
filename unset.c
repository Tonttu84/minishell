/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:06:02 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/11 10:21:41 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "printf.h"

int unset_env(const char *var, t_data *data)
{
	char *target;
	int	tar_i;
	
	tar_i = find_env(var, data);
	if (tar_i == -1)
		return (-1);
	else 
		{
			free(data->env[tar_i]);
			data->env[tar_i] = NULL;
		}
	return (0);
}