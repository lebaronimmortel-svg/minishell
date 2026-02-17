/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:45:51 by lukrodri          #+#    #+#             */
/*   Updated: 2025/10/17 13:46:09 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*int_min_fill(char *str)
{
	str[0] = '-';
	str[1] = '2';
	str[2] = '1';
	str[3] = '4';
	str[4] = '7';
	str[5] = '4';
	str[6] = '8';
	str[7] = '3';
	str[8] = '6';
	str[9] = '4';
	str[10] = '8';
	str[11] = '\0';
	return (str);
}

static char	*ft_memory(int n)
{
	char	*array;
	int		i;
	int		signe;

	i = 0;
	signe = 0;
	if (n <= 0)
	{
		n = -n;
		signe = 1;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	array = malloc((i + signe) * sizeof(char) + 1);
	if (!array)
		return (NULL);
	return (array);
}

static int	ft_len(int n)
{
	int	i;
	int	cpy;

	i = 0;
	cpy = n;
	if (n <= 0)
	{
		cpy = -cpy;
		i++;
	}
	while (cpy > 0)
	{
		cpy = cpy / 10;
		i++;
	}
	return (i);
}

static void	ft_putnbr(char **array, int nb, int i)
{
	if (nb < 0)
	{
		(*array)[0] = '-';
		nb = -nb;
	}
	if (nb >= 10)
	{
		ft_putnbr(array, nb / 10, i - 1);
		(*array)[i] = nb % 10 + '0';
	}
	else
		(*array)[i] = nb + '0';
}

char	*ft_itoa(int n)
{
	char	*array;

	if (n == -2147483648)
	{
		array = malloc(12 * sizeof(char));
		if (!array)
		{
			array = NULL;
			return (array);
		}
		array = int_min_fill(array);
		return (array);
	}
	array = ft_memory(n);
	if (!array)
		return (NULL);
	ft_putnbr(&array, n, ft_len(n) - 1);
	array[ft_len(n)] = '\0';
	return (array);
}
