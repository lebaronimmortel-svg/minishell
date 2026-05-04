/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 21:32:50 by alexfuen          #+#    #+#             */
/*   Updated: 2026/05/04 21:32:51 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

int	is_numeric_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

void	display_error_msg(t_data *data, char **args)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free_split(args, 0);
	data->end = 1;
}

int	err_msg_1(char **args)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	free_split(args, 0);
	return (1);
}

int	finish_program(t_data *data, char **args)
{
	free_split(args, 0);
	data->end = 1;
	return (data->error_code);
}

int	err_msg_2(t_data *data, char **args)
{
	display_error_msg(data, args);
	return (2);
}
