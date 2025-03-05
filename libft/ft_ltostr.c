/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltostr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:39:24 by jtuomi            #+#    #+#             */
/*   Updated: 2025/03/05 14:19:36 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(long nbr, unsigned int base)
{
	int	len;

	len = 0;
	if (nbr < 0)
	{
		len++;
		nbr = -nbr;
	}
	if (nbr == 0)
		len++;
	while (nbr != 0)
	{
		nbr /= base;
		len++;
	}
	return (len);
}

char	*ft_ltostr(long n, unsigned int base)
{
	char	*number;
	long	nbr;
	int		len;

	nbr = n;
	len = get_len(nbr, base);
	number = ft_xcalloc(len + 1, sizeof "");
	if (!number)
		return (NULL);
	if (nbr == 0)
		number[0] = '0';
	if (nbr < 0)
	{
		nbr = ft_abs(nbr);
		number[0] = '-';
		number[len--] = '\0';
	}
	else
		number[len--] = '\0';
	while (nbr != 0)
	{
		number[len--] = BASE32[nbr % base];
		nbr /= base;
	}
	return (number);
}
