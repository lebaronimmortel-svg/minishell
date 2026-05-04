/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 09:07:45 by lukrodri          #+#    #+#             */
/*   Updated: 2026/04/11 09:07:46 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

int	skip_token1(char **split, int *i)
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
	return (0);
}

int	skip_token2(char **split, int *i)
{
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

int	should_skip_token(char **split, int *i)
{
	if (skip_token1(split, i))
		return (1);
	if (skip_token2(split, i))
		return (1);
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
