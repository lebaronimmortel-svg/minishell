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

int	export_plus(char **split, t_data *data)
{
	int		i;
	int		j;
	int		flag;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
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
			tmp = data->env_bis[i];
			if (ft_strchr(data->env_bis[i], '='))
			{
				data->env_bis[i] = ft_strjoin(data->env_bis[i], &split[1][1]);
				if (!data->env_bis[i])
					return (1);
				j = 0;
				while (data->env[j])
				{
					if (!ft_strncmp(split[0], data->env[j],
							ft_strlen(split[0])))
					{		
						data->env[j] = ft_strjoin(data->env[j], &split[1][1]);
						if (!data->env[j])
							return (1);
					}
					j++;
				}
			}
			else
			{
				if (my_memlen(split) >= 2)
				{
					tmp = ft_strjoin("export ", split[0]);
					if (!tmp)
						return (1);
					tmp2 = ft_strjoin("=", &split[1][1]);
					if (!tmp2)
						return (1);
					tmp3 = ft_strjoin(tmp, tmp2);
					if (!tmp3)
						return (1);
					status = ft_export(tmp3, data, 0, 0);
					free(tmp);
					free(tmp2);
					free(tmp3);
				}
				else if (*split[0] == '=')
					return (status);
				else
				{
					tmp = ft_strjoin("export ", split[0]);
					if (!tmp)
						return (1);
					tmp2 = ft_strjoin(tmp, "=");
					if (!tmp2)
						return (1);
					status = ft_export(tmp2, data, 0, 0);
					free(tmp);
					free(tmp2);
				}
			}
			flag = 1;
			break ;
		}
		i++;
	}
	if (!flag)
	{
		if (my_memlen(split) >= 2)
		{
			tmp = ft_strjoin("export ", split[0]);
			if (!tmp)
				return (1);
			tmp2 = ft_strjoin("=", &split[1][1]);
			if (!tmp2)
				return (1);
			tmp3 = ft_strjoin(tmp, tmp2);
			if (!tmp3)
				return (1);
			status = ft_export(tmp3, data, 0, 0);
			free(tmp);
			free(tmp2);
			free(tmp3);
		}
		else if (*split[0] == '=')
			return (0);
		else
		{
			tmp = ft_strjoin("export ", split[0]);
			if (!tmp)
				return (1);
			tmp2 = ft_strjoin(tmp, "=");
			if (!tmp2)
				return (1);
			status = ft_export(tmp2, data, 0, 0);
			free(tmp);
			free(tmp2);
		}
	}
	return (status);
}

int	ft_export(char *input, t_data *data, int j, int i)
{
	char	**split;
	char	**split_plus;
	int		len;
	char	*chr;
	int		status;

	split = ft_split(input, ' ');
	if (!split)
		return (1);
	while (split && split[i])
	{
		j = 0;
		while (split[i][j])
		{
			if (split[i][j] == '\1')
				split[i][j] = ' ';
			j++;
		}
		i++;
	}
	i = 0;
	while (split && split[i])
	{
		chr = ft_strchr(split[i], '+');
		if (chr && chr[1] && chr[1] == '=')
		{
			split_plus = ft_split(split[i], '+');
			if (!split_plus)
			{
				free_split(split, 0);
				return (1);
			}
			chr = 0;
			status = export_plus(split_plus, data);
			free_split(split, 0);
			free_split(split_plus, 0);
			free(chr);
			return (status);
		}
		i++;
	}
	len = my_memlen(split);
	if (len < 2)
	{
		free_split(split, 0);
		return (1);
	}
	i = 1;
	while (split[i])
	{
		if (add_var(split[i++], data))
			return (1);
	}
	free_split(split, 0);
	return (0);
}
