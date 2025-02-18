/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:42:12 by jtuomi            #+#    #+#             */
/*   Updated: 2024/11/06 12:38:12 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	all_isspace(char *nptr);

int	ft_atoi(const char *nptr)
{
	int	ret;
	int	sign;
	int	i;

	sign = 1;
	ret = 0;
	i = all_isspace((char *)nptr);
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (ft_isdigit(nptr[i]))
	{
		ret *= 10;
		ret += nptr[i] - '0';
		i++;
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
