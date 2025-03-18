/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:29:12 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/18 12:49:15 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
static void	sort_cpy(char **cpy);
static void	final_print(char **env);

// Creates an array of pointers that are later sorted and printed
int	print_alphabetically(char env[ENV_SIZE + 1][MAX_LENGTH + 1])
{
	char	*cpy[ENV_SIZE + 1];
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (k < ENV_SIZE)
	{
		if (env[k][0] != '\0')
		{
			cpy[i] = env[k];
			i++;
		}
		k++;
	}
	cpy[i] = NULL;
	sort_cpy(cpy);
	final_print(cpy);
	return (0);
}

static void	sort_cpy(char **cpy)
{
	int		i;
	char	*tmp;
	int		k;

	k = 0;
	while (k < ENV_SIZE && cpy[k])
	{
		i = 0;
		while (i < ENV_SIZE && cpy[i])
		{
			if (cpy[i + 1] && ft_strncmp(cpy[i], cpy[i + 1], MAX_LENGTH) > 0)
			{
				tmp = cpy[i];
				cpy[i] = cpy[i + 1];
				cpy[i + 1] = tmp;
			}
			i++;
		}
		k++;
	}
}

// Prints the variables in the format desired by export;
static void	final_print(char **env)
{
	int	i;

	i = 0;
	while (i < ENV_SIZE && env[i])
	{
		if (ft_strchr(env[i], '=') && (ft_strncmp(env[i], "_=", 2) != 0))
			printf("declare -x \"%s\"\n", env[i]);
		i++;
	}
}


