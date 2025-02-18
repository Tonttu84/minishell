/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:56:52 by jrimpila          #+#    #+#             */
/*   Updated: 2024/11/03 11:47:54 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

static int	ft_check_overflow(long long overflow, int positive, int last)
{
	if (overflow < LLONG_MIN / 10 || (last == 9 && overflow == LLONG_MIN / 10))
	{
		if (positive == 1)
			return (-1);
		else
			return (0);
	}
	return (2);
}

int	ft_atoi(const char *nptr)
{
	int			positive;
	long long	rval;

	rval = 0;
	positive = 1;
	while ((*nptr > 8 && *nptr < 14) || (*nptr == 32))
		nptr++;
	if (*nptr == '-')
	{
		positive = 0;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (ft_check_overflow(rval, positive, *nptr) != 2)
			return (ft_check_overflow(rval, positive, *nptr));
		rval = rval * 10 - (*nptr - '0');
		nptr++;
	}
	if (positive == 1)
		return (rval * -1);
	else
		return (rval);
}
