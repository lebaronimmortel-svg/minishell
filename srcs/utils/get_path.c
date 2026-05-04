/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 09:25:11 by lukrodri          #+#    #+#             */
/*   Updated: 2026/04/27 09:25:14 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

void	close_exec_fds(t_exec_ctx *ctx, int ret)
{
	if (ret == 2 && !ctx->data->end)
		ctx->data->error_code = 127;
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
}

int	handle_exec_result(int ret, int built_in, t_exec_ctx *ctx)
{
	if (!ctx->data->signal)
	{
		ctx->data->error_code = ret;
	}
	if (built_in)
	{
		process_built_in(ctx);
		return (1);
	}
	if (ret == 1 || (ret == 2 && !ctx->data->end))
	{
		close_exec_fds(ctx, ret);
		ctx->cmd_index++;
		return (1);
	}
	return (0);
}

void	process_built_in(t_exec_ctx *ctx)
{
	ctx->cmd_index++;
	free_exec_cmd(ctx->exec);
	free_redir(ctx->exec);
}

int	end_exec_sig(t_exec_ctx *ctx, int exit_code, int last_pid_status)
{
	free_fd(ctx->exec);
	if (ctx->exec->pid)
		free(ctx->exec->pid);
	if (ctx->data->end)
		return (ctx->data->error_code);
	if (WIFEXITED(last_pid_status))
		exit_code = WEXITSTATUS(last_pid_status);
	else if (WIFSIGNALED(last_pid_status))
		exit_code = 128 + WTERMSIG(last_pid_status);
	else
		exit_code = ctx->data->error_code;
	ctx->data->error_code = exit_code;
	return (exit_code);
}

char	*get_path(char **env)
{
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	while (env[i])
	{
		if (!ft_strncmp("PATH=", env[i], 5))
		{
			result = &env[i][5];
			if (!result)
				return (NULL);
			return (result);
		}
		i++;
	}
	return (NULL);
}
