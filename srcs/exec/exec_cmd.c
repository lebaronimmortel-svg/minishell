/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 12:08:51 by lukrodri          #+#    #+#             */
/*   Updated: 2026/04/27 12:08:53 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

void	set_end_split(char **split, int cmd_pos, int i, int sp)
{
	char	*extra;

	extra = ft_strdup(&split[i + 1][sp + 1]);
	if (extra)
	{
		append_to_cmd(split, cmd_pos, extra);
		free(extra);
	}
	split[i + 1][sp] = '\0';
}

void	preprocess_split(char **split, int i, int cmd_pos)
{
	int		sp;

	while (split && split[i])
	{
		if (is_pipe(split[i]))
			cmd_pos = i + 1;
		else if (split[i][0] == '<' || split[i][0] == '>')
		{
			if (split[i + 1])
			{
				sp = space_pos(split[i + 1]);
				if (sp != -1)
					set_end_split(split, cmd_pos, i, sp);
				i++;
			}
		}
		i++;
	}
}

int	exec_cmd(t_exec *exec, t_data *data, char **split)
{
	int	saved_stdin;
	int	saved_stdout;
	int	result;

	exec->env = data->env;
	exec->redir_count = 0;
	exec->redir = NULL;
	collect_redirs(exec, split, 0, data->env);
	result = 0;
	if (exec->redir_count > 0)
	{
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
		result = apply_redirs(exec);
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
	}
	return (result);
}
