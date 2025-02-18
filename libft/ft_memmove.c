/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:53:29 by jtuomi            #+#    #+#             */
/*   Updated: 2024/11/04 14:41:01 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*tmp_dest;
	char	*tmp_src;

	if (!dest && !src)
		return (NULL);
	tmp_src = (char *)src;
	tmp_dest = (char *)dest;
	if (tmp_dest > tmp_src)
		while (n-- > 0)
			tmp_dest[n] = tmp_src[n];
	else
		while (n-- > 0)
			*tmp_dest++ = *tmp_src++;
	return (dest);
}
