/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:13:12 by jtuomi            #+#    #+#             */
/*   Updated: 2025/03/05 14:19:40 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	i1;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	i1 = 0;
	str = ft_xcalloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof "");
	if (!str)
		return (NULL);
	while (s1[i1])
		str[i++] = s1[i1++];
	i1 = 0;
	while (s2[i1])
		str[i++] = s2[i1++];
	str[i] = '\0';
	return (str);
}
