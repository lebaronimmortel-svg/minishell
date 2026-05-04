/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 21:32:10 by alexfuen          #+#    #+#             */
/*   Updated: 2026/05/04 21:32:17 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

void	ctx_init(t_exec_ctx *ctx, t_exec *exec, t_data *data, int cmd_count)
{
	ctx->exec = exec;
	ctx->data = data;
	ctx->cmd_index = 0;
	ctx->cmd_count = cmd_count;
}

int	get_next_index(char **split, int i, int *is_cmd)
{
	*is_cmd = 0;
	if (is_pipe(split[i]))
		return (i + 1);
	if (split[i][0] == '<' || split[i][0] == '>')
		return (skip_redirection(split, i));
	if (should_skip_empty(split, i) || is_redir_argument(split, i))
		return (i + 1);
	if ((split[i][0] == '\0' || ft_strcmp(split[i], " ") == 0)
		&& !has_redir_after_empty(split, i))
		return (i + 1);
	*is_cmd = 1;
	return (i + 1);
}

int	count_cmds(char **split, int i, int count)
{
	int	is_cmd;

	while (split && split[i])
	{
		i = get_next_index(split, i, &is_cmd);
		if (is_cmd)
			count++;
	}
	return (count);
}

void	check_exec(t_exec *exec)
{
	int	j;

	j = 0;
	while (j < exec->pipe_count)
	{
		if (exec->fd[j][0] != -1)
			close(exec->fd[j][0]);
		if (exec->fd[j][1] != -1)
			close(exec->fd[j][1]);
		j++;
	}
	j = 0;
	while (j < exec->redir_count)
	{
		if (exec->redir[j].fd >= 0)
			close(exec->redir[j].fd);
		j++;
	}
}

void	expand_heredoc(int expand, char *line, int *pipefd, char **envp)
{
	if (expand)
	{
		while (!are_var_hd(line))
			line = change_var_hd(line, envp);
		unmask_spaces(line);
	}
	write(pipefd[1], line, ft_strlen(line));
	write(pipefd[1], "\n", 1);
	free(line);
}
