/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:56:50 by jtuomi            #+#    #+#             */
/*   Updated: 2025/03/12 19:08:49 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <signal.h>

extern volatile sig_atomic_t	flag;

void	signal_handler(int sig_nbr)
{
	flag = sig_nbr;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	void_signal(int sig_nbr)
{
	flag = sig_nbr;
	rl_redisplay();
}

void	set_signals(void)
{
	struct sigaction	sigint;
	struct sigaction	sigquit;
	sigset_t			blocked;

	sigemptyset(&blocked);
	sigaddset(&blocked, SIGINT);
	sigaddset(&blocked, SIGQUIT);
	sigint.sa_handler = signal_handler;
	sigint.sa_mask = blocked;
	sigint.sa_flags = 0;
	sigquit.sa_handler = SIG_IGN;
	sigaction(SIGTSTP, &sigint, NULL);
	sigaction(SIGINT, &sigint, NULL);
	sigaction(SIGQUIT, &sigquit, NULL);
}

void	unset_signals(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

void	block_signals_in_parent(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}
