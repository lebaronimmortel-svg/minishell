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

static void	print_token(char c)
{
	if (c == 'p')
		printf("\n\nPipe to :\n\n");
	else if (c == 'r')
		printf("\n\nRedir out to :\n\n");
	else if (c == 'a')
		printf("\n\nAppend to :\n\n");
	else if (c == 'h')
		printf("\n\nHeredoc to :\n\n");
	else if (c == 's')
		printf("\n\nRedir in to :\n\n");
}

static void	join_cmd(char **split, t_token *lexer, int *i, int j)
{
	char	*tmp;

	tmp = ft_strjoin(split[j], " ");
	free(split[j]);
	split[j] = tmp;
	tmp = ft_strjoin(split[j], lexer[*i].value);
	free(split[j]);
	split[j] = tmp;
	printf("	%s", lexer[*i].value);
	(*i)++;
}

static void	loop(t_token *lexer, char **split)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (1)
	{
		while (lexer[i].type == 'w')
			join_cmd(split, lexer, &i, j);
		if (lexer[i].type)
		{
			j++;
			split[j] = ft_strdup("");
			print_token(lexer[i].type);
		}
		else if (lexer[i].type == 0)
		{
			if (i)
				split[j + 1] = NULL;
			else
				split[0] = NULL;
			break ;
		}
		i++;
	}
}

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

// Commands to be executed successively are in split
void	main_loop(char **split, t_token *lex, char **envp)
{
	char	*str;

	while (1)
	{
		str = readline("\n🌈 ");
		if (str == NULL)
			exit(0);
		lex = lexer(str);
		if (lex)
		{
			print_lexer(lex);
			if (parser(lex))
			{
				printf("\n✅ OK\n\n\n");
				split = print_order(lex);
				print_icon(2);
				exec_main(envp, split);
			}
			else
				printf("\n❌ NOK\n\n");
		}
	}
}
