/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_third_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 08:55:08 by lukrodri          #+#    #+#             */
/*   Updated: 2026/04/16 08:55:09 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

char	*my_get_pid(void)
{
	char	**split;
	char	*result;
	int		fd;
	char	buf[1024];
	int		bytes;

	fd = open("/proc/self/stat", O_RDONLY);
	bytes = read(fd, buf, sizeof(buf));
	close(fd);
	buf[bytes] = '\0';
	split = ft_split(buf, ' ');
	if (!split)
		return (NULL);
	result = ft_strdup(split[0]);
	if (!result)
		return (NULL);
	free_split(split, 0);
	return (result);
}

void	unmask_spaces(char *str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\1' || str[i] == '\x1f')
			str[i] = ' ';
		else if (str[i] == '\3')
			str[i] = '|';
		else if (str[i] == '\4')
			str[i] = '<';
		else if (str[i] == '\5')
			str[i] = '>';
		else if (str[i] == '\6')
		{
			move_one(&str[i]);
			continue ;
		}
		i++;
	}
}

char	**quote_clean(char **split)
{
	int	i;
	int	j;

	i = 0;
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
	return (split);
}

char	*change_var_hd(char *str, char **envp)
{
	int		i;
	char	*tmp;

	i = 0;
	while (!(str[i] == '$' && is_valid_var(&str[i], 0)))
		i++;
	tmp = convert_var(str, i, envp);
	free(str);
	return (tmp);
}

int	is_path(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (0);
	return (1);
}
