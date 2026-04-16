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

static void	execute_prompt(char **split, t_token *lex,
	t_data *data)
{
	if (parser(lex))
	{
		split = print_order(lex);
		free_lexer(lex);
		data->error_code = exec_main(split, 0, data);
		free_split(split, 0);
	}
	else
		printf("parsing error\n");
}

void	main_loop(char **split, t_token *lex, t_data *data)
{
	char	*str;

	while (1)
	{
		str = readline("$> ");
		if (str == NULL)
			exit_cleanly(0, data, split);
		add_history(str);
		lex = lexer(str, data);
		free(str);
		if (lex)
			execute_prompt(split, lex, data);
	}
}
