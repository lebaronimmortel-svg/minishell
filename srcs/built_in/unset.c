/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                             :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 19:30:13 by alexfuen          #+#    #+#             */
/*   Updated: 2026/04/09 19:30:16 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

static int	is_var(char *str, char **envp)
{
	int	i;
	int	len;

	if (!envp || !(*envp))
		return (0);
	i = 0;
	while (envp[i])
	{
		len = ft_strlen(str);
		if (!ft_strncmp(str, envp[i], len)
			&& envp[i][len] == '=')
			return (2);
		if (!ft_strncmp(str, envp[i], len) && !envp[i][len])
			return (1);
		i++;
	}
	return (0);
}

static void	free_line(char **envp, char **split, int i)
{
	int		j;

	j = 0;
	while (envp[j] && ft_strncmp(split[i], envp[j], ft_strlen(split[i])))
		j++;
	if (!envp[j])
		return ;
	free(envp[j]);
	while (envp[j + 1])
	{
		envp[j] = envp[j + 1];
		j++;
	}
	envp[j] = envp[j + 1];
}

int	unset(char **split, t_data *data)
{
	int		i;

	i = 0;
	while (split[i])
	{
		if (is_var(split[i], data->env_bis))
		{
			free_line(data->env, split, i);
			free_line(data->env_bis, split, i);
		}
		i++;
	}
	return (0);
}
