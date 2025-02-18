/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:15:15 by jtuomi            #+#    #+#             */
/*   Updated: 2024/11/09 17:56:24 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	substr_match(char *str, char *sub, size_t i);

char	*ft_strnstr(char *big, char *little, size_t len)
{
	size_t	i;
	size_t	len_little;

	i = 0;
	if (!*little)
		return (big);
	len_little = ft_strlen(little);
	while (len > 0 && big[i] && len >= len_little)
	{
		if (big[i] == little[0])
			if (substr_match(big, little, i))
				return (&big[i]);
		i++;
		len--;
	}
	return (NULL);
}

static int	substr_match(char *str, char *sub, size_t i)
{
	size_t	i1;

	i1 = 0;
	while (sub[i1])
		if (sub[i1++] != str[i++])
			return (0);
	return (1);
}
