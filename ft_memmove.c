/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:59:41 by jrimpila          #+#    #+#             */
/*   Updated: 2024/11/03 14:59:09 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	int					i;

	i = 0;
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d > s)
	{
		while ((n) > 0)
		{
			n--;
			d[n] = s[n];
		}
	}
	else
	{
		while ((n) > 0)
		{	
			n--;
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}
