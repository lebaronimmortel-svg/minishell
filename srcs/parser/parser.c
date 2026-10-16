/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 21:03:29 by alexfuen          #+#    #+#             */
/*   Updated: 2026/05/04 21:03:32 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

char	*expand_code(char *str, t_data *data)
{
	int		i;
	char	*code_str;
	char	*old_str;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i + 1])
	{
		if (str[i] == '$' && str[i + 1] == '?' && is_ok_quote(str, i))
		{
			code_str = ft_itoa(data->error_code);
			old_str = str;
			str = transpose_var(str, i, code_str, 0);
			free(old_str);
			free(code_str);
			if (!str)
				return (NULL);
			i = 0;
		}
		else
			i++;
	}
	return (str);
}

void	assign_begin(char *buffer, int flag)
{
	if (!flag)
	{
		buffer[0] = '\2';
		buffer[1] = '\0';
	}
}

void	fill_input_spaces(char *buffer)
{
	int	j;

	j = 0;
	while (buffer[j])
	{
		if (buffer[j] == ' ')
			buffer[j] = '\x1f';
		j++;
	}
}

void	var_search(char *buffer, char **envp)
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
			fill_input_spaces(buffer);
			break ;
		}
		i++;
	}
	assign_begin(buffer, flag);
}

int	parser(t_token *lexer)
{
	int	i;

	if (lexer[0].type == 'p')
		return (0);
	i = 0;
	while (lexer[i].type)
	{
		if ((lexer[i].type == 's' || lexer[i].type == 'h'
				|| lexer[i].type == 'r' || lexer[i].type == 'a')
			&& lexer[i + 1].type != 'w')
			return (0);
		if (lexer[i].type == 'p' && !has_cmd_after_pipe(lexer, i + 1))
			return (0);
		i++;
	}
	return (1);
}
