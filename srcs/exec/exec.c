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

#include "../header/header.h"

static int	exec_init(t_exec *exec, char **envp)
{
	size_t	len;

	exec->all_path = NULL;
	exec->command = NULL;
	exec->w_path = NULL;
	exec->pid[0] = 0;
	exec->pid[1] = 0;
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
	if (!exec->command || !exec->all_path)
		return (1);
	return (0);
}

static int	find_env(t_exec *exec, int i)
{
	char	*tmp;

	if (exec->command && exec->command[0]
		&& access(exec->command[0], X_OK) == 0)
	{
		if (ft_strchr(exec->command[0], '/'))
			exec->w_path = ft_strdup(exec->command[0]);
		if (!exec->w_path)
			return (1);
		return (0);
	}
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
	return (0);
}

int	exec_command(t_exec *exec, int i)
{
	if (find_env(exec, 0) == 1)
		return (1);
	exec->pid[i] = fork();
	if (exec->pid[i] < 0)
	{
		execve_error("fork error", "");
		return (1);
	}
	if (exec->pid[i] == 0)
	{
		if (exec->w_path)
			execve(exec->w_path, exec->command, exec->env);
		execve_error("command not found : ", exec->command[0]);
	}
	free_split_exec(exec);
	return (0);
}

void	exec_main(char **envp, char **split)
{
	t_exec	exec;
	int		i;

	exec.input = split[0];
	i = 0;
	if (exec_init(&exec, envp) == 1 || exec_command(&exec, i) == 1)
	{
		free_split_exec(&exec);
		return ;
	}
	waitpid(exec.pid[i], NULL, 0);
}
