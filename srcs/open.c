/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:59:49 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/18 12:20:02 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//Seem to be unused, delete if commenting out doesnt break anything

// char	*test_outfile(t_char *raw_path)
// {
// 	int		fd;
// 	char	*proc_path;

// 	proc_path = cnvrt_to_char(raw_path);
// 	fd = open(proc_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	close(fd);
// 	if (fd == -1)
// 		return (NULL);
// 	return (proc_path);
// }

// char	*test_append(t_char *raw_path)
// {
// 	int		fd;
// 	char	*proc_path;

// 	proc_path = cnvrt_to_char(raw_path);
// 	fd = open(proc_path, O_WRONLY | O_CREAT, 0644);
// 	close(fd);
// 	if (fd == -1)
// 		return (NULL);
// 	return (proc_path);
// }

// O_EXCL prevents the file from being linked to 
//filesystem when used together with __)
int	open_temp_heredocs(t_node *node, int expand)
{
	int		fd;
	char	*eof;
	char	*txt;

	fd = open("/tmp", O_RDWR | __O_TMPFILE, 0640);
	if (-1 == fd)
	{
		perror("Failed to create a tmp file\n");
		return (fd);
	}
	eof = cnvrt_to_char(node->str);
	printf("%s\n", eof);
	txt = create_heredoc(eof, expand, NULL, NULL);
	free(eof);
	eof = NULL;
	if (0 > write(fd, txt, ft_strlen(txt)))
	{
		perror("Write error, what to do");
	}
	free(txt);
	return (fd);
}
