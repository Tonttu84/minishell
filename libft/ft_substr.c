/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:01:10 by jtuomi            #+#    #+#             */
/*   Updated: 2024/11/09 18:12:36 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len1;
	char	*str;

	if (!s)
		return (NULL);
	len1 = ft_strlen(s);
	if (start > len1)
		return (ft_strdup(""));
	if (len1 - start < len)
		len = len1 - start;
	str = ft_calloc(len + 1, sizeof "");
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s[start], len + 1);
	return (str);
}
