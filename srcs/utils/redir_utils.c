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

int g_ack = 0;

void	handle_sigint_son(int sig)
{
	g_ack = sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
}

void	free_son_heredoc(t_exec *exec, char *delim, int pipe_fd[2])
{
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	if (delim)
		free(delim);
	free_redir(exec);
	free_exec_cmd(exec);
	if (exec->pid)
		free(exec->pid);
	exit_cleanly(130, exec->data, exec->split);
}

static int	handle_hdoc_bis(t_exec *exec, char *delim, int expand, char **envp, int *pipefd)
{
	pid_t	pid;
	int		status;
	char	*line;

	pid = fork();
	if (pid == 0)
	{
		g_ack = 0;
		signal(SIGINT, handle_sigint_son);
		while (1)
		{
			line = readline("heredoc> ");
			if (g_ack == SIGINT)
			{
				if (line) free(line);
				free_son_heredoc(exec, delim, pipefd);
			}
			if (!line)
			{
				write(1, "minishell: warning: here-document delimited by end-of-file\n", 59);
				break ;
			}
			if (ft_strcmp(line, delim) == 0)
			{
				free(line);
				break ;
			}
			if (expand)
				while (!are_var_hd(line))
					line = change_var_hd(line, envp);
			write(pipefd[1], line, ft_strlen(line));
			write(pipefd[1], "\n", 1);
			free(line);
		}
		free_son_heredoc(exec, delim, pipefd);
	}
	close(pipefd[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, handler0);
	return (WEXITSTATUS(status));
}

int	handle_heredoc(t_exec *exec, char *delimiter, char **envp, int expand, int len)
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
	unmask_spaces(delim);
	if (pipe(pipefd) < 0)
	{
		free(delim);
		return (-1);
	}
	handle_hdoc_bis(exec, delim, expand, envp, pipefd);
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
