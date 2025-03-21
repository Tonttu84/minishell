/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:11:31 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/20 14:54:37 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cwd(void)
{
	getcwd(get_data()->cwd, sizeof(get_data()->cwd));
	return (0);
}

void	process(char *line)
{
	t_data	*data;
	t_char	*result;

	data = get_data();
	result = lexify(line, data);
	free(result);
	result = NULL;
	iterate_list(&data->tokens, print_node);
	create_page(&data->tokens);
}

static char	*rl_gets(void)
{
	static char	*line = NULL;
	static char	*strcwd;
	static char	*tmp;

	cwd();
	tmp = ft_strjoin(PROMPT, get_data()->cwd);
	strcwd = ft_strjoin(tmp, BRIGHT_YELLOW "😎>" RESET);
	free(tmp);
	tmp = NULL;
	if (line)
	{
		free(line);
		line = NULL;
	}
	line = readline(strcwd);
	free(strcwd);
	strcwd = NULL;
	if (line && *line)
		add_history(line);
	return (line);
}

int	prompt_input(char *line, int pfd[2], t_data *data, int input)
{
	set_signals();
	if (input == 1)
		input = 0;
	else
		line = rl_gets();
	rl_on_new_line();
	if (line == NULL)
		return (1);
	else if (line[0] == '\0')
		return (0);
	process(line);
	if (data->page[0] && !data->page[0]->inpipe && !data->page[0]->outpipe
		&& is_builtin(data->page[0]->array[0]))
		store_return_value(run_builtin(data->page[0]->argc,
				data->page[0]->array, data->page[0]), true);
	else
	{
		util_parse_args(data, 0);
		block_signals_in_parent();
		if (-1 == pipe(pfd))
			ft_exit(data, "pipe", strerror(errno), errno);
		store_return_value(execute(data->page[0], pfd, 1, 0), true);
	}
	return (0);
}
