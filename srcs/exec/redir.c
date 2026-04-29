/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 09:53:50 by lukrodri          #+#    #+#             */
/*   Updated: 2026/04/16 10:53:50 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

void	end_redir_sequel(t_exec *exec, char **split, int i, char type)
{
	char	*file;
	int		sp;

	exec->redir[exec->redir_count].type = type;
	sp = space_pos(split[i + 1]);
	if (sp != -1)
		file = ft_substr(split[i + 1], 0, sp);
	else
		file = ft_strdup(split[i + 1]);
	if (!file)
		return ;
	unmask_spaces(file);
	exec->redir[exec->redir_count].file = file;
	exec->redir[exec->redir_count].malloced = 1;
	exec->redir_count++;
}

static void	end_pre_redir(t_exec *exec, char type)
{
	exec->redir[exec->redir_count].type = type;
	exec->redir[exec->redir_count].malloced = 1;
	exec->redir_count++;
}

void	collect_redirs_sequel(t_exec *exec, char **split,
								int cmd_pos, int i)
{
	i = cmd_pos + 1;
	while (split[i] && split[i + 1])
	{
		if (split[i][0] == '|')
			break ;
		handle_redir_sequel(exec, split, cmd_pos, i);
		i += 2;
	}
}

static void	collect_pre_redir(t_exec *exec, char **split, int cmd_pos)
{
	char	type;
	int		sp;

	if (cmd_pos < 1)
		return ;
	type = 0;
	if (ft_strcmp(split[cmd_pos - 1], "<") == 0)
		type = 's';
	else if (ft_strcmp(split[cmd_pos - 1], "<<") == 0)
		type = 'h';
	else if (ft_strcmp(split[cmd_pos - 1], ">") == 0)
		type = 'r';
	else if (ft_strcmp(split[cmd_pos - 1], ">>") == 0)
		type = 'a';
	if (!type)
		return ;
	sp = space_pos(split[cmd_pos]);
	if (sp != -1)
		exec->redir[exec->redir_count].file = ft_substr(split[cmd_pos], 0, sp);
	else
		exec->redir[exec->redir_count].file = ft_strdup(split[cmd_pos]);
	if (!exec->redir[exec->redir_count].file)
		return ;
	unmask_spaces(exec->redir[exec->redir_count].file);
	end_pre_redir(exec, type);
}

void	collect_redirs(t_exec *exec, char **split, int cmd_pos, char **envp)
{
	int	count;

	count = count_redirs(split, cmd_pos);
	if (count == 0)
		return ;
	if (!init_redirs(exec, count))
		return ;
	collect_pre_redir(exec, split, cmd_pos);
	collect_redirs_sequel(exec, split, cmd_pos, 0);
	end_collect_redir(exec, envp);
}
