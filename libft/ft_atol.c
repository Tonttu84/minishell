/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:40:32 by jtuomi            #+#    #+#             */
/*   Updated: 2025/03/18 11:43:23 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(char *nptr)
{
	long	ret;
	int		sign;
	long	i;

	sign = 1;
	ret = 0;
	i = 0;
	while (ft_isspace(nptr[i]))
}

