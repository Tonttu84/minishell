/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:48:12 by jtuomi            #+#    #+#             */
/*   Updated: 2025/02/27 10:54:50 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//The change in calloc explodes something.
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
