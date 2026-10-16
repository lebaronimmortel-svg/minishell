/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 21:31:23 by alexfuen          #+#    #+#             */
/*   Updated: 2026/05/04 21:31:25 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

void	handle_echo(int *status, char *input)
{
	char	**split;

	if (!ft_strncmp(input, "echo ", 5) || (!ft_strncmp(input, "echo", 4)
			&& ft_strlen(input) == 4))
	{
		split = ft_split(input, ' ');
		if (!split)
		{
			*status = 139;
			return ;
		}
		*status = echo(input, 0);
		free_split(split, 0);
	}
}

void	handle_export(int *status, char *input, t_data *data)
{
	if ((!ft_strncmp(input, "export", 6)) && ft_strlen(input) == 6)
		export_single(data);
	else if ((!ft_strncmp(input, "export ", 7)))
		*status = ft_export(input, data);
}

void	handle_cd(int *status, char *input, t_data *data)
{
	if (!ft_strncmp(input, "cd ", 3)
		|| (!ft_strncmp(input, "cd", 2)
			&& ft_strlen(input) == 2))
		*status = cd(input, data);
}

void	handle_dot(int *status, char *input)
{
	if (!ft_strncmp(input, ".", 1) && ft_strlen(input) == 1)
	{
		ft_putstr_fd(" filename argument required . filename [arguments]\n", 2);
		*status = 2;
	}
}

int	exec_built_in(char *input, t_data *data, char **cmd_split, int i)
{
	int		status;
	int		flag;

	flag = my_memlen(cmd_split) > i + 1;
	status = 0;
	handle_pwd(&status, input);
	handle_unset(&status, input, data);
	handle_env(&status, input, data);
	handle_exit(&status, input, data, flag);
	handle_echo(&status, input);
	handle_export(&status, input, data);
	handle_cd(&status, input, data);
	handle_dot(&status, input);
	return (status);
}
