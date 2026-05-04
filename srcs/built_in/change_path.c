/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 21:36:56 by alexfuen          #+#    #+#             */
/*   Updated: 2026/05/04 21:36:57 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

int	export_env_env(t_data *data, char *str)
{
	int	len;

	len = my_memlen(data->env);
	data->env = my_realloc(data->env, len);
	if (!data->env)
		return (1);
	data->env[len] = ft_strdup(str);
	if (!data->env[len])
		return (1);
	return (0);
}

int	add_var_equal(t_data *data, char *str, int *i, int *j)
{
	if (does_var_exist(str, data->env_bis, j))
	{
		(replace(str, data->env_bis, *j));
		if (does_var_exist(str, data->env, i))
			(replace(str, data->env, *j));
		else
			if (export_env_env(data, str))
				return (1);
		return (0);
	}
	else
	{
		if (replace_both_env(data, str))
			return (1);
		return (0);
	}
}

int	add_var(char *str, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ft_strchr(str, '+'))
		return (0);
	if (!is_valid_export_var(str))
		return (1);
	if (ft_strchr(str, '='))
	{
		if (add_var_equal(data, str, &i, &j))
			return (1);
		return (0);
	}
	j = 0;
	if (does_var_exist(str, data->env_bis, &j))
		return (0);
	else
		if (replace_export_env(data, str))
			return (1);
	return (0);
}

static	int	update_var(t_data *data, char *prefix, char *path, int i)
{
	free(data->env[i]);
	free(data->env_bis[i]);
	data->env[i] = ft_strjoin(prefix, path);
	data->env_bis[i] = ft_strjoin(prefix, path);
	free(prefix);
	if (!data->env[i] || !data->env_bis[i])
		return (1);
	return (0);
}

int	change_path(int flag, char *path, t_data *data)
{
	int		i;
	char	*prefix;
	char	*tmp;

	prefix = ft_strdup("PWD=\0");
	if (prefix && !flag)
	{
		tmp = prefix;
		prefix = ft_strjoin("OLD\0", tmp);
		free(tmp);
	}
	if (!prefix)
		return (1);
	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], prefix, ft_strlen(prefix)))
			return (update_var(data, prefix, path, i));
		i++;
	}
	free(prefix);
	return (1);
}
