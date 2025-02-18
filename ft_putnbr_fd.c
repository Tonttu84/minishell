/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrimpila <jrimpila@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:05:19 by jrimpila          #+#    #+#             */
/*   Updated: 2024/11/02 14:30:11 by jrimpila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	print(int nb, int digits, int fd)
{
	int		divider;
	char	print;
	int		first;

	divider = 1;
	while (--digits > 0)
		divider = divider * 10;
	while (divider > 0)
	{
		print = nb / divider + '0';
		write(fd, &print, 1);
		first = nb / divider;
		nb = nb - (first * divider);
		divider = divider / 10;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int	nb;
	int	digits;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = n * -1;
	}
	nb = n;
	digits = 1;
	while (n > 9)
	{
		n = n / 10;
		digits++;
	}
	print(nb, digits, fd);
}
