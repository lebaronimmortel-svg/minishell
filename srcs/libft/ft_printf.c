/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 20:27:59 by lukrodri          #+#    #+#             */
/*   Updated: 2025/10/21 20:28:01 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	function(const char *s, va_list args, int i)
{
	if (s[0] == 'c')
		i = ft_c(args);
	else if (s[0] == 's')
		i = ft_s(args);
	else if (s[0] == '%')
	{
		i = 1;
		write(1, "%", 1);
	}
	else if (s[0] == 'd' || s[0] == 'i')
		i = ft_di(args);
	else if (s[0] == 'p')
		i = ft_p(args);
	else if (s[0] == 'x')
		i = ft_x(args);
	else if (s[0] == 'X')
		i = ft_xx(args);
	else if (s[0] == 'u')
		i = ft_u(args);
	return (i);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	int		result;
	va_list	args;

	if (!s)
		return (-1);
	va_start(args, s);
	result = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			result += function(&s[i + 1], args, 0);
			i++;
		}
		else
		{
			write(1, &s[i], 1);
			result++;
		}
		i++;
	}
	va_end(args);
	return (result);
}
