/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 23:41:09 by alexfuen          #+#    #+#             */
/*   Updated: 2026/03/12 23:41:11 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

static void	my_memmove(char *str)
{
	int	i;

	if (!str || !(*str) || *str != ' ')
		return ;
	i = 0;
	while (str[i + 1])
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i] = 0;
}

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

static void	join_symbol(char **split, int *j, t_token *lexer, int i)
{
	(*j)++;
	split[*j] = ft_strdup(lexer[i].value);
	(*j)++;
	split[*j] = ft_strdup("");
	print_token(lexer[i].type);
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

void	loop(t_token *lexer, char **split)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (1)
	{
		while (lexer[i].type == 'w')
			join_cmd(split, lexer, &i, j);
		my_memmove(split[j]);
		if (lexer[i].type)
			join_symbol(split, &j, lexer, i);
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
