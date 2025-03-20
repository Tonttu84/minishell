/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:55:05 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/20 17:16:03 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <unistd.h>

/*
 *frees all heap memory, prints message to stderr and exits with correct code
 */
void	ft_exit(t_data *data, char *cmd, char *message, int exit_code)
{
	deallocate(data);
	error_printf(cmd, message);
	rl_clear_history();
	exit(exit_code);
}

/*
** writes to stderr
 */
void error_printf(char *cmd, char *message)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("minishell: %s: %s\n", cmd, message);
}

/*
** frees memory
*/
void	deallocate(t_data *data)
{
	int i;

	destroy_old_page();
	i = 0;
	while(data->path && data->path[i])
	{
		free(data->path[i]);
		data->path[i++] = NULL;
	}
	free(data->path);
	data->path = NULL;
}

/*
*   checks with what value and if to exit at all.
*/
static int check_exit_status(int exit_status, t_sent *sentence,
   char **argv, int argc)
{
   	if (exit_status == 2 && ft_strncmp(argv[1], "2", 2) != 0)
	{
		if (sentence->outpipe || sentence->inpipe)
			return (2);
		else
		{
			deallocate(get_data());
			rl_clear_history();
			exit (2);
		}
	}
	if (argc > 2)
	{
		error_printf("exit", "too many arguments");
		return (127);
	}
	if (sentence->outpipe == 0 && sentence->inpipe == 0)
	{
		deallocate(get_data());
		rl_clear_history();
		exit (exit_status);
	}
	return (exit_status);
}

//bash exits if first argument is  illegal even if it has too many arguments
//if both arguments are legal it will fail to exit
int	bi_exit(int argc, char *argv[], t_sent *sentence)
{
	int exit_status;

	printf("exit\n");
	if (argc == 0)
	{
		if (sentence->outpipe || sentence->inpipe)
			return (0);
		else
		{
			deallocate(get_data());
			rl_clear_history();
			exit (0);
		}
	}
	exit_status = ft_atoi_spec(argv[1], 0);
	return (check_exit_status(exit_status, sentence, argv, argc));
}
