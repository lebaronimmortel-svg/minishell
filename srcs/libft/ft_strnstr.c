/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:18:47 by lukrodri          #+#    #+#             */
/*   Updated: 2025/10/14 16:18:48 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	int			check;
	int			len_to_find;

	len_to_find = 0;
	if (little[0] == 0)
		return ((char *)big);
	while (little[len_to_find])
		len_to_find++;
	i = 0;
	check = 0;
	while (big[i] && i < len)
	{
		if (big[i] == little[check])
			check++;
		else
		{
			i = i - check;
			check = 0;
		}
		if (check == len_to_find)
			return ((char *)&big[i - len_to_find + 1]);
		i++;
	}
	return (NULL);
}
