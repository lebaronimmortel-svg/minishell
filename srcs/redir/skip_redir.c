/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 10:01:31 by lukrodri          #+#    #+#             */
/*   Updated: 2026/04/02 10:01:32 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

int	is_pipe(char *s)
{
	return (s && s[0] == '|');
}

int	skip_redirection(char **split, int i)
{
	if (split[i][0] == '<' || split[i][0] == '>')
	{
		if (split[i][1] == split[i][0])
			return (i + 2);
		return (i + 1);
	}
	return (i);
}

int	should_skip_empty(char **split, int i)
{
	if (split[i][0] != 0)
		return (0);
	if (split[i + 1]
		&& (split[i + 1][0] == '<' || split[i + 1][0] == '>')
		&& split[i + 1][1] != split[i + 1][0]
		&& split[i + 2]
		&& space_pos(split[i + 2]) != -1)
		return (1);
	return (0);
}

int	is_redir_argument(char **split, int i)
{
	if (i >= 1
		&& (split[i - 1][0] == '<' || split[i - 1][0] == '>')
		&& split[i - 1][1] != split[i - 1][0]
		&& space_pos(split[i]) == -1)
		return (1);
	return (0);
}

int	has_redir_after_empty(char **split, int i)
{
	i++;
	while (split[i] && split[i][0] != '|')
	{
		if (split[i][0] == '<' || split[i][0] == '>')
			return (1);
		i++;
	}
	return (0);
}
