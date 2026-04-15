/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 02:39:57 by alexfuen          #+#    #+#             */
/*   Updated: 2026/04/09 02:39:59 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

int	exists(char *str, char **env, int *i)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	while (env[*i])
	{
		if (!ft_strncmp(str, env[*i], len) && env[*i][len] == '=')
			return (1);
		if (!ft_strncmp(str, env[*i], len) && !env[*i][len])
			return (1);
		(*i)++;
	}
	return (0);
}

static void	sort_split(char **split)
{
	int		i;
	char	*tmp;

	if (!split || !(*split))
		return ;
	i = 1;
	while (split[i])
	{
		if (ft_strncmp(split[i - 1], split[i], ft_strlen(split[i] + 1)) > 0)
		{
			tmp = split[i];
			split[i] = split[i - 1];
			split[i - 1] = tmp;
			i = 1;
		}
		else
			i++;
	}
}

void	export_single(t_data *data)
{
	sort_split(data->env_bis);
	print_split(data->env_bis);
}

void	ft_export(char *input, t_data *data)
{
	char	**split;
	int		len;
	int		i;

	split = ft_split(input, ' ');
	len = my_memlen(split);
	if (len < 2)
	{
		free_split(split, 0);
		return ;
	}
	i = 1;
	while (split[i])
		add_var(split[i++], data);
	free_split(split, 0);
	return ;
}
