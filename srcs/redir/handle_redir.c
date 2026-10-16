/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 10:30:56 by lukrodri          #+#    #+#             */
/*   Updated: 2026/04/16 10:30:57 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

int	update_status(t_data *data)
{
	if (data->signal)
	{
		data->signal = 0;
		data->error_code = 130;
		return (130);
	}
	return (data->error_code);
}

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

void	append_to_cmd(char **split, int cmd_pos, char *extra)
{
	char	*tmp;
	char	*new;

	if (!extra || !extra[0])
		return ;
	if (split[cmd_pos] && split[cmd_pos][0])
	{
		tmp = ft_strjoin(split[cmd_pos], " ");
		if (!tmp)
			return ;
		new = ft_strjoin(tmp, extra);
		free(tmp);
	}
	else
		new = ft_strdup(extra);
	if (!new)
		return ;
	free(split[cmd_pos]);
	split[cmd_pos] = new;
}

void	handle_redir_sequel(t_exec *exec, char **split, int cmd_pos, int i)
{
	char	type;
	int		sp;
	char	*extra;

	type = 0;
	if (ft_strcmp(split[i], ">") == 0)
		type = 'r';
	else if (ft_strcmp(split[i], ">>") == 0)
		type = 'a';
	else if (ft_strcmp(split[i], "<") == 0)
		type = 's';
	else if (ft_strcmp(split[i], "<<") == 0)
		type = 'h';
	if (!type)
		return ;
	sp = space_pos(split[i + 1]);
	if (sp != -1)
	{
		extra = ft_strdup(&split[i + 1][sp + 1]);
		if (extra)
			append_to_cmd(split, cmd_pos, extra);
		free(extra);
	}
	end_redir_sequel(exec, split, i, type);
}
