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

int	fonction_un_milliard(char **split, t_data *data, int *status)
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

int	fonction_deux_milliards(char **split, t_data *data, int *status)
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

int	fonction_alpha(char **split, t_data *data, int *status)
{
	if (my_memlen(split) >= 2)
	{
		if (fonction_un_milliard(split, data, status))
			return (1);
	}
	else if (*split[0] == '=')
		return (1);
	else
		if (fonction_deux_milliards(split, data, status))
			return (1);
	return (0);
}

int	fonction_beta(char **split, t_data *data, char *tmp, int i)
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

int	fonction_omega(char **split, t_data *data, int *status, int i)
{
	char	*tmp;

	tmp = data->env_bis[i];
	if (ft_strchr(data->env_bis[i], '='))
	{
		if (fonction_beta(split, data, tmp, i))
			return (1);
	}
	else
		if (fonction_alpha(split, data, status))
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
			if (fonction_omega(split, data, &status, i))
				return (1);
			flag = 1;
			break ;
		}
		i++;
	}
	if (!flag)
		if (fonction_alpha(split, data, &status))
			return (1);
	return (status);
}

void	fonction3000000(char **split, int i)
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

int	fonction_samere(char **split, t_data *data)
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

int	fonction3000001(char **split, char *chr, t_data *data, int i)
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

int	ft_export(char *input, t_data *data)
{
	char	**split;
	char	*chr;
	int		i;

	split = ft_split(input, ' ');
	if (!split)
		return (1);
	fonction3000000(split, 0);
	i = 0;
	while (split && split[i])    /// il faut traiter les args 1 par 1, += ou non ...
	{
		chr = ft_strchr(split[i], '+');
		if (chr && chr[1] && chr[1] == '=')
		{
			if (fonction3000001(split, chr, data, i))
			{
				free_split(split, 0);
				return (1);
			}
		}
		i++;
	}
	if (fonction_samere(split, data))
	{
		free_split(split, 0);
		return (1);
	}
	free_split(split, 0);
	return (0);
}
