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

#include "./header/header.h"

static void	print_icon(int flag)
{
	if (flag)
	{
		printf("╔══╗\n");
		printf("║🛄║\n");
		printf("╚══╝\n");
	}
	else
	{
		printf("\n╔══╗\n");
		printf("║🛃║\n");
		printf("╚══╝\n");
	}
}

static void	print_lexer(t_token *lexer)
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

static void	print_order(t_token *lexer)
{
	int	i;

	print_icon(1);
	printf("\nExecute :\n\n");
	i = 0;
	while (1)
	{
		while (lexer[i].type == 'w')
			printf("	%s", lexer[i++].value);
		if (lexer[i].type == 'p')
			printf("\n\nPipe to :\n\n");
		else if (lexer[i].type == 'r')
			printf("\n\nRedir out to :\n\n");
		else if (lexer[i].type == 'a')
			printf("\n\nAppend to :\n\n");
		else if (lexer[i].type == 'h')
			printf("\n\nHeredoc to :\n\n");
		else if (lexer[i].type == 's')
			printf("\n\nRedir in to :\n\n");
		else if (lexer[i].type == 0)
			break ;
		i++;
	}
	printf("\n\n");
}

static void	print_header(void)
{
	printf("\n");
	printf("███╗   ███╗██╗███╗   ██╗██╗███████╗");
	printf("██╗  ██╗███████╗██╗     ██╗     \n");
	printf("████╗ ████║██║████╗  ██║██║██╔════╝");
	printf("██║  ██║██╔════╝██║     ██║     \n");
	printf("██╔████╔██║██║██╔██╗ ██║██║███████╗");
	printf("███████║█████╗  ██║     ██║     \n");
	printf("██║╚██╔╝██║██║██║╚██╗██║██║╚════██║");
	printf("██╔══██║██╔══╝  ██║     ██║     \n");
	printf("██║ ╚═╝ ██║██║██║ ╚████║██║███████║");
	printf("██║  ██║███████╗███████╗███████╗\n");
	printf("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝");
	printf("╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
}

int	main(void)
{
	char	*str;
	t_token	*lex;

	print_header();
	printf("\n");
	while (1)
	{
		str = readline("\n🌈 ");
		lex = lexer(str);
		if (lex)
		{
			print_lexer(lex);
			if (parser(lex))
			{
				printf("\n✅ OK\n\n\n");
				print_order(lex);
			}
			else
				printf("\n❌ NOK\n\n");
			free(str);
		}
	}
	return (0);
}
