/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
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

void	print_split(char **split)
{
	int	i;

	if (!split || !(*split))
		return ;
	i = 0;
	while (split[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(split[i], 1);
		write(1, "\n", 1);
		i++;
	}
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
