/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <alexfuen@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 21:30:40 by alexfuen          #+#    #+#             */
/*   Updated: 2026/10/19 21:30:40 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

int	update_flag(int flag)
{
	if (flag)
		return (0);
	return (1);
}

void	move_one(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = str[i + 1];
		if (!str[i])
			break ;
		i++;
	}
}

void	remove_quotes(char *str)
{
	int		i;
	char	c;
	char	*chr;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
		{
			c = str[i];
			chr = ft_strchr(&str[i + 1], c);
			if (chr)
			{
				move_one(&str[i]);
				chr--;
				while (&str[i] != chr)
					i++;
				move_one(&str[i]);
			}
			else
				i++;
		}
		else
			i++;
	}
}

int	split_len(char **split)
{
	int	i;

	i = 0;
	if (!split || !(*split))
		return (0);
	while (split[i])
		i++;
	return (i);
}

void	free_split(char **split, int flag)
{
	int	i;

	if (!split)
		return ;
	if (!flag)
		i = 0;
	else
		i = 1;
	while (split && split[i])
		free(split[i++]);
	if (split)
		free(split);
}
