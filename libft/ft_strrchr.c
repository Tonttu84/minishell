/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:13:37 by jtuomi            #+#    #+#             */
/*   Updated: 2024/11/09 17:47:05 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *s, int c)
{
	unsigned int	i;
	char			*rtrn;

	if (!c)
		return (s + ft_strlen(s));
	rtrn = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			rtrn = &s[i];
		i++;
	}
	return (rtrn);
}
