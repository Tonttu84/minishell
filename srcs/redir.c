/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 15:39:47 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/01 16:12:58 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
//Double check that the struct keeps the t_dir alive even after this returns
void  add_redirection(t_node *node, t_sent *sentence, int i)
{
	
	if (node->str)
		sentence->redirs[i].path = cnvrt_to_char(node->str);
	else 
		sentence->redirs[i].path = ft_strdup("\0");
	sentence->redirs[i].type = node->type;

}