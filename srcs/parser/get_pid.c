/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <alexfuen@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 21:30:40 by alexfuen          #+#    #+#             */
/*   Updated: 2026/10/19 21:30:40 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

int	retrieve_status(t_exec *exec, int *i)
{
	if (!exec->input[0] && exec->redir_count > 0)
	{
		if (setup_empty_cmd(exec))
		{
			free_redir(exec);
			return (1);
		}
		return (0);
	}
	if (exec_init(exec, 0))
	{
		free_redir(exec);
		free_exec_cmd(exec);
		(*i)++;
		return (2);
	}
	return (0);
}

void	end_collect_redir(t_exec *exec, char **envp)
{
	int	k;

	k = 0;
	while (k < exec->redir_count)
	{
		if (exec->redir[k].type == 'h' && exec->redir[k].fd == -1)
			exec->redir[k].fd = handle_heredoc(exec, exec->redir[k].file,
					envp);
		k++;
	}
}

char	*my_get_pid(void)
{
	char	**split;
	char	*result;
	int		fd;
	char	buf[1024];
	int		bytes;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
		return (NULL);
	bytes = read(fd, buf, sizeof(buf));
	close(fd);
	buf[bytes] = '\0';
	split = ft_split(buf, ' ');
	if (!split)
		return (NULL);
	result = ft_strdup(split[0]);
	if (!result)
		return (NULL);
	free_split(split, 0);
	return (result);
}

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

void	close_fd(t_exec *exec, int cmd_count)
{
	int	j;

	(void)cmd_count;
	if (!exec->fd)
		return ;
	j = 0;
	while (j < exec->pipe_count)
	{
		if (exec->fd[j][0] != -1)
		{
			close(exec->fd[j][0]);
			exec->fd[j][0] = -1;
		}
		if (exec->fd[j][1] != -1)
		{
			close(exec->fd[j][1]);
			exec->fd[j][1] = -1;
		}
		j++;
	}
}
