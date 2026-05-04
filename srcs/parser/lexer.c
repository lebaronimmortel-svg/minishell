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

void	fonction_void(t_token *token, int i, int quoted)
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
		fonction_void(token, i, quoted);
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
