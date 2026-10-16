/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:27:33 by lukrodri          #+#    #+#             */
/*   Updated: 2025/10/22 14:27:34 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_putnbr_base(unsigned int nbr, char *base)
{
	char			now;
	unsigned long	len_base;
	size_t			i;

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

size_t	ft_u(va_list args)
{
	unsigned long	content;
	size_t			len;

	content = va_arg(args, unsigned int);
	len = ft_putnbr_base(content, "0123456789");
	return (len);
}
