/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:43:25 by jtuomi            #+#    #+#             */
/*   Updated: 2025/03/10 15:54:36 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int builtin_cd(char *path)
{
    struct stat buf;

    lstat(path, &buf);
    if (buf.st_mode != S_IFDIR || buf.st_mode != S_IFLNK)
       ft_exit(get_data(), path, 1);
    if (-1 == chdir(path))
        ft_exit(get_data(), path, 1);
    return (0);
}
