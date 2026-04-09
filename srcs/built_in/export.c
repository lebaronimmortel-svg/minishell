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
		new_split[i] = split[i];
		i++;
	}
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

void	export_single(t_data *data)
{
	print_split(data->env);
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
	return ;
}
