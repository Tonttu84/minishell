/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:32:40 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/16 12:16:39 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// unset can take multiple argumetns
// rewrite to deal with

static int	unset_one(char *env_val)
{
	t_data	*data;
	int		i;
	int		lenght;

	i = 0;
	data = get_data();
	if (env_val == NULL)
		return (1);
	lenght = ft_strlen(env_val);
	while (i < ENV_SIZE)
	{
		if (ft_strncmp(env_val, data->env[i], lenght + 1)
			&& (data->env[i][lenght] == 0 || data->env[i][lenght] == '='))
		{
			ft_memset(data->env[i], 0, MAX_LENGTH + 1);
			return (1);
		}
		i++;
	}
	return (0);
}
//seems to return 0 even if the value does not exist, maybe errors if you cant find env variable
int	bi_unset(int argc, char *argv[], t_sent *sent)
{
	int	i;

	if (argc == 1 || sent->inpipe || sent->outpipe)
		return (0);
	i = 1;
	while (i < argc)
	{
		if (argv[i])
		{
			unset_one(argv[i]);
		}
		i++;
	}
	return (0);
}

// Gets the variable name ,
//	value and location of the free slot as input and writes the value there
int	set_envvar(char env[ENV_SIZE + 1][MAX_LENGTH + 1], char *envvar,
		char *value, int free_slot)
{
	int	i;
	int	k;

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

// First it unsets the variable, then it adds it with a new value
int	add_envvar(char env[ENV_SIZE + 1][MAX_LENGTH + 1], char *envvar,
		char *value)
{
	int	i;

	if (envvar == NULL || value == NULL)
		return (1);
	unset_one(envvar);
	i = 0;
	while (i < ENV_SIZE)
	{
		if (env[i][0] == '\0')
			return (set_envvar(env, envvar, value, i));
		i++;
	}
	perror("Env variables full\n");
	return (231);
}
// Not sure if Im sorting alphabetically or counter alphabetically;
void	sort_cpy(char **cpy)
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
void	final_print(char **env)
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

// bash: export: `': not a valid identifier
// Not sure what the valid env variable values can be
int	errorcheck_expand(char *var)
{
	int	i;

	i = 0;
	if (!var || (var[i] != '_' && ft_isalpha(var[i]) == 0))
	{
		perror("Not a valid variable");
		return (-1);
	}
	while (ft_isalnum(var[i]) || var[i] == '_')
		i++;
	if (var[i] != 0 && var[i] != '=')
	{
		perror("Not a valid variable");
		return (-1);
	}
	return (0);
}

void	process_new_envvarr(char env[ENV_SIZE + 1][MAX_LENGTH + 1], char *var)
{
	char	name[MAX_LENGTH + 1];
	char	value[MAX_LENGTH + 1];
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (k < MAX_LENGTH + 1 && var[i] != '=' && var[i] != '\0')
	{
		name[k] = var[i];
		i++;
		k++;
	}
	name[k] = '\0';
	if (var[i] == '=')
		i++;
	k = 0;
	while (k < MAX_LENGTH + 1 && var[i] != '\0')
	{
		value[k] = var[i];
		k++;
		i++;
	}
	value[k] = '\0';
	add_envvar(env, name, value);
}

int	bi_export(int argc, char *argv[], t_sent *sent)
{
	int	i;

	if (argc == 1)
		return (print_alphabetically(get_data()->env));
	if (sent->outpipe || sent->inpipe)
		return (0);
	i = 1;
	while (i < argc)
	{
		if (argv[i] && errorcheck_expand(argv[i]))
		{
			perror("Print error, set errno and so on");
			return (-1);
		}
		i++;
	}
	i = 1;
	while (i < argc)
	{
		if (argv[i])
			process_new_envvarr(get_data()->env, argv[i]);
		i++;
	}
	return (0);
}
