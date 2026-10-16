/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 07:49:44 by lukrodri          #+#    #+#             */
/*   Updated: 2026/05/06 07:49:46 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

int	has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			return (1);
		i++;
	}
	return (0);
}

char	*strip_quotes(char *delimiter)
{
	char	*result;
	int		i;
	int		j;

	result = malloc(ft_strlen(delimiter) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (delimiter[i])
	{
		if (delimiter[i] != 34 && delimiter[i] != 39)
			result[j++] = delimiter[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

void	child_heredoc(t_exec *exec, char *delim,
							char **envp, int *pipefd)
{
	char	*line;
	int		normal_exit;
	int		expand;

	normal_exit = 0;
	expand = exec->data->expand;
	check_exec(exec);
	g_ack = 0;
	signal(SIGINT, handle_sigint_son);
	while (1)
	{
		line = get_line_heredoc(exec, delim, pipefd);
		if (handle_heredoc_end(&normal_exit, line, delim))
			break ;
		expand_heredoc(exec->data->expand, line, pipefd, envp);
	}
	free_son_heredoc(exec, delim, pipefd, 0);
}
