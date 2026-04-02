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

static void	exit_cleanly(int code, t_data *data, char **split)
{
	free(data);
	free_split(split, 0);
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
	print_icon(1);
	printf("\nExecute :\n\n");
	loop(lexer, split);
	printf("\n\n");
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
	free(lex);
}

void	main_loop(char **split, t_token *lex, char **envp, t_data *data)
{
	char	*str;

	while (1)
	{
		str = readline("\n🌈 ");
		if (str == NULL)
			exit_cleanly(0, data, split);
		add_history(str);
		lex = lexer(str, envp, data);
		free(str);
		if (lex)
		{
			print_lexer(lex);
			if (parser(lex))
			{
				printf("\n✅ OK\n\n\n");
				free_split(split, 0);
				split = print_order(lex);
				free_lexer(lex);
				print_icon(2);
				data->error_code = exec_main(envp, split, 0, 0, data);
				printf("\n");
			}
			else
				printf("\n❌ NOK\n\n");
		}
	}
}
