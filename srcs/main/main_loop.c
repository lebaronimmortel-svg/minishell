/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 22:57:33 by alexfuen          #+#    #+#             */
/*   Updated: 2026/03/18 18:03:52 by alexfuen         ###   ########.fr       */
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

static void	free_lexer(t_token *lex)
{
	int	i;

	i = 0;
	while (lex[i].type)
	{
		free(lex[i].value);
		i++;
	}
	free(lex[i].value);
	free(lex);
}

static int	execute_prompt(char **split, t_token *lex, t_data *data)
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
		ft_putstr_fd("minishell: syntax error\n", 2);
	}
	return (status_code);
}

void	main_loop(char **split, t_token *lex, t_data *data)
{
	char	*str;
	int		status;

	status = 0;
	while (1)
	{
		str = readline("$> ");
		if (str == NULL)
			exit_cleanly(status, data, split);
		else
			add_history(str);
		lex = lexer(str, data);
		free(str);
		if (lex)
			status = execute_prompt(split, lex, data);
		if (data->end)
			exit_cleanly(data->error_code, data, split);
	}
}
