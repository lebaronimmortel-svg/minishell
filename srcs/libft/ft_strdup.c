/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:20:55 by lukrodri          #+#    #+#             */
/*   Updated: 2025/10/14 13:20:56 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	int		i;
	int		taille_source;

	i = 0;
	while (src[i] != '\0')
	{
		i++;
	}
	taille_source = i;
	i = 0;
	while (i < taille_source)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *src)
{
	char	*copy;
	int		len_src;

	len_src = ft_strlen(src) + 1;
	copy = (char *) malloc(len_src * sizeof(char));
	if (!copy)
		return (NULL);
	copy = ft_strcpy(copy, src);
	return (copy);
}
