/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <alexfuen@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 21:30:40 by alexfuen          #+#    #+#             */
/*   Updated: 2026/10/19 21:30:40 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

int	check_space(const char *str, int i)
{
	while (str[i] == '\t'
		|| str[i] == '\n'
		|| str[i] == '\v'
		|| str[i] == '\f'
		|| str[i] == '\r'
		|| str[i] == ' ')
		return (1);
	return (0);
}

int	calculation(const char *str, int i, int signe, long long *result)
{
	int	digit;

	while (str[i])
	{
		digit = str[i] - '0';
		if (digit < 0 || digit > 9)
			return (0);
		if (signe == 1)
		{
			if (*result > (LLONG_MAX - digit) / 10)
				return (0);
		}
		if (signe == -1)
		{
			if (*result * (-1) < (LLONG_MIN + digit) / 10)
				return (0);
		}
		if (str[i] >= '0' && str[i] <= '9')
			*result = *result * 10 + str[i] - '0';
		else
			return (1);
		i++;
	}
	return (1);
}

int	pwd(void)
{
	char	buffer[1024];

	if (getcwd(buffer, sizeof(buffer)) != NULL)
	{
		ft_putstr_fd(buffer, 1);
		write(1, "\n", 1);
		return (0);
	}
	else
	{
		perror("getcwd");
		return (1);
	}
}

int	env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], 1);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
