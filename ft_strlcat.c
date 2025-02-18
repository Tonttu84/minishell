/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:57:58 by jrimpila          #+#    #+#             */
/*   Updated: 2024/11/02 14:30:51 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count++] != 0)
	{
	}
	return (--count);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int	rval;

	rval = ft_strlen(dst) + ft_strlen(src);
	if (size <= ft_strlen(dst))
	{
		return (size + ft_strlen(src));
	}
	while ((size - 1) && *dst)
	{
		dst++;
		size--;
	}
	while (*src && (size - 1))
	{
		*dst = *src;
		size--;
		dst++;
		src++;
	}
	*dst = '\0';
	return (rval);
}
