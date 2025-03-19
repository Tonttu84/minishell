/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:59:49 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/19 11:33:08 by jrimpila         ###   ########.fr       */
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

//We need to create a named temporary file. Luckily there is a limit on how many of these can be

// O_EXCL prevents the file from being linked to 
//filesystem when used together with __)

static char *ft_itoa_rec(unsigned int nbr, char *buffer)
{
    if (nbr >= 10)
        buffer = ft_itoa_rec(nbr / 10, buffer);
    *buffer = (nbr % 10) + '0'; 
    return (++buffer); 
}

static char *ft_itoa(unsigned int nbr)
{
    static char result[12]; 
    char *buffer = result;

    buffer = ft_itoa_rec(nbr, buffer); 
    *buffer = '\0'; 

    return result;
}



int open_temp_heredocs(t_node *node, int expand)
{
    int     fd;
    char    *file_name;
    char    *txt;
    char    *eof;
	static unsigned int suffix = 0;

    file_name = ft_strjoin("/tmp/here_docs_", ft_itoa(suffix++));
    fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0640);
    if (fd == -1)
    {
        perror("Failed to create a tmp file\n");
        free(file_name);
        return (fd);
    }
    eof = cnvrt_to_char(node->str);
    txt = create_heredoc(eof, expand, NULL, NULL);
    free(eof);
    eof = NULL;
    if (write(fd, txt, ft_strlen(txt)) < 0)
    {
		unlink(file_name);
		free(file_name);
        perror("Write error");
        close(fd);
        free(txt);
        return (-1);
    }
	close(fd);
	fd = open(file_name, O_RDWR, 0640);
    if (fd == -1)
		perror("Failed to create a tmp file\n");
	unlink(file_name);
	free(file_name);
    free(txt);
    return (fd); 
}

