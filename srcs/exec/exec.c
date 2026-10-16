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
		if (command[*i][j] == '\1' || command[*i][j] == '\x1f')
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

int	exec_init(t_exec *exec, int i)
{
	size_t	len;
	char	*p;

	exec->all_path = NULL;
	exec->command = NULL;
	exec->w_path = NULL;
	exec->path = get_path(exec->data->env);
	len = ft_strlen(exec->input);
	if (len > 0 && exec->input[len - 1] == '\n')
		exec->input[len - 1] = '\0';
	p = exec->input;
	while (*p)
	{
		if (*p == '\x1f')
			*p = ' ';
		p++;
	}
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
	if (pipe_and_pid_init(exec, cmd_count, 0) == 1)
		return (1);
	return (0);
}

int	setup_empty_cmd(t_exec *exec)
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
		if (is_end_input(split, data) != 1)
			return (data->error_code);
		data->error_code = exec_cmd(&exec, data, split);
		free_redir(&exec);
		return (update_status(data));
	}
	if (pipe_and_pid(&exec, cmd_count, data->env) == 1)
		return (1);
	ctx_init(&ctx, &exec, data, cmd_count);
	set_signal_ign();
	process_exec_loop(split, &i, &ctx);
	exit_code = end_exec(&ctx, 0, 0, 0);
	set_signal_dfl();
	free_redir(&exec);
	return (exit_code);
}
