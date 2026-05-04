/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 21:35:05 by alexfuen          #+#    #+#             */
/*   Updated: 2026/05/04 21:35:07 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

long long	atoll_loop(const char *str, int i, int sign, long long *result)
{
	int	digit;

	while (str[i])
	{
		digit = str[i] - '0';
		if (digit < 0 || digit > 9)
			return (0);
		if (sign == 1)
		{
			if (*result > (LLONG_MAX - digit) / 10)
				return (0);
		}
		if (sign == -1)
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

long long	ft_atoll(const char *nptr, long long *result)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while (check_space(nptr, i))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	if (!atoll_loop(nptr, i, sign, result))
		return (0);
	*result = *result * sign;
	return (1);
}

int	get_home_path(char *path, t_data *data)
{
	char	*user;

	user = get_user(data);
	if (!user)
		return (1);
	path = ft_strjoin("cd /home/", user);
	if (!path)
		return (1);
	free(user);
	cd(path, data);
	free(path);
	return (0);
}

int	display_cd_error_msg(int flag)
{
	if (flag == 1)
		ft_putstr_fd("cd: too many arguments\n", 2);
	else if (flag == 2)
		ft_putstr_fd("cd: no such file or directory\n", 2);
	else if (flag == 3)
		ft_putstr_fd("cd: permission denied\n", 2);
	else if (flag == 4)
		ft_putstr_fd("cd: error retrieving current directory\n", 2);
	return (1);
}

int	cd(char *input, t_data *data)
{
	char		*path;
	char		buffer[1024];
	struct stat	info;

	path = &input[3];
	unmask_spaces(path);
	if (ft_strchr(path, ' '))
		return (display_cd_error_msg(1));
	if (!(*path) || (ft_strlen(path) == 1 && path[0] == '~'))
		return (get_home_path(path, data));
	if (stat(path, &info) != 0)
		return (display_cd_error_msg(2));
	if (access(path, X_OK) != 0)
		return (display_cd_error_msg(3));
	if (!getcwd(buffer, sizeof(buffer)))
		buffer[0] = '\0';
	change_path(0, buffer, data);
	if (chdir(path))
		return (1);
	if (!getcwd(buffer, sizeof(buffer)))
		return (display_cd_error_msg(4));
	change_path(1, buffer, data);
	return (0);
}
