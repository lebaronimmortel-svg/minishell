/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:25:02 by alexfuen          #+#    #+#             */
/*   Updated: 2026/03/17 21:45:19 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

static int	is_alphanum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

int	is_valid_var(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != 39 && str[i] != 34)
	{
		if (i != 0 && !is_alphanum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	quote_type(char *str, int *i, int index)
{
	char	c;
	int		flag;

	flag = 0;
	c = str[*i];
	(*i)++;
	while (str[*i] != c)
	{
		if (*i == index)
			flag = 1;
		(*i)++;
	}
	if (flag)
	{
		if (c == 39)
			return (0);
		if (c == 34)
			return (1);
	}
	return (2);
}

static int	check_quote_var(char *str, int index)
{
	int		i;
	int		ret;

	i = 0;
	while (str[i])
	{
		if ((str[i] == 39 && ft_strchr(&str[i + 1], 39))
			|| (str[i] == 34 && ft_strchr(&str[i + 1], 34)))
		{
			ret = quote_type(str, &i, index);
			if (ret != 2)
				return (ret);
		}
		i++;
	}
	return (1);
}

int	is_ok_quote(char *str, int index)
{
	if (!ft_strchr(str, '$'))
		return (1);
	if (!ft_strchr(str, 39))
		return (1);
	return (check_quote_var(str, index));
}
