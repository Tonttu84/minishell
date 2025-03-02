/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:11:31 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/02 17:43:45 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	process(char *line)
{
	t_data	*data;
	t_char	*result;

	data = get_data();
	result = lexify(line, data);
	printf("\n");
	free(result);
	result = NULL;
	iterate_list(&data->tokens, print_node);
	create_page(&data->tokens);
}

void	prompt_input(void)
{
	char	*line;
	int pfd[2];

	pipe(pfd);
	while (1)
	{
		line = readline("minishell> ");
		if (line == NULL)
			break ;
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		process(line);
		execute(get_data()->page[0], pfd, 1);
		free(line);
	}
}

