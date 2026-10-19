/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <alexfuen@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 21:30:40 by alexfuen          #+#    #+#             */
/*   Updated: 2026/10/19 21:30:40 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

void	handle_sigint_son(int sig)
{
	g_ack = sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
}

void	free_son_heredoc(t_exec *exec, char *delim, int pipe_fd[2], int code)
{
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	if (delim)
		free(delim);
	free_redir(exec);
	free_exec_cmd(exec);
	free_fd(exec);
	if (exec->pid)
		free(exec->pid);
	exit_cleanly(code, exec->data, exec->split);
}

void	wait_son(int *pipefd, int *status, t_exec *exec, pid_t pid)
{
	close(pipefd[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, status, 0);
	signal(SIGINT, handler0);
	if (*status)
		exec->data->signal = 1;
}

char	*get_line_heredoc(t_exec *exec, char *delim, int *pipefd)
{
	char	*line;

	line = readline("heredoc> ");
	if (g_ack == SIGINT)
	{
		if (line)
			free(line);
		free_son_heredoc(exec, delim, pipefd, 130);
	}
	return (line);
}

int	handle_heredoc_end(int *normal_exit, char *line, char *delim)
{
	if (!line)
	{
		ft_putstr_fd("minishell: warning: here-document delimited"
			" by end-of-file\n", 2);
		*normal_exit = 1;
		return (1);
	}
	if (ft_strcmp(line, delim) == 0)
	{
		free(line);
		*normal_exit = 1;
		return (1);
	}
	return (0);
}
