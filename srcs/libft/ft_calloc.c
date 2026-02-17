/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:38:32 by lukrodri          #+#    #+#             */
/*   Updated: 2025/10/14 16:38:33 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*memory;
	size_t	i;

	if (!nmemb || !size)
	{
		memory = malloc(0);
		return (memory);
	}
	memory = malloc(nmemb * size);
	if (!memory)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		((unsigned char *)memory)[i] = '\0';
		i++;
	}
	return (memory);
}
