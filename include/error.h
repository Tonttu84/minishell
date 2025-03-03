/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:51:41 by jtuomi            #+#    #+#             */
/*   Updated: 2025/03/03 14:57:22 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
#define ERROR_H

typedef enum e_error
{
SUCCESS = 0,
FAILURE = 1,
PERMISSION = 126,
COMMAND_NOT_FOUND = 127,
} t_error;

struct s_message
{
    int code;
    const char *message;
} s_message[] = {
{SUCCESS, ""},
{FAILURE, "minishell: "},
{PERMISSION, "Permission denied"},
{COMMAND_NOT_FOUND, "No such file or directory"}
};

typedef struct s_message t_message;
#endif
