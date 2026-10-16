/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:59:35 by lukrodri          #+#    #+#             */
/*   Updated: 2025/10/16 17:59:37 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**memory(int nb_word)
{
	char	**array;

	array = malloc((1 + nb_word) * sizeof(char *));
	if (!array)
		return (NULL);
	array[nb_word] = NULL;
	return (array);
}

static void	ft_free(char **array, int max)
{
	while (max >= 0)
	{
		free(array[max]);
		max--;
	}
	free(array);
}

static char	**memory_sub(char const *s, char **array, char c, int sub)
{
	int		i;
	int		word;

	i = 0;
	word = 0;
	while (s && s[i])
	{
		sub = 0;
		while (s[i + sub] && s[i + sub] != c)
			sub++;
		if (sub > 0)
		{
			array[word] = ft_calloc(1 + sub, sizeof(char));
			if (!array[word])
			{
				ft_free(array, word);
				return (NULL);
			}
			word++;
			i += sub;
		}
		else
			i++;
	}
	return (array);
}

static char	**memory_final(char const *s, char c)
{
	char	**array;
	int		i;
	int		nb_word;

	i = 1;
	nb_word = 0;
	if (s && ft_strlen(s) == 0)
	{
		array = memory(nb_word);
		return (array);
	}
	if (s && s[0] != c)
		nb_word = 1;
	while (s && s[i])
	{
		if (s[i] != c && s[i - 1] == c)
			nb_word++;
		i++;
	}
	array = memory(nb_word);
	if (!array)
		return (NULL);
	array = memory_sub(s, array, c, 0);
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		j;
	int		sub;

	array = memory_final(s, c);
	if (!array)
		return (NULL);
	j = 0;
	sub = 0;
	while (s && *s)
	{
		if (*s != c)
		{
			array[sub][j] = *s;
			j++;
		}
		else if (array[sub] && ft_strlen(array[sub]) && *s == c)
		{
			array[sub][j] = '\0';
			sub++;
			j = 0;
		}
		s++;
	}
	return (array);
}
