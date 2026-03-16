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

#include "../header/header.h"

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
		exec->command[i] = NULL;
		i++;
	}
	free_var(exec);
}
