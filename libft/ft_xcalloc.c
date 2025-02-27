/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xcalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:01:06 by jrimpila          #+#    #+#             */
/*   Updated: 2025/02/27 11:14:37 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//BASH sets ERRNO ENOMEM
//1 is the general error code for  malloc fails

void	*ft_xcalloc(size_t nmemb, size_t size)
{
	void	*ptr;
	t_data	*data;

	data = get_data();
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
