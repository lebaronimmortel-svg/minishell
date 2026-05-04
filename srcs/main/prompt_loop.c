/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
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

static void	join_symbol(char **split, int *j, t_token *lexer, int i)
{
	(*j)++;
	split[*j] = ft_strdup(lexer[i].value);
	(*j)++;
	split[*j] = ft_strdup("");
}

static void	join_cmd(char **split, t_token *lexer, int *i, int j)
{
	char	*tmp;

	if (lexer[*i].value[0] == '\0')
	{
		(*i)++;
		return ;
	}
	if (lexer[*i].value[0] == ' ' && !lexer[*i].value[1])
		tmp = ft_strjoin(split[j], " ");
	else
	{
		tmp = ft_strjoin(split[j], " ");
		if (!tmp)
			return ;
		free(split[j]);
		split[j] = tmp;
		tmp = ft_strjoin(split[j], lexer[*i].value);
	}
	if (!tmp)
		return ;
	free(split[j]);
	split[j] = tmp;
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
			{
				free(split[0]);
				split[0] = NULL;
			}
			break ;
		}
		i++;
	}
}
