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
	if (exec->pid)
		free(exec->pid);
	exit_cleanly(code, exec->data, exec->split);
}

void	fonction_hfc(t_exec *exec)
{
	int	j;

	j = 0;
	while (j < exec->pipe_count)
	{
		if (exec->fd[j][0] != -1)
			close(exec->fd[j][0]);
		if (exec->fd[j][1] != -1)
			close(exec->fd[j][1]);
		j++;
	}
	j = 0;
	while (j < exec->redir_count)
	{
		if (exec->redir[j].fd >= 0)
			close(exec->redir[j].fd);
		j++;
	}
}

void	fonction_mfc(int expand, char *line, int *pipefd, char **envp)
{
	if (expand)
	{
		while (!are_var_hd(line))
			line = change_var_hd(line, envp);
		unmask_spaces(line);
	}
	write(pipefd[1], line, ft_strlen(line));
	write(pipefd[1], "\n", 1);
	free(line);
}

void	fonction33(int *pipefd, int *status, t_exec *exec, pid_t pid)
{
	close(pipefd[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, status, 0);
	signal(SIGINT, handler0);
	if (*status)
		exec->data->signal = 1;
}

char	*fonction_abcdef(t_exec *exec, char *delim, int *pipefd)
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

int	fonction_kfc(int *normal_exit, char *line, char *delim)
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

static int	handle_hdoc_bis(t_exec *exec, char *delim, int expand,
							char **envp, int *pipefd)
{
	pid_t	pid;
	int		status;
	char	*line;
	int		normal_exit;

	normal_exit = 0;
	pid = fork();
	if (pid == 0)
	{
		fonction_hfc(exec);
		g_ack = 0;
		signal(SIGINT, handle_sigint_son);
		while (1)
		{
			line = fonction_abcdef(exec, delim, pipefd);
			if (fonction_kfc(&normal_exit, line, delim))
				break ;
			fonction_mfc(expand, line, pipefd, envp);
		}
		free_son_heredoc(exec, delim, pipefd, 0);
	}
	fonction33(pipefd, &status, exec, pid);
	return (WEXITSTATUS(status));
}

void	fonction2008(t_exec *exec, char *delim, int expand, char **envp, int *pipefd)
{
	int	ret;

	ret = handle_hdoc_bis(exec, delim, expand, envp, pipefd);
	if (ret)
		exec->data->error_code = ret;
	free(delim);
	close(pipefd[1]);
}

int	handle_heredoc(t_exec *exec, char *delimiter, char **envp, int expand)
{
	int		pipefd[2];
	char	*delim;
	int		len;

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
	fonction2008(exec, delim, expand, envp, pipefd);
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
