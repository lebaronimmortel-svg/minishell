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
	if (access(exec->command[0], X_OK) == 0)
	{
		exec->w_path = ft_strdup(exec->command[0]);
		if (!exec->w_path)
			return (1);
		return (0);
	}
	if (exec->command[0][0] == '/')
	{
		exec->w_path = NULL;
		return (1);
	}
	if (find_env_loop(exec, i) == 0)
		return (0);
	return (1);
}

static int	exec_command(t_exec *exec)
{
	if (!exec->command || !exec->command[0] || exec->command[0][0] == '\0')
		exit(0);
	if (find_env(exec, 0) == 1)
	{
		if (ft_strchr(exec->command[0], '/'))
			execve_error(exec->command[0], ": No such file or directory");
		else
			execve_error(exec->command[0], ": command not found");
		free_exec_failed(exec);
		exit(127);
	}
	if (exec->w_path)
	{
		free_data_split(exec);
		execve(exec->w_path, exec->command, exec->env);
		perror(exec->command[0]);
		free_split_exec(exec);
		if (exec->pid)
			free(exec->pid);
		exit(126);
	}
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

int	end_exec(t_exec_ctx *ctx, int exit_code, int status)
{
	int		i;
	int		last_builtin;

	last_builtin = (ctx->exec->pid[ctx->cmd_count - 1] <= 0);
	close_fd(ctx->exec, ctx->cmd_count);
	i = 0;
	while (i < ctx->cmd_count)
	{
		if (ctx->exec->pid[i] > 0)
			waitpid(ctx->exec->pid[i], &status, 0);
		i++;
	}
	if (ctx->exec->pid)
		free(ctx->exec->pid);
	if (last_builtin)
		return (ctx->data->error_code);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = 128 + WTERMSIG(status);
	else
		exit_code = 1;
	ctx->data->error_code = exit_code;
	return (exit_code);
}
