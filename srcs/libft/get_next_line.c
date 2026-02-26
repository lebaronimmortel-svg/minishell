/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:31:51 by lukrodri          #+#    #+#             */
/*   Updated: 2025/10/24 15:31:53 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ncpy(char *g_stock, char *result, int i)
{
	while (g_stock && g_stock[i] && g_stock[i] != '\n')
	{
		result[i] = g_stock[i];
		i++;
	}
	if (g_stock[i] == '\n')
	{
		result[i] = '\n';
		i++;
	}
	result[i] = '\0';
	return (result);
}

static char	*ft_trim(char *g_stock, char **result)
{
	int		i;
	int		j;
	char	*tmp;

	if (ft_strlens(g_stock) == 0)
	{
		free(g_stock);
		return (NULL);
	}
	j = 0;
	i = ft_strlens(g_stock);
	while (g_stock && j < ft_strlens(g_stock) && g_stock[j] != '\n')
		j++;
	tmp = malloc(i - j + 1);
	if (!tmp)
	{
		free(g_stock);
		free(*result);
		*result = NULL;
		return (NULL);
	}
	tmp = ft_cpy(tmp, g_stock, i, j);
	free(g_stock);
	return (tmp);
}

static char	*ft_result(char **g_stock)
{
	int		i;
	int		j;
	char	*result;

	if (ft_strlens(*g_stock) == 0)
		return (NULL);
	j = 0;
	while (*g_stock && j < ft_strlens(*g_stock) && (*g_stock)[j] != '\n')
		j++;
	if ((*g_stock)[j] == '\n')
		result = malloc(j + 2);
	else
		result = malloc(j + 1);
	if (!result)
		return (NULL);
	i = 0;
	result = ft_ncpy(*g_stock, result, i);
	*g_stock = ft_trim(*g_stock, &result);
	return (result);
}

static char	*ft_stock(char *tmp_buffer, int to_read, int fd, char *g_stock)
{
	int		i;
	int		size;

	size = ft_strlens(g_stock);
	while (is_ins(g_stock) == 0 && to_read > 0)
	{
		tmp_buffer[to_read] = '\0';
		i = 0;
		g_stock = ft_realloc(to_read, g_stock, size);
		if (!g_stock)
			return (NULL);
		while (i < to_read)
		{
			g_stock[size + i] = tmp_buffer[i];
			i++;
		}
		g_stock[size + i] = '\0';
		if (is_ins(g_stock) == 0)
		{
			to_read = read(fd, tmp_buffer, BUFFER_SIZE);
			size += i;
		}
	}
	return (g_stock);
}

char	*get_next_line(int fd)
{
	static char	*g_stock;
	int			to_read;
	char		*tmp_buffer;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	to_read = 0;
	tmp_buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!tmp_buffer)
	{
		free(tmp_buffer);
		return (NULL);
	}
	if (is_ins(g_stock) == 0)
		to_read = read(fd, tmp_buffer, BUFFER_SIZE);
	g_stock = ft_stock(tmp_buffer, to_read, fd, g_stock);
	result = ft_result(&g_stock);
	if (ft_strlen(g_stock) == 0 && to_read == 0)
	{
		free(g_stock);
		g_stock = NULL;
	}
	ft_free_gnl(fd, &g_stock, &tmp_buffer);
	return (result);
}
