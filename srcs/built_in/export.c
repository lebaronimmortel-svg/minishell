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

int	add_var(char *src, t_data *data)
{
	int	len;

	if (!is_valid_var(src, 1))
		return (1);
	if (ft_strchr(src, '='))
	{
		len = my_memlen(data->env);
		data->env = my_realloc(data->env, len);
		if (!data->env)
			return (1);
		data->env[len] = ft_strdup(src);
	}
	else
	{
		len = my_memlen(data->env_bis);
		data->env_bis = my_realloc(data->env_bis, len);
		if (!data->env_bis)
			return (1);
		data->env_bis[len] = ft_strdup(src);
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
		return ;
	i = 1;
	while (split[i])
		add_var(split[i++], data);
	free_split(split, 0);
	return ;
}
