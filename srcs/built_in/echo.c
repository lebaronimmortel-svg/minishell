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
	int	flag;

	i = 0;
	flag = 1;
	while (1)
	{
		while (input[i] && !(input[i] == '-' && input[i - 1] == ' '))
		{
			if (i && input[i] != ' ' && input[i] != '-' && input[i - 1] == ' ')
				break ;
			i++;
		}
		if (!input[i])
			break ;
		i++;
		flag = assign_flag(flag, input, &i);
	}
	if (flag == 2)
		return (1);
	else
		return (0);
}

void	echo(char *input)
{
	int	i;

	i = 0;
	while (1)
	{
		while (input[i] && input[i] != ' ')
			i++;
		if (!input[i])
			return ;
		i++;
		if (!input[i])
			return ;
		if (input[i] != '-')
			break ;
	}
	printf("%s", &input[i]);
	if (has_n_flag(input))
		printf("\n");
}
