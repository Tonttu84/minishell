/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:07:43 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/06 11:54:31 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

//old is static char	**is_path_in_env(t_data *data, char *s, char *s1, int i)
static char	*is_path_in_env(t_data *data, char *s, char *s1, int i)
{
	while (data->env[i])
	{
		s1 = ft_strnstr(data->env[i], s, 5);
		if (s1)
			{
				//return (ft_split(&data->env[i][5], ':'));
				return (data->env + i);
			}
			
		i++;
	}
	return (NULL);
}

/*
** checks whether command can be found and if it can't replaced the command
** later to be executed by /usr/lib/command-not-found to offer suggestions
** how to install or fix a typo etc.
*/


//Check if arrays are malloced;
static void	command_not_found(t_data *data, int nbr)
{
	int		i;
	
	free(data->page[nbr]->array[1]);
	data->page[nbr]->array[1] = data->page[nbr]->array[0];
	data->page[nbr]->array[0] = ft_strdup("/usr/lib/command-not-found");
	i = 2;
	while (data->page[nbr]->array[i])
		{
			free(data->page[nbr]->array[i]);
			data->page[nbr]->array[i]= NULL;
			i++;
		}
}

/*
** this seeks path, check what kind of command we're dealing with and
** calls the other functions accordingly.
*/
void	util_parse_args(t_data *data, int i)
{
	char *temp;
	
	if (data->env[0])
	{
		temp = is_path_in_env(data, "PATH=", NULL, 0);
		data->path = ft_split(temp[5], ':');
		//data->path = is_path_in_env(data, "PATH=", NULL, 0);
	}
	while (data->page[i]->array[0])
	{
		/* Currently this is checking if the first slot is empty which doesnt seem to be what is intended
		if (!data->env[0])
		{
			if (path_is_abs_or_rel(pipex, i))
				return ;
			command_not_found(pipex, i);
			return ;
		}
		*/
		if (path_is_abs_or_rel(data, i))
			;
		else if (command_in_path(data, i, NULL, 0))
			command_not_found(data, i);
		i++;
	}
}

/*
** if there is a / in any command it is just executed like in bash.
** checks just for that case.
*/
bool	path_is_abs_or_rel(t_data *data, int nbr)
{
	return (ft_strchr(data->page[nbr]->array[0], '/'));
}
/*
** this join / to end of every file in path and that to command
** then checks with access if file exists and tries to see
** whether that file is also executable (has those rights).
*/
bool	command_in_path(t_data *data, int nbr, char *cmd_p, int i)
{
	char	*tmp;

	while (data->path[i])
	{
		tmp = ft_strjoin(data->path[i], "/");
		if (!tmp)
			free_and_exit(data, NULL, "malloc", errno);
		cmd_p = ft_strjoin(tmp, data->page[nbr]->array[0]);
		if (!cmd_p)
			free_and_exit(NULL, NULL, "malloc", errno);
		free(tmp);
		if (0 == access(cmd_p, X_OK))
		{
			free(data->page[nbr]->array[0]);
			data->page[nbr]->array[0] = cmd_p;
			break ;
		}
		else
			free(cmd_p);
		i++;
	}
	if (!access(data->page[nbr]->array[0], X_OK) && path_is_abs_or_rel(data,
			nbr))
		return (false);
	return (true);
}