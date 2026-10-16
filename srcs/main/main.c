/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 06:44:34 by lukrodri          #+#    #+#             */
/*   Updated: 2026/02/17 06:44:36 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

int	g_ack = 0;

void	handler0(int sig)
{
	(void) sig;
	g_ack = sig + 128;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static int	init(t_data *data, char **envp)
{
	data->error_code = 0;
	data->end = 0;
	data->expand = 1;
	data->signal = 0;
	data->env = split_dup(envp);
	if (!data->env)
	{
		data->env = ft_calloc(1, sizeof(char *));
		if (!data->env)
			return (0);
	}
	data->env_bis = split_dup(data->env);
	if (!data->env_bis)
	{
		data->env_bis = ft_calloc(1, sizeof(char *));
		if (!data->env_bis)
		{
			free_split(data->env, 0);
			return (0);
		}
	}
	return (1);
}

void	prompt_loop(t_data *data, char **split, t_token *lex)
{
	int		flag;
	char	*str;

	flag = 0;
	str = readline("$> ");
	if (g_ack)
	{
		flag = g_ack;
		g_ack = 0;
	}
	if (flag)
	{
		data->error_code = flag;
		flag = 0;
	}
	if (str == NULL)
		exit_cleanly(data->error_code, data, split);
	else if (ft_strlen(str) != 0)
		add_history(str);
	lex = lexer(str, data);
	free(str);
	if (lex)
		execute_prompt(split, lex, data);
	if (data->end)
		exit_cleanly(data->error_code, data, split);
}

void	main_loop(char **split, t_token *lex, t_data *data)
{
	while (1)
		prompt_loop(data, split, lex);
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*lex;
	char	**split;
	t_data	*data;

	set_signal_dfl();
	(void) argv;
	if (argc != 1)
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (139);
	if (!init(data, envp))
		return (139);
	lex = NULL;
	split = NULL;
	main_loop(split, lex, data);
	return (0);
}
