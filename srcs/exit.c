/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:55:05 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/20 15:38:54 by jrimpila         ###   ########.fr       */
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
	exit(exit_code);
}

void error_printf(char *cmd, char *message)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("minishell: %s: %s\n", cmd, message);
}

void	deallocate(t_data *data)
{
	int i;
	int i1;

	i = 0;
	while(data->path[i])
	{
		free(data->path[i]);
		data->path[i++] = NULL;
	}
	free(data->path);
	data->path = NULL;
	i = 0;
	i1 = 0;
	while(data->page[i])
	{
		while(data->page[i]->array[i1])
		{
			free(data->page[i]->array[i1]);
			data->page[i]->array[i1++] = NULL;
		}
		free(data->page[i]);
		data->page[i++] = NULL;
	}

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
			exit (0);
		}
	}
	exit_status = ft_atoi_spec(argv[1], 0);
	if (exit_status == 2 && ft_strncmp(argv[1], "2", 2) != 0)
	{
		if (sentence->outpipe || sentence->inpipe)
			return (2);
		else
		{
			deallocate(get_data());
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
		exit (exit_status);
	}
	return (exit_status);
	
}
