/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 22:57:33 by alexfuen          #+#    #+#             */
/*   Updated: 2026/03/10 22:57:35 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

static char	**print_order(t_token *lexer)
{
	int		i;
	char	**split;

	i = 0;
	while (lexer[i].type)
		i++;
	split = ft_calloc(i + 1, sizeof(char *));
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

void	main_loop(char **split, t_token *lex, char **envp)
{
	char	*str;

	while (1)
	{
		str = readline("\n🌈 ");
		if (str == NULL)
			exit(0);
		lex = lexer(str);
		free(str);
		if (lex)
		{
			print_lexer(lex);
			if (parser(lex))
			{
				printf("\n✅ OK\n\n\n");
				split = print_order(lex);
				free_lexer(lex);
				print_icon(2);
				exec_main(envp, split);
			}
			else
				printf("\n❌ NOK\n\n");
		}
	}
}
