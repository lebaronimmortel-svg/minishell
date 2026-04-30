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

static void	fill_input(char **command, int *i)
{
	int	j;

	j = 0;
	while (command[*i][j])
	{
		if (command[*i][j] == '\1')
			command[*i][j] = ' ';
		else if (command[*i][j] == '\3')
			command[*i][j] = '|';
		else if (command[*i][j] == '\4')
			command[*i][j] = '<';
		else if (command[*i][j] == '\5')
			command[*i][j] = '>';
		else if (command[*i][j] == '\6')
		{
			move_one(&command[*i][j]);
			continue ;
		}
		j++;
	}
	(*i)++;
}

static int	exec_init(t_exec *exec, int i)
{
	size_t	len;

	exec->all_path = NULL;
	exec->command = NULL;
	exec->w_path = NULL;
	exec->path = get_path(exec->data->env);
	len = ft_strlen(exec->input);
	if (len > 0 && exec->input[len - 1] == '\n')
		exec->input[len - 1] = '\0';
	exec->command = ft_split(exec->input, ' ');
	exec->all_path = ft_split(exec->path, ':');
	if (!exec->command || !exec->all_path || !exec->command[0])
		return (1);
	while (exec->command && exec->command[i])
		fill_input(exec->command, &i);
	return (0);
}

int	pipe_and_pid(t_exec *exec, int cmd_count, char **envp)
{
	exec->env = envp;
	if (pipe_and_pid_init(exec, cmd_count) == 1)
		return (1);
	return (0);
}

static int	setup_empty_cmd(t_exec *exec)
{
	exec->all_path = ft_calloc(1, sizeof(char *));
	exec->command = ft_calloc(2, sizeof(char *));
	if (!exec->all_path || !exec->command)
		return (1);
	exec->command[0] = ft_strdup("");
	if (!exec->command[0])
		return (1);
	exec->w_path = NULL;
	return (0);
}

int	exec_main_sequel(char **split, int *i, t_exec_ctx *ctx)
{
	t_exec	*exec;
	t_data	*data;
	int		status;

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
	{
		status = do_built_in_part(split, i, ctx);
		return (status);
	}
	if (!exec->input[0] && exec->redir_count > 0)
	{
		if (setup_empty_cmd(exec))
		{
			free_redir(exec);
			return (1);
		}
		return (0);
	}
	if (exec_init(exec, 0))
	{
		free_redir(exec);
		free_exec_cmd(exec);
		(*i)++;
		return (2);
	}
	return (0);
}

int	exec_main(char **split, int i, t_data *data, int cmd_count)
{
	t_exec		exec;
	t_exec_ctx	ctx;
	int			exit_code;

	ft_memset(&exec, 0, sizeof(t_exec));
	exec.data = data;
	exec.split = split;
	if (cmd_count == 0)
	{
		if (split && split[0] && ft_strchr(split[0], '\6'))
		{
			ft_putstr_fd("Command '' not found\n", 2);
			data->error_code = 127;
			return (127);
		}
		if (split && split[0] && (split[0][0] == '\0' || ft_strcmp(split[0], " ") == 0))
		{
			data->error_code = 0;
			return (0);
		}
		data->error_code = exec_cmd(&exec, data, split);
		free_redir(&exec);
		if (data->signal)          // <-- ajouter ici
    	{
        	data->signal = 0;
        	data->error_code = 130;
        	return (130);
    	}
		return (data->error_code);
	}
	if (pipe_and_pid(&exec, cmd_count, data->env) == 1)
		return (1);
	ctx_innit(&ctx, &exec, data, cmd_count);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	process_exec_loop(split, &i, &ctx);
	exit_code = end_exec(&ctx, 0, 0, 0);
	signal(SIGINT, handler0);
	signal(SIGQUIT, SIG_IGN);
	free_redir(&exec);
	return (exit_code);
}
