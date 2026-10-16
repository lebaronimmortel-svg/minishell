/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:00:42 by lukrodri          #+#    #+#             */
/*   Updated: 2025/10/22 14:00:43 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putnbr_base(unsigned long nbr, char *base)
{
	char				now;
	unsigned long		len_base;
	size_t				i;

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

size_t	ft_p(va_list args)
{
	unsigned long	content;
	size_t			len;

	content = (unsigned long)va_arg(args, void *);
	if (!content)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	len = ft_putnbr_base(content, "0123456789abcdef");
	return (len + 2);
}
