/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:21:29 by lukrodri          #+#    #+#             */
/*   Updated: 2025/10/14 16:21:31 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_space(const char *str, int i)
{
	while (str[i] == '\t'
		|| str[i] == '\n'
		|| str[i] == '\v'
		|| str[i] == '\f'
		|| str[i] == '\r'
		|| str[i] == ' ')
		return (1);
	return (0);
}

int	calculation_atoi(const char *str, int i, int sign, int result)
{
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = result * 10 + str[i] - '0';
		else
			return (result * sign);
		i++;
	}
	return (result * sign);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	i;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	while (check_space(nptr, i))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	result = calculation_atoi(nptr, i, sign, result);
	return (result);
}
