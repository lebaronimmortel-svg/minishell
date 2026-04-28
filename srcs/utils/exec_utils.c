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
	if (!exec->command || !exec->command[0])
		return (1);
	
	if (ft_strchr(exec->command[0], '/'))
	{
		if (access(exec->command[0], X_OK) == 0)
		{
			check_dir(exec);
			exec->w_path = ft_strdup(exec->command[0]);
			if (!exec->w_path)
				return (1);
			return (0);
		}
		exec->w_path = NULL;
		return (1);
	}
	
	if (find_env_loop(exec, i) == 0)
		return (0);
		
	return (1);
}

static int	get_path_error(char *path)
{
	int		i;
	char	c;

	i = 0;
	while (path[i])
	{
		while (path[i] == '/')
			i++;
		while (path[i] && path[i] != '/')
			i++;
		if (i == 0)
			break ;
		c = path[i];
		path[i] = '\0';
		if (access(path, F_OK) != 0)
		{
			path[i] = c;
			return (127);
		}
		if (access(path, X_OK) != 0)
		{
			path[i] = c;
			return (126);
		}
		path[i] = c;
	}
	return (127);
}

static void	exec_command(t_exec *exec)
{
	int	err_code;

	if (!exec->command || !exec->command[0])
	{
		free_redir(exec);
		free_exec_failed(exec, 0);
	}
	if (exec->command[0][0] == '\0')
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
	if (find_env(exec, 0) == 1)
	{
		if (ft_strchr(exec->command[0], '/'))
		{
			err_code = get_path_error(exec->command[0]);
			if (err_code == 126)
				execve_error(exec->command[0], ": Permission denied");
			else
				execve_error(exec->command[0], ": No such file or directory");
			free_exec_failed(exec, err_code);
		}
		else
		{
			execve_error(exec->command[0], ": command not found");
			free_exec_failed(exec, 127);
		}
	}
	if (exec->w_path)
	{
		free_data_split(exec);
		execve(exec->w_path, exec->command, exec->env);
		execve_error(exec->command[0], ": Permission denied");
		free_exec_failed(exec, 126);
	}
	free_exec_failed(exec, 127);
}

static void	end_fork_created(t_exec *exec, int cmd_index, int cmd_count)
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
		{
			free_redir(exec);
			free_exec_failed(exec, 1);
		}
		exec_command(exec);
		free_split_exec(exec);
		exit(1);
	}
	else
		end_fork_created(exec, cmd_index, cmd_count);
}

int	end_exec(t_exec_ctx *ctx, int exit_code, int status, int i)
{
	int	last_pid_status;
	int	had_real_pid;

	close_fd(ctx->exec, ctx->cmd_count);
	last_pid_status = 0;
	had_real_pid = 0;
	while (i < ctx->cmd_count)
	{
		if (ctx->exec->pid[i] > 0)
		{
			had_real_pid = 1;
			waitpid(ctx->exec->pid[i], &status, 0);
			if (i == ctx->cmd_count - 1)
				last_pid_status = status;
		}
		i++;
	}
	if (!had_real_pid)
	{
		if (ctx->exec->pid)
			free(ctx->exec->pid);
		return (ctx->data->error_code);
	}
	exit_code = end_exec_sig(ctx, exit_code, last_pid_status);
	return (exit_code);
}
