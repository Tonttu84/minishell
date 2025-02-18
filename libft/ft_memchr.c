/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:16:34 by jtuomi            #+#    #+#             */
/*   Updated: 2024/11/09 17:34:41 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	ch;
	size_t			i;

	ch = (unsigned char)c;
	i = 0;
	ptr = (unsigned char *)s;
	while (n-- > 0)
	{
		if (ptr[i] == ch)
			return (&ptr[i]);
		i++;
	}
	return (NULL);
}
