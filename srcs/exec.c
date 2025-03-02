/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:21:45 by jtuomi            #+#    #+#             */
/*   Updated: 2025/03/02 15:09:01 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdlib.h>
#include <unistd.h>

void handle_redirection(char *sentence, enum e_token type);
void print_error_and_exit(char *error_msg, int error_nbr);
static void print_error_return_control(void);
static void free_and_close(void);
static void deal_with_sentence(t_sent *sentence, int i, int pfd[2]);

/*
** this is called recursively as long as there are new commands to
** execute, with fork going to execve. then we wait for all pids to return.
 */
int execute(t_sent *sentence, int pfd[2], pid_t my_child)
{
    static int i;
    int state;

    if (my_child > 0 && get_data()->page[++i])
        execute(get_data()->page[i], pfd, fork());
    if (!my_child)
    {
        deal_with_sentence(sentence, -1, pfd);
        if (-1 == execve(sentence->array[0], sentence->array, \
                         (char *const *)get_data()->env))
            print_error_and_exit(sentence->array[0], errno);
    }
    else if (my_child == -1)
        print_error_return_control();
    free_and_close();
    while(i-- > 1)
        waitpid(0, &state, 0);
    waitpid(my_child, &state, 0);
    if (WIFEXITED(state))
        return (WEXITSTATUS(state));
    return (EXIT_SUCCESS);
}

void deal_with_sentence(t_sent *sentence, int i, int pfd[2])
{
    while(sentence->redirs[++i].path)
        if (sentence->redirs[i].type == APPEND)
            handle_redirection(sentence->redirs[i].path, APPEND);
        else if (sentence->redirs[i].type == OUT_FILE)
            handle_redirection(sentence->redirs[i].path, OUT_FILE);
        else if (sentence->redirs[i].type == IN_FILE)
            handle_redirection(sentence->redirs[i].path, IN_FILE);
        else
            handle_redirection(sentence->redirs[i].path, HERE_DOCS);
    if (sentence->inpipe)
        dup2(pfd[STDIN_FILENO], STDIN_FILENO);
    else if (sentence->outpipe)
        dup2(pfd[STDOUT_FILENO], STDOUT_FILENO);
    close(pfd[STDIN_FILENO]);
    close(pfd[STDOUT_FILENO]);
}

void print_error_and_exit(char *error_msg, int error_nbr)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(error_msg, 2);
    ft_putstr_fd(": ", 2);
    ft_putstr_fd(strerror(error_nbr), 2);
    if (error_nbr == 2)
        error_nbr = 126;
    else if (error_nbr == 13)
        error_nbr = 127;
    free_and_close();
    exit(error_nbr);
}

void print_error_return_control(void)
{
//TODO: error handling subprocess
}

void free_and_close(void)
{
    //TODO: what to close? what to free?
}
