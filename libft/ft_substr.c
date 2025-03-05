/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:01:10 by jtuomi            #+#    #+#             */
/*   Updated: 2025/03/05 14:19:11 by jrimpila         ###   ########.fr       */
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
	str = ft_xcalloc(len + 1, sizeof "");
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s[start], len + 1);
	return (str);
}
