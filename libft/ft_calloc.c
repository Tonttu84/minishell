/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:48:12 by jtuomi            #+#    #+#             */
/*   Updated: 2024/11/08 14:19:53 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	bytes;

	if (!size || !nmemb)
		return (malloc(0));
	if (SIZE_MAX / size > nmemb)
	{
		bytes = size * nmemb;
		ptr = malloc(bytes);
		if (!ptr)
			return (NULL);
		ft_bzero(ptr, bytes);
		return (ptr);
	}
	return (NULL);
}
