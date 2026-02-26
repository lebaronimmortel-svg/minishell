/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:32:01 by lukrodri          #+#    #+#             */
/*   Updated: 2025/10/24 15:32:02 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_cpy(char *tmp, char *g_stock, int i, int j)
{
	int	start;

	start = 0;
	while (g_stock && j < i)
	{
		tmp[start++] = g_stock[j + 1];
		j++;
	}
	tmp[start] = '\0';
	return (tmp);
}

int	ft_strlens(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	is_ins(char *g_stock)
{
	int	i;

	i = 0;
	while (g_stock && g_stock[i])
	{
		if (g_stock[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_realloc(int len, char *g_stock, int size)
{
	char	*tmp;
	int		i;

	tmp = malloc(size + len + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	while (g_stock && g_stock[i] && i < size)
	{
		tmp[i] = g_stock[i];
		i++;
	}
	tmp[i] = '\0';
	free(g_stock);
	return (tmp);
}

void	ft_free_gnl(int fd, char **g_stock, char **tmp_buffer)
{
	if (*tmp_buffer)
	{
		free(*tmp_buffer);
		*tmp_buffer = NULL;
	}
	if (fd == 0 && *g_stock)
	{
		free(*g_stock);
		*g_stock = NULL;
	}
}
