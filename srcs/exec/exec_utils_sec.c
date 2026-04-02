/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_sec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 10:01:31 by lukrodri          #+#    #+#             */
/*   Updated: 2026/04/02 10:01:32 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

int	pipe_and_pid_init(t_exec *exec, int cmd_count)
{
	int	i;

	exec->pid = NULL;
	exec->pid = malloc(sizeof(pid_t) * cmd_count);
	if (!exec->pid)
		return (1);
	i = 0;
	while (i < cmd_count)
		exec->pid[i++] = -1;
	return (0);
}

int	count_cmds(char **split)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (split && split[i])
	{
		if (i % 2 == 0 && split[i][0] != 0)
			count++;
		i++;
	}
	return (count);
}

void	infile_redir(char **split, int *i)
{
	int	z;
	int	j;

	j = 0;
	while (split[*i] && split[*i][j] && split[*i][j] != ' ')
		j++;
	z = 0;
	while (split[*i] && split[*i][j + z])
	{
		split[*i][z] = split[*i][j + 1 + z];
		z++;
	}
}
