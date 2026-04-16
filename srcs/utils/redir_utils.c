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

static void	handle_hdoc_bis(char *delim, int expand, char **envp, int *pipefd)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line || ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		if (expand)
		{
			while (!are_var_hd(line))
				line = change_var_hd(line, envp);
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
}

int	handle_heredoc(char *delimiter, char **envp, int expand, int len)
{
	int		pipefd[2];
	char	*delim;

	if (delimiter[0] == 34 || delimiter[0] == 39)
	{
		len = ft_strlen(delimiter);
		delim = ft_substr(delimiter, 1, len - 2);
		if (!delim)
			return (-1);
		expand = 0;
	}
	else
		delim = ft_strdup(delimiter);
	if (!delim)
		return (-1);
	if (pipe(pipefd) < 0)
	{
		free(delim);
		return (-1);
	}
	handle_hdoc_bis(delim, expand, envp, pipefd);
	free(delim);
	close(pipefd[1]);
	return (pipefd[0]);
}

int	first_part_apply_redir(char type, t_exec *exec, int i, int fd)
{
	(void)fd;
	if (type == 's')
		return (handle_input_redir(exec, i));
	if (type == 'r')
		return (handle_output_redir(exec, i));
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
		fd = exec->redir[i].fd;
		if (fd < 0)
			return (1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

int	apply_redirs(t_exec *exec)
{
	int		i;
	int		result;
	char	type;

	if (!exec->redir || exec->redir_count == 0)
		return (0);
	i = 0;
	while (i < exec->redir_count)
	{
		type = exec->redir[i].type;
		result = first_part_apply_redir(type, exec, i, 0);
		if (result == 1)
			return (1);
		if (result != 2)
			if (second_part_apply_redir(type, exec, i) == 1)
				return (1);
		i++;
	}
	return (0);
}
