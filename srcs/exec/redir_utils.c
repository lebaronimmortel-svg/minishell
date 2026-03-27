/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 08:14:41 by lukrodri          #+#    #+#             */
/*   Updated: 2026/03/26 08:14:42 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

int	space_pos(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == ' ')
			return (i);
		i++;
	}
	return (-1);
}

static int	handle_heredoc(char *delimiter)
	{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) < 0)
		return (-1);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

int	first_part_apply_redir(char type, t_exec *exec, int i, int fd)
{
	if (type == 's')
	{
		fd = open(exec->redir[i].file, O_RDONLY);
		if (fd < 0)
		{
			perror(exec->redir[i].file);
			return (1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
		return (2);
	}
	else if (type == 'r')
	{
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
	return (0);
}

int	second_part_apply_redir(char type, t_exec *exec, int i)
{
	int	fd;

	if (type == 'a')
	{
		fd = open(exec->redir[i].file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			perror(exec->redir[i].file);
			return (1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (type == 'h')
	{
		fd = handle_heredoc(exec->redir[i].file);
		if (fd < 0)
			return (1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}
