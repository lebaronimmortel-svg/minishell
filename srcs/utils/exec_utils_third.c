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

int	find_env_loop(t_exec *exec, int i)
{
	char	*tmp;

	tmp = NULL;
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

void	do_built_in_part(t_exec *exec, t_data *data, char **split, int *i)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (exec->redir_count > 0)
		apply_redirs(exec);
	exec_built_in(exec->input, data, split);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	free_redir(exec);
	(*i)++;
}

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
	if (is_redir_argument(split, *i))
	{
		(*i)++;
		return (1);
	}
	return (0);
}

void	process_exec_loop(char **split, int *i, t_exec_ctx *ctx)
{
	while (split && split[*i])
	{
		if (should_skip_token(split, i))
			continue ;
		if (exec_main_sequel(split, i, ctx->exec, ctx->data))
			continue ;
		fork_and_free_exec(ctx->exec, &ctx->cmd_index, ctx->cmd_count);
		(*i)++;
	}
}
