/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:54:12 by lukrodri          #+#    #+#             */
/*   Updated: 2025/10/14 15:54:14 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	if (n < 1)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && (i < n))
	{
		if (s1[i] != s2[i])
		{
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		}
		i++;
	}
	if (i == n && n > 0)
	{
		return (((unsigned char *)s1)[i - 1] - ((unsigned char *)s2)[i - 1]);
	}
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
