/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_X.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:00:27 by lukrodri          #+#    #+#             */
/*   Updated: 2025/10/22 14:00:29 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putnbr_base(long long nbr, char *base)
{
	char		now;
	long long	len_base;
	size_t		i;

	i = 0;
	len_base = ft_strlen(base);
	if (nbr >= len_base)
	{
		i += ft_putnbr_base(nbr / len_base, base);
		now = base[nbr % len_base];
		write(1, &now, 1);
	}
	else
	{
		now = base[nbr % len_base];
		write(1, &now, 1);
	}
	return (i + 1);
}

static long long	ft_recursive_power(long long nb, int power)
{
	if (power == 0)
		return (1);
	if (power < 0 || nb == 0)
		return (0);
	return (nb * ft_recursive_power(nb, power - 1));
}

size_t	ft_xx(va_list args)
{
	long long	content;
	size_t		len;

	content = va_arg(args, int);
	if (content < 0)
	{
		content = -content;
		content = ft_recursive_power(2, 32) - content;
	}
	len = ft_putnbr_base(content, "0123456789ABCDEF");
	return (len);
}
