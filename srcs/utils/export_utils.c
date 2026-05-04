/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 18:25:30 by alexfuen          #+#    #+#             */
/*   Updated: 2026/04/11 18:25:31 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

static char	**my_realloc(char **split, int old_size)
{
	char	**new_split;
	int		i;

	if (!split)
		return (NULL);
	new_split = calloc(old_size + 2, sizeof(char *));
	if (!new_split)
		return (NULL);
	i = 0;
	while (i < old_size)
	{
		new_split[i] = ft_strdup(split[i]);
		if (!new_split[i])
		{
			free_split(new_split, 0);
			return (NULL);
		}
		i++;
	}
	free_split(split, 0);
	return (new_split);
}

static int	replace(char *str, char **env, int i)
{
	free(env[i]);
	env[i] = ft_strdup(str);
	if (!env[i])
		return (0);
	return (1);
}

int	is_valid_export_var(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]))
		return (0);
	while (str[i] && str[i] != ' ' && str[i] != '=')
	{
		if (!ft_isalpha(str[i]) && str[i] != '_'
			&& (str[i] < '0' || str[i] > '9'))
			return (0);
		i++;
	}
	if (!i)
		return (0);
	return (1);
}

int	fonction(t_data *data, char *str)
{
	int	len;

	len = my_memlen(data->env);
	data->env = my_realloc(data->env, len);
	if (!data->env)
		return (1);
	data->env[len] = ft_strdup(str);
	if (!data->env[len])
		return (1);
	len = my_memlen(data->env_bis);
	data->env_bis = my_realloc(data->env_bis, len);
	if (!data->env_bis)
		return (1);
	data->env_bis[len] = ft_strdup(str);
	if (!data->env_bis[len])
		return (1);
	return (0);
}

int	fonction1(t_data *data, char *str)
{
	int	len;

	len = my_memlen(data->env_bis);
	data->env_bis = my_realloc(data->env_bis, len);
	if (!data->env_bis)
		return (1);
	data->env_bis[len] = ft_strdup(str);
	if (!data->env_bis[len])
		return (1);
	return (0);
}

int	fonction2(t_data *data, char *str)
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

int	fonction4(t_data *data, char *str, int *i, int *j)
{
	if (does_var_exist(str, data->env_bis, j))
	{
		(replace(str, data->env_bis, *j));
		if (does_var_exist(str, data->env, i))
			(replace(str, data->env, *j));
		else
			if (fonction2(data, str))
				return (1);
		return (0);
	}
	else
	{
		if (fonction(data, str))
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
		if (fonction4(data, str, &i, &j))
			return (1);
		return (0);
	}
	j = 0;
	if (does_var_exist(str, data->env_bis, &j))
		return (0);
	else
		if (fonction1(data, str))
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
