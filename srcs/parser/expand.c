/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 16:16:04 by alexfuen          #+#    #+#             */
/*   Updated: 2026/03/14 16:16:06 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

static char	*transpose(char *str, int index, char *buffer)
{
	int		i;
	char	*tmp;

	i = 0;
	i++;
	while (ft_isalnum(str[index + i]) || str[index + i] == '_')
		i++;
	tmp = ft_strjoin(buffer, &str[index + i]);
	if (!tmp)
		return (NULL);
	str[index] = '\0';
	str = ft_strjoin(str, tmp);
	free(tmp);
	return (str);
}

static void	var_search(char *buffer, char **envp)
{
	int	flag;
	int	i;
	int	j;

	flag = 0;
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], buffer, ft_strlen(buffer))
			&& envp[i][ft_strlen(buffer)] == '=')
		{
			flag = 1;
			j = 0;
			while (envp[i][j] != '=')
				j++;
			j++;
			ft_strlcpy(buffer, &envp[i][j], ft_strlen(envp[i]) - j + 1);
			break ;
		}
		i++;
	}
	if (!flag)
		buffer[0] = '\0';
}

static char	*convert_var(char *str, int index, char **envp)
{
	int		i;
	char	*buffer;

	buffer = malloc(5000);
	if (!buffer)
		return (NULL);
	if (str[index] != '$')
		return (NULL);
	i = index;
	i++;
	while ((ft_isalnum(str[i]) || str[i] == '_')
		&& str[i] != 39 && str[i] != 34)
	{
		buffer[i - index - 1] = str[i];
		i++;
	}
	buffer[i - index - 1] = '\0';
	var_search(buffer, envp);
	str = transpose(str, index, buffer);
	free(buffer);
	return (str);
}

char	*change_var(char *str, char **envp)
{
	int		i;
	char	*tmp;

	i = 0;
	while (!(str[i] == '$' && is_valid_var(&str[i]) && is_ok_quote(str, i)))
		i++;
	tmp = convert_var(str, i, envp);
	return (tmp);
}
