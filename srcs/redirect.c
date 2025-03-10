/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 13:25:30 by jtuomi            #+#    #+#             */
/*   Updated: 2025/03/10 14:50:40 by jtuomi           ###   ########.fr       */
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
    printf("append: %s", sent);
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

static void handle_outfile(char *sent, int fd)
{
    fd = open(sent, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (-1 == fd)
        print_error_and_exit(sent, errno);
    printf("outfile: %s", sent);
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

static void handle_infile(char *sent, int fd)
{
    fd = open(sent, O_RDONLY);
    if (-1 == fd)
        print_error_and_exit(sent, errno);
    printf("infile: %s", sent);
    dup2(fd, STDIN_FILENO);
    close(fd);
}

static void handle_heredoc(char *sent, int fd)
{
    sent = create_heredoc(sent, 0);
    write(fd, sent, ft_strlen(sent));
}

void handle_redirection(char *sentence, enum e_token type, int fd)
{
    if (type == APPEND)
        handle_append(sentence, fd);
    else if (type == OUT_FILE)
        handle_outfile(sentence, fd);
    else if (type == IN_FILE)
        handle_infile(sentence, fd);
    else
        handle_heredoc(sentence, fd);
}
