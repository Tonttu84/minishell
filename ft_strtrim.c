/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:01:32 by jrimpila          #+#    #+#             */
/*   Updated: 2024/11/02 14:31:42 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*newstr;
	int		len;
	int		start;
	int		end;

	if (s1 == NULL)
		return (NULL);
	start = 0;
	len = ft_strlen(s1);
	end = ft_strlen(s1);
	if (set != NULL )
	{
		while ((ft_strchr (set, s1[start]) != NULL) && (len > 0))
		{
			len--;
			start++;
		}
		while ((ft_strchr (set, s1[end -1])) && len != 0 && len-- > 0)
			end--;
	}
	newstr = (char *)malloc((len + 1) * sizeof(char));
	if (newstr == NULL)
		return (NULL);
	ft_strlcpy(newstr, (s1 + start), (len + 1));
	return (newstr);
}
