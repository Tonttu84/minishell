/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:01:37 by jrimpila          #+#    #+#             */
/*   Updated: 2024/11/02 14:31:18 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*retstr;
	int		i;

	retstr = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (retstr == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		retstr[i] = f(i, s[i]);
		i++;
	}
	retstr[i] = '\0';
	return (retstr);
}
