/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:04:31 by jrimpila          #+#    #+#             */
/*   Updated: 2024/11/03 15:48:12 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_stringify(char *n_string, int neg, int digits, int pos_n)
{
	int	divider;
	int	first_digit;

	divider = 1;
	while (digits-- > 1)
		divider = divider * 10;
	if (neg == 1)
		*n_string++ = '-';
	while (divider > 0)
	{
		first_digit = pos_n / divider;
		*n_string++ = first_digit + '0';
		pos_n = pos_n - first_digit * divider;
		divider = divider / 10;
	}
	*n_string = '\0';
	return (n_string);
}

static char	*stringify_min(void)
{
	char	*newstr;

	newstr = malloc(12 * sizeof(char));
	if (!newstr)
		return (NULL);
	ft_memcpy(newstr, "-2147483648", 12);
	return (newstr);
}

char	*ft_itoa(int n)
{
	char	*newstr;
	int		negative;
	int		digits;
	int		copy;

	if (n == -2147483648)
		return (stringify_min());
	negative = 0;
	digits = 1;
	if (n < 0)
	{
		negative = 1;
		n = n * -1;
	}
	copy = n;
	while (n > 9)
	{
		digits++;
		n = n / 10;
	}
	newstr = (char *)malloc((digits + 1 + negative) * sizeof(char));
	if (newstr == NULL)
		return (NULL);
	ft_stringify(newstr, negative, digits, copy);
	return (newstr);
}
