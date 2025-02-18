/* ************************************************************************** */
/*                                                                            */
/*                                                     __     h  _ _  _| _    */
/*   ft_atof.c                                      __/  \__  i (_(_)(_|(/_   */
/*                                                 /  \__/  \ v  _ _|_        */
/*   By: marvin <marvin@42.fr>                     \__/  \__/ e _>(_| | --    */
/*                                                 /  \__/  \ .  _  _ |       */
/*   Created: 2025/02/09 13:03:23 by marvin        \__/  \__/ f (_)(_)|       */
/*   Updated: 2025/02/09 15:03:43 by marvin           \__/    i               */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *s)
{
	char	*ptr;
	double	new;
	double	mantissa;

	if (!s)
		return (0.);
	ptr = ft_strchr(s, '.');
	new = ft_atoi(s);
	if (!ptr)
		return (new);
	mantissa = ft_atoi(ptr + 1);
	while (mantissa >= 1)
		mantissa *= 0.1;
	if (new > 0)
		return (new + mantissa);
	return (new - mantissa);
}
