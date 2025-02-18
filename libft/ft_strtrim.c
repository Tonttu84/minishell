/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:05:20 by jtuomi            #+#    #+#             */
/*   Updated: 2024/11/09 17:39:14 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		char_in_set(char s, char *set);
static size_t	trim_amount(char *str, char *set, size_t len, size_t start);

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*str;
	size_t	trim_start;

	if (!s1 || !set)
		return (NULL);
	else if (*s1 == '\0' || *set == '\0')
		return (ft_strdup(s1));
	str = NULL;
	len = ft_strlen(s1);
	trim_start = trim_amount((char *)s1, (char *)set, len, 1);
	if (len == trim_start)
		return (ft_strdup(""));
	len = trim_amount((char *)s1, (char *)set, len, 0) - trim_start;
	str = ft_substr(s1, trim_start, len);
	return (str);
}

static size_t	trim_amount(char *str, char *set, size_t len, size_t start)
{
	size_t	c;

	c = 0;
	if (start)
		while (char_in_set(str[c], set))
			c++;
	else
	{
		c = len;
		while (char_in_set(str[c - 1], set))
			c--;
	}
	return (c);
}

static int	char_in_set(char s, char *set)
{
	unsigned int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}
