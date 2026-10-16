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

int	does_var_exist(char *str, char **env, int *i)
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

int	append_env_var(char **split, t_data *data, int *status)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_strjoin("export ", split[0]);
	if (!tmp)
		return (1);
	tmp2 = ft_strjoin("=", &split[1][1]);
	if (!tmp2)
	{
		free(tmp);
		return (1);
	}
	tmp3 = ft_strjoin(tmp, tmp2);
	if (!tmp3)
	{
		free(tmp);
		free(tmp2);
		return (1);
	}
	*status = ft_export(tmp3, data);
	free(tmp);
	free(tmp2);
	free(tmp3);
	return (0);
}

int	create_env_var(char **split, t_data *data, int *status)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin("export ", split[0]);
	if (!tmp)
		return (1);
	tmp2 = ft_strjoin(tmp, "=");
	if (!tmp2)
	{
		free(tmp);
		return (1);
	}
	*status = ft_export(tmp2, data);
	free(tmp);
	free(tmp2);
	return (0);
}
