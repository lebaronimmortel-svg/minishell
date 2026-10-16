/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 08:48:18 by lukrodri          #+#    #+#             */
/*   Updated: 2026/03/20 08:48:19 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

int	check_access(t_exec *exec)
{
	struct stat	info;

	if (access(exec->command[0], X_OK) == 0
		&& stat(exec->command[0], &info) == 0
		&& S_ISREG(info.st_mode))
	{
		exec->w_path = ft_strdup(exec->command[0]);
		if (exec->w_path)
			return (0);
	}
	return (1);
}

int	find_env(t_exec *exec, int i)
{
	if (!exec->command || !exec->command[0])
		return (1);
	if (access(exec->command[0], X_OK) == 0 && ft_strchr(exec->command[0], '/'))
	{
		check_dir(exec);
		exec->w_path = ft_strdup(exec->command[0]);
		if (!exec->w_path)
			return (1);
		return (0);
	}
	if (exec->command[0][0] == '/' || exec->command[0][0] == '.')
	{
		if (exec->command[0][0] == '/')
			check_dir(exec);
		exec->w_path = NULL;
		return (1);
	}
	if (find_env_loop(exec, i) == 0)
		return (0);
	if (!check_access(exec))
		return (0);
	return (1);
}

int	get_path_error(char *path)
{
	int		i;
	char	c;

	i = 0;
	while (path[i])
	{
		while (path[i] == '/')
			i++;
		while (path[i] && path[i] != '/')
			i++;
		if (i == 0)
			break ;
		c = path[i];
		path[i] = '\0';
		if (access(path, F_OK) != 0)
			path[i] = c;
		if (access(path, F_OK) != 0)
			return (127);
		if (access(path, X_OK) != 0)
			path[i] = c;
		if (access(path, X_OK) != 0)
			return (126);
		path[i] = c;
	}
	return (127);
}

void	dup_exec_fds(t_exec *exec, int cmd_index, int cmd_count)
{
	if (cmd_index > 0)
		dup2(exec->fd[cmd_index - 1][0], STDIN_FILENO);
	if (cmd_index < cmd_count - 1)
		dup2(exec->fd[cmd_index][1], STDOUT_FILENO);
	close_fd(exec, cmd_count);
	if (apply_redirs(exec) != 0)
	{
		free_redir(exec);
		free_exec_failed(exec, 1);
	}
	exec_command(exec);
	free_split_exec(exec);
}
