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

void	print_icon(int flag)
{
	if (flag == 1)
	{
		printf("╔══╗\n");
		printf("║🛄║ -> Parsing\n");
		printf("╚══╝\n");
	}
	else if (flag == 0)
	{
		printf("\n╔══╗\n");
		printf("║🛃║ -> Lexing\n");
		printf("╚══╝\n");
	}
	else if (flag == 2)
	{
		printf("\n╔══╗\n");
		printf("║♿║ -> Executing\n");
		printf("╚══╝\n\n");
	}
}

void	print_lexer(t_token *lexer)
{
	int	i;

	print_icon(0);
	i = 0;
	printf("\n");
	while (lexer[i].type)
	{
		if (lexer[i].type == 'p')
			printf("PIPE : ");
		else if (lexer[i].type == 'a')
			printf("APPEND : ");
		else if (lexer[i].type == 'h')
			printf("HEREDOC : ");
		else if (lexer[i].type == 'r')
			printf("OUT_REDIR : ");
		else if (lexer[i].type == 's')
			printf("INP_REDIR : ");
		else if (lexer[i].type == 'w')
			printf("WORD : ");
		printf("%s\n", lexer[i].value);
		i++;
	}
	return ;
}

static void	handler0(int sig)
{
	(void) sig;
	printf("\n\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static int	init(t_data *data, char **envp)
{
	data->error_code = 0;
	data->env = split_dup(envp);
	if (!data->env)
	{
		free(data);
		return (0);
	}
	data->env_bis = split_dup(envp);
	if (!data->env_bis)
	{
		free_split(data->env, 0);
		free(data);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*lex;
	char	**split;
	t_data	*data;

	signal(SIGINT, handler0);
	signal(SIGQUIT, SIG_IGN);
	(void) argv;
	if (argc != 1)
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (!init(data, envp))
		return (1);
	printf("\n");
	lex = NULL;
	split = NULL;
	main_loop(envp, split, lex, data);
	return (0);
}
