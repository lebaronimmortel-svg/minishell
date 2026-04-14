/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:44:09 by lukrodri          #+#    #+#             */
/*   Updated: 2026/04/02 11:44:10 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

void	end_collect_redir(t_exec *exec, char **envp)
{
	int	k;

	k = 0;
	while (k < exec->redir_count)
	{
		if (exec->redir[k].type == 'h' && exec->redir[k].fd == -1)
			exec->redir[k].fd = handle_heredoc(exec->redir[k].file, envp);
		k++;
	}
}
