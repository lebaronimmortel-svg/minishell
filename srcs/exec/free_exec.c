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
	if (exec->data->env)
	{
		free_split(exec->data->env, 0);
		exec->data->env = NULL;
	}
	if (exec->data->env_bis)
	{
		free_split(exec->data->env_bis, 0);
		exec->data->env_bis = NULL;
	}
}

void	fork_and_free_exec(t_exec *exec, int *cmd_index, int cmd_count)
{
	fork_created(exec, *cmd_index, cmd_count);
	free_split_exec(exec);
	free_data_split(exec);
	(*cmd_index)++;
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
	free_data_split(exec);
	free_var(exec);
}
