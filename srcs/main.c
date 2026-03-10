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

static char **print_order(t_token *lexer)
{
	int	i;
	int j;
	char **split;
	char *tmp;
	
	i = 0;
	while(lexer[i].type)
		i++;

	split = ft_calloc(i + 1, sizeof(char *));
	split[0] = ft_strdup("");
	print_icon(1);
	printf("\nExecute :\n\n");
	i = 0;
	j = 0;
	while (1)
	{
		while (lexer[i].type == 'w')
		{

			tmp = ft_strjoin(split[j], " ");
			free(split[j]);
			split[j] = tmp;
			tmp = ft_strjoin(split[j], lexer[i].value);
			free(split[j]);
			split[j] = tmp;
			
			printf("	%s", lexer[i].value);
			i++;
		}
		if (lexer[i].type == 'p')
		{
			j++;
			split[j] = ft_strdup("");
			printf("\n\nPipe to :\n\n");
		}
		else if (lexer[i].type == 'r')
		{
			j++;
			split[j] = ft_strdup("");
			printf("\n\nRedir out to :\n\n");
		}
		else if (lexer[i].type == 'a')
		{
			j++;
			split[j] = ft_strdup("");
			printf("\n\nAppend to :\n\n");
		}
		else if (lexer[i].type == 'h')
		{
			j++;
			split[j] = ft_strdup("");
			printf("\n\nHeredoc to :\n\n");
		}
		else if (lexer[i].type == 's')
		{
			j++;
			split[j] = ft_strdup("");
			printf("\n\nRedir in to :\n\n");
		}
		else if (lexer[i].type == 0)
		{
			split[j + 1] = NULL;
			break ;
		}
		i++;
	}
	printf("\n\n");
	return (split);
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

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_token	*lex;
	char **split;

	(void) argc;
	(void) argv;
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
				split = print_order(lex);
				print_icon(2);
				exec_main(envp, split);
			}
			else
				printf("\n❌ NOK\n\n");
		}
	}
	return (0);
}
