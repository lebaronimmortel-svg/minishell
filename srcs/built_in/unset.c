/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_bis.c                                      :+:      :+:    :+:  */
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
			&& envp[i][len] == '='
			&& envp[i][len + 1]
			&& envp[i][len + 1] != ' ')
			return (2);
		if (!ft_strncmp(str, envp[i], len) && !envp[i][len + 1])
			return (1);
		i++;
	}
	return (0);
}

static void	free_line(t_data *data, char **split, int flag, int i)
{
	int		j;
	char	**envp;

	if (flag == 1)
		envp = data->env_bis;
	else if (flag == 2)
		envp = data->env;
	else
		return ;
	j = 0;
	while (ft_strncmp(split[i], envp[j], ft_strlen(split[i])))
		j++;
	while (envp[j + 1])
	{
		envp[j] = envp[j + 1];
		j++;
	}
	envp[j] = envp[j + 1];
}

void	unset(char **split, t_data *data)
{
	int		i;
	int		flag;

	i = 0;
	while (split[i])
	{
		flag = is_var(split[i], data->env);
		if (!flag)
			flag = is_var(split[i], data->env_bis);
		if (flag)
			free_line(data, split, flag, i);
		i++;
	}
}
