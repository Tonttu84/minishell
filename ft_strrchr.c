/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:57:19 by jrimpila          #+#    #+#             */
/*   Updated: 2024/11/03 16:25:52 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	int	counter;
	int	marker;

	counter = 0;
	marker = -1;
	while (s[counter])
	{
		if ((unsigned char)s[counter] == (unsigned char)c)
			marker = counter;
		counter++;
	}
	if ((unsigned char)s[counter] == (unsigned char)c)
		marker = counter;
	if (marker == -1)
		return (NULL);
	else
		return ((char *)&s[marker]);
}
