/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:24:54 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/01 20:58:55 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	copy_env_to_tchar(t_char *dst, int i, const char *env)
{
	int env_i;

	if (env == NULL)
		return (i);
	env_i = 0;
	while (env[env_i])
	{
		dst[i].c = env[env_i];
		dst[i].var = 1;
		dst[i].esc = 0;
		dst[i].com = 0;
		dst[i].ghost = 0;
		dst[i].added = 0;
		i++;
		env_i++;
	}
	return (i);
}
