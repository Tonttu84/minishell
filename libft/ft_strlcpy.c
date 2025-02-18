/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:28:43 by jtuomi            #+#    #+#             */
/*   Updated: 2024/11/05 15:38:14 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	s;

	s = 0;
	if (size <= 0)
	{
		return (ft_strlen(src));
	}
	while (s < size - 1 && src[s])
	{
		dst[s] = src[s];
		s++;
	}
	dst[s] = '\0';
	return (ft_strlen(src));
}
