/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 08:37:42 by lukrodri          #+#    #+#             */
/*   Updated: 2026/03/09 08:37:44 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

void	free_fd(t_exec *exec)
{
	int	i;

	if (!exec->fd)
		return ;
	i = 0;
	while (i < exec->pipe_count)
	{
		if (exec->fd[i])
			free(exec->fd[i]);
		i++;
	}
	free(exec->fd);
	exec->fd = NULL;
	exec->pipe_count = 0;
}

void	free_data_split(t_exec *exec)
{
	int	i;

	i = 0;
	if (!exec->data)
		return ;
	while (exec->split && exec->split[i])
	{
		free(exec->split[i]);
		exec->split[i] = NULL;
		i++;
	}
	free(exec->split);
	exec->split = NULL;
	if (exec->data->env_bis)
	{
		free_split(exec->data->env_bis, 0);
		exec->data->env_bis = NULL;
	}
}

void	free_redir(t_exec *exec)
{
	int	i;

	if (!exec->redir)
		return ;
	i = 0;
	while (i < exec->redir_count)
	{
		if (exec->redir[i].malloced && exec->redir[i].file)
			free(exec->redir[i].file);
		if (exec->redir[i].fd >= 0)
			close(exec->redir[i].fd);
		i++;
	}
	if (exec->redir)
		free(exec->redir);
	exec->redir = NULL;
	exec->redir_count = 0;
}

static void	free_var(t_exec *exec)
{
	if (exec->all_path)
		free(exec->all_path);
	if (exec->command)
		free(exec->command);
	if (exec->w_path)
		free(exec->w_path);
	exec->w_path = NULL;
	exec->all_path = NULL;
	exec->command = NULL;
	exec->input = NULL;
}

void	free_split_exec(t_exec *exec)
{
	int	i;

	i = 0;
	while (exec->all_path && exec->all_path[i])
	{
		free(exec->all_path[i]);
		i++;
	}
	i = 0;
	while (exec->command && exec->command[i])
	{
		free(exec->command[i]);
		i++;
	}
	if (exec->data->env)
	{
		free_split(exec->data->env, 0);
		exec->data->env = NULL;
	}
	free_data_split(exec);
	free_fd(exec);
	free_var(exec);
}
