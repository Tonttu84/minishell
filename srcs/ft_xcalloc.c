/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xcalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:01:06 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/18 20:17:50 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//BASH sets ERRNO ENOMEM
//1 is the general error code for  malloc fails

void	*ft_xcalloc(size_t nmemb, size_t size, t_data *data)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	if (nmemb > SIZE_MAX / size)
		ft_exit(data, "ERROR MESSAGE", 1);
	ptr = (void *)malloc(nmemb * size);
	if (ptr == NULL)
		ft_exit(data, "ERROR MESSAGE", 1);
	ft_memset(ptr, 0, (nmemb * size));
	return (ptr);
}
