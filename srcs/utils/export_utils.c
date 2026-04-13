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
		i++;
	}
	free_split(split, 0);
	return (new_split);
}

static int	replace(char *str, t_data *data, int flag, int *i)
{
	int	j;

	if (!flag)
		return (0);
	if (flag == 1)
	{
		free(data->env[*i]);
		data->env[*i] = ft_strdup(str);
		if (!data->env[*i])
			return (0);
		return (1);
	}
	else
	{
		j = *i;
		free(data->env_bis[j]);
		while (data->env_bis[j + 1])
		{
			data->env_bis[j] = data->env_bis[j + 1];
			j++;
		}
		data->env_bis[j] = data->env_bis[j + 1];
		add_var(str, data);
		return (1);
	}
}

int	add_var(char *str, t_data *data)
{
	int	i;
	int	len;

	i = 0;
	if (!is_valid_var(str, 1))
		return (1);
	if (ft_strchr(str, '='))
	{
		if (replace(str, data, exists(str, data, &i), &i))
			return (0);
		else
		{
			len = my_memlen(data->env);
			data->env = my_realloc(data->env, len);
			if (!data->env)
				return (1);
			data->env[len] = ft_strdup(str);
		}
	}
	len = my_memlen(data->env_bis);
	data->env_bis = my_realloc(data->env_bis, len);
	if (!data->env_bis)
		return (1);
	data->env_bis[len] = ft_strdup(str);
	return (0);
}

static int	update_var(t_data *data, char *prefix, char *path, int i)
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
