/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 10:05:00 by lukrodri          #+#    #+#             */
/*   Updated: 2026/04/02 10:05:01 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	print_split(char **split)
{
	int		i;
	char	**word_split;

	if (!split || !(*split))
		return (1);
	i = 0;
	while (split[i])
	{
		if (ft_strchr(split[i], '='))
		{
			word_split = ft_split(split[i], '=');
			if (!word_split)
				return (1);
			if (word_split[1])
				printf("declare -x %s=\"%s\"\n", word_split[0], word_split[1]);
			else
				printf("declare -x %s=\"\"\n", word_split[0]);
			free_split(word_split, 0);
		}
		else
			printf("declare -x %s\n", split[i]);
		i++;
	}
	return (0);
}

char	**split_dup(char **envp)
{
	char	**new_split;
	int		i;
	int		len;

	len = my_memlen(envp);
	if (!len)
		return (NULL);
	new_split = ft_calloc(len + 1, sizeof(char *));
	if (!new_split)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_split[i] = ft_strdup(envp[i]);
		if (!new_split[i])
		{
			free_split(new_split, 0);
			return (NULL);
		}
		i++;
	}
	return (new_split);
}

int	my_memlen(char **split)
{
	int	i;

	if (!split)
		return (0);
	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	is_alphanum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}
