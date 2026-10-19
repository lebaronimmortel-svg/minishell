/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <alexfuen@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 21:30:40 by alexfuen          #+#    #+#             */
/*   Updated: 2026/10/19 21:30:40 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

void	handle_invalid(t_exec *exec, int *err_code)
{
	if (ft_strchr(exec->command[0], '/'))
	{
		*err_code = get_path_error(exec->command[0]);
		if (*err_code == 126)
			execve_error(exec->command[0], ": Permission denied");
		else
			execve_error(exec->command[0], ": No such file or directory");
		free_redir(exec);
		free_exec_failed(exec, *err_code);
	}
	else
	{
		execve_error(exec->command[0], ": command not found");
		free_redir(exec);
		free_exec_failed(exec, 127);
	}
}

void	handle_perm(t_exec *exec)
{
	free_data_split(exec);
	execve(exec->w_path, exec->command, exec->env);
	execve_error(exec->command[0], ": Permission denied");
	free_exec_failed(exec, 126);
}

void	handle_unknown(t_exec *exec)
{
	if (ft_strchr(exec->input, '\6'))
	{
		ft_putstr_fd("Command '' not found\n", 2);
		free_redir(exec);
		free_exec_failed(exec, 127);
	}
	free_redir(exec);
	free_exec_failed(exec, 0);
}

void	exec_command(t_exec *exec)
{
	int	err_code;

	if (!exec->command || !exec->command[0])
	{
		free_redir(exec);
		free_exec_failed(exec, 0);
	}
	if (exec->command[0][0] == '\0')
		handle_unknown(exec);
	if (find_env(exec, 0) == 1)
		handle_invalid(exec, &err_code);
	if (exec->w_path)
		handle_perm(exec);
	free_exec_failed(exec, 127);
}

void	end_fork_created(t_exec *exec, int cmd_index, int cmd_count)
{
	if (cmd_index > 0 && exec->fd[cmd_index - 1][0] != -1)
	{
		close(exec->fd[cmd_index - 1][0]);
		exec->fd[cmd_index - 1][0] = -1;
	}
	if (cmd_index < cmd_count - 1 && exec->fd[cmd_index][1] != -1)
	{
		close(exec->fd[cmd_index][1]);
		exec->fd[cmd_index][1] = -1;
	}
}
