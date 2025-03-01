/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:32:12 by jrimpila          #+#    #+#             */
/*   Updated: 2025/03/01 15:18:32 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		check_emp_arg(char *src, int i, t_char *dst, int *k, int in_d_quotes,
			int in_s_quotes);

void	mark_commands(t_char *com_line, t_data *data)
{
	int	i;

	(void)data;
	i = 0;
	while (com_line[i].c != 0)
	{
		if (i == 0 || com_line[i].esc || com_line[i - 1].esc || com_line[i \
		+ 1].c == 0 || com_line[i + 1].esc)
			;
		else if (com_line[i - 1].c == '<' && !com_line[i - 2].esc && com_line[i \
		- 2].c == ' ' && com_line[i].c == '<' && com_line[i + 1].c == ' ')
		{
			com_line[i].com = 1;
			com_line[i - 1].com = 1;
		}
		else if (com_line[i - 1].c == '>' && !com_line[i - 2].esc && com_line[i \
		- 2].c == ' ' && com_line[i].c == '>' && com_line[i + 1].c == ' ')
		{
			com_line[i - 1].com = 1;
			com_line[i].com = 1;
		}
		else if (com_line[i - 1].c == ' ' && com_line[i].c == '>' && com_line[i \
		+ 1].c == '>' && !com_line[i + 2].esc && com_line[i + 2].c == ' ')
		{
			com_line[i].com = 1;
			com_line[i + 1].com = 1;
		}
		else if (com_line[i].c == '<' && com_line[i + 1].c == '<' && com_line[i \
		+ 2].c != 0 && (com_line[i + 2].esc == 0 && com_line[i + 2].c != ' '))
			com_line[i].com = 1;
		else if (com_line[i - 1].c != ' ' || com_line[i + 1].c != ' ')
			;
		else if (com_line[i].c == '|' || com_line[i].c == '<' \
		|| com_line[i].c == '>')
			com_line[i].com = 1;
		i++;
	}
}

void	mark_env_var(t_char *newline, int start, t_data *data)
{
	int	end;

	(void)data;
	end = start;
	newline[end].var = 1;
	end++;
	if (newline[end].c == 0 || newline[end].esc || (!ft_isalpha(newline[end].c)
			&& newline[end].c != '_'))
		return ;
	else
	{
		newline[end].var = 1;
		end++;
	}
	while (newline[end].ghost || (newline[end].c != 0 && !newline[end].esc
			&& (ft_isalnum(newline[end].c) || newline[end].c == '_')))
	{
		if (newline[end + 1].blok != 1)
			newline[end].var = 1;
		else
			return ;
		end++;
	}
}

void	mark_arguments(t_char *newline, t_data *data)
{
	int	i;

	(void)data;
	i = 0;
	while (newline[i].c != 0)
	{
		if (newline[i].esc)
			;
		else if (newline[i].c == '$')
			mark_env_var(newline, i, data);
		i++;
	}
}

void	expand_arguments(t_char *dst, t_char *src, t_data *data)
{
	int			di;
	int			si;
	const char	*temp;

	di = 0;
	si = 0;
	while (src[si].c != 0)
	{
		if (src[si].c == '$' && src[si].esc == 0 && src[si].var)
		{
			temp = find_env(src + si, data);
			di = copy_env_to_tchar(dst, di, temp);
		}
		if (src[si].var == 0)
		{
			dst[di].ghost = src[si].ghost;
			dst[di].c = src[si].c;
			dst[di].esc = src[si].esc;
			dst[di].var = src[si].var;
			dst[di].com = src[si].com;
			dst[di].added = src[si].added;
			di++;
		}
		si++;
	}
	dst[di].c = 0;
}



t_char	*lexify(char *line, t_data *data)
{
	t_char			*newline;
	static t_char	expanded[1000];


	
	//dynamic memory is problematic due to possible ghosts 
	newline = ft_xcalloc(ft_strlen(line) * 2 + 1, sizeof(t_char));
	remove_quotes(newline, line);
	debug_print(newline, data);
	printf("\n");
	mark_commands(newline, data);
	debug_print(newline, data);
	printf("\n");
	mark_arguments(newline, data);
	debug_print(newline, data);
printf("\n");
	expand_arguments(expanded, newline, data);
	debug_print(expanded, data);
	printf("\n");
	create_list(data, expanded);
	//iterate_list(&data->tokens, print_node);
	return (newline);
}
