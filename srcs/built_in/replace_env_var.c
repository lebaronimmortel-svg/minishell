/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 18:25:30 by alexfuen          #+#    #+#             */
/*   Updated: 2026/04/11 18:25:31 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

char	**my_realloc(char **split, int old_size)
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

int	replace(char *str, char **env, int i)
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
	if (!ft_isalpha(str[i]) && str[i] != '_')
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

int	replace_both_env(t_data *data, char *str)
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

int	replace_export_env(t_data *data, char *str)
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
