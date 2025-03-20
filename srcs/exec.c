/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:21:45 by jtuomi            #+#    #+#             */
/*   Updated: 2025/03/18 20:16:56 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		handle_redirection(char *sentence, enum e_token type, int fd);
static void	deal_with_sentence(t_sent *sentence, int i, int pfd[2]);

/*
 * all the forked subprocesses end up here, redirections are dealt with
 * and commands get executed.
 */
static void execute_child(t_sent *sent, int pfd[2], pid_t child, int i)
{
	if (!child)
	{
		unset_signals();
		deal_with_sentence(sent, -1, pfd);
		if (!sent->array[0])
			exit(0);
		if(is_builtin(sent->array[0]))
			run_builtin(get_data()->page[i]->argc,
						sent->array, get_data()->page[0]);
		if (-1 == execve(sent->array[0], sent->array, __environ))
			ft_exit(get_data(), sent->array[0], strerror(errno), errno);
	}
	else if(child == -1)
		ft_exit(get_data(), "fork", strerror(errno), errno);
}

/*
** this is forks recursively as long as there are new commands
*/
int	execute(t_sent *sentence, int pfd[2], pid_t my_child, int state)
{
	static int	i;
	int			ret;

	if (my_child > 0 && get_data()->page[i])
		return (execute(get_data()->page[i++], pfd, fork(), 0));
	execute_child(sentence, pfd, my_child, i);
	close(pfd[0]);
	close(pfd[1]);
	while (i)
	{
		if (my_child == waitpid(0, &state, 0))
			ret = state;
		i--;
	}
	i = 0;
	if (WIFEXITED(ret))
		return (WEXITSTATUS(ret));
	return (EXIT_SUCCESS);
}

/*
** take from sentence the out and infiles plus here docs and dup2 them to
** stdin or out.
*/
void	deal_with_sentence(t_sent *sentence, int i, int pfd[2])
{
	while (sentence->redirs[++i].path)
	{
		if (sentence->redirs[i].type == APPEND)
			handle_redirection(sentence->redirs[i].path, APPEND, -1);
		else if (sentence->redirs[i].type == OUT_FILE)
			handle_redirection(sentence->redirs[i].path, OUT_FILE, -1);
		else if (sentence->redirs[i].type == IN_FILE)
			handle_redirection(sentence->redirs[i].path, IN_FILE, -1);
		else if (sentence->redirs[i].type == HERE_DOCS)
			handle_redirection(sentence->redirs[i].path, HERE_DOCS, pfd[0]);
	}
	if (sentence->inpipe)
		dup2(pfd[STDIN_FILENO], STDIN_FILENO);
	if (sentence->outpipe)
		dup2(pfd[STDOUT_FILENO], STDOUT_FILENO);
	close(pfd[STDIN_FILENO]);
	close(pfd[STDOUT_FILENO]);
}
