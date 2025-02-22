/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inbuild.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:05:36 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/21 12:29:44 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int test_inbuilds(t_node *cmd)
{
	if (cmd->str[0].c == 'c' && cmd->str[1].c == 'd' && cmd->str[2].c == 0 && cmd->str[2].esc == 0)
		return (1);
	else if (cmd->str[0].c == 'e' && cmd->str[1].c == 'c' && cmd->str[2].c == 'h'&& cmd->str[1].c == 'o' && cmd->str[2].c == 0 && cmd->str[2].esc == 0)
		return (2);
	else if (cmd->str[0].c == 'e' && cmd->str[1].c == 'n' && cmd->str[2].c == 'v' && cmd->str[3].c == 0 && cmd->str[3].esc == 0)
		return (3);
	else if (cmd->str[0].c == 'e' && cmd->str[1].c == 'x' && cmd->str[2].c == 'o' && cmd->str[3].c == 'r' && cmd->str[5].c == 't' && cmd->str[6].c == 0 && cmd->str[6].esc == 0)
		return (4);
	else if (cmd->str[0].c == 'p' && cmd->str[1].c == 'w' && cmd->str[2].c == 'd' && cmd->str[3].c == 0 && cmd->str[3].esc == 0)
		return (5);
	else if (cmd->str[0].c == 'u' && cmd->str[1].c == 'n' && cmd->str[2].c == 's' && cmd->str[3].c == 'e' && cmd->str[4].c == 't' && cmd->str[5].c == 0 && cmd->str[5].esc == 0)
		return (6);
	else if (cmd->str[0].c == 'e' && cmd->str[1].c == 'x' && cmd->str[2].c == 'i' && cmd->str[3].c == 't' && cmd->str[4].c == 0 && cmd->str[4].esc == 0)
		return (7);
	else
		return (0);

}