/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <alexfuen@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 21:30:40 by alexfuen          #+#    #+#             */
/*   Updated: 2026/10/19 21:30:40 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

int	status_code(char *input, t_data *data)
{
	char		**args;
	long long	code;
	int			i;
	int			len;

	args = ft_split(input, ' ');
	if (!args)
		return (data->error_code);
	i = 0;
	while (args[i])
		unmask_spaces(args[i++]);
	len = i;
	if (len == 1)
		return (finish_program(data, args));
	code = 0;
	if (!is_numeric_arg(args[1]) || !ft_atoll(args[1], &code))
		return (err_msg_2(data, args));
	if (len > 2)
		return (err_msg_1(args));
	free_split(args, 0);
	data->end = 1;
	return ((code % 256 + 256) % 256);
}

void	handle_pwd(int *status, char *input)
{
	if (!ft_strncmp(input, "pwd", 3) && ft_strlen(input) == 3)
		*status = pwd();
	else if (!ft_strncmp(input, "pwd ", 4))
		*status = pwd();
}

void	handle_unset(int *status, char *input, t_data *data)
{
	char	**split;

	if (!ft_strncmp(input, "unset", 5) && ft_strlen(input) == 5)
		*status = 0;
	else if (!ft_strncmp(input, "unset ", 6))
	{
		split = ft_split(input, ' ');
		if (!split)
		{
			*status = 139;
			return ;
		}
		split = quote_clean(split);
		*status = unset(&split[1], data);
		free_split(split, 0);
	}
}

void	handle_env(int *status, char *input, t_data *data)
{
	if (!ft_strncmp(input, "env", 3) && ft_strlen(input) == 3)
		*status = env(data->env);
	else if (!ft_strncmp(input, "env ", 4))
		*status = env(data->env);
}

void	handle_exit(int *status, char *input, t_data *data, int flag)
{
	if (!ft_strncmp(input, "exit", 4)
		&& ft_strlen(input) == 4)
	{
		*status = status_code(input, data);
		data->end = 1;
	}
	else if (!ft_strncmp(input, "exit ", 5))
	{
		if (flag)
			*status = status_code(input, data);
		else
		{
			*status = status_code(input, data);
			if (*status != 1)
				data->end = 1;
		}
	}
}
