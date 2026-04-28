/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_third.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 09:07:45 by lukrodri          #+#    #+#             */
/*   Updated: 2026/04/11 09:07:46 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

void	check_dir(t_exec *exec)
{
	struct stat	info;

	stat(exec->command[0], &info);
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

int	do_built_in_part(char **split, int *i, t_exec_ctx *ctx)
{
	int	saved_stdin;
	int	saved_stdout;
	int	status;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (ctx->cmd_index > 0 && ctx->exec->fd[ctx->cmd_index - 1][0] != -1)
		dup2(ctx->exec->fd[ctx->cmd_index - 1][0], STDIN_FILENO);
	if (ctx->cmd_index < ctx->cmd_count - 1 && ctx->exec->fd[ctx->cmd_index][1] != -1)
		dup2(ctx->exec->fd[ctx->cmd_index][1], STDOUT_FILENO);
	status = 0;
	if (ctx->exec->redir_count > 0)
	{
		if (apply_redirs(ctx->exec) != 0)
			status = 1;
	}
	if (status == 0)
		status = exec_built_in(ctx->exec->input, ctx->data, split, *i);
	ctx->exec->env = ctx->data->env;
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	if (ctx->cmd_index > 0 && ctx->exec->fd[ctx->cmd_index - 1][0] != -1)
	{
		close(ctx->exec->fd[ctx->cmd_index - 1][0]);
		ctx->exec->fd[ctx->cmd_index - 1][0] = -1;
	}
	if (ctx->cmd_index < ctx->cmd_count - 1 && ctx->exec->fd[ctx->cmd_index][1] != -1)
	{
		close(ctx->exec->fd[ctx->cmd_index][1]);
		ctx->exec->fd[ctx->cmd_index][1] = -1;
	}
	free_redir(ctx->exec);
	(*i)++;
	return (status);
}

/*
** Returns 1 and advances *i when the current token should be skipped by
** the execution loop.  An empty slot is only skipped when it has NO
** redirect operators following it before the next pipe; if it does own
** redirects it must be executed as an anonymous subshell (e.g. "< f | wc").
*/
int	should_skip_token(char **split, int *i)
{
	if (is_pipe(split[*i]))
	{
		(*i)++;
		return (1);
	}
	if (split[*i][0] == '<' || split[*i][0] == '>')
	{
		*i = skip_redirection(split, *i);
		return (1);
	}
	if (should_skip_empty(split, *i))
	{
		(*i)++;
		return (1);
	}
	if (split[*i][0] == '\0' && !has_redir_after_empty(split, *i))
	{
		(*i)++;
		return (1);
	}
	if (ft_strcmp(split[*i], " ") == 0 && !has_redir_after_empty(split, *i))
	{
		(*i)++;
		return (1);
	}
	if (is_redir_argument(split, *i))
	{
		(*i)++;
		return (1);
	}
	return (0);
}

void	process_exec_loop(char **split, int *i, t_exec_ctx *ctx)
{
	int	ret;
	int	built_in;

	while (split && split[*i])
	{
		if (should_skip_token(split, i))
			continue ;
			
		if (ctx->cmd_index < ctx->cmd_count - 1)
		{
			if (pipe(ctx->exec->fd[ctx->cmd_index]) == -1)
			{
				perror("pipe");
				ctx->data->error_code = 1;
				break ;
			}
		}

		built_in = is_built_in(split[*i]);
		ret = exec_main_sequel(split, i, ctx);
		if (handle_exec_result(ret, built_in, ctx))
			continue ;
		fork_and_free_exec(ctx->exec, &ctx->cmd_index, ctx->cmd_count);
		(*i)++;
	}
}
