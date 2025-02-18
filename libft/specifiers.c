/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifiers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:52:41 by jtuomi            #+#    #+#             */
/*   Updated: 2024/12/08 19:09:46 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	handle_ptr(va_list ap)
{
	char		*str;
	uintptr_t	i;
	int			len;
	int			wrote;
	char		*ptr;

	wrote = 0;
	ptr = (va_arg(ap, void *));
	if (!ptr)
	{
		wrote += writer("(nil)", 5, 0);
		return (wrote);
	}
	wrote = writer("0x", 2, 0);
	if (wrote != 2)
		return (-1);
	i = (uintptr_t)ptr;
	str = ft_ltostr(i, 16);
	if (!str)
		return (-1);
	len = ft_strlen(str);
	wrote += writer(str, len, 0);
	free(str);
	str = NULL;
	return (wrote);
}

int	handle_dec(va_list ap)
{
	char	*str;
	int		len;

	str = ft_ltostr(va_arg(ap, int), 10);
	if (str)
		len = ft_strlen(str);
	else
		return (-1);
	len = writer(str, len, 0);
	free(str);
	str = NULL;
	return (len);
}

int	handle_udec(va_list ap)
{
	char			*str;
	int				len;
	unsigned int	i;

	i = va_arg(ap, unsigned int);
	str = ft_ltostr(i, 10);
	len = ft_strlen(str);
	i = writer(str, len, 0);
	free(str);
	str = NULL;
	return (i);
}

int	handle_hex_lf(va_list ap)
{
	char			*str;
	unsigned int	ui;
	int				len;

	ui = va_arg(ap, unsigned int);
	str = ft_ltostr(ui, 16);
	if (!str)
		return (-1);
	len = ft_strlen(str);
	ui = writer(str, len, 0);
	free(str);
	str = NULL;
	return (ui);
}

int	handle_hex_uf(va_list ap)
{
	char			*str;
	unsigned int	ui;
	int				len;

	ui = va_arg(ap, unsigned int);
	str = ft_ltostr(ui, 16);
	if (!str)
		return (-1);
	len = ft_strlen(str);
	ui = 0;
	while (str[ui])
	{
		str[ui] = ft_toupper(str[ui]);
		++ui;
	}
	ui = writer(&str[0], len, 0);
	free(str);
	str = NULL;
	return (ui);
}
