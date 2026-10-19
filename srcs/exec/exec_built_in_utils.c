/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <alexfuen@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 21:30:40 by alexfuen          #+#    #+#             */
/*   Updated: 2026/10/19 21:30:40 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

void	check_dir(t_exec *exec)
{
	struct stat	info;

	if (stat(exec->command[0], &info) != 0)
		return ;
	if (S_ISDIR(info.st_mode))
	{
		ft_putstr_fd(exec->command[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		free_exec_failed(exec, 126);
	}
}

int	find_env_loop(t_exec *exec, int i)
{
	char		*tmp;
	struct stat	info;

	tmp = NULL;
	while (exec->all_path && exec->all_path[i])
	{
		tmp = ft_strjoin(exec->all_path[i], "/");
		exec->w_path = ft_strjoin(tmp, exec->command[0]);
		free(tmp);
		if (exec->w_path && access(exec->w_path, X_OK) == 0)
		{
			if (stat(exec->w_path, &info) == 0 && S_ISDIR(info.st_mode))
			{
				free(exec->w_path);
				exec->w_path = NULL;
				i++;
				continue ;
			}
			return (0);
		}
		free(exec->w_path);
		exec->w_path = NULL;
		i++;
	}
	return (1);
}

void	close_fds_built_in(t_exec_ctx *ctx)
{
	if (ctx->cmd_index > 0 && ctx->exec->fd[ctx->cmd_index - 1][0] != -1)
	{
		close(ctx->exec->fd[ctx->cmd_index - 1][0]);
		ctx->exec->fd[ctx->cmd_index - 1][0] = -1;
	}
	if (ctx->cmd_index < ctx->cmd_count - 1
		&& ctx->exec->fd[ctx->cmd_index][1] != -1)
	{
		close(ctx->exec->fd[ctx->cmd_index][1]);
		ctx->exec->fd[ctx->cmd_index][1] = -1;
	}
	free_redir(ctx->exec);
}

void	dup_fds_built_in(t_exec_ctx *ctx)
{
	if (ctx->cmd_index > 0 && ctx->exec->fd[ctx->cmd_index - 1][0] != -1)
		dup2(ctx->exec->fd[ctx->cmd_index - 1][0], STDIN_FILENO);
	if (ctx->cmd_index < ctx->cmd_count - 1
		&& ctx->exec->fd[ctx->cmd_index][1] != -1)
		dup2(ctx->exec->fd[ctx->cmd_index][1], STDOUT_FILENO);
}

int	do_built_in_part(char **split, int *i, t_exec_ctx *ctx)
{
	int	saved_stdin;
	int	saved_stdout;
	int	status;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	dup_fds_built_in(ctx);
	status = 0;
	if (ctx->exec->redir_count > 0)
	{
		if (apply_redirs(ctx->exec) != 0)
			status = 1;
	}
	if (status == 0)
		status = exec_built_in(ctx->exec->input, ctx->data, split, *i);
	ctx->exec->env = ctx->data->env;
	if (ctx->cmd_count > 1)
		ctx->data->end = 0;
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	close_fds_built_in(ctx);
	(*i)++;
	return (status);
}
