/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 13:25:30 by jtuomi            #+#    #+#             */
/*   Updated: 2025/03/02 15:09:03 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <unistd.h>

void print_error_and_exit(char *error_msg, int error_nbr);

static void handle_append(char *sent, int fd)
{
    fd = open(sent, O_WRONLY | O_CREAT, 0644);
    if (-1 == fd)
        print_error_and_exit(sent, errno);
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

static void handle_outfile(char *sent, int fd)
{
     fd = open(sent, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (-1 == fd)
        print_error_and_exit(sent, errno);
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

static void handle_infile(char *sent, int fd)
{
    fd = open(sent, O_WRONLY);
    if (-1 == fd)
        print_error_and_exit(sent, errno);
    dup2(fd, STDIN_FILENO);
    close(fd);
}

static void handle_heredoc(char *sent)
{
    //TODO: how?
}

void handle_redirection(char *sentence, enum e_token type)
{
    if (type == APPEND)
        handle_append(sentence, -1);
    else if (type == OUT_FILE)
        handle_outfile(sentence, -1);
    else if (type == IN_FILE)
        handle_infile(sentence, -1);
    else
        handle_heredoc(sentence);
}
