/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <alexfuen@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 21:30:40 by alexfuen          #+#    #+#             */
/*   Updated: 2026/10/19 21:30:40 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

void	handle_single(char *str)
{
	int	i;
	int	flag1;
	int	flag2;

	i = 0;
	flag1 = 0;
	flag2 = 0;
	while (str[i])
	{
		if (str[i] == 39 && flag1 == 0)
			flag2 = update_flag(flag2);
		else if (str[i] == 34 && flag2 == 0)
			flag1 = update_flag(flag1);
		if (str[i] == '$')
		{
			if (flag1 == 0 && flag2 == 0
				&& (str[i + 1] == 39 || str[i + 1] == 34))
				move_one(&str[i]);
			else
				i++;
		}
		else
			i++;
	}
}

int	has_cmd_after_pipe(t_token *lexer, int i)
{
	while (lexer[i].type && lexer[i].type != 'p')
	{
		if (lexer[i].type == 'w')
			return (1);
		if (lexer[i].type == 'r' || lexer[i].type == 'a'
			|| lexer[i].type == 's' || lexer[i].type == 'h')
			return (1);
		i += 2;
	}
	return (0);
}

void	fill_space(char *str, int *i, char c)
{
	(*i)++;
	while (str[*i] != c)
	{
		if (str[*i] == ' ')
			str[*i] = '\1';
		else if (str[*i] == '|')
			str[*i] = '\3';
		else if (str[*i] == '<')
			str[*i] = '\4';
		else if (str[*i] == '>')
			str[*i] = '\5';
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
