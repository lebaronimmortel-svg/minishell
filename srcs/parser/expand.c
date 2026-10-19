/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <alexfuen@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 21:30:40 by alexfuen          #+#    #+#             */
/*   Updated: 2026/10/19 21:30:40 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

char	*transpose_var(char *str, int index, char *buffer, int flag)
{
	int		i;
	char	*tmp;

	i = 0;
	i++;
	if (flag)
	{
		while (ft_isalnum(str[index + i]) || str[index + i] == '_')
			i++;
	}
	else
		i++;
	tmp = ft_strjoin(buffer, &str[index + i]);
	if (!tmp)
		return (NULL);
	str[index] = '\0';
	str = ft_strjoin(str, tmp);
	free(tmp);
	return (str);
}

void	empty_prompt_spaces(char *buffer)
{
	int	j;

	j = 0;
	while (buffer[j])
	{
		if (buffer[j] == '\x1f')
			buffer[j] = '\1';
		j++;
	}
}

static int	is_in_dquote(char *str, int index)
{
	int	i;
	int	in_dq;

	i = 0;
	in_dq = 0;
	while (i < index)
	{
		if (str[i] == 39 && !in_dq)
		{
			i++;
			while (str[i] && str[i] != 39)
				i++;
		}
		else if (str[i] == 34)
			in_dq = !in_dq;
		i++;
	}
	return (in_dq);
}

char	*convert_var(char *str, int index, char **envp)
{
	int		i;
	char	buffer[2048];
	int		in_dq;

	if (str[index] != '$')
		return (NULL);
	in_dq = is_in_dquote(str, index);
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
	if (in_dq)
		empty_prompt_spaces(buffer);
	str = transpose_var(str, index, buffer, 1);
	return (str);
}

char	*change_var(char *str, char **envp)
{
	int		i;
	char	*tmp;

	i = 0;
	while (!(str[i] == '$' && is_valid_var(&str[i], 0) && is_ok_quote(str, i)))
		i++;
	tmp = convert_var(str, i, envp);
	free(str);
	if (!tmp)
		return (NULL);
	return (tmp);
}
