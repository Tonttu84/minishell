/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xcalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:01:06 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/24 14:35:27 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// BASH sets ERRNO ENOMEM
// 1 is the general error code for  malloc fails

void	*ft_xcalloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = ft_calloc(nmemb, size);
	if (!ptr)
		ft_exit(get_data(), "malloc", strerror(errno), EXIT_FAILURE);
	return (ptr);
}
