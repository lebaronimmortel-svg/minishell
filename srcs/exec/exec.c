/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 11:02:16 by lukrodri          #+#    #+#             */
/*   Updated: 2026/04/09 02:44:52 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

static int	exec_init(t_exec *exec, int i, int j)
{
	size_t	len;

	exec->all_path = NULL;
	exec->command = NULL;
	exec->w_path = NULL;
	exec->path = getenv("PATH");
	len = ft_strlen(exec->input);
	if (len > 0 && exec->input[len - 1] == '\n')
		exec->input[len - 1] = '\0';
	exec->command = ft_split(exec->input, ' ');
	exec->all_path = ft_split(exec->path, ':');
	if (!exec->command || !exec->all_path || !exec->command[0])
		return (1);
	while (exec->command && exec->command[i])
	{
		j = 0;
		while (exec->command[i][j])
		{
			if (exec->command[i][j] == '\1')
				exec->command[i][j] = ' ';
			j++;
		}
		i++;
	}
	return (0);
}

int	pipe_and_pid(t_exec *exec, int cmd_count, char **envp)
{
	int	i;

	exec->env = envp;
	if (pipe_and_pid_init(exec, cmd_count) == 1)
		return (1);
	i = 0;
	while (i < cmd_count - 1)
	{
		if (pipe(exec->fd[i]) == -1)
		{
			i--;
			while (i >= 0)
			{
				close(exec->fd[i][0]);
				close(exec->fd[i][1]);
				i--;
			}
			free(exec->pid);
			exec->pid = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

int	exec_main_sequel(char **split, int *i, t_exec_ctx *ctx)
{
	t_exec	*exec;
	t_data	*data;

	exec = ctx->exec;
	data = ctx->data;
	exec->redir_count = 0;
	exec->redir = NULL;
	collect_redirs(exec, split, *i, exec->env);
	if (*i >= 1 && (split[(*i) - 1][0] == '<' || split[(*i) - 1][0] == '>'))
		infile_redir(split, i, 0);
	exec->input = split[*i];
	if (is_built_in(exec->input))
	{
		do_built_in_part(split, i, ctx);
		return (1);
	}
	if (exec_init(exec, 0, 0))
	{
		free_redir(exec);
		free_exec_cmd(exec);
		(*i)++;
		return (2);
	}
	return (0);
}

int	exec_main(char **split, int i, t_data *data)
{
	t_exec		exec;
	t_exec_ctx	ctx;
	int			cmd_count;
	int			exit_code;

	exec.redir = NULL;
	exec.data = data;
	exec.split = split;
	cmd_count = count_cmds(split, 0, 0);
	if (cmd_count == 0)
		return (0);
	if (pipe_and_pid(&exec, cmd_count, data->env) == 1)
		return (1);
	ctx.exec = &exec;
	ctx.data = data;
	ctx.cmd_index = 0;
	ctx.cmd_count = cmd_count;
	process_exec_loop(split, &i, &ctx);
	exit_code = end_exec(&ctx, 0, 0);
	free_redir(&exec);
	return (exit_code);
}
