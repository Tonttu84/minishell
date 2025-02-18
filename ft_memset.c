/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:59:34 by jrimpila          #+#    #+#             */
/*   Updated: 2024/11/02 14:30:01 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	int				counter;

	ptr = (unsigned char *)s;
	counter = 0;
	while (n--)
	{
		ptr[counter] = (unsigned char)c;
		counter++;
	}
	return (s);
}
