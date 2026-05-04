/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:12:06 by lukrodri          #+#    #+#             */
/*   Updated: 2026/04/14 14:12:07 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

void	free_exec_failed(t_exec *exec, int exit_code)
{
	free_split_exec(exec);
	if (exec->split)
		free(exec->split);
	if (exec->data)
		free(exec->data);
	if (exec->pid)
		free(exec->pid);
	exec->pid = NULL;
	exec->data = NULL;
	exec->split = NULL;
	exit(exit_code);
}

void	free_exec_cmd(t_exec *exec)
{
	int	i;

	i = 0;
	while (exec->all_path && exec->all_path[i])
		free(exec->all_path[i++]);
	free(exec->all_path);
	exec->all_path = NULL;
	i = 0;
	while (exec->command && exec->command[i])
		free(exec->command[i++]);
	free(exec->command);
	exec->command = NULL;
	if (exec->w_path)
		free(exec->w_path);
	exec->w_path = NULL;
	exec->input = NULL;
}

void	fork_and_free_exec(t_exec *exec, int *cmd_index, int cmd_count)
{
	fork_created(exec, *cmd_index, cmd_count);
	free_exec_cmd(exec);
	free_redir(exec);
	(*cmd_index)++;
}
