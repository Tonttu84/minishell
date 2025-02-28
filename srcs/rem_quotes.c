/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rem_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:27:03 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/28 11:32:18 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	next_is_delim(char *str, int i, t_char *dst, int k)
{
	if (dst[k - 1].added)
		return (0);
	if (i != 0 && dst[k - 1].c != ' ' && dst[k - 1].esc != 0)
	{
		return (0);
	}
	i += 2;
	while (str[i] != 0 && str[i] != ' ')
	{
		if (str[i] == '\'' && str[i] == '\'')
		{
			i += 2;
		}
		else if (str[i] == '\"' && str[i] == '\"')
			i += 2;
		else
			return (0);
	}
	return (1);
}

void	remove_quotes(t_char *dst, char *src)
{
	int	i;
	int	in_s_quotes;
	int	in_d_quotes;
	int	k;
	int	exp;

	i = 0;
	in_s_quotes = 0;
	in_d_quotes = 0;
	k = 0;
	exp = 0;
	while (src && src[i] != 0)
	{
		if (check_emp_arg(src, i, dst, &k, in_d_quotes, in_s_quotes))
			i++;
		/*Heredocs treats the next characters as literals until space,
			except <<< has a specia meaning
		cat << EOF
	This is a $SHELL variable.
	EOF
	cat << "EOF"
This is a $SHELL variable.
EOF
	*/
		else if (!in_s_quotes && !in_d_quotes && src[i] == src[i + 1]
			&& (src[i] == '>' || src[i] == '<'))
		{
			dst[k].c = ' ';
			k++;
			dst[k].c = src[i];
			k++;
			i++;
			dst[k].c = src[i];
			k++;
			dst[k].c = ' ';
			k++;
		}
		else if (!in_s_quotes && !in_d_quotes && src[i + 1] != src[i]
			&& (src[i] == '>' || src[i] == '<'))
		{
			dst[k].c = ' ';
			k++;
			dst[k].c = src[i];
			k++;
			dst[k].c = ' ';
			k++;
		}
		else if (in_s_quotes && src[i] == '\'')
			in_s_quotes = 0;
		else if (in_d_quotes && src[i] == '\"')
		{
			if (exp == 1)
				exp = 0;
			in_d_quotes = 0;
			dst[k+ 1].blok = 1;
		}
		else if (!in_d_quotes && !in_s_quotes && src[i] == '\"')
			in_d_quotes = 1;
		else if (!in_d_quotes && !in_s_quotes && src[i] == '\'')
		{
			in_s_quotes = 1;
			dst[k+ 1].blok = 1;
		}
		else if (in_s_quotes)
		{
			dst[k].c = src[i];
			dst[k].esc = 1;
			k++;
		}
		else if (in_d_quotes)
		{
			dst[k].c = src[i];
			if (src[i] == '$')
				exp = 1;
			else if (exp == 1)
			{
				if (ft_isalnum(src[i]) == 0 && src[i] != '_')
				{
					exp = 0;
					dst[k + 1].blok = 1;
				}
			}
			if (exp == 0 && src[i])
				dst[k].esc = 1;
			k++;
		}
		else
		{
			dst[k].c = src[i];
			k++;
		}
		i++;

	}
	dst[i].c = '\0';
}

// I will later refactor to remove the i and just pass the pointer to (src + i);
int	check_emp_arg(char *src, int i, t_char *dst, int *k, int in_d_quotes,
		int in_s_quotes)
{
	if (!in_d_quotes && !in_s_quotes && src[i] == '\'' && src[i + 1] == '\''
		&& next_is_delim(src, i, dst, *k))
	{
		dst[*k].ghost = 1;
		dst[*k].c = 'G';
		dst[*k + 1].c = ' ';
		dst[*k + 1].added = 1;
		*k += 2;
		return (1);
	}
	else if (!in_d_quotes && !in_s_quotes && src[i] == '\"' && src[i
		+ 1] == '\"' && next_is_delim(src, i, dst, *k))
	{
		dst[*k].ghost = 1;
		dst[*k].c = 'G';
		dst[*k + 1].c = ' ';
		dst[*k + 1].added = 1;
		*k += 2;
		return (1);
	}
	return (0);
}