/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:32:40 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/28 16:49:25 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

int	unset(char *envvar)
{
	int i;
	int	len;
	int k;
	char **env;

	env = get_data()->env;
	k = 0;
	len = ft_strlen(envvar);
	i = 0;
	while(i < ENV_SIZE)
	{
		if (ft_strncmp(env[i], envvar, len) == 0)
		{
			if (env[i][len] == '=' || env[i][len] == '\0')
			{
				while (k < MAX_LENGTH)
					{
						env[i][k] = '\0';
						k++;
					}
				return (0);
			}
		}
		
	}
	return (1);
}

int set_envvar(char *envvar, char *value, int free_slot)
{
	int i;
	int k;
	char **env;

	env = get_data()->env;
	i = 0;
	while (envvar[i] && i < MAX_LENGTH)
	{
		env[free_slot][i] = envvar[i];
		i++;
	}
	if (envvar[i])
		return (perror("Env max exceeded\n"), 1);
	if (value && i < MAX_LENGTH)
	{
		env[free_slot][i] = '=';
		i++;	
	}
	k = 0;
	while (value && value[k] && i < MAX_LENGTH)
	{
		env[free_slot][i] = value[k];
		i++;
		k++;
	}
	if (value[k])
		return (perror("Env max exceeded\n"), 1);
	return (0);
}
//Value van be NULL or \0, if NULL then dont set the =
int add_envvar(char *envvar, char *value)
{
	char **env;
	int i;
	
	env = get_data()->env;
	unset(envvar);
	i = 0;
	while (i < ENV_SIZE)
	{
		if (env[i] == NULL)
			i++;
		else
		{
			return (set_envvar(envvar, value, i));
		}
	}
	perror("Env variables full\n");
	return (231);
}


void sort_cpy(char **cpy)
{
	int		i;
	char	*tmp;

	int k;
	k = 0;
	while (k < MAX_VARS && cpy[k])
	{
		i = 0;
		while(i < MAX_VARS && cpy[i])
		{
		//Not sure if Im sorting alphabetically or counter alphabetically;
			if (cpy [i + 1] && ft_strncmp(cpy[i], cpy[i + 1], MAX_LENGTH))
			{			
				tmp = cpy[i];
				cpy[i] = cpy [i + 1];
				cpy[i + 1] = tmp;
				
			}
		}
		k++;
	}
}

void	final_print(char **env)
{
	int	i;

	i = 0;
	while (i < MAX_VARS && env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
}


int print_alphabetically(void)
{
	char	*env[MAX_VARS];
	char	**orig;
	int		i;
	int		k;
	
	i = 0;
	k = 0;
	orig = get_data()->env;
	while (k < MAX_VARS)
	{
		if (orig[k])
		{
			env[i] = orig[k];
			i++;
		}
		k++;
	}
	while (i < MAX_VARS)
	{
		env[i] = NULL;
		i++;
	}
	sort_cpy(env);
	final_print(env);
	return (0);

}


void	process_new_envvarr(char *var)
{
	char	name[MAX_LENGTH + 1];
	char	value[MAX_LENGTH + 1];
	int		i;
	int		k;
	
	i = 0;
	k = 0;
	while (k < MAX_LENGTH + 1)
	{
		while (var[i] != 0 && var[i] != '=')
		{
			name[k] = var[i];
			i++;
			k++;
		}  
		name[k] = 0;
		k++;
	}
	k = 0;
	while (k < MAX_LENGTH + 1)
	{
		while (var[i] != 0)
		{
			value[k] = var[i];
			k++;
			i++;
		}
		value[k] = 0;
		k++;
	}
	add_envvar(name, value);
}

int export(int argc, char *argv[])
{
	int	i;
	
	if (argc == 1)
		return(print_alphabetically());
	i = 1;
	while (i < argc)
	{
		if (errorcheck(argv[i]))
		{
			perror ("Print error, set errno and so on");
			return (-1);
		}
		i++;
	}
	i = 1;
	while (i < argc)
	{
		process_new_envvarr(argv[i]);
		i++;
	}	
	return (0);
}
