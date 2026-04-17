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
			printf("%s\n", data->env[i]);
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
		return (0);
	path = ft_strjoin("cd /home/", user);
	if (!path)
		return (0);
	free(user);
	cd(path, data);
	free(path);
	return (1);
}

int	cd(char *input, t_data *data)
{
	char	*path;
	char	buffer[1024];

	(void)data;
	path = &input[3];
	unmask_spaces(path);
	if (!(*path) || (ft_strlen(path) == 1 && path[0] == '~'))
		return (get_home_path(path, data));
	if (!getcwd(buffer, sizeof(buffer)))
		return (0);
	if (chdir(path))
		return (0);
	change_path(0, buffer, data);
	if (!getcwd(buffer, sizeof(buffer)))
		return (0);
	change_path(1, buffer, data);
	return (1);
}

static void	pwd(void)
{
	char	buffer[1024];

	if (getcwd(buffer, sizeof(buffer)) != NULL)
	{
		ft_putstr_fd(buffer, 1);
		write(1, "\n", 1);
	}
	else
		perror("getcwd");
}

static void	env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], 1);
		write(1, "\n", 1);
		i++;
	}
}

static int	status_code(char *input, t_data *data)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != ' ')
		i++;
	if (!input[i])
		return (data->error_code);
	return (ft_atoi(&input[i]));
}

void	exec_built_in(char *input, t_data *data, char **cmd_split)
{
	char	**split;

	if (!ft_strncmp(input, "pwd", 3) && ft_strlen(input) == 3)
		pwd();
	else if (!ft_strncmp(input, "unset ", 6))
	{
		split = ft_split(input, ' ');
		split = quote_clean(split);
		unset(&split[1], data);
		free_split(split, 0);
	}
	else if (!ft_strncmp(input, "env", 3) && ft_strlen(input) == 3)
		env(data->env);
	else if ((!ft_strncmp(input, "exit", 4)
			&& ft_strlen(input) == 4)
		|| (!ft_strncmp(input, "exit ", 5)))
		exit_cleanly(status_code(input, data), data, cmd_split);
	else if ((!ft_strncmp(input, "echo ", 5)))
	{
		split = ft_split(input, ' ');
		echo(input, 0);
		free_split(split, 0);
	}
	else if ((!ft_strncmp(input, "export", 6)) && ft_strlen(input) == 6)
		export_single(data);
	else if ((!ft_strncmp(input, "export ", 7)))
		ft_export(input, data, 0, 0);
	else if (!ft_strncmp(input, "cd ", 3)
		|| (!ft_strncmp(input, "cd", 2)
			&& ft_strlen(input) == 2))
		cd(input, data);
}
