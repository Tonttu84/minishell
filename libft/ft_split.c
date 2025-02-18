/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:41:12 by jtuomi            #+#    #+#             */
/*   Updated: 2024/11/09 18:20:25 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	str_count(char *s, char c);
static char			**free_mem(char **arr);
static void			split(char **arr, char const *s, char c, unsigned int strs);

char	**ft_split(char const *s, char c)
{
	unsigned int	strs;
	char			**arr;

	if (!s)
		return (NULL);
	strs = str_count((char *)s, c);
	arr = ft_calloc(strs + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	split(arr, s, c, strs);
	return (arr);
}

static void	split(char **arr, char const *s, char c, unsigned int strs)
{
	char	*ptr;
	char	*ptr_nxt;
	size_t	i;

	i = 0;
	ptr = (char *)s;
	while (i != strs)
	{
		if (*ptr != c)
		{
			ptr_nxt = ft_strchr(ptr, c);
			arr[i] = ft_substr(s, ptr - s, ptr_nxt - ptr);
			if (!arr[i++])
			{
				free_mem(arr);
				break ;
			}
			ptr = ptr_nxt;
		}
		else
			++ptr;
	}
	return ;
}

static unsigned int	str_count(char *s, char c)
{
	unsigned int	i;
	unsigned int	i1;
	unsigned int	i2;
	size_t			t;

	i = 0;
	i1 = 0;
	i2 = 0;
	t = ft_strlen(s);
	i = 0;
	while (s[i] && i < t)
	{
		while (s[i] == c && i < t)
			i++;
		while (s[i] != c && i < t)
		{
			if (i2 == 0)
				i2++;
			i++;
		}
		while (s[i] == c && i < t)
			i++;
		i1++;
	}
	return (i1 * i2);
}

static char	**free_mem(char **arr)
{
	while (*arr)
		free(*arr++);
	free(arr);
	return (NULL);
}
