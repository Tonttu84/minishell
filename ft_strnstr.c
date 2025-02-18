/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:57:24 by jrimpila          #+#    #+#             */
/*   Updated: 2024/11/04 20:49:08 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	counter;

	counter = 0;
	while (len > counter)
	{
		if (little[counter] == 0)
			return ((char *)big);
		if (big[counter] == 0)
			return (NULL);
		if (big[counter] != little[counter])
		{
			big++;
			len--;
			counter = 0;
			continue ;
		}
		counter++;
	}
	if (little[counter] == 0)
		return ((char *)big);
	return (NULL);
}
