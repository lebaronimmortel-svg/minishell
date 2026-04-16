/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils_third.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 10:30:56 by lukrodri          #+#    #+#             */
/*   Updated: 2026/04/16 10:30:57 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

int	handle_input_redir(t_exec *exec, int i)
{
	int	fd;

	if (exec->redir[i].fd == -2)
		return (1);
	if (exec->redir[i].fd >= 0)
	{
		fd = exec->redir[i].fd;
		exec->redir[i].fd = -1;
	}
	else
	{
		fd = open(exec->redir[i].file, O_RDONLY);
		if (fd < 0)
		{
			perror(exec->redir[i].file);
			return (1);
		}
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (2);
}

int	handle_output_redir(t_exec *exec, int i)
{
	int	fd;

	fd = open(exec->redir[i].file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(exec->redir[i].file);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (2);
}
