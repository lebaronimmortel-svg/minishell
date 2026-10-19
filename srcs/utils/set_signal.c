/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <alexfuen@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 21:30:40 by alexfuen          #+#    #+#             */
/*   Updated: 2026/10/19 21:30:40 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

static void	retrieve_result(int *result, t_exec *exec, int *i)
{
	*result = retrieve_status(exec, i);
	if (*result == 1 || *result == 2)
		free_redir(exec);
}

int	exec_main_sequel(char **split, int *i, t_exec_ctx *ctx)
{
	t_exec	*exec;
	t_data	*data;
	int		status;
	int		result;

	exec = ctx->exec;
	data = ctx->data;
	exec->redir_count = 0;
	exec->redir = NULL;
	collect_redirs(exec, split, *i, exec->env);
	if (data->signal)
	{
		free_redir(exec);
		(*i)++;
		return (1);
	}
	if (*i >= 1 && (split[(*i) - 1][0] == '<' || split[(*i) - 1][0] == '>'))
		infile_redir(split, i, 0);
	exec->input = split[*i];
	if (is_built_in(exec->input))
		status = do_built_in_part(split, i, ctx);
	if (is_built_in(exec->input))
		return (status);
	retrieve_result(&result, exec, i);
	return (result);
}

int	is_end_input(char **split, t_data *data)
{
	if (split && split[0] && ft_strchr(split[0], '\6'))
	{
		ft_putstr_fd("Command '' not found\n", 2);
		data->error_code = 127;
		return (127);
	}
	if (split && split[0] && (split[0][0] == '\0'
		|| ft_strcmp(split[0], " ") == 0))
	{
		data->error_code = 0;
		return (0);
	}
	return (1);
}

void	set_signal_ign(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_dfl(void)
{
	signal(SIGINT, handler0);
	signal(SIGQUIT, SIG_IGN);
}
