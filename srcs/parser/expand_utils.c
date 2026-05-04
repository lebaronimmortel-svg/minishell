/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 21:34:06 by alexfuen          #+#    #+#             */
/*   Updated: 2026/05/04 21:34:07 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

char	convert_type(char *str)
{
	char	c;

	if (str[0] == '|' && !str[1])
		c = 'p';
	else if (str[0] == '>' && str[1] == '>' && !str[2])
		c = 'a';
	else if (str[0] == '<' && str[1] == '<' && !str[2])
		c = 'h';
	else if (str[0] == '>' && !str[1])
		c = 'r';
	else if (str[0] == '<' && !str[1])
		c = 's';
	else
		c = 'w';
	return (c);
}

char	*append_pid(char *str, int i)
{
	char	*ret;
	char	*tmp;
	char	*tmp2;
	char	*result;
	char	*pid;

	tmp2 = str;
	tmp = &str[i + 1];
	str[i - 1] = '\0';
	pid = my_get_pid();
	result = ft_strjoin(str, pid);
	if (!result)
		return (NULL);
	ret = ft_strjoin(result, tmp);
	if (!str)
	{
		free(result);
		return (NULL);
	}
	free(result);
	free(tmp2);
	free(pid);
	return (ret);
}

static char	*expand_double(char *str)
{
	int		i;

	i = 1;
	while (str[i])
	{
		if (str[i] == '$' && str[i - 1] == '$')
		{
			str = append_pid(str, i);
			if (!str)
				return (NULL);
		}
		i++;
	}
	return (str);
}

void	delete_spaces(t_token *token, int i, int quoted)
{
	int	k;

	k = 0;
	while (token[i].value[k])
	{
		if (token[i].value[k] == '\2')
			move_one(&token[i].value[k]);
		else
			k++;
	}
	if (token[i].value[0] == '\0' && quoted)
	{
		token[i].value[0] = '\6';
		token[i].value[1] = '\0';
	}
}

int	expand_input(t_token *token, char *str, t_data *data, int i)
{
	token[i].type = convert_type(str);
	token[i].value = ft_strdup(str);
	if (!token[i].value)
		return (0);
	handle_single(token[i].value);
	token[i].value = expand_double(token[i].value);
	if (!token[i].value)
		return (0);
	while (!are_var_handled(token[i].value))
	{
		token[i].value = change_var(token[i].value, data->env);
		if (!token[i].value)
			return (0);
	}
	token[i].value = expand_code(token[i].value, data);
	if (!token[i].value)
		return (0);
	return (1);
}
