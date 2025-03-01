/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:32:40 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/01 14:24:22 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

int unset(char **env, char *envvar)
{
    int i;
    int len;
    int k;

    k = 0;
    len = strlen(envvar);
    i = 0;
    while(env[i] != NULL)
    {
        if (strncmp(env[i], envvar, len) == 0)
        {
            if (env[i][len] == '=' || env[i][len] == '\0')
            {
                while (env[i][k] != '\0')
                {
                    env[i][k] = '\0';
                    k++;
                }
                return (0);
            }
        }
        i++;
    }
    return (1);
}


int set_envvar(char **env, char *envvar, char *value, int free_slot)
{
    int i;
    int k;

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
int add_envvar(char **env, char *envvar, char *value)
{
    int i;

    unset(env, envvar);
    i = 0;
    while (i < ENV_SIZE)
    {
        if (env[i] == NULL || env[i][0] == '\0')
            return (set_envvar(env, envvar, value, i));
        i++;
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
	while (k < ENV_SIZE && cpy[k])
	{
		i = 0;
		while(i < ENV_SIZE && cpy[i])
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
	while (i < ENV_SIZE && env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
}


int print_alphabetically(char **env)
{
    char *cpy[ENV_SIZE + 1];
    int  i;
    int  k;

    i = 0;
    k = 0;

    while (env[k] != NULL)
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


//Not sure what the valid env variable values can be
int errorcheck_expand(char *var)
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


void process_new_envvarr(char **env, char *var)
{
    char name[MAX_LENGTH + 1];
    char value[MAX_LENGTH + 1];
    int  i;
    int  k;

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

int export(int argc, char *argv[], char **env)
{
    int i;

    if (argc == 1)
        return(print_alphabetically(env));

    for (i = 1; i < argc; i++)
    {
        if (errorcheck_expand(argv[i]))
        {
            perror("Print error, set errno and so on");
            return (-1);
        }
    }

    for (i = 1; i < argc; i++)
    {
        process_new_envvarr(env, argv[i]);
    }
    return (0);
}
