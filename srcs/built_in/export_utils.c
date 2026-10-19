/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <alexfuen@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 21:30:40 by alexfuen          #+#    #+#             */
/*   Updated: 2026/10/19 21:30:40 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

int	end_of_string(char *input)
{
	if (!has_n_flag(input))
		ft_putstr_fd("\n", 1);
	return (0);
}

int	add_to_var(char **split, t_data *data, int *status, int i)
{
	char	*tmp;

	tmp = data->env_bis[i];
	if (ft_strchr(data->env_bis[i], '='))
	{
		if (add_to_var_equal(split, data, tmp, i))
			return (1);
	}
	else
		if (add_to_var_null(split, data, status))
			return (1);
	return (0);
}

int	export_plus(char **split, t_data *data)
{
	int		flag;
	int		i;
	int		status;

	flag = 0;
	i = 0;
	status = 0;
	while (data->env_bis[i])
	{
		if (!ft_strncmp(split[0], data->env_bis[i], ft_strlen(split[0]))
			&& (data->env_bis[i][ft_strlen(split[0])] == '='
			|| data->env_bis[i][ft_strlen(split[0])] == '\0'))
		{
			if (add_to_var(split, data, &status, i))
				return (1);
			flag = 1;
			break ;
		}
		i++;
	}
	if (!flag)
		if (add_to_var_null(split, data, &status))
			return (1);
	return (status);
}

void	replace_fill(char **split, int i)
{
	int	j;

	while (split && split[i])
	{
		j = 0;
		while (split[i][j])
		{
			if (split[i][j] == '\1' || split[i][j] == '\x1f')
				split[i][j] = ' ';
			else if (split[i][j] == '\3')
				split[i][j] = '|';
			else if (split[i][j] == '\4')
				split[i][j] = '<';
			else if (split[i][j] == '\5')
				split[i][j] = '>';
			else if (split[i][j] == '\6')
			{
				move_one(&split[i][j]);
				continue ;
			}
			j++;
		}
		i++;
	}
}

int	export_basic(char **split, t_data *data)
{
	int	len;
	int	i;

	len = my_memlen(split);
	if (len < 2)
		return (1);
	i = 1;
	while (split[i])
	{
		if (add_var(split[i++], data))
		{
			ft_putstr_fd("Error : invalid identifier\n", 2);
			return (1);
		}
	}
	return (0);
}
