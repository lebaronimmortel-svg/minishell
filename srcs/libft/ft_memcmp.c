/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:57:29 by lukrodri          #+#    #+#             */
/*   Updated: 2025/10/14 15:57:30 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*fi;
	unsigned char	*sec;

	fi = (unsigned char *)s1;
	sec = (unsigned char *)s2;
	i = 0;
	if (n < 1)
		return (0);
	while (i < n)
	{
		if (fi[i] != sec[i])
		{
			return (fi[i] - sec[i]);
		}
		i++;
	}
	if (i == n && n > 0)
	{
		return (fi[i - 1] - sec[i - 1]);
	}
	return (fi[i] - sec[i]);
}
