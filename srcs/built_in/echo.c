/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 19:10:33 by alexfuen          #+#    #+#             */
/*   Updated: 2026/04/08 19:10:35 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

static int	assign_flag(int flag, char *input, int *i)
{
	while (input[*i] && is_alphanum((int)input[*i]))
	{
		if (input[*i] == 'n' && flag)
			flag = 2;
		if (input[*i] != 'n')
			flag = 0;
		(*i)++;
	}
	return (flag);
}

int	return_status(int flag)
{
	if (flag == 2)
		return (1);
	else
		return (0);
}

static int	has_n_flag(char *input)
{
	int	i;
	int	flag;
	int	flag2;

	i = 0;
	flag = 1;
	flag2 = 0;
	while (1)
	{
		while (input[i] && !(input[i] == '-' && input[i - 1] == ' '))
		{
			if (i && input[i] != ' ' && input[i] != '-' && input[i - 1] == ' ')
			{
				flag2 = 1;
				break ;
			}
			i++;
		}
		if (!input[i++] || flag2)
			break ;
		flag = assign_flag(flag, input, &i);
		if (flag == 2)
			break ;
	}
	return (return_status(flag));
}

static int	is_valid_flag(char *str)
{
	int	i;

	i = 0;
	if (!str[i] || str[i] == ' ')
		return (0);
	while (str[i] && str[i] != ' ')
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	has_more_n_flag(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (!str[i] || str[i] != '-')
			break ;
		i++;
		while (str[i] && str[i] != ' ')
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		flag = 1;
	}
	return (flag);
}

int	end_of_string(char *input)
{
	if (!has_n_flag(input))
		ft_putstr_fd("\n", 1);
	return (0);
}

void	replace_fill_basic(char *input, int k)
{
	while (input[k])
	{
		if (input[k] == '\1' || input[k] == '\x1f')
			input[k] = ' ';
		else if (input[k] == '\3')
			input[k] = '|';
		else if (input[k] == '\4')
			input[k] = '<';
		else if (input[k] == '\5')
			input[k] = '>';
		else if (input[k] == '\6')
		{
			move_one(&input[k]);
			continue ;
		}
		k++;
	}
}

void	skip_spaces(char *input, int i)
{
	while (input[i] == ' ')
		i++;
	if (input[i])
		ft_putstr_fd(" ", 1);
}

void	skip_all_spaces(char *input, int *i)
{
	if (input[*i] == ' ')
		skip_spaces(input, *i);
	while (input[*i] && input[*i] == ' ')
		(*i)++;
}

int	echo_status(char *input, int i, int k)
{
	replace_fill_basic(input, k);
	ft_putstr_fd(&input[i], 1);
	return (end_of_string(input));
}

int	echo(char *input, int k)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (1)
	{
		while (input[i] && input[i] != ' ')
			i++;
		if (!input[i])
			return (end_of_string(input));
		i++;
		if (!input[i])
			return (end_of_string(input));
		skip_all_spaces(input, &i);
		if (!input[i])
			return (end_of_string(input));
		if (flag && !has_more_n_flag(&input[i]))
			break ;
		if (input[i] != '-' || !is_valid_flag(&input[i + 1]))
			break ;
		else
			flag = 1;
	}
	return (echo_status(input, i, k));
}
