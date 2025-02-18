/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 21:34:16 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/09 16:39:39 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

static char	*cut_string(char *source, int len, char **target, int loc)
{
	char	*new;
	int		i;

	if (len == 0)
		return (source);
	i = 0;
	new = malloc((len + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	target[loc] = new;
	while (len > 0)
	{
		new[i] = source[i];
		i++;
		len--;
	}
	new[i] = '\0';
	return (source + i);
}

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	int		in_word;

	in_word = 0;
	count = 0;
	if (s == NULL)
		return (0);
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
		{
			in_word = 0;
		}
		s++;
	}
	return (count);
}

static int	count_string(char *source, char c)
{
	int	count;

	count = 0;
	while (source[count] != '\0')
	{
		if (source[count] == c)
			return (count);
		count++;
	}
	return (count);
}

char	**free_string(char **strstr)
{
	int	i;

	i = 0;
	while (strstr && strstr[i] != NULL)
	{
		free(strstr[i]);
		i++;
	}
	free(strstr);
	strstr = NULL;
	return (strstr);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		res_loc;
	char	*str;

	str = (char *)s;
	res_loc = 0;
	result = malloc((count_words(s, c) + 1) * sizeof (char *));
	if (result == NULL)
		return (NULL);
	while (*str != '\0')
	{
		while (*str == c)
			str++;
		if (count_string(str, c) > 0)
		{
			str = cut_string(str, count_string(str, c), result, res_loc);
			if (str == NULL)
				return (free_string(result));
			res_loc++;
		}
	}
	result[res_loc] = NULL;
	return (result);
}
