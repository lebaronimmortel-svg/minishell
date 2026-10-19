/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <alexfuen@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 21:30:40 by alexfuen          #+#    #+#             */
/*   Updated: 2026/10/19 21:30:40 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

int	add_to_var_null(char **split, t_data *data, int *status)
{
	if (my_memlen(split) >= 2)
	{
		if (append_env_var(split, data, status))
			return (1);
	}
	else if (*split[0] == '=')
		return (1);
	else
		if (create_env_var(split, data, status))
			return (1);
	return (0);
}

int	add_to_var_equal(char **split, t_data *data, char *tmp, int i)
{
	int	j;

	data->env_bis[i] = ft_strjoin(data->env_bis[i], &split[1][1]);
	free(tmp);
	if (!data->env_bis[i])
		return (1);
	j = 0;
	while (data->env[j])
	{
		if (!ft_strncmp(split[0], data->env[j],
				ft_strlen(split[0])))
		{
			tmp = data->env[j];
			data->env[j] = ft_strjoin(data->env[j], &split[1][1]);
			free(tmp);
			if (!data->env[j])
				return (1);
		}
		j++;
	}
	return (0);
}

int	export_add(char **split, char *chr, t_data *data, int i)
{
	char	**split_plus;
	int		status;

	split_plus = ft_split(split[i], '+');
	if (!split_plus)
		return (1);
	chr = 0;
	status = export_plus(split_plus, data);
	free_split(split_plus, 0);
	free(chr);
	return (status);
}

int	add_to_env_var(char **split, int i, t_data *data)
{
	char	*chr;

	chr = ft_strchr(split[i], '+');
	if (chr && chr[1] && chr[1] == '=')
	{
		if (export_add(split, chr, data, i))
		{
			free_split(split, 0);
			return (1);
		}
	}
	return (0);
}

int	ft_export(char *input, t_data *data)
{
	char	**split;
	int		i;

	split = ft_split(input, ' ');
	if (!split)
		return (1);
	replace_fill(split, 0);
	i = 0;
	while (split && split[i])
	{
		if (add_to_env_var(split, i, data))
			return (1);
		i++;
	}
	if (export_basic(split, data))
	{
		free_split(split, 0);
		return (1);
	}
	free_split(split, 0);
	return (0);
}
