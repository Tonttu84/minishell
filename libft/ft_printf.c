/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:15:07 by jtuomi            #+#    #+#             */
/*   Updated: 2024/12/08 19:08:56 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	int		i;
	int		tmp;

	i = 0;
	va_start(ap, fmt);
	while (*fmt)
	{
		tmp = i;
		if (*fmt == '%')
		{
			i += handle_specifier(ap, fmt[1]);
			fmt += 2;
		}
		else
			i += write(1, fmt++, 1);
		if (i < tmp)
			return (-1);
	}
	return (i);
	va_end(ap);
	return (i);
}

int	handle_specifier(va_list ap, const char fmt)
{
	char	c;

	c = '%';
	if (fmt == 'c')
	{
		c = (char)va_arg(ap, int);
		return (write(1, &c, 1));
	}
	else if (fmt == 's')
		return (handle_s(ap));
	else if (fmt == 'p')
		return (handle_ptr(ap));
	else if (fmt == 'd')
		return (handle_dec(ap));
	else if (fmt == 'i')
		return (handle_dec(ap));
	else if (fmt == 'u')
		return (handle_udec(ap));
	else if (fmt == 'x')
		return (handle_hex_lf(ap));
	else if (fmt == 'X')
		return (handle_hex_uf(ap));
	else if (fmt == '%')
		return (write(1, &c, 1));
	return (-1);
}

int	handle_s(va_list ap)
{
	char	*str;
	int		len;
	int		written;

	written = 0;
	str = va_arg(ap, char *);
	if (!str)
	{
		written += writer("(null)", 6, 0);
		return (written);
	}
	len = ft_strlen(str);
	while (written < len)
	{
		written += write(1, str, len);
		if (written < 0)
			return (-1);
	}
	return (written);
}

int	writer(char *str, int len, int written)
{
	while (written < len)
	{
		written += write(1, str, len);
		if (written < 0)
			return (-1);
	}
	return (len);
}
