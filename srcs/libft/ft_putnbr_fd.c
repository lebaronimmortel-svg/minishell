/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:04:36 by lukrodri          #+#    #+#             */
/*   Updated: 2025/10/17 16:04:37 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_for_neg(int nb, int fd)
{
	char	now;

	nb = nb * (-1);
	now = '-';
	write (fd, &now, 1);
	return (nb);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	now;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		n = print_for_neg(n, fd);
	}
	now = '0';
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		now = n % 10 + '0';
		write(fd, &now, 1);
	}
	else
	{
		now = n + '0';
		write(fd, &now, 1);
	}
}
