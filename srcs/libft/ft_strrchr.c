/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:04:51 by lukrodri          #+#    #+#             */
/*   Updated: 2025/10/14 15:04:52 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	index;

	index = -1;
	if (s[0] == (char)c)
		index = 0;
	i = 1;
	while (s[i - 1])
	{
		if (s[i] == (char)c)
			index = i;
		i++;
	}
	if (index == -1)
		return (NULL);
	return ((char *)&s[index]);
}
