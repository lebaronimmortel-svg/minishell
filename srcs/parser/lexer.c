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

int	are_var_handled(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && is_valid_var(&str[i], 0) && is_ok_quote(str, i))
			return (0);
		i++;
	}
	return (1);
}

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

static void	lex_convert(char **split, t_token *token, t_data *data)
{
	int	i;

	i = 0;
	while (split[i])
	{
		token[i].type = convert_type(split[i]);
		token[i].value = ft_strdup(split[i]);
		handle_single(token[i].value);
		while (!are_var_handled(token[i].value))
			token[i].value = change_var(token[i].value, data->env);
		token[i].value = expand_code(token[i].value, data);
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

t_token	*lexer(char *str, t_data *data)
{
	char	**split;
	t_token	*token;

	if (!str)
		return (NULL);
	check_quote(str);
	split = ft_split(str, ' ');
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
