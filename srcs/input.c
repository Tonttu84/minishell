/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:11:31 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/10 13:02:55 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

void	process(char *line)
{
	t_data	*data;
	t_char	*result;

	data = get_data();
	result = lexify(line, data);
	write(1, "\n", 1);
	free(result);
	result = NULL;
	iterate_list(&data->tokens, print_node);
	create_page(&data->tokens);
}

static char *rl_gets(void)
{
	static char *line = NULL;

	if (line)
	{
		free (line);
		line = NULL;
	}
	line = readline(PROMPT);
	if (line && *line)
		add_history(line);
	return line;
}

void	prompt_input(void)
{
	char	 *line;
	int pfd[2];

	pipe(pfd);
	while (1)
	{
		line = rl_gets();
		if (line == NULL)
			break ;
		if (line[0] == '\0')
			continue ;
		process(line);
		util_parse_args(get_data(), 0);
		execute(get_data()->page[0], pfd, 1, 0);
	}
}

