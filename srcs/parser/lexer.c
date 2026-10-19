/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <alexfuen@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 21:30:40 by alexfuen          #+#    #+#             */
/*   Updated: 2026/10/19 21:30:40 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

static int	lex_convert(char **split, t_token *token, t_data *data)
{
	int	i;
	int	j;
	int	quoted;

	i = 0;
	j = 0;
	while (split[j])
	{
		quoted = (ft_strchr(split[j], '"') || ft_strchr(split[j], '\''));
		if (!expand_input(token, split[j], data, i))
			return (0);
		if (i == 0 || token[i - 1].type != 'h')
			remove_quotes(token[i].value);
		delete_spaces(token, i, quoted);
		i++;
		j++;
	}
	token[i].type = 0;
	token[i].value = NULL;
	return (1);
}

static int	handle_special(char *str, char *res, int *i, int *j)
{
	if (str[*i] == '\t')
	{
		res[(*j)++] = ' ';
		return (1);
	}
	if (str[*i] == '<' || str[*i] == '>' || str[*i] == '|')
	{
		if (*j > 0 && res[*j - 1] != ' ')
			res[(*j)++] = ' ';
		res[(*j)++] = str[*i];
		if ((str[*i] == '<' || str[*i] == '>')
			&& str[*i + 1] == str[*i])
			res[(*j)++] = str[++(*i)];
		if (str[*i + 1] && str[*i + 1] != ' ')
			res[(*j)++] = ' ';
		return (1);
	}
	return (0);
}

static char	*preprocess_operators(char *str, int i, int j)
{
	char	*result;
	int		in_sq;
	int		in_dq;

	in_sq = 0;
	in_dq = 0;
	result = malloc(ft_strlen(str) * 3 + 1);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == 39 && !in_dq)
			in_sq = !in_sq;
		else if (str[i] == 34 && !in_sq)
			in_dq = !in_dq;
		if (!in_sq && !in_dq && handle_special(str, result, &i, &j))
		{
			i++;
			continue ;
		}
		result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

t_token	*assign_lexer(char **split, t_data *data)
{
	t_token	*token;

	token = malloc((split_len(split) + 1) * sizeof(t_token));
	if (!token)
	{
		free_split(split, 0);
		return (NULL);
	}
	if (!lex_convert(split, token, data))
	{
		free_split(split, 0);
		free_lexer(token);
		return (NULL);
	}
	free_split(split, 0);
	return (token);
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
	token = assign_lexer(split, data);
	if (!token)
		return (NULL);
	return (token);
}
