/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <alexfuen@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 21:30:40 by alexfuen          #+#    #+#             */
/*   Updated: 2026/10/19 21:30:40 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

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
