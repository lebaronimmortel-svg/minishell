/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 08:31:09 by lukrodri          #+#    #+#             */
/*   Updated: 2026/03/16 08:31:10 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

void	execve_error(char *str, char *command)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd("\n", 2);
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
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup_exec_fds(exec, cmd_index, cmd_count);
		exit(1);
	}
	else
		end_fork_created(exec, cmd_index, cmd_count);
}

int	wait_son_status(int *had_real_pid, t_exec_ctx *ctx, int i, int *status)
{
	int	last_pid_status;

	last_pid_status = 0;
	*had_real_pid = 1;
	waitpid(ctx->exec->pid[i], status, 0);
	if (i == ctx->cmd_count - 1)
		last_pid_status = *status;
	return (last_pid_status);
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
			last_pid_status = wait_son_status(&had_real_pid, ctx, i, &status);
		i++;
	}
	if (!had_real_pid)
	{
		free_fd(ctx->exec);
		if (ctx->exec->pid)
			free(ctx->exec->pid);
		ctx->data->signal = 0;
		return (ctx->data->error_code);
	}
	exit_code = end_exec_sig(ctx, exit_code, last_pid_status);
	return (exit_code);
}

int	handle_hdoc_bis(t_exec *exec, char *delim,
						char **envp, int *pipefd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free(delim);
		close(pipefd[1]);
		return (1);
	}
	if (pid == 0)
		child_heredoc(exec, delim, envp, pipefd);
	wait_son(pipefd, &status, exec, pid);
	return (WEXITSTATUS(status));
}
