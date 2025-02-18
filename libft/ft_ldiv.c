/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldiv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:22:43 by jtuomi            #+#    #+#             */
/*   Updated: 2024/12/04 16:30:34 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ldiv	ft_ldiv(long nbr, unsigned int base)
{
	t_ldiv	result;

	result.quot = nbr / base;
	result.rem = nbr % base;
	return (result);
}
