/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <alexfuen@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 21:30:40 by alexfuen          #+#    #+#             */
/*   Updated: 2026/10/19 21:30:40 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

void	exit_cleanly(int code, t_data *data, char **split)
{
	free_split(split, 0);
	free_split(data->env, 0);
	free_split(data->env_bis, 0);
	free(data);
	rl_clear_history();
	exit(code);
}

static char	**print_order(t_token *lexer)
{
	int		i;
	char	**split;

	i = 0;
	while (lexer[i].type)
		i++;
	split = ft_calloc(2 * (i + 1), sizeof(char *));
	if (!split)
		return (NULL);
	split[0] = ft_strdup("");
	loop(lexer, split);
	return (split);
}

void	free_lexer(t_token *lex)
{
	int	i;

	if (!lex)
		return ;
	i = 0;
	while (lex[i].type)
	{
		free(lex[i].value);
		i++;
	}
	free(lex[i].value);
	free(lex);
}

int	execute_prompt(char **split, t_token *lex, t_data *data)
{
	int	status_code;

	if (parser(lex))
	{
		split = print_order(lex);
		free_lexer(lex);
		preprocess_split(split, 0, 0);
		status_code = exec_main(split, 0, data, count_cmds(split, 0, 0));
		free_split(split, 0);
	}
	else
	{
		free_lexer(lex);
		status_code = 2;
		data->error_code = 2;
		ft_putstr_fd("minishell: syntax error\n", 2);
	}
	return (status_code);
}

char	*get_user(t_data *data)
{
	int		i;
	char	*result;
	char	**split;

	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], "USER=", 5))
		{
			split = ft_split(data->env[i], '=');
			if (!split)
				return (NULL);
			result = ft_strdup(split[1]);
			if (!result)
				return (NULL);
			free_split(split, 0);
			return (result);
		}
		i++;
	}
	return (NULL);
}
