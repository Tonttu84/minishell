/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:59:49 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/19 11:55:32 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_itoa_rec(unsigned int nbr, char *buffer)
{
	if (nbr >= 10)
		buffer = ft_itoa_rec(nbr / 10, buffer);
	*buffer = (nbr % 10) + '0';
	return (++buffer);
}

static char	*ft_itoa(unsigned int nbr)
{
	static char	result[12];
	char		*buffer;

	buffer = result;
	buffer = ft_itoa_rec(nbr, buffer);
	*buffer = '\0';
	return (result);
}

int	open_temp_heredocs(t_node *node, int expand)
{
	int					fd;
	char				*file_name;
	char				*txt;
	char				*eof;
	static unsigned int	suffix = 0;

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
