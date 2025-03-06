/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:21:10 by jtuomi            #+#    #+#             */
/*   Updated: 2025/03/06 12:01:39 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*is_path_in_env(void)
{
    t_data *data;
    int i;
    char *s1;

    data = get_data();
    i = 0;
    while (data->env[i])
	{
		s1 = ft_strnstr(data->env[i], "PATH=", 5);
		if (s1)
			return (&data->env[i][5]);
		i++;
	}
	return (NULL);
}

/*
** checks whether command can be found and if it can't replaced the command
** later to be executed by /usr/lib/command-not-found to offer suggestions
** how to install or fix a typo etc.
*/
static void	command_not_found(int nbr)
{
    t_data *data;
    char *s;

    data = get_data();
    s = "/usr/lib/command-not-found";
    ft_memmove(data->page[nbr]->array[1], data->page[nbr]->array[0], \
               ft_strlen(data->page[nbr]->array[1]));
	ft_memmove(data->page[nbr]->array[0], s, ft_strlen(s) + 1);
}

bool   command_in_path(char *path, int nbr, char *cmd_p, int i);
/*
** this seeks path, check what kind of command we're dealing with and
** calls the other functions accordingly.
*/
void	util_parse_args(t_data *data, int i, void *ptr, bool flag)
{
	(void) flag;
	if (data->env[0])
	{
		ptr = is_path_in_env();
	
	}
	while (data->page[i]->array[0])
	{
        if (ft_strnstr(data->page[i]->array[0], "/", 100))
			 ;
        else if (command_in_path(ptr, i, NULL, 0))
			command_not_found(i);
		i++;
	}
}

void print_error_and_exit(char *error_msg, int error_nbr);
/*
** this join / to end of every file in path and that to command
** then checks with access if file exists and tries to see
** whether that file is also executable (has those rights).
*/
bool	command_in_path(char *path, int nbr, char *cmd_p, int i)
{
	char	*tmp;
    char    *full_path_cmd;

	(void) i;
    cmd_p = ft_strjoin("/", get_data()->page[nbr]->array[0]);
	while (path)
	{
        tmp = path;
        path = ft_strchr(path, ':');
        tmp = ft_substr(tmp, 1, path - tmp - 1);
        if (!tmp)
            print_error_and_exit("malloc", ENOMEM);
        full_path_cmd =  ft_strjoin(tmp, cmd_p);
        if (!full_path_cmd)
            print_error_and_exit("malloc", ENOMEM);
        free(tmp);
        if (!access(full_path_cmd, X_OK))
            break;
	}
	return (true);
}
