/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:10:57 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/15 16:42:12 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>

static size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	if (s == NULL)
		return (-1);
	while (s[count++] != 0)
	{
	}
	return (--count);
}

static char	*ft_strcpy(char *destination, const char *source)
{
	int	counter;

	if (destination == NULL || source == NULL)
		return NULL;
	counter = 0;
	while (source[counter] != '\0')
	{
		destination[counter] = source[counter];
		counter++;
	}
	destination[counter] = '\0';
	return (destination);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		s1len;
	int		s2len;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	new = (char *)malloc((s1len + s2len + 1) * (sizeof(char)));
	if (new == NULL)
		return (NULL);
	ft_strcpy(new, s1);
	ft_strcpy(new + s1len, s2);
	return (new);
}
