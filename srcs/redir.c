/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 15:39:47 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/19 14:20:34 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_redirection(t_node *node, t_sent *sentence, int i)
{
	if (node->type == HERE_DOCS && (node->str[0].esc || node->str[0].blok))
		sentence->redirs[i].type = HERE_QUOTE;
	else
		sentence->redirs[i].type = node->type;
	if (sentence->redirs[i].type == HERE_DOCS)
		sentence->redirs[i].here_fd = open_temp_heredocs(node, 0);
	else if (sentence->redirs[i].type == HERE_QUOTE)
		sentence->redirs[i].here_fd = open_temp_heredocs(node, 1);
	else if (node->str)
		sentence->redirs[i].path = cnvrt_to_char(node->str);
	else
	{
		error_printf("", "syntax error near unexpected token `newline'");
		sentence->redirs[i].path = ft_strdup("\0");
	}
}
