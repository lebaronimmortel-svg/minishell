/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 08:48:18 by lukrodri          #+#    #+#             */
/*   Updated: 2026/03/20 08:48:19 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

static int	find_env(t_exec *exec, int i)
{
	char	*tmp;

	if (!exec->command || !exec->command[0])
		return (1);
	if (access(exec->command[0], X_OK) == 0)
	{
		exec->w_path = ft_strdup(exec->command[0]);
		if (!exec->w_path)
			return (1);
		return (0);
	}
	while (exec->all_path && exec->all_path[i])
	{
		tmp = ft_strjoin(exec->all_path[i], "/");
		exec->w_path = ft_strjoin(tmp, exec->command[0]);
		free(tmp);
		if (exec->w_path && access(exec->w_path, X_OK) == 0)
			return (0);
		free(exec->w_path);
		exec->w_path = NULL;
		i++;
	}
	return (1);
}

static int	exec_command(t_exec *exec)
{
	if (find_env(exec, 0) == 1)
	{
		execve_error("command not found : ", exec->command[0]);
		free_split_exec(exec);
		if (exec->pid)
			free(exec->pid);
		exec->pid = NULL;
		exit(127);
	}
	if (exec->w_path)
	{
		execve(exec->w_path, exec->command, exec->env);
		perror(exec->command[0]);
		free_split_exec(exec);
		if (exec->pid)
			free(exec->pid);
		exit(126);
	}
	execve_error("command not found : ", exec->command[0]);
	exit(127);
}

static void	end_fork_created(t_exec *exec, int cmd_index, int cmd_count)
{
	if (cmd_index > 0)
		close(exec->fd[cmd_index - 1][0]);
	if (cmd_index < cmd_count - 1)
		close(exec->fd[cmd_index][1]);
}

void	fork_created(t_exec *exec, int cmd_index, int cmd_count)
{
	exec->pid[cmd_index] = fork();
	if (exec->pid[cmd_index] < 0)
	{
		execve_error("Fork error", "");
		close_fd(exec, cmd_count);
		return ;
	}
	if (exec->pid[cmd_index] == 0)
	{
		if (cmd_index > 0)
			dup2(exec->fd[cmd_index - 1][0], STDIN_FILENO);
		if (cmd_index < cmd_count - 1)
			dup2(exec->fd[cmd_index][1], STDOUT_FILENO);
		close_fd(exec, cmd_count);
		if (apply_redirs(exec) != 0)
			exit(1);
		exec_command(exec);
		free_split_exec(exec);
		exit(1);
	}
	else
		end_fork_created(exec, cmd_index, cmd_count);
}

int	end_exec(t_exec *exec, int cmd_count, t_data *data)
{
	int	i;
	int	status;
	int	exit_code;

	exit_code = 0;
	status = 0;
	close_fd(exec, cmd_count);
	i = 0;
	while (i < cmd_count)
	{
		if (exec->pid[i] > 0)
			waitpid(exec->pid[i], &status, 0);
		i++;
	}
	if (exec->pid)
		free(exec->pid);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = 128 + WTERMSIG(status);
	else
		exit_code = 1;
	data->error_code = exit_code;
	return (exit_code);
}
