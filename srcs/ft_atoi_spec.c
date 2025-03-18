/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_spec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:42:12 by jtuomi            #+#    #+#             */
/*   Updated: 2025/03/18 12:20:51 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	all_isspace(char *nptr);

int	overflow_check(long ret, int sign, int addition)
{
	if (ret == 922337203685477580 && addition > 7)
	{
		perror("Overflow happens");
		return (2);
	}
	if (ret >= 922337203685477581)
	{
		perror("Overflow happens");
		return (2);
	}
	if (ret == 922337203685477580 && addition > 8 && sign == -1)
	{
		perror("Overflow happens");
		return (2);
	}
	return (0);
}

// Meant to handle the inbuilt exit the same way as bash. 
// int sign should be passed as 1
int	ft_atoi_spec(const char *nptr, int sign)
{
	long	ret;
	int		i;

	ret = 0;
	i = all_isspace((char *)nptr);
	if (nptr[i++] == '-')
	{
		sign = -1;
	}
	else if (nptr[i] == '+')
		i++;
	while (ft_isdigit(nptr[i]))
	{
		if (overflow_check(ret, sign, (nptr[i] - '0')))
			return (2);
		ret *= 10;
		ret += nptr[i] - '0';
		i++;
	}
	if (nptr[i] != 0)
	{
		perror("numeric argument required");
		return (2);
	}
	return (ret * sign);
}

static int	all_isspace(char *nptr)
{
	int	ret;

	ret = 0;
	while (nptr[ret])
	{
		if (nptr[ret] == '\n')
			ret++;
		else if (nptr[ret] == '\t')
			ret++;
		else if (nptr[ret] == '\v')
			ret++;
		else if (nptr[ret] == '\r')
			ret++;
		else if (nptr[ret] == ' ')
			ret++;
		else if (nptr[ret] == '\f')
			ret++;
		else
			break ;
	}
	return (ret);
}
