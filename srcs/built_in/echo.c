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
	while (input[*i] && ft_isalpha((int)input[*i]))
	{
		if (input[*i] == 'n' && flag)
			flag = 2;
		if (input[*i] != 'n')
			flag = 0;
		(*i)++;
	}
	return (flag);
}

static int	has_n_flag(char *input)
{
	int	i;
	int flag2;
	int	flag;

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
		if (!input[i] || flag2)
			break ;
		i++;
		flag = assign_flag(flag, input, &i);
		if (flag == 2)
			break ;
	}
	if (flag == 2)
		return (1);
	else
		return (0);
}

void	echo(char *input, int k)
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
			return ;
		i++;
		if (!input[i])
			return ;
		if (flag)
			break ;
		if (input[i] != '-')
			break ;
		else
			flag = 1;
	}
	k = i;
	while (input[k])
	{
		if (input[k] == '\1')
			input[k] = ' ';
		k++;
	}
	ft_putstr_fd(&input[i], 1);
	if (!has_n_flag(input))
		ft_putstr_fd("\n", 1);
}
