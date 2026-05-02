/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 02:51:24 by alexfuen          #+#    #+#             */
/*   Updated: 2026/04/09 02:51:26 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

static int	check_space(const char *str, int i)
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

static int	calcul(const char *str, int i, int signe, long long *result)
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

long long	ft_atoll(const char *nptr, long long *result)
{
	int	i;
	int	signe;

	i = 0;
	signe = 1;
	while (check_space(nptr, i))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			signe = -1;
		i++;
	}
	if (!calcul(nptr, i, signe, result))
		return (0);
	*result = *result * signe;
	return (1);
}

static char	*get_user(t_data *data)
{
	int		i;
	char	*result;
	char	**split;

	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], "USER=", 5))
		{
			split = ft_split(data->env[i], '=');
			if (!split)
				return (NULL);
			result = ft_strdup(split[1]);
			if (!result)
				return (NULL);
			free_split(split, 0);
			return (result);
		}
		i++;
	}
	return (NULL);
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

int cd(char *input, t_data *data)
{
    char        *path;
    char        buffer[1024];
    struct stat info;

    path = &input[3];
    unmask_spaces(path);
    if (ft_strchr(path, ' '))
    {
        ft_putstr_fd("cd: too many arguments\n", 2);
        return (1);
    }
    if (!(*path) || (ft_strlen(path) == 1 && path[0] == '~'))
        return (get_home_path(path, data));
    if (stat(path, &info) != 0)
    {
        ft_putstr_fd("cd: no such file or directory\n", 2);
        return (1);
    }
    if (access(path, X_OK) != 0)
    {
        ft_putstr_fd("cd: permission denied\n", 2);
        return (1);
    }

    if (!getcwd(buffer, sizeof(buffer)))
        buffer[0] = '\0';
    change_path(0, buffer, data);

    if (chdir(path))
        return (1);

    if (!getcwd(buffer, sizeof(buffer)))
    {
        ft_putstr_fd("cd: error retrieving current directory\n", 2);
        return (1);
    }
    change_path(1, buffer, data);
    return (0);
}

static int	pwd(void)
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

static int	env(char **envp)
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

static int	is_numeric_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

static int	status_code(char *input, t_data *data)
{
	char		**args;
	long long	code;
	int			i;
	int			len;

	args = ft_split(input, ' ');
	if (!args)
		return (data->error_code);
	i = 0;
	while (args[i])
	{
		unmask_spaces(args[i]);
		i++;
	}
	len = i;
	if (len == 1)
	{
		free_split(args, 0);
		data->end = 1;
		return (data->error_code);
	}
	code = 0;
	if (!is_numeric_arg(args[1]) || !ft_atoll(args[1], &code))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_split(args, 0);
		data->end = 1;
		return (2);
	}
	if (len > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		free_split(args, 0);
		return (1);
	}
	free_split(args, 0);
	data->end = 1;
	return ((code % 256 + 256) % 256);
}

int	exec_built_in(char *input, t_data *data, char **cmd_split, int i)
{
	char	**split;
	int		status;

	status = 0;
	if (!ft_strncmp(input, "pwd", 3) && ft_strlen(input) == 3)
		status = pwd();
	if (!ft_strncmp(input, "pwd ", 4))
		status = pwd();
	else if (!ft_strncmp(input, "unset", 5) && ft_strlen(input) == 5)
		status = 0;
	else if (!ft_strncmp(input, "unset ", 6))
	{
		split = ft_split(input, ' ');
		if (!split)
			return (-1);
		split = quote_clean(split);
		status = unset(&split[1], data);
		free_split(split, 0);
	}
	else if (!ft_strncmp(input, "env", 3) && ft_strlen(input) == 3)
		status = env(data->env);
	else if (!ft_strncmp(input, "env ", 4))
		status = env(data->env);
	else if (!ft_strncmp(input, "exit", 4)
		&& ft_strlen(input) == 4)
	{
		status = status_code(input, data);
		data->end = 1;
	}
	else if (!ft_strncmp(input, "exit ", 5))
	{
		if (my_memlen(cmd_split) > i + 1)
			status = status_code(input, data);
		else
		{
			status = status_code(input, data);
			if (status != 1)
				data->end = 1;
		}
	}
	else if (!ft_strncmp(input, ".", 1) && ft_strlen(input) == 1)
	{
		ft_putstr_fd(" filename argument required . filename [arguments]\n", 2);
		status = 2;
	}
	else if (!ft_strncmp(input, "echo ", 5) || (!ft_strncmp(input, "echo", 4) && ft_strlen(input) == 4))
	{
		split = ft_split(input, ' ');
		if (!split)
			return (-1);
		status = echo(input, 0);
		free_split(split, 0);
	}
	else if ((!ft_strncmp(input, "export", 6)) && ft_strlen(input) == 6)
		export_single(data);
	else if ((!ft_strncmp(input, "export ", 7)))
		status = ft_export(input, data, 0, 0);
	else if (!ft_strncmp(input, "cd ", 3)
		|| (!ft_strncmp(input, "cd", 2)
			&& ft_strlen(input) == 2))
		status = cd(input, data);
	return (status);
}
