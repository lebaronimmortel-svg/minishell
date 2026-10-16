/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:44:09 by lukrodri          #+#    #+#             */
/*   Updated: 2026/04/02 11:44:10 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

int	init_fds(t_exec *exec, int *i)
{
	exec->fd[*i] = malloc(sizeof(int) * 2);
	if (!exec->fd[*i])
	{
		while (--(*i) >= 0)
			free(exec->fd[*i]);
		free(exec->fd);
		exec->fd = NULL;
		free(exec->pid);
		exec->pid = NULL;
		return (1);
	}
	exec->fd[*i][0] = -1;
	exec->fd[*i][1] = -1;
	(*i)++;
	return (0);
}

int	pipe_and_pid_init(t_exec *exec, int cmd_count, int i)
{
	int	pipe_count;

	exec->pid = NULL;
	exec->fd = NULL;
	exec->pipe_count = 0;
	exec->pid = malloc(sizeof(pid_t) * cmd_count);
	if (!exec->pid)
		return (1);
	while (i < cmd_count)
		exec->pid[i++] = -1;
	pipe_count = cmd_count - 1;
	if (pipe_count <= 0)
		return (0);
	exec->fd = malloc(sizeof(int *) * pipe_count);
	if (!exec->fd)
		free(exec->pid);
	if (!exec->fd)
		return (1);
	i = 0;
	while (i < pipe_count)
		if (init_fds(exec, &i))
			return (1);
	exec->pipe_count = pipe_count;
	return (0);
}

int	count_redirs(char **split, int cmd_pos)
{
	int	i;
	int	count;

	count = 0;
	if (cmd_pos >= 1 && split[cmd_pos - 1]
		&& (split[cmd_pos - 1][0] == '<' || split[cmd_pos - 1][0] == '>'))
		count++;
	i = cmd_pos + 1;
	while (split[i] && split[i + 1])
	{
		if (split[i][0] == '|')
			break ;
		if (split[i][0] == '>' || split[i][0] == '<')
			count++;
		i += 2;
	}
	return (count);
}

int	init_redirs(t_exec *exec, int count)
{
	int	i;

	exec->redir = malloc(sizeof(t_redir) * count);
	if (!exec->redir)
		return (0);
	i = 0;
	while (i < count)
	{
		exec->redir[i].fd = -1;
		i++;
	}
	return (1);
}

void	infile_redir(char **split, int *i, int check)
{
	int	z;
	int	j;

	j = 0;
	while (split[*i] && split[*i][j])
	{
		if (split[*i][j] == ' ')
		{
			check = 1;
			break ;
		}
		j++;
	}
	if (check == 0)
	{
		split[*i][0] = 0;
		return ;
	}
	z = 0;
	while (split[*i] && split[*i][j + z])
	{
		split[*i][z] = split[*i][j + 1 + z];
		z++;
	}
}
