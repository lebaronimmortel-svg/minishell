/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:21:18 by lukrodri          #+#    #+#             */
/*   Updated: 2025/10/15 11:21:19 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in(char const s1, char const *set)
{
	int	j;

	j = 0;
	while (set[j])
	{
		if (set[j] == s1)
			return (1);
		j++;
	}
	return (0);
}

static char	*start(char *s1, char const *set, size_t i)
{
	while (is_in(s1[i], set))
		i++;
	if (i == ft_strlen(s1))
		return ("");
	return (&s1[i]);
}

static int	end(char *s1, char const *set, int j)
{
	while (is_in(s1[j], set))
		j--;
	return (j);
}

static char	*empty(char *s1)
{
	char	*newstr;
	int		i;

	newstr = malloc(ft_strlen(s1) * sizeof(char) + 1);
	if (!newstr)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		newstr[i] = s1[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*newstr;
	char	*str;
	int		j;

	if (!s1 || !set)
	{
		newstr = malloc(0);
		return (newstr);
	}
	str = (char *)s1;
	if (ft_strlen(set) == 0)
	{
		newstr = empty(str);
		return (newstr);
	}
	str = start(str, set, 0);
	j = end(str, set, ft_strlen(str) - 1) + 1;
	newstr = malloc((ft_strlen(str) - (ft_strlen(str) - j)) * sizeof(char) + 1);
	if (!newstr)
		return (NULL);
	if (ft_strlen(str) == 0)
		newstr[0] = '\0';
	else
		ft_strlcpy(newstr, str, j + 1);
	return (newstr);
}
