/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_third_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 08:55:08 by lukrodri          #+#    #+#             */
/*   Updated: 2026/04/16 08:55:09 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

void	unmask_spaces(char *str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\1')
			str[i] = ' ';
		i++;
	}
}

char	**quote_clean(char **split)
{
	int	i;
	int	j;

	i = 0;
	while (split && split[i])
	{
		j = 0;
		while (split[i][j])
		{
			if (split[i][j] == '\1')
				split[i][j] = ' ';
			j++;
		}
		i++;
	}
	return (split);
}

char	*change_var_hd(char *str, char **envp)
{
	int		i;
	char	*tmp;

	i = 0;
	while (!(str[i] == '$' && is_valid_var(&str[i], 0)))
		i++;
	tmp = convert_var(str, i, envp);
	free(str);
	return (tmp);
}
