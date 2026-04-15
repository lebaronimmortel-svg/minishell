/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 13:27:20 by alexfuen          #+#    #+#             */
/*   Updated: 2026/03/08 13:27:23 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

static char	convert_type(char *str)
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

static void	expand_pid(char *str)
{
	int i;

	if (!str)
		return ;
	i = 1;
	while (str[i])
	{
		if (str[i] == '$' && str[i - 1] == '$' && is_ok_quote(str, i - 1))
		{
			str[i] = '>';
			str[i - 1] = '<';
		}
		i++;
	}
}

static void	lex_convert(char **split, t_token *token, t_data *data)
{
	int	i;

	i = 0;
	while (split[i])
	{
		token[i].type = convert_type(split[i]);
		token[i].value = ft_strdup(split[i]);
		handle_single(token[i].value);
		expand_pid(token[i].value);
		while (!are_var_handled(token[i].value))
			token[i].value = change_var(token[i].value, data->env);
		token[i].value = expand_code(token[i].value, data);
		if (i == 0 || token[i - 1].type != 'h')
			remove_quotes(token[i].value);
		i++;
	}
	token[i].type = 0;
	token[i].value = NULL;
}

static void	quote_clean(char **split)
{
	int	i;
	int	j;

	i = 0;
	while (split[i])
	{
		j = 0;
		while (split[i][j])
		{
			if (split[i][j] == '@')
				split[i][j] = ' ';
			j++;
		}
		i++;
	}
}

static char	*preprocess_operators(char *str, int i, int j)
{
	char	*result;

	result = malloc(ft_strlen(str) * 3 + 1);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\t')
		{
			result[j++] = ' ';
			i++;
			continue ;
		}
		if (str[i] == '<' || str[i] == '>' || str[i] == '|')
		{
			if (j > 0 && result[j - 1] != ' ')
				result[j++] = ' ';
			result[j++] = str[i];
			if ((str[i] == '<' || str[i] == '>') && str[i + 1] == str[i])
				result[j++] = str[++i];
			if (str[i + 1] && str[i + 1] != ' ')
				result[j++] = ' ';
		}
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

t_token	*lexer(char *str, t_data *data)
{
	char	**split;
	t_token	*token;
	char	*processed;

	if (!str)
		return (NULL);
	processed = preprocess_operators(str, 0, 0);
	if (!processed)
		return (NULL);
	check_quote(processed);
	split = ft_split(processed, ' ');
	free(processed);
	if (!split)
		return (NULL);
	quote_clean(split);
	token = malloc((split_len(split) + 1) * sizeof(t_token));
	if (!token)
	{
		free_split(split, 0);
		return (NULL);
	}
	lex_convert(split, token, data);
	free_split(split, 0);
	return (token);
}
