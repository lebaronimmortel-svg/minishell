/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 11:02:16 by lukrodri          #+#    #+#             */
/*   Updated: 2026/03/05 11:02:17 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

int	count_cmds(char **split)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (split && split[i])
	{
		if (i % 2 == 0)
			count++;
		i++;
	}
	return (count);
}

static int	exec_init(t_exec *exec, char **envp)
{
	size_t	len;

	exec->all_path = NULL;
	exec->command = NULL;
	exec->w_path = NULL;
	exec->env = envp;
	exec->path = getenv("PATH");
	if (!exec->path)
		exec->path
			= "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	len = ft_strlen(exec->input);
	if (len > 0 && exec->input[len - 1] == '\n')
		exec->input[len - 1] = '\0';
	exec->command = ft_split(exec->input, ' ');
	exec->all_path = ft_split(exec->path, ':');
	if (!exec->command || !exec->all_path || !exec->command[0])
		return (1);
	return (0);
}

int	pipe_and_pid(t_exec *exec, int cmd_count)
{
	int	i;

	exec->pid = NULL;
	exec->pid = malloc(sizeof(pid_t) * cmd_count);
	if (!exec->pid)
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

static void	fork_and_free_exec(t_exec *exec, int cmd_index, int cmd_count)
{
	fork_created(exec, cmd_index, cmd_count);
	free_split_exec(exec);
	free_redir(exec);
}

int	exec_main(char **envp, char **split, int i, int cmd_index)
{
	t_exec	exec;
	int		cmd_count;
	int		status;
	int		exit_code;

	cmd_count = count_cmds(split);
	if (pipe_and_pid(&exec, cmd_count) == 1)
		return (1);
	while (split && split[i])
	{
		if (i % 2 == 0)
		{
			exec.input = split[i];
			collect_redirs(&exec, split, i, 0);
			if (exec_init(&exec, envp))
			{
				free_split_exec(&exec);
				i++;
				continue ;
			}
			fork_and_free_exec(&exec, cmd_index, cmd_count);
			cmd_index++;
		}
		i++;
	}
	waitpid(exec.pid[0], &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = 128 + WTERMSIG(status);
	else
		exit_code = 1;
	return (exit_code);
	//end_exec(&exec, cmd_count);
}
