/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:59:49 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/28 12:09:21 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *test_outfile(t_char *raw_path)
{
	int		fd;
	char	*proc_path;
	
	proc_path = cnvrt_to_char(raw_path);
	fd = open(proc_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	close(fd);
	if (fd == -1)
		return (NULL);		
	return (proc_path);
}
//should maybe return errno
char *test_append(t_char *raw_path)
{
	int		fd;
	char	*proc_path;
	
	proc_path = cnvrt_to_char(raw_path);
	fd = open(proc_path, O_WRONLY | O_CREAT | 0644);
	close(fd);
	if (fd == -1)
		return (NULL);		
	return (proc_path);
}