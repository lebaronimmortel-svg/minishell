/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 13:32:29 by alexfuen          #+#    #+#             */
/*   Updated: 2026/03/08 13:32:31 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/header.h"

int	parser(t_token *lexer)
{
	int	i;

	if (lexer[0].type == 'p')
		return (0);
	i = 0;
	while (lexer[i].type)
	{
		if ((lexer[i].type == 's' || lexer[i].type == 'h'
				|| lexer[i].type == 'r' || lexer[i].type == 'a')
			&& lexer[i + 1].type != 'w')
			return (0);
		if (lexer[i].type == 'p' && lexer[i + 1].type == 'p')
			return (0);
		i++;
	}
	return (1);
}

static void	fill_space(char *str, int *i, char c)
{
	(*i)++;
	while (str[*i] != c)
	{
		if (str[*i] == ' ')
			str[*i] = '@';
		(*i)++;
	}
	(*i)++;
}

static void	check(char *str, int *i, int *flag, char *c)
{
	while (str[*i])
	{
		while (str[*i] && str[*i] != 39 && str[*i] != 34)
			(*i)++;
		if (str[*i] && ft_strchr(&str[*i + 1], str[*i]))
		{
			*c = str[*i];
			*flag = 1;
			break ;
		}
		else
		{
			if (str[*i] && str[*i + 1])
				(*i)++;
			else
				break ;
		}
	}
}

void	check_quote(char *str)
{
	int		i;
	char	c;
	int		flag;

	i = 0;
	c = 0;
	while (1)
	{
		flag = 0;
		check(str, &i, &flag, &c);
		if (flag)
			fill_space(str, &i, c);
		else
			break ;
	}
}
