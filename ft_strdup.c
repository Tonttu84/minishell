/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:58:09 by jrimpila          #+#    #+#             */
/*   Updated: 2024/11/02 14:30:33 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

static size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count++] != 0)
	{
	}
	return (--count);
}

static char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	counter;

	counter = 0;
	while (n--)
	{
		if (src[counter])
			dest[counter] = src[counter];
		else
			dest[counter] = '\0';
		counter++;
	}
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*copy;

	if (s == NULL)
		return (NULL);
	copy = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	return (ft_strncpy(copy, s, (ft_strlen(s) + 1)));
}
